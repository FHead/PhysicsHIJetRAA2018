#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

#include "TGraphErrors.h"
#include "TF1.h"

#include "CommandLine.h"
#include "DataHelper.h"
#include "CustomAssert.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "RootUtilities.h"

int main(int argc, char *argv[]);
string TransformFormula(string Formula);
string GetSubFormula(int Index);

int main(int argc, char *argv[])
{
   SilenceRoot();

   SetThesisStyle();

   CommandLine CL(argc, argv);

   string DHFileName        = CL.Get("DHFile");
   string DHState           = CL.Get("DHState");
   string OutputFileName    = CL.Get("Output");
   string PDFOutputFileName = CL.Get("PDFOutput", "Plot.pdf");
   bool KeepScale           = CL.GetBool("KeepScale", false);

   PdfFileHelper PdfFile(PDFOutputFileName);
   PdfFile.AddTextPage("Fourier component interpolation");

   DataHelper DHFile(DHFileName);

   Assert(DHFile.Exist(DHState) == true, "State not found in the DHFile");

   int NEta       = DHFile[DHState]["NEta"].GetInteger();
   int NPT        = DHFile[DHState]["NPT"].GetInteger();
   int NRho       = DHFile[DHState]["NRho"].GetInteger();
   string Formula = TransformFormula(DHFile[DHState]["Formula"].GetString());

   cout << Formula << endl;

   ofstream out(OutputFileName);

   out << "{2 JetEta JetRho 2 JetPhi JetPT " << Formula << " Correction L3Absolute}" << endl;

   for(int iEta = 0; iEta < NEta; iEta++)
   {
      for(int iRho = 0; iRho < NRho; iRho++)
      {
         PdfFile.AddTextPage("Eta bin " + to_string(iEta) + ", Rho bin " + to_string(iRho));

         int NMax = 0;
         for(int iPT = 0; iPT < NPT; iPT++)
         {
            string KeyBase = "Eta" + to_string(iEta) + "_PT" + to_string(iPT) + "_Rho" + to_string(iRho);
            if(DHFile[DHState].Exist(KeyBase+"_EtaMin") == false)   // missing bin (from statistics etc)
               continue;
            int NParameter = DHFile[DHState][KeyBase+"_NParameter"].GetInteger();
            if(NParameter > NMax)
               NMax = NParameter;
         }

         string KeyBase = "Eta" + to_string(iEta) + "_PT0_Rho" + to_string(iRho);
         double EtaMin = DHFile[DHState][KeyBase+"_EtaMin"].GetDouble();
         double EtaMax = DHFile[DHState][KeyBase+"_EtaMax"].GetDouble();
         double RhoMin = DHFile[DHState][KeyBase+"_RhoMin"].GetDouble();
         double RhoMax = DHFile[DHState][KeyBase+"_RhoMax"].GetDouble();

         int NParameter = DHFile[DHState][KeyBase+"_NParameter"].GetInteger();
            
         out << EtaMin << " " << EtaMax << " " << RhoMin << " " << RhoMax
            << " " << NParameter * 3 + 4 << " " << -M_PI << " " << M_PI << " " << 15 << " " << 1500;

         for(int iP = 0; iP < NMax; iP++)
         {
            TGraphErrors G;
            G.SetTitle(Form("Eta %d Rho %d P %d", iEta, iRho, iP));

            for(int iPT = 1; iPT < NPT; iPT++)
            {
               string KeyBase = "Eta" + to_string(iEta) + "_PT" + to_string(iPT) + "_Rho" + to_string(iRho);
               if(DHFile[DHState].Exist(KeyBase+"_EtaMin") == false)   // missing bin (from statistics etc)
                  continue;

               double PTMean = DHFile[DHState][KeyBase+"_PTMean"].GetDouble();
               double P      = DHFile[DHState][KeyBase+"_P"+to_string(iP)].GetDouble();
               double E      = DHFile[DHState][KeyBase+"_E"+to_string(iP)].GetDouble();

               if(KeepScale == true)
               {
                  PTMean = DHFile[DHState][KeyBase+"_GenPTMean"].GetDouble();
                  P = P / DHFile[DHState][KeyBase+"_P0"].GetDouble();
               }

               if(iP == 0)
                  P = P - 1;

               int I = G.GetN();
               G.SetPoint(I, PTMean, P);
               // G.SetPointError(I, 0, E);
            }

            TF1 F("F", "[0]+[1]*exp(-x/[2]/[2])", 0, 1000);
            if(iP == 0)
            {
               if(KeepScale == true)
                  F.SetParameters(0, 0, 1);
               else
               {
                  F.SetParameters(0, -0.2, 5);
                  G.Fit(&F, "Q");
               }
            }
            else
            {
               F.SetParameters(0, 0.05, 5);
               G.Fit(&F, "Q");
               F.SetParameter(2, 5);
               G.Fit(&F, "Q");
               F.SetParameter(2, 5);
               G.Fit(&F, "Q");
            }
            PdfFile.AddPlot(G, "ap", false, false, true, true);

            if(iP == 0)
               out << " " << 1 + F.GetParameter(0) << " " << F.GetParameter(1) << " " << F.GetParameter(2);
            else
               out << " " << F.GetParameter(0) << " " << F.GetParameter(1) << " " << F.GetParameter(2);
         }
         
         out << endl;

         /*
         for(int iPT = 1; iPT < NPT; iPT++)
         {
            string KeyBase = "Eta" + to_string(iEta) + "_PT" + to_string(iPT) + "_Rho" + to_string(iRho);

            if(DHFile[DHState].Exist(KeyBase+"_EtaMin") == false)   // missing bin (from statistics etc)
               continue;

         }
         */
      }
   }

   out.close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

string TransformFormula(string Formula)
{
   for(char &c : Formula)
   {
      if(c == '[')   c = '{';
      if(c == ']')   c = '}';
   }

   for(int i = 0; i < (int)Formula.size(); i++)
   {
      if(Formula[i] != '{')
         continue;

      int Start = i;
      int End = -1;
      for(int j = Start + 1; j < (int)Formula.size(); j++)
      {
         if(Formula[j] == '}')
         {
            End = j;
            break;
         }
      }

      if(End == -1)   // WTF
         break;

      int Index = stoi(Formula.substr(Start + 1, End - Start - 1));
      string SubFormula = GetSubFormula(Index * 3);

      Formula.erase(Formula.begin() + Start, Formula.begin() + End + 1);
      Formula.insert(Start, SubFormula);
   }

   return Formula;
}

string GetSubFormula(int Index)
{
   string I0 = to_string(Index);
   string I1 = to_string(Index + 1);
   string I2 = to_string(Index + 2);
   return "([" + I0 + "]+[" + I1 + "]*exp(-y/[" + I2 + "]*[" + I2 + "]))";
}



