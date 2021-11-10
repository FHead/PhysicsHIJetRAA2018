#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TF1.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "CustomAssert.h"
#include "SetStyle.h"
#include "ProgressBar.h"

int main(int argc, char *argv[]);
bool IsExcluded(double Eta, double Phi, vector<double> &Exclusion);
int FindBin(double Value, vector<double> &Bins);
vector<double> CalculateCn(TProfile *P, int NMax);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> FileNames    = CL.GetStringVector("Input", vector<string>{});
   string OutputFileName       = CL.Get("Output", "Result.pdf");
   vector<double> EtaBinning   = CL.GetDoubleVector("Eta", vector<double>{-2.0, -1.0, 0.0, 1.0, 2.0});
   vector<double> JetExclusion = CL.GetDoubleVector("Exclusion", vector<double>{});
   vector<double> PTBinning    = CL.GetDoubleVector("PT", vector<double>{50, 100, 200, 300, 500, 750, 1000, 9999});
   vector<double> RhoBinning   = CL.GetDoubleVector("Rho", vector<double>{0, 100, 200, 300, 400, 500, 600, 9999});
   int NPhi                    = CL.GetInt("NPhi", 20);
   double JetR                 = CL.GetDouble("JetR", 0.4);
   int NMax                    = CL.GetInt("NMax", 4);

   double JetArea = JetR * JetR * M_PI;
            
   Assert(EtaBinning.size() > 1,        "We need at least one eta bin");
   Assert(PTBinning.size() > 1,         "We need at least one PT bin");
   Assert(RhoBinning.size() > 1,        "We need at least one Rho bin");
   Assert(JetR > 0,                     "Nonsense jet radius detected!");
   Assert(NPhi >= 10,                   "Please specify a valid phi binning count.  It's too small now.");
   Assert(JetExclusion.size() % 4 == 0, "Format: {eta min, eta max, phi min, phi max}^n");

   // Line up eta binning so that within each eta bin it's always full exclusion or no exclusion
   for(int i = 0; i + 4 <= (int)JetExclusion.size(); i = i + 4)
   {
      EtaBinning.push_back(JetExclusion[i+0]);
      EtaBinning.push_back(JetExclusion[i+1]);
   }
   sort(EtaBinning.begin(), EtaBinning.end());
   EtaBinning.erase(unique(EtaBinning.begin(), EtaBinning.end()), EtaBinning.end());

   int NEta = EtaBinning.size() - 1;
   int NPT  = PTBinning.size() - 1;
   int NRho = RhoBinning.size() - 1;

   // Exclusion min-max switch if needed
   for(int i = 0; i + 2 < (int)JetExclusion.size(); i = i + 2)
      if(JetExclusion[i] > JetExclusion[i+1])
         swap(JetExclusion[i], JetExclusion[i+1]);

   // Create the profile histograms
   vector<vector<vector<TProfile *>>> P;
   P.resize(NEta);
   for(int iEta = 0; iEta < NEta; iEta++)
   {
      P[iEta].resize(NPT);
      for(int iPT = 0; iPT < NPT; iPT++)
      {
         P[iEta][iPT].resize(NRho);
         for(int iRho = 0; iRho < NRho; iRho++)
         {
            string Range = Form("Eta: [%.2f, %.2f], PT: [%.1f, %.1f], Rho: [%.1f, %.1f]",
               EtaBinning[iEta], EtaBinning[iEta+1],
               PTBinning[iPT], PTBinning[iPT+1],
               RhoBinning[iRho], RhoBinning[iRho+1]);
            P[iEta][iPT][iRho] = new TProfile(Form("PResponse_%d_%d_%d", iEta, iPT, iRho),
               (Range + ";Jet #phi;<R>").c_str(), NPhi, -M_PI, M_PI);
         }
      }
   }
   TProfile POverall("PResponseOverall", "Overall;Jet #phi;<R>", NPhi, -M_PI, M_PI);

   double CY[100] = {0};
   double SY[100] = {0};
   double CC[100][100] = {0};
   double CS[100][100] = {0};
   double SC[100][100] = {0};
   double SS[100][100] = {0};

   // Loop over input files
   for(string FileName : FileNames)
   {
      TFile File(FileName.c_str());

      TTree *Tree = (TTree *)File.Get("UnfoldingTree");

      if(Tree == nullptr)
      {
         File.Close();
         continue;
      }

      vector<float> *GenJetPT = nullptr;
      vector<float> *GenJetEta = nullptr;
      vector<float> *GenJetPhi = nullptr;
      vector<float> *MatchedJetPT = nullptr;
      vector<float> *MatchedJetEta = nullptr;
      vector<float> *MatchedJetPhi = nullptr;
      vector<float> *MatchedJetRho = nullptr;
      vector<float> *MatchedJetUE = nullptr;

      Tree->SetBranchAddress("GenJetPT", &GenJetPT);
      Tree->SetBranchAddress("GenJetEta", &GenJetEta);
      Tree->SetBranchAddress("GenJetPhi", &GenJetPhi);
      Tree->SetBranchAddress("MatchedJetPT", &MatchedJetPT);
      Tree->SetBranchAddress("MatchedJetEta", &MatchedJetEta);
      Tree->SetBranchAddress("MatchedJetPhi", &MatchedJetPhi);
      Tree->SetBranchAddress("MatchedJetRho", &MatchedJetRho);
      Tree->SetBranchAddress("MatchedJetUE", &MatchedJetUE);

      int EntryCount = Tree->GetEntries();
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(5);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         Bar.Update(iE);
         if(EntryCount < 500 || (iE % (EntryCount / 300) == 0))
            Bar.Print();

         int NJet = GenJetPT->size();

         for(int iJ = 0; iJ < NJet; iJ++)
         {
            if(GenJetPT->at(iJ) < PTBinning[0])
               continue;

            double AverageRho = MatchedJetUE->at(iJ) / JetArea;

            int IEta = FindBin(GenJetEta->at(iJ), EtaBinning);
            int IPT  = FindBin(GenJetPT->at(iJ), PTBinning);
            int IRho = FindBin(AverageRho, RhoBinning);

            if(IEta < 0 || IPT < 0 || IRho < 0)   // Not in range of current run
               continue;

            if(IsExcluded(GenJetEta->at(iJ), GenJetPhi->at(iJ), JetExclusion) == true)
               continue;

            double R = MatchedJetPT->at(iJ) / GenJetPT->at(iJ);
            double Phi = GenJetPhi->at(iJ);

            for(int i = 0; i < NMax; i++)
            {
               CY[i] = CY[i] + cos(i * Phi) * R;
               SY[i] = SY[i] + sin(i * Phi) * R;
               for(int j = 0; j < NMax; j++)
               {
                  CC[i][j] = CC[i][j] + cos(i * Phi) * cos(j * Phi);
                  SC[i][j] = SC[i][j] + sin(i * Phi) * cos(j * Phi);
                  CS[i][j] = CS[i][j] + cos(i * Phi) * sin(j * Phi);
                  SS[i][j] = SS[i][j] + sin(i * Phi) * sin(j * Phi);
               }
            }

            POverall.Fill(Phi, R);
            P[IEta][IPT][IRho]->Fill(Phi, R);
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   // Output!
   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Residual JEC");

   for(vector<vector<TProfile *>> &VV: P)
   {
      for(vector<TProfile *> &V: VV)
      {
         for(TProfile *X : V)
         {
            if(X != nullptr)
            {
               CalculateCn(X, NMax);
               X->SetStats(0);
               X->SetMinimum(0.75);
               X->SetMaximum(1.25);
               PdfFile.AddPlot(X);
            }
         }
      }
   }
   PdfFile.AddPlot(POverall);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   // Cleanup
   for(vector<vector<TProfile *>> &VV: P)
      for(vector<TProfile *> &V : VV)
         for(TProfile *X : V)
            if(X != nullptr)
               delete X;

   return 0;
}

bool IsExcluded(double Eta, double Phi, vector<double> &Exclusion)
{
   // true = excluded
   if(Exclusion.size() == 0)
      return false;

   for(int i = 0; i + 4 <= (int)Exclusion.size(); i = i + 4)
   {
      if(Eta > Exclusion[i+0] && Eta < Exclusion[i+1])   // eta in range, check phi
      {
         if(Phi > Exclusion[i+2] && Phi < Exclusion[i+3])   // phi also in range, kill
            return true;
         if(Phi + 2 * M_PI > Exclusion[i+2] && Phi + 2 * M_PI < Exclusion[i+3])   // shift phi for wrapping
            return true;
         if(Phi - 2 * M_PI > Exclusion[i+2] && Phi - 2 * M_PI < Exclusion[i+3])   // shift phi for wrapping
            return true;
      }
   }

   return false;
}

int FindBin(double Value, vector<double> &Bins)
{
   for(int i = 0; i + 1 < (int)Bins.size(); i++)
      if(Value >= Bins[i] && Value <= Bins[i+1])
         return i;

   return -1;
}

vector<double> CalculateCn(TProfile *P, int NMax)
{
   if(P == nullptr)
      return vector<double>{1};

   vector<double> Result;

   string Formula = "[0]";
   for(int i = 1; i <= NMax; i++)
      Formula = Formula
         + "+[" + to_string(2 * i - 1) + "]*cos(" + to_string(i) + "*x)"
         + "+[" + to_string(2 * i) + "]*sin(" + to_string(i) + "*x)";

   TF1 F("F", Formula.c_str(), -M_PI, M_PI);
   P->Fit(&F);

   for(int i = 0; i < NMax * 2 + 1; i++)
      Result.push_back(F.GetParameter(i));

   return Result;
}

