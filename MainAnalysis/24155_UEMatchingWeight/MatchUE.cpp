#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"
#include "DataHelper.h"
#include "CustomAssert.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "ProgressBar.h"

struct Jet
{
   double UE;
   double W;
   bool operator <(const Jet &other) const
   {
      if(UE < other.UE)   return true;
      if(UE > other.UE)   return false;
      if(W < other.W)     return true;
      if(W > other.W)     return false;
      return false;
   }
};
int main(int argc, char *argv[]);
void ReadData(string FileName, vector<Jet> &Data, vector<Jet> &MC);
TGraphAsymmErrors SplitIntoBins(vector<Jet> &Data, int BinCount, int BinMagnification = 1);
TGraphAsymmErrors FillGraph(vector<Jet> Data, TGraphAsymmErrors &GInput);
TGraphAsymmErrors BuildRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2, bool Log = false, bool SkipFinalBin = false);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName         = CL.Get("Input");
   int BinCount                 = CL.GetInteger("BinCount", 100);
   int BinMagnification         = CL.GetInteger("BinMagnification", 5);
   string OutputFileName        = CL.Get("Output");
   string RootOutputFileName    = CL.Get("RootOutput");
   bool SkipFinalBin            = CL.GetBool("SkipFinalBin", false);

   vector<Jet> Data;
   vector<Jet> MC;
   ReadData(InputFileName, Data, MC);

   TFile OutputFile(RootOutputFileName.c_str(), "RECREATE");

   TGraphAsymmErrors GData     = SplitIntoBins(Data, BinCount, BinMagnification);
   TGraphAsymmErrors GMC       = FillGraph(MC, GData);
   TGraphAsymmErrors GRatio    = BuildRatio(GData, GMC, false, SkipFinalBin);
   TGraphAsymmErrors GRatioLog = BuildRatio(GData, GMC, true,  SkipFinalBin);

   GData.SetName("GData");
   GMC.SetName("GMC");
   GRatio.SetName("GRatio");
   GRatioLog.SetName("GRatioLog");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("UE reweighting derivation");

   PdfFile.AddPlot(GData,     "ap", true);
   PdfFile.AddPlot(GMC,       "ap", true);
   PdfFile.AddPlot(GRatio,    "ap", true);
   PdfFile.AddPlot(GRatioLog, "ap", false);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   GData.Write();
   GMC.Write();
   GRatio.Write();
   GRatioLog.Write();

   OutputFile.Close();

   return 0;
}

void ReadData(string FileName, vector<Jet> &Data, vector<Jet> &MC)
{
   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("Tree");

   int T;
   Jet M;
   Tree->SetBranchAddress("Type", &T);
   Tree->SetBranchAddress("JetUE", &M.UE);
   Tree->SetBranchAddress("Weight", &M.W);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);
      if(T == 0)
         Data.push_back(M);
      else
         MC.push_back(M);
   }

   File.Close();
}

TGraphAsymmErrors SplitIntoBins(vector<Jet> &Data, int BinCount, int BinMagnification)
{
   TGraphAsymmErrors G;

   sort(Data.begin(), Data.end());
   reverse(Data.begin(), Data.end());

   double TotalWeight = 0;
   for(Jet &J : Data)
      TotalWeight = TotalWeight + J.W;

   int BinSoFar = 0;

   double SumW = 0;
   double SumW2 = 0;
   double SumX = 0;
   double UEBound = Data[0].UE;
   for(int i = 0; i < (int)Data.size(); i++)
   {
      SumW = SumW + Data[i].W;
      SumW2 = SumW2 + Data[i].W * Data[i].W;
      SumX = SumX + Data[i].W * Data[i].UE;

      bool NewBin = false;
      if(BinSoFar < BinMagnification)
      {
         if(SumW > TotalWeight / BinCount / BinMagnification)
            NewBin = true;
      }
      else if(BinSoFar >= BinMagnification + BinCount - 2)
      {
         if(SumW > TotalWeight / BinCount / BinMagnification)
            NewBin = true;
      }
      else if(i == (int)Data.size() - 1)
         NewBin = true;
      else
      {
         if(SumW > TotalWeight / BinCount)
            NewBin = true;
      }

      if(Data[i].UE == UEBound)   // we need to at least have some UE difference from the previous bin
         NewBin = false;

      if(NewBin == true && SumW > 0)
      {
         double X = SumX / SumW;
         double NewUEBound = Data[i].UE;
         double Y = SumW / fabs(NewUEBound - UEBound);
         double EY = sqrt(SumW2) / fabs(NewUEBound - UEBound);

         int N = G.GetN();
         G.SetPoint(N, X, Y);
         G.SetPointError(N, X - NewUEBound, UEBound - X, EY, EY);
         BinSoFar = G.GetN();

         SumW = 0;
         SumW2 = 0;
         SumX = 0;
         UEBound = NewUEBound;
      }
   }

   return G;
}

TGraphAsymmErrors FillGraph(vector<Jet> Data, TGraphAsymmErrors &GInput)
{
   TGraphAsymmErrors G;

   for(int i = 0; i < GInput.GetN(); i++)
   {
      double X, Y;
      GInput.GetPoint(i, X, Y);
      double XL = X - GInput.GetErrorXlow(i);
      double XH = X + GInput.GetErrorXhigh(i);

      double SumW = 0;
      double SumW2 = 0;
      double SumX = 0;
      for(Jet &J : Data)
      {
         if(J.UE < XL)   continue;
         if(J.UE > XH)   continue;

         SumW = SumW + J.W;
         SumW2 = SumW2 + J.W * J.W;
         SumX = SumX + J.UE * J.W;
      }

      double XWidth = XH - XL;
      double MeanX = SumX / SumW;
      double MeanY = SumW / XWidth;
      double EY = sqrt(SumW2) / XWidth;
      G.SetPoint(i, MeanX, MeanY);
      G.SetPointError(i, MeanX - XL, XH - MeanX, EY, EY);
   }

   return G;
}

TGraphAsymmErrors BuildRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2, bool Log, bool SkipFinalBin)   
{
   TGraphAsymmErrors G;

   for(int i = 0; i < G1.GetN(); i++)
   {
      // if(SkipFinalBin == true && i == G1.GetN() - 1)
      //    break;
      if(SkipFinalBin == true && i == 0)
         continue;

      double X1, Y1;
      double X2, Y2;

      G1.GetPoint(i, X1, Y1);
      G2.GetPoint(i, X2, Y2);

      double Y = Y1 / Y2;

      int N = G.GetN();
      
      if(Log == false)
         G.SetPoint(N, X1, Y);
      else
         G.SetPoint(N, X1, log(Y));
      
      double EXL1 = G1.GetErrorXlow(i);
      double EXH1 = G1.GetErrorXhigh(i);
      double EYL1 = G1.GetErrorYlow(i) / Y1;
      double EYH1 = G1.GetErrorYhigh(i) / Y1;
      double EYL2 = G2.GetErrorYlow(i) / Y2;
      double EYH2 = G2.GetErrorYhigh(i) / Y2;

      double EYL = sqrt(EYL1 * EYL1 + EYL2 * EYL2) * Y;
      double EYH = sqrt(EYH1 * EYH1 + EYH2 * EYH2) * Y;

      if(Log == false)
         G.SetPointError(N, EXL1, EXH1, EYL, EYH);
      else
         G.SetPointError(N, EXL1, EXH1, log(Y) - log(Y - EYL), log(Y + EYH) - log(Y));
   }

   return G;
}


