#include <iostream>
#include <vector>
using namespace std;

#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"

#include "CommandLine.h"
#include "SetStyle.h"
#include "DataHelper.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
void AddPlot(PdfFileHelper &PdfFile, DataHelper &DHFile, vector<string> States, vector<string> Labels);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   DataHelper DHFile("StatisticsRho.dh");

   PdfFileHelper PdfFile("RhoSummary.pdf");
   PdfFile.AddTextPage("Rho Summary");

   vector<int> Base = {1, 2, 8, 9};
   vector<int> Radius = {1, 2, 3, 4, 5, 6, 7, 8, 9};

   for(int B : Base)
   {
      for(int R : Radius)
      {
         string Key = "PbPbR" + to_string(R) + "R" + to_string(B);
         AddPlot(PdfFile, DHFile, {Key, "Reco" + Key, "Data" + Key}, {"Gen", "Reco", "Data"});
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, DataHelper &DHFile, vector<string> States, vector<string> Labels)
{
   static vector<int> Colors = GetPrimaryColors();

   int N = States.size();
   int MaxCount = 0;

   vector<TGraph> G(N);

   for(int i = 0; i < N; i++)
   {
      G[i].SetLineWidth(2);
      G[i].SetLineColor(Colors[i]);
      G[i].SetMarkerStyle(20);
      G[i].SetMarkerColor(Colors[i]);

      if(DHFile.Exist(States[i]) == false)
         continue;

      int Count = DHFile[States[i]]["N"].GetInteger();
      for(int j = 0; j < Count; j++)
      {
         double Rho = DHFile[States[i]]["Rho"+to_string(j)].GetDouble();
         G[i].SetPoint(j, j + 0.5, Rho);
      }

      if(Count > MaxCount)
         MaxCount = Count;
   }

   TLegend Legend(0.2, 0.6, 0.4, 0.8);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   for(int i = 0; i < N; i++)
      Legend.AddEntry(&G[i], (Labels[i] + " (" + States[i] + ")").c_str(), "pl");

   TH2D HWorld("HWorld", ";Bin index;Correlation", 100, 0, MaxCount, 100, 0, 1);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.Draw("axis");
   for(int i = 0; i < N; i++)
      G[i].Draw("pl");

   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}




