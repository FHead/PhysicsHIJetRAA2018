#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TGraph.h"

#include "CustomAssert.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
TGraphAsymmErrors BuildRAA(string PPFileName, string AAFileName, string Name);
TGraphAsymmErrors BuildSystematics(TGraphAsymmErrors &G, string FileName);
void SetPad(TPad &P);
void SetAxis(TGaxis &A);
void SetWorld(TH2D &H);

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   vector<string> PPInputFileName     = CL.GetStringVector("PP");
   vector<string> AAInputFileName     = CL.GetStringVector("AA");
   vector<string> SystematicsFileName = CL.GetStringVector("Systematics");
   vector<string> Labels              = CL.GetStringVector("Labels");

   int N = PPInputFileName.size();
   Assert((int)AAInputFileName.size() == N,     "Input file count mismatch");
   Assert((int)SystematicsFileName.size() == N, "Systematics file count mismatch");
   Assert((int)Labels.size() == N,              "Label count mismatch");

   string FinalOutputFileName         = CL.Get("FinalOutput", "RAA.pdf");

   double WorldXMin                   = CL.GetDouble("WorldXMin", 150);
   double WorldXMax                   = CL.GetDouble("WorldXMax", 1500);
   double WorldYMin                   = CL.GetDouble("WorldYMin", 0.0);
   double WorldYMax                   = CL.GetDouble("WorldYMax", 1.2);
   bool LogX                          = CL.GetBool("LogX", true);
   bool LogY                          = CL.GetBool("LogY", false);

   string XLabel                      = CL.Get("XLabel", "Jet P (GeV)");
   string YLabel                      = CL.Get("YLabel", "dN / d(Jet P)");

   int XAxisSpacing                   = CL.GetInt("XAxis", 505);
   int YAxisSpacing                   = CL.GetInt("YAxis", 505);

   double PPLumi                      = CL.GetDouble("PPLumi", 1);
   double AALumi                      = CL.GetDouble("AALumi", 1);
   string PPLumiUnit                  = CL.Get("PPLumiUnit", "Bananas");
   string AALumiUnit                  = CL.Get("AALumiUnit", "Bananas");

   double LegendX                     = CL.GetDouble("LegendX", 0.5);
   double LegendY                     = CL.GetDouble("LegendY", 0.5);
   double LegendSize                  = CL.GetDouble("LegendSize", 0.075);

   int PadWidth     = 250;
   int PadHeight    = 250;
   int MarginLeft   = 25;
   int MarginRight  = 25;
   int MarginTop    = 25;
   int MarginBottom = 25;

   double CanvasWidth = MarginLeft + PadWidth + MarginRight;
   double CanvasHeight = MarginTop + PadHeight + MarginBottom;

   double PadDX = PadWidth / CanvasWidth;
   double PadDY = PadHeight / CanvasHeight;
   double PadX0 = MarginLeft / CanvasWidth;
   double PadY0 = MarginBottom / CanvasHeight;

   vector<TGraphAsymmErrors> GRAA(N), GSys(N);
   for(int i = 0; i < N; i++)
   {
      GRAA[i] = BuildRAA(PPInputFileName[i], AAInputFileName[i], "Result0");
      if(SystematicsFileName[i] == "none")
         GSys[i] = BuildRAA(PPInputFileName[i], AAInputFileName[i], "FullSystematics0");
      else
         GSys[i] = BuildSystematics(GRAA[i], SystematicsFileName[i]);
   }

   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   TPad Pad("Pad", "", PadX0, PadY0, PadX0 + PadDX, PadY0 + PadDY);
   if(LogX == true)   Pad.SetLogx();
   if(LogY == true)   Pad.SetLogy();
   SetPad(Pad);

   TGaxis XAxis(PadX0, PadY0, PadX0 + PadDX, PadY0, WorldXMin, WorldXMax, XAxisSpacing, (LogX ? "G" : ""));
   TGaxis YAxis(PadX0, PadY0, PadX0, PadY0 + PadDY, WorldYMin, WorldYMax, YAxisSpacing, (LogY ? "G" : ""));
   SetAxis(XAxis);
   SetAxis(YAxis);

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(22);
   Latex.DrawLatex(PadX0 + PadDX * 0.5, PadY0 * 0.3, XLabel.c_str());
   Latex.SetTextAngle(90);
   Latex.SetTextAlign(22);
   Latex.DrawLatex(PadX0 * 0.3, PadY0 + PadDY * 0.5, YLabel.c_str());

   Latex.SetTextAngle(0);
   Latex.SetTextAlign(11);
   Latex.DrawLatex(PadX0, PadY0 + PadDY + 0.01, "CMS #font[52]{Preliminary}");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(PadX0 + PadDX, PadY0 + PadDY + 0.01,
      Form("pp (PbPb) 5.02 TeV %.1f %s (%.1f %s)", PPLumi, PPLumiUnit.c_str(), AALumi, AALumiUnit.c_str()));
   
   Pad.cd();
   TH2D HWorld("HWorld", "", 100, WorldXMin, WorldXMax, 100, WorldYMin, WorldYMax);
   SetWorld(HWorld);
   HWorld.GetXaxis()->SetNdivisions(XAxisSpacing);
   HWorld.GetYaxis()->SetNdivisions(YAxisSpacing);

   TLegend Legend(LegendX, LegendY, LegendX + 0.3, LegendY + 0.065 * (1 + N));
   Legend.SetTextFont(42);
   Legend.SetTextSize(LegendSize);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   for(int i = 0; i < N; i++)
      Legend.AddEntry(&GSys[i], Labels[i].c_str(), "lfp");

   for(int i = 0; i < N; i++)
   {
      GSys[i].SetLineColor(Colors[i]);
      GSys[i].SetLineWidth(2);
      GSys[i].SetMarkerColor(Colors[i]);
      GSys[i].SetMarkerStyle(20);
      GSys[i].SetMarkerSize(0.75);
      GSys[i].SetFillColorAlpha(Colors[i], 0.25);
      GSys[i].Draw("2");

      GRAA[i].SetLineColor(Colors[i]);
      GRAA[i].SetLineWidth(2);
      GRAA[i].SetMarkerColor(Colors[i]);
      GRAA[i].SetMarkerStyle(20);
      GRAA[i].SetMarkerSize(0.75);
      GRAA[i].Draw("p");
   }

   TGraph G;
   G.SetPoint(0, WorldXMin, 1.0);
   G.SetPoint(1, WorldXMax, 1.0);
   G.Draw("l");

   Legend.Draw();

   Canvas.SaveAs(FinalOutputFileName.c_str());

   return 0;
}

TGraphAsymmErrors BuildRAA(string PPFileName, string AAFileName, string Name)
{
   TGraphAsymmErrors G;

   TFile FPP(PPFileName.c_str());
   TFile FAA(AAFileName.c_str());

   TGraphAsymmErrors *GPP = (TGraphAsymmErrors *)FPP.Get(Name.c_str());
   TGraphAsymmErrors *GAA = (TGraphAsymmErrors *)FAA.Get(Name.c_str());

   if(GPP == nullptr || GAA == nullptr)
   {
      FPP.Close();
      FAA.Close();
      return G;
   }

   for(int i = 0; i < GAA->GetN(); i++)
   {
      double XAA, YAA;
      GAA->GetPoint(i, XAA, YAA);
      double EXLAA, EXHAA, EYLAA, EYHAA;
      EXLAA = GAA->GetErrorXlow(i);
      EXHAA = GAA->GetErrorXhigh(i);
      EYLAA = GAA->GetErrorYlow(i) / YAA;
      EYHAA = GAA->GetErrorYhigh(i) / YAA;

      int I = -1;
      for(int j = 0; j < GPP->GetN(); j++)
      {
         double x, y;
         GPP->GetPoint(j, x, y);
         if(x < XAA + EXHAA && x > XAA - EXLAA)
         {
            I = j;
            break;
         }
      }
      if(I < 0)
         continue;

      double XPP, YPP;
      GPP->GetPoint(I, XPP, YPP);
      double EXLPP, EXHPP, EYLPP, EYHPP;
      EXLPP = GPP->GetErrorXlow(i);
      EXHPP = GPP->GetErrorXhigh(i);
      EYLPP = GPP->GetErrorYlow(i) / YPP;
      EYHPP = GPP->GetErrorYhigh(i) / YPP;

      double RAA = YAA / YPP;

      if(YAA == 0 || YPP == 0)
         continue;

      int P = G.GetN();
      G.SetPoint(P, XAA, RAA);
      G.SetPointError(P, EXLAA, EXHAA,
         RAA * sqrt(EYLAA * EYLAA + EYLPP * EYLPP),
         RAA * sqrt(EYHAA * EYHAA + EYHPP * EYHPP));
   }

   FAA.Close();
   FPP.Close();

   return G;
}

TGraphAsymmErrors BuildSystematics(TGraphAsymmErrors &G, string FileName)
{
   int N = G.GetN();
   TGraphAsymmErrors Result(N);

   TFile File(FileName.c_str());

   TH1D *HMin = (TH1D *)File.Get("HGenPrimaryBinMin");
   TH1D *HMax = (TH1D *)File.Get("HGenPrimaryBinMax");

   TH1D *HPlus = (TH1D *)File.Get("HTotalPlus");
   TH1D *HMinus = (TH1D *)File.Get("HTotalMinus");

   bool FileOK = true;
   if(HMin == nullptr)     FileOK = false;
   if(HMax == nullptr)     FileOK = false;
   if(HPlus == nullptr)    FileOK = false;
   if(HMinus == nullptr)   FileOK = false;

   if(FileOK == false)
   {
      cout << "Systematic file \"" << FileName << "\" not good!" << endl;
      cout << "Proceed without uncertainty..." << endl;
   }

   for(int i = 0; i < N; i++)
   {
      double X = G.GetPointX(i);
      double Y = G.GetPointY(i);
      double EXL = G.GetErrorXlow(i);
      double EXH = G.GetErrorXhigh(i);

      double EYL = 0;
      double EYH = 0;

      if(FileOK == true)
      {
         for(int j = 1; j <= HMin->GetNbinsX(); j++)
         {
            if(X >= HMin->GetBinContent(j) && X < HMax->GetBinContent(j))
            {
               EYL = HPlus->GetBinContent(j) * Y;
               EYH = -HMinus->GetBinContent(j) * Y;
               break;
            }
         }
      }

      Result.SetPoint(i, X, Y);
      Result.SetPointError(i, EXL, EXH, EYL, EYH);
   }

   File.Close();

   return Result;
}

void SetPad(TPad &P)
{
   P.SetLeftMargin(0);
   P.SetTopMargin(0);
   P.SetRightMargin(0);
   P.SetBottomMargin(0);
   P.SetTickx();
   P.SetTicky();
   P.Draw();
}

void SetAxis(TGaxis &A)
{
   A.SetLabelFont(42);
   A.SetLabelSize(0.030);
   A.SetMaxDigits(6);
   A.SetMoreLogLabels();
   // A.SetNoExponent();
   A.Draw();
}

void SetWorld(TH2D &H)
{
   H.SetStats(0);
   H.Draw("axis");
}

