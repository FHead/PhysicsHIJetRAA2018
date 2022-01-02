#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "TFile.h"
#include "TKey.h"
#include "TH1D.h"
#include "TH2D.h"

std::vector<double> DetectBins(TH1D *HMin, TH1D *HMax);
std::vector<double> ParseList(std::string List);
TH1D *ForwardFold(TH1D *HGen, TH2D *HResponse);
std::vector<int> ListIterations(std::string FileName);
vector<string> DetectVariations(DataHelper &DHFile, string State);

std::vector<double> DetectBins(TH1D *HMin, TH1D *HMax)
{
   if(HMin == nullptr || HMax == nullptr)
      return std::vector<double>{};

   std::vector<std::pair<double, double>> Bins;

   for(int i = 1; i <= HMin->GetNbinsX(); i++)
      Bins.push_back(std::pair<double, double>(HMin->GetBinContent(i), HMax->GetBinContent(i)));

   std::sort(Bins.begin(), Bins.end());
   auto iterator = std::unique(Bins.begin(), Bins.end());
   Bins.erase(iterator, Bins.end());

   std::vector<double> Result;
   for(auto iterator : Bins)
   {
      if(iterator.second == 999)
         iterator.second = 9999;

      Result.push_back(iterator.first);
      Result.push_back(iterator.second);
   }

   std::sort(Result.begin(), Result.end());
   auto iterator2 = std::unique(Result.begin(), Result.end());
   Result.erase(iterator2, Result.end());

   return Result;
}

std::vector<double> ParseList(std::string List)
{
   std::vector<double> Result;

   for(char &c : List)
      if(c == ',')
         c = ' ';

   std::stringstream str(List);

   while(str)
   {
      double Temp = -1;
      str >> Temp;
      if(Temp > 0)
         Result.push_back(Temp);
   }

   return Result;
}

TH1D *ForwardFold(TH1D *HGen, TH2D *HResponse)
{
   if(HGen == nullptr || HResponse == nullptr)
      return nullptr;

   static int Count = 0;
   Count = Count + 1;

   int NGen = HResponse->GetNbinsY();
   int NReco = HResponse->GetNbinsX();

   TH1D *HResult = new TH1D(Form("HFold%d", Count), "", NReco, 0, NReco);
   HResult->Sumw2();

   for(int iG = 1; iG <= NGen; iG++)
   {
      double N = 0;
      for(int iR = 1; iR <= NReco; iR++)
         N = N + HResponse->GetBinContent(iR, iG);

      if(N == 0)
         continue;

      double VG = HGen->GetBinContent(iG);
      double EG = HGen->GetBinError(iG);

      for(int iR = 1; iR <= NReco; iR++)
      {
         double VR = HResult->GetBinContent(iR);
         double ER = HResult->GetBinError(iR);

         double R = HResponse->GetBinContent(iR, iG);

         VR = VR + VG * R / N;
         ER = sqrt(ER * ER + (EG * R / N) * (EG * R / N));

         HResult->SetBinContent(iR, VR);
         HResult->SetBinError(iR, ER);

         // HResult->Fill(iR - 1, HResponse->GetBinContent(iR, iG) * HGen->GetBinContent(iG) / N);
      }
   }

   return HResult;
}

vector<int> ListIterations(string FileName)
{
   vector<int> Result;

   TFile File(FileName.c_str());

   TIter Iter(File.GetListOfKeys());
   for(TKey *Key = (TKey *)Iter(); Key != nullptr; Key = (TKey *)Iter())
   {
      string Name = Key->ReadObj()->GetName();
      if(Name.rfind("HUnfoldedBayes", 0) != 0)
         continue;

      Result.push_back(stoi(Name.substr(14)));
   }

   File.Close();

   return Result;
}

std::vector<std::string> DetectVariations(DataHelper &DHFile, std::string std::State)
{
   std::vector<std::string> Result;

   Assert(DHFile.Exist(State), "State does not exist in the DHFile");

   std::vector<std::string> Keys = DHFile[State].GetListOfKeys();
   for(std::string &Key : Keys)
   {
      int Location = Key.rfind("_");
      if(Location == std::string::npos)   // unrelated
         continue;
      Result.push_back(Key.substr(0, Location));
   }

   sort(Result.begin(), Result.end());
   Result.erase(unique(Result.begin(), Result.end()), Result.end());

   for(int i = 0; i < (int)Result.size(); i++)
   {
      std::string Source = Result[i];

      int ExistCount = 0;
      if(DHFile[State].Exist(Source + "_BaseFile") == true)           ExistCount = ExistCount + 1;
      if(DHFile[State].Exist(Source + "_BaseHistogram") == true)      ExistCount = ExistCount + 1;
      if(DHFile[State].Exist(Source + "_VariantFile") == true)        ExistCount = ExistCount + 1;
      if(DHFile[State].Exist(Source + "_VariantHistogram") == true)   ExistCount = ExistCount + 1;
      if(DHFile[State].Exist(Source + "_Label") == true)              ExistCount = ExistCount + 1;
      if(DHFile[State].Exist(Source + "_Include") == true)            ExistCount = ExistCount + 1;
      if(DHFile[State].Exist(Source + "_Bridging") == true)           ExistCount = ExistCount + 1;
      if(DHFile[State].Exist(Source + "_ExtraScaling") == true)       ExistCount = ExistCount + 1;

      if(ExistCount == 0)   // unrelated stuff
      {
         Result.erase(Result.begin() + i);
         i = i - 1;
         continue;
      }

      if(ExistCount < 8)
         cerr << "Warning: source " << Source << " incomplete!" << endl;
   }

   return Result;
}


