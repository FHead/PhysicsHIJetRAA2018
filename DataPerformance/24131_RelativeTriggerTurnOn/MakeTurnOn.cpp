#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "Code/TauHelperFunctions3.h"
#include "ProgressBar.h"
#include "SetStyle.h"

#include "Messenger.h"
#include "JetCorrector.h"

int main(int argc, char *argv[]);
double GetUE(RhoTreeMessenger &M, double Eta, double R);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFiles = CL.GetStringVector("Input");
   string OutputBase         = CL.Get("OutputBase", "Result");

   string BaseTrigger        = CL.Get("Base");
   string Trigger            = CL.Get("Trigger");
   string JetName            = CL.Get("Jet");
   vector<string> JECFile    = CL.GetStringVector("JEC");
   double CentralityMin      = CL.GetDouble("CentralityMin", 0.00);
   double CentralityMax      = CL.GetDouble("CentralityMax", 0.90);
   double EtaMin             = CL.GetDouble("EtaMin", -2.0);
   double EtaMax             = CL.GetDouble("EtaMax", +2.0);
   bool DoBaselineCutPP      = CL.GetBool("DoBaselineCutPP", false);
   bool DoBaselineCutAA      = CL.GetBool("DoBaselineCutAA", false);
   
   double JetR               = CL.GetDouble("JetR", 0.4);
   bool Recluster            = CL.GetBool("Recluster", false);

   JetCorrector JEC(JECFile);

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage("Trigger plot");

   TFile OutputFile((OutputBase + ".root").c_str(), "RECREATE");

   TH1D HAll("HAll", ";Jet p_{T};", 250, 0, 500);
   TH1D HTrigger("HTrigger", ";Jet p_{T};", 250, 0, 500);

   for(string FileName : InputFiles)
   {
      TFile File(FileName.c_str());

      HiEventTreeMessenger MEvent(File);
      JetTreeMessenger MJet(File, JetName);
      TriggerTreeMessenger MTrigger(File, "hltanalysis/HltTree");
      SkimTreeMessenger MSkim(File);
      PFTreeMessenger MPF(File, "pfcandAnalyzer/pfTree");
      RhoTreeMessenger MRho(File, "hiPuRhoAnalyzer/t");

      int EntryCount = MEvent.Tree->GetEntries();
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(2);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         if(EntryCount < 500 || (iE % (EntryCount / 250)) == 0)
         {
            Bar.Update(iE);
            Bar.Print();
         }

         MEvent.GetEntry(iE);
         MJet.GetEntry(iE);
         MTrigger.GetEntry(iE);
         MSkim.GetEntry(iE);
         if(Recluster == true)
            MPF.GetEntry(iE);
         MRho.GetEntry(iE);

         double Centrality = MEvent.hiBin * 0.005;
         if(Centrality < CentralityMin)
            continue;
         if(Centrality > CentralityMax)
            continue;

         if(MTrigger.CheckTriggerStartWith(BaseTrigger) <= 0)
            continue;
         int Decision = MTrigger.CheckTriggerStartWith(Trigger);

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

         FourVector LeadingJet(0, 0, 0, 0);

         if(Recluster == false)
         {
            int LeadingJetIndex = 0;
            for(int iJ = 0; iJ < MJet.JetCount; iJ++)
            {
               double UE = GetUE(MRho, MJet.JetEta[iJ], JetR);
               
               JEC.SetJetPT(MJet.JetRawPT[iJ]);
               JEC.SetJetEta(MJet.JetEta[iJ]);
               JEC.SetJetPhi(MJet.JetPhi[iJ]);
               JEC.SetRho(UE / (JetR * JetR * M_PI));
               MJet.JetPT[iJ] = JEC.GetCorrectedPT();

               if(MJet.JetPT[iJ] > MJet.JetPT[LeadingJetIndex])
                  LeadingJetIndex = iJ;
            }

            LeadingJet.SetPtEtaPhi(MJet.JetPT[LeadingJetIndex], MJet.JetEta[LeadingJetIndex], MJet.JetPhi[LeadingJetIndex]);
         }
         else
         {
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

               double UE = GetUE(MRho, P.GetEta(), JetR);

               JEC.SetJetPT(P.GetPT());
               JEC.SetJetEta(P.GetEta());
               JEC.SetJetPhi(P.GetPhi());
               JEC.SetRho(UE / (JetR * JetR * M_PI));
               P = P * JEC.GetCorrection();

               if(P.GetPT() > LeadingJet.GetPT())
                  LeadingJet = P;
            }
         }

         if(LeadingJet.GetEta() < EtaMin || LeadingJet.GetEta() > EtaMax)
            continue;

         HAll.Fill(LeadingJet.GetPT());
         if(Decision > 0)
            HTrigger.Fill(LeadingJet.GetPT());
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   PdfFile.AddPlot(HAll);
   PdfFile.AddPlot(HTrigger);

   OutputFile.cd();

   TGraphAsymmErrors G;
   G.Divide(&HTrigger, &HAll);
   PdfFile.AddPlot(G, "ap");

   HTrigger.Write();
   HAll.Write();
   G.Write();

   OutputFile.Close();
   
   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
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



