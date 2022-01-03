#include <string>
#include <vector>
using namespace std;

#include "TFile.h"

#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string FileName = CL.Get("Input");
   vector<string> Directories = CL.GetStringVector("Directories");

   TFile File(FileName.c_str(), "update");
   
   for(string Name : Directories)
      File.Delete(Form("%s;*", Name.c_str()));

   File.Close();

   return 0;
}
