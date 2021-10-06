#include <iostream>
using namespace std;

#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TList.h"
#include "TKey.h"
// #include "TIter.h"

int main(int argc, char *argv[])
{
   TFile File("SampleData/OutputAll.root");

   TList *DirList = File.GetListOfKeys();

   TIter DirIter(DirList);

   while(TKey *DirKey = (TKey *)DirIter())
   {
      TObject *Dir = (TObject *)File.Get(DirKey->GetName());
      // cout << Dir->GetName() << " " << Dir->IsA()->GetName() << endl;

      if(string(Dir->IsA()->GetName()) != "TDirectoryFile")
         continue;

      TList *TreeList = ((TDirectoryFile *)Dir)->GetListOfKeys();
      TIter TreeIter(TreeList);

      while(TKey *TreeKey = (TKey *)TreeIter())
      {
         TObject *Tree = (TObject *)((TDirectoryFile *)Dir)->Get(TreeKey->GetName());
         if(string(Tree->IsA()->GetName()) != "TTree")
            continue;

         cout << Dir->GetName() << " - " << Tree->GetName() << ": " << ((TTree *)Tree)->GetZipBytes()
            << " (" << (double)((TTree *)Tree)->GetZipBytes() / 1024 / 1024 << ")" << endl;
      }
   }

   File.Close();

   return 0;
}
