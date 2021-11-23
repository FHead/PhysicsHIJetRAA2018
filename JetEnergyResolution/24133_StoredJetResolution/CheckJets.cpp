#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"
#include "ProgressBar.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

#include "JetCorrector.h"

int main(int argc, char *argv[]);
bool IsExcluded(double Eta, double Phi, vector<double> &Exclusion);
void PlotProfile1D(PdfFileHelper &PdfFile, TProfile &P);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   double Fraction               = CL.GetDouble("Fraction", 1.000);
   string Output                 = CL.Get("Output", "Result.pdf");
   vector<double> JetExclusion   = CL.GetDoubleVector("Exclusion", vector<double>{});
   bool OnTheFlyJEC              = CL.GetBool("OnTheFlyJEC", false);
   double JetR                   = OnTheFlyJEC ? CL.GetDouble("JetR", 0.4) : 0.4;
   vector<string> JECFile        = OnTheFlyJEC ? CL.GetStringVector("JEC", vector<string>{}) : vector<string>();

   JetCorrector JEC(JECFile);
   
   double JetPTBins[101];
   double JetPTMin = 10;
   double JetPTMax = 1000;
   int JetPTBin = 50;
   for(int i = 0; i <= JetPTBin; i++)
      JetPTBins[i] = exp(log(JetPTMin) + (log(JetPTMax) - log(JetPTMin)) / JetPTBin * i);
   
   double JetPTBins2[101];
   JetPTMin = 200, JetPTMax = 1000;
   for(int i = 0; i <= JetPTBin; i++)
      JetPTBins2[i] = exp(log(JetPTMin) + (log(JetPTMax) - log(JetPTMin)) / JetPTBin * i);

   TProfile2D P1("P1", ";JetPT;JetEta", JetPTBin, JetPTBins, 25, -2, 2);
   TProfile2D P2("P2", "Jet PT > 100;JetPhi;JetEta", 50, -M_PI, M_PI, 25, -2, 2);
   TProfile2D P3("P3", "Jet eta = [0.5, 1.0];JetPT;JetPhi", JetPTBin, JetPTBins, 50, -M_PI, M_PI);
   TProfile2D P4("P4", "Jet eta = [-2.0, -1.5];JetPT;JetPhi", JetPTBin, JetPTBins, 50, -M_PI, M_PI);
   TProfile2D P5("P5", ";JetPT;JetEta", JetPTBin, JetPTBins2, 25, -2, 2);
   TProfile2D P6("P6", "Jet PT > 200;JetPhi;JetEta", 50, -M_PI, M_PI, 25, -2, 2);
   TProfile2D P24("P24", "Jet PT > 50;JetPhi;JetEta", 50, -M_PI, M_PI, 25, -2, 2);

   string Option = "";
   TProfile P7("P7",   "Jet eta = [-2.0, -1.5];JetPT;<R>", JetPTBin, JetPTBins,  Option.c_str());
   TProfile P8("P8",   "Jet eta = [-1.5, -1.0];JetPT;<R>", JetPTBin, JetPTBins,  Option.c_str());
   TProfile P9("P9",   "Jet eta = [-1.0, -0.5];JetPT;<R>", JetPTBin, JetPTBins,  Option.c_str());
   TProfile P10("P10", "Jet eta = [-0.5, 0.0];JetPT;<R>",  JetPTBin, JetPTBins,  Option.c_str());
   TProfile P11("P11", "Jet eta = [0.0, 0.5];JetPT;<R>",   JetPTBin, JetPTBins,  Option.c_str());
   TProfile P12("P12", "Jet eta = [0.5, 1.0];JetPT;<R>",   JetPTBin, JetPTBins,  Option.c_str());
   TProfile P14("P14", "Jet eta = [1.0, 1.5];JetPT;<R>",   JetPTBin, JetPTBins,  Option.c_str());
   TProfile P15("P15", "Jet eta = [1.5, 2.0];JetPT;<R>",   JetPTBin, JetPTBins,  Option.c_str());
   TProfile P16("P16", "Jet eta = [-2.0, -1.5];JetPT;<R>", JetPTBin, JetPTBins2, Option.c_str());
   TProfile P17("P17", "Jet eta = [-1.5, -1.0];JetPT;<R>", JetPTBin, JetPTBins2, Option.c_str());
   TProfile P18("P18", "Jet eta = [-1.0, -0.5];JetPT;<R>", JetPTBin, JetPTBins2, Option.c_str());
   TProfile P19("P19", "Jet eta = [-0.5, 0.0];JetPT;<R>",  JetPTBin, JetPTBins2, Option.c_str());
   TProfile P20("P20", "Jet eta = [0.0, 0.5];JetPT;<R>",   JetPTBin, JetPTBins2, Option.c_str());
   TProfile P21("P21", "Jet eta = [0.5, 1.0];JetPT;<R>",   JetPTBin, JetPTBins2, Option.c_str());
   TProfile P22("P22", "Jet eta = [1.0, 1.5];JetPT;<R>",   JetPTBin, JetPTBins2, Option.c_str());
   TProfile P23("P23", "Jet eta = [1.5, 2.0];JetPT;<R>",   JetPTBin, JetPTBins2, Option.c_str());

   for(string FileName : InputFileNames)
   {
      TFile File(FileName.c_str());

      TTree *Tree = (TTree *)File.Get("UnfoldingTree");
      
      if(Tree == nullptr)
      {
         File.Close();
         continue;
      }

      int NGenJets = 0;
      vector<float> *GenJetPT = nullptr;
      vector<float> *GenJetEta = nullptr;
      vector<float> *GenJetPhi = nullptr;
      vector<float> *MatchedJetPT = nullptr;
      vector<float> *MatchedJetEta = nullptr;
      vector<float> *MatchedJetPhi = nullptr;
      vector<float> *MatchedJetUE = nullptr;
      vector<float> *MatchedJetAngle = nullptr;

      Tree->SetBranchAddress("NGenJets", &NGenJets);
      Tree->SetBranchAddress("GenJetPT", &GenJetPT);
      Tree->SetBranchAddress("GenJetEta", &GenJetEta);
      Tree->SetBranchAddress("GenJetPhi", &GenJetPhi);
      Tree->SetBranchAddress("MatchedJetPT", &MatchedJetPT);
      Tree->SetBranchAddress("MatchedJetEta", &MatchedJetEta);
      Tree->SetBranchAddress("MatchedJetPhi", &MatchedJetPhi);
      Tree->SetBranchAddress("MatchedJetUE", &MatchedJetUE);
      Tree->SetBranchAddress("MatchedJetAngle", &MatchedJetAngle);

      int EntryCount = Tree->GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0)
            Bar.Print();

         Tree->GetEntry(iE);

         for(int iJ = 0; iJ < NGenJets; iJ++)
         {
            if(MatchedJetAngle->at(iJ) > 0.2)
               continue;
            if(GenJetPT->at(iJ) < 10)
               continue;
            if(IsExcluded(GenJetEta->at(iJ), GenJetPhi->at(iJ), JetExclusion) == true)
               continue;

            if(OnTheFlyJEC == true)
            {
               JEC.SetJetPT(MatchedJetPT->at(iJ));
               JEC.SetJetEta(MatchedJetEta->at(iJ));
               JEC.SetJetPhi(MatchedJetPhi->at(iJ));
               JEC.SetRho(MatchedJetUE->at(iJ) / (JetR * JetR * M_PI));
               MatchedJetPT->at(iJ) = JEC.GetCorrectedPT();
            }

            P1.Fill(GenJetPT->at(iJ), GenJetEta->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetPT->at(iJ) > 50)
               P24.Fill(GenJetPhi->at(iJ), GenJetEta->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetPT->at(iJ) > 100)
               P2.Fill(GenJetPhi->at(iJ), GenJetEta->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > 0.5 && GenJetEta->at(iJ) <= 1.0)
               P3.Fill(GenJetPT->at(iJ), GenJetPhi->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > -2.0 && GenJetEta->at(iJ) <= -1.5)
               P4.Fill(GenJetPT->at(iJ), GenJetPhi->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            P5.Fill(GenJetPT->at(iJ), GenJetEta->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetPT->at(iJ) > 200)
               P6.Fill(GenJetPhi->at(iJ), GenJetEta->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            
            if(GenJetEta->at(iJ) > -2.0 && GenJetEta->at(iJ) <= -1.5)
               P7.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > -1.5 && GenJetEta->at(iJ) <= -1.0)
               P8.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > -1.0 && GenJetEta->at(iJ) <= -0.5)
               P9.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > -0.5 && GenJetEta->at(iJ) <= 0.0)
               P10.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > 0.0 && GenJetEta->at(iJ) <= 0.5)
               P11.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > 0.5 && GenJetEta->at(iJ) <= 1.0)
               P12.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > 1.0 && GenJetEta->at(iJ) <= 1.5)
               P14.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > 1.5 && GenJetEta->at(iJ) <= 2.0)
               P15.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            
            if(GenJetEta->at(iJ) > -2.0 && GenJetEta->at(iJ) <= -1.5)
               P16.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > -1.5 && GenJetEta->at(iJ) <= -1.0)
               P17.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > -1.0 && GenJetEta->at(iJ) <= -0.5)
               P18.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > -0.5 && GenJetEta->at(iJ) <= 0.0)
               P19.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > 0.0 && GenJetEta->at(iJ) <= 0.5)
               P20.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > 0.5 && GenJetEta->at(iJ) <= 1.0)
               P21.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > 1.0 && GenJetEta->at(iJ) <= 1.5)
               P22.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
            if(GenJetEta->at(iJ) > 1.5 && GenJetEta->at(iJ) <= 2.0)
               P23.Fill(GenJetPT->at(iJ), MatchedJetPT->at(iJ) / GenJetPT->at(iJ));
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   P1.SetMinimum(0.75);
   P1.SetMaximum(1.25);
   P1.SetStats(0);
   P2.SetMinimum(0.75);
   P2.SetMaximum(1.25);
   P2.SetStats(0);
   P3.SetMinimum(0.75);
   P3.SetMaximum(1.25);
   P3.SetStats(0);
   P4.SetMinimum(0.75);
   P4.SetMaximum(1.25);
   P4.SetStats(0);
   P5.SetMinimum(0.75);
   P5.SetMaximum(1.25);
   P5.SetStats(0);
   P6.SetMinimum(0.75);
   P6.SetMaximum(1.25);
   P6.SetStats(0);
   P24.SetMinimum(0.75);
   P24.SetMaximum(1.25);
   P24.SetStats(0);

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Meooooow");

   PdfFile.AddPlot(P1, "colz", false, false, true, true);
   PdfFile.AddPlot(P24, "colz", false, false, true, false);
   PdfFile.AddPlot(P2, "colz", false, false, true, false);
   PdfFile.AddPlot(P3, "colz", false, false, true, true);
   PdfFile.AddPlot(P4, "colz", false, false, true, true);
   PdfFile.AddPlot(P5, "colz", false, false, true, true);
   PdfFile.AddPlot(P6, "colz", false, false, true, false);
   
   PlotProfile1D(PdfFile, P7);
   PlotProfile1D(PdfFile, P8);
   PlotProfile1D(PdfFile, P9);
   PlotProfile1D(PdfFile, P10);
   PlotProfile1D(PdfFile, P11);
   PlotProfile1D(PdfFile, P12);
   PlotProfile1D(PdfFile, P14);
   PlotProfile1D(PdfFile, P15);
   
   PlotProfile1D(PdfFile, P16);
   PlotProfile1D(PdfFile, P17);
   PlotProfile1D(PdfFile, P18);
   PlotProfile1D(PdfFile, P19);
   PlotProfile1D(PdfFile, P20);
   PlotProfile1D(PdfFile, P21);
   PlotProfile1D(PdfFile, P22);
   PlotProfile1D(PdfFile, P23);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

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

void PlotProfile1D(PdfFileHelper &PdfFile, TProfile &P)
{
   TGraph G;
   G.SetPoint(0, 0, 1);
   G.SetPoint(1, 10000, 1);
   G.SetPoint(2, 10000, 1.02);
   G.SetPoint(3, 0, 1.02);
   G.SetPoint(4, 0, 0.98);
   G.SetPoint(5, 10000, 0.98);

   P.SetMinimum(0.75);
   P.SetMaximum(1.25);
   P.SetStats(0);

   TCanvas Canvas;
   Canvas.SetLogx();
   Canvas.SetGridx();
   Canvas.SetGridy();

   P.Draw("");
   G.Draw("l");

   PdfFile.AddCanvas(Canvas);

   TGraphAsymmErrors GError;
   for(int i = 1; i <= P.GetNbinsX(); i++)
   {
      double XLow = P.GetXaxis()->GetBinLowEdge(i);
      double XHigh = P.GetXaxis()->GetBinLowEdge(i);
      double X = (XHigh + XLow) / 2;
      double Y = P.GetBinError(i);

      if(Y > 0)
      {
         int I = GError.GetN();
         GError.SetPoint(I, X, Y);
         GError.SetPointError(I, X - XLow, XHigh - X, 0, 0);
      }
   }

   PdfFile.AddPlot(GError, "ap", true, false, true, true);
}







