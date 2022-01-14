#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "ProgressBar.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   double Fraction       = CL.GetDouble("Fraction", 1.00);
   double JetR           = CL.GetDouble("JetR", 0.4);
   double Match          = CL.GetDouble("Match", 0.2);

   TFile InputFile(InputFileName.c_str());

   TTree *Tree = (TTree *)InputFile.Get("UnfoldingTree");

   int NJet;
   vector<float> *GenJetPT         = nullptr;
   vector<float> *GenJetEta        = nullptr;
   vector<float> *MatchedJetPT     = nullptr;
   vector<float> *MatchedJetAngle  = nullptr;
   vector<float> *MatchedJetUE     = nullptr;
   vector<float> MatchedJetRho;
   vector<float> *MatchedJetWeight = nullptr;

   Tree->SetBranchAddress("NGenJets",         &NJet);
   Tree->SetBranchAddress("GenJetPT",         &GenJetPT);
   Tree->SetBranchAddress("GenJetEta",        &GenJetEta);
   Tree->SetBranchAddress("MatchedJetPT",     &MatchedJetPT);
   Tree->SetBranchAddress("MatchedJetAngle",  &MatchedJetAngle);
   Tree->SetBranchAddress("MatchedJetUE",     &MatchedJetUE);
   Tree->SetBranchAddress("MatchedJetWeight", &MatchedJetWeight);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("JERTree", "");

   OutputTree.Branch("NJet",   &NJet, "NJet/I");
   OutputTree.Branch("Eta",    &GenJetEta);
   OutputTree.Branch("GenPT",  &GenJetPT);
   OutputTree.Branch("RecoPT", &MatchedJetPT);
   OutputTree.Branch("Rho",    &MatchedJetRho);
   OutputTree.Branch("Weight", &MatchedJetWeight);

   int EntryCount = Tree->GetEntries() * Fraction;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 500 || (iE % (EntryCount / 300) == 0))
      {
         Bar.Update(iE);
         Bar.Print();
      }

      Tree->GetEntry(iE);

      for(int iJ = 0; iJ < NJet; iJ++)
      {
         if(MatchedJetAngle->at(iJ) < 0 || MatchedJetAngle->at(iJ) > Match)   // failed match
         {
            GenJetPT->erase(GenJetPT->begin() + iJ);
            GenJetEta->erase(GenJetEta->begin() + iJ);
            MatchedJetPT->erase(MatchedJetPT->begin() + iJ);
            MatchedJetAngle->erase(MatchedJetAngle->begin() + iJ);
            if(MatchedJetUE != nullptr)
               MatchedJetUE->erase(MatchedJetUE->begin() + iJ);
            MatchedJetWeight->erase(MatchedJetWeight->begin() + iJ);
           
            iJ = iJ - 1;
            NJet = NJet - 1;
         }
      }

      MatchedJetRho.resize(NJet);
      if(MatchedJetUE != nullptr)
         for(int iJ = 0; iJ < NJet; iJ++)
            MatchedJetRho[iJ] = MatchedJetUE->at(iJ) / (M_PI * JetR * JetR);
      
      OutputTree.Fill();
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   OutputFile.Close();

   InputFile.Close();

   return 0;
}






