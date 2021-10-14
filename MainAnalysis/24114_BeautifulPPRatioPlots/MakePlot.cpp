#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TH2D.h"

#include "CommandLine.h"
#include "CustomAssert.h"
#include "DataHelper.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
vector<double> DetectBins(TH1D *HMin, TH1D *HMax);
vector<TGraphAsymmErrors> Transcribe(TH1D *H, vector<double> Bins1, vector<double> Bins2, TH1D *H2 = nullptr, bool Normalize = true);
TGraphAsymmErrors CalculateRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2);

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   // Command line inputs
   CommandLine CL(argc, argv);

   string BaseFileName       = CL.Get("BaseFileName");
   string BaseRLabel         = CL.Get("BaseRLabel");
   vector<string> FileName   = CL.GetStringVector("FileName", vector<string>{});
   vector<string> RLabel     = CL.GetStringVector("RLabel", vector<string>{});
   vector<int> Color         = CL.GetIntVector("Color", vector<int>{1,2,3,4,5,6,7});
   bool AddHIN18014          = CL.GetBool("AddHIN18014", false);

   string OutputFileName     = CL.Get("Output", "PPRatio.pdf");

   int FileCount = FileName.size();

   Assert(FileCount > 0, "Please specify at least one curve to plot");
   Assert(FileCount == RLabel.size(), "Please specify the radius labels for the input files");

   // Get the global setting DH file
   string GlobalSettingFile  = CL.Get("GlobalSetting", "GlobalSetting.dh");
   DataHelper DHFile(GlobalSettingFile);

   TFile BaseFile(BaseFileName.c_str());

   // Find out the binnings
   vector<double> GenBins1
      = DetectBins((TH1D *)BaseFile.Get("HGenPrimaryBinMin"), (TH1D *)BaseFile.Get("HGenPrimaryBinMax"));
   vector<double> GenBins2
      = DetectBins((TH1D *)BaseFile.Get("HGenBinningBinMin"), (TH1D *)BaseFile.Get("HGenBinningBinMax"));

   // Get base spectrum
   int BaseIteration
      = DHFile["TestRunPPData"][Form("BestIteration_R%s_CentralityInclusive",BaseRLabel.c_str())].GetInteger();
   TH1D *HBase = (TH1D *)BaseFile.Get(Form("HUnfoldedBayes%d", BaseIteration));
   vector<TGraphAsymmErrors> GBase = Transcribe(HBase, GenBins1, GenBins2, nullptr);

   // Get the spectra
   vector<vector<TGraphAsymmErrors>> GSpectra(FileCount);
   for(int i = 0; i < FileCount; i++)
   {
      TFile File(FileName[i].c_str());

      int Iteration
         = DHFile["TestRunPPData"][Form("BestIteration_R%s_CentralityInclusive",RLabel[i].c_str())].GetInteger();
      TH1D *H = (TH1D *)File.Get(Form("HUnfoldedBayes%d", Iteration));
      GSpectra[i] = Transcribe(H, GenBins1, GenBins2, nullptr);

      File.Close();
   }

   // Calculate all the ratio's
   vector<vector<TGraphAsymmErrors>> GRatio(FileCount);
   for(int i = 0; i < FileCount; i++)
      for(int j = 0; j < GSpectra[i].size(); j++)
         GRatio[i].push_back(CalculateRatio(GSpectra[i][j], GBase[j]));

   TCanvas Canvas;
   Canvas.SetLogx();

   TH2D HWorld("HWorld", Form(";Jet p_{T} (GeV);(R = X) / (R = %.1f)", DHFile["JetR"][BaseRLabel].GetDouble()),
      100, 100, 1500, 100, 0, 1.2);
   HWorld.SetStats(0);

   HWorld.Draw("axis");

   vector<TGraph> HIN18014(5);
   if(AddHIN18014 == true)
   {
      TFile File("HEPData/HIN18014PPRatio.root");

      HIN18014[0] = *((TGraph *)File.Get("R2"));
      HIN18014[1] = *((TGraph *)File.Get("R3"));
      HIN18014[2] = *((TGraph *)File.Get("R4"));
      HIN18014[3] = *((TGraph *)File.Get("R6"));
      HIN18014[4] = *((TGraph *)File.Get("R7"));

      File.Close();

      for(int i = 0; i < 5; i++)
      {
         HIN18014[i].SetLineColor(Colors[i]);
         HIN18014[i].SetLineWidth(2);
         HIN18014[i].Draw("l");
      }
   }

   for(int i = 0; i < FileCount; i++)
   {
      for(int j = 0; j < GRatio[i].size(); j++)
      {
         GRatio[i][j].SetLineColor(Colors[Color[i]]);
         GRatio[i][j].SetLineWidth(2);
         GRatio[i][j].SetMarkerColor(Colors[Color[i]]);
         GRatio[i][j].SetMarkerStyle(20);
         GRatio[i][j].SetMarkerSize(2);
         GRatio[i][j].Draw("p");
      }
   }

   TLegend Legend(0.15, 0.12, 0.30, 0.32);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   for(int i = 0; i < FileCount; i++)
      Legend.AddEntry(&GRatio[i][0], Form("R = %.1f", DHFile["JetR"][RLabel[i]].GetDouble()), "lp");
   Legend.Draw();

   Canvas.SaveAs(OutputFileName.c_str());

   BaseFile.Close();

   return 0;
}

vector<double> DetectBins(TH1D *HMin, TH1D *HMax)
{
   if(HMin == nullptr || HMax == nullptr)
      return vector<double>{};

   vector<pair<double, double>> Bins;

   for(int i = 1; i <= HMin->GetNbinsX(); i++)
      Bins.push_back(pair<double, double>(HMin->GetBinContent(i), HMax->GetBinContent(i)));

   sort(Bins.begin(), Bins.end());
   auto iterator = unique(Bins.begin(), Bins.end());
   Bins.erase(iterator, Bins.end());

   vector<double> Result;
   for(auto iterator : Bins)
   {
      if(iterator.second == 999)
         iterator.second = 9999;

      Result.push_back(iterator.first);
      Result.push_back(iterator.second);
   }

   sort(Result.begin(), Result.end());
   auto iterator2 = unique(Result.begin(), Result.end());
   Result.erase(iterator2, Result.end());

   return Result;
}

vector<TGraphAsymmErrors> Transcribe(TH1D *H, vector<double> Bins1, vector<double> Bins2, TH1D *H2, bool Normalize)
{
   int BinningCount = Bins2.size() - 1;
   if(BinningCount <= 0)
      BinningCount = 1;

   vector<TGraphAsymmErrors> Result(BinningCount);
   if(H == nullptr)
      return Result;

   int PrimaryBinCount = Bins1.size() - 1;
   double PrimaryBins[1000] = {0};
   for(int i = 0; i <= PrimaryBinCount; i++)
      PrimaryBins[i] = Bins1[i];
   double Delta = PrimaryBins[PrimaryBinCount-1] - PrimaryBins[1];

   if(PrimaryBins[0] < -998)
      PrimaryBins[0] = PrimaryBins[1] - Delta * 0.05;
   if(PrimaryBins[PrimaryBinCount] > 998)
      PrimaryBins[PrimaryBinCount] = PrimaryBins[PrimaryBinCount-1] + Delta * 0.05;
   if(PrimaryBins[0] < 0 && PrimaryBins[1] > 0)
      PrimaryBins[0] = 0;

   for(int iB = 0; iB < BinningCount; iB++)
   {
      for(int i = 0; i < PrimaryBinCount; i++)
      {
         double X = (PrimaryBins[i] + PrimaryBins[i+1]) / 2;
         double DX = (PrimaryBins[i+1] - PrimaryBins[i]) / 2;
         double Y = 0, DY = 0;

         if(H2 == nullptr)
         {
            Y = H->GetBinContent(i + iB * PrimaryBinCount + 1);
            DY = H->GetBinError(i + iB * PrimaryBinCount + 1);
         }
         else
         {
            double YUp = H->GetBinContent(i + iB * PrimaryBinCount + 1);
            double YDown = H2->GetBinContent(i + iB * PrimaryBinCount + 1);

            // cout << iB << " " << i << " " << YUp << " " << YDown << endl;

            Y = (YUp + YDown) / 2;
            DY = fabs(YUp - YDown) / 2;
         }

         double Width = PrimaryBins[i+1] - PrimaryBins[i];
         if(Normalize == false)
            Width = 1;

         Result[iB].SetPoint(i, X, Y / Width);
         Result[iB].SetPointError(i, DX, DX, DY / Width, DY / Width);
      }
   }

   return Result;
}

TGraphAsymmErrors CalculateRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2)
{
   TGraphAsymmErrors G;

   if(G1.GetN() != G2.GetN())
      return G;

   cout << G1.GetN() << " " << G2.GetN() << endl;

   int N = G2.GetN();
   for(int i = 0; i < N; i++)
   {
      double X1, X2, Y1, Y2, E1YH, E1YL, E1XH, E1XL;

      G1.GetPoint(i, X1, Y1);
      E1YH = G1.GetErrorYhigh(i);
      E1YL = G1.GetErrorYlow(i);
      E1XH = G1.GetErrorXhigh(i);
      E1XL = G1.GetErrorXlow(i);
      G2.GetPoint(i, X2, Y2);

      if(Y2 == 0)
      {
         G.SetPoint(i, X1, 0);
         G.SetPointError(i, E1XL, E1XH, 0, 0);
      }
      else
      {
         G.SetPoint(i, X1, Y1 / Y2);
         G.SetPointError(i, E1XL, E1XH, E1YL / Y2, E1YH / Y2);
      }
   }

   return G;
}


