#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"
#include "DataHelper.h"
#include "CustomAssert.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "ProgressBar.h"

#define MAX 25000

struct Jet
{
   double UE;
   double W;
   bool operator <(const Jet &other) const
   {
      if(UE < other.UE)   return true;
      if(UE > other.UE)   return false;
      if(W < other.W)     return true;
      if(W > other.W)     return false;
      return false;
   }
};
int main(int argc, char *argv[]);
void ReadData(string FileName, vector<Jet> &Data, double JetMinPT, bool UseMatch = false);
TGraphAsymmErrors SplitIntoBins(vector<Jet> &Data, int BinCount, int BinMagnification = 1);
TGraphAsymmErrors FillGraph(vector<Jet> Data, TGraphAsymmErrors &GInput);
TGraphAsymmErrors BuildRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2, bool Log = false, bool SkipFinalBin = false);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> DataFileNames = CL.GetStringVector("Data", vector<string>{});
   vector<string> MCFileNames   = CL.GetStringVector("MC", vector<string>{});
   double JetMinPT              = CL.GetDouble("JetMinPT", 150);
   string RootOutputFileName    = CL.Get("Output");

   Assert(DataFileNames.size() > 0, "Please provide at least one data file");
   Assert(MCFileNames.size() > 0,   "Please provide at least one MC file");

   vector<Jet> Data;
   vector<Jet> MC;

   for(string FileName : DataFileNames)
      ReadData(FileName, Data, JetMinPT, false);
   for(string FileName : MCFileNames)
      ReadData(FileName, MC, JetMinPT, true);

   TFile OutputFile(RootOutputFileName.c_str(), "RECREATE");

   TTree OutputTree("Tree", "Tree");

   int T;
   Jet M;
   OutputTree.Branch("Type", &T);
   OutputTree.Branch("JetUE", &M.UE);
   OutputTree.Branch("Weight", &M.W);

   T = 0;
   for(Jet &J : Data)
   {
      M = J;
      OutputTree.Fill();
   }
   
   T = 1;
   for(Jet &J : MC)
   {
      M = J;
      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

void ReadData(string FileName, vector<Jet> &Data, double JetMinPT, bool UseMatch)
{
   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("UnfoldingTreeFlat");
   if(Tree == nullptr)
   {
      File.Close();
      return;
   }

   double EventWeight;
   int NRecoJets;
   float RecoJetPT[MAX];
   float RecoJetUE[MAX];
   float RecoJetWeight[MAX];
   float RecoJetPhiWeight[MAX];

   for(int i = 0; i < MAX; i++)
   {
      RecoJetWeight[i] = 1;
      RecoJetPhiWeight[i] = 1;
   }

   Tree->SetBranchAddress("EventWeight",      &EventWeight);
   if(UseMatch == false)
   {
      Tree->SetBranchAddress("NRecoJets",           &NRecoJets);
      Tree->SetBranchAddress("RecoJetPT",           &RecoJetPT);
      Tree->SetBranchAddress("RecoJetUE",           &RecoJetUE);
      if(Tree->GetBranch("RecoJetWeight") != nullptr)
         Tree->SetBranchAddress("RecoJetWeight",       &RecoJetWeight);
      if(Tree->GetBranch("RecoJetWeight") != nullptr)
         Tree->SetBranchAddress("RecoJetPhiWeight",    &RecoJetPhiWeight);
   }
   else
   {
      Tree->SetBranchAddress("NGenJets",            &NRecoJets);
      Tree->SetBranchAddress("MatchedJetPT",        &RecoJetPT);
      Tree->SetBranchAddress("MatchedJetUE",        &RecoJetUE);
      if(Tree->GetBranch("MatchJetWeight") != nullptr)
         Tree->SetBranchAddress("MatchJetWeight",       &RecoJetWeight);
      if(Tree->GetBranch("MatchJetWeight") != nullptr)
         Tree->SetBranchAddress("MatchJetPhiWeight",    &RecoJetPhiWeight);
   }

   int EntryCount = Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(3);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(EntryCount < 500 || (iE % (EntryCount / 300) == 0))
      {
         Bar.Update(iE);
         Bar.Print();
      }

      for(int iJ = 0; iJ < NRecoJets; iJ++)
      {
         if(RecoJetPT[iJ] < JetMinPT)
            continue;

         double UE = RecoJetUE[iJ];
         double Weight = EventWeight;
         Weight = Weight * RecoJetWeight[iJ];
         // Weight = Weight * RecoJetPhiWeight[iJ];   // this is a bug!  the weight includes already phi

         Data.push_back(Jet{UE, Weight});
      }
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();
}


