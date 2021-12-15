#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"

#include "CommandLine.h"
#include "DataHelper.h"
#include "CustomAssert.h"

#include "JetCorrector.h"
#include "BinHelper.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string DHFileName              = CL.Get("DHFile", "GlobalSetting.dh");
   string Base                    = CL.Get("Base", "R1_Centrality0to10");
   string NominalFile             = CL.Get("NominalFile");

   double MaxPT                   = CL.GetDouble("MaxPT", 99999);

   bool DoRecoStat                = CL.GetBool("DoRecoStat", false);
   double RecoStatLimit           = DoRecoStat ? CL.GetDouble("RecoStatLimit") : 0;
   bool DoRecoStatResolution      = DoRecoStat ? CL.GetBool("DoRecoStatResolution") : false;
   double RecoStatResolutionShift = DoRecoStatResolution ? CL.GetDouble("RecoStatResolutionShift") : 1;
   string ResolutionFile          = DoRecoStatResolution ? CL.Get("ResolutionFile") : "NONE";

   double PTBound = MaxPT;

   DataHelper DHFile(DHFileName);

   vector<double> GenBins         = ParseList(DHFile["Binning"]["GenPT"].GetString());
   vector<double> RecoBins        = ParseList(DHFile["Binning"]["RecoPT"].GetString());
   GenBins.insert(GenBins.begin(), 0);
   GenBins.push_back(99999);
   RecoBins.insert(RecoBins.begin(), 0);
   RecoBins.push_back(99999);

   if(DoRecoStat == true)
   {
      TFile File(NominalFile.c_str());

      TH1D *HReco = (TH1D *)File.Get("HDataReco");
      Assert(HReco != nullptr, "Reco histogram not found");

      int N = HReco->GetNbinsX();
      int FirstBadBin = N;
      for(int i = N; i >= 1; i--)
      {
         if(HReco->GetBinContent(i) >= RecoStatLimit)
            break;
         FirstBadBin = i;
      }

      if(FirstBadBin <= N && FirstBadBin >= 1)   // we found our bin!
      {
         double RecoPTBound = RecoBins[FirstBadBin-1];
         
         if(DoRecoStatResolution == true)
         {
            JetCorrector JER(ResolutionFile);

            JER.SetJetPT(RecoPTBound);
            JER.SetJetEta(0);
            JER.SetJetPhi(0);
            JER.SetRho(0);
            JER.SetJetArea(0.5);

            double Value = JER.GetCorrection();
            RecoPTBound = RecoPTBound * (1 - Value * RecoStatResolutionShift);
         }

         if(RecoPTBound < PTBound)
            PTBound = RecoPTBound;
      }

      File.Close();
   }

   // Set final output
   int NumberLarger = 0;
   for(double Value : GenBins)
      if(Value > PTBound)
         NumberLarger = NumberLarger + 1;
   DHFile["Binning"]["PTOverflow_"+Base] = NumberLarger;
   DHFile["Binning"]["PTOverflowValue_"+Base] = PTBound;

   DHFile.SaveToFile();

   return 0;
}





