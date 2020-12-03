// .... This script has created to anasyzed the HGC's whole in it using the TCutG....
// .... Created Date: Nov 21, 2021 ....
// .... Author: Vijay Kumar ....
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#define EFF_SCANNING_cxx
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <TSystem.h>
#include <TTree.h>
#include <TArc.h>
#include <TCutG.h>
#include <TExec.h>
#include <TColor.h>

// Input should be the input root file name (including suffix) and an output file name string (without any suffix)
void EFF_SCANNING(string InFilename = "", string OutFilename = "")
{
  TString Hostname = gSystem->HostName();
  TString User = (gSystem->GetUserInfo())->fUser;
  TString Replaypath;
  TString Outpath;
  TString Outpath1;
  TString rootFile;
  gStyle->SetPalette(55);

  // Set paths depending on system you're running on
  if(Hostname.Contains("farm")){
    Replaypath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt";
    // Output path for root file
    Outpath = Replaypath+"/UTIL_KAONLT/scripts/pid/src/PYTHON_EFFICIENCY_SCRIPTS/OUTPUT";
    // Output path for output files (pdf or root )
    Outpath1 = Replaypath+"/UTIL_KAONLT/scripts/pid/src/ROOT_EFFICIENCY_SCRIPTS/OUTPUT";
  }
  else if(Hostname.Contains("qcd")){
    Replaypath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt";
    Outpath = Replaypath+"/UTIL_KAONLT/scripts/CoinTimePeak/OUTPUT";
  }
  else if (Hostname.Contains("phys.uregina.ca")){
    Replaypath = "/home/"+User+"/work/JLab/hallc_replay_lt";
    Outpath = Replaypath+"/UTIL_KAONLT/scripts/CoinTimePeak/OUTPUT";
  }
  // Add more as needed for your own envrionment
    if(InFilename == "") {
    cout << "Enter a Filename to analyse: ";
    cin >> InFilename;
  }  
    if(OutFilename == "") {
    cout << "Enter a Filename to outpu: ";
    cin >> OutFilename;
  }  

  TString TInFilename = InFilename;
  rootFile = Outpath+"/"+TInFilename;
  // Complain and exit if your file doesn't exist
  if (gSystem->AccessPathName(rootFile) == kTRUE){
    cerr << "!!!!! ERROR !!!!! " << endl << rootFile <<  " not found" << endl <<  "!!!!! ERRROR !!!!!" << endl;
    exit;
  }
  TFile *InFile = new TFile(rootFile, "READ");
  TString TOutFilename = OutFilename;
  // Establish the names of our output files quickly
  TString foutname = Outpath1+"/" + TOutFilename + ".root";
  TString foutpdf = Outpath1+"/" + TOutFilename + ".pdf";

  
 // Particles information with  pid
  TTree* Pion_No_HGC_Cut  = (TTree*)InFile->Get("SHMS_Pions_Without_HGC_Cuts"); Long64_t nEntries_Pion_No_HGC_Cut  = (Long64_t)Pion_No_HGC_Cut->GetEntries();

  Double_t P_hgcer_xAtCer;Pion_No_HGC_Cut->SetBranchAddress("P_hgcer_xAtCer", &P_hgcer_xAtCer);
  Double_t P_hgcer_yAtCer;Pion_No_HGC_Cut->SetBranchAddress("P_hgcer_yAtCer", &P_hgcer_yAtCer);
  Double_t P_aero_yAtCer;Pion_No_HGC_Cut->SetBranchAddress("P_aero_yAtCer", &P_aero_yAtCer);
  Double_t P_gtr_dp; Pion_No_HGC_Cut->SetBranchAddress("P_gtr_dp", &P_gtr_dp);
  Double_t Pion_npeSum;Pion_No_HGC_Cut->SetBranchAddress("P_hgcer_npeSum", &Pion_npeSum);
  Double_t Pion_aero_npeSum;Pion_No_HGC_Cut->SetBranchAddress("P_aero_npeSum", &Pion_aero_npeSum);
  Double_t Pion_gtr_p; Pion_No_HGC_Cut->SetBranchAddress("P_gtr_p", &Pion_gtr_p);
  Double_t Pion_e_miss;Pion_No_HGC_Cut->SetBranchAddress("emiss", &Pion_e_miss);
  Double_t Pion_p_miss;Pion_No_HGC_Cut->SetBranchAddress("pmiss", &Pion_p_miss);

 
  // Histograms for scanning the efficiency 
  TH2D *h2_Eff_Pos1    = new TH2D("h2_Eff_Pos1","Efficiency vs Position; X Position (cm); Y Position (cm);", 300, -30, 30.0, 300, -30, 30.0 ); 
  TH2D *h2_Eff_Pos2    = new TH2D("h2_Eff_Pos2","Efficiency vs Position; X Position (cm); Y Position (cm);", 300, -30, 30.0, 300, -30, 30.0 ); 
  TH2D *h2_Eff_Pos3    = new TH2D("h2_Eff_Pos3","Efficiency vs Position; X Position (cm); Y Position (cm);", 300, -30, 30.0, 300, -30, 30.0 ); 
 
  //Fill entries for efficiency scanning

  for(Long64_t i = 0; i < nEntries_Pion_No_HGC_Cut; i++){
    Pion_No_HGC_Cut->GetEntry(i);
    if(Pion_npeSum < 0.1 || Pion_aero_npeSum <1.0 || P_aero_yAtCer >31) continue;
    h2_Eff_Pos1->Fill(P_hgcer_xAtCer, P_hgcer_yAtCer);
  }

  for(Long64_t i = 0; i < nEntries_Pion_No_HGC_Cut; i++){
    Pion_No_HGC_Cut->GetEntry(i);
    if(Pion_npeSum < 1.0 || Pion_aero_npeSum <1.5 || P_aero_yAtCer >31) continue;
    h2_Eff_Pos2->Fill(P_hgcer_xAtCer, P_hgcer_yAtCer);
  }

  // Take Efficiency scanning 
  h2_Eff_Pos3 = (TH2D*)h2_Eff_Pos2->Clone();
  h2_Eff_Pos3->Divide(h2_Eff_Pos1);
 
  //Write the info in the root format

  TFile *OutHisto_file = new TFile(foutname,"RECREATE");
  TDirectory *EFF_SCA = OutHisto_file->mkdir("EFF_SCA");
  EFF_SCA->cd();
  h2_Eff_Pos3->Write();
  OutHisto_file->Close();

  // TString RunNumStr = TInFilename(0,4); Int_t RunNum=(RunNumStr.Atoi());
  //TString OutputStr = Form("%i,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f", RunNum, PionFit->GetParameter(1), PionFit->GetParError(1), PionFWHM, PionFWHMErr, KaonFit->GetParameter(1), KaonFit->GetParError(1), KaonFWHM, KaonFWHMErr, ProtonFit->GetParameter(1), ProtonFit->GetParError(1), ProtonFWHM, ProtonFWHMErr);
    //cout << OutputStr << endl;
}
