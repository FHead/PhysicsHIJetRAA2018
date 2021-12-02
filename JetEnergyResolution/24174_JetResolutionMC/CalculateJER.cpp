#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooArgSet.h"
#include "RooPlot.h"
using namespace RooFit;

#include "CommandLine.h"
#include "ProgressBar.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "Code/DrawRandom.h"
#include "DataHelper.h"

struct Jet;
int main(int argc, char *argv[]);
double GaussianRMSCorrection(double FractionEachSide);

struct Jet
{
   float PT;
   float R;
   bool operator <(const Jet &other) const
   {
      if(PT < other.PT)   return true;
      if(PT > other.PT)   return false;
      if(R < other.R)     return true;
      if(R > other.R)     return false;
      return false;
   }
};

int main(int argc, char *argv[])
{
   SetThesisStyle();
   CommandLine CL(argc, argv);

   string InputFileName    = CL.Get("Input");
   double Fraction         = CL.GetDouble("Fraction", 1.00);
   string OutputFileName   = CL.Get("Output");
   string DHFileName       = CL.Get("DHFile");

   int GenBin              = CL.GetInt("GenBin", 20);
   double GenPTMin         = CL.GetDouble("GenPTMin", 30);
   int MinStats            = CL.GetInt("MinStats", 10000);
   float FractionEachSide  = CL.GetDouble("FractionEachSide", 0.025);

   double RMSCorrection = GaussianRMSCorrection(FractionEachSide);

   vector<float> EtaBins{-2.0, -1.7, -1.3, -1.1, -0.8, -0.5, 0.0, 0.5, 0.8, 1.1, 1.3, 1.7, 2.0};
   // vector<float> EtaBins{-2.0, -1.7, -1.3, -1.1};
   sort(EtaBins.begin(), EtaBins.end());
   int NEtaBin = EtaBins.size() - 1;

   DataHelper DHFile(DHFileName);

   DHFile["EtaBins"]["N"] = NEtaBin;
   for(int i = 0; i <= NEtaBin; i++)
      DHFile["EtaBins"]["Eta_"+to_string(i)] = EtaBins[i];

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("JER FITS");

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get("JERTree");

   int NJet = 0;
   vector<float> *Eta = nullptr;
   vector<float> *GenPT = nullptr;
   vector<float> *RecoPT = nullptr;

   Tree->SetBranchAddress("NJet",   &NJet);
   Tree->SetBranchAddress("Eta",    &Eta);
   Tree->SetBranchAddress("GenPT",  &GenPT);
   Tree->SetBranchAddress("RecoPT", &RecoPT);

   for(int iEta = 0; iEta < NEtaBin; iEta++)
   {
      PdfFile.AddTextPage(Form("Eta: [%.2f, %.2f]", EtaBins[iEta], EtaBins[iEta+1]));

      int EntryCount = Tree->GetEntries() * Fraction;

      vector<Jet> Jets;

      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         if(EntryCount < 300 || (iE % (EntryCount / 200) == 0))
         {
            Bar.Update(iE);
            Bar.Print();
         }

         for(int iJ = 0; iJ < NJet; iJ++)
         {
            if(Eta->at(iJ) < EtaBins[iEta] || Eta->at(iJ) > EtaBins[iEta+1])
               continue;
            if(GenPT->at(iJ) < GenPTMin)
               continue;

            Jets.push_back({GenPT->at(iJ), RecoPT->at(iJ) / GenPT->at(iJ)});
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      sort(Jets.begin(), Jets.end());

      int BinCount = GenBin;
      if(Jets.size() < BinCount * MinStats)
         BinCount = Jets.size() / MinStats;
      int BinStats = Jets.size() / BinCount;

      DHFile["EtaBins"]["PTBinCount_"+to_string(iEta)] = BinCount;
      DHFile["EtaBins"]["PTBinStats_"+to_string(iEta)] = BinStats;

      for(int iB = 0; iB < BinCount; iB++)
      {
         int Min = iB * BinStats;
         int Max = (iB + 1) * BinStats;
         if(iB == BinCount - 1)   // make sure we don't waste jets
            Max = Jets.size();

         double MinPT = Jets[Min].PT;
         double MaxPT = Jets[Max-1].PT;

         double SumPT = 0;
         for(int iJ = Min; iJ < Max; iJ++)
            SumPT = SumPT + Jets[iJ].PT;
         double MeanPT = SumPT / (Max - Min);

         vector<float> Rs(Max - Min);
         for(int iJ = Min; iJ < Max; iJ++)
            Rs[iJ-Min] = Jets[iJ].R;

         sort(Rs.begin(), Rs.end());

         int ToDiscardEachSide = FractionEachSide * (Max - Min);

         double MinR = Rs[ToDiscardEachSide];
         double MaxR = Rs[(Max-Min-1)-ToDiscardEachSide];

         RooRealVar R("R", Form("R GenPT [%.2f,%.2f]", MinPT, MaxPT), MinR, MaxR);
         RooRealVar Mean("Mean", "", MinR, MaxR);
         RooRealVar Width("Width", "", 0.02, 1.5);
         RooGaussian Gauss("Gauss", "", R, Mean, Width);

         double SumR0 = 0;
         double SumR1 = 0;
         double SumR2 = 0;

         RooDataSet Data("Data", "", RooArgSet(R));
         for(int i = ToDiscardEachSide; i < (Max - Min) - ToDiscardEachSide; i++)
         {
            R = Rs[i];
            Data.add(RooArgSet(R));

            SumR0 = SumR0 + 1;
            SumR1 = SumR1 + Rs[i];
            SumR2 = SumR2 + Rs[i] * Rs[i];
         }

         RooFitResult *Result = Gauss.fitTo(Data, Save());

         cout << "PT Range: [" << MinPT << ", " << MaxPT << "], Mean = " << Mean.getVal() << ", Sigma = " << Width.getVal() << endl;

         RooPlot *Frame = R.frame();
         Data.plotOn(Frame);
         Gauss.plotOn(Frame);

         PdfFile.AddPlot(Frame);

         string State = Form("Eta%dPT%d", iEta, iB);

         DHFile[State]["EtaMin"]       = EtaBins[iEta];
         DHFile[State]["EtaMax"]       = EtaBins[iEta+1];
         DHFile[State]["PTMin"]        = MinPT;
         DHFile[State]["PTMax"]        = MaxPT;
         DHFile[State]["MeanPT"]       = MeanPT;
         DHFile[State]["Excluded"]     = FractionEachSide;

         DHFile[State]["Mean"]         = Mean.getVal();
         DHFile[State]["MeanError"]    = Mean.getError();
         DHFile[State]["Width"]        = Width.getVal();
         DHFile[State]["WidthError"]   = Width.getError();

         double VisibleRMS = sqrt((SumR2 - SumR1 * SumR1 / SumR0) / (SumR0));

         DHFile[State]["Average"]      = SumR1 / SumR0;
         DHFile[State]["VisibleRMS"]   = VisibleRMS;
         DHFile[State]["CorrectedRMS"] = VisibleRMS * RMSCorrection;
      }
   }

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   DHFile.SaveToFile();

   return 0;
}

double GaussianRMSCorrection(double FractionEachSide)
{
   int Tries = 1000000;

   double Sum0 = 0;
   double Sum1 = 0;
   double Sum2 = 0;

   vector<double> Xs;
   for(int i = 0; i < Tries; i++)
   {
      double X = DrawGaussian(0, 1);
      Xs.push_back(X);
   }

   sort(Xs.begin(), Xs.end());

   for(int i = FractionEachSide * Tries; i < Tries * (1 - FractionEachSide); i++)
   {
      Sum0 = Sum0 + 1;
      Sum1 = Sum1 + Xs[i];
      Sum2 = Sum2 + Xs[i] * Xs[i];
   }

   double RMS = sqrt((Sum2 - Sum1 * Sum1 / Sum0) / Sum0);
   return 1 / RMS;
}






