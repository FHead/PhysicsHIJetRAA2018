#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TF1.h"

#include "CommandLine.h"
#include "DataHelper.h"

#define MAX 10000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");

   string DHFileName    = CL.Get("DHFile");
   string DHState       = CL.Get("DHState");

   DataHelper DHFile(DHFileName);
   TF1 F("F", ("("+DHFile[DHState]["Formula"].GetString()+")/[0]").c_str());
   for(int i = 0; i < DHFile[DHState]["N"].GetInteger(); i++)
      F.SetParameter(i, DHFile[DHState]["P"+to_string(i)].GetDouble());

   double CentralityMin = CL.GetDouble("CentralityMin", -999);
   double CentralityMax = CL.GetDouble("CentralityMax", 999);
   double PTMin         = CL.GetDouble("PTMin", 200);
   double PTMax         = CL.GetDouble("PTMax", 1500);

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get("UnfoldingTreeFlat");

   double Centrality;
   int NRecoJets;
   float RecoJetPT[MAX];
   float RecoJetEta[MAX];
   float RecoJetPhi[MAX];
   float RecoJetWeight[MAX];

   Tree->SetBranchAddress("Centrality", &Centrality);
   Tree->SetBranchAddress("NRecoJets", &NRecoJets);
   Tree->SetBranchAddress("RecoJetPT", &RecoJetPT);
   Tree->SetBranchAddress("RecoJetEta", &RecoJetEta);
   Tree->SetBranchAddress("RecoJetPhi", &RecoJetPhi);
   Tree->SetBranchAddress("RecoJetWeight", &RecoJetWeight);

   double Total = 0;
   double Weighted = 0;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(Centrality < CentralityMin)    continue;
      if(Centrality >= CentralityMax)   continue;

      for(int iJ = 0; iJ < NRecoJets; iJ++)
      {
         if(RecoJetPT[iJ] < PTMin)   continue;
         if(RecoJetPT[iJ] > PTMax)   continue;

         double Weight = F.Eval(fabs(RecoJetEta[iJ]));

         // cout << RecoJetEta[iJ] << " " << Weight << endl;

         Total = Total + RecoJetWeight[iJ];
         Weighted = Weighted + RecoJetWeight[iJ] / Weight;
      }
   }

   cout << Total << " " << Weighted << " " << Weighted / Total << endl;

   File.Close();

   return 0;
}



