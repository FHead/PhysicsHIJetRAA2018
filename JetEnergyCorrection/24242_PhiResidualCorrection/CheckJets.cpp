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

struct Jet {double PT; double Eta; double Phi; double Rho; double R;};

int main(int argc, char *argv[]);
bool IsExcluded(double Eta, double Phi, vector<double> &Exclusion);
void PlotPT(PdfFileHelper &PdfFile, vector<Jet> &Jets,
   double EtaMin, double EtaMax, double PTMin, double PTMax,
   string Title);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   double Fraction               = CL.GetDouble("Fraction", 1.000);
   string Output                 = CL.Get("Output", "Result.pdf");
   bool OnTheFlyJEC              = CL.GetBool("OnTheFlyJEC", false);
   double JetR                   = OnTheFlyJEC ? CL.GetDouble("JetR", 0.4) : 0.4;
   vector<string> JECFile        = OnTheFlyJEC ? CL.GetStringVector("JEC", vector<string>{}) : vector<string>();

   JetCorrector JEC(JECFile);
   
   /*
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
   */

   vector<Jet> Jets;

   for(string FileName : InputFileNames)
   {
      TFile File(FileName.c_str());

      TTree *Tree = (TTree *)File.Get("PhiTree");
      
      if(Tree == nullptr)
      {
         File.Close();
         continue;
      }

      Jet M;
      Tree->SetBranchAddress("PT", &M.PT);
      Tree->SetBranchAddress("Eta", &M.Eta);
      Tree->SetBranchAddress("Phi", &M.Phi);
      Tree->SetBranchAddress("Rho", &M.Rho);
      Tree->SetBranchAddress("R", &M.R);

      int EntryCount = Tree->GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0)
            Bar.Print();

         Tree->GetEntry(iE);

         if(OnTheFlyJEC == true)
         {
            JEC.SetJetPT(M.PT * M.R);
            JEC.SetJetEta(M.Eta);
            JEC.SetJetPhi(M.Phi);
            JEC.SetRho(M.Rho);
            M.R = JEC.GetCorrectedPT() * M.R;
         }

         Jets.push_back(M);
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Meow");

   PlotPT(PdfFile, Jets, -2.0, -1.5, 10, 1000, "Jet eta = [-2.0, -1.5];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [-1.5, -1.0];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [-1.0, -0.5];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [-0.5, 0.0];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [0.0, 0.5];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [0.5, 1.0];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [1.0, 1.5];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [1.5, 2.0];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [-2.0, -1.5];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [-1.5, -1.0];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [-1.0, -0.5];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [-0.5, 0.0];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [0.0, 0.5];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [0.5, 1.0];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [1.0, 1.5];JetPT;<R>");
   // PlotPT(PdfFile, Jets, 1.0, 3.0, 10, 1000, "Jet eta = [1.5, 2.0];JetPT;<R>");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void PlotPT(PdfFileHelper &PdfFile, vector<Jet> &Jets,
   double EtaMin, double EtaMax, double PTMin, double PTMax,
   string Title)
{
   int NBin = 100;
   double PTBin[101] = {0};
   for(int i = 0; i <= NBin; i++)
      PTBin[i] = exp((log(PTMax) - log(PTMin)) / NBin * i + log(PTMin));

   static int Index = 0;
   Index = Index + 1;
   TH1D H(Form("HPT%d", Index), Title.c_str(), NBin, PTBin);
   H.SetStats(0);

   for(int i = 0; i < NBin; i++)
   {
      vector<double> BinJets;

      for(Jet &J : Jets)
      {
         if(J.PT > PTBin[i+1] || J.PT <= PTBin[i])
            continue;
         if(J.Eta > EtaMax || J.Eta <= EtaMin)
            continue;

         BinJets.push_back(J.R);
      }

      sort(BinJets.begin(), BinJets.end());
      if(BinJets.size() > 10)
         H.SetBinContent(i + 1, BinJets[BinJets.size()/2]);
   }

   PdfFile.AddPlot(H);
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







