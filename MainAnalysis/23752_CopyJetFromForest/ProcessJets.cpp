#include <vector>
#include <iostream>
#include <map>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"
#include "TF1.h"

#include "ProgressBar.h"
#include "CommandLine.h"
#include "CustomAssert.h"
#include "Code/TauHelperFunctions3.h"
#include "DataHelper.h"

#include "Messenger.h"
#include "JetCorrector.h"
#include "JetUncertainty.h"

int main(int argc, char *argv[]);
bool IsExcluded(double Eta, double Phi, vector<double> &Exclusion);
double GetRhoAtCenter(RhoTreeMessenger &M, double Eta);
double GetUE(RhoTreeMessenger &M, double Eta, double R);
double JetPhiWeight(double Eta, vector<double> &JetExclusion);
double GetRhoWeight(DataHelper &DHFile, string &Key, double UE);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input", vector<string>{"SampleExample/HiForestAOD.root"});
   string OutputFileName         = CL.Get("Output", "Output/JetTreeAOD.root");

   string DHFileName             = CL.Get("DHFile", "GlobalSetting.dh");
   string DHKeyBase              = CL.Get("RhoKeyBase", "none");
   // bool CutUE                    = CL.GetBool("CutUE", false);

   double Fraction               = CL.GetDouble("Fraction", 1.00);

   bool DoBaselineCutPP          = CL.GetBool("DoBaselineCutPP", false);
   bool DoBaselineCutAA          = CL.GetBool("DoBaselineCutAA", false);

   string JetName                = CL.Get("Jet", "akFlowPuCs4PFJetAnalyzer/t");
   double JetR                   = CL.GetDouble("JetR", 0.4);
   vector<string> JECFile        = CL.GetStringVector("JEC", vector<string>{"None"});
   string JEUFile                = CL.Get("JEU", "None");
   string Trigger                = CL.Get("Trigger", "NONE");

   string PFName                 = CL.Get("PF", "pfcandAnalyzer/pfTree");

   double EtaMin                 = CL.GetDouble("EtaMin", -2.0);
   double EtaMax                 = CL.GetDouble("EtaMax", +2.0);

   double PTMin                  = CL.GetDouble("PTMin", 0);
   double GenPTMin               = CL.GetDouble("GenPTMin", 0);

   bool CheckCentrality          = CL.GetBool("CheckCentrality", true);
   double CentralityMin          = CL.GetDouble("CentralityMin", 0.00);
   double CentralityMax          = CL.GetDouble("CentralityMax", 1.00);

   bool UseStoredGen             = CL.GetBool("UseStoredGen", false);
   bool UseStoredReco            = CL.GetBool("UseStoredReco", true);
   bool DoRecoSubtraction        = UseStoredReco ? CL.GetBool("DoRecoSubtraction") : false;

   Assert(DoRecoSubtraction == false, "reco reclustering in PbPb case not implemented yet");
   
   vector<double> JetExclusion   = CL.GetDoubleVector("Exclusion", vector<double>{});

   Assert(JetExclusion.size() % 4 == 0, "Exclusion zone format: (eta min, eta max, phi min, phi max)");

   DataHelper DHFile(DHFileName);
   GetRhoWeight(DHFile, DHKeyBase, 0);   // Initialize rho weight function

   JetCorrector JEC(JECFile);
   JetUncertainty JEU(JEUFile);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("UnfoldingTree", "Trees for unfolding studies");

   double EventWeight = 1;
   double PTHat = 1;
   int Run;
   int Lumi;
   long long Event;
   double Centrality = 0;
   int NRecoJets = 0;
   vector<float> RecoJetPT;
   vector<float> RecoJetEta;
   vector<float> RecoJetPhi;
   vector<float> RecoJetMass;
   vector<float> RecoJetJEC;
   vector<float> RecoJetJEU;
   vector<float> RecoJetRho;
   vector<float> RecoJetUE;
   vector<float> RecoJetWeight;
   vector<float> RecoJetRhoWeight;
   vector<float> RecoJetPhiWeight;
   int NGenJets = 0;
   vector<float> GenJetPT;
   vector<float> GenJetEta;
   vector<float> GenJetPhi;
   vector<float> GenJetMass;
   vector<float> GenJetWeight;
   vector<float> GenJetPhiWeight;
   vector<float> MatchedJetPT;
   vector<float> MatchedJetEta;
   vector<float> MatchedJetPhi;
   vector<float> MatchedJetMass;
   vector<float> MatchedJetAngle;
   vector<float> MatchedJetJEC;
   vector<float> MatchedJetJEU;
   vector<float> MatchedJetRho;
   vector<float> MatchedJetUE;
   vector<float> MatchedJetWeight;
   vector<float> MatchedJetRhoWeight;
   vector<float> MatchedJetPhiWeight;

   OutputTree.Branch("EventWeight",         &EventWeight,    "EventWeight/D");
   OutputTree.Branch("PTHat",               &PTHat,          "PTHat/D");
   OutputTree.Branch("Run",                 &Run,            "Run/I");
   OutputTree.Branch("Lumi",                &Lumi,           "Lumi/I");
   OutputTree.Branch("Event",               &Event,          "Event/L");
   OutputTree.Branch("Centrality",          &Centrality,     "Centrality/D");
   OutputTree.Branch("NRecoJets",           &NRecoJets,      "NRecoJets/I");
   OutputTree.Branch("RecoJetPT",           &RecoJetPT);
   OutputTree.Branch("RecoJetEta",          &RecoJetEta);
   OutputTree.Branch("RecoJetPhi",          &RecoJetPhi);
   OutputTree.Branch("RecoJetMass",         &RecoJetMass);
   OutputTree.Branch("RecoJetJEC",          &RecoJetJEC);
   OutputTree.Branch("RecoJetJEU",          &RecoJetJEU);
   OutputTree.Branch("RecoJetRho",          &RecoJetRho);
   OutputTree.Branch("RecoJetUE",           &RecoJetUE);
   OutputTree.Branch("RecoJetWeight",       &RecoJetWeight);
   OutputTree.Branch("RecoJetPhiWeight",    &RecoJetPhiWeight);
   OutputTree.Branch("RecoJetRhoWeight",    &RecoJetRhoWeight);
   OutputTree.Branch("NGenJets",            &NGenJets,       "NGenJets/I");
   OutputTree.Branch("GenJetPT",            &GenJetPT);
   OutputTree.Branch("GenJetEta",           &GenJetEta);
   OutputTree.Branch("GenJetPhi",           &GenJetPhi);
   OutputTree.Branch("GenJetMass",          &GenJetMass);
   OutputTree.Branch("GenJetWeight",        &GenJetWeight);
   OutputTree.Branch("GenJetPhiWeight",     &GenJetPhiWeight);
   OutputTree.Branch("MatchedJetPT",        &MatchedJetPT);
   OutputTree.Branch("MatchedJetEta",       &MatchedJetEta);
   OutputTree.Branch("MatchedJetPhi",       &MatchedJetPhi);
   OutputTree.Branch("MatchedJetMass",      &MatchedJetMass);
   OutputTree.Branch("MatchedJetAngle",     &MatchedJetAngle);
   OutputTree.Branch("MatchedJetJEC",       &MatchedJetJEC);
   OutputTree.Branch("MatchedJetJEU",       &MatchedJetJEU);
   OutputTree.Branch("MatchedJetRho",       &MatchedJetRho);
   OutputTree.Branch("MatchedJetUE",        &MatchedJetUE);
   OutputTree.Branch("MatchedJetWeight",    &MatchedJetWeight);
   OutputTree.Branch("MatchedJetPhiWeight", &MatchedJetPhiWeight);
   OutputTree.Branch("MatchedJetRhoWeight", &MatchedJetRhoWeight);

   for(string InputFileName : InputFileNames)
   {
      TFile InputFile(InputFileName.c_str());

      HiEventTreeMessenger MEvent(InputFile);
      GenParticleTreeMessenger MGen(InputFile);
      JetTreeMessenger MJet(InputFile, JetName);
      TriggerTreeMessenger MTrigger(InputFile, "hltanalysis/HltTree");
      PFTreeMessenger MPF(InputFile, PFName);
      SkimTreeMessenger MSkim(InputFile);
      RhoTreeMessenger MRho(InputFile, "hiPuRhoAnalyzer/t");

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
         MSkim.GetEntry(iE);
         MRho.GetEntry(iE);

         Run = MEvent.Run;
         Lumi = MEvent.Lumi;
         Event = MEvent.Event;

         EventWeight = MEvent.weight;
         PTHat = MJet.PTHat;

         if(Trigger != "NONE" && Trigger != "None")
         {
            int Decision = MTrigger.CheckTriggerStartWith(Trigger);

            if(Decision < 0)
               cerr << "Warning! Trigger not found!" << endl;
            if(Decision == 0)   // trigger found and not fired
               continue;
         }

         Centrality = MEvent.hiBin * 0.005;
         if(CheckCentrality == true)
         {
            if(MEvent.hiBin * 0.005 < CentralityMin)
               continue;
            if(MEvent.hiBin * 0.005 > CentralityMax)
               continue;
         }

         if(DoBaselineCutAA == true)
         {
            if(MSkim.HBHENoiseRun2Loose != 1)
               continue;
            if(MSkim.PVFilter != 1)
               continue;
            if(MSkim.ClusterCompatibilityFilter != 1)
               continue;
            if(MSkim.HFCoincidenceFilter2Th4 != 1)
               continue;
         }
         if(DoBaselineCutPP == true)
         {
            if(MSkim.HBHENoiseRun2Loose != 1)
               continue;
            if(MSkim.PVFilter != 1)
               continue;
            if(MSkim.BeamScrapingFilter != 1)
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
               if(MJet.GenPT[iG] < GenPTMin)
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
                  if(GenFastJets[iG].perp() < GenPTMin)
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
            
               double AverageRho = GetUE(MRho, MJet.JetEta[iR], JetR) / (JetR * JetR * M_PI);

               JEC.SetJetPT(MJet.JetRawPT[iR]);
               JEC.SetJetEta(MJet.JetEta[iR]);
               JEC.SetJetPhi(MJet.JetPhi[iR]);
               JEC.SetRho(AverageRho);
               if(JEC.GetCorrection() > 0)
                  MJet.JetPT[iR] = JEC.GetCorrectedPT();

               if(MJet.JetPT[iR] < PTMin && MJet.JetRawPT[iR] < PTMin)
                  continue;
               if(IsExcluded(MJet.JetEta[iR], MJet.JetPhi[iR], JetExclusion) == true)
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

               double AverageRho = GetUE(MRho, P.GetEta(), JetR) / (JetR * JetR * M_PI);
               
               JEC.SetJetPT(P.GetPT());
               JEC.SetJetEta(P.GetEta());
               JEC.SetJetPhi(P.GetPhi());
               JEC.SetRho(AverageRho);

               if(P.GetPT() < PTMin && P.GetPT() * JEC.GetCorrection() < PTMin)
                  continue;
               if(IsExcluded(P.GetEta(), P.GetPhi(), JetExclusion) == true)
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
         GenJetWeight.resize(NGenJets);
         GenJetPhiWeight.resize(NGenJets);
         for(int iG = 0; iG < NGenJets; iG++)
         {
            GenJetPT[iG]        = GenJets[iG].first.GetPT();
            GenJetEta[iG]       = GenJets[iG].first.GetEta();
            GenJetPhi[iG]       = GenJets[iG].first.GetPhi();
            GenJetMass[iG]      = GenJets[iG].first.GetMass();
            
            GenJetPhiWeight[iG] = JetPhiWeight(GenJetEta[iG], JetExclusion);
            GenJetWeight[iG]    = GenJetPhiWeight[iG];
         }

         // Export reco jets
         NRecoJets = RecoJets.size();
         RecoJetPT.resize(NRecoJets);
         RecoJetEta.resize(NRecoJets);
         RecoJetPhi.resize(NRecoJets);
         RecoJetMass.resize(NRecoJets);
         RecoJetJEU.resize(NRecoJets);
         RecoJetRho.resize(NRecoJets);
         RecoJetUE.resize(NRecoJets);
         RecoJetWeight.resize(NRecoJets);
         RecoJetPhiWeight.resize(NRecoJets);
         RecoJetRhoWeight.resize(NRecoJets);
         for(int iR = 0; iR < NRecoJets; iR++)
         {
            RecoJetPT[iR]        = RecoJets[iR].first.GetPT();
            RecoJetEta[iR]       = RecoJets[iR].first.GetEta();
            RecoJetPhi[iR]       = RecoJets[iR].first.GetPhi();
            RecoJetMass[iR]      = RecoJets[iR].first.GetMass();

            JEU.SetJetPT(RecoJetPT[iR]);
            JEU.SetJetEta(RecoJetEta[iR]);
            JEU.SetJetPhi(RecoJetPhi[iR]);
            RecoJetJEU[iR]       = JEU.GetUncertainty().first;

            RecoJetRho[iR]       = GetRhoAtCenter(MRho, RecoJetEta[iR]);
            RecoJetUE[iR]        = GetUE(MRho, RecoJetEta[iR], JetR);

            RecoJetPhiWeight[iR] = JetPhiWeight(RecoJetEta[iR], JetExclusion);
            RecoJetRhoWeight[iR] = GetRhoWeight(DHFile, DHKeyBase, RecoJetUE[iR]);
            RecoJetWeight[iR]    = RecoJetPhiWeight[iR] * RecoJetRhoWeight[iR];
         }

         // For each gen jet, find the best reco jet
         MatchedJetPT.resize(NGenJets);
         MatchedJetEta.resize(NGenJets);
         MatchedJetPhi.resize(NGenJets);
         MatchedJetMass.resize(NGenJets);
         MatchedJetAngle.resize(NGenJets);
         MatchedJetJEC.resize(NGenJets);
         MatchedJetJEU.resize(NGenJets);
         MatchedJetRho.resize(NGenJets);
         MatchedJetUE.resize(NGenJets);
         MatchedJetWeight.resize(NGenJets);
         MatchedJetPhiWeight.resize(NGenJets);
         MatchedJetRhoWeight.resize(NGenJets);
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

            MatchedJetPT[iG]        = RecoJets[BestIndex].first.GetPT();
            MatchedJetEta[iG]       = RecoJets[BestIndex].first.GetEta();
            MatchedJetPhi[iG]       = RecoJets[BestIndex].first.GetPhi();
            MatchedJetMass[iG]      = RecoJets[BestIndex].first.GetMass();
            MatchedJetJEC[iG]       = RecoJetJEC[BestIndex];
            MatchedJetJEU[iG]       = RecoJetJEU[BestIndex];
            MatchedJetRho[iG]       = RecoJetRho[BestIndex];
            MatchedJetUE[iG]        = RecoJetUE[BestIndex];
            MatchedJetAngle[iG]     = BestAngle;
            MatchedJetPhiWeight[iG] = RecoJetPhiWeight[BestIndex];
            MatchedJetRhoWeight[iG] = RecoJetRhoWeight[BestIndex];
            MatchedJetWeight[iG]    = RecoJetWeight[BestIndex];
         }

         OutputTree.Fill();
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   OutputFile.cd();
   OutputTree.Write();
   OutputFile.Close();

   return 0;
}

bool IsExcluded(double Eta, double Phi, vector<double> &Exclusion)
{
   // true = excluded
   if(Exclusion.size() == 0)
      return false;

   for(int i = 0; i + 4 <= (int)Exclusion.size(); i = i + 4)
   {
      if(Eta > Exclusion[i+0] && Eta < Exclusion[i+1])   // eta in range, check phi
      {
         if(Phi > Exclusion[i+2] && Phi < Exclusion[i+3])   // phi also in range, kill
            return true;
         if(Phi + 2 * M_PI > Exclusion[i+2] && Phi + 2 * M_PI < Exclusion[i+3])   // shift phi for wrapping
            return true;
         if(Phi - 2 * M_PI > Exclusion[i+2] && Phi - 2 * M_PI < Exclusion[i+3])   // shift phi for wrapping
            return true;
      }
   }

   return false;
}

double GetRhoAtCenter(RhoTreeMessenger &M, double Eta)
{
   double Result = 0;

   if(M.EtaMin == nullptr)
      return -1;

   int NBin = M.EtaMin->size();
   if(NBin == 0)
      return -1;

   for(int i = 0; i < NBin; i++)
   {
      if(M.EtaMin->at(i) <= Eta && M.EtaMax->at(i) >= Eta)
      {
         Result = M.Rho->at(i);
         break;
      }
   }

   return Result;
}

double GetUE(RhoTreeMessenger &M, double Eta, double R)
{
   double Result = 0;

   if(M.EtaMin == nullptr)
      return -1;

   int NBin = M.EtaMin->size();
   if(NBin == 0)
      return -1;

   for(int i = 0; i < NBin; i++)
   {
      if(M.EtaMax->at(i) < Eta - R)
         continue;
      if(M.EtaMin->at(i) > Eta + R)
         continue;

      double XMin = (max(M.EtaMin->at(i), Eta - R) - Eta) / R;
      double XMax = (min(M.EtaMax->at(i), Eta + R) - Eta) / R;

      if(XMin <= -1)
         XMin = -0.99999;
      if(XMax >= +1)
         XMax = +0.99999;

      double High = XMax * sqrt(1 - XMax * XMax) + asin(XMax);
      double Low = XMin * sqrt(1 - XMin * XMin) + asin(XMin);

      Result = Result + R * R * (High - Low) * M.Rho->at(i);
   }

   return Result;
}

double JetPhiWeight(double Eta, vector<double> &JetExclusion)
{
   vector<pair<double, double>> PhiRanges;

   for(int i = 0; i + 4 <= (int)JetExclusion.size(); i = i + 4)
   {
      if(Eta < JetExclusion[i] || Eta > JetExclusion[i+1])
         continue;

      double PhiMin = JetExclusion[i+2];
      double PhiMax = JetExclusion[i+3];
      if(PhiMax < PhiMin)   // goes over the +-pi boundary
         PhiMax = PhiMax + 2 * M_PI;

      PhiRanges.push_back(pair<double, double>(PhiMin, PhiMax));
   }

   bool Change = true;
   while(Change == true)
   {
      Change = false;

      int N = PhiRanges.size();
      for(int i = 0; i < N && Change == false; i++)
      {
         for(int j = i + 1; j < N && Change == false; j++)
         {
            double Min1 = PhiRanges[i].first;
            double Max1 = PhiRanges[i].second;
            double Min2 = PhiRanges[j].first;
            double Max2 = PhiRanges[j].second;
            // The criteria for intersection is one of the end points is enclosed by the other range
            // This checks the case where shifting by 2pi is not needed
            if((Min1 > Min2 && Min1 < Max2) || (Max1 > Min2 && Max1 < Max2)
                  || (Min2 > Min1 && Min2 < Max1) || (Max2 > Min1 && Max2 < Max1))
            {
               Change = true;
               PhiRanges[i].first = min(Min1, Min2);
               PhiRanges[i].second = min(Max1, Max2);
               PhiRanges.erase(PhiRanges.begin() + j);
               break;
            }

            // Shift the lower one up by 2 * pi, since the lower bound is always within [-pi, +pi]
            // So this is sufficient and we don't need further cases
            if(Min1 < Min2) { Min1 = Min1 + 2 * M_PI; Max1 = Max1 + 2 * M_PI; }
            else            { Min2 = Min2 + 2 * M_PI; Max2 = Max2 + 2 * M_PI; }

            // Again checking if any endpoints are inside other ranges
            if((Min1 > Min2 && Min1 < Max2) || (Max1 > Min2 && Max1 < Max2)
                  || (Min2 > Min1 && Min2 < Max1) || (Max2 > Min1 && Max2 < Max1))
            {
               Change = true;
               PhiRanges[i].first = min(Min1, Min2);
               PhiRanges[i].second = min(Max1, Max2);
               PhiRanges.erase(PhiRanges.begin() + j);
               break;
            }
         }
      }
   }

   double ExcludedPhi = 0;
   for(pair<double, double> R : PhiRanges)
      ExcludedPhi = ExcludedPhi + (R.second - R.first);
   if(ExcludedPhi > 2 * M_PI)   // all excluded
      return 0;

   return (2 * M_PI) / (2 * M_PI - ExcludedPhi);
}

double GetRhoWeight(DataHelper &DHFile, string &Key, double UE)
{
   static bool First = true;
   static bool NoWeight = false;

   if(First == true)
   {
      if(DHFile["RhoWeight"].Exist(Key+"_Formula") == false)
         NoWeight = true;
   }
   if(NoWeight == true)
      return 1;

   static TF1 Function("Function", DHFile["RhoWeight"][Key+"_Formula"].GetString().c_str(), 0, 1500);

   if(First == true)
   {
      cout << "Rho weighting formula = " << DHFile["RhoWeight"][Key+"_Formula"].GetString() << endl;

      int N = DHFile["RhoWeight"][Key+"_NPar"].GetInteger();

      First = false;
      for(int i = 0; i < N; i++)
         Function.SetParameter(i, DHFile["RhoWeight"][Key+"_P"+to_string(i)].GetDouble());

      Function.Print("v");
   }
   
   if(UE > DHFile["RhoWeight"][Key+"_MaxUE"].GetDouble())
      return 0;

   return Function.Eval(UE);
}



