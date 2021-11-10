#include <iostream>
using namespace std;

#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"
#include "Math/ProbFuncMathCore.h"

#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

#include "JetProducer.h"
#include "RhoCalculator.h"
#include "Messenger.h"

int main(int argc, char *argv[]);
vector<FourVector> ClusterGenJets(GenParticleTreeMessenger &MGen, double R, double MinPT);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   
   string InputFileName = CL.Get("input");
   double MinPT = CL.GetDouble("MinPT", 3);
   double R = CL.GetDouble("R", 0.40);
   double JetMinPT = CL.GetDouble("JetMinPT", 0);
   double CSR = CL.GetDouble("CSR", -1.0);
   double CSAlpha = CL.GetDouble("CSAlpha", 2.0);
   double MinProbability = CL.GetDouble("MinProbability", 0);
   double MaxProbability = CL.GetDouble("MaxProbability", 0);

   TFile File(InputFileName.c_str());

   HiEventTreeMessenger     MHiEvent(File);
   PFTreeMessenger          MPF(File, "particleFlowAnalyser/pftree");
   RhoTreeMessenger         MRho(File, "hiPuRhoAnalyzer/t");
   JetTreeMessenger         MJet(File, "akCs3PFJetAnalyzer/t");

   if(MHiEvent.Tree == nullptr)
      return -1;

   JetProducer Producer;
   Producer.SetJetR(R);
   Producer.SetMinJetPT(JetMinPT);
   Producer.SetCSR(CSR);
   Producer.SetCSAlpha(CSAlpha);
   Producer.SetMinProbability(MinProbability);
   Producer.SetMaxProbability(MaxProbability);
   Producer.SetPassThrough(false);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MHiEvent.GetEntry(iE);
      MPF.GetEntry(iE);
      MRho.GetEntry(iE);
      MJet.GetEntry(iE);

      vector<FourVector> PF;
      vector<FourVector> PFID1;
      for(int iPF = 0; iPF < (int)MPF.ID->size(); iPF++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
         P[0] = (*MPF.E)[iPF];

         PF.emplace_back(P);
         if((*MPF.ID)[iPF] == 1)
            PFID1.emplace_back(P);
      }

      cout << "Event #" << iE << endl;

      Producer.GetRhoCalculator().SetRhoVector(*(MRho.Rho));
      vector<FourVector> Jets = Producer.ClusterJets(PF, PFID1, false);
      vector<FourVector> Jets2 = Producer.ClusterJets(PF, PFID1, true);
      
      cout << "Jet Redo Rho" << endl;
      for(int iJ = 0; iJ < (int)Jets2.size(); iJ++)
         if(Jets2[iJ].GetPT() > 20)
            cout << " " << Jets2[iJ].GetPT() << " " << Jets2[iJ].GetEta() << " " << Jets2[iJ].GetPhi() << endl;
      cout << endl;

      cout << "Jet using ForestRho" << endl;
      for(int iJ = 0; iJ < (int)Jets.size(); iJ++)
         if(Jets[iJ].GetPT() > 20)
            cout << " " << Jets[iJ].GetPT() << " " << Jets[iJ].GetEta() << " " << Jets[iJ].GetPhi() << endl;
      cout << endl;
      
      cout << "Jet from Forest" << endl;
      for(int iJ = 0; iJ < MJet.JetCount; iJ++)
         if(MJet.JetRawPT[iJ] > 20)
            cout << " " << MJet.JetRawPT[iJ] << " " << MJet.JetEta[iJ] << " " << MJet.JetPhi[iJ] << endl;
      cout << endl;
   }

   File.Close();

   return 0;
}

vector<FourVector> ClusterGenJets(GenParticleTreeMessenger &MGen, double R, double MinPT)
{
   vector<PseudoJet> GenParticles;
   int NGen = MGen.ID->size();
   for(int i = 0; i < NGen; i++)
   {
      // if((*MGen.ID)[i] == 12 || (*MGen.ID)[i] == -12)   continue;
      // if((*MGen.ID)[i] == 14 || (*MGen.ID)[i] == -14)   continue;
      // if((*MGen.ID)[i] == 16 || (*MGen.ID)[i] == -16)   continue;
      if((*MGen.DaughterCount)[i] > 0)                  continue;
      if((*MGen.SubEvent)[i] != 0)                      continue;

      FourVector P;
      P.SetPtEtaPhiMass((*MGen.PT)[i], (*MGen.Eta)[i], (*MGen.Phi)[i], 0);
      GenParticles.emplace_back(P[1], P[2], P[3], P[0]);
   }
   JetDefinition Definition(antikt_algorithm, R);
   ClusterSequence GenSequence(GenParticles, Definition);
   vector<PseudoJet> GenJets = sorted_by_pt(GenSequence.inclusive_jets(MinPT));

   vector<FourVector> Jets;
   for(int iJ = 0; iJ < GenJets.size(); iJ++)
   {
      FourVector P;
      P.SetPtEtaPhiMass(GenJets[iJ].perp(), GenJets[iJ].eta(), GenJets[iJ].phi(), GenJets[iJ].m());
      Jets.emplace_back(P);
   }

   return Jets;
}


