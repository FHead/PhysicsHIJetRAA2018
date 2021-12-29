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

int main(int argc, char *argv[])
{
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
   string Formula = DHFile[DHState]["Formula"].GetString();

   ofstream out(OutputFileName);

   out << "{3 JetEta JetPT JetRho 1 JetPhi " << Formula << " Correction L3Absolute}" << endl;

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

         for(int iP = 0; iP < NMax; iP++)
         {
            TGraphErrors G;
            for(int iPT = 0; iPT < NPT; iPT++)
            {
               string KeyBase = "Eta" + to_string(iEta) + "_PT" + to_string(iPT) + "_Rho" + to_string(iRho);
               if(DHFile[DHState].Exist(KeyBase+"_EtaMin") == false)   // missing bin (from statistics etc)
                  continue;

               double PTMean = DHFile[DHState][KeyBase+"_PTMean"].GetDouble();
               double P      = DHFile[DHState][KeyBase+"_P"+to_string(iP)].GetDouble();
               double E      = DHFile[DHState][KeyBase+"_E"+to_string(iP)].GetDouble();
               G.SetPoint(iPT, PTMean, P);
               // G.SetPointError(iPT, 0, E);
            }

            TF1 F("F", "[0]+[1]*exp(-x/[2]/[2])", 0, 1000);
            F.SetParameters(0, 0.001, 5);
            G.Fit(&F);
            PdfFile.AddPlot(G, "ap", false, false, true, true);
         }

         /*
         for(int iPT = 1; iPT < NPT; iPT++)
         {
            string KeyBase = "Eta" + to_string(iEta) + "_PT" + to_string(iPT) + "_Rho" + to_string(iRho);

            if(DHFile[DHState].Exist(KeyBase+"_EtaMin") == false)   // missing bin (from statistics etc)
               continue;

            double EtaMin = DHFile[DHState][KeyBase+"_EtaMin"].GetDouble();
            double EtaMax = DHFile[DHState][KeyBase+"_EtaMax"].GetDouble();
            double PTMin  = DHFile[DHState][KeyBase+"_PTMin"].GetDouble();
            double PTMax  = DHFile[DHState][KeyBase+"_PTMax"].GetDouble();
            double RhoMin = DHFile[DHState][KeyBase+"_RhoMin"].GetDouble();
            double RhoMax = DHFile[DHState][KeyBase+"_RhoMax"].GetDouble();

            int NParameter = DHFile[DHState][KeyBase+"_NParameter"].GetInteger();

            if(NParameter > 0 && KeepScale == true)
               DHFile[DHState][KeyBase+"_P0"] = 1.00;

            out << EtaMin << " " << EtaMax << " " << PTMin << " " << PTMax << " " << RhoMin << " " << RhoMax
               << " " << NParameter + 2 << " " << -M_PI << " " << M_PI;
            for(int i = 0; i < NParameter; i++)
               out << " " << DHFile[DHState][KeyBase+"_P"+to_string(i)].GetDouble();
            out << endl;
         }
         */
      }
   }

   out.close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}





