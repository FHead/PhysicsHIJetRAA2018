#include <iostream>
#include <vector>
using namespace std;

#include "TF1.h"

#include "CommandLine.h"
#include "DataHelper.h"

int main(int argc, char *argv[]);
vector<double> ParseList(string List);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string DHFileName        = CL.Get("DHFile", "GlobalSetting.dh");
   string Base              = CL.Get("Base", "R1_Centrality0to10");

   double MinPT             = CL.GetDouble("MinPT");

   bool DoTrigger           = CL.GetBool("DoTrigger", false);
   double TriggerPercentage = CL.GetDouble("TriggerPercentage", 0.99);
   double TriggerTolerance  = CL.GetDouble("TriggerTolerance", 0.001);
   // bool TriggerResolution   = CL.GetBool("TriggerResolutionShift", false);

   double PTBound = MinPT;

   DataHelper DHFile(DHFileName);

   vector<double> GenBins   = ParseList(DHFile["Binning"]["GenPT"].GetString());
   vector<double> RecoBins  = ParseList(DHFile["Binning"]["RecoPT"].GetString());

   // If we decide to look at trigger, evaluate the turn on point
   if(DoTrigger == true)
   {
      string Formula = DHFile["TriggerTurnOn"][Base+"_Formula"].GetString();
      TF1 Function("Function", Formula.c_str(), 0, 1500);
      int N = DHFile["TriggerTurnOn"][Base+"_NParameter"].GetInteger();
      for(int i = 0; i < N; i++)
      {
         Function.SetParameter(i, DHFile["TriggerTurnOn"][Base+"_P"+to_string(i)].GetDouble());
         Function.SetParError(i, DHFile["TriggerTurnOn"][Base+"_E"+to_string(i)].GetDouble());
      }

      double Min = 0;
      double Max = 1;
      while(Function.Eval(Max) < TriggerPercentage)
         Max = Max * 2;
      while(Max - Min > TriggerTolerance)
      {
         if(Function.Eval((Min + Max) / 2) < TriggerPercentage)
            Min = (Min + Max) / 2;
         else
            Max = (Min + Max) / 2;
      }

      if(PTBound < (Min + Max) / 2)
         PTBound = (Min + Max) / 2;
   }

   // Set final output
   int NumberSmaller = 0;
   for(double Value : GenBins)
      if(Value < PTBound)
         NumberSmaller = NumberSmaller + 1;
   DHFile["Binning"]["PTUnderflow_"+Base] = NumberSmaller;

   DHFile.SaveToFile();

   return 0;
}

vector<double> ParseList(string List)
{
   vector<double> Result;

   for(char &c : List)
      if(c == ',')
         c = ' ';

   stringstream str(List);

   while(str)
   {
      double Temp = -1;
      str >> Temp;
      if(Temp > 0)
         Result.push_back(Temp);
   }

   return Result;
}

