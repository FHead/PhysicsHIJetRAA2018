#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions3.h"
#include "CommandLine.h"

#define MAX 10000

int main(int argc, char *argv[]);
bool PTSort(const pair<FourVector, FourVector> &P1, const pair<FourVector, FourVector> &P2);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   double Fraction               = CL.GetDouble("Fraction", 1.00);
   bool IsMC                     = CL.GetBool("IsMC", false);
   double MaxAngle               = CL.GetDouble("MaxAngle", 0.2);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("DijetTree", "");

   float Weight, Centrality;
   float PT1, Eta1, Phi1, PT2, Eta2, Phi2, PT3, Eta3, Phi3;
   float GenPT1, GenPT2, GenPT3;
   OutputTree.Branch("Weight", &Weight, "Weight/F");
   OutputTree.Branch("Centrality", &Centrality, "Centrality/F");
   OutputTree.Branch("PT1",    &PT1,    "PT1/F");
   OutputTree.Branch("Eta1",   &Eta1,   "Eta1/F");
   OutputTree.Branch("Phi1",   &Phi1,   "Phi1/F");
   OutputTree.Branch("PT2",    &PT2,    "PT2/F");
   OutputTree.Branch("Eta2",   &Eta2,   "Eta2/F");
   OutputTree.Branch("Phi2",   &Phi2,   "Phi2/F");
   OutputTree.Branch("PT3",    &PT3,    "PT3/F");
   OutputTree.Branch("Eta3",   &Eta3,   "Eta3/F");
   OutputTree.Branch("Phi3",   &Phi3,   "Phi3/F");
   OutputTree.Branch("GenPT1", &GenPT1, "GenPT1/F");
   OutputTree.Branch("GenPT2", &GenPT2, "GenPT2/F");
   OutputTree.Branch("GenPT3", &GenPT3, "GenPT3/F");

   for(string FileName : InputFileNames)
   {
      TFile File(FileName.c_str());

      TTree *Tree = (TTree *)File.Get("UnfoldingTreeFlat");

      double EventWeight;
      double EventCentrality;
      int NJets;
      float RecoJetPT[MAX];
      float RecoJetEta[MAX];
      float RecoJetPhi[MAX];
      float GenJetPT[MAX];
      float GenJetEta[MAX];
      float GenJetPhi[MAX];
      float JetAngle[MAX] = {0};
      
      Tree->SetBranchAddress("EventWeight", &EventWeight);
      Tree->SetBranchAddress("Centrality", &EventCentrality);
      if(IsMC == false)
      {
         Tree->SetBranchAddress("NRecoJets", &NJets);
         Tree->SetBranchAddress("RecoJetPT", &RecoJetPT);
         Tree->SetBranchAddress("RecoJetEta", &RecoJetEta);
         Tree->SetBranchAddress("RecoJetPhi", &RecoJetPhi);
      }
      else
      {
         Tree->SetBranchAddress("NGenJets", &NJets);
         Tree->SetBranchAddress("GenJetPT", &GenJetPT);
         Tree->SetBranchAddress("GenJetEta", &GenJetEta);
         Tree->SetBranchAddress("GenJetPhi", &GenJetPhi);
         Tree->SetBranchAddress("MatchedJetPT", &RecoJetPT);
         Tree->SetBranchAddress("MatchedJetEta", &RecoJetEta);
         Tree->SetBranchAddress("MatchedJetPhi", &RecoJetPhi);
         Tree->SetBranchAddress("MatchedJetAngle", &JetAngle);
      }

      int EntryCount = Tree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);
         Weight = EventWeight;
         Centrality = EventCentrality;

         if(NJets == 0)
            continue;

         vector<pair<FourVector, FourVector>> Jets;
         for(int iJ = 0; iJ < NJets; iJ++)
         {
            FourVector PGen, PReco;
            PGen.SetPtEtaPhi(GenJetPT[iJ], GenJetEta[iJ], GenJetPhi[iJ]);
            PReco.SetPtEtaPhi(RecoJetPT[iJ], RecoJetEta[iJ], RecoJetPhi[iJ]);
            if(IsMC == true)
            {
               if(JetAngle[iJ] < MaxAngle && JetAngle[iJ] > 0)
                 Jets.push_back(pair<FourVector, FourVector>(PGen, PReco));
            }
            else
               Jets.push_back(pair<FourVector, FourVector>(PReco, PReco));
         }

         sort(Jets.begin(), Jets.end(), PTSort);

         PT1 = 0; Eta1 = 0; Phi1 = 0; GenPT1 = 0;
         PT2 = 0; Eta2 = 0; Phi2 = 0; GenPT2 = 0;
         PT3 = 0; Eta3 = 0; Phi3 = 0; GenPT3 = 0;

         if(Jets.size() > 0)
         {
            GenPT1 = Jets[0].first.GetPT();
            PT1    = Jets[0].second.GetPT();
            Eta1   = Jets[0].second.GetEta();
            Phi1   = Jets[0].second.GetPhi();
         }
         if(Jets.size() > 1)
         {
            GenPT2 = Jets[1].first.GetPT();
            PT2    = Jets[1].second.GetPT();
            Eta2   = Jets[1].second.GetEta();
            Phi2   = Jets[1].second.GetPhi();
         }
         if(Jets.size() > 2)
         {
            GenPT3 = Jets[2].first.GetPT();
            PT3    = Jets[2].second.GetPT();
            Eta3   = Jets[2].second.GetEta();
            Phi3   = Jets[2].second.GetPhi();
         }

         OutputTree.Fill();
      }

      File.Close();
   }

   OutputFile.cd();
   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

bool PTSort(const pair<FourVector, FourVector> &P1, const pair<FourVector, FourVector> &P2)
{
   if(P1.second.InnerGetPT() > P2.second.InnerGetPT())   return true;
   if(P1.second.InnerGetPT() < P2.second.InnerGetPT())   return false;
   if(P1.first.InnerGetPT() > P2.first.InnerGetPT())   return true;
   if(P1.first.InnerGetPT() < P2.first.InnerGetPT())   return false;
   return false;
}



