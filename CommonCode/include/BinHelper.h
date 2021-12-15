#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "TH1D.h"

std::vector<double> DetectBins(TH1D *HMin, TH1D *HMax);
std::vector<double> ParseList(std::string List);

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
