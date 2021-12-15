#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TArrow.h"
#include "TCanvas.h"
#include "TProfile.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "ProgressBar.h"
#include "SetStyle.h"
#include "DataHelper.h"

#include "Messenger.h"
#include "JetCorrector.h"

int main(int argc, char *argv[]);
double GetUE(RhoTreeMessenger &M, double Eta, double R);
void SetHistogram(TH1 &H, int Color);
void AddPlot(PdfFileHelper &PdfFile, TH1 &H, double Min, double Max);

int main(int argc, char *argv[])
{
   vector<int> Colors = GetPrimaryColors();
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string TreeName               = CL.Get("Tree");
   string OutputFileName         = CL.Get("Output");
   vector<string> JECFileNames   = CL.GetStringVector("JEC", vector<string>{""});
   string Trigger                = CL.Get("Trigger");
   double CentralityMin          = CL.GetDouble("CentralityMin", -999);
   double CentralityMax          = CL.GetDouble("CentralityMax", 999);
   double EtaMin                 = CL.GetDouble("EtaMin", -2.0);
   double EtaMax                 = CL.GetDouble("EtaMax", +2.0);
   double MinPT                  = CL.GetDouble("MinPT", 150);
   double JetR                   = CL.GetDouble("JetR", 0.4);
   bool DoBaselineCutPP          = CL.GetBool("DoBaselineCutPP", false);
   bool DoBaselineCutAA          = CL.GetBool("DoBaselineCutAA", false);
   double Fraction               = CL.GetDouble("Fraction", 1.00);

   string DHFileName             = CL.Get("DHFile");
   string DHState                = CL.Get("State");
   string DHKeyBase              = CL.Get("KeyBase");

   DataHelper DHFile(DHFileName);

   double CHFMin = DHFile[DHState][DHKeyBase+"_CHFMinCut"].GetDouble();
   double CHFMax = DHFile[DHState][DHKeyBase+"_CHFMaxCut"].GetDouble();
   double CEFMin = DHFile[DHState][DHKeyBase+"_CEFMinCut"].GetDouble();
   double CEFMax = DHFile[DHState][DHKeyBase+"_CEFMaxCut"].GetDouble();
   double NHFMin = DHFile[DHState][DHKeyBase+"_NHFMinCut"].GetDouble();
   double NHFMax = DHFile[DHState][DHKeyBase+"_NHFMaxCut"].GetDouble();
   double NEFMin = DHFile[DHState][DHKeyBase+"_NEFMinCut"].GetDouble();
   double NEFMax = DHFile[DHState][DHKeyBase+"_NEFMaxCut"].GetDouble();
   double MUFMin = DHFile[DHState][DHKeyBase+"_MUFMinCut"].GetDouble();
   double MUFMax = DHFile[DHState][DHKeyBase+"_MUFMaxCut"].GetDouble();
   int MultiplicityMin = DHFile[DHState][DHKeyBase+"_MultiplicityMinCut"].GetInteger();
   int MultiplicityMax = DHFile[DHState][DHKeyBase+"_MultiplicityMaxCut"].GetInteger();
   int ChargedMultiplicityMin = DHFile[DHState][DHKeyBase+"_ChargedMultiplicityMinCut"].GetInteger();
   int ChargedMultiplicityMax = DHFile[DHState][DHKeyBase+"_ChargedMultiplicityMaxCut"].GetInteger();

   JetCorrector JEC(JECFileNames);

   TH1D HJetPFCHF("HJetPFCHF", "Charged Hadron Fraction;PF CHF;", 100, 0, 1);
   TH1D HJetPFCEF("HJetPFCEF", "Charged EM Fraction;PF CEF;", 100, 0, 1);
   TH1D HJetPFNHF("HJetPFNHF", "Neutral Hadron Fraction;PF NHF;", 100, 0, 1);
   TH1D HJetPFNEF("HJetPFNEF", "Neutral EM Fraction;PF NEF;", 100, 0, 1);
   TH1D HJetPFMUF("HJetPFMUF", "Muon Fraction;PF MuF;", 100, 0, 1);
   TH1D HJetPFCM("HJetPFCM", "Charged Multiplicity;PF Charged Multiplicity;", 30, 0, 30);
   TH1D HJetPFM("HJetPFM", "Multiplicity;PF Multiplicity;", 30, 0, 30);
   TH1D HPassPFCHF("HPassPFCHF", "Charged Hadron Fraction;PF CHF;", 100, 0, 1);
   TH1D HPassPFCEF("HPassPFCEF", "Charged EM Fraction;PF CEF;", 100, 0, 1);
   TH1D HPassPFNHF("HPassPFNHF", "Neutral Hadron Fraction;PF NHF;", 100, 0, 1);
   TH1D HPassPFNEF("HPassPFNEF", "Neutral EM Fraction;PF NEF;", 100, 0, 1);
   TH1D HPassPFMUF("HPassPFMUF", "Muon Fraction;PF MuF;", 100, 0, 1);
   TH1D HPassPFCM("HPassPFCM", "Charged Multiplicity;PF Charged Multiplicity;", 30, 0, 30);
   TH1D HPassPFM("HPassPFM", "Multiplicity;PF Multiplicity;", 30, 0, 30);

   int NBin = 40;
   double MaxPT = 1000;
   double Bins[101];
   for(int i = 0; i <= NBin; i++)
      Bins[i] = MinPT * exp((log(MaxPT) - log(MinPT)) / NBin * i);
   TProfile PSurvival("PSurvival", ";Jet PT;%", NBin, Bins);
   
   SetHistogram(HJetPFCHF, Colors[0]);
   SetHistogram(HJetPFCEF, Colors[1]);
   SetHistogram(HJetPFNHF, Colors[2]);
   SetHistogram(HJetPFNEF, Colors[3]);
   SetHistogram(HJetPFMUF, Colors[4]);
   SetHistogram(HJetPFCM, Colors[5]);
   SetHistogram(HJetPFM, Colors[6]);
   SetHistogram(HPassPFCHF, Colors[0]);
   SetHistogram(HPassPFCEF, Colors[1]);
   SetHistogram(HPassPFNHF, Colors[2]);
   SetHistogram(HPassPFNEF, Colors[3]);
   SetHistogram(HPassPFMUF, Colors[4]);
   SetHistogram(HPassPFCM, Colors[5]);
   SetHistogram(HPassPFM, Colors[6]);

   SetHistogram(PSurvival, Colors[7]);

   for(string FileName : InputFileNames)
   {
      TFile File(FileName.c_str());

      HiEventTreeMessenger MEvent(File);
      SkimTreeMessenger MSkim(File);
      JetTreeMessenger MJet(File, TreeName);
      TriggerTreeMessenger MTrigger(File, "hltanalysis/HltTree");
      RhoTreeMessenger MRho(File, "hiPuRhoAnalyzer/t");

      if(MEvent.Tree == nullptr)
      {
         File.Close();
         continue;
      }

      int EntryCount = MEvent.Tree->GetEntries();
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         if(EntryCount < 300 || (iE % (EntryCount / 250) == 0))
         {
            Bar.Update(iE);
            Bar.Print();
         }

         MEvent.GetEntry(iE);
         MSkim.GetEntry(iE);
         MJet.GetEntry(iE);
         MTrigger.GetEntry(iE);
         MRho.GetEntry(iE);

         double Centrality = MEvent.hiBin * 0.005;
         if(Centrality < CentralityMin)
            continue;
         if(Centrality > CentralityMax)
            continue;

         if(Trigger != "none" && MTrigger.CheckTriggerStartWith(Trigger) <= 0)
            continue;

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

         for(int iJ = 0; iJ < MJet.JetCount; iJ++)
         {
            if(MJet.JetEta[iJ] < EtaMin)   continue;
            if(MJet.JetEta[iJ] > EtaMax)   continue;

            double UE = GetUE(MRho, MJet.JetEta[iJ], JetR);

            JEC.SetJetPT(MJet.JetRawPT[iJ]);
            JEC.SetJetEta(MJet.JetEta[iJ]);
            JEC.SetJetPhi(MJet.JetPhi[iJ]);
            JEC.SetRho(UE / (JetR * JetR * M_PI));
            MJet.JetPT[iJ] = JEC.GetCorrectedPT();

            if(MJet.JetPT[iJ] < MinPT)
               continue;

            int CM = MJet.JetPFCHM[iJ] + MJet.JetPFCEM[iJ];
            int M = CM + MJet.JetPFNHM[iJ] + MJet.JetPFNEM[iJ];

            HJetPFCHF.Fill(MJet.JetPFCHF[iJ]);
            HJetPFCEF.Fill(MJet.JetPFCEF[iJ]);
            HJetPFNHF.Fill(MJet.JetPFNHF[iJ]);
            HJetPFNEF.Fill(MJet.JetPFNEF[iJ]);
            HJetPFMUF.Fill(MJet.JetPFMUF[iJ]);
            HJetPFCM.Fill(CM);
            HJetPFM.Fill(M);

            bool PassID = true;
            if(MJet.JetPFCHF[iJ] <= CHFMin)    PassID = false;
            if(MJet.JetPFCHF[iJ] >= CHFMax)    PassID = false;
            if(MJet.JetPFCEF[iJ] <= CEFMin)    PassID = false;
            if(MJet.JetPFCEF[iJ] >= CEFMax)    PassID = false;
            if(MJet.JetPFNHF[iJ] <= NHFMin)    PassID = false;
            if(MJet.JetPFNHF[iJ] >= NHFMax)    PassID = false;
            if(MJet.JetPFNEF[iJ] <= NEFMin)    PassID = false;
            if(MJet.JetPFNEF[iJ] >= NEFMax)    PassID = false;
            if(MJet.JetPFMUF[iJ] <= MUFMin)    PassID = false;
            if(MJet.JetPFMUF[iJ] >= MUFMax)    PassID = false;
            if(CM <= ChargedMultiplicityMin)   PassID = false;
            if(CM >= ChargedMultiplicityMax)   PassID = false;
            if(M <= MultiplicityMin)           PassID = false;
            if(M >= MultiplicityMax)           PassID = false;

            if(PassID == true)
            {
               HPassPFCHF.Fill(MJet.JetPFCHF[iJ]);
               HPassPFCEF.Fill(MJet.JetPFCEF[iJ]);
               HPassPFNHF.Fill(MJet.JetPFNHF[iJ]);
               HPassPFNEF.Fill(MJet.JetPFNEF[iJ]);
               HPassPFMUF.Fill(MJet.JetPFMUF[iJ]);
               HPassPFCM.Fill(CM);
               HPassPFM.Fill(M);
            }

            PSurvival.Fill(MJet.JetPT[iJ], PassID);
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Jet ID Plots");

   PdfFile.AddTextPage("Pre-cut distributions");
   AddPlot(PdfFile, HJetPFCHF, CHFMin, CHFMax);
   AddPlot(PdfFile, HJetPFCEF, CEFMin, CEFMax);
   AddPlot(PdfFile, HJetPFNHF, NHFMin, NHFMax);
   AddPlot(PdfFile, HJetPFNEF, NEFMin, NEFMax);
   AddPlot(PdfFile, HJetPFMUF, MUFMin, MUFMax);
   AddPlot(PdfFile, HJetPFCM, ChargedMultiplicityMin + 1, ChargedMultiplicityMax - 1);
   AddPlot(PdfFile, HJetPFM, MultiplicityMin + 1, MultiplicityMax - 1);
   
   PdfFile.AddTextPage("Post-cut distributions");
   AddPlot(PdfFile, HPassPFCHF, CHFMin, CHFMax);
   AddPlot(PdfFile, HPassPFCEF, CEFMin, CEFMax);
   AddPlot(PdfFile, HPassPFNHF, NHFMin, NHFMax);
   AddPlot(PdfFile, HPassPFNEF, NEFMin, NEFMax);
   AddPlot(PdfFile, HPassPFMUF, MUFMin, MUFMax);
   AddPlot(PdfFile, HPassPFCM, ChargedMultiplicityMin + 1, ChargedMultiplicityMax - 1);
   AddPlot(PdfFile, HPassPFM, MultiplicityMin + 1, MultiplicityMax - 1);

   PdfFile.AddTextPage("Survival fractions");

   TCanvas Canvas;
   TH2D HWorld("HWorld", ";JetPT;%", 100, MinPT, MaxPT, 100, 0.9, 1.02);
   HWorld.SetStats(0);
   HWorld.Draw("axis");
   PSurvival.Draw("same");
   Canvas.SetLogx();
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);

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

void SetHistogram(TH1 &H, int Color)
{
   H.SetStats(0);
   H.SetLineColor(Color);
   H.SetLineWidth(2);
   H.SetMarkerColor(Color);
   H.SetMarkerStyle(20);
}

void AddPlot(PdfFileHelper &PdfFile, TH1 &H, double Min, double Max)
{
   TCanvas Canvas;

   H.Draw("");

   double RightEdge = H.GetXaxis()->GetBinUpEdge(H.GetNbinsX());
   double LeftEdge = H.GetXaxis()->GetBinLowEdge(1);

   double MinY = H.GetMinimum();
   double MaxY = H.GetMaximum();

   if(MinY == 0)
      MinY = 1;
   double Location = sqrt(MinY * MaxY);

   TArrow Arrow(max(LeftEdge, Min), Location, min(RightEdge, Max), Location, 0.01, "<|>");
   Arrow.SetLineWidth(2);
   Arrow.Draw();

   Canvas.SetLogy(true);

   PdfFile.AddCanvas(Canvas);
}


