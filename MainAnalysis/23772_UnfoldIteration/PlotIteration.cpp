#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "DataHelper.h"
#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
double CalculateChi2(TH1D *H1, TH1D *H2, int IgnoreBin = 0, bool UseError = true);

int main(int argc, char *argv[])
{
   SetThumbStyle();

   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   int PointsToIgnore    = CL.GetInt("Ignore");
   string Reference      = CL.Get("Reference", "HMCTruth");
   string State          = CL.Get("State");
   string Key            = CL.Get("Key");
   double DPower         = CL.GetDouble("DPower", 1.7);

   vector<int> Iteration{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 68, 70, 80, 90, 100, 125, 150, 175, 200, 250, 300, 350, 400, 450, 500};

   TGraph Graph;
   TGraph GraphD;
   TGraph GraphWD;

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Iteration scan");

   TFile InputFile(InputFileName.c_str());

   TH1D *HMCMeasured = (TH1D *)InputFile.Get("HMCTruth");
   TH1D *HInput = (TH1D *)InputFile.Get("HInput");
   double ScalingFactor = HInput->Integral() / HMCMeasured->Integral();

   TH1D *HMCTruth = (TH1D *)InputFile.Get(Reference.c_str());
   HMCTruth->Scale(ScalingFactor);
   HMCTruth->SetStats(0);
   HMCTruth->SetLineColor(kBlack);
   HMCTruth->SetLineWidth(2);

   double MaxChi2 = -1, MinChi2 = -1;
   double MaxD2 = -1, MinD2 = -1;
   double MaxWD2 = -1, MinWD2 = -1;

   int BestIteration = -1;

   for(int i : Iteration)
   {
      TH1D *HUnfolded = (TH1D *)InputFile.Get(Form("HUnfoldedBayes%d", i));
      if(HUnfolded == nullptr)
         continue;

      double Chi2 = CalculateChi2(HMCTruth, HUnfolded, PointsToIgnore, true);
      double D2 = CalculateChi2(HMCTruth, HUnfolded, PointsToIgnore, false);

      if(Chi2 > 0 && isinf(Chi2) == false)
      {
         if(MaxChi2 < 0 || MaxChi2 < Chi2)   MaxChi2 = Chi2;
         if(MinChi2 < 0 || MinChi2 > Chi2)   MinChi2 = Chi2;
         Graph.SetPoint(Graph.GetN(), i, Chi2);
      }
      if(D2 > 0 && isinf(D2) == false)
      {
         if(MaxD2 < 0 || MaxD2 < D2)   MaxD2 = D2;
         if(MinD2 < 0 || MinD2 > D2)   MinD2 = D2;
         GraphD.SetPoint(GraphD.GetN(), i, D2);
      }

      TCanvas Canvas;
      HMCTruth->SetTitle(Form("Iteration %d", i));
      HMCTruth->Draw("hist");
      HUnfolded->SetMarkerStyle(20);
      HUnfolded->Draw("same");
      PdfFile.AddCanvas(Canvas);
      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);

      TH1D *HTruthPower = (TH1D *)HMCTruth->Clone("TruthPower");
      TH1D *HUnfoldedPower = (TH1D *)HUnfolded->Clone("UnfoldedPower");

      double Power = 1;
      for(int j = 1; j <= HTruthPower->GetNbinsX(); j++)
      {
         HTruthPower->SetBinContent(j, HTruthPower->GetBinContent(j) * Power);
         HTruthPower->SetBinError(j, HTruthPower->GetBinError(j) * Power);
         HUnfoldedPower->SetBinContent(j, HUnfoldedPower->GetBinContent(j) * Power);
         HUnfoldedPower->SetBinError(j, HUnfoldedPower->GetBinError(j) * Power);
         Power = Power * DPower;
      }

      HTruthPower->SetTitle(Form("Iteration %d power", i));
      HTruthPower->Draw("hist");
      HUnfoldedPower->SetMarkerStyle(20);
      HUnfoldedPower->Draw("same");
      PdfFile.AddCanvas(Canvas);
      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);
      
      double WD2 = CalculateChi2(HTruthPower, HUnfoldedPower, PointsToIgnore, false);
      if(WD2 > 0 && isinf(WD2) == false)
      {
         if(MaxWD2 < 0 || MaxWD2 < WD2)   MaxWD2 = WD2;
         if(MinWD2 < 0 || MinWD2 > WD2)   MinWD2 = WD2, BestIteration = i;
         GraphWD.SetPoint(GraphWD.GetN(), i, WD2);
      }
   }

   if(MinChi2 != MinChi2)   MinChi2 = 1;
   if(MaxChi2 != MaxChi2)   MaxChi2 = 9999;
   if(MinChi2 == MaxChi2)   MaxChi2 = MinChi2 + 1;
   if(MinD2 != MinD2)   MinD2 = 1;
   if(MaxD2 != MaxD2)   MaxD2 = 9999;
   if(MinD2 == MaxD2)   MaxD2 = MinD2 + 1;
   if(MinWD2 != MinWD2)   MinWD2 = 1;
   if(MaxWD2 != MaxWD2)   MaxWD2 = 9999;
   if(MinWD2 == MaxWD2)   MaxWD2 = MinWD2 + 1;

   InputFile.Close();

   cout << "!" << endl;

   DataHelper DHFile("GlobalSetting.dh");
   DHFile[State][Key] = BestIteration;
   DHFile.SaveToFile();

   PdfFile.AddTextPage("Summary plots");

   Graph.SetNameTitle("GChi2", "");
   GraphD.SetNameTitle("GD2", "");
   GraphWD.SetNameTitle("GWD2", "");

   Graph.GetXaxis()->SetTitle("Number of iterations");
   Graph.GetYaxis()->SetTitle("#chi^{2}");
   GraphD.GetXaxis()->SetTitle("Number of iterations");
   GraphD.GetYaxis()->SetTitle("Distance^{2}");
   GraphWD.GetXaxis()->SetTitle("Number of iterations");
   GraphWD.GetYaxis()->SetTitle("Weighted distance^{2}");

   Graph.GetYaxis()->SetRangeUser(MinChi2, MaxChi2);
   GraphD.GetYaxis()->SetRangeUser(MinD2, MaxD2);
   GraphWD.GetYaxis()->SetRangeUser(MinWD2, MaxWD2);

   Graph.Print();
   GraphD.Print();

   PdfFile.AddPlot(Graph, "apl");
   PdfFile.AddPlot(Graph, "apl", false, false, true, true);
   PdfFile.AddPlot(Graph, "apl", true, false, true, true);
   PdfFile.AddPlot(GraphD, "apl");
   PdfFile.AddPlot(GraphD, "apl", false, false, true, true);
   PdfFile.AddPlot(GraphD, "apl", true, false, true, true);
   PdfFile.AddPlot(GraphWD, "apl");
   PdfFile.AddPlot(GraphWD, "apl", false, false, true, true);
   PdfFile.AddPlot(GraphWD, "apl", true, false, true, true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double CalculateChi2(TH1D *H1, TH1D *H2, int IgnoreBin, bool UseError)
{
   if(H1 == nullptr)
      return 0;
   if(H2 == nullptr)
      return 0;

   int N = H1->GetNbinsX();

   double Chi2 = 0;

   for(int i = IgnoreBin + 1; i <= N; i++)
   {
      double V1 = H1->GetBinContent(i);
      double V2 = H2->GetBinContent(i);
      double E1 = H1->GetBinError(i);
      double E2 = H2->GetBinError(i);

      double D = V1 - V2;
      double Chi = (V1 - V2) / sqrt(E1 * E1 + E2 * E2);
      if(V1 == 0 && V2 == 0)
         continue;

      if(UseError == true)
         Chi2 = Chi2 + Chi * Chi;
      else
         Chi2 = Chi2 + D * D;
   }

   if(Chi2 != Chi2)
      return 0;

   return Chi2;
}



