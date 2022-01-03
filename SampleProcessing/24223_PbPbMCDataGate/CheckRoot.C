{
   string Names[14] = {"hltanalysis/HltTree", "skimanalysis/HltTree", "HiForestInfo/HiForest", "hiEvtAnalyzer/HiTree", "akCs1PFJetAnalyzer/t", "akCs2PFJetAnalyzer/t", "akCs3PFJetAnalyzer/t", "akCs4PFJetAnalyzer/t", "akCs5PFJetAnalyzer/t", "akCs6PFJetAnalyzer/t", "akCs7PFJetAnalyzer/t", "akCs8PFJetAnalyzer/t", "akCs9PFJetAnalyzer/t", "hiPuRhoAnalyzer/t"};

   for(int i = 0; i < 14; i++)
   {
      if(_file0->Get(Names[i].c_str()) == nullptr)
         continue;

      cout << Names[i] << " " << ((TTree *)(_file0->Get(Names[i].c_str())))->GetEntries() << endl;
   }
}
