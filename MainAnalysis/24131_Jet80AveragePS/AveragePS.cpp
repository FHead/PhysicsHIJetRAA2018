#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "CommandLine.h"
#include "ProgressBar.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string HLTrigger = CL.Get("HLT");
   string L1Trigger = CL.Get("L1");

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get("MBCounter/MBTree");

   vector<string> *Names = nullptr;
   vector<int> *Counts = nullptr;
   vector<int> *Prescales = nullptr;
   Tree->SetBranchAddress("Names", &Names);
   Tree->SetBranchAddress("Counts", &Counts);
   Tree->SetBranchAddress("Prescales", &Prescales);

   int Raw = 0;
   int Scaled = 0;
   
   int EntryCount = Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(4);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0)
         Bar.Print();

      Tree->GetEntry(iE);

      int L1PS = 0;
      for(int iT = 0; iT < (int)Names->size(); iT++)
      {
         if(Names->at(iT) == L1Trigger)
            L1PS = Prescales->at(iT);
      }
      if(L1PS == 0)
         continue;

      for(int iT = 0; iT < (int)Names->size(); iT++)
      {
         if(Names->at(iT).find(HLTrigger) != string::npos)
         {
            int Count = Counts->at(iT);
            int PS = Prescales->at(iT);

            Raw = Raw + Count;
            Scaled = Scaled + Count * PS * L1PS;
         }
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();

   cout << Scaled << "/" << Raw << " = " << (double)Scaled / Raw << endl;

   return 0;
}



