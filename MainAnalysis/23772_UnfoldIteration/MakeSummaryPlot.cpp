#include <iostream>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "DataHelper.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DHFileName = CL.Get("DHFile");
   string OutputFileName = CL.Get("Output");
   string PPBase = CL.Get("PPBase");
   string AABase = CL.Get("AABase");

   vector<string> RLabel = CL.GetStringVector("R", vector<string>{"1", "2", "3", "4", "5", "6", "7", "8", "9"});
   vector<string> CLabel = CL.GetStringVector("C", vector<string>{"Inclusive", "0to10", "10to30", "30to50", "50to70", "70to90", "50to90"});
   vector<string> Base   = CL.GetStringVector("B", vector<string>{PPBase, AABase, AABase, AABase, AABase, AABase, AABase});

   DataHelper DHFile(DHFileName);

   int NX = RLabel.size();
   int NY = CLabel.size();

   TH2D H("H", ";;", NX, 0, NX, NY, 0, NY);
   H.SetStats(0);

   for(int i = 0; i < NX; i++)
      H.GetXaxis()->SetBinLabel(i + 1, Form("%.2f", DHFile["JetR"][RLabel[i]].GetDouble()));
   for(int i = 0; i < NY; i++)
      H.GetYaxis()->SetBinLabel(i + 1, CLabel[i].c_str());

   for(int iX = 0; iX < NX; iX++)
   {
      for(int iY = 0; iY < NY; iY++)
      {
         string Key = Base[iY] + "_R" + RLabel[iX] + "_Centrality" + CLabel[iY];
         string Prior = DHFile["PriorToUse"][Key+"_Default"].GetString();
         Key = Key + "_Nominal_" + Prior + "Prior";
         int Value = DHFile["Iterations"][Key].GetInteger();
         H.SetBinContent(iX + 1, iY + 1, Value);
      }
   }

   TCanvas Canvas;
   H.Draw("colz text00");
   Canvas.SaveAs(OutputFileName.c_str());

   return 0;
}




