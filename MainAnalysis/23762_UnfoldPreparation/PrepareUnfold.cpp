#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"

#include "CustomAssert.h"
#include "CommandLine.h"

enum ObservableType {ObservableNone, ObservableJetPT};
enum ObservableStep {Gen, Reco, Matched};

class Messenger;
int main(int argc, char *argv[]);
void FillMinMax(TH1D &HMin1, TH1D &HMax1, TH1D &HMin2, TH1D &HMax2, vector<double> &Bin1, vector<double> &Bin2);

class Messenger
{
private:
   TTree *Tree;
   double                 EventWeight;
   vector<float>         *RecoJetPT;
   vector<float>         *RecoJetEta;
   vector<float>         *RecoJetPhi;
   vector<float>         *RecoJetMass;
   vector<float>         *RecoJetJEC;
   vector<float>         *RecoJetJEU;
   vector<float>         *GenJetPT;
   vector<float>         *GenJetEta;
   vector<float>         *GenJetPhi;
   vector<float>         *GenJetMass;
   vector<float>         *MatchedJetPT;
   vector<float>         *MatchedJetEta;
   vector<float>         *MatchedJetPhi;
   vector<float>         *MatchedJetMass;
   vector<float>         *MatchedJetJEC;
   vector<float>         *MatchedJetJEU;
   vector<float>         *MatchedJetAngle;
   double                 MaxMatchedJetAngle;
public:
   Messenger()              { Initialize(nullptr); }
   Messenger(TTree *Tree)   { Initialize(Tree); }
   Messenger(TFile &File, string TreeName = "UnfoldingTree")
   {
      TTree *Tree = (TTree *)File.Get(TreeName.c_str());
      Initialize(Tree);
   }
   ~Messenger() {}
   void Initialize(TTree *InputTree = nullptr)
   {
      EventWeight = 1;
      RecoJetPT = nullptr;
      RecoJetEta = nullptr;
      RecoJetPhi = nullptr;
      RecoJetMass = nullptr;
      RecoJetJEC = nullptr;
      RecoJetJEU = nullptr;
      GenJetPT = nullptr;
      GenJetEta = nullptr;
      GenJetPhi = nullptr;
      GenJetMass = nullptr;
      MatchedJetPT = nullptr;
      MatchedJetEta = nullptr;
      MatchedJetPhi = nullptr;
      MatchedJetMass = nullptr;
      MatchedJetJEC = nullptr;
      MatchedJetJEU = nullptr;
      MatchedJetAngle = nullptr;
      MaxMatchedJetAngle = -1;

      Tree = InputTree;
      if(Tree == nullptr)
         return;

      Tree->SetBranchAddress("EventWeight", &EventWeight);
      Tree->SetBranchAddress("RecoJetPT", &RecoJetPT);
      Tree->SetBranchAddress("RecoJetEta", &RecoJetEta);
      Tree->SetBranchAddress("RecoJetPhi", &RecoJetPhi);
      Tree->SetBranchAddress("RecoJetMass", &RecoJetMass);
      Tree->SetBranchAddress("RecoJetJEC", &RecoJetJEC);
      Tree->SetBranchAddress("RecoJetJEU", &RecoJetJEU);
      Tree->SetBranchAddress("GenJetPT", &GenJetPT);
      Tree->SetBranchAddress("GenJetEta", &GenJetEta);
      Tree->SetBranchAddress("GenJetPhi", &GenJetPhi);
      Tree->SetBranchAddress("GenJetMass", &GenJetMass);
      Tree->SetBranchAddress("MatchedJetPT", &MatchedJetPT);
      Tree->SetBranchAddress("MatchedJetEta", &MatchedJetEta);
      Tree->SetBranchAddress("MatchedJetPhi", &MatchedJetPhi);
      Tree->SetBranchAddress("MatchedJetMass", &MatchedJetMass);
      Tree->SetBranchAddress("MatchedJetJEC", &MatchedJetJEC);
      Tree->SetBranchAddress("MatchedJetJEU", &MatchedJetJEU);
      Tree->SetBranchAddress("MatchedJetAngle", &MatchedJetAngle);
   }
   void SetMaxMatchedJetAngle(double Value = -1) { MaxMatchedJetAngle = Value; }
   void GetEntry(int Entry)
   {
      if(Tree == nullptr)
         return;

      Tree->GetEntry(Entry);

      if(EventWeight < 0)
         EventWeight = 1;

      if(MaxMatchedJetAngle > 0)
      {
         for(int iJ = 0; iJ < (int)MatchedJetAngle->size(); iJ++)
         {
            if((*MatchedJetAngle)[iJ] < 0 || (*MatchedJetAngle)[iJ] > MaxMatchedJetAngle)
            {
               (*MatchedJetPT)[iJ] = 0;
               (*MatchedJetMass)[iJ] = 0;
            }
         }
      }
   }
   int GetEntries()           { if(Tree != nullptr) return Tree->GetEntries(); return 0;}
   double GetItemCount(ObservableStep Step, ObservableType &Type)
   {
      if(Type == ObservableJetPT && Step == Gen)
         return GenJetPT->size();
      if(Type == ObservableJetPT && Step == Reco)
         return RecoJetPT->size();
      if(Type == ObservableJetPT && Step == Matched)
         return MatchedJetPT->size();
      
      return 0;
   }
   double GetValue(ObservableStep Step, ObservableType &Type, int Index, int Item,
      double Shift = 0, double Smear = 1, double ExtraScale = 1)
   {
      double Value = GetValueNoScale(Step, Type, Index, Item, Shift, Smear);
      if(Value > 0)
         Value = Value * ExtraScale;
      return Value;
   }
   double GetValueNoScale(ObservableStep Step, ObservableType &Type, int Index, int Item,
      double Shift = 0, double Smear = 1)
   {
      if(Type == ObservableJetPT && Step == Gen && Item < GenJetPT->size())
         return (*GenJetPT)[Item];
      if(Type == ObservableJetPT && Step == Reco && Item < RecoJetPT->size())
      {
         double Value = (*RecoJetPT)[Item];
         Value = Value * (1 + Shift * (*RecoJetJEU)[Item] / (*RecoJetJEC)[Item]);
         return Value;
      }
      if(Type == ObservableJetPT && Step == Matched && Item < MatchedJetPT->size())
      {
         double Value = (*MatchedJetPT)[Item];
         Value = Value * (1 + Shift * (*MatchedJetJEU)[Item] / (*MatchedJetJEC)[Item]);
         Value = (Value - (*GenJetPT)[Item]) * Smear + (*GenJetPT)[Item];
         return Value;
      }

      return -1;
   }
   int GetSimpleBin(ObservableStep Step, ObservableType &Type, int Index, int Item, vector<double> &Bins,
      double Shift = 0, double Smear = 1, double ExtraScale = 1, double Min = -99999, double Max = 99999)
   {
      if(Bins.size() == 0)
         return 0;

      double Value = GetValue(Step, Type, Index, Item, Shift, Smear, ExtraScale);
      if(Value < Min || Value > Max)
         return -1;
      for(int i = 0; i < (int)Bins.size(); i++)
         if(Value < Bins[i])
            return i;

      return Bins.size();
   }
   int GetCompositeBin(ObservableStep Step,
      ObservableType &Type1, int Index1, int Item1, vector<double> &Bins1, double Shift1, double Smear1,
         double ExtraScale1, double Min1, double Max1,
      ObservableType &Type2, int Index2, int Item2, vector<double> &Bins2, double Shift2, double Smear2,
         double ExtraScale2, double Min2, double Max2)
   {
      // #1 is the primary binning, and #2 is the additional binning

      int SimpleBin1 = GetSimpleBin(Step, Type1, Index1, Item1, Bins1, Shift1, Smear1, ExtraScale1, Min1, Max1);
      int SimpleBin2 = GetSimpleBin(Step, Type2, Index2, Item2, Bins2, Shift2, Smear2, ExtraScale2, Min2, Max2);

      if(Type2 == ObservableNone)
         return SimpleBin1;

      return SimpleBin2 * (Bins1.size() + 1) + SimpleBin1;
   }
   double GetMatchedAngle(ObservableType Type, int Item)
   {
      if(Item < 0)                          return 999;
      if(Item >= MatchedJetAngle->size())   return 999;
      return (*MatchedJetAngle)[Item];
   }
   double GetEventWeight()
   {
      return EventWeight;
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   string MCFileName     = CL.Get("MC");
   string DataFileName   = CL.Get("Data");
   string OutputFileName = CL.Get("Output");

   vector<double> Default{0.0, 1.0};
   string Primary                 = CL.Get("Observable", "JetP");
   int PrimaryIndex               = CL.GetInt("ObservableIndex", -1);
   vector<double> PrimaryGenBins  = CL.GetDoubleVector("ObservableGenBins", Default);
   vector<double> PrimaryRecoBins = CL.GetDoubleVector("ObservableRecoBins", Default);
   double PrimaryUncertaintyShift = CL.GetDouble("ObservableUncertaintyShift", 0);
   double PrimaryUncertaintySmear = CL.GetDouble("ObservableUncertaintySmear", 1);
   string Binning                 = CL.Get("Binning", "None");
   int BinningIndex               = CL.GetInt("BinningIndex", -1);
   vector<double> BinningGenBins  = CL.GetDoubleVector("BinningGenBins", Default);
   vector<double> BinningRecoBins = CL.GetDoubleVector("BinningRecoBins", Default);
   double BinningUncertaintyShift = CL.GetDouble("BinningUncertaintyShift", 0);
   double BinningUncertaintySmear = CL.GetDouble("BinningUncertaintySmear", 1);
   bool CheckMatchAngle           = CL.GetBool("CheckMatchAngle", true);
   
   double PrimaryGenMin           = CL.GetDouble("ObservableGenMin", -99999);
   double PrimaryGenMax           = CL.GetDouble("ObservableGenMax", +99999);
   double PrimaryRecoMin          = CL.GetDouble("ObservableRecoMin", -99999);
   double PrimaryRecoMax          = CL.GetDouble("ObservableRecoMax", +99999);
   double BinningGenMin           = CL.GetDouble("BinningGenMin", -99999);
   double BinningGenMax           = CL.GetDouble("BinningGenMax", +99999);
   double BinningRecoMin          = CL.GetDouble("BinningRecoMin", -99999);
   double BinningRecoMax          = CL.GetDouble("BinningRecoMax", +99999);

   bool DoFlooring                = CL.GetBool("Flooring", false);

   sort(PrimaryGenBins.begin(), PrimaryGenBins.end());
   sort(PrimaryRecoBins.begin(), PrimaryRecoBins.end());
   sort(BinningGenBins.begin(), BinningGenBins.end());
   sort(BinningRecoBins.begin(), BinningRecoBins.end());

   ObservableType PrimaryType = ObservableNone;
   if(Primary == "JetPT")              PrimaryType = ObservableJetPT;

   ObservableType BinningType = ObservableNone;
   if(Binning == "JetPT")              BinningType = ObservableJetPT;

   if(BinningType == ObservableNone)
   {
      BinningGenBins.clear();
      BinningRecoBins.clear();
   }

   Assert(PrimaryType != ObservableNone, "Primary observable type is none");

   TFile FMC(MCFileName.c_str());
   TFile FData(DataFileName.c_str());
   TFile FOutput(OutputFileName.c_str(), "RECREATE");

   vector<string> ToCopy{"EventCount", "BaselineEventCount", "AllEventCount"};
   for(string S : ToCopy)
   {
      if(FData.Get(S.c_str()) != nullptr)
         FData.Get(S.c_str())->Clone(("Data" + S).c_str())->Write();
      if(FMC.Get(S.c_str()) != nullptr)
         FMC.Get(S.c_str())->Clone(("MC" + S).c_str())->Write();
   }

   int GenBinCount = PrimaryGenBins.size() + 1;
   if(BinningType != ObservableNone)
      GenBinCount = GenBinCount * (BinningGenBins.size() + 1);
   int RecoBinCount = PrimaryRecoBins.size() + 1;
   if(BinningType != ObservableNone)
      RecoBinCount = RecoBinCount * (BinningRecoBins.size() + 1);
   int MatchedBinCount = PrimaryRecoBins.size() + 1;
   if(BinningType != ObservableNone)
      MatchedBinCount = MatchedBinCount * (BinningRecoBins.size() + 1);

   TH1D HMCGen("HMCGen", ";Gen", GenBinCount, 0, GenBinCount);
   TH1D HMCMatched("HMCMatched", ";Matched", MatchedBinCount, 0, MatchedBinCount);
   TH1D HMCMatchedGenBin("HMCMatchedGenBin", ";Matched (Gen)", GenBinCount, 0, GenBinCount);
   TH1D HMCReco("HMCReco", ";Reco", RecoBinCount, 0, RecoBinCount);
   TH1D HMCRecoGenBin("HMCRecoGenBin", ";Reco (Gen)", GenBinCount, 0, GenBinCount);
   TH2D HResponse("HResponse", ";Matched;Gen", MatchedBinCount, 0, MatchedBinCount, GenBinCount, 0, GenBinCount);
   TH1D HDataReco("HDataReco", ";Reco", RecoBinCount, 0, RecoBinCount);

   TH1D HGenPrimaryBinMin("HGenPrimaryBinMin", ";Gen;Min", GenBinCount, 0, GenBinCount);
   TH1D HGenPrimaryBinMax("HGenPrimaryBinMax", ";Gen;Max", GenBinCount, 0, GenBinCount);
   TH1D HGenBinningBinMin("HGenBinningBinMin", ";Gen;Min", GenBinCount, 0, GenBinCount);
   TH1D HGenBinningBinMax("HGenBinningBinMax", ";Gen;Max", GenBinCount, 0, GenBinCount);
   TH1D HRecoPrimaryBinMin("HRecoPrimaryBinMin", ";Reco;Min", RecoBinCount, 0, RecoBinCount);
   TH1D HRecoPrimaryBinMax("HRecoPrimaryBinMax", ";Reco;Max", RecoBinCount, 0, RecoBinCount);
   TH1D HRecoBinningBinMin("HRecoBinningBinMin", ";Reco;Min", RecoBinCount, 0, RecoBinCount);
   TH1D HRecoBinningBinMax("HRecoBinningBinMax", ";Reco;Max", RecoBinCount, 0, RecoBinCount);
   TH1D HMatchedPrimaryBinMin("HMatchedPrimaryBinMin", ";Matched;Min", MatchedBinCount, 0, MatchedBinCount);
   TH1D HMatchedPrimaryBinMax("HMatchedPrimaryBinMax", ";Matched;Max", MatchedBinCount, 0, MatchedBinCount);
   TH1D HMatchedBinningBinMin("HMatchedBinningBinMin", ";Matched;Min", MatchedBinCount, 0, MatchedBinCount);
   TH1D HMatchedBinningBinMax("HMatchedBinningBinMax", ";Matched;Max", MatchedBinCount, 0, MatchedBinCount);

   FillMinMax(HGenPrimaryBinMin, HGenPrimaryBinMax, HGenBinningBinMin,
      HGenBinningBinMax, PrimaryGenBins, BinningGenBins);
   FillMinMax(HRecoPrimaryBinMin, HRecoPrimaryBinMax, HRecoBinningBinMin,
      HRecoBinningBinMax, PrimaryRecoBins, BinningRecoBins);
   FillMinMax(HMatchedPrimaryBinMin, HMatchedPrimaryBinMax, HMatchedBinningBinMin,
      HMatchedBinningBinMax, PrimaryRecoBins, BinningRecoBins);

   Messenger MMC(FMC);
   if(CheckMatchAngle == true)
      MMC.SetMaxMatchedJetAngle(0.2);
   int EntryCount = MMC.GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MMC.GetEntry(iE);

      int NJet = MMC.GetItemCount(Gen, PrimaryType);
      for(int iJ = 0; iJ < NJet; iJ++)
      {
         int GenBin = MMC.GetCompositeBin(Gen,
            PrimaryType, PrimaryIndex, iJ, PrimaryGenBins, 0, 1, 1, PrimaryGenMin, PrimaryGenMax,
            BinningType, BinningIndex, iJ, BinningGenBins, 0, 1, 1, BinningGenMin, BinningGenMax);
         HMCGen.Fill(GenBin, MMC.GetEventWeight());
      }

      ObservableType PrimaryMatrixType = PrimaryType;
      ObservableType BinningMatrixType = BinningType;

      NJet = MMC.GetItemCount(Gen, PrimaryMatrixType);
      for(int iJ = 0; iJ < NJet; iJ++)
      {
         double Angle = MMC.GetMatchedAngle(PrimaryMatrixType, iJ);
         if(CheckMatchAngle == true && (Angle > 0.2 || Angle < 0))
            continue;

         int GenBin = MMC.GetCompositeBin(Gen,
            PrimaryMatrixType, PrimaryIndex, iJ, PrimaryGenBins, 0, 1, 1, PrimaryGenMin, PrimaryGenMax,
            BinningMatrixType, BinningIndex, iJ, BinningGenBins, 0, 1, 1, BinningGenMin, BinningGenMax);
         int MatchedBin = MMC.GetCompositeBin(Matched,
            PrimaryMatrixType, PrimaryIndex, iJ, PrimaryRecoBins, PrimaryUncertaintyShift, PrimaryUncertaintySmear, 1,
               PrimaryRecoMin, PrimaryRecoMax,
            BinningMatrixType, BinningIndex, iJ, BinningRecoBins, BinningUncertaintyShift, BinningUncertaintySmear, 1,
               BinningRecoMin, BinningRecoMax);
        
         int MatchedGenBin = MMC.GetCompositeBin(Matched,
            PrimaryMatrixType, PrimaryIndex, iJ, PrimaryGenBins, PrimaryUncertaintyShift, PrimaryUncertaintySmear, 1,
               PrimaryGenMin, PrimaryGenMax,
            BinningMatrixType, BinningIndex, iJ, BinningGenBins, BinningUncertaintyShift, BinningUncertaintySmear, 1,
               BinningGenMin, BinningGenMax);

         HMCMatched.Fill(MatchedBin, MMC.GetEventWeight());
         // HResponse.Fill(MatchedBin, GenBin, MMC.GetEventWeight());
         HResponse.Fill(MatchedBin, GenBin);

         HMCMatchedGenBin.Fill(MatchedGenBin, MMC.GetEventWeight());
      }

      NJet = MMC.GetItemCount(Reco, PrimaryType);
      for(int iJ = 0; iJ < NJet; iJ++)
      {
         int RecoBin = MMC.GetCompositeBin(Reco,
            PrimaryType, PrimaryIndex, iJ, PrimaryRecoBins, 0, 1, 1, PrimaryRecoMin, PrimaryRecoMax,
            BinningType, BinningIndex, iJ, BinningRecoBins, 0, 1, 1, BinningRecoMin, BinningRecoMax);
         HMCReco.Fill(RecoBin, MMC.GetEventWeight());
         
         int RecoGenBin = MMC.GetCompositeBin(Reco,
            PrimaryType, PrimaryIndex, iJ, PrimaryGenBins, 0, 1, 1, PrimaryGenMin, PrimaryGenMax,
            BinningType, BinningIndex, iJ, BinningGenBins, 0, 1, 1, BinningGenMin, BinningGenMax);
         HMCRecoGenBin.Fill(RecoGenBin, MMC.GetEventWeight());
      }
   }

   if(DoFlooring == true)
   {
      for(int i = 1; i <= HResponse.GetNbinsX(); i++)
         for(int j = 1; j <= HResponse.GetNbinsY(); j++)
            if(HResponse.GetBinContent(i, j) == 0)
               HResponse.SetBinContent(i, j, 0.5);
   }

   Messenger MData(FData);
   EntryCount = MData.GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MData.GetEntry(iE);

      int NJet = MData.GetItemCount(Reco, PrimaryType);
      for(int iJ = 0; iJ < NJet; iJ++)
      {
         int RecoBin = MData.GetCompositeBin(Reco,
            PrimaryType, PrimaryIndex, iJ, PrimaryRecoBins, 0, 1, 1, PrimaryRecoMin, PrimaryRecoMax,
            BinningType, BinningIndex, iJ, BinningRecoBins, 0, 1, 1, BinningRecoMin, BinningRecoMax);
         HDataReco.Fill(RecoBin, MData.GetEventWeight());
      }
   }

   FOutput.cd();
   HMCGen.Write();
   HMCMatched.Write();
   HMCMatchedGenBin.Write();
   HMCReco.Write();
   HMCRecoGenBin.Write();
   HResponse.Write();
   HDataReco.Write();
   HGenPrimaryBinMin.Write();
   HGenPrimaryBinMax.Write();
   HGenBinningBinMin.Write();
   HGenBinningBinMax.Write();
   HRecoPrimaryBinMin.Write();
   HRecoPrimaryBinMax.Write();
   HRecoBinningBinMin.Write();
   HRecoBinningBinMax.Write();
   HMatchedPrimaryBinMin.Write();
   HMatchedPrimaryBinMax.Write();
   HMatchedBinningBinMin.Write();
   HMatchedBinningBinMax.Write();

   FOutput.Close();
   FData.Close();
   FMC.Close();

   return 0;
}

void FillMinMax(TH1D &HMin1, TH1D &HMax1, TH1D &HMin2, TH1D &HMax2, vector<double> &Bin1, vector<double> &Bin2)
{
   for(int iP = 0; iP <= Bin1.size(); iP++)
   {
      for(int iB = 0; iB <= Bin2.size(); iB++)
      {
         int Bin = iB * (Bin1.size() + 1) + iP + 1;

         if(iP == 0)
            HMin1.SetBinContent(Bin, -999);
         else
            HMin1.SetBinContent(Bin, Bin1[iP-1]);
         
         if(iP >= Bin1.size())
            HMax1.SetBinContent(Bin, 999);
         else
            HMax1.SetBinContent(Bin, Bin1[iP]);

         if(iB == 0)
            HMin2.SetBinContent(Bin, -999);
         else
            HMin2.SetBinContent(Bin, Bin2[iB-1]);
         
         if(iB >= Bin2.size())
            HMax2.SetBinContent(Bin, 999);
         else
            HMax2.SetBinContent(Bin, Bin2[iB]);
      }
   }
}


