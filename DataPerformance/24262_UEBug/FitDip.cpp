#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "CommandLine.h"
#include "DataHelper.h"

class FitDip;
int main(int argc, char *argv[]);

class FitDip
{
public:
   vector<double> EtaPass;
   vector<double> EtaNoPass;
public:
   string GetFunction()
   {
      return "([0]-[1]*exp(-(x-[2])**2/[3]**2))";
   }
   double EvaluateFunction(double x, double P0, double P1, double P2, double P3)
   {
      return P0 - P1 * exp(-(x - P2) * (x - P2) / P3 / P3);
   }
   vector<double> FitFunction()
   {
      double SumY = EtaPass.size();
      double N = EtaPass.size() + EtaNoPass.size();
      double SumStar = 0;
      double SumStar2 = 0;
      double SumYStar = 0;

      for(double Eta : EtaPass)
      {
         double Star = exp(-(Eta - 1.45) * (Eta - 1.45) / (0.052 * 0.052));
         SumStar  = SumStar + Star;
         SumStar2 = SumStar2 + Star * Star;
         SumYStar = SumYStar + Star;
      }
      for(double Eta : EtaNoPass)
      {
         double Star = exp(-(Eta - 1.45) * (Eta - 1.45) / (0.052 * 0.052));
         SumStar  = SumStar + Star;
         SumStar2 = SumStar2 + Star * Star;
      }

      cout << SumY << " " << N << " " << SumStar << " " << SumStar2 << " " << SumYStar << endl;

      double P0 = (SumStar2 * SumY - SumStar * SumYStar) / (SumStar2 * N - SumStar * SumStar);
      double P1 = (N * P0 - SumY) / SumStar;

      return {P0, P1, 1.45, 0.052};
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   double CentralityMin = CL.GetDouble("CentralityMin", 0);
   double CentralityMax = CL.GetDouble("CentralityMax", 1);
   double PTMin         = CL.GetDouble("PTMin", 150);
   double PTMax         = CL.GetDouble("PTMax", 1000);
   double PhiMin        = CL.GetDouble("PhiMin", 2.0);
   double PhiMax        = CL.GetDouble("PhiMax", -2.0);
   string DHFileName    = CL.Get("DHFile");
   string State         = CL.Get("DHState");

   while(PhiMin > +M_PI)   PhiMin = PhiMin - 2 * M_PI;
   while(PhiMin < -M_PI)   PhiMin = PhiMin + 2 * M_PI;
   while(PhiMax > +M_PI)   PhiMax = PhiMax - 2 * M_PI;
   while(PhiMax < -M_PI)   PhiMax = PhiMax + 2 * M_PI;
   if(PhiMin > PhiMax)     PhiMax = PhiMax + 2 * M_PI;

   TFile InputFile(InputFileName.c_str());

   FitDip Fit;

   TTree *Tree = (TTree *)InputFile.Get("TriggerTree");

   float Centrality;
   float JetPT, JetEta, JetPhi;
   bool PassTrigger;
   Tree->SetBranchAddress("Centrality", &Centrality);
   Tree->SetBranchAddress("JetPT", &JetPT);
   Tree->SetBranchAddress("JetEta", &JetEta);
   Tree->SetBranchAddress("JetPhi", &JetPhi);
   Tree->SetBranchAddress("PassTrigger", &PassTrigger);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(Centrality < CentralityMin)   continue;
      if(Centrality > CentralityMax)   continue;

      if(JetPT < PTMin)   continue;
      if(JetPT > PTMax)   continue;

      bool InPhi = false;
      if(JetPhi + 0 * M_PI >= PhiMin && JetPhi + 0 * M_PI <= PhiMax)   InPhi = true;
      if(JetPhi + 2 * M_PI >= PhiMin && JetPhi + 2 * M_PI <= PhiMax)   InPhi = true;
      if(InPhi == false)
         continue;

      if(PassTrigger == true)
         Fit.EtaPass.push_back(fabs(JetEta));
      else
         Fit.EtaNoPass.push_back(fabs(JetEta));
   }

   vector<double> Result = Fit.FitFunction();

   cout << Result[0] << " " << Result[1] << " " << Result[2] << " " << Result[3] << endl;

   DataHelper DHFile(DHFileName);
   DHFile[State]["N"] = (int)Result.size();
   DHFile[State]["Formula"] = Fit.GetFunction();
   for(int i = 0; i < (int)Result.size(); i++)
      DHFile[State]["P"+to_string(i)] = Result[i];
   DHFile.SaveToFile();

   InputFile.Close();

   return 0;
}



