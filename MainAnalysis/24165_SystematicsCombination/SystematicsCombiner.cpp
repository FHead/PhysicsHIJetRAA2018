#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TKey.h"
#include "TH1D.h"

#include "CommandLine.h"
#include "DataHelper.h"

#define MODE_LINEAR 1
#define MODE_RATIO 2

int main(int argc, char *argv[]);
void CopyEssentialHistograms(TFile &FSource, TFile &FDestination);
vector<string> DiscoverVariationList(TFile &F);
bool CopyUncertainty(TFile &FI, TFile &FO, string Name, int Mode, bool First);
bool CombineUncertainty(TFile &F1, TFile &F2, TFile &FO, string Name, int Mode, double Correlation);
void AddQuadrature(TH1D &HTotalPlus, TH1D &HTotalMinus, TH1D &HNominal, TH1D &HVariation);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string FileName1      = CL.Get("File1");
   string FileName2      = CL.Get("File2");
   string OutputFileName = CL.Get("Output");
   string DHFileName     = CL.Get("DHFile");
   string State          = CL.Get("State");

   DataHelper DHFile(DHFileName);

   TFile F1(FileName1.c_str());
   TFile F2(FileName2.c_str());
   TFile FO(OutputFileName.c_str(), "RECREATE");

   CopyEssentialHistograms(F1, FO);

   vector<string> VariationList1 = DiscoverVariationList(F1);
   vector<string> VariationList2 = DiscoverVariationList(F2);

   vector<string> AllVariation;
   AllVariation.insert(AllVariation.end(), VariationList1.begin(), VariationList1.end());
   AllVariation.insert(AllVariation.end(), VariationList2.begin(), VariationList2.end());
   sort(AllVariation.begin(), AllVariation.end());
   AllVariation.erase(unique(AllVariation.begin(), AllVariation.end()), AllVariation.end());

   FO.cd();

   TH1D *HTotalPlus  = (TH1D *)F1.Get("HTotalPlus")->Clone("HTotalPlus");
   TH1D *HTotalMinus = (TH1D *)F1.Get("HTotalMinus")->Clone("HTotalMinus");

   HTotalPlus->Reset();
   HTotalMinus->Reset();

   for(string Name : AllVariation)
   {
      double Correlation = 0;
      if(DHFile[State].Exist(Name+"_Correlation"))
         Correlation = DHFile[State][Name+"_Correlation"].GetDouble();

      bool Combined = CombineUncertainty(F1, F2, FO, Name, MODE_RATIO, Correlation);

      if(Combined == true)
      {
         TH1D *HBase      = (TH1D *)FO.Get((Name + "Base").c_str());
         TH1D *HVariation = (TH1D *)FO.Get(Name.c_str());
         AddQuadrature(*HTotalPlus, *HTotalMinus, *HBase, *HVariation);
      }
   }

   FO.cd();

   HTotalPlus->Write();
   HTotalMinus->Write();

   FO.Close();
   F2.Close();
   F1.Close();

   return 0;
}

void CopyEssentialHistograms(TFile &FSource, TFile &FDestination)
{
   FDestination.cd();

   vector<string> Essential
   {
      "HGenPrimaryBinMin", "HGenPrimaryBinMax", "HGenBinningBinMin", "HGenBinningBinMax",
      "HRecoPrimaryBinMin", "HRecoPrimaryBinMax", "HRecoBinningBinMin", "HRecoBinningBinMax",
      "HMatchedPrimaryBinMin", "HMatchedPrimaryBinMax", "HMatchedBinningBinMin", "HMatchedBinningBinMax"
   };

   for(string S : Essential)
      ((TH1D *)FSource.Get(S.c_str())->Clone(S.c_str()))->Write();
}

vector<string> DiscoverVariationList(TFile &F)
{
   vector<string> Essential
   {
      "HGenPrimaryBinMin", "HGenPrimaryBinMax", "HGenBinningBinMin", "HGenBinningBinMax",
      "HRecoPrimaryBinMin", "HRecoPrimaryBinMax", "HRecoBinningBinMin", "HRecoBinningBinMax",
      "HMatchedPrimaryBinMin", "HMatchedPrimaryBinMax", "HMatchedBinningBinMin", "HMatchedBinningBinMax",
      "HTotalPlus", "HTotalMinus"
   };
   

   vector<string> HistogramList;
   TIter Iter(F.GetListOfKeys());
   for(TKey *Key = (TKey *)Iter(); Key != nullptr; Key = (TKey *)Iter())
   {
      string Name = Key->ReadObj()->GetName();

      // Check if the object is part of the baseline essential objects - ie., not systematics-related
      if(find(Essential.begin(), Essential.end(), Name) != Essential.end())
         continue;

      if(Key->ReadObj()->IsA()->InheritsFrom("TH1") == false)
         continue;

      HistogramList.push_back(Name);
   }

   vector<string> Result;
   for(string Name : HistogramList)
   {
      // not a variation - no base histogram
      if(find(HistogramList.begin(), HistogramList.end(), Name + "Base") == HistogramList.end())
         continue;

      Result.push_back(Name);
   }

   return Result;
}

bool CopyUncertainty(TFile &FI, TFile &FO, string Name, int Mode, bool First)
{
   return false;
   
   // Do nothing at the moment.  Need to think what it means that uncertainty list is different when ratio
}

bool CombineUncertainty(TFile &F1, TFile &F2, TFile &FO, string Name, int Mode, double Correlation)
{
   TH1D *H1     = (TH1D *)F1.Get(Name.c_str());
   TH1D *H1Base = (TH1D *)F1.Get((Name + "Base").c_str());
   TH1D *H2     = (TH1D *)F2.Get(Name.c_str());
   TH1D *H2Base = (TH1D *)F2.Get((Name + "Base").c_str());

   if((H1 == nullptr || H1Base == nullptr) && (H2 == nullptr || H2Base ==  nullptr))   // all invalid!
      return false;

   if(H1 == nullptr || H1Base == nullptr)
      return CopyUncertainty(F2, FO, Name, Mode, false);
   if(H2 == nullptr || H2Base == nullptr)
      return CopyUncertainty(F1, FO, Name, Mode, true);

   FO.cd();

   TH1D *HVariation = (TH1D *)H1->Clone(Name.c_str());
   TH1D *HBase      = (TH1D *)H1Base->Clone((Name + "Base").c_str());

   HVariation->Reset();
   HBase->Reset();

   int N = H1->GetNbinsX();

   for(int i = 1; i <= N; i++)
   {
      double B1 = H1Base->GetBinContent(i);
      double V1 = H1->GetBinContent(i);
      double B2 = H2Base->GetBinContent(i);
      double V2 = H2->GetBinContent(i);

      double B = 0, E1 = 0, E2 = 0;

      if(Mode == MODE_LINEAR)
      {
         B  = B1 + B2;
         E1 = V1 - B1;
         E2 = V2 - B2;
      }
      if(Mode == MODE_RATIO)
      {
         B  = (B2 > 0) ? (B1 / B2) : 0;   // for the time being
         E1 = (B1 > 0) ? (V1 / B1 - 1) : 0;
         E2 = (B2 > 0) ? (V2 / B2 - 1) : 0;
      }

      double E = sqrt(E1 * E1 + E2 * E2 - 2 * Correlation * E1 * E2);
      double V = 0;

      if(Mode == MODE_LINEAR)
         V = B + E;
      if(Mode == MODE_RATIO)
         V = B * (1 + E);

      HBase->SetBinContent(i, B);
      HVariation->SetBinContent(i, V);
   }

   HBase->Write();
   HVariation->Write();

   return true;
}

void AddQuadrature(TH1D &HTotalPlus, TH1D &HTotalMinus, TH1D &HNominal, TH1D &HVariation)
{
   for(int i = 1; i <= HNominal.GetNbinsX(); i++)
   {
      double VN = HNominal.GetBinContent(i);
      double VV = HVariation.GetBinContent(i);

      if(VN == 0)
         continue;

      double Ratio = VV / VN - 1;

      double TotalPlus = HTotalPlus.GetBinContent(i);
      double TotalMinus = HTotalMinus.GetBinContent(i);

      TotalPlus = sqrt(TotalPlus * TotalPlus + Ratio * Ratio);
      TotalMinus = sqrt(TotalMinus * TotalMinus + Ratio * Ratio);

      HTotalPlus.SetBinContent(i, TotalPlus);
      HTotalMinus.SetBinContent(i, -TotalMinus);
   }
}
