#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#include "TGraph.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TF1.h"
#include "TLegend.h"

#include "DataHelper.h"
#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   vector<int> Colors = GetPrimaryColors();
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DHFileName = CL.Get("DHFile");
   string DHFileNameNew = CL.Get("DHFileNew");
   string OutputFileName = CL.Get("Output");

   DataHelper DHFile(DHFileName);
   DataHelper DHFileNew(DHFileNameNew);

   vector<string> Keys = DHFile["RhoWeight"].GetListOfKeys();

   vector<string> States;
   for(string Key : Keys)
   {
      size_t index = Key.find_last_of('_');
      if(index == string::npos)
         continue;
      States.push_back(Key.substr(0, index));
   }
   sort(States.begin(), States.end());
   States.erase(unique(States.begin(), States.end()), States.end());

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Rho weight comparison");

   for(string State : States)
   {
      cout << State << endl;

      double XMin = min(DHFile["RhoWeight"][State+"_MinUE"].GetDouble(),
         DHFileNew["RhoWeight"][State+"_MinUE"].GetDouble());
      double XMax = max(DHFile["RhoWeight"][State+"_MaxUE"].GetDouble(),
         DHFileNew["RhoWeight"][State+"_MaxUE"].GetDouble());
      double YMax = 0;
      double YMin = 1;

      TF1 FOld("FOld", DHFile["RhoWeight"][State+"_Formula"].GetString().c_str(),
         DHFile["RhoWeight"][State+"_MinUE"].GetDouble(),
         DHFile["RhoWeight"][State+"_MaxUE"].GetDouble());
      TF1 FNew("FNew", DHFileNew["RhoWeight"][State+"_Formula"].GetString().c_str(),
         DHFileNew["RhoWeight"][State+"_MinUE"].GetDouble(),
         DHFileNew["RhoWeight"][State+"_MaxUE"].GetDouble());

      int NOld = DHFile["RhoWeight"][State+"_NPar"].GetInteger();
      for(int i = 0; i < NOld; i++)
         FOld.SetParameter(i, DHFile["RhoWeight"][State+"_P"+to_string(i)].GetDouble());

      int NNew = DHFileNew["RhoWeight"][State+"_NPar"].GetInteger();
      for(int i = 0; i < NNew; i++)
         FNew.SetParameter(i, DHFileNew["RhoWeight"][State+"_P"+to_string(i)].GetDouble());

      int N = 1000;
      double OldMax = 0, NewMax = 0;
      for(int i = 0; i < N; i++)
      {
         double X = (XMax - XMin) * (i + 0.5) / N + XMin;

         double YOld = FOld.Eval(X);
         double YNew = FNew.Eval(X);

         if(OldMax < YOld)   OldMax = YOld;
         if(NewMax < YNew)   NewMax = YNew;
      }

      TGraph GOld, GNew;
      for(int i = 0; i < N; i++)
      {
         double X = (XMax - XMin) * (i + 0.5) / N + XMin;

         double YOld = FOld.Eval(X) / OldMax;
         double YNew = FNew.Eval(X) / NewMax;

         GOld.SetPoint(GOld.GetN(), X, YOld);
         GNew.SetPoint(GNew.GetN(), X, YNew);

         if(YMin >= YMax)
         {
            YMin = min(YOld, YNew);
            YMax = max(YOld, YNew);
         }

         if(YMin > YOld)   YMin = YOld;
         if(YMin > YNew)   YMin = YNew;
         if(YMax < YOld)   YMax = YOld;
         if(YMax < YNew)   YMax = YNew;
      }

      GOld.SetLineWidth(2);
      GOld.SetLineColor(Colors[0]);
      GNew.SetLineWidth(2);
      GNew.SetLineColor(Colors[1]);

      TH2D HWorld("HWorld", Form("%s;UE (GeV);Weight", State.c_str()), 100, XMin, XMax, 100, 0, YMax * 1.2);
      HWorld.SetStats(0);

      TCanvas Canvas;

      HWorld.Draw();
      GOld.Draw("l");
      GNew.Draw("l");

      TLegend Legend(0.5, 0.8, 0.8, 0.6);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.AddEntry(&GOld, "Old", "l");
      Legend.AddEntry(&GNew, "New", "l");
      Legend.Draw();

      PdfFile.AddCanvas(Canvas);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}


