#include <iostream>
using namespace std;

#include "TF1.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "DataHelper.h"

#include "Messenger.h"

int main(int argc, char *argv[]);
TGraph FindCorrection(string DataFileName, string MCFileName, double JetPTMin);

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string DataFileName = CL.Get("Data");
   string MCFileName   = CL.Get("MC");
   string DHFileName   = CL.Get("DHFile", "GlobalSetting.dh");

   PdfFileHelper PdfFile("Output.pdf");
   PdfFile.AddTextPage("Centrality weighting");

   vector<double> PTMins{-1, 100, 120, 140, 200};

   TH2D HWorld("HWorld", ";Centrality;Weight", 100, 0, 1, 100, 0.01, 10);
   HWorld.SetStats(0);

   TCanvas Canvas;
   HWorld.Draw("axis");
 
   vector<TGraph> Gs;

   for(double PTMin: PTMins)
   {
      TGraph G = FindCorrection(DataFileName, MCFileName, PTMin);
      G.SetTitle(Form("JetPT > %f", PTMin));
      G.SetMarkerStyle(20);
      Gs.push_back(G);
   }
   
   for(int i = 0; i < (int)Gs.size(); i++)
   {
      Gs[i].SetMarkerColor(Colors[i]);
      Gs[i].SetLineColor(Colors[i]);
      Gs[i].Draw("pl");
   }

   Canvas.SetLogy();

   PdfFile.AddCanvas(Canvas);

   TF1 F("Function", "[0]*exp([1]*x+[2]*x*x)", 0, 0.9);

   Gs[0].Fit(&F, "", "", 0, 0.9);

   PdfFile.AddPlot(Gs[0], "apl", true);

   DataHelper DHFile(DHFileName);
   DHFile["CentralityReweight"]["Formula"] = "[0]*exp([1]*x+[2]*x*x)";
   DHFile["CentralityReweight"]["P0"]      = F.GetParameter(0);
   DHFile["CentralityReweight"]["P1"]      = F.GetParameter(1);
   DHFile["CentralityReweight"]["P2"]      = F.GetParameter(2);
   DHFile["CentralityReweight"]["P0Error"] = F.GetParError(0);
   DHFile["CentralityReweight"]["P1Error"] = F.GetParError(1);
   DHFile["CentralityReweight"]["P2Error"] = F.GetParError(2);
   DHFile.SaveToFile();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

TGraph FindCorrection(string DataFileName, string MCFileName, double JetPTMin)
{
   int N = 50;

   TH1D HMC("HMC", "", N, 0, 1);
   TH1D HData("HData", "", N, 0, 1);

   TFile FMC(MCFileName.c_str());

   HiEventTreeMessenger MMCEvent(FMC);
   JetTreeMessenger     MMCJet(FMC, "akCs4PFJetAnalyzer/t");

   int MCEntryCount = MMCEvent.Tree->GetEntries();
   for(int iE = 0; iE < MCEntryCount; iE++)
   {
      MMCEvent.GetEntry(iE);
      MMCJet.GetEntry(iE);

      bool HasJet = false;
      for(int iJ = 0; iJ < MMCJet.JetCount; iJ++)
      {
         if(MMCJet.JetEta[iJ] < -2 || MMCJet.JetEta[iJ] > 2)
            continue;
         if(MMCJet.JetPT[iJ] < JetPTMin)
            continue;
         HasJet = true;
      }

      if(HasJet == false)
         continue;

      HMC.Fill(MMCEvent.hiBin * 0.005);
   }

   FMC.Close();

   TFile FData(DataFileName.c_str());

   HiEventTreeMessenger MDataEvent(FData);
   JetTreeMessenger     MDataJet(FData, "akCs4PFJetAnalyzer/t");
   TriggerTreeMessenger MDataTrigger(FData, "hltanalysis/HltTree");

   int DataEntryCount = MDataEvent.Tree->GetEntries();
   for(int iE = 0; iE < DataEntryCount; iE++)
   {
      MDataEvent.GetEntry(iE);
      MDataJet.GetEntry(iE);
      MDataTrigger.GetEntry(iE);

      int Decision = MDataTrigger.CheckTriggerStartWith("HLT_HIPuAK4CaloJet100Eta5p1");
      if(Decision == 0)
         continue;

      bool HasJet = false;
      for(int iJ = 0; iJ < MDataJet.JetCount; iJ++)
      {
         if(MDataJet.JetEta[iJ] < -2 || MDataJet.JetEta[iJ] > 2)
            continue;
         if(MDataJet.JetPT[iJ] < JetPTMin)
            continue;
         HasJet = true;
      }

      if(HasJet == false)
         continue;

      HData.Fill(MDataEvent.hiBin * 0.005);
   }

   FData.Close();

   HMC.Scale(1.0 / HMC.Integral());
   HData.Scale(1.0 / HData.Integral());

   cout << HMC.Integral() << " " << HData.Integral() << endl;

   TGraph G;

   for(int i = 1; i <= N; i++)
   {
      double VMC = HMC.GetBinContent(i);
      double VData = HData.GetBinContent(i);

      cout << (i - 0.5) / N << " " << VData << " " << VMC << endl;

      if(VMC > 0)
         G.SetPoint(i - 1, (i - 0.5) / N, VData / VMC);
      else
         G.SetPoint(i - 1, (i - 0.5) / N, 0);
   }

   return G;
}


