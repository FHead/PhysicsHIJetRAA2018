#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TF1.h"
#include "TH2Poly.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "CustomAssert.h"
#include "SetStyle.h"
#include "ProgressBar.h"

struct Jet {double PT; double Eta; double Phi; double Rho; double R;};

int main(int argc, char *argv[]);
bool IsExcluded(double Eta, double Phi, vector<double> &Exclusion);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> FileNames    = CL.GetStringVector("Input", vector<string>{});
   string OutputFileName       = CL.Get("Output", "Result.root");
   vector<double> JetExclusion = CL.GetDoubleVector("Exclusion", vector<double>{});
   double MinPT                = CL.GetDouble("MinPT", 50);
   double JetR                 = CL.GetDouble("JetR", 0.4);
   bool BaseOnGen              = CL.GetBool("BaseOnGen", false);
   
   double JetArea = JetR * JetR * M_PI;
            
   Assert(JetR > 0,                     "Nonsense jet radius detected!");
   Assert(JetExclusion.size() % 4 == 0, "Format: {eta min, eta max, phi min, phi max}^n");

   // Exclusion min-max switch if needed
   for(int i = 0; i + 2 < (int)JetExclusion.size(); i = i + 2)
      if(JetExclusion[i] > JetExclusion[i+1])
         swap(JetExclusion[i], JetExclusion[i+1]);

   vector<Jet> Jets;

   for(string FileName : FileNames)
   {
      TFile File(FileName.c_str());

      TTree *Tree = (TTree *)File.Get("UnfoldingTree");

      if(Tree == nullptr)
      {
         File.Close();
         continue;
      }

      vector<float> *GenJetPT = nullptr;
      vector<float> *GenJetEta = nullptr;
      vector<float> *GenJetPhi = nullptr;
      vector<float> *MatchedJetPT = nullptr;
      vector<float> *MatchedJetEta = nullptr;
      vector<float> *MatchedJetPhi = nullptr;
      vector<float> *MatchedJetRho = nullptr;
      vector<float> *MatchedJetUE = nullptr;
      vector<float> *MatchedJetAngle = nullptr;

      Tree->SetBranchAddress("GenJetPT", &GenJetPT);
      Tree->SetBranchAddress("GenJetEta", &GenJetEta);
      Tree->SetBranchAddress("GenJetPhi", &GenJetPhi);
      Tree->SetBranchAddress("MatchedJetPT", &MatchedJetPT);
      Tree->SetBranchAddress("MatchedJetEta", &MatchedJetEta);
      Tree->SetBranchAddress("MatchedJetPhi", &MatchedJetPhi);
      Tree->SetBranchAddress("MatchedJetRho", &MatchedJetRho);
      Tree->SetBranchAddress("MatchedJetUE", &MatchedJetUE);
      Tree->SetBranchAddress("MatchedJetAngle", &MatchedJetAngle);

      int EntryCount = Tree->GetEntries();
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(5);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         Bar.Update(iE);
         if(EntryCount < 500 || (iE % (EntryCount / 300) == 0))
            Bar.Print();

         int NJet = GenJetPT->size();

         for(int iJ = 0; iJ < NJet; iJ++)
         {
            if(BaseOnGen == true && GenJetPT->at(iJ) < MinPT)
               continue;
            if(BaseOnGen == false && GenJetPT->at(iJ) < MinPT)
               continue;

            if(MatchedJetAngle->at(iJ) > JetR * 0.5)
               continue;

            double AverageRho = MatchedJetUE->at(iJ) / JetArea;

            if(BaseOnGen == true && IsExcluded(GenJetEta->at(iJ), GenJetPhi->at(iJ), JetExclusion) == true)
               continue;
            if(BaseOnGen == false && IsExcluded(MatchedJetEta->at(iJ), MatchedJetPhi->at(iJ), JetExclusion) == true)
               continue;

            double R = MatchedJetPT->at(iJ) / GenJetPT->at(iJ);

            if(BaseOnGen == true)
               Jets.push_back({GenJetPT->at(iJ), GenJetEta->at(iJ), GenJetPhi->at(iJ), AverageRho, R});
            else
               Jets.push_back({MatchedJetPT->at(iJ), MatchedJetEta->at(iJ), MatchedJetPhi->at(iJ), AverageRho, R});
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   // Root output
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("PhiTree", "");

   Jet M;
   OutputTree.Branch("PT", &M.PT, "PT/D");
   OutputTree.Branch("Eta", &M.Eta, "Eta/D");
   OutputTree.Branch("Phi", &M.Phi, "Phi/D");
   OutputTree.Branch("Rho", &M.Rho, "Rho/D");
   OutputTree.Branch("R", &M.R, "R/D");

   for(Jet J : Jets)
   {
      M = J;
      OutputTree.Fill();
   }

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





