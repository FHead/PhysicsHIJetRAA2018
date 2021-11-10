{
   JetEnergyTree->Draw("MatchedJetPT/GenJetPT:MatchedJetUE>>HA(50,0,60)",
      "GenJetPT > 0 && MatchedJetAngle < 0.2 && GenJetPT > 80 && GenJetPT < 100", "prof");
   JetEnergyTree->Draw("MatchedJetPT/GenJetPT:MatchedJetUE>>HB(50,0,60)",
      "GenJetPT > 0 && MatchedJetAngle < 0.2 && GenJetPT > 100 && GenJetPT < 150", "prof");
   JetEnergyTree->Draw("MatchedJetPT/GenJetPT:MatchedJetUE>>HC(50,0,60)",
      "GenJetPT > 0 && MatchedJetAngle < 0.2 && GenJetPT > 150 && GenJetPT < 200", "prof");
   JetEnergyTree->Draw("MatchedJetPT/GenJetPT:MatchedJetUE>>HD(50,0,60)",
      "GenJetPT > 0 && MatchedJetAngle < 0.2 && GenJetPT > 200 && GenJetPT < 500", "prof");

   HA->SetLineColor(1);
   HB->SetLineColor(2);
   HC->SetLineColor(3);
   HD->SetLineColor(4);
   HA->SetMarkerColor(1);
   HB->SetMarkerColor(2);
   HC->SetMarkerColor(3);
   HD->SetMarkerColor(4);
   HA->SetMarkerStyle(20);
   HB->SetMarkerStyle(20);
   HC->SetMarkerStyle(20);
   HD->SetMarkerStyle(20);

   HA->Draw();
   HB->Draw("same");
   HC->Draw("same");
   HD->Draw("same");
}

