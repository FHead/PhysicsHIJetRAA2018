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

   TH1D HCentralityRaw150("HCentralityRaw150", "Reco Jet PT > 150 GeV;Centrality;", 20, 0, 1);
   TH1D HCentralityTAA150("HCentralityTAA150", "Reco Jet PT > 150 GeV;Centrality;", 20, 0, 1);
   TH1D HCentralityRaw250("HCentralityRaw250", "Reco Jet PT > 250 GeV;Centrality;", 20, 0, 1);
   TH1D HCentralityTAA250("HCentralityTAA250", "Reco Jet PT > 250 GeV;Centrality;", 20, 0, 1);
   TH1D HCentralityRaw350("HCentralityRaw350", "Reco Jet PT > 350 GeV;Centrality;", 20, 0, 1);
   TH1D HCentralityTAA350("HCentralityTAA350", "Reco Jet PT > 350 GeV;Centrality;", 20, 0, 1);
   TH1D HCentralityRaw450("HCentralityRaw450", "Reco Jet PT > 450 GeV;Centrality;", 20, 0, 1);
   TH1D HCentralityTAA450("HCentralityTAA450", "Reco Jet PT > 450 GeV;Centrality;", 20, 0, 1);

   HCentralityRaw250.SetStats(0);
   HCentralityTAA250.SetStats(0);
   HCentralityRaw350.SetStats(0);
   HCentralityTAA350.SetStats(0);
   HCentralityRaw450.SetStats(0);
   HCentralityTAA450.SetStats(0);

   for(string InputFileName : InputFileNames)
   {
      TFile InputFile(InputFileName.c_str());

      TTree *Tree = (TTree *)InputFile.Get("UnfoldingTreeFlat");

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

      int EntryCount = Tree->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         int CBin = (int)(Centrality * 100);
         if(CBin == 100)   // just in case
            CBin = 99;

         for(int iJ = 0; iJ < NRecoJets; iJ++)
         {
            if(RecoJetPT[iJ] > 150)
            {
               HCentralityRaw150.Fill(Centrality + 0.00001, RecoJetWeight[iJ]);
               HCentralityTAA150.Fill(Centrality + 0.00001, RecoJetWeight[iJ] * CentralityWeights[CBin]);
            }
            if(RecoJetPT[iJ] > 250)
            {
               HCentralityRaw250.Fill(Centrality + 0.00001, RecoJetWeight[iJ]);
               HCentralityTAA250.Fill(Centrality + 0.00001, RecoJetWeight[iJ] * CentralityWeights[CBin]);
            }
            if(RecoJetPT[iJ] > 350)
            {
               HCentralityRaw350.Fill(Centrality + 0.00001, RecoJetWeight[iJ]);
               HCentralityTAA350.Fill(Centrality + 0.00001, RecoJetWeight[iJ] * CentralityWeights[CBin]);
            }
            if(RecoJetPT[iJ] > 450)
            {
               HCentralityRaw450.Fill(Centrality + 0.00001, RecoJetWeight[iJ]);
               HCentralityTAA450.Fill(Centrality + 0.00001, RecoJetWeight[iJ] * CentralityWeights[CBin]);
            }
         }
      }

      InputFile.Close();
   }

   PdfFile.AddPlot(HCentralityRaw150);
   PdfFile.AddPlot(HCentralityTAA150);
   PdfFile.AddPlot(HCentralityRaw250);
   PdfFile.AddPlot(HCentralityTAA250);
   PdfFile.AddPlot(HCentralityRaw350);
   PdfFile.AddPlot(HCentralityTAA350);
   PdfFile.AddPlot(HCentralityRaw450);
   PdfFile.AddPlot(HCentralityTAA450);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




