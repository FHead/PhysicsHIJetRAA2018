{
   TTree *M = (TTree *)_file0->Get("skimanalysis/HltTree");
   TTree *T = (TTree *)_file0->Get("akCs4PFJetAnalyzer/t");
   T->AddFriend(M, "M");
   T->Draw("jtpt", "M.HBHENoiseFilterResultRun2Loose == 1");
}
