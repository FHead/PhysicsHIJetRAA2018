#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TF1.h"

#include "PlotHelper4.h"
#include "SetStyle.h"
#include "RootUtilities.h"
#include "CommandLine.h"
#include "ProgressBar.h"

#define MAX 1000

struct Configuration;
int main(int argc, char *argv[]);

struct Configuration
{
   double PTMin;
   double PTMax;
};

int main(int argc, char *argv[])
{
   SilenceRoot();

   vector<int> Colors = GetPrimaryColors();
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   string RootOutputFileName = CL.Get("Root");
   double DRMax = CL.GetDouble("DRMax", 0.1);
   double Fraction = CL.GetDouble("Fraction", 1.00);

   vector<Configuration> Cs;
   Cs.emplace_back(Configuration{100, 200});
   Cs.emplace_back(Configuration{200, 300});
   Cs.emplace_back(Configuration{300, 500});
   Cs.emplace_back(Configuration{500, 700});
   Cs.emplace_back(Configuration{700, 1000});
   const int NC = Cs.size();
   
   vector<double> Ts{1.0, 1.5, 2.0, 2.5, 3.0, 1000};
   const int NT = Ts.size();

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Soft fraction");

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get("UnfoldingTreeFlat");

   int NGenJets;
   float GenJetPT[MAX];
   float GenJetEta[MAX];
   float GenJetPhi[MAX];
   float GenJetWeight[MAX];
   float MatchedJetPT[MAX];
   float MatchedJetEta[MAX];
   float MatchedJetPhi[MAX];
   float MatchedJetJEC[MAX];
   float MatchedJetAngle[MAX];
   float MatchedJetSF10[MAX];
   float MatchedJetSF15[MAX];
   float MatchedJetSF20[MAX];
   float MatchedJetSF25[MAX];
   float MatchedJetSF30[MAX];

   Tree->SetBranchAddress("NGenJets", &NGenJets);
   Tree->SetBranchAddress("GenJetPT", &GenJetPT);
   Tree->SetBranchAddress("GenJetEta", &GenJetEta);
   Tree->SetBranchAddress("GenJetPhi", &GenJetPhi);
   Tree->SetBranchAddress("GenJetWeight", &GenJetWeight);
   Tree->SetBranchAddress("MatchedJetPT", &MatchedJetPT);
   Tree->SetBranchAddress("MatchedJetEta", &MatchedJetEta);
   Tree->SetBranchAddress("MatchedJetPhi", &MatchedJetPhi);
   Tree->SetBranchAddress("MatchedJetJEC", &MatchedJetJEC);
   Tree->SetBranchAddress("MatchedJetAngle", &MatchedJetAngle);
   Tree->SetBranchAddress("MatchedJetSF10", &MatchedJetSF10);
   Tree->SetBranchAddress("MatchedJetSF15", &MatchedJetSF15);
   Tree->SetBranchAddress("MatchedJetSF20", &MatchedJetSF20);
   Tree->SetBranchAddress("MatchedJetSF25", &MatchedJetSF25);
   Tree->SetBranchAddress("MatchedJetSF30", &MatchedJetSF30);

   TFile OutputFile(RootOutputFileName.c_str(), "RECREATE");

   TTree OutputTree("Tree", "Tree");

   float TreePT, TreeR, TreeW;
   float TreeF10, TreeF15, TreeF20, TreeF25, TreeF30;
   OutputTree.Branch("PT", &TreePT, "PT/F");
   OutputTree.Branch("R", &TreeR, "R/F");
   OutputTree.Branch("W", &TreeW, "W/F");
   OutputTree.Branch("F10", &TreeF10, "F10/F");
   OutputTree.Branch("F15", &TreeF15, "F15/F");
   OutputTree.Branch("F20", &TreeF20, "F20/F");
   OutputTree.Branch("F25", &TreeF25, "F25/F");
   OutputTree.Branch("F30", &TreeF30, "F30/F");

   int EntryCount = Tree->GetEntries() * Fraction;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   vector<vector<TProfile *>> Ps(NC);
   vector<vector<TH2D *>> Hs(NC);
   for(int iC = 0; iC < NC; iC++)
   {
      Ps[iC].resize(NT);
      Hs[iC].resize(NT);
      for(int iT = 0; iT < NT; iT++)
      {
         Ps[iC][iT] = new TProfile(Form("P%d%d", iC, iT), ";;Response", 100, 0, 0.3);
         Ps[iC][iT]->SetTitle(Form("PT = [%.0f, %.0f]", Cs[iC].PTMin, Cs[iC].PTMax));
         if(iT > 0)
            Ps[iC][iT]->GetXaxis()->SetTitle(Form("Fraction (PF PT = %.2f-%.2f GeV)", Ts[iT-1], Ts[iT]));
         else
            Ps[iC][iT]->GetXaxis()->SetTitle(Form("Fraction (PF PT < %.2f GeV)", Ts[iT]));
         
         Hs[iC][iT] = new TH2D(Form("H%d%d", iC, iT), ";;Response", 100, 0, 0.3, 100, 0, 2);
         Hs[iC][iT]->SetTitle(Form("PT = [%.0f, %.0f]", Cs[iC].PTMin, Cs[iC].PTMax));
         if(iT > 0)
            Hs[iC][iT]->GetXaxis()->SetTitle(Form("Fraction (PF PT = %.2f-%.2f GeV)", Ts[iT-1], Ts[iT]));
         else
            Hs[iC][iT]->GetXaxis()->SetTitle(Form("Fraction (PF PT < %.2f GeV)", Ts[iT]));
      }
   }

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(EntryCount < 200 || (iE % (EntryCount / 100)) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      for(int iJ = 0; iJ < NGenJets; iJ++)
      {
         if(MatchedJetAngle[iJ] > DRMax)
            continue;

         double R = MatchedJetPT[iJ] / GenJetPT[iJ];
         double RawPT = MatchedJetPT[iJ] / MatchedJetJEC[iJ];

         double F10 = MatchedJetSF10[iJ] / RawPT;
         double F15 = MatchedJetSF15[iJ] / RawPT;
         double F20 = MatchedJetSF20[iJ] / RawPT;
         double F25 = MatchedJetSF25[iJ] / RawPT;
         double F30 = MatchedJetSF30[iJ] / RawPT;

         TreeR = R;
         TreePT = GenJetPT[iJ];
         TreeW = GenJetWeight[iJ];
         TreeF10 = F10;
         TreeF15 = F15 - F10;
         TreeF20 = F20 - F15;
         TreeF25 = F25 - F20;
         TreeF30 = F30 - F25;
         OutputTree.Fill();

         for(int iC = 0; iC < NC; iC++)
         {
            if(GenJetPT[iJ] < Cs[iC].PTMin)
               continue;
            if(GenJetPT[iJ] > Cs[iC].PTMax)
               continue;
            
            Hs[iC][0]->Fill(F10, R, GenJetWeight[iJ]);
            Hs[iC][1]->Fill(F15 - F10, R, GenJetWeight[iJ]);
            Hs[iC][2]->Fill(F20 - F15, R, GenJetWeight[iJ]);
            Hs[iC][3]->Fill(F25 - F20, R, GenJetWeight[iJ]);
            Hs[iC][4]->Fill(F30 - F25, R, GenJetWeight[iJ]);
            Hs[iC][5]->Fill(1 - F30, R, GenJetWeight[iJ]);
            
            Ps[iC][0]->Fill(F10, R, GenJetWeight[iJ]);
            Ps[iC][1]->Fill(F15 - F10, R, GenJetWeight[iJ]);
            Ps[iC][2]->Fill(F20 - F15, R, GenJetWeight[iJ]);
            Ps[iC][3]->Fill(F25 - F20, R, GenJetWeight[iJ]);
            Ps[iC][4]->Fill(F30 - F25, R, GenJetWeight[iJ]);
            Ps[iC][5]->Fill(1 - F30, R, GenJetWeight[iJ]);
         }
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   for(int iC = 0; iC < NC; iC++)
   {
      for(int iT = 0; iT < NT; iT++)
      {
         TF1 F(Form("F%d%d", iC, iT), "pol1");
         Ps[iC][iT]->Fit(&F);
         Ps[iC][iT]->SetStats(0);
         PdfFile.AddPlot(Ps[iC][iT]);
         PdfFile.AddPlot(Hs[iC][iT], "colz");
      }
   }

   OutputFile.cd();
   OutputTree.Write();
   OutputFile.Close();

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



