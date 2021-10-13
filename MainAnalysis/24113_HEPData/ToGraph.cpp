#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[])
{
   vector<string> FileBases{"CMS-R02", "CMS-R03", "CMS-R04", "CMS-R06", "CMS-R08", "CMS-R10", "ATLAS-R04"};

   for(string FileBase : FileBases)
   {
      TFile OutputFile(Form("Graph_%s.root", FileBase.c_str()), "RECREATE");

      TGraphAsymmErrors G;

      TFile InputFile(Form("%s.root", FileBase.c_str()));

      TTree *Tree = (TTree *)InputFile.Get("Tree");

      double XMin, XMax, Y, StatLow, StatHigh, SysLow, SysHigh, GlobalLow, GlobalHigh;
      Tree->SetBranchAddress("XMin",       &XMin);
      Tree->SetBranchAddress("XMax",       &XMax);
      Tree->SetBranchAddress("Y",          &Y);
      Tree->SetBranchAddress("StatLow",    &StatLow);
      Tree->SetBranchAddress("StatHigh",   &StatHigh);
      Tree->SetBranchAddress("SysLow",     &SysLow);
      Tree->SetBranchAddress("SysHigh",    &SysHigh);
      Tree->SetBranchAddress("GlobalLow",  &GlobalLow);
      Tree->SetBranchAddress("GlobalHigh", &GlobalHigh);

      int EntryCount = Tree->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         double X = (XMin + XMax) / 2;

         double Low = sqrt(StatLow * StatLow + SysLow * SysLow + GlobalLow * GlobalLow);
         double High = sqrt(StatHigh * StatHigh + SysHigh * SysHigh + GlobalHigh * GlobalHigh);

         G.SetPoint(iE, X, Y);
         G.SetPointError(iE, X - XMin, XMax - X, Low, High);
      }

      InputFile.Close();

      G.SetNameTitle("GHEPData", "G");

      OutputFile.cd();

      G.Write();

      OutputFile.Close();
   }

   return 0;
}




