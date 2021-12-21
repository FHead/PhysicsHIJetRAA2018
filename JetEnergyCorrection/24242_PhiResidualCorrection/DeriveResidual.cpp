#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TF1.h"
#include "TH2Poly.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "CustomAssert.h"
#include "SetStyle.h"
#include "ProgressBar.h"

struct Jet {double PT; double Eta; double Phi; double Rho; double R;};

int main(int argc, char *argv[]);
bool IsExcluded(double Eta, double Phi, vector<double> &Exclusion);
int FindBin(double Value, vector<double> &Bins);
vector<double> CalculateCn(TH1D *P, int NMax);
vector<double> SplitEvenly(vector<Jet> &Jets, bool UsePT, int NBin);
void SetTH2Poly(TH2Poly &H);
string GetFormula(int NMax);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> FileNames    = CL.GetStringVector("Input", vector<string>{});
   string OutputFileName       = CL.Get("Output", "Result.pdf");
   vector<double> EtaBinning   = CL.GetDoubleVector("Eta", vector<double>{-2.0, -1.0, 0.0, 1.0, 2.0});
   vector<double> JetExclusion = CL.GetDoubleVector("Exclusion", vector<double>{});
   double MinPT                = CL.GetDouble("MinPT", 50);
   int NPT                     = CL.GetInt("NPT", 10);
   int NRho                    = CL.GetInt("NRho", 10);
   int NPhi                    = CL.GetInt("NPhi", 20);
   double JetR                 = CL.GetDouble("JetR", 0.4);
   int NMax                    = CL.GetInt("NMax", 4);
   bool BaseOnGen              = CL.GetBool("BaseOnGen", false);
   
   string CorrectionFile       = CL.Get("Correction", "Correction.txt");
   bool BinnedCorrection       = CL.GetBool("BinnedCorrection", true);

   Assert(BinnedCorrection == true, "Unbinned correction not implemented yet");

   double JetArea = JetR * JetR * M_PI;
            
   Assert(EtaBinning.size() > 1,        "We need at least one eta bin");
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

   // Exclusion min-max switch if needed
   for(int i = 0; i + 2 < (int)JetExclusion.size(); i = i + 2)
      if(JetExclusion[i] > JetExclusion[i+1])
         swap(JetExclusion[i], JetExclusion[i+1]);

   // Create the profile histograms
   vector<vector<vector<TH1D *>>> P;
   P.resize(NEta);
   for(int iEta = 0; iEta < NEta; iEta++)
   {
      P[iEta].resize(NPT);
      for(int iPT = 0; iPT < NPT; iPT++)
      {
         P[iEta][iPT].resize(NRho);
         for(int iRho = 0; iRho < NRho; iRho++)
         {
            P[iEta][iPT][iRho] = new TH1D(Form("MResponse_%d_%d_%d", iEta, iPT, iRho),
               Form("EtaBin%d, PTBin %d, RhoBin %d;Jet #phi;<R>", iEta, iPT, iRho), NPhi, -M_PI, M_PI);
         }
      }
   }
   TH1D POverall("MResponseOverall", "Overall;Jet #phi;<R>", NPhi, -M_PI, M_PI);

   vector<vector<Jet>> Jets(NEta);

   for(string FileName : FileNames)
   {
      TFile File(FileName.c_str());

      TTree *Tree = (TTree *)File.Get("PhiTree");

      if(Tree == nullptr)
      {
         File.Close();
         continue;
      }

      Jet M;
      Tree->SetBranchAddress("PT", &M.PT);
      Tree->SetBranchAddress("Eta", &M.Eta);
      Tree->SetBranchAddress("Phi", &M.Phi);
      Tree->SetBranchAddress("Rho", &M.Rho);
      Tree->SetBranchAddress("R", &M.R);

      int EntryCount = Tree->GetEntries();
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(5);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         Bar.Update(iE);
         if(EntryCount < 500 || (iE % (EntryCount / 300) == 0))
            Bar.Print();

         int IEta = FindBin(M.Eta, EtaBinning);
         if(IEta < 0)   // Not in range of current run
            continue;

         Jets[IEta].push_back(M);

         POverall.Fill(M.Phi, M.R);
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   // Declare output!
   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Residual JEC");

   ofstream out(CorrectionFile.c_str());
   out << "{3 JetEta JetPT JetRho 1 JetPhi 1/(" + GetFormula(NMax) + ") Correction L3Absolute}" << endl;

   // Now we split into bins and fill profiles
   for(int iEta = 0; iEta < NEta; iEta++)
   {
      vector<double> RhoBinning = SplitEvenly(Jets[iEta], false, NRho);
      vector<vector<double>> PTBinning(NRho);
      
      TH2Poly H0, H1C, H1S, H2C, H2S, H3C, H3S, H4C, H4S;
      H0.SetTitle(Form("C0, Eta [%.1f,%.1f]", EtaBinning[iEta], EtaBinning[iEta+1]));
      H1C.SetTitle(Form("C1, Eta [%.1f,%.1f]", EtaBinning[iEta], EtaBinning[iEta+1]));
      H1S.SetTitle(Form("S1, Eta [%.1f,%.1f]", EtaBinning[iEta], EtaBinning[iEta+1]));
      H2C.SetTitle(Form("C2, Eta [%.1f,%.1f]", EtaBinning[iEta], EtaBinning[iEta+1]));
      H2S.SetTitle(Form("S2, Eta [%.1f,%.1f]", EtaBinning[iEta], EtaBinning[iEta+1]));
      H3C.SetTitle(Form("C3, Eta [%.1f,%.1f]", EtaBinning[iEta], EtaBinning[iEta+1]));
      H3S.SetTitle(Form("S3, Eta [%.1f,%.1f]", EtaBinning[iEta], EtaBinning[iEta+1]));
      H4C.SetTitle(Form("C4, Eta [%.1f,%.1f]", EtaBinning[iEta], EtaBinning[iEta+1]));
      H4S.SetTitle(Form("S4, Eta [%.1f,%.1f]", EtaBinning[iEta], EtaBinning[iEta+1]));

      for(int iRho = 0; iRho < NRho; iRho++)
      {
         vector<Jet> RhoJets;
         for(Jet J : Jets[iEta])
            if(J.Rho >= RhoBinning[iRho] && J.Rho < RhoBinning[iRho+1])
               RhoJets.push_back(J);

         PTBinning[iRho] = SplitEvenly(RhoJets, true, NPT);

         for(int iPT = 0; iPT < NPT; iPT++)
         {
            string Ranges = Form("Eta [%.1f,%.1f], PT [%.1f,%.1f], Rho[%.1f,%.1f]",
               EtaBinning[iEta], EtaBinning[iEta+1],
               PTBinning[iRho][iPT], PTBinning[iRho][iPT+1],
               RhoBinning[iRho], RhoBinning[iRho+1]);
            P[iEta][iPT][iRho]->SetTitle(Ranges.c_str());

            vector<vector<double>> Rs(NPhi);

            for(Jet J : RhoJets)
            {
               if(J.PT >= PTBinning[iRho][iPT] && J.PT < PTBinning[iRho][iPT+1])
               {
                  int Bin = (J.Phi - (-M_PI)) / (M_PI - (-M_PI)) * NPhi;
                  Rs[Bin].push_back(J.R);
               }
            }
            for(int iPhi = 0; iPhi < NPhi; iPhi++)
            {
               int N = Rs[iPhi].size();
               if(N < 10)
                  continue;
               sort(Rs[iPhi].begin(), Rs[iPhi].end());
               P[iEta][iPT][iRho]->SetBinContent(iPhi + 1, Rs[iPhi][N/2]);
            }

            double PTMin = PTBinning[iRho][iPT];
            double PTMax = PTBinning[iRho][iPT+1];
            double RhoMin = (RhoBinning[iRho] < 0) ? 0.1 : RhoBinning[iRho];
            double RhoMax = RhoBinning[iRho+1];

            double X[4] = {PTMin, PTMax, PTMax, PTMin};
            double Y[4] = {RhoMin, RhoMin, RhoMax, RhoMax};
            H0.AddBin(4, X, Y);
            H1C.AddBin(4, X, Y);
            H1S.AddBin(4, X, Y);
            H2C.AddBin(4, X, Y);
            H2S.AddBin(4, X, Y);
            H3C.AddBin(4, X, Y);
            H3S.AddBin(4, X, Y);
            H4C.AddBin(4, X, Y);
            H4S.AddBin(4, X, Y);
         }
      }
      
      for(int iRho = 0; iRho < NRho; iRho++)
      {
         vector<vector<double>> Cs(NPT);
         for(int iPT = 0; iPT < NPT; iPT++)
            Cs[iPT] = CalculateCn(P[iEta][iPT][iRho], NMax);
         vector<double> AdjustedBinning = PTBinning[iRho];
         for(int iPT = 0; iPT < NPT - 1; iPT++)
            AdjustedBinning[iPT+1] = PTBinning[iRho][iPT+1] * (Cs[iPT][0] + Cs[iPT+1][0]) / 2;

         for(int iPT = 0; iPT < NPT; iPT++)
         {
            P[iEta][iPT][iRho]->SetStats(0);
            P[iEta][iPT][iRho]->SetMinimum(0.75);
            P[iEta][iPT][iRho]->SetMaximum(1.25);
            PdfFile.AddPlot(P[iEta][iPT][iRho]);
            
            double EtaMin = EtaBinning[iEta];
            double EtaMax = EtaBinning[iEta+1];
            double PTMin = PTBinning[iRho][iPT];
            double PTMax = PTBinning[iRho][iPT+1];
            double RhoMin = (RhoBinning[iRho] < 0) ? 0.1 : RhoBinning[iRho];
            double RhoMax = RhoBinning[iRho+1];

            double PTCenter = (PTMin + PTMax) / 2;
            double RhoCenter = (RhoMin + RhoMax) / 2;
            H0.Fill(PTCenter, RhoCenter, Cs[iPT][0]);
            H1C.Fill(PTCenter, RhoCenter, NMax >= 1 ? Cs[iPT][1] : 0);
            H1S.Fill(PTCenter, RhoCenter, NMax >= 1 ? Cs[iPT][2] : 0);
            H2C.Fill(PTCenter, RhoCenter, NMax >= 2 ? Cs[iPT][3] : 0);
            H2S.Fill(PTCenter, RhoCenter, NMax >= 2 ? Cs[iPT][4] : 0);
            H3C.Fill(PTCenter, RhoCenter, NMax >= 3 ? Cs[iPT][5] : 0);
            H3S.Fill(PTCenter, RhoCenter, NMax >= 3 ? Cs[iPT][6] : 0);
            H4C.Fill(PTCenter, RhoCenter, NMax >= 4 ? Cs[iPT][7] : 0);
            H4S.Fill(PTCenter, RhoCenter, NMax >= 4 ? Cs[iPT][8] : 0);
            
            if(BaseOnGen == true)
            {
               PTMin = AdjustedBinning[iPT];
               PTMax = AdjustedBinning[iPT+1];
            }

            if(iEta == 0)          EtaMin = -9999;
            if(iEta == NEta - 1)   EtaMax = +9999;
            if(iPT == 1)           PTMin = -9999;
            if(iPT == NPT - 1)     PTMax = +9999;
            if(iRho == 0)          RhoMin = -9999;
            if(iRho == NRho - 1)   RhoMax = +9999;

            if(iPT != 0)
            {
               out << EtaMin << " " << EtaMax
                  << " " << PTMin << " " << PTMax
                  << " " << RhoMin << " " << RhoMax
                  << " " << Cs[iPT].size() + 2 << " " << -M_PI << " " << M_PI;
               for(int i = 0; i < (int)Cs.size(); i++)
                  out << " " << Cs[iPT][i];
               out << endl;
            }
         }
      }

      SetTH2Poly(H0);
      SetTH2Poly(H1C);
      SetTH2Poly(H1S);
      SetTH2Poly(H2C);
      SetTH2Poly(H2S);
      SetTH2Poly(H3C);
      SetTH2Poly(H3S);
      SetTH2Poly(H4C);
      SetTH2Poly(H4S);

      TCanvas Canvas;
      Canvas.SetLogx();
      Canvas.SetLogy();

      TH2D HWorld("HWorld", Form("Eta [%.1f, %.1f];p_{T};#bar{#rho}", EtaBinning[iEta], EtaBinning[iEta+1]),
            100, MinPT * 0.8, 1200, 100, 0.1, 300);
      HWorld.SetStats(0);

      HWorld.Draw("axis");
      H0.SetMaximum(1.1);
      H0.SetMinimum(0.9);
      H0.Draw("colz text00 same");
      HWorld.Draw("axis same");
      PdfFile.AddCanvas(Canvas);

      HWorld.Draw("axis");
      H1C.Draw("colz text00 same");
      HWorld.Draw("axis same");
      PdfFile.AddCanvas(Canvas);
      HWorld.Draw("axis");
      H1S.Draw("colz text00 same");
      HWorld.Draw("axis same");
      PdfFile.AddCanvas(Canvas);
      HWorld.Draw("axis");
      H2C.Draw("colz text00 same");
      HWorld.Draw("axis same");
      PdfFile.AddCanvas(Canvas);
      HWorld.Draw("axis");
      H2S.Draw("colz text00 same");
      HWorld.Draw("axis same");
      PdfFile.AddCanvas(Canvas);
      HWorld.Draw("axis");
      H3C.Draw("colz text00 same");
      HWorld.Draw("axis same");
      PdfFile.AddCanvas(Canvas);
      HWorld.Draw("axis");
      H3S.Draw("colz text00 same");
      HWorld.Draw("axis same");
      PdfFile.AddCanvas(Canvas);
      HWorld.Draw("axis");
      H4C.Draw("colz text00 same");
      HWorld.Draw("axis same");
      PdfFile.AddCanvas(Canvas);
      HWorld.Draw("axis");
      H4S.Draw("colz text00 same");
      HWorld.Draw("axis same");
      PdfFile.AddCanvas(Canvas);
   }

   out.close();

   PdfFile.AddPlot(POverall);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   // Cleanup
   for(vector<vector<TH1D *>> &VV: P)
      for(vector<TH1D *> &V : VV)
         for(TH1D *X : V)
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

vector<double> CalculateCn(TH1D *P, int NMax)
{
   if(P == nullptr)
      return vector<double>{1};

   vector<double> Result;

   string Formula = GetFormula(NMax);

   TF1 F("F", Formula.c_str(), -M_PI, M_PI);
   P->Fit(&F);

   for(int i = 0; i < NMax * 2 + 1; i++)
      Result.push_back(F.GetParameter(i));

   return Result;
}

vector<double> SplitEvenly(vector<Jet> &Jets, bool UsePT, int NBin)
{
   Assert(Jets.size() > NBin * 2, Form("Not enough data to split into bins, jets size = %d", Jets.size()));

   vector<double> V;
   for(Jet J : Jets)
   {
      if(UsePT == true)
         V.push_back(J.PT);
      else
         V.push_back(J.Rho);
   }

   sort(V.begin(), V.end());

   vector<double> Result(NBin + 1);
   Result[0] = V[0] - 0.00001;
   for(int i = 1; i < NBin; i++)
      Result[i] = V[(double)V.size()/NBin*i];
   Result[NBin] = V[V.size()-1] + 0.00001;

   return Result;
}

void SetTH2Poly(TH2Poly &H)
{
   H.SetStats(0);
   H.SetMaximum(0.1);
   H.SetMinimum(-0.1);
}

string GetFormula(int NMax)
{
   string Formula = "[0]";
   for(int i = 1; i <= NMax; i++)
      Formula = Formula
         + "+[" + to_string(2 * i - 1) + "]*cos(" + to_string(i) + "*x)"
         + "+[" + to_string(2 * i) + "]*sin(" + to_string(i) + "*x)";

   return Formula;
}
