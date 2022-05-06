#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TLatex.h"
#include "TImage.h"

#include "PlotHelper4.h"
#include "CommandLine.h"
#include "SetStyle.h"
#include "CustomAssert.h"
#include "RootUtilities.h"
#include "DataHelper.h"

int main(int argc, char *argv[]);
vector<double> DetectBins(TH1D *HMin, TH1D *HMax);
void SelfNormalize(TH1D *H, vector<double> Bins1, vector<double> Bins2);
TH1D *BuildSystematics(TH1D *HResult, TH1D *HVariation);
vector<TGraphAsymmErrors> Transcribe(TH1D *H, vector<double> Bins1, vector<double> Bins2);
void SetPad(TPad *P);
void SetAxis(TGaxis &A);
void SetWorld(TH2D *H);
TGraphAsymmErrors CalculateRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2);
double CalculateIntegral(TGraphAsymmErrors &G, double MinX = -9999);
string GuessState(string FileName);
double GetTotalGlobalUncertainty(string DHFileName, string FileName);
bool CheckInclude(string DHFileName, string FileName, string KeyBase);

int main(int argc, char *argv[])
{
   SilenceRoot();

   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string InputFileName           = CL.Get("Input");
   string OutputFileName          = CL.Get("Output");
   string FinalOutputFileName     = CL.Get("FinalOutput", "Meow.pdf");
   double GenPrimaryMinOverwrite  = CL.GetDouble("GenPrimaryMin", -9999);
   double GenPrimaryMaxOverwrite  = CL.GetDouble("GenPrimaryMax", 9999);
   double RecoPrimaryMinOverwrite = CL.GetDouble("RecoPrimaryMin", -9999);
   double RecoPrimaryMaxOverwrite = CL.GetDouble("RecoPrimaryMax", 9999);

   vector<string> Variations      = CL.GetStringVector("Variations");
   vector<int> SystematicGroups   = CL.GetIntVector("SystematicGroups");
   vector<string> Labels          = CL.GetStringVector("Labels");

   vector<string> Texts           = CL.GetStringVector("Texts", vector<string>());

   double MarkerModifier          = CL.GetDouble("MarkerModifier", 1.0);

   double WorldXMin               = CL.GetDouble("WorldXMin", 10);
   double WorldXMax               = CL.GetDouble("WorldXMax", 50);
   double WorldYMin               = CL.GetDouble("WorldYMin", 1000);
   double WorldYMax               = CL.GetDouble("WorldYMax", 5e5);
   bool LogX                      = CL.GetBool("LogX", true);
   bool LogY                      = CL.GetBool("LogY", false);

   string XLabel                  = CL.Get("XLabel", "Jet P (GeV)");
   string YLabel                  = CL.Get("YLabel", "dN / d(Jet P)");
   string BinningLabel            = CL.Get("Binning", "Jet P");

   int XAxisSpacing               = CL.GetInt("XAxis", 505);
   int YAxisSpacing               = CL.GetInt("YAxis", 505);

   double LegendX                 = CL.GetDouble("LegendX", 0.5);
   double LegendY                 = CL.GetDouble("LegendY", 0.5);
   double LegendSize              = CL.GetDouble("LegendSize", 0.075);

   string GlobalDHFileName        = CL.Get("Global");
   double TotalGlobal = GetTotalGlobalUncertainty(GlobalDHFileName, InputFileName);

   Assert(SystematicGroups.size() == Variations.size(), "Grouping size is not the same as label count");
   Assert(Texts.size() % 4 == 0, "Wrong additional text format!  It should be a collection of quadruplets: pad_index,x,y,text");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Unfolding plots");

   TFile InputFile(InputFileName.c_str());

   vector<double> GenBins1
      = DetectBins((TH1D *)InputFile.Get("HGenPrimaryBinMin"), (TH1D *)InputFile.Get("HGenPrimaryBinMax"));
   vector<double> GenBins2
      = DetectBins((TH1D *)InputFile.Get("HGenBinningBinMin"), (TH1D *)InputFile.Get("HGenBinningBinMax"));
   GenBins1[0] = GenPrimaryMinOverwrite;
   GenBins1[GenBins1.size()-1] = GenPrimaryMaxOverwrite;

   map<string, TH1D *> H1;
   for(string Name : Variations)
   {
      H1[Name]         = (TH1D *)InputFile.Get(Name.c_str());
      H1[Name+"Base"]  = (TH1D *)InputFile.Get((Name + "Base").c_str());
      H1[Name+"Ratio"] = BuildSystematics(H1[Name+"Base"], H1[Name]);
   }

   int SystematicGroupCount = 0;
   for(int G : SystematicGroups)
      if(SystematicGroupCount < G + 1)
         SystematicGroupCount = G + 1;

   for(int i = 0; i < (int)Variations.size(); i++)
   {
      string HName = Form("HG%dRatio", SystematicGroups[i]);
      if(H1.find(HName) == H1.end())
      {
         H1[HName] = (TH1D *)H1[Variations[i]]->Clone(HName.c_str());
         H1[HName]->Reset();
      }
      
      Assert(H1[Variations[i]+"Ratio"] != nullptr, ("Error getting systematic ratio for " + Variations[i]).c_str());
      
      if(CheckInclude(GlobalDHFileName, InputFileName, Variations[i]) == false)
         continue;

      for(int j = 1; j <= H1[HName]->GetNbinsX(); j++)
      {
         double V1 = H1[HName]->GetBinContent(j);
         double V2 = H1[Variations[i]+"Ratio"]->GetBinContent(j);
         double V = sqrt(V1 * V1 + V2 * V2);
         H1[HName]->SetBinContent(j, V);
      }
   }

   H1["HSystematicsRatioPlus"] = (TH1D *)InputFile.Get("HTotalPlus");
   H1["HSystematicsRatioMinus"] = (TH1D *)InputFile.Get("HTotalMinus");

   vector<int> Group = CL.GetIntVector("Group", vector<int>{});
   int Column        = CL.GetInt("Column", 4);
   int Row           = CL.GetInt("Row", 2);

   sort(Group.begin(), Group.end());
   Group.erase(unique(Group.begin(), Group.end()), Group.end());
   
   for(int i = 0; i < (int)Group.size(); i++)
   {
      if(Group[i] < 0 || Group[i] >= (int)GenBins2.size() - 1)
      {
         Group.erase(Group.begin() + i);
         i = i - 1;
      }
   }

   int BinningCount = GenBins2.size() - 1;
   if(BinningCount == 1)
   {
      Group = vector<int>{0};
      Column = 1;
      Row = 1;
   }

   if(Group.size() == 0)
      for(int i = 0; i < (int)GenBins2.size() - 1; i++)
         Group.push_back(i);
   if(Group.size() > Column * Row)
      Group.resize(Column * Row);

   int PadWidth     = 250;
   int PadHeight    = 250;
   int MarginLeft   = (30 + (Column - 1) * 15);
   int MarginRight  = (25 + (Column - 1) * 5);
   int MarginTop    = (25 + (Column - 1) * 5);
   int MarginBottom = (30 + (Column - 1) * 10);

   double CanvasWidth = MarginLeft + PadWidth * Column + MarginRight;
   double CanvasHeight = MarginBottom + PadHeight * Row + MarginTop;

   double PadDX = PadWidth / CanvasWidth;
   double PadDY = PadHeight / CanvasHeight;
   double PadX0 = MarginLeft / CanvasWidth;
   double PadY0 = MarginBottom / CanvasHeight;

   double TextSize = 0.040 - Row * 0.002;
   double InsideTextSize = TextSize;
   if(Column > 1)
   {
      TextSize = 0.050;
      InsideTextSize = 0.075;
   }

   vector<vector<TGraphAsymmErrors>> GCurves(SystematicGroupCount);
   GCurves[0] = Transcribe(H1["HSystematicsRatioPlus"], GenBins1, GenBins2);
   for(int i = 1; i < SystematicGroupCount; i++)
   {
      string HName = Form("HG%dRatio", i);
      GCurves[i] = Transcribe(H1[HName], GenBins1, GenBins2);
      for(TGraphAsymmErrors G : GCurves[i])
      {
         G.SetTitle(HName.c_str());
         PdfFile.AddPlot(G, "ap");
      }
   }

   Labels.insert(Labels.begin(), "Total");

   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   // Setup pads
   vector<TPad *> Pads;
   for(int i = 0; i < (int)Group.size(); i++)
   {
      int R = i / Column;
      int C = i % Column;

      double XMin = PadX0 + PadDX * C;
      double XMax = PadX0 + PadDX * (C + 1);
      double YMin = PadY0 + PadDY * R;
      double YMax = PadY0 + PadDY * (R + 1);

      Pads.emplace_back(new TPad(Form("P%d", i), "", XMin, YMin, XMax, YMax));

      if(LogX == true)
         Pads[i]->SetLogx();
      if(LogY == true)
         Pads[i]->SetLogy();
   }

   for(TPad *P : Pads)
      SetPad(P);
   
   // Setup axes
   vector<TGaxis *> XAxis, YAxis;
   for(int i = 0; i < Column; i++)
   {
      string Option = (LogX ? "G" : "");
      XAxis.emplace_back(new TGaxis(PadX0 + PadDX * i, PadY0, PadX0 + PadDX * (i + 1), PadY0, WorldXMin, WorldXMax, XAxisSpacing, Option.c_str()));
      SetAxis(*XAxis[i]);
      XAxis[i]->SetLabelSize(TextSize);
   }
   for(int i = 0; i < Row; i++)
   {
      double YMin = PadY0 + PadDY * i;
      double YMax = YMin + PadDY;
      string Option = (LogY ? "G" : "");
      YAxis.emplace_back(new TGaxis(PadX0, YMin, PadX0, YMax, WorldYMin, WorldYMax, YAxisSpacing, Option.c_str()));
      SetAxis(*YAxis[i]);
      YAxis[i]->SetLabelSize(TextSize);
   }

   // Setup axis labels
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(TextSize);
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(22);
   Latex.SetNDC();
   for(int i = 0; i < Column; i++)
      Latex.DrawLatex(PadX0 + PadDX * (i + 0.5), PadY0 * 0.3, XLabel.c_str());
   Latex.SetTextAngle(90);
   Latex.SetTextAlign(22);
   for(int i = 0; i < Row; i++)
      Latex.DrawLatex(PadX0 * 0.3, PadY0 + PadDY * (i + 0.5), YLabel.c_str());

   // Setup general information
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(11);
   Latex.DrawLatex(PadX0, PadY0 + PadDY * Row + 0.01, "CMS #font[52]{Preliminary}");

   // Global uncertainty
   if(TotalGlobal > 0)
   {
      Latex.SetTextAngle(0);
      Latex.SetTextAlign(31);
      Latex.DrawLatex(PadX0 + PadDX * Column, PadY0 + PadDY * Row + 0.01, Form("Global uncertainty: %.2f%%", TotalGlobal * 100));
   }

   // Setup worlds
   vector<TH2D *> HWorld;
   for(int i = 0; i < (int)Group.size(); i++)
   {
      int Index = i;

      Pads[Index]->cd();
      HWorld.emplace_back(new TH2D(Form("HWorld%d", i), "", 100, WorldXMin, WorldXMax, 100, WorldYMin, WorldYMax));
      SetWorld(HWorld[Index]);
      HWorld[Index]->GetXaxis()->SetNdivisions(XAxisSpacing);
      HWorld[Index]->GetYaxis()->SetNdivisions(YAxisSpacing);
   }

   // Adding panel labeling
   if(Column > 1 || Row > 1)
   {
      for(int i = 0; i < (int)Group.size(); i++)
      {
         int Index = i;
         Pads[Index]->cd();

         string BinLabel = "";
         if(GenBins2[Group[i]] > -9999)
            BinLabel = BinLabel + Form("%.1f < ", GenBins2[Group[i]]);
         BinLabel = BinLabel + BinningLabel;
         if(GenBins2[Group[i]+1] < 9999)
            BinLabel = BinLabel + Form(" < %.1f", GenBins2[Group[i]+1]);

         Latex.SetTextFont(42);
         Latex.SetTextSize(InsideTextSize);
         Latex.SetTextAlign(23);
         Latex.DrawLatex(0.5, 0.9, BinLabel.c_str());
      }
   }

   // Make the legend
   TLegend Legend(LegendX, LegendY, LegendX + 0.3, LegendY + LegendSize * 1.1 * GCurves.size());
   Legend.SetTextFont(42);
   Legend.SetTextSize(LegendSize);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);

   // Plot the actual curves & legend
   for(int i = 0; i < (int)Group.size(); i++)
   {
      int Index = i;

      Pads[Index]->cd();

      for(int j = 0; j < (int)GCurves.size(); j++)
      {
         GCurves[j][Group[i]].SetLineWidth(2);
         GCurves[j][Group[i]].SetMarkerStyle(20);
         GCurves[j][Group[i]].SetMarkerSize(MarkerModifier);
         GCurves[j][Group[i]].SetLineColor(Colors[j%9]);
         GCurves[j][Group[i]].SetMarkerColor(Colors[j%9]);
                   
         GCurves[j][Group[i]].Draw("pl");

         if(Index == 0)
            Legend.AddEntry(&GCurves[j][Group[i]], Labels[j].c_str(), "lp");
      }
      
      HWorld[Index]->Draw("axis same");

      for(int j = 0; j < (int)Texts.size(); j = j + 4)
      {
         int PadIndex = atoi(Texts[j+0].c_str());
         double X     = atof(Texts[j+1].c_str());
         double Y     = atof(Texts[j+2].c_str());
         string Text  = Texts[j+3];

         if(PadIndex != Index)
            continue;

         Latex.SetNDC();
         Latex.SetTextFont(42);
         Latex.SetTextSize(InsideTextSize);
         Latex.SetTextAlign(12);
         Latex.DrawLatex(X, Y, Text.c_str());
      }

      if(i == Group.size() - 1)
         Legend.Draw();
   }

   Canvas.cd();

   for(int j = 0; j < (int)Texts.size(); j = j + 4)
   {
      int PadIndex = atoi(Texts[j+0].c_str());
      double X     = atof(Texts[j+1].c_str());
      double Y     = atof(Texts[j+2].c_str());
      string Text  = Texts[j+3];

      if(PadIndex != -1)
         continue;

      Latex.SetNDC();
      Latex.SetTextFont(42);
      Latex.SetTextSize(TextSize);
      Latex.SetTextAlign(12);
      Latex.DrawLatex(X, Y, Text.c_str());
   }

   Canvas.SaveAs(FinalOutputFileName.c_str());

   for(TH2D *H : HWorld)    delete H;
   for(TGaxis *A : XAxis)   delete A;
   for(TGaxis *A : YAxis)   delete A;
   for(TPad *P : Pads)      delete P;

   InputFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

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
      Result.push_back(iterator.first);
      Result.push_back(iterator.second);
   }
   
   sort(Result.begin(), Result.end());
   auto iterator2 = unique(Result.begin(), Result.end());
   Result.erase(iterator2, Result.end());

   return Result;
}

void SelfNormalize(TH1D *H, vector<double> Bins1, vector<double> Bins2)
{
   if(H == nullptr)
      return;
   
   int BinningCount = Bins2.size() - 1;
   if(BinningCount <= 0)
      BinningCount = 1;

   for(int iB = 0; iB < BinningCount; iB++)
   {
      int BinCount = Bins1.size() - 1;
      if(BinCount <= 0)
         BinCount = 1;

      double Total = 0;
      for(int i = 0; i < BinCount; i++)
         Total = Total + H->GetBinContent(i + 1 + iB * BinCount);
      
      for(int i = 0; i < BinCount; i++)
      {
         H->SetBinContent(i + 1 + iB * BinCount, H->GetBinContent(i + 1 + iB * BinCount) / Total);
         H->SetBinError(i + 1 + iB * BinCount, H->GetBinError(i + 1 + iB * BinCount) / Total);
      }
   }
}

TH1D *BuildSystematics(TH1D *HBase, TH1D *HVariation)
{
   if(HBase == nullptr)
      return nullptr;

   TH1D *HSystematics = (TH1D *)HBase->Clone();

   if(HVariation == nullptr)
      return HSystematics;

   HSystematics->Reset();
   for(int i = 1; i <= HBase->GetNbinsX(); i++)
   {
      double V = HBase->GetBinContent(i);
      double R = HVariation->GetBinContent(i);
      if(V > 0)
         HSystematics->SetBinContent(i, fabs(R / V - 1));
   }

   return HSystematics;
}

vector<TGraphAsymmErrors> Transcribe(TH1D *H, vector<double> Bins1, vector<double> Bins2)
{
   int BinningCount = Bins2.size() - 1;
   if(BinningCount <= 0)
      BinningCount = 1;
   
   vector<TGraphAsymmErrors> Result(BinningCount);
   if(H == nullptr)
      return Result;

   int PrimaryBinCount = Bins1.size() - 1;
   double PrimaryBins[1000] = {0};
   for(int i = 0; i <= PrimaryBinCount; i++)
      PrimaryBins[i] = Bins1[i];
   double Delta = PrimaryBins[PrimaryBinCount-1] - PrimaryBins[1];

   if(PrimaryBins[0] < -99998)
      PrimaryBins[0] = PrimaryBins[1] - Delta * 0.05;
   if(PrimaryBins[PrimaryBinCount] > 99998)
      PrimaryBins[PrimaryBinCount] = PrimaryBins[PrimaryBinCount-1] + Delta * 0.05;
   // if(PrimaryBins[0] < 0 && PrimaryBins[1] > 0)
   //    PrimaryBins[0] = 0;

   for(int iB = 0; iB < BinningCount; iB++)
   {
      for(int i = 0; i < PrimaryBinCount; i++)
      {
         double X = (PrimaryBins[i] + PrimaryBins[i+1]) / 2;
         double DX = (PrimaryBins[i+1] - PrimaryBins[i]) / 2;
         double Y = 0, DY = 0;

         // Hack for now
         DX = 0;

         Y = H->GetBinContent(i + iB * PrimaryBinCount + 1);
         DY = H->GetBinError(i + iB * PrimaryBinCount + 1);

         if(Y != Y)     Y = 0;
         if(DY != DY)   DY = 0;

         // double Width = PrimaryBins[i+1] - PrimaryBins[i];
         double Width = 1;

         Result[iB].SetPoint(i, X, Y / Width);
         Result[iB].SetPointError(i, DX, DX, DY / Width, DY / Width);
      }
   }

   return Result;
}

void SetPad(TPad *P)
{
   if(P == nullptr)
      return;
   P->SetLeftMargin(0);
   P->SetTopMargin(0);
   P->SetRightMargin(0);
   P->SetBottomMargin(0);
   P->SetTickx();
   P->SetTicky();
   P->Draw();
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

void SetWorld(TH2D *H)
{
   if(H == nullptr)
      return;
   H->SetStats(0);
   H->Draw("axis");
}

TGraphAsymmErrors CalculateRatio(TGraphAsymmErrors &G1, TGraphAsymmErrors &G2)
{
   TGraphAsymmErrors G;

   int N = G2.GetN();
   for(int i = 0; i < N; i++)
   {
      double X1, X2, Y1, Y2, E1YH, E1YL, E1XH, E1XL;

      G1.GetPoint(i, X1, Y1);
      E1YH = G1.GetErrorYhigh(i);
      E1YL = G1.GetErrorYlow(i);
      E1XH = G1.GetErrorXhigh(i);
      E1XL = G1.GetErrorXlow(i);
      G2.GetPoint(i, X2, Y2);

      if(Y2 == 0)
         continue;

      G.SetPoint(i, X1, Y1 / Y2);
      G.SetPointError(i, E1XL, E1XH, E1YL / Y2, E1YH / Y2);
   }

   return G;
}

double CalculateIntegral(TGraphAsymmErrors &G, double MinX)
{
   double Total = 0;

   int N = G.GetN();
   for(int i = 0; i < N; i++)
   {
      double EX1, EX2, X, Y;

      G.GetPoint(i, X, Y);
      EX1 = G.GetErrorXlow(i);
      EX2 = G.GetErrorXhigh(i);

      if(X < MinX)
         continue;

      Total = Total + Y * (EX1 + EX2);
   }

   return Total;
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

double GetTotalGlobalUncertainty(string DHFileName, string FileName)
{
   string State = GuessState(FileName);

   DataHelper DHFile(DHFileName);

   double Variance = 0;

   vector<string> Keys = DHFile[State].GetListOfKeys();
   for(string Key : Keys)
   {
      if(Key.rfind("Global_", 0) == string::npos)
         continue;
      Variance = Variance + DHFile[State][Key].GetDouble() * DHFile[State][Key].GetDouble();
   }

   return sqrt(Variance);
}

bool CheckInclude(string DHFileName, string FileName, string KeyBase)
{
   string State = GuessState(FileName);

   DataHelper DHFile(DHFileName);

   vector<string> ToCheck{KeyBase, "H" + KeyBase, KeyBase.substr(1)};

   bool Included = false;
   for(string Check : ToCheck)
   {
      if(DHFile[State].Exist(Check + "_Include") == false)
         continue;
      if(DHFile[State][Check+"_Include"].GetInteger() > 0)
         Included = true;
   }

   return Included;
}
