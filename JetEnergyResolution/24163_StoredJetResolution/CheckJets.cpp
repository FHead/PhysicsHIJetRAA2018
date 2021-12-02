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

#define AXIS_PT 0
#define AXIS_ETA 1
#define AXIS_PHI 2

struct Jet;
struct Region;
int main(int argc, char *argv[]);
void ReadFile(string FileName, vector<Jet> &Jets, double Fraction,
   bool DoJEC, JetCorrector &JEC, double JetR, vector<double> &JetExclusion);
bool IsExcluded(double Eta, double Phi, vector<double> &Exclusion);
TGraphAsymmErrors GetResolution(PdfFileHelper &PdfFile, vector<Jet> &Jets, vector<Region> &Regions, int Axis);
void PlotResolution(PdfFileHelper &PdfFile, TGraphAsymmErrors &G, bool LogX);

struct Jet
{
   double GenPT;
   double GenEta;
   double GenPhi;
   double RecoPT;
   double RecoRho;
   double RecoWeight;
   double Centrality;
};

struct Region
{
   double PTMin;
   double PTMax;
   double EtaMin;
   double EtaMax;
   double PhiMin;
   double PhiMax;
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   double Fraction               = CL.GetDouble("Fraction", 1.000);
   string Output                 = CL.Get("Output", "Result.pdf");
   string RootOutput             = CL.Get("RootOutput", "Result.root");
   vector<double> JetExclusion   = CL.GetDoubleVector("Exclusion", vector<double>{});
   bool OnTheFlyJEC              = CL.GetBool("OnTheFlyJEC", false);
   double JetR                   = OnTheFlyJEC ? CL.GetDouble("JetR", 0.4) : 0.4;
   vector<string> JECFile        = OnTheFlyJEC ? CL.GetStringVector("JEC", vector<string>{}) : vector<string>();

   JetCorrector JEC(JECFile);
   
   vector<Jet> Jets;
   for(string FileName : InputFileNames)
      ReadFile(FileName, Jets, Fraction, OnTheFlyJEC, JEC, JetR, JetExclusion);

   cout << "Number of jets read: " << Jets.size() << endl;

   double JetPTBins[101];
   double JetPTMin = 10;
   double JetPTMax = 1000;
   int JetPTBin = 50;
   for(int i = 0; i <= JetPTBin; i++)
      JetPTBins[i] = exp(log(JetPTMin) + (log(JetPTMax) - log(JetPTMin)) / JetPTBin * i);
   
   vector<Region> Region_PT_EtaBin1;
   vector<Region> Region_PT_EtaBin2;
   vector<Region> Region_PT_EtaBin3;
   vector<Region> Region_PT_EtaBin4;
   vector<Region> Region_PT_EtaBin5;
   vector<Region> Region_PT_EtaBin6;
   vector<Region> Region_PT_EtaBin7;
   vector<Region> Region_PT_EtaBin8;
   for(int i = 0; i < JetPTBin; i++)
   {
      Region_PT_EtaBin1.push_back(Region{JetPTBins[i], JetPTBins[i+1], -2.0, -1.5, -M_PI, +M_PI});
      Region_PT_EtaBin2.push_back(Region{JetPTBins[i], JetPTBins[i+1], -1.5, -1.0, -M_PI, +M_PI});
      Region_PT_EtaBin3.push_back(Region{JetPTBins[i], JetPTBins[i+1], -1.0, -0.5, -M_PI, +M_PI});
      Region_PT_EtaBin4.push_back(Region{JetPTBins[i], JetPTBins[i+1], -0.5,  0.0, -M_PI, +M_PI});
      Region_PT_EtaBin5.push_back(Region{JetPTBins[i], JetPTBins[i+1],  0.0, +0.5, -M_PI, +M_PI});
      Region_PT_EtaBin6.push_back(Region{JetPTBins[i], JetPTBins[i+1], +0.5, +1.0, -M_PI, +M_PI});
      Region_PT_EtaBin7.push_back(Region{JetPTBins[i], JetPTBins[i+1], +1.0, +1.5, -M_PI, +M_PI});
      Region_PT_EtaBin8.push_back(Region{JetPTBins[i], JetPTBins[i+1], +1.5, +2.0, -M_PI, +M_PI});
   }

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Meow");

   TGraphAsymmErrors G_JER_PT_EtaBin1 = GetResolution(PdfFile, Jets, Region_PT_EtaBin1, AXIS_PT);
   TGraphAsymmErrors G_JER_PT_EtaBin2 = GetResolution(PdfFile, Jets, Region_PT_EtaBin2, AXIS_PT);
   TGraphAsymmErrors G_JER_PT_EtaBin3 = GetResolution(PdfFile, Jets, Region_PT_EtaBin3, AXIS_PT);
   TGraphAsymmErrors G_JER_PT_EtaBin4 = GetResolution(PdfFile, Jets, Region_PT_EtaBin4, AXIS_PT);
   TGraphAsymmErrors G_JER_PT_EtaBin5 = GetResolution(PdfFile, Jets, Region_PT_EtaBin5, AXIS_PT);
   TGraphAsymmErrors G_JER_PT_EtaBin6 = GetResolution(PdfFile, Jets, Region_PT_EtaBin6, AXIS_PT);
   TGraphAsymmErrors G_JER_PT_EtaBin7 = GetResolution(PdfFile, Jets, Region_PT_EtaBin7, AXIS_PT);
   TGraphAsymmErrors G_JER_PT_EtaBin8 = GetResolution(PdfFile, Jets, Region_PT_EtaBin8, AXIS_PT);

   PlotResolution(PdfFile, G_JER_PT_EtaBin1, true);
   PlotResolution(PdfFile, G_JER_PT_EtaBin2, true);
   PlotResolution(PdfFile, G_JER_PT_EtaBin3, true);
   PlotResolution(PdfFile, G_JER_PT_EtaBin4, true);
   PlotResolution(PdfFile, G_JER_PT_EtaBin5, true);
   PlotResolution(PdfFile, G_JER_PT_EtaBin6, true);
   PlotResolution(PdfFile, G_JER_PT_EtaBin7, true);
   PlotResolution(PdfFile, G_JER_PT_EtaBin8, true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   TFile File(RootOutput.c_str(), "RECREATE");

   G_JER_PT_EtaBin1.Clone("G_JER_PT_EtaBin1")->Write();
   G_JER_PT_EtaBin2.Clone("G_JER_PT_EtaBin2")->Write();
   G_JER_PT_EtaBin3.Clone("G_JER_PT_EtaBin3")->Write();
   G_JER_PT_EtaBin4.Clone("G_JER_PT_EtaBin4")->Write();
   G_JER_PT_EtaBin5.Clone("G_JER_PT_EtaBin5")->Write();
   G_JER_PT_EtaBin6.Clone("G_JER_PT_EtaBin6")->Write();
   G_JER_PT_EtaBin7.Clone("G_JER_PT_EtaBin7")->Write();
   G_JER_PT_EtaBin8.Clone("G_JER_PT_EtaBin8")->Write();

   File.Close();

   return 0;
}

void ReadFile(string FileName, vector<Jet> &Jets, double Fraction,
   bool DoJEC, JetCorrector &JEC, double JetR, vector<double> &JetExclusion)
{
   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("UnfoldingTree");

   if(Tree == nullptr)
   {
      File.Close();
      return;
   }

   vector<float> F0;

   double Centrality = 0;
   int NGenJets = 0;
   vector<float> *GenJetPT = nullptr;
   vector<float> *GenJetEta = nullptr;
   vector<float> *GenJetPhi = nullptr;
   vector<float> *MatchedJetPT = nullptr;
   vector<float> *MatchedJetEta = nullptr;
   vector<float> *MatchedJetPhi = nullptr;
   vector<float> *MatchedJetUE = nullptr;
   vector<float> *MatchedJetAngle = nullptr;
   vector<float> *MatchedJetWeight = nullptr;

   Tree->SetBranchAddress("Centrality", &Centrality);
   Tree->SetBranchAddress("NGenJets", &NGenJets);
   Tree->SetBranchAddress("GenJetPT", &GenJetPT);
   Tree->SetBranchAddress("GenJetEta", &GenJetEta);
   Tree->SetBranchAddress("GenJetPhi", &GenJetPhi);
   Tree->SetBranchAddress("MatchedJetPT", &MatchedJetPT);
   Tree->SetBranchAddress("MatchedJetEta", &MatchedJetEta);
   Tree->SetBranchAddress("MatchedJetPhi", &MatchedJetPhi);
   Tree->SetBranchAddress("MatchedJetUE", &MatchedJetUE);
   Tree->SetBranchAddress("MatchedJetAngle", &MatchedJetAngle);
   Tree->SetBranchAddress("MatchedJetWeight", &MatchedJetWeight);

   int EntryCount = Tree->GetEntries() * Fraction;
   ProgressBar Bar(cout, EntryCount);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0)
         Bar.Print();

      Tree->GetEntry(iE);
      
      F0.resize(NGenJets, 1.0);

      if(MatchedJetUE == nullptr)       MatchedJetUE = &F0;
      if(MatchedJetWeight == nullptr)   MatchedJetWeight = &F0;

      for(int iJ = 0; iJ < NGenJets; iJ++)
      {
         if(MatchedJetAngle->at(iJ) > 0.2)
            continue;
         if(GenJetPT->at(iJ) < 10)
            continue;
         if(IsExcluded(GenJetEta->at(iJ), GenJetPhi->at(iJ), JetExclusion) == true)
            continue;

         if(DoJEC == true)
         {
            JEC.SetJetPT(MatchedJetPT->at(iJ));
            JEC.SetJetEta(MatchedJetEta->at(iJ));
            JEC.SetJetPhi(MatchedJetPhi->at(iJ));
            JEC.SetRho(MatchedJetUE->at(iJ) / (JetR * JetR * M_PI));
            MatchedJetPT->at(iJ) = JEC.GetCorrectedPT();
         }

         Jet NewJet;
         NewJet.GenPT      = GenJetPT->at(iJ);
         NewJet.GenEta     = GenJetEta->at(iJ);
         NewJet.GenPhi     = GenJetPhi->at(iJ);
         NewJet.RecoPT     = MatchedJetPT->at(iJ);
         NewJet.RecoRho    = MatchedJetUE->at(iJ) / (JetR * JetR * M_PI);
         NewJet.RecoWeight = MatchedJetWeight->at(iJ);
         NewJet.Centrality = Centrality;

         if(NewJet.RecoWeight <= 0)   // no point in storing 0-weight jets
            continue;
         Jets.push_back(NewJet);
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();
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

TGraphAsymmErrors GetResolution(PdfFileHelper &PdfFile, vector<Jet> &Jets, vector<Region> &Regions, int Axis)
{
   TGraphAsymmErrors G(Regions.size());

   for(int iR = 0; iR < (int)Regions.size(); iR++)
   {
      Region R = Regions[iR];

      double SumW = 0;
      double SumWR1 = 0;
      double SumWR2 = 0;

      TH1D HR("HR", Form("PT[%.1f,%.1f], Eta[%.2f,%.2f], Phi[%.2f,%.2f];;", R.PTMin, R.PTMax, R.EtaMin, R.EtaMax, R.PhiMin, R.PhiMax), 100, 0, 2);

      for(Jet &J : Jets)
      {
         if(J.GenPT  < R.PTMin)    continue;
         if(J.GenPT  > R.PTMax)    continue;
         if(J.GenEta < R.EtaMin)   continue;
         if(J.GenEta > R.EtaMax)   continue;
         if(J.GenPhi < R.PhiMin)   continue;
         if(J.GenPhi > R.PhiMax)   continue;

         double R = J.RecoPT / J.GenPT;

         SumW   = SumW + J.RecoWeight;
         SumWR1 = SumWR1 + J.RecoWeight * R;
         SumWR2 = SumWR2 + J.RecoWeight * R * R;

         HR.Fill(R, J.RecoWeight);
      }

      double Mean = SumWR1 / SumW;
      double RMS = sqrt((SumWR2 - SumW * Mean * Mean) / SumW);
      double RMSError = 0;

      double X, DX;
      if(Axis == AXIS_PT)
      {
         X = (R.PTMin + R.PTMax) / 2;
         DX = (R.PTMax - R.PTMin) / 2;
      }

      // G.SetPoint(iR, X, Mean);
      // G.SetPointError(iR, DX, DX, RMS, RMS);
      
      // G.SetPoint(iR, X, RMS);
      // G.SetPointError(iR, DX, DX, RMSError, RMSError);

      TF1 F("F", "gaus");
      F.SetParameters(HR.GetMaximum(), 1, 0.15);
      HR.Fit(&F, "w", "", 0.5, 1.5);
      HR.Fit(&F, "", "", 0.5, 1.5);
      PdfFile.AddPlot(HR, "");
      
      G.SetPoint(iR, X, F.GetParameter(2));
      G.SetPointError(iR, DX, DX, F.GetParError(2), F.GetParError(2));
   }

   return G;
}

void PlotResolution(PdfFileHelper &PdfFile, TGraphAsymmErrors &G, bool LogX)
{
   double MinX = +9999;
   double MaxX = -9999;

   for(int i = 0; i < G.GetN(); i++)
   {
      double X = G.GetPointX(i);
      double EXL = G.GetErrorXlow(i);
      double EXH = G.GetErrorXhigh(i);

      if(MinX > X - EXL)   MinX = X - EXL;
      if(MaxX < X + EXH)   MaxX = X + EXH;
   }

   if(LogX == true)
   {
      double RangeX = MaxX / MinX;
      MinX = MinX / pow(RangeX, 0.05);
      MaxX = MaxX * pow(RangeX, 0.05);
   }
   else
   {
      double RangeX = MaxX - MinX;
      MinX = MinX - RangeX * 0.05;
      MaxX = MaxX + RangeX * 0.05;
   }

   TH2D HWorld("HWorld", ";;RMS", 100, MinX, MaxX, 100, 0.01, 1.00);
   HWorld.SetStats(0);

   TCanvas Canvas;
   
   HWorld.Draw("axis");
   G.Draw("p");
   
   Canvas.SetLogx(LogX);
   Canvas.SetLogy(true);
   
   PdfFile.AddCanvas(Canvas);
}





