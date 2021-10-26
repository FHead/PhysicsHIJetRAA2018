#include <iostream>
using namespace std;

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

   JetCorrector JEC(JECFile);

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage("Trigger plot");

   TFile OutputFile((OutputBase + ".root").c_str(), "RECREATE");

   TH1D HAll("HAll", ";Jet p_{T};", 150, 0, 300);
   TH1D HTrigger("HTrigger", ";Jet p_{T};", 150, 0, 300);

   for(string FileName : InputFiles)
   {
      TFile File(FileName.c_str());

      HiEventTreeMessenger MEvent(File);
      JetTreeMessenger MJet(File, JetName);
      TriggerTreeMessenger MTrigger(File, "hltanalysis/HltTree");
      SkimTreeMessenger MSkim(File);

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

         int LeadingJetIndex = 0;
         for(int iJ = 0; iJ < MJet.JetCount; iJ++)
         {
            JEC.SetJetPT(MJet.JetRawPT[iJ]);
            JEC.SetJetEta(MJet.JetEta[iJ]);
            JEC.SetJetPhi(MJet.JetPhi[iJ]);
            MJet.JetPT[iJ] = JEC.GetCorrectedPT();

            if(MJet.JetPT[iJ] > MJet.JetPT[LeadingJetIndex])
               LeadingJetIndex = iJ;
         }

         FourVector P;
         P.SetPtEtaPhi(MJet.JetPT[LeadingJetIndex], MJet.JetEta[LeadingJetIndex], MJet.JetPhi[LeadingJetIndex]);

         if(P.GetEta() < EtaMin || P.GetEta() > EtaMax)
            continue;

         HAll.Fill(P.GetPT());
         if(Decision > 0)
            HTrigger.Fill(P.GetPT());
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




