#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"

int main(int argc, char *argv[])
{
   TFile File("MergedMB0.root");

   TTree *Tree = (TTree *)File.Get("MBCounter/MBTree");

   int Run, Lumi;
   Tree->SetBranchAddress("Run", &Run);
   Tree->SetBranchAddress("Lumi", &Lumi);

   map<int, vector<int>> Lumis;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);
      // cout << "RunLumi " << Run << " " << Lumi << endl;

      Lumis[Run].push_back(Lumi);
   }
   
   cout << "{";
   for(auto R : Lumis)
   {
      sort(R.second.begin(), R.second.end());
   
      int Before = -1;

      cout << "\"" << R.first << "\":[";
      for(int i = 0; i < R.second.size(); i++)
      {
         int Now = R.second[i];

         if(Before < 0)   // first one
            cout << "[" << Now << ",";
         else
         {
            if(Now != Before + 1)
               cout << Before << "],[" << Now << ",";
         }

         Before = Now;

      }
      cout << Before << "]],";
   }
   cout << "}" << endl;

   File.Close();

   return 0;
}



