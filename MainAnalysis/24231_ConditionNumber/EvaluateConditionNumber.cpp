#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompSVD.h"

#include "CommandLine.h"
#include "DataHelper.h"

int main(int argc, char *argv[]);
string GuessState(string Name);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string ResponseName  = CL.Get("Response", "HResponse");
   string DHFileName    = CL.Get("DHFile", "ConditionNumber.dh");

   TFile File(InputFileName.c_str());

   TH2D *HResponse = (TH2D *)File.Get("HResponse");
   if(HResponse == nullptr)
   {
      cerr << "Error getting response matrix, exiting." << endl;
      File.Close();
      return -1;
   }

   int NX = HResponse->GetNbinsX() - 1;
   int NY = HResponse->GetNbinsY() - 1;

   TMatrixD M(NX, NY);
   for(int iX = 0; iX < NX; iX++)
      for(int iY = 0; iY < NY; iY++)
         M[iX][iY] = HResponse->GetBinContent(iX + 1, iY + 1);

   TDecompSVD SVD(M);
   TVectorD SingularValues = SVD.GetSig();

   // SingularValues.Print();

   DataHelper DHFile(DHFileName);

   string State = GuessState(InputFileName);

   double Max = 0;
   double Min = 0;

   int N = SingularValues.GetNoElements();
   DHFile[State]["NSingular"] = N;
   for(int i = 0; i < N; i++)
   {
      DHFile[State]["Singular"+to_string(i)] = SingularValues[i];

      if(i == 0)
      {
         Min = SingularValues[i];
         Max = SingularValues[i];
      }
      else
      {
         if(SingularValues[i] < Min)   Min = SingularValues[i];
         if(SingularValues[i] > Max)   Max = SingularValues[i];
      }
   }

   DHFile[State]["ConditionNumber"] = Max / max((double)1e-10, Min);

   DHFile.SaveToFile();

   File.Close();

   return 0;
}

string GuessState(string FileName)
{
   int Location = FileName.find_last_of('/');
   if(Location != string::npos)
      FileName = FileName.substr(Location + 1);
   Location = FileName.find(".root");
   if(Location != string::npos)
      FileName = FileName.substr(0, Location);

   return FileName;
}


