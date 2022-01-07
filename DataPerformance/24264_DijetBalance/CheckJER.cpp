#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraphErrors.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

struct Balance;
struct RMean;
int main(int argc, char *argv[]);
vector<Balance> ReadFile(string FileName, double PTMin, double DPhiMin, double AlphaMax);
RMean PlotJER(PdfFileHelper &PdfFile, vector<Balance> &Data, vector<Balance> &MC, double JERSF, double AlphaMax);

struct Balance
{
   float PT1;
   float PT2;
   float GenPT1;
   float GenPT2;
   float Alpha;
   float Weight;
};

struct RMean
{
   float DataMean;
   float DataMeanError;
   float MCMean;
   float MCMeanError;
};

int main(int argc, char *argv[])
{
   vector<int> Colors = GetPrimaryColors();

   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileNameData = CL.Get("Data");
   string InputFileNameMC   = CL.Get("MC");
   string OutputBase        = CL.Get("OutputBase");

   double PTMin             = CL.GetDouble("PTMin", 150);
   double DPhiMin           = CL.GetDouble("DPhiMin", 2.7);
   double AlphaMax          = CL.GetDouble("AlphaMax", 0.3);

   vector<Balance> Data = ReadFile(InputFileNameData, PTMin, DPhiMin, AlphaMax);
   vector<Balance> MC   = ReadFile(InputFileNameMC,   PTMin, DPhiMin, AlphaMax);

   cout << Data.size() << " " << MC.size() << endl;

   PdfFileHelper PdfFileCheck(OutputBase + "_Check.pdf");
   PdfFileCheck.AddTextPage("JER SF check");
   
   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage("JER SF check - summary");

   vector<double> AlphaCut{0.10, 0.15, 0.20, 0.25, AlphaMax};

   TFile OutputFile((OutputBase + ".root").c_str(), "RECREATE");

   for(double Alpha : AlphaCut)
   {
      TGraphErrors GData, GMC;

      double DataMean = -1;

      for(double JERSF = 1.00; JERSF < 1.75; JERSF = JERSF + 0.005)
      {
         RMean Result = PlotJER(PdfFileCheck, Data, MC, JERSF, Alpha);

         int N = GData.GetN();

         GData.SetPoint(N, JERSF, Result.DataMean);
         GData.SetPointError(N, 0, Result.DataMeanError);
         GMC.SetPoint(N, JERSF, Result.MCMean);
         GMC.SetPointError(N, 0, Result.MCMeanError);

         DataMean = Result.DataMean;
      }

      TCanvas Canvas;

      TH2D HWorld("HWorld", ";JER SF;<PT2/PT1>", 100, 0.95, 1.80, 100, DataMean - 0.025, DataMean + 0.025);

      HWorld.SetStats(0);

      HWorld.SetTitle(Form("Alpha < %.2f", Alpha));
      
      GData.SetMarkerColor(Colors[0]);
      GMC.SetMarkerColor(Colors[1]);
      GData.SetLineColor(Colors[0]);
      GMC.SetLineColor(Colors[1]);
      GData.SetLineWidth(2);
      GMC.SetLineWidth(2);

      HWorld.Draw("hist");
      GData.Draw("p");
      GMC.Draw("p");

      Canvas.SetGridx();
      Canvas.SetGridy();

      PdfFile.AddCanvas(Canvas);

      GData.SetName(Form("GData_Alpha%.02f", Alpha));
      GMC.SetName(Form("GMC_Alpha%.02f", Alpha));

      GData.Write();
      GMC.Write();
   }

   OutputFile.Close();
   
   PdfFile.AddTimeStampPage();
   PdfFile.Close();
   
   PdfFileCheck.AddTimeStampPage();
   PdfFileCheck.Close();

   return 0;
}

vector<Balance> ReadFile(string FileName, double PTMin, double DPhiMin, double AlphaMax)
{
   vector<Balance> Result;

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("DijetTree");

   float Weight, PT1, PT2, PT3, GenPT1, GenPT2, Phi1, Phi2;
   Tree->SetBranchAddress("Weight", &Weight);
   Tree->SetBranchAddress("PT1", &PT1);
   Tree->SetBranchAddress("PT2", &PT2);
   Tree->SetBranchAddress("PT3", &PT3);
   Tree->SetBranchAddress("GenPT1", &GenPT1);
   Tree->SetBranchAddress("GenPT2", &GenPT2);
   Tree->SetBranchAddress("Phi1", &Phi1);
   Tree->SetBranchAddress("Phi2", &Phi2);

   int EntryCount = Tree->GetEntries() * 1.00;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(PT2 <= 0)
         continue;

      if(PT1 < PTMin)
         continue;

      float DPhi = Phi1 - Phi2;
      if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
      if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;
      if(DPhi < 0)       DPhi = -DPhi;

      if(DPhi < DPhiMin)
         continue;

      float Alpha = 2 * PT3 / (PT1 + PT2);
      if(Alpha == 0)
         Alpha = 2 * 60 / (PT1 + PT2);
      if(Alpha > AlphaMax)
         continue;

      Result.push_back({PT1, PT2, GenPT1, GenPT2, Alpha, Weight});
   }

   File.Close();

   return Result;
}

RMean PlotJER(PdfFileHelper &PdfFile, vector<Balance> &Data, vector<Balance> &MC, double JERSF, double AlphaMax)
{
   static vector<int> Colors = GetPrimaryColors();

   TH1D HData("HData", ";PT2/PT1;a.u.", 100, 0, 1);
   TH1D HMC("HMC", ";PT2/PT1;a.u.", 100, 0, 1);

   HData.SetTitle(Form("JER SF = %.03f, alpha max = %.02f", JERSF, AlphaMax));

   for(Balance &B : Data)
      if(B.Alpha < AlphaMax)
         HData.Fill(B.PT2 / B.PT1);
   for(Balance &B : MC)
   {
      double PT1 = B.GenPT1 + (B.PT1 - B.GenPT1) * JERSF;
      double PT2 = B.GenPT2 + (B.PT2 - B.GenPT2) * JERSF;
      if(PT2 > PT1)
         swap(PT1, PT2);
      if(B.Alpha < AlphaMax)
         HMC.Fill(PT2 / PT1, B.Weight);
   }

   HData.SetStats(0);
   HMC.SetStats(0);

   HData.Scale(1 / HData.Integral());
   HMC.Scale(1 / HMC.Integral());

   HData.SetLineColor(Colors[0]);
   HData.SetMarkerColor(Colors[0]);
   HData.SetLineWidth(2);
   HMC.SetLineColor(Colors[1]);
   HMC.SetMarkerColor(Colors[1]);
   HMC.SetLineWidth(2);

   TCanvas Canvas;

   HData.Draw();
   HMC.Draw("same");

   TLegend Legend(0.2, 0.5, 0.4, 0.7);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HData, "Data", "pl");
   Legend.AddEntry(&HMC, "MC", "pl");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   RMean Result;

   Result.DataMean = HData.GetMean();
   Result.DataMeanError = HData.GetMeanError();
   Result.MCMean = HMC.GetMean();
   Result.MCMeanError = HMC.GetMeanError();

   return Result;
}

