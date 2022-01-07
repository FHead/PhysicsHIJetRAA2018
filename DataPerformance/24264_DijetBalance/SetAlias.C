{
   DijetTree->SetAlias("DPhiRaw", "(Phi1-Phi2)");
   DijetTree->SetAlias("DPhi", "(DPhiRaw+2*3.14159*(DPhiRaw<-3.14159)-2*3.14159*(DPhiRaw>3.14159))");
}
