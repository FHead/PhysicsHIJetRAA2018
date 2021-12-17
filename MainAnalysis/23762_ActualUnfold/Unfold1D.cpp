#include <iostream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TMatrixD.h"
#include "TError.h"
#include "TSpline.h"
#include "TGraph.h"

#include "RooUnfold.h"
#include "RooUnfoldInvert.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldSvd.h"
#include "TUnfoldDensity.h"

#include "RootUtilities.h"
#include "CommandLine.h"

int main(int argc, char *argv[]);
vector<double> DetectBins(TH1D *HMin, TH1D *HMax);
void RemoveOutOfRange(TH1D *H);
void RemoveOutOfRange(TH2D *HResponse);
void ReweightResponse(TH2D *HResponse, TH1D *HPrior);
TH1D *ConstructPriorCopy(TH1D *HMC);
TH1D *ConstructPriorCopyExternal(string FileName, string HistName);
TH1D *ConstructPriorFlat(vector<double> GenBins);
TH1D *ConstructPriorPower(vector<double> GenBins, double K);
void DoProjection(TH2D *HResponse, TH1D **HGen, TH1D **HReco);
TH1D *ForwardFold(TH1 *HGen, TH2D *HResponse);

int main(int argc, char *argv[])
{
   SilenceRoot();

   CommandLine CL(argc, argv);

   string InputFileName    = CL.Get("Input",             "Input/DataJetPNominal.root");
   string DataName         = CL.Get("InputName",         "HDataReco");
   string ResponseName     = CL.Get("ResponseName",      "HResponse");
   string ResponseTruth    = CL.Get("ResponseTruth",     "HMCGen");
   string ResponseMeasured = CL.Get("ResponseMeasured",  "HMCReco");
   string Output           = CL.Get("Output",            "Unfolded.root");
   string PriorChoice      = CL.Get("Prior",             "MC");
   bool DoBayes            = CL.GetBool("DoBayes",       true);
   bool DoSVD              = CL.GetBool("DoSVD",         true);
   bool DoInvert           = CL.GetBool("DoInvert",      true);
   bool DoTUnfold          = CL.GetBool("DoTUnfold",     true);
   bool DoFoldNormalize    = CL.GetBool("FoldNormalize", false);
   bool DoToyError         = CL.GetBool("DoToyError",    false);
   
   RooUnfold::ErrorTreatment ErrorChoice = RooUnfold::kErrors;
   if(DoToyError == true)
      ErrorChoice = RooUnfold::kCovToy;

   TFile InputFile(InputFileName.c_str());

   TH1D *HMeasured = (TH1D *)InputFile.Get(ResponseMeasured.c_str());
   TH1D *HTruth    = (TH1D *)InputFile.Get(ResponseTruth.c_str());
   TH2D *HResponse = (TH2D *)InputFile.Get(ResponseName.c_str());
   TH2D *HRawResponse = (TH2D *)HResponse->Clone("HRawResponse");

   TH1D *HInput    = (TH1D *)InputFile.Get(DataName.c_str())->Clone();

   RemoveOutOfRange(HMeasured);
   RemoveOutOfRange(HTruth);
   RemoveOutOfRange(HResponse);
   RemoveOutOfRange(HInput);

   TH1D *HPrior = nullptr;
   if(PriorChoice == "MC")
      HPrior = ConstructPriorCopy(HTruth);
   else if(PriorChoice == "ExternalMC")
   {
      string ExternalMCPriorFileName = CL.Get("ExternalPriorFile");
      HPrior = ConstructPriorCopyExternal(ExternalMCPriorFileName, ResponseTruth);
   }
   else if(PriorChoice == "External")
   {
      string ExternalPriorFileName  = CL.Get("ExternalPriorFile");
      string ExternalPriorHistogram = CL.Get("ExternalPriorHistogram");
      HPrior = ConstructPriorCopyExternal(ExternalPriorFileName, ExternalPriorHistogram);
   }
   else if(PriorChoice == "Flat")
   {
      vector<double> GenBins = DetectBins((TH1D *)InputFile.Get("HGenPrimaryBinMin"),
                                          (TH1D *)InputFile.Get("HGenPrimaryBinMax"));
      GenBins[0] = GenBins[1] - 5;
      GenBins[GenBins.size()-1] = GenBins[GenBins.size()-2] + 1;
      HPrior = ConstructPriorFlat(GenBins);
   }
   else if(PriorChoice == "Power")
   {
      vector<double> GenBins = DetectBins((TH1D *)InputFile.Get("HGenPrimaryBinMin"),
                                          (TH1D *)InputFile.Get("HGenPrimaryBinMax"));
      GenBins[0] = GenBins[1] - 5;
      GenBins[GenBins.size()-1] = GenBins[GenBins.size()-2] + 1;
      double PriorK = CL.GetDouble("PriorK", -5);
      HPrior = ConstructPriorPower(GenBins, PriorK);
   }
   else if(PriorChoice == "Original")
   {
      TH1D *HProjected = nullptr;
      DoProjection(HResponse, &HPrior, &HProjected);
   }
   else
   {
      cout << "Unsupported prior option \"" << PriorChoice << "\"!" << endl;
      return -1;
   }

   ReweightResponse(HResponse, HPrior);

   TH1D *HGen = nullptr;
   TH1D *HReco = nullptr;
   DoProjection(HResponse, &HGen, &HReco);

   // cout << HGen << endl;

   vector<TH1 *> HUnfolded;
   vector<TH1 *> HRefolded;
   vector<TGraph *> Graphs;
   vector<TSpline *> Splines;
   map<string, TMatrixD> Covariance;

   RooUnfoldResponse *Response = new RooUnfoldResponse(HReco, HGen, HResponse);

   if(DoBayes == true)
   {
      vector<int> Iterations{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 80, 90, 100, 125, 150, 200, 250};
      for(int I : Iterations)
      {
         RooUnfoldBayes BayesUnfold(Response, HInput, I);
         BayesUnfold.SetVerbose(-1);
         HUnfolded.push_back((TH1 *)(BayesUnfold.Hreco(ErrorChoice)->Clone(Form("HUnfoldedBayes%d", I))));
         Covariance.insert(pair<string, TMatrixD>(Form("MUnfoldedBayes%d", I), BayesUnfold.Ereco()));
         TH1D *HFold = ForwardFold(HUnfolded[HUnfolded.size()-1], HResponse);
         HFold->SetName(Form("HRefoldedBayes%d", I));
         HRefolded.push_back(HFold);
      }
   }

   if(DoInvert == true)
   {
      RooUnfoldInvert InvertUnfold(Response, HInput);
      InvertUnfold.SetVerbose(-1);
      HUnfolded.push_back((TH1 *)(InvertUnfold.Hreco(ErrorChoice)->Clone("HUnfoldedInvert")));
      Covariance.insert(pair<string, TMatrixD>("MUnfoldedInvert", InvertUnfold.Ereco()));
      TH1D *HFold = ForwardFold(HUnfolded[HUnfolded.size()-1], HResponse);
      HFold->SetName("HRefoldedInvert");
      HRefolded.push_back(HFold);
   }
   
   if(DoSVD == true)
   {
      vector<double> SVDRegularization{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 80, 90, 100, 125, 150};
      for(double D : SVDRegularization)
      {
         if(D >= HGen->GetNbinsX())
            continue;

         RooUnfoldSvd SVDUnfold(Response, HInput, D);
         SVDUnfold.SetVerbose(-1);
         HUnfolded.push_back((TH1 *)(SVDUnfold.Hreco(ErrorChoice)->Clone(Form("HUnfoldedSVD%.1f", D))));
         Covariance.insert(pair<string, TMatrixD>(Form("MUnfoldedSVD%.1f", D), SVDUnfold.Ereco()));
         TH1D *HFold = ForwardFold(HUnfolded[HUnfolded.size()-1], HResponse);
         HFold->SetName(Form("HRefoldedSVD%.1f", D));
         HRefolded.push_back(HFold);
      }
   }

   if(DoTUnfold == true)
   {
      TUnfoldDensity Unfold((TH2 *)HRawResponse,
         TUnfold::kHistMapOutputVert,
         TUnfold::kRegModeCurvature,
         TUnfold::kEConstraintArea,
         TUnfoldDensity::kDensityModeBinWidth);
      Unfold.SetInput(HInput);

      TSpline *LogTauX, *LogTauY;
      TGraph *LCurve;
      int IBest = Unfold.ScanLcurve(100, 0, 0, &LCurve, &LogTauX, &LogTauY);

      TH1 *H = Unfold.GetOutput("HTUnfold");
      TH2 *HError = Unfold.GetEmatrixInput("HTUnfoldMatrix");
      HUnfolded.push_back(H);

      LCurve->SetName("GTUnfoldLCurve");
      Graphs.push_back(LCurve);

      LogTauX->SetName("STUnfoldTauX");
      LogTauY->SetName("STUnfoldTauY");
      Splines.push_back(LogTauX);
      Splines.push_back(LogTauY);

      double X, Y, T;
      LogTauX->GetKnot(IBest, T, X);
      LogTauY->GetKnot(IBest, T, Y);
      // TGraph *GXY = new TGraph("GTUnfoldXY");
      // GXY->SetPoint(0, X, Y);
      // Graphs.push_back(GXY);
   }

   if(DoFoldNormalize == true)
   {
      int Ignore = CL.GetInt("Ignore", 10);
      for(TH1 *H : HUnfolded)
      {
         TH1D *HFold = ForwardFold(H, HResponse);
         double Scale = HInput->Integral(Ignore, -1) / HFold->Integral(Ignore, -1);
         H->Scale(Scale);
      }
   }

   TFile OutputFile(Output.c_str(), "RECREATE");
   HMeasured->Clone("HMCMeasured")->Write();
   HTruth->Clone("HMCTruth")->Write();
   HResponse->Clone("HMCResponse")->Write();
   Response->Mresponse().Clone("HMCFilledResponse")->Write();
   HInput->Clone("HInput")->Write();
   for(TH1 *H : HUnfolded)     if(H != nullptr)   H->Write();
   for(TH1 *H : HRefolded)     if(H != nullptr)   H->Write();
   for(TGraph *G : Graphs)     if(G != nullptr)   G->Write();
   for(TSpline *S : Splines)   if(S != nullptr)   S->Write();
   for(auto I : Covariance)    I.second.Write(I.first.c_str());

   InputFile.Get("HGenPrimaryBinMin")->Clone()->Write();
   InputFile.Get("HGenPrimaryBinMax")->Clone()->Write();
   InputFile.Get("HGenBinningBinMin")->Clone()->Write();
   InputFile.Get("HGenBinningBinMax")->Clone()->Write();
   InputFile.Get("HRecoPrimaryBinMin")->Clone()->Write();
   InputFile.Get("HRecoPrimaryBinMax")->Clone()->Write();
   InputFile.Get("HRecoBinningBinMin")->Clone()->Write();
   InputFile.Get("HRecoBinningBinMax")->Clone()->Write();
   InputFile.Get("HMatchedPrimaryBinMin")->Clone()->Write();
   InputFile.Get("HMatchedPrimaryBinMax")->Clone()->Write();
   InputFile.Get("HMatchedBinningBinMin")->Clone()->Write();
   InputFile.Get("HMatchedBinningBinMax")->Clone()->Write();

   vector<string> ToCopy
   {
      "MCEventCount", "MCAllEventCount", "MCBaselineEventCount",
      "DataEventCount", "DataAllEventCount", "DataBaselineEventCount"
   };
   for(string S : ToCopy)
      if(InputFile.Get(S.c_str()) != nullptr)
         InputFile.Get(S.c_str())->Clone(S.c_str())->Write();

   HPrior->Clone("HPrior")->Write();

   OutputFile.Close();

   InputFile.Close();

   return 0;
}

vector<double> DetectBins(TH1D *HMin, TH1D *HMax)
{
   if(HMin == nullptr || HMax == nullptr)
      return vector<double>{};

   vector<pair<double, double>> Bins;

   for(int i = 1; i <= HMin->GetNbinsX(); i++)
      Bins.push_back(pair<double, double>(HMin->GetBinContent(i), HMax->GetBinContent(i)));

   sort(Bins.begin(), Bins.end());
   auto iterator = unique(Bins.begin(), Bins.end());
   Bins.erase(iterator, Bins.end());

   vector<double> Result;
   for(auto iterator : Bins)
   {
      if(iterator.second == 999)
         iterator.second = 9999;

      Result.push_back(iterator.first);
      Result.push_back(iterator.second);
   }

   sort(Result.begin(), Result.end());
   auto iterator2 = unique(Result.begin(), Result.end());
   Result.erase(iterator2, Result.end());

   return Result;
}

void RemoveOutOfRange(TH1D *H)
{
   if(H == nullptr)
      return;

   H->SetBinContent(0, 0);
   H->SetBinContent(H->GetNbinsX() + 1, 0);
}

void RemoveOutOfRange(TH2D *HResponse)
{
   if(HResponse == nullptr)
      return;

   int NX = HResponse->GetNbinsX();
   int NY = HResponse->GetNbinsY();

   for(int iX = 0; iX <= NX + 1; iX++)
   {
      HResponse->SetBinContent(iX, 0, 0);
      HResponse->SetBinContent(iX, NY + 1, 0);
   }
   for(int iY = 0; iY <= NY + 1; iY++)
   {
      HResponse->SetBinContent(0, iY, 0);
      HResponse->SetBinContent(NX + 1, iY, 0);
   }
}

void ReweightResponse(TH2D *HResponse, TH1D *HPrior)
{
   if(HResponse == nullptr)
      return;
   if(HPrior == nullptr)
      return;

   HPrior->Scale(1 / HPrior->Integral());

   int NX = HResponse->GetNbinsX();
   int NY = HResponse->GetNbinsY();

   vector<double> Total(NY, 0);
   for(int X = 1; X <= NX; X++)
      for(int Y = 1; Y <= NY; Y++)
         Total[Y-1] = Total[Y-1] + HResponse->GetBinContent(X, Y);
   
   for(int X = 1; X <= NX; X++)
   {
      for(int Y = 1; Y <= NY; Y++)
      {
         if(Total[Y-1] > 0)
            HResponse->SetBinContent(X, Y, HResponse->GetBinContent(X, Y) / Total[Y-1] * HPrior->GetBinContent(Y));
      }
   }
}

TH1D *ConstructPriorCopy(TH1D *HMC)
{
   if(HMC == nullptr)
      return nullptr;

   TH1D *HPrior = (TH1D *)HMC->Clone("HP");
   HPrior->Reset();

   int N = HPrior->GetNbinsX();
   for(int i = 1; i <= N; i++)
      HPrior->SetBinContent(i, HMC->GetBinContent(i));
   HPrior->Scale(1 / HPrior->Integral());

   return HPrior;
}

TH1D *ConstructPriorCopyExternal(string FileName, string HistName)
{
   vector<double> Bins;

   TFile File(FileName.c_str());
   TH1D *H = (TH1D *)File.Get(HistName.c_str());
   // cout << H << " " << FileName << " " << HistName << endl;
   if(H != nullptr)
   {
      for(int i = 1; i <= H->GetNbinsX(); i++)
         Bins.push_back(H->GetBinContent(i));
   }
   File.Close();

   if(Bins.size() == 0)
      return nullptr;

   TH1D *HPrior = new TH1D("HP", "", Bins.size(), 0, Bins.size());
   for(int i = 1; i <= HPrior->GetNbinsX(); i++)
      HPrior->SetBinContent(i, Bins[i-1]);
   return HPrior;
}

TH1D *ConstructPriorFlat(vector<double> GenBins)
{
   int N = GenBins.size() - 1; 
   TH1D *HPrior = new TH1D("HP", "", N, 0, N);

   for(int i = 1; i <= N; i++)
      HPrior->SetBinContent(i, GenBins[i] - GenBins[i-1]);
   HPrior->Scale(1 / HPrior->Integral());

   return HPrior;
}

TH1D *ConstructPriorPower(vector<double> GenBins, double K)
{
   if(K >= -1)   // ugh
      return nullptr;
   
   int N = GenBins.size() - 1;
   TH1D *HPrior = new TH1D("HP", "", N, 0, N);
   
   for(int i = 1; i <= N; i++)
      HPrior->SetBinContent(i, -(pow(GenBins[i], K + 1) - pow(GenBins[i-1], K + 1)));
   HPrior->Scale(1 / HPrior->Integral());

   return HPrior;
}

void DoProjection(TH2D *HResponse, TH1D **HGen, TH1D **HReco)
{
   if(HResponse == nullptr)
      return;
   if((*HGen) != nullptr || (*HReco) != nullptr)
      return;

   static int Count = 0;
   Count = Count + 1;

   int NX = HResponse->GetNbinsX();
   int NY = HResponse->GetNbinsY();

   *HGen = new TH1D(Form("HGen%d", Count), "", NY, 0, NY);
   *HReco = new TH1D(Form("HReco%d", Count), "", NX, 0, NX);

   for(int iX = 1; iX <= NX; iX++)
   {
      for(int iY = 1; iY <= NY; iY++)
      {
         double V = HResponse->GetBinContent(iX, iY);
         (*HGen)->AddBinContent(iY, V);
         (*HReco)->AddBinContent(iX, V);
      }
   }
}

TH1D *ForwardFold(TH1 *HGen, TH2D *HResponse)
{
   if(HGen == nullptr || HResponse == nullptr)
      return nullptr;

   static int Count = 0;
   Count = Count + 1;

   int NGen = HResponse->GetNbinsY();
   int NReco = HResponse->GetNbinsX();

   TH1D *HResult = new TH1D(Form("HFold%d", Count), "", NReco, 0, NReco);

   for(int iG = 1; iG <= NGen; iG++)
   {
      double N = 0;
      for(int iR = 1; iR <= NReco; iR++)
         N = N + HResponse->GetBinContent(iR, iG);

      if(N == 0)
         continue;

      for(int iR = 1; iR <= NReco; iR++)
         HResult->AddBinContent(iR, HResponse->GetBinContent(iR, iG) * HGen->GetBinContent(iG) / N);
   }

   return HResult;
}


