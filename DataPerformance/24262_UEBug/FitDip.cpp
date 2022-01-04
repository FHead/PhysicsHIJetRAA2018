#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "CommandLine.h"

class FitDip;
int main(int argc, char *argv[]);

class FitDip
{
   vector<double> EtaPass;
   vector<double> EtaNoPass;
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   double CentralityMin = CL.GetDouble("CentralityMin", 0);
   double CentralityMax = CL.GetDouble("CentralityMax", 1);
   double PTMin         = CL.GetDouble("PTMin", 150);
   double PTMax         = CL.GetDouble("PTMax", 1000);
   double PhiMin        = CL.GetDouble("PhiMin", 2.0);
   double PhiMax        = CL.GetDouble("PhiMax", -2.0);

   if(PhiMin > PhiMax)
      PhiMax = PhiMax + 2 * M_PI;

   TFile InputFile(InputFileName.c_str());

   FitDip Fit;

   TTree *Tree = (TTree *)InputFile.Get("TriggerTree");

   float Centrality;
   float JetPT, JetEta, JetPhi;
   bool PassTrigger;
   Tree->SetBranchAddress("Centrality", &Centrality);
   Tree->SetBranchAddress("JetPT", &JetPT);
   Tree->SetBranchAddress("JetEta", &JetEta);
   Tree->SetBranchAddress("JetPhi", &JetPhi);
   Tree->SetBranchAddress("PassTrigger", &PassTrigger);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(Centrality < CentralityMin)   continue;
      if(Centrality > CentralityMax)   continue;

      if(JetPT < PTMin)   continue;
      if(JetPT > PTMax)   continue;

      if(JetPhi + 0 * M_PI < PhiMin)   continue;
      if(JetPhi + 0 * M_PI > PhiMax)   continue;
      if(JetPhi + 2 * M_PI < PhiMin)   continue;
      if(JetPhi + 2 * M_PI > PhiMax)   continue;
      if(JetPhi - 2 * M_PI < PhiMin)   continue;
      if(JetPhi - 2 * M_PI > PhiMax)   continue;

      if(PassTrigger == true)
         EtaPass.push_back(JetEta);
      else
         EtaNoPass.push_back(JetEta);
   }

   InputFile.Close();
}



