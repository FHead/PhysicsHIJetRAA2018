#include <iostream>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "DataHelper.h"
#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "RootUtilities.h"
#include "BinHelper.h"

int main(int argc, char *argv[]);
double GetDistance(TH1D *H1, TH1D *H2, int Ignore = 0);

int main(int argc, char *argv[])
{
   SetThesisStyle();
   CommandLine CL(argc, argv);

   string InputFileName  = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   int GenPointToIgnore  = CL.GetInt("Ignore");
   int RecoPointToIgnore = CL.GetInt("IgnoreReco", 0);

   string Reference      = CL.Get("Reference", "HMCTruth");
   string RecoReference  = CL.Get("ReferenceReco", "HInput");

   vector<int> Iterations = ListIterations(InputFileName);

   TFile File(InputFileName.c_str());

   TH2D *HResponse = (TH2D *)File.Get("HMCResponse");

   TH1D *HGenReference = (TH1D *)File.Get(Reference.c_str());
   TH1D *HRecoReference = (TH1D *)File.Get(RecoReference.c_str());

   TGraph G;

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("LCurve");

   for(int I : Iterations)
   {
      TH1D *HUnfolded = (TH1D *)File.Get(Form("HUnfoldedBayes%d", I));
      TH1D *HRefolded = ForwardFold(HUnfolded, HResponse);

      HGenReference->Scale(HUnfolded->Integral() / HGenReference->Integral());

      double D1 = GetDistance(HUnfolded, HGenReference);
      double D2 = GetDistance(HRefolded, HRecoReference);

      G.SetPoint(G.GetN(), D1, D2);

      PdfFile.AddTextPage(Form("Iteration %d", I));

      TCanvas Canvas;
      Canvas.SetLogy();

      HUnfolded->Draw("hist");
      HGenReference->Draw("same hist");
      PdfFile.AddCanvas(Canvas);

      HRefolded->Draw("hist");
      HRecoReference->Draw("same hist");
      PdfFile.AddCanvas(Canvas);
   }

   PdfFile.AddPlot(G, "apl", false, false, true, false);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double GetDistance(TH1D *H1, TH1D *H2, int Ignore)
{
   if(H1 == nullptr || H2 == nullptr)
      return 0;

   int N = H1->GetNbinsX();

   double Result = 0;

   for(int i = Ignore; i <= N; i++)
   {
      double V1 = H1->GetBinContent(i);
      double E1 = H1->GetBinError(i);
      double V2 = H2->GetBinContent(i);
      double E2 = H2->GetBinError(i);

      double DV = V1 - V2;
      double DE = E1 * E1 + E2 * E2;
      if(DE > 0)
         Result = Result + DV * DV / DE;

      // if(V2 == 0)
      //    V2 = 1;
      // double R = V1 / V2 - 1;
      // Result = Result + R * R;
   }

   return Result;
}

