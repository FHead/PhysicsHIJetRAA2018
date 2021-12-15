#include <iostream>
#include <vector>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "DataHelper.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[])
{
   vector<int> Colors = GetPrimaryColors();
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Resolution");

   DataHelper DHFile(InputFileName);

   double NEtaBin = DHFile["EtaBins"]["N"].GetInteger();

   vector<double> EtaBins(NEtaBin + 1);
   for(int i = 0; i <= NEtaBin; i++)
      EtaBins[i] = DHFile["EtaBins"]["Eta_"+to_string(i)].GetDouble();

   for(int iEta = 0; iEta < NEtaBin; iEta++)
   {
      int PTBinCount = DHFile["EtaBins"]["PTBinCount_"+to_string(iEta)].GetInteger();

      TGraphAsymmErrors GAverage, GMean, GRMS, GRMSCorrected, GSigma;

      for(int iPT = 0; iPT < PTBinCount; iPT++)
      {
         string State = "Eta" + to_string(iEta) + "PT" + to_string(iPT);

         double PTMin        = DHFile[State]["PTMin"].GetDouble();
         double PTMax        = DHFile[State]["PTMax"].GetDouble();

         double PT           = DHFile[State]["MeanPT"].GetDouble();

         double Average      = DHFile[State]["Average"].GetDouble();
         double Mean         = DHFile[State]["Mean"].GetDouble();
         double EMean        = DHFile[State]["MeanError"].GetDouble();
         double RMS          = DHFile[State]["VisibleRMS"].GetDouble();
         double RMSCorrected = DHFile[State]["CorrectedRMS"].GetDouble();
         double Sigma        = DHFile[State]["Width"].GetDouble();
         double ESigma       = DHFile[State]["WidthError"].GetDouble();

         GAverage.SetPoint(iPT, PT, Average);
         GAverage.SetPointError(iPT, PT - PTMin, PTMax - PT, 0, 0);
         GMean.SetPoint(iPT, PT, Mean);
         GMean.SetPointError(iPT, PT - PTMin, PTMax - PT, EMean, EMean);
         
         GRMS.SetPoint(iPT, PT, RMS);
         GRMS.SetPointError(iPT, PT - PTMin, PTMax - PT, 0, 0);
         GRMSCorrected.SetPoint(iPT, PT, RMSCorrected);
         GRMSCorrected.SetPointError(iPT, PT - PTMin, PTMax - PT, 0, 0);
         GSigma.SetPoint(iPT, PT, Sigma);
         GSigma.SetPointError(iPT, PT - PTMin, PTMax - PT, ESigma, ESigma);
      }

      GAverage.SetMarkerColor(Colors[0]);
      GAverage.SetLineColor(Colors[0]);
      GAverage.SetLineWidth(2);
      GMean.SetMarkerColor(Colors[1]);
      GMean.SetLineColor(Colors[1]);
      GMean.SetLineWidth(2);
      
      GRMS.SetMarkerColor(Colors[2]);
      GRMS.SetLineColor(Colors[2]);
      GRMS.SetLineWidth(2);
      GRMSCorrected.SetMarkerColor(Colors[0]);
      GRMSCorrected.SetLineColor(Colors[0]);
      GRMSCorrected.SetLineWidth(2);
      GSigma.SetMarkerColor(Colors[1]);
      GSigma.SetLineColor(Colors[1]);
      GSigma.SetLineWidth(2);

      TCanvas Canvas;

      TLegend Legend1(0.5, 0.8, 0.8, 0.6);
      Legend1.SetTextFont(42);
      Legend1.SetTextSize(0.035);
      Legend1.SetBorderSize(0);
      Legend1.SetFillStyle(0);
      Legend1.AddEntry(&GAverage, "Average", "pl");
      Legend1.AddEntry(&GMean, "Gaussian mean", "pl");

      TH2D HWorld1("HWorld1", Form("Eta = [%.1f,%.1f];Jet p_{T};Scale", EtaBins[iEta], EtaBins[iEta+1]),
         100, 40, 1500, 100, 0.9, 1.1);
      HWorld1.SetStats(0);
      HWorld1.Draw("axis");

      GAverage.Draw("p");
      GMean.Draw("p");
      Legend1.Draw();

      Canvas.SetLogx();
      Canvas.SetLogy(false);
      Canvas.SetGridx();
      Canvas.SetGridy();

      PdfFile.AddCanvas(Canvas);

      TLegend Legend2(0.5, 0.8, 0.8, 0.6);
      Legend2.SetTextFont(42);
      Legend2.SetTextSize(0.035);
      Legend2.SetBorderSize(0);
      Legend2.SetFillStyle(0);
      // Legend2.AddEntry(&GRMS, "Raw RMS", "pl");
      Legend2.AddEntry(&GRMSCorrected, "Corrected RMS", "pl");
      Legend2.AddEntry(&GSigma, "Gaussian sigma", "pl");

      TH2D HWorld2("HWorld2", Form("Eta = [%.1f,%.1f];Jet p_{T};Resolution", EtaBins[iEta], EtaBins[iEta+1]),
         100, 40, 1500, 100, 0.01, 1.0);
      HWorld2.SetStats(0);
      HWorld2.Draw("axis");

      // GRMS.Draw("p");
      GRMSCorrected.Draw("p");
      GSigma.Draw("p");
      Legend2.Draw();

      Canvas.SetLogx();
      Canvas.SetLogy();
      Canvas.SetGridx();
      Canvas.SetGridy();

      PdfFile.AddCanvas(Canvas);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}






