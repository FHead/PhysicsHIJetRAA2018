#ifndef SFSFCorrector_H_24512
#define SFSFCorrector_H_24512

#include <iostream>
#include <vector>

#include "DataHelper.h"

class SFCorrector
{
public:
   std::vector<double> P;
public:
   SFCorrector();
   SFCorrector(std::string FileName);
   void Initialize(std::string FileName, std::string State = "SoftFraction", std::string KeyPrefix = "R4");
   double GetCorrection(double SF00, double SF10, double SF15, double SF20, double SF25, double SF30);
};


// implementation

SFCorrector::SFCorrector()
{
}

SFCorrector::SFCorrector(std::string FileName)
{
   Initialize(FileName);
}

void SFCorrector::Initialize(std::string FileName, std::string State = "SoftFraction", std::string KeyPrefix = "R4")
{
   DataHelper DHFile(FileName);
   for(int i = 0; i < 13; i++)
      P.push_back(DHFile[State][KeyPrefix+"_P"+std::to_string(i)].GetDouble());
}

double SFCorrector::GetCorrection(double SF00, double SF10, double SF15, double SF20, double SF25, double SF30)
{
   double F0 = (SF00 - SF10) / SF00;
   double F1 = (SF10 - SF15) / SF00;
   double F2 = (SF15 - SF20) / SF00;
   double F3 = (SF20 - SF25) / SF00;
   double F4 = (SF25 - SF30) / SF00;
   double F5 = (SF30) / SF00;

   double C0 = P[1]  * F0 + P[2]  * F0 * F0;
   double C1 = P[3]  * F1 + P[4]  * F1 * F1;
   double C2 = P[5]  * F2 + P[6]  * F2 * F2;
   double C3 = P[7]  * F3 + P[8]  * F3 * F3;
   double C4 = P[9]  * F4 + P[10] * F4 * F4;
   double C5 = P[11] * F5 + P[12] * F5 * F5;

   double C = sqrt(P[0] + C0 + C1 + C2 + C3 + C4 + C5);

   return C;
}

#endif
