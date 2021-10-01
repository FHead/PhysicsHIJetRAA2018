#include <vector>
#include <iostream>
#include <map>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "CustomAssert.h"
#include "Code/TauHelperFunctions3.h"

#include "Messenger.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input", "SampleExample/HiForestAOD.root");
   string OutputFileName = CL.Get("Output", "Output/JetTreeAOD.root");

   double Fraction       = CL.GetDouble("Fraction", 1.00);

   string JetName        = CL.Get("Jet", "akFlowPuCs4PFJetAnalyzer/t");
   double JetR           = CL.GetDouble("JetR", 0.4);
   string Trigger        = CL.Get("Trigger", "NONE");

   double EtaMin         = CL.GetDouble("EtaMin", -2.0);
   double EtaMax         = CL.GetDouble("EtaMax", +2.0);

   bool CheckCentrality  = CL.GetBool("CheckCentrality", true);
   double CentralityMin  = CL.GetDouble("CentralityMin", 0.00);
   double CentralityMax  = CL.GetDouble("CentralityMax", 1.00);

   bool UseStoredGen     = CL.GetBool("UseStoredGen", false);
   bool UseStoredReco    = CL.GetBool("UseStoredReco", true);

   Assert(UseStoredReco == true, "reco reclustering not implemented yet");

   TFile InputFile(InputFileName.c_str());

   HiEventTreeMessenger MEvent(InputFile);
   GenParticleTreeMessenger MGen(InputFile);
   JetTreeMessenger MJet(InputFile, JetName);
   TriggerTreeMessenger MTrigger(InputFile, "hltanalysis/HltTree");

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("UnfoldingTree", "Trees for unfolding studies");

   double EventWeight = 1;
   int NRecoJets = 0;
   vector<float> RecoJetPT;
   vector<float> RecoJetEta;
   vector<float> RecoJetPhi;
   vector<float> RecoJetMass;
   vector<float> RecoJetJEC;
   vector<float> RecoJetJEU;
   int NGenJets = 0;
   vector<float> GenJetPT;
   vector<float> GenJetEta;
   vector<float> GenJetPhi;
   vector<float> GenJetMass;
   vector<float> MatchedJetPT;
   vector<float> MatchedJetEta;
   vector<float> MatchedJetPhi;
   vector<float> MatchedJetMass;
   vector<float> MatchedJetAngle;
   vector<float> MatchedJetJEC;
   vector<float> MatchedJetJEU;

   OutputTree.Branch("EventWeight",     &EventWeight,    "EventWeight/D");
   OutputTree.Branch("NRecoJets",       &NRecoJets);
   OutputTree.Branch("RecoJetPT",       &RecoJetPT);
   OutputTree.Branch("RecoJetEta",      &RecoJetEta);
   OutputTree.Branch("RecoJetPhi",      &RecoJetPhi);
   OutputTree.Branch("RecoJetMass",     &RecoJetMass);
   OutputTree.Branch("RecoJetJEC",      &RecoJetJEC);
   OutputTree.Branch("RecoJetJEU",      &RecoJetJEU);
   OutputTree.Branch("NGenJets",        &NGenJets);
   OutputTree.Branch("GenJetPT",        &GenJetPT);
   OutputTree.Branch("GenJetEta",       &GenJetEta);
   OutputTree.Branch("GenJetPhi",       &GenJetPhi);
   OutputTree.Branch("GenJetMass",      &GenJetMass);
   OutputTree.Branch("MatchedJetPT",    &MatchedJetPT);
   OutputTree.Branch("MatchedJetEta",   &MatchedJetEta);
   OutputTree.Branch("MatchedJetPhi",   &MatchedJetPhi);
   OutputTree.Branch("MatchedJetMass",  &MatchedJetMass);
   OutputTree.Branch("MatchedJetAngle", &MatchedJetAngle);
   OutputTree.Branch("MatchedJetJEC",   &MatchedJetJEC);
   OutputTree.Branch("MatchedJetJEU",   &MatchedJetJEU);

   int EntryCount = MEvent.Tree->GetEntries() * Fraction;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MEvent.GetEntry(iE);
      MGen.GetEntry(iE);
      MJet.GetEntry(iE);
      MTrigger.GetEntry(iE);

      EventWeight = MEvent.weight;

      if(Trigger != "NONE" && Trigger != "None")
      {
         int Decision = MTrigger.CheckTriggerStartWith(Trigger);

         if(Decision < 0)
            cerr << "Warning! Trigger not found!" << endl;
         if(Decision == 0)   // trigger found and not fired
            continue;
      }

      if(CheckCentrality == true)
      {
         if(MEvent.hiBin * 0.005 < CentralityMin)
            continue;
         if(MEvent.hiBin * 0.005 > CentralityMax)
            continue;
      }

      vector<pair<FourVector, PseudoJet>> GenJets;
      vector<pair<FourVector, PseudoJet>> RecoJets;

      if(UseStoredGen == true)
      {
         for(int iG = 0; iG < MJet.GenCount; iG++)
         {
            if(MJet.GenEta[iG] < EtaMin || MJet.GenEta[iG] > EtaMax)
               continue;

            FourVector P;
            P.SetPtEtaPhi(MJet.GenPT[iG], MJet.GenEta[iG], MJet.GenPhi[iG]);
            PseudoJet J(P[1], P[2], P[3], P[0]);
            GenJets.push_back(pair<FourVector, PseudoJet>(P, J));
         }
      }
      else
      {
         // Cluster gen jets
         vector<PseudoJet> VisibleParticles;
         for(int iG = 0; iG < MGen.ID->size(); iG++)
         {
            FourVector P;
            P.SetPtEtaPhi(MGen.PT->at(iG), MGen.Eta->at(iG), MGen.Phi->at(iG));

            if(MGen.ID->at(iG) == 12 || MGen.ID->at(iG) == -12)
               continue;
            if(MGen.ID->at(iG) == 14 || MGen.ID->at(iG) == -14)
               continue;
            if(MGen.ID->at(iG) == 16 || MGen.ID->at(iG) == -16)
               continue;
            if(MGen.DaughterCount->at(iG) > 0)
               continue;

            VisibleParticles.emplace_back(PseudoJet(P[1], P[2], P[3], P[0]));
         }

         JetDefinition Definition(antikt_algorithm, JetR);
         ClusterSequence Sequence(VisibleParticles, Definition);
         vector<PseudoJet> GenFastJets = Sequence.inclusive_jets(0.5);   // anti-kt, R = 0.4

         vector<pair<FourVector, PseudoJet>> GenJets;
         for(int iG = 0; iG < GenFastJets.size(); iG++)
         {
            if(GenFastJets[iG].eta() < EtaMin || GenFastJets[iG].eta() > EtaMax)
               continue;
            
            PseudoJet &J = GenFastJets[iG];
            FourVector P(J.e(), J.px(), J.py(), J.pz());
            GenJets.push_back(pair<FourVector, PseudoJet>(P, J));
         }
      }
      
      for(int iR = 0; iR < MJet.JetCount; iR++)
      {
         if(MJet.JetEta[iR] < EtaMin || MJet.JetEta[iR] > EtaMax)
            continue;
         
         FourVector P;
         P.SetPtEtaPhi(MJet.JetPT[iR], MJet.JetEta[iR], MJet.JetPhi[iR]);
         PseudoJet J(P[1], P[2], P[3], P[0]);
         RecoJets.push_back(pair<FourVector, PseudoJet>(P, J));
      }

      // Export gen jet as clustered from the gen particles
      NGenJets = GenJets.size();
      GenJetPT.resize(NGenJets);
      GenJetEta.resize(NGenJets);
      GenJetPhi.resize(NGenJets);
      GenJetMass.resize(NGenJets);
      for(int iG = 0; iG < NGenJets; iG++)
      {
         GenJetPT[iG]   = GenJets[iG].first.GetPT();
         GenJetEta[iG]  = GenJets[iG].first.GetEta();
         GenJetPhi[iG]  = GenJets[iG].first.GetPhi();
         GenJetMass[iG] = GenJets[iG].first.GetMass();
      }

      // Export reco jets
      NRecoJets = RecoJets.size();
      RecoJetPT.resize(NRecoJets);
      RecoJetEta.resize(NRecoJets);
      RecoJetPhi.resize(NRecoJets);
      RecoJetMass.resize(NRecoJets);
      RecoJetJEC.resize(NRecoJets);
      RecoJetJEU.resize(NRecoJets);
      for(int iR = 0; iR < NRecoJets; iR++)
      {
         RecoJetPT[iR]   = RecoJets[iR].first.GetPT();
         RecoJetEta[iR]  = RecoJets[iR].first.GetEta();
         RecoJetPhi[iR]  = RecoJets[iR].first.GetPhi();
         RecoJetMass[iR] = RecoJets[iR].first.GetMass();
         RecoJetJEC[iR]  = 1.00;   // to be implemented
         RecoJetJEU[iR]  = 0.02;
      }

      // For each gen jet, find the best reco jet
      MatchedJetPT.resize(NGenJets);
      MatchedJetEta.resize(NGenJets);
      MatchedJetPhi.resize(NGenJets);
      MatchedJetMass.resize(NGenJets);
      MatchedJetAngle.resize(NGenJets);
      MatchedJetJEC.resize(NGenJets);
      MatchedJetJEU.resize(NGenJets);
      for(int iG = 0; iG < NGenJets; iG++)
      {
         MatchedJetAngle[iG] = -1;

         int BestIndex = -1;
         double BestAngle = -1;
         for(int iR = 0; iR < NRecoJets; iR++)
         {
            double Angle = GetDR(GenJets[iG].first, RecoJets[iR].first);
            if(BestAngle < 0 || Angle < BestAngle)
            {
               BestIndex = iR;
               BestAngle = Angle;
            }
         }

         if(BestIndex < 0)   // not found for some reason
            continue;

         MatchedJetPT[iG]    = RecoJets[BestIndex].first.GetPT();
         MatchedJetEta[iG]   = RecoJets[BestIndex].first.GetEta();
         MatchedJetPhi[iG]   = RecoJets[BestIndex].first.GetPhi();
         MatchedJetMass[iG]  = RecoJets[BestIndex].first.GetMass();
         MatchedJetJEC[iG]   = RecoJetJEC[BestIndex];
         MatchedJetJEU[iG]   = RecoJetJEU[BestIndex];
         MatchedJetAngle[iG] = BestAngle;
      }

      OutputTree.Fill();
   }

   OutputFile.cd();
   OutputTree.Write();
   OutputFile.Close();

   InputFile.Close();

   return 0;
}





