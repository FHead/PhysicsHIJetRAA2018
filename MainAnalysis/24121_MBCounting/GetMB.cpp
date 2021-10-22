#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "CustomAssert.h"
#include "DataHelper.h"

int main(int argc, char *argv[]);
vector<pair<int, int>> ParseJSON(string JSONFileName);
void CheckMBFile(string MBFileName, vector<string> &HLTMatch, vector<string> &L1Match,
   vector<pair<int, int>> &Lumis, int Raw[100], int HLT[100], int Final[100], double FinalW2[100]);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   
   string JSONFileName      = CL.Get("JSON");
   string MB1FileName       = CL.Get("MB1");
   vector<string> HLTMatch1 = CL.GetStringVector("HLTMatch1");
   vector<string> L1Match1  = CL.GetStringVector("L1Match1");
   string MB2FileName       = CL.Get("MB2");
   vector<string> HLTMatch2 = CL.GetStringVector("HLTMatch2");
   vector<string> L1Match2  = CL.GetStringVector("L1Match2");
   string MB3FileName       = CL.Get("MB3");
   vector<string> HLTMatch3 = CL.GetStringVector("HLTMatch3");
   vector<string> L1Match3  = CL.GetStringVector("L1Match3");

   string DHFileName        = CL.Get("DHFile", "GlobalSetting.dh");
   string State             = CL.Get("State", "MBCount");
   string Tag               = CL.Get("Tag");
   string CentralityTag     = CL.Get("CentralityTag");

   vector<pair<int, int>> Lumis = ParseJSON(JSONFileName);

   int Count[100] = {0};
   int HLTWeightedCount[100] = {0};
   int WeightedCount[100] = {0};
   double FinalW2[100] = {0};

   CheckMBFile(MB1FileName, HLTMatch1, L1Match1, Lumis, Count, HLTWeightedCount, WeightedCount, FinalW2);
   CheckMBFile(MB2FileName, HLTMatch2, L1Match2, Lumis, Count, HLTWeightedCount, WeightedCount, FinalW2);
   CheckMBFile(MB3FileName, HLTMatch3, L1Match3, Lumis, Count, HLTWeightedCount, WeightedCount, FinalW2);

   // for(int iC = 0; iC < 100; iC++)
   //    cout << iC << " " << Count[iC] << " " << HLTWeightedCount[iC] << " " << WeightedCount[iC] << endl;

   string LumiNotFound = "";

   if(Lumis.size() > 0)
   {
      cout << "Lumis in JSON but not found in MB file (or present in MB file but count = 0):" << endl;
      for(int iL = 0; iL < Lumis.size(); iL++)
      {
         cout << "(" << Lumis[iL].first << ", " << Lumis[iL].second << ")" << endl;
         if(iL != 0)
            LumiNotFound = LumiNotFound + ";";
         LumiNotFound = LumiNotFound + "(" + Lumis[iL].first + "," + Lumis[iL].second + ")";
      }
   }
   else
      LumiNotFound = "None";

   DataHelper DHFile(DHFileName);

   int Total = 0, WeightedTotal = 0;
   double W2Total = 0;
   int Min = (int)(DHFile["CentralityMin"][CentralityTag].GetDouble() * 100);
   int Max = (int)(DHFile["CentralityMax"][CentralityTag].GetDouble() * 100);
   for(int iC = Min; iC < Max; iC++)
   {
      Total = Total + Count[iC];
      WeightedTotal = WeightedTotal + WeightedCount[iC];
      W2Total = W2Total + FinalW2[iC];
   }

   DHFile[State][Tag+"_TriggedCount"]  = Total;
   DHFile[State][Tag+"_WeightedCount"] = WeightedTotal;
   DHFile[State][Tag+"_Error"]         = sqrt(W2Total);
   DHFile[State][Tag+"_MissingLumi"]   = LumiNotFound;

   DHFile.SaveToFile();

   return 0;
}

vector<pair<int, int>> ParseJSON(string JSONFileName)
{
   vector<pair<int, int>> Result;
   
   ifstream in(JSONFileName);
   stringstream buffer;
   buffer << in.rdbuf();
   string content(buffer.str());
   in.close();

   for(int i = 0; i < content.size(); i++)
   {
      if(content[i] == ' ')
      {
         content.erase(content.begin() + i);
         i = i - 1;
      }
      else if(content[i] == '\n')
      {
         content.erase(content.begin() + i);
         i = i - 1;
      }
      else if(i > 0 && content[i-1] == ',' && content[i] == '"')
      {
         content[i-1] =  ' ';
         content[i] = '\n';
      }
   }
   for(int i = 0; i < content.size(); i++)
   {
      if(content[i] == '"')   content[i] = ' ';
      if(content[i] == ':')   content[i] = ' ';
      if(content[i] == '[')   content[i] = ' ';
      if(content[i] == ']')   content[i] = ' ';
      if(content[i] == '{')   content[i] = ' ';
      if(content[i] == '}')   content[i] = ' ';
      if(content[i] == ',')   content[i] = ' ';
   }

   // cout << content << endl;

   stringstream str(content);
   while(str)
   {
      char line[10240];
      line[0] = '\0';
      str.getline(line, 10239, '\n');

      if(line[0] == '\0')
         continue;

      stringstream strline(line);

      int Run = -1;
      strline >> Run;

      if(Run < 0)
         continue;

      while(strline)
      {
         int LumiStart = -1;
         int LumiEnd = -1;
         strline >> LumiStart >> LumiEnd;
         if(LumiStart < 0 || LumiEnd < 0)
            continue;

         if(LumiStart > LumiEnd)
            swap(LumiStart, LumiEnd);
         for(int Lumi = LumiStart; Lumi <= LumiEnd; Lumi++)
            Result.push_back(pair<int, int>(Run, Lumi));
      }
   }

   return Result;
}

void CheckMBFile(string MBFileName, vector<string> &HLTMatch, vector<string> &L1Match,
   vector<pair<int, int>> &Lumis, int Raw[100], int HLT[100], int Final[100], double FinalW2[100])
{
   TFile MBFile(MBFileName.c_str());
   TTree *Tree = (TTree *)MBFile.Get("MBCounter/MBTree");

   if(Tree == nullptr)
   {
      MBFile.Close();
      cerr << "MB tree not found in file " << MBFileName << endl;
      return;
   }

   int Run;
   int Lumi;
   vector<string> *Names = nullptr;
   vector<int> *Prescales = nullptr;
   vector<int> *CountC[100] = {nullptr};

   Tree->SetBranchAddress("Run", &Run);
   Tree->SetBranchAddress("Lumi", &Lumi);
   Tree->SetBranchAddress("Names", &Names);
   Tree->SetBranchAddress("Prescales", &Prescales);
   for(int iC = 0; iC < 100; iC++)
      Tree->SetBranchAddress(Form("CountsC%d", iC), &CountC[iC]);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      int NTrigger = Names->size();

      // Check run and lumi
      bool Found = false;
      int LumiIndex = -1;
      for(int iL = 0; iL < Lumis.size(); iL++)
      {
         if(Lumis[iL].first == Run && Lumis[iL].second == Lumi)
         {
            Found = true;
            LumiIndex = iL;
            break;
         }
      }
      if(Found == false)
         continue;

      // Get L1 prescale
      int L1Prescale = 1;
      for(int iT = 0; iT < NTrigger; iT++)
      {
         bool Good = true;

         string Name = Names->at(iT);
         for(int iS = 0; iS < (int)L1Match.size(); iS++)
            if(Name.find(L1Match[iS]) == string::npos)
               Good = false;
         if(Good == false)
            continue;

         L1Prescale = (*Prescales)[iT];
         if(L1Prescale > 0)
            break;
      }

      // Get HLT counts
      int TotalRawCount = 0;
      for(int iT = 0; iT < NTrigger; iT++)
      {
         bool Good = true;

         string Name = Names->at(iT);
         for(int iS = 0; iS < (int)HLTMatch.size(); iS++)
            if(Name.find(HLTMatch[iS]) == string::npos)
               Good = false;
         if(Good == false)
            continue;

         for(int iC = 0; iC < 100; iC++)
         {
            TotalRawCount = TotalRawCount + (*CountC[iC])[iT];

            Raw[iC] = Raw[iC] + (*CountC[iC])[iT];
            HLT[iC] = HLT[iC] + (*CountC[iC])[iT] * (*Prescales)[iT];
            Final[iC] = Final[iC] + (*CountC[iC])[iT] * (*Prescales)[iT] * L1Prescale;
            FinalW2[iC] = Final[iC] + (*CountC[iC])[iT] * (*Prescales)[iT] * (*Prescales)[iT] * L1Prescale * L1Prescale;
         }
      }
      
      // Remove lumi from list if count is nonzero
      if(TotalRawCount > 0)
         Lumis.erase(Lumis.begin() + LumiIndex);
   }
   
   MBFile.Close();
}

