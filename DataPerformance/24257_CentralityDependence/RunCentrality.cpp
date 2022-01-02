#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"

#include "CommandLine.h"
#include "DataHelper.h"
#include "SetStyle.h"
#include "PlotHelper4.h"

#define MAX 10000

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string DHFileName             = CL.Get("DHFile");
   string OutputFileName         = CL.Get("Output");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Centrality check");

   DataHelper DHFile(DHFileName);

   double CentralityWeights[100] = {0};
   for(int i = 0; i < 100; i = i + 5)
   {
      string Key = to_string(i) + "to" + to_string(i + 5);
      double InverseTAA = 1 / DHFile["TAA"][Key].GetDouble();

      CentralityWeights[i+0] = InverseTAA;
      CentralityWeights[i+1] = InverseTAA;
      CentralityWeights[i+2] = InverseTAA;
      CentralityWeights[i+3] = InverseTAA;
      CentralityWeights[i+4] = InverseTAA;
   }

   TH1D HCentralityRaw("HCentralityRaw", "Reco Jet PT > 250 GeV;Centrality;", 200, 0, 1);
   TH1D HCentralityTAA("HCentralityTAA", "Reco Jet PT > 250 GeV;Centrality;", 200, 0, 1);

   HCentralityRaw.SetStats(0);
   HCentralityTAA.SetStats(0);

   for(string InputFileName : InputFileNames)
   {
      TFile InputFile(InputFileName.c_str());

      TTree *Tree = (TTree *)InputFile.Get("UnfoldingTreeFlat");

      double Centrality;
      int NRecoJets;
      double RecoJetPT[MAX];
      double RecoJetEta[MAX];
      double RecoJetPhi[MAX];
      double RecoJetWeight[MAX];
      
      Tree->SetBranchAddress("Centrality", &Centrality);
      Tree->SetBranchAddress("NRecoJets", &NRecoJets);
      Tree->SetBranchAddress("RecoJetPT", &RecoJetPT);
      Tree->SetBranchAddress("RecoJetEta", &RecoJetEta);
      Tree->SetBranchAddress("RecoJetPhi", &RecoJetPhi);
      Tree->SetBranchAddress("RecoJetWeight", &RecoJetWeight);

      int EntryCount = Tree->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         int CBin = (int)(Centrality * 100);
         if(CBin == 100)   // just in case
            CBin = 99;

         for(int iJ = 0; iJ < NRecoJets; iJ++)
         {
            if(RecoJetPT[iJ] < 250)
               continue;

            HCentralityRaw.Fill(Centrality + 0.0025, RecoJetWeight[iJ]);
            HCentralityTAA.Fill(Centrality + 0.0025, RecoJetWeight[iJ] * CentralityWeights[CBin]);
         }
      }

      InputFile.Close();
   }

   PdfFile.AddPlot(HCentralityRaw);
   PdfFile.AddPlot(HCentralityRaw, "hist");
   PdfFile.AddPlot(HCentralityTAA);
   PdfFile.AddPlot(HCentralityTAA, "hist");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




