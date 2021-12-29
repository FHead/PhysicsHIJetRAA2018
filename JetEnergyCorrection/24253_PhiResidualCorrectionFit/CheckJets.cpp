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
void PlotPTEta(PdfFileHelper &PdfFile, vector<Jet> &Jets,
   double EtaMin, double EtaMax, double PTMin, double PTMax,
   string Title);
void PlotEtaPhi(PdfFileHelper &PdfFile, vector<Jet> &Jets,
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

         if(M.R <= 0)
            continue;

         if(OnTheFlyJEC == true)
         {
            JEC.SetJetPT(M.PT * M.R);
            JEC.SetJetEta(M.Eta);
            JEC.SetJetPhi(M.Phi);
            JEC.SetRho(M.Rho);
            M.R = JEC.GetCorrection() * M.R;
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
   PlotPT(PdfFile, Jets, -1.5, -1.0, 10, 1000, "Jet eta = [-1.5, -1.0];JetPT;<R>");
   PlotPT(PdfFile, Jets, -1.0, -0.5, 10, 1000, "Jet eta = [-1.0, -0.5];JetPT;<R>");
   PlotPT(PdfFile, Jets, -0.5, -0.0, 10, 1000, "Jet eta = [-0.5, 0.0];JetPT;<R>");
   PlotPT(PdfFile, Jets, +0.0, +0.5, 10, 1000, "Jet eta = [0.0, 0.5];JetPT;<R>");
   PlotPT(PdfFile, Jets, +0.5, +1.0, 10, 1000, "Jet eta = [0.5, 1.0];JetPT;<R>");
   PlotPT(PdfFile, Jets, +1.0, +1.5, 10, 1000, "Jet eta = [1.0, 1.5];JetPT;<R>");
   PlotPT(PdfFile, Jets, +1.5, +2.0, 10, 1000, "Jet eta = [1.5, 2.0];JetPT;<R>");
   PlotPT(PdfFile, Jets, -2.0, -1.5, 200, 1000, "Jet eta = [-2.0, -1.5];JetPT;<R>");
   PlotPT(PdfFile, Jets, -1.5, -1.0, 200, 1000, "Jet eta = [-1.5, -1.0];JetPT;<R>");
   PlotPT(PdfFile, Jets, -1.0, -0.5, 200, 1000, "Jet eta = [-1.0, -0.5];JetPT;<R>");
   PlotPT(PdfFile, Jets, -0.5, -0.0, 200, 1000, "Jet eta = [-0.5, 0.0];JetPT;<R>");
   PlotPT(PdfFile, Jets, +0.0, +0.5, 200, 1000, "Jet eta = [0.0, 0.5];JetPT;<R>");
   PlotPT(PdfFile, Jets, +0.5, +1.0, 200, 1000, "Jet eta = [0.5, 1.0];JetPT;<R>");
   PlotPT(PdfFile, Jets, +1.0, +1.5, 200, 1000, "Jet eta = [1.0, 1.5];JetPT;<R>");
   PlotPT(PdfFile, Jets, +1.5, +2.0, 200, 1000, "Jet eta = [1.5, 2.0];JetPT;<R>");
   
   PlotPTEta(PdfFile, Jets, -2.0, +2.0, 10, 1000, ";JetPT;JetEta;<R>");
   PlotPTEta(PdfFile, Jets, -2.0, +2.0, 150, 1000, ";JetPT;JetEta;<R>");
   PlotEtaPhi(PdfFile, Jets, -2.0, +2.0, 10, 50, "Jet PT = [10, 50];JetEta;JetPhi;<R>");
   PlotEtaPhi(PdfFile, Jets, -2.0, +2.0, 50, 100, "Jet PT = [50, 100];JetEta;JetPhi;<R>");
   PlotEtaPhi(PdfFile, Jets, -2.0, +2.0, 100, 500, "Jet PT = [100, 500];JetEta;JetPhi;<R>");

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

   vector<vector<double>> BinJets(NBin);

   for(Jet &J : Jets)
   {
      if(J.Eta > EtaMax || J.Eta <= EtaMin)
         continue;
      for(int i = 0; i < NBin; i++)
         if(J.PT > PTBin[i] && J.PT <= PTBin[i+1])
            BinJets[i].push_back(J.R);
   }
      
   for(int i = 0; i < NBin; i++)
   {
      sort(BinJets[i].begin(), BinJets[i].end());
      if(BinJets[i].size() > 10)
         H.SetBinContent(i + 1, BinJets[i][BinJets[i].size()/2]);
   }

   TCanvas Canvas;
   
   H.SetMinimum(0.75);
   H.SetMaximum(1.25);
   H.Draw();

   Canvas.SetGridx();
   Canvas.SetGridy();
   Canvas.SetLogx();

   PdfFile.AddCanvas(Canvas);
}

void PlotPTEta(PdfFileHelper &PdfFile, vector<Jet> &Jets,
   double EtaMin, double EtaMax, double PTMin, double PTMax,
   string Title)
{
   int NBin = 100;
   double PTBin[101] = {0};
   for(int i = 0; i <= NBin; i++)
      PTBin[i] = exp((log(PTMax) - log(PTMin)) / NBin * i + log(PTMin));

   static int Index = 0;
   Index = Index + 1;
   TH2D H(Form("HPTEta%d", Index), Title.c_str(), NBin, PTBin, NBin, EtaMin, EtaMax);
   H.SetStats(0);

   vector<vector<vector<double>>> BinJets(NBin);
   for(vector<vector<double>> &V : BinJets)
      V.resize(NBin);

   for(Jet &J : Jets)
   {
      if(J.Eta >= EtaMax || J.Eta <= EtaMin)
         continue;
      for(int i = 0; i < NBin; i++)
      {
         if(J.PT > PTBin[i] && J.PT <= PTBin[i+1])
         {
            int iEta = (J.Eta - EtaMin) / (EtaMax - EtaMin) * NBin;
            BinJets[i][iEta].push_back(J.R);
         }
      }
   }
      
   for(int i = 0; i < NBin; i++)
   {
      for(int j = 0; j < NBin; j++)
      {
         sort(BinJets[i][j].begin(), BinJets[i][j].end());
         if(BinJets[i][j].size() > 10)
            H.SetBinContent(i + 1, j + 1, BinJets[i][j][BinJets[i][j].size()/2]);
      }
   }

   TCanvas Canvas;
   
   H.SetMinimum(0.75);
   H.SetMaximum(1.25);
   H.Draw("colz");

   Canvas.SetGridx();
   Canvas.SetGridy();
   Canvas.SetLogx();

   PdfFile.AddCanvas(Canvas);
}

void PlotEtaPhi(PdfFileHelper &PdfFile, vector<Jet> &Jets,
   double EtaMin, double EtaMax, double PTMin, double PTMax,
   string Title)
{
   int NBin = 100;

   static int Index = 0;
   Index = Index + 1;
   TH2D H(Form("HEtaPhi%d", Index), Title.c_str(), NBin, EtaMin, EtaMax, NBin, -M_PI, M_PI);
   H.SetStats(0);

   vector<vector<vector<double>>> BinJets(NBin);
   for(vector<vector<double>> &V : BinJets)
      V.resize(NBin);

   for(Jet &J : Jets)
   {
      if(J.Eta >= EtaMax || J.Eta <= EtaMin)
         continue;
      if(J.PT >= PTMax || J.PT <= PTMin)
         continue;
   
      int iEta = (J.Eta - EtaMin) / (EtaMax - EtaMin) * NBin;
      int iPhi = (J.Phi + M_PI) / (2 * M_PI) * NBin;

      if(iEta == NBin)   iEta = NBin - 1;
      if(iPhi == NBin)   iPhi = NBin - 1;
      BinJets[iEta][iPhi].push_back(J.R);
   }
      
   for(int i = 0; i < NBin; i++)
   {
      for(int j = 0; j < NBin; j++)
      {
         sort(BinJets[i][j].begin(), BinJets[i][j].end());
         if(BinJets[i][j].size() > 10)
            H.SetBinContent(i + 1, j + 1, BinJets[i][j][BinJets[i][j].size()/2]);
      }
   }

   TCanvas Canvas;
   
   H.SetMinimum(0.75);
   H.SetMaximum(1.25);
   H.Draw("colz");

   Canvas.SetGridx();
   Canvas.SetGridy();

   PdfFile.AddCanvas(Canvas);
}

