// .... This script has created to measurement of  the HGC's efficiency....
// .... Created Date: Nov 25, 2020 ....
// .... Author: Vijay Kumar ....
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#define HGC_efficiency_cxx
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
void HGC_efficiency(string RunNumber = "")
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
  if(RunNumber == "") {
    cout << "Enter a run number to analyse: ";
    cin >> RunNumber;
  }  
  TString TInFilename = RunNumber + "_-1.root";
  rootFile = Outpath+"/"+TInFilename;
  // Complain and exit if your file doesn't exist
  if (gSystem->AccessPathName(rootFile) == kTRUE){
    cerr << "!!!!! ERROR !!!!! " << endl << rootFile <<  " not found" << endl <<  "!!!!! ERRROR !!!!!" << endl;
    exit;
  }
  TFile *InFile = new TFile(rootFile, "READ");
  TString TOutFilename = RunNumber;
  // Establish the names of our output files quickly
  TString foutname = Outpath1+"/" + RunNumber + "_out" + ".root";
  TString foutpdf = Outpath1+"/"  + RunNumber + "_out" + ".pdf";
  
  // Get entries for Pions with HGC cut
  TTree* Pion_HGC_Cut = (TTree*)InFile->Get("SHMS_Pions"); Long64_t nEntries_Pion_HGC_Cut = (Long64_t)Pion_HGC_Cut->GetEntries();
  // Get entries for Pions without HGC cut
  TTree* Pion_No_HGC_Cut = (TTree*)InFile->Get("SHMS_Pions_Without_HGC_Cuts"); Long64_t nEntries_Pion_No_HGC_Cut = (Long64_t)Pion_No_HGC_Cut->GetEntries();
  // Get entries for Kaon with HGC cut
  TTree* Kaon_HGC_Cut = (TTree*)InFile->Get("SHMS_Kaons"); Long64_t nEntries_Kaon_HGC_Cut = (Long64_t)Kaon_HGC_Cut->GetEntries();
  // Get entries for Kaon without HGC cut
  TTree* Kaon_No_HGC_Cut = (TTree*)InFile->Get("SHMS_Kaons_Without_HGC_Cuts"); Long64_t nEntries_Kaon_No_HGC_Cut = (Long64_t)Kaon_No_HGC_Cut->GetEntries();
  // Get entries for Proton with HGC cut
  TTree* Proton_HGC_Cut = (TTree*)InFile->Get("SHMS_Protons"); Long64_t nEntries_Proton_HGC_Cut = (Long64_t)Proton_HGC_Cut->GetEntries();
  // Get entries for Proton without HGC cut
  TTree* Proton_No_HGC_Cut = (TTree*)InFile->Get("SHMS_Protons_Without_HGC_Cuts"); Long64_t nEntries_Proton_No_HGC_Cut = (Long64_t)Proton_No_HGC_Cut->GetEntries();


  // Set Branches
  //For Pion
  Double_t Pion_HGC_Cut_npeSum;Pion_HGC_Cut->SetBranchAddress("P_hgcer_npeSum", &Pion_HGC_Cut_npeSum);
  Double_t Pion_No_HGC_Cut_npeSum;Pion_No_HGC_Cut->SetBranchAddress("P_hgcer_npeSum", &Pion_No_HGC_Cut_npeSum);
  //For Kaon
  Double_t Kaon_HGC_Cut_npeSum;Kaon_HGC_Cut->SetBranchAddress("P_hgcer_npeSum", &Kaon_HGC_Cut_npeSum);
  Double_t Kaon_No_HGC_Cut_npeSum;Kaon_No_HGC_Cut->SetBranchAddress("P_hgcer_npeSum", &Kaon_No_HGC_Cut_npeSum);
  //For Proton
  Double_t Proton_HGC_Cut_npeSum;Proton_HGC_Cut->SetBranchAddress("P_hgcer_npeSum", &Proton_HGC_Cut_npeSum);
  Double_t Proton_No_HGC_Cut_npeSum;Proton_No_HGC_Cut->SetBranchAddress("P_hgcer_npeSum", &Proton_No_HGC_Cut_npeSum);


  // Defined Geometrical Cuts1
  TCutG *cutg1 = new TCutG("cutg1",21);
  cutg1->SetVarX("P_hgcer_yAtCer");
  cutg1->SetVarY("P_hgcer_xAtCer");
  cutg1->SetPoint(0,-25,2);
  cutg1->SetPoint(1,-2,2);
  cutg1->SetPoint(2,-1,2.5);
  cutg1->SetPoint(3,0,3);
  cutg1->SetPoint(4,1,3);
  cutg1->SetPoint(5,2,3.3);
  cutg1->SetPoint(6,3,3.0);
  cutg1->SetPoint(7,4,2.5);
  cutg1->SetPoint(8,5,2);
  cutg1->SetPoint(9,25,2);
  cutg1->SetPoint(10,25,0.5);
  cutg1->SetPoint(11,5,0.5);
  cutg1->SetPoint(12,4,1);
  cutg1->SetPoint(13,3,-1);
  cutg1->SetPoint(14,2,-2);
  cutg1->SetPoint(15,1,-2.3);
  cutg1->SetPoint(16,0,-1.5);
  cutg1->SetPoint(17,-1,-1);
  cutg1->SetPoint(18,-2,0.5);
  cutg1->SetPoint(19,-25,0.5);
  cutg1->SetPoint(20,-25,2);
  cutg1->SetLineColor(kRed);
  cutg1->SetLineWidth(5);

  // Defined Geometrical Cuts2
  TCutG *cutg2 = new TCutG("cutg2",19);
  cutg2->SetVarX("P_hgcer_yAtCer");
  cutg2->SetVarY("P_hgcer_xAtCer");
  cutg2->SetPoint(0,-25,2);
  cutg2->SetPoint(1,-2,2);
  cutg2->SetPoint(2,0,3.5);
  cutg2->SetPoint(3,2,5.5);
  cutg2->SetPoint(4,4,5);
  cutg2->SetPoint(5,6,4.5);
  cutg2->SetPoint(6,8,4);
  cutg2->SetPoint(7,10,2);
  cutg2->SetPoint(8,25,2);
  cutg2->SetPoint(9,25,0.5);
  cutg2->SetPoint(10,6,0.5);
  cutg2->SetPoint(11,4,-1);
  cutg2->SetPoint(12,2,-3);
  cutg2->SetPoint(13,0,-3.5);
  cutg2->SetPoint(14,-2,-2);
  cutg2->SetPoint(15,-4,-0.75);
  cutg2->SetPoint(16,-6,-0.5);
  cutg2->SetPoint(17,-25,0.5);
  cutg2->SetPoint(18,-25,2);
  cutg2->SetLineColor(kRed);
  cutg2->SetLineWidth(5); 
  
  //Defined Histograms for npeSum

  //Pion
  TH1D *h1_Pion_HGC_Cut_npeSum         =  new TH1D("h1_Pion_HGC_Cut_npeSum;","NPE with HGC Cut (Pion Selected);  P_hgcer_npeSum;" ,300, 0.0, 40);
  TH1D *h1_Pion_No_HGC_Cut_npeSum      =  new TH1D("h1_Pion_No_HGC_Cut_npeSum;", "NPE No HGC Cut (Pion Selected); P_hgcer_npeSum;" ,300, 0.0, 40);
  //Kaon

  TH1D *h1_Kaon_HGC_Cut_npeSum         =  new TH1D("h1_Kaon_HGC_Cut_npeSum;", "NPE with HGC Cut (Kaon Selected); P_hgcer_npeSum;" ,300, 0.0, 40);
  TH1D *h1_Kaon_No_HGC_Cut_npeSum      =  new TH1D("h1_Kaon_No_HGC_Cut_npeSum;", "NPE No HGC Cut (Kaon Selected); P_hgcer_npeSum;" ,300, 0.0, 40);
  //Proton

  TH1D *h1_Proton_HGC_Cut_npeSum       =  new TH1D("h1_Proton_HGC_Cut_npeSum;", "NPE with HGC Cut (Proton Selected); P_hgcer_npeSum;", 300, 0.0, 40);
  TH1D *h1_Proton_No_HGC_Cut_npeSum    =  new TH1D("h1_Proton_No_HGC_Cut_npeSum;", "NPE No HGC Cut (Proton Selected); P_hgcer_npeSum;", 300, 0.0, 40);


  //Fill npeSum entries
      
  for(Long64_t i = 0; i < nEntries_Pion_HGC_Cut; i++){
    Pion_HGC_Cut->GetEntry(i);
    if(Pion_HGC_Cut_npeSum < 0.1) continue;
    h1_Pion_HGC_Cut_npeSum->Fill(Pion_HGC_Cut_npeSum);
  }

  for(Long64_t i = 0; i < nEntries_Pion_No_HGC_Cut; i++){
    Pion_No_HGC_Cut->GetEntry(i);
    if(Pion_No_HGC_Cut_npeSum < 0.1) continue;
    h1_Pion_No_HGC_Cut_npeSum->Fill(Pion_No_HGC_Cut_npeSum);
  }

  for(Long64_t i = 0; i < nEntries_Kaon_HGC_Cut; i++){
    Kaon_HGC_Cut->GetEntry(i);
  if(Kaon_HGC_Cut_npeSum < 0.1) continue;  
  h1_Kaon_HGC_Cut_npeSum->Fill(Kaon_HGC_Cut_npeSum);
  }
  for(Long64_t i = 0; i < nEntries_Kaon_No_HGC_Cut; i++){
    Kaon_No_HGC_Cut->GetEntry(i);
    if(Kaon_No_HGC_Cut_npeSum < 0.1) continue;  
    h1_Kaon_HGC_Cut_npeSum->Fill(Kaon_No_HGC_Cut_npeSum);
  }

  for(Long64_t i = 0; i < nEntries_Proton_HGC_Cut; i++){
    Proton_HGC_Cut->GetEntry(i);
    // if(P_hgcer_npeSum < 1.5) continue;
    h1_Proton_HGC_Cut_npeSum->Fill(Proton_HGC_Cut_npeSum);
  }
  for(Long64_t i = 0; i < nEntries_Proton_No_HGC_Cut; i++){
    Proton_No_HGC_Cut->GetEntry(i);
    // if(P_hgcer_npeSum < 1.5) continue;
    h1_Proton_HGC_Cut_npeSum->Fill(Proton_No_HGC_Cut_npeSum);
  }
  
  //Write the info in the root format

  TFile *OutHisto_file = new TFile(foutname,"RECREATE");
  TDirectory *Efficiency_Plots = OutHisto_file->mkdir("Efficiency_Plots");
  Efficiency_Plots->cd();
  h1_Pion_HGC_Cut_npeSum->Write();
  h1_Pion_No_HGC_Cut_npeSum->Write();
  h1_Kaon_HGC_Cut_npeSum->Write();
  h1_Kaon_No_HGC_Cut_npeSum->Write();
  h1_Proton_HGC_Cut_npeSum->Write();
  h1_Proton_No_HGC_Cut_npeSum->Write();
  OutHisto_file->Close();
  //  cutg->SaveAs("cutg.txt");
  // TString RunNumStr = TInFilename(0,4); Int_t RunNum=(RunNumStr.Atoi());
  //TString OutputStr = Form("%i,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f", RunNum, PionFit->GetParameter(1), PionFit->GetParError(1), PionFWHM, PionFWHMErr, KaonFit->GetParameter(1), KaonFit->GetParError(1), KaonFWHM, KaonFWHMErr, ProtonFit->GetParameter(1), ProtonFit->GetParError(1), ProtonFWHM, ProtonFWHMErr);
    //cout << OutputStr << endl;
}
