#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

int main(int argc, char *argv[])
{
   TFile File("MergedMB.root");

   TTree *Tree = (TTree *)File.Get("MBCounter/MBTree");

   int Run, Lumi;
   Tree->SetBranchAddress("Run", &Run);
   Tree->SetBranchAddress("Lumi", &Lumi);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);
      cout << Run << " " << Lumi << endl;
   }

   File.Close();

   return 0;
}



