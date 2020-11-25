{
  gROOT->Reset();
  
  // Draw histos filled by Geant4 simulation 
  TFile f("Co60.root");      
  TCanvas* c1 = new TCanvas("c1", "  ");
  
  c1->SetLogy(1);
  c1->cd();
  c1->Update();
  
  TH1D* hist1 = (TH1D*)f.Get("1");
  hist1->Draw("HIST");

}  
