#include <iostream>
#include <map>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TFile.h"
#include "TF1.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "DataHelper.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
pair<double, double> GetMinMax(TGraphAsymmErrors *G);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   string DHFileName     = CL.Get("DHFile");
   string State          = CL.Get("State", "RhoWeight");
   string KeyBase        = CL.Get("Key");
   int Order1            = CL.GetInteger("Order1", 8);
   int Order2            = CL.GetInteger("Order2", 0);
   bool PinSmall         = CL.GetBool("PinSmall", false);
   bool PinLarge         = CL.GetBool("PinLarge", true);

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Fit");

   TFile File(InputFileName.c_str());

   TGraphAsymmErrors *GRatio = (TGraphAsymmErrors *)File.Get("GRatio");
   TGraphAsymmErrors *GRatioLog = (TGraphAsymmErrors *)File.Get("GRatioLog");

   if(GRatioLog == nullptr)
      return -1;

   if(PinSmall == true)
   {
      int N = GRatioLog->GetN();
      double X = GRatioLog->GetPointX(N - 1); // - GRatioLog->GetErrorXlow(N - 1);
      double Y = GRatioLog->GetPointY(N - 1);
      GRatioLog->SetPoint(N, X * 0.7, Y - 5);
   }
   if(PinLarge == true)
   {
      int N = GRatioLog->GetN();
      double X = GRatioLog->GetPointX(0); // + GRatioLog->GetErrorXhigh(0);
      double Y = GRatioLog->GetPointY(0);
      GRatioLog->SetPoint(N, X * 1.1, Y - 5);
   }

   string Formula = "([0]";
   for(int i = 1; i <= Order1; i++)
   {
      Formula = Formula + "+[" + i + "]";
      for(int j = 0; j < i; j++)
         Formula = Formula + "*x";
   }
   Formula = Formula + ")/(1";
   for(int i = 1; i <= Order2; i++)
   {
      Formula = Formula + "+[" + (i + Order1) + "]";
      for(int j = 0; j < i; j++)
         Formula = Formula + "*x";
   }
   Formula = Formula + ")";

   pair<double, double> MinMax = GetMinMax(GRatio);

   TF1 FLog("FLog", Formula.c_str(), 0, 1500);
   for(int i = 0; i < 10; i++)
      GRatioLog->Fit(&FLog, "W");

   TF1 F("F", Form("exp(%s)", Formula.c_str()), 0, 1500);
   for(int i = 0; i <= Order1 + Order2; i++)
   {
      F.SetParameter(i, FLog.GetParameter(i));
      F.SetParError(i, FLog.GetParError(i));
   }

   DataHelper DHFile(DHFileName);

   DHFile[State][KeyBase+"_Formula"] = "exp(" + Formula + ")";
   DHFile[State][KeyBase+"_NPar"] = Order1 + Order2 + 1;
   for(int i = 0; i <= Order1 + Order2; i++)
   {
      DHFile[State][KeyBase+"_P"+to_string(i)] = F.GetParameter(i);
      DHFile[State][KeyBase+"_E"+to_string(i)] = F.GetParError(i);
   }
   DHFile[State][KeyBase+"_MinUE"] = MinMax.first;
   DHFile[State][KeyBase+"_MaxUE"] = MinMax.second;

   DHFile.SaveToFile();

   TCanvas Canvas;
   
   GRatioLog->Draw("ap");
   FLog.Draw("same");
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   GRatio->Draw("ap");
   F.Draw("same");
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   GRatio->Draw("ap");
   F.Draw("same");
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);

   TGraph GF;
   for(double X = 0; X < 1500; X = X + 0.1)
   {
      double Y = F.Eval(X);
      if(Y != Y || Y > 1000)
         Y = 1000;
      GF.SetPoint(GF.GetN(), X, Y);
   }
   GF.Draw("ap");
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

pair<double, double> GetMinMax(TGraphAsymmErrors *G)
{
   if(G == nullptr)
      return pair<double, double>{0, 0};

   pair<double, double> MinMax{9999, -9999};

   for(int i = 0; i < G->GetN(); i++)
   {
      double X, Y;
      G->GetPoint(i, X, Y);
      double EXL, EXH;
      EXL = G->GetErrorXlow(i);
      EXH = G->GetErrorXhigh(i);

      if(X - EXL < MinMax.first)    MinMax.first = X - EXL;
      if(X + EXH > MinMax.second)   MinMax.second = X + EXH;
   }

   return MinMax;
}


