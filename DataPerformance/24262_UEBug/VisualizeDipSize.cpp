#include <iostream>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "DataHelper.h"
#include "PlotHelper4.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   vector<int> Colors = GetPrimaryColors();
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DHFileName = CL.Get("DHFile", "Dip.dh");
   string OutputFileName = CL.Get("Output", "DipSummary.pdf");

   DataHelper DHFile("Dip.dh");

   TGraph G1, G2, G3, G4;

   vector<double> PTList{100, 110, 120, 140, 150, 160, 170, 180, 190, 200};

   for(double PT : PTList)
   {
      string State = Form("R1_CentralityAll_PT%.0f", PT);
      double DipSize = DHFile[State]["P1"].GetDouble() / DHFile[State]["P0"].GetDouble();
      G1.SetPoint(G1.GetN(), PT, DipSize);
      
      State = Form("R2_CentralityAll_PT%.0f", PT);
      DipSize = DHFile[State]["P1"].GetDouble() / DHFile[State]["P0"].GetDouble();
      G2.SetPoint(G2.GetN(), PT, DipSize);
      
      State = Form("R3_CentralityAll_PT%.0f", PT);
      DipSize = DHFile[State]["P1"].GetDouble() / DHFile[State]["P0"].GetDouble();
      G3.SetPoint(G3.GetN(), PT, DipSize);
      
      State = Form("R4_CentralityAll_PT%.0f", PT);
      DipSize = DHFile[State]["P1"].GetDouble() / DHFile[State]["P0"].GetDouble();
      G4.SetPoint(G4.GetN(), PT, DipSize);
   }

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Dip size summary");

   G1.SetTitle("R = 0.15");
   G1.GetXaxis()->SetTitle("PT cut (GeV)");
   G1.GetYaxis()->SetTitle("Relative dip size");
   PdfFile.AddPlot(G1, "ap");

   G2.SetTitle("R = 0.20");
   G2.GetXaxis()->SetTitle("PT cut (GeV)");
   G2.GetYaxis()->SetTitle("Relative dip size");
   PdfFile.AddPlot(G2, "ap");

   G3.SetTitle("R = 0.30");
   G3.GetXaxis()->SetTitle("PT cut (GeV)");
   G3.GetYaxis()->SetTitle("Relative dip size");
   PdfFile.AddPlot(G3, "ap");

   G4.SetTitle("R = 0.40");
   G4.GetXaxis()->SetTitle("PT cut (GeV)");
   G4.GetYaxis()->SetTitle("Relative dip size");
   PdfFile.AddPlot(G4, "ap");

   TCanvas Canvas;

   G1.SetMarkerColor(Colors[0]);
   G1.SetLineColor(Colors[0]);
   G2.SetMarkerColor(Colors[1]);
   G2.SetLineColor(Colors[1]);
   G3.SetMarkerColor(Colors[2]);
   G3.SetLineColor(Colors[2]);
   G4.SetMarkerColor(Colors[3]);
   G4.SetLineColor(Colors[3]);

   TH2D HWorld("HWorld", ";PT Cut (GeV);Relative dip size", 100, 90, 210, 100, 0, 1.1);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   G1.Draw("pl");
   G2.Draw("pl");
   G3.Draw("pl");
   G4.Draw("pl");

   TLegend Legend(0.2, 0.2, 0.4, 0.5);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&G1, "R = 0.15", "pl");
   Legend.AddEntry(&G2, "R = 0.20", "pl");
   Legend.AddEntry(&G3, "R = 0.30", "pl");
   Legend.AddEntry(&G4, "R = 0.40", "pl");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




