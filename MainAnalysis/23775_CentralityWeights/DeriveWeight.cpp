#include <iostream>
using namespace std;

#include "Messenger.h"

#include "CommandLine.h"

int main(int argc, char *argv[]);
TGraph FindCorrection(string DataFileName, string MCFileName, double JetPTMin);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string DataFileName = CL.Get("Data");
   string MCFileName   = CL.Get("MC");

   return 0;
}

TGraph FindCorrection(string DataFileName, string MCFileName, double JetPTMin)
{
}
