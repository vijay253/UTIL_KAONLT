// .... This script has created to anasyzed the HGC's whole in it using the TCutG....
// .... Created Date: Nov 21, 2021 ....
// .... Author: Vijay Kumar ....
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#define HGC_TCutG_cxx
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
void KAON_MM(string InFilename = "", string OutFilename = "")
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
    cout << "Enter a Filename to output: ";
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

  // Defined masses of particles for the calcualtions of massing masses
  //................................................................... 
  Double_t Mp    = 0.93828; 
  Double_t MPi   = 0.13957018;
  Double_t MK    = 0.493677;
  //...................................................................
  // Particles information with acceptnce cuts ONLY... 
  
  // Particles information with "KAON" pid 
  TTree* Kaon_No_HGC_Cut  = (TTree*)InFile->Get("SHMS_Kaons_Without_HGC_Cuts"); Long64_t nEntries_Kaon_No_HGC_Cut  = (Long64_t)Kaon_No_HGC_Cut->GetEntries();

  Double_t P_hgcer_xAtCer;Kaon_No_HGC_Cut->SetBranchAddress("P_hgcer_xAtCer", &P_hgcer_xAtCer);
  Double_t P_hgcer_yAtCer;Kaon_No_HGC_Cut->SetBranchAddress("P_hgcer_yAtCer", &P_hgcer_yAtCer);
  Double_t P_aero_yAtCer;Kaon_No_HGC_Cut->SetBranchAddress("P_aero_yAtCer", &P_aero_yAtCer);
  Double_t Kaon_npeSum;Kaon_No_HGC_Cut->SetBranchAddress("P_hgcer_npeSum", &Kaon_npeSum);
  Double_t Kaon_aero_npeSum;Kaon_No_HGC_Cut->SetBranchAddress("P_aero_npeSum", &Kaon_aero_npeSum);
  Double_t Kaon_gtr_p; Kaon_No_HGC_Cut->SetBranchAddress("P_gtr_p", &Kaon_gtr_p);
  Double_t Kaon_e_miss;Kaon_No_HGC_Cut->SetBranchAddress("emiss", &Kaon_e_miss);
  Double_t Kaon_p_miss;Kaon_No_HGC_Cut->SetBranchAddress("pmiss", &Kaon_p_miss);

  // Missing masses calculations...
  //For Kaon 

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

  
  TH1D *h1_MM_K_IN_TCutG1    = new TH1D("h1_MM_K_IN_TCutG1","Kaon Missing Mass; Missing Mass (Kaon); Events;", 300, 0.5, 2.0 ); 
  TH1D *h1_MM_K_IN_TCutG12   = new TH1D("h1_MM_K_IN_TCutG12","Kaon Missing Mass; Missing Mass (Kaon); Events;", 300, 0.5, 2.0 ); 
  TH1D *h1_MM_K_OUT_TCutG2   = new TH1D("h1_MM_K_OUT_TCutG2","Kaon Missing Mass; Missing Mass (Kaon); Events;", 300, 0.5, 2.0 );
  
  //Fill entries for missing masses
 
  for(Long64_t i = 0; i < nEntries_Kaon_No_HGC_Cut; i++){
    Kaon_No_HGC_Cut->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(Kaon_npeSum > 1.0 || Kaon_aero_npeSum < 1.0 || P_aero_yAtCer >31) continue;
    h1_MM_K_IN_TCutG1->Fill(sqrt(abs(Kaon_e_miss*Kaon_e_miss - Kaon_p_miss*Kaon_p_miss)));
  }
  for(Long64_t i = 0; i < nEntries_Kaon_No_HGC_Cut; i++){
    Kaon_No_HGC_Cut->GetEntry(i);
    if (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(Kaon_npeSum > 1.5 || Kaon_aero_npeSum < 1.0 || P_aero_yAtCer >31) continue;
    h1_MM_K_OUT_TCutG2->Fill(sqrt(abs(Kaon_e_miss*Kaon_e_miss - Kaon_p_miss*Kaon_p_miss)));
  }
 
  for(Long64_t i = 0; i < nEntries_Kaon_No_HGC_Cut; i++){
    Kaon_No_HGC_Cut->GetEntry(i);
    if(!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;   
    if (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue; 
    if(Kaon_npeSum > 1.0 || Kaon_aero_npeSum < 1.0 || P_aero_yAtCer >31) continue;
    h1_MM_K_IN_TCutG12->Fill(sqrt(abs(Kaon_e_miss*Kaon_e_miss - Kaon_p_miss*Kaon_p_miss)));
  }
  //Write the info in the root format

  TFile *OutHisto_file = new TFile(foutname,"RECREATE");
  TDirectory *KAON_MM = OutHisto_file->mkdir("KAON_MM");
  KAON_MM->cd();
  h1_MM_K_IN_TCutG1->Write();
  h1_MM_K_IN_TCutG12->Write();
  h1_MM_K_OUT_TCutG2->Write();
  OutHisto_file->Close();
  // TString RunNumStr = TInFilename(0,4); Int_t RunNum=(RunNumStr.Atoi());
  //TString OutputStr = Form("%i,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f", RunNum, PionFit->GetParameter(1), PionFit->GetParError(1), PionFWHM, PionFWHMErr, KaonFit->GetParameter(1), KaonFit->GetParError(1), KaonFWHM, KaonFWHMErr, ProtonFit->GetParameter(1), ProtonFit->GetParError(1), ProtonFWHM, ProtonFWHMErr);
    //cout << OutputStr << endl;
}
