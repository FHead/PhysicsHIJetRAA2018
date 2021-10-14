#include <iostream>
using namespace std;

#include "TGraph.h"
#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   string GraphName      = CL.Get("Graph");

   TFile InputFile(InputFileName.c_str());

   TTree *Tree = (TTree *)InputFile.Get("Tree");

   double XMin, XMax, Y, StatMin, StatMax, SysMin, SysMax;
   Tree->SetBranchAddress("XMin", &XMin);
   Tree->SetBranchAddress("XMax", &XMax);
   Tree->SetBranchAddress("Y", &Y);
   Tree->SetBranchAddress("StatMin", &StatMin);
   Tree->SetBranchAddress("StatMax", &StatMax);
   Tree->SetBranchAddress("SysMin", &SysMin);
   Tree->SetBranchAddress("SysMax", &SysMax);

   TFile OutputFile(OutputFileName.c_str(), "UPDATE");

   TGraph G;
   G.SetName(GraphName.c_str());

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);
      G.SetPoint(G.GetN(), XMin, Y);
      G.SetPoint(G.GetN(), XMax, Y);
   }

   OutputFile.cd();
   G.Write();
   OutputFile.Close();

   InputFile.Close();

   return 0;
}




