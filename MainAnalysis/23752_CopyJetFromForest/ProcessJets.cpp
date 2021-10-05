#include <vector>
#include <iostream>
#include <map>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "ProgressBar.h"
#include "CommandLine.h"
#include "CustomAssert.h"
#include "Code/TauHelperFunctions3.h"

#include "Messenger.h"
#include "JetCorrector.h"
#include "JetUncertainty.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName    = CL.Get("Input", "SampleExample/HiForestAOD.root");
   string OutputFileName   = CL.Get("Output", "Output/JetTreeAOD.root");

   double Fraction         = CL.GetDouble("Fraction", 1.00);

   string JetName          = CL.Get("Jet", "akFlowPuCs4PFJetAnalyzer/t");
   double JetR             = CL.GetDouble("JetR", 0.4);
   vector<string> JECFile  = CL.GetStringVector("JEC", vector<string>{"None"});
   string JEUFile          = CL.Get("JEU", "None");
   string Trigger          = CL.Get("Trigger", "NONE");

   double EtaMin           = CL.GetDouble("EtaMin", -2.0);
   double EtaMax           = CL.GetDouble("EtaMax", +2.0);

   double PTMin            = CL.GetDouble("PTMin", 0);

   bool CheckCentrality    = CL.GetBool("CheckCentrality", true);
   double CentralityMin    = CL.GetDouble("CentralityMin", 0.00);
   double CentralityMax    = CL.GetDouble("CentralityMax", 1.00);

   bool UseStoredGen       = CL.GetBool("UseStoredGen", false);
   bool UseStoredReco      = CL.GetBool("UseStoredReco", true);
   bool DoRecoSubtraction  = UseStoredReco ? CL.GetBool("DoRecoSubtraction") : false;

   Assert(DoRecoSubtraction == false, "reco reclustering in PbPb case not implemented yet");

   JetCorrector JEC(JECFile);
   JetUncertainty JEU(JEUFile);

   TFile InputFile(InputFileName.c_str());

   HiEventTreeMessenger MEvent(InputFile);
   GenParticleTreeMessenger MGen(InputFile);
   JetTreeMessenger MJet(InputFile, JetName);
   TriggerTreeMessenger MTrigger(InputFile, "hltanalysis/HltTree");
   PFTreeMessenger MPF(InputFile, "pfcandAnalyzer/pfTree");

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
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(2);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0)
         Bar.Print();

      MEvent.GetEntry(iE);
      MGen.GetEntry(iE);
      MJet.GetEntry(iE);
      MTrigger.GetEntry(iE);
      MPF.GetEntry(iE);

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
      RecoJetJEC.clear();

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
         if(MGen.Tree != nullptr)
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

            for(int iG = 0; iG < GenFastJets.size(); iG++)
            {
               if(GenFastJets[iG].eta() < EtaMin || GenFastJets[iG].eta() > EtaMax)
                  continue;

               PseudoJet &J = GenFastJets[iG];
               FourVector P(J.e(), J.px(), J.py(), J.pz());
               GenJets.push_back(pair<FourVector, PseudoJet>(P, J));
            }
         }
      }
      
      if(UseStoredReco == true)
      {
         for(int iR = 0; iR < MJet.JetCount; iR++)
         {
            if(MJet.JetEta[iR] < EtaMin || MJet.JetEta[iR] > EtaMax)
               continue;

            JEC.SetJetPT(MJet.JetRawPT[iR]);
            JEC.SetJetEta(MJet.JetEta[iR]);
            JEC.SetJetPhi(MJet.JetPhi[iR]);
            MJet.JetPT[iR] = JEC.GetCorrectedPT();

            if(MJet.JetPT[iR] < PTMin && MJet.JetRawPT[iR] < PTMin)
               continue;

            FourVector P;
            P.SetPtEtaPhi(MJet.JetPT[iR], MJet.JetEta[iR], MJet.JetPhi[iR]);
            PseudoJet J(P[1], P[2], P[3], P[0]);
            RecoJets.push_back(pair<FourVector, PseudoJet>(P, J));
            RecoJetJEC.push_back(JEC.GetCorrection());
         }
      }
      else
      {
         // Cluster reco jets from PF candidates.  No subtraction at the moment
         vector<PseudoJet> Particles;
         for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
         {
            FourVector P;
            P.SetPtEtaPhi(MPF.PT->at(iPF), MPF.Eta->at(iPF), MPF.Phi->at(iPF));
            P[0] = MPF.E->at(iPF);

            Particles.emplace_back(PseudoJet(P[1], P[2], P[3], P[0]));
         }

         JetDefinition Definition(antikt_algorithm, JetR);
         ClusterSequence Sequence(Particles, Definition);
         vector<PseudoJet> FastJets = Sequence.inclusive_jets(0.5);   // anti-kt, R = 0.4

         for(int iR = 0; iR < FastJets.size(); iR++)
         {
            if(FastJets[iR].eta() < EtaMin || FastJets[iR].eta() > EtaMax)
               continue;
            
            PseudoJet &J = FastJets[iR];
            FourVector P(J.e(), J.px(), J.py(), J.pz());
            
            JEC.SetJetPT(P.GetPT());
            JEC.SetJetEta(P.GetEta());
            JEC.SetJetPhi(P.GetPhi());

            if(P.GetPT() < PTMin && P.GetPT() * JEC.GetCorrection() < PTMin)
               continue;
            
            P = P * JEC.GetCorrection();
            
            RecoJets.push_back(pair<FourVector, PseudoJet>(P, J));
            RecoJetJEC.push_back(JEC.GetCorrection());
         }
      }

      // Export gen jet
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
      RecoJetJEU.resize(NRecoJets);
      for(int iR = 0; iR < NRecoJets; iR++)
      {
         RecoJetPT[iR]   = RecoJets[iR].first.GetPT();
         RecoJetEta[iR]  = RecoJets[iR].first.GetEta();
         RecoJetPhi[iR]  = RecoJets[iR].first.GetPhi();
         RecoJetMass[iR] = RecoJets[iR].first.GetMass();
         
         JEU.SetJetPT(RecoJetPT[iR]);
         JEU.SetJetEta(RecoJetEta[iR]);
         JEU.SetJetPhi(RecoJetPhi[iR]);
         RecoJetJEU[iR]  = JEU.GetUncertainty().first;
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

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputFile.cd();
   OutputTree.Write();
   OutputFile.Close();

   InputFile.Close();

   return 0;
}






