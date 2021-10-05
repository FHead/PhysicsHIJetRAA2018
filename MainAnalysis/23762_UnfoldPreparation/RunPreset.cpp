#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "CommandLine.h"

int main(int argc, char *argv[]);
map<string, string> GetBinnings();

int main(int argc, char *argv[])
{
   map<string, string> Binnings = GetBinnings();

   CommandLine CL(argc, argv);
   
   string DataTag            = CL.Get("DataTag");
   string MCTag              = CL.Get("MCTag");
   string Prefix             = CL.Get("Prefix");
   string Suffix             = CL.Get("Suffix");

   string JetShift           = CL.Get("Shift", "0.0");
   string JetSmear           = CL.Get("Smear", "1.025");
   string Flooring           = CL.Get("Flooring", "false");

   vector<string> JetR       = CL.GetStringVector("JetR", {"1", "2", "3", "4", "5", "6", "7", "8", "9"});
   vector<string> Centrality = CL.GetStringVector("Centrality", {"0to10", "10to30", "30to50", "50to90"});

   for(string R : JetR)
   {
      for(string C : Centrality)
      {
         string RC = "R" + R + "_Centrality" + C;
         string MCFile = MCTag + "_" + RC + ".root";
         string DataFile = DataTag + "_" + RC + ".root";

         cout << "time ./Execute --MC " << MCFile << " --Data " << DataFile
            << " --Output Output/" << Prefix << "_" << RC << "_" << Suffix << ".root"
            << " --Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1"
            << " --ObservableGenBins " << Binnings["GenJetPTBins"]
            << " --ObservableRecoBins " << Binnings["RecoJetPTBins"]
            << " --BinningGenBins 0,1 --BinningRecoBins 0,1"
            << " --ObservableUncertaintyShift " << JetShift
            << " --ObservableUncertaintySmear " << JetSmear
            << " --Flooring " << Flooring
            << ";" << endl;
      }
   }

   return 0;
}

map<string, string> GetBinnings()
{
   map<string, string> Binnings;

   Binnings["GenJetPTBins"] = "20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1100,1200,1300,1400,1500";
   Binnings["RecoJetPTBins"] = "20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1100,1200,1300,1400,1500";

   return Binnings;
}

