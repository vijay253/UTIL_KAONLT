// .... This script has created to anasyzed the HGC's whole in it using the TCutG....
// .... Created Date: Nov 21, 2021 ....
// .... Author: Vijay Kumar ....
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#define PION_MM_cxx
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
void PION_MM(string InFilename = "", string OutFilename = "")
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

  // Defined masses of particles for the calcualtions of massing masses
  //................................................................... 
  Double_t Mp    = 0.93828; 
  Double_t MPi   = 0.13957018;
  Double_t MK    = 0.493677;
  //...................................................................
  // Particles information with acceptnce cuts ONLY... 
  
 // Particles information with "PION" pid
  TTree* Pion_No_HGC_Cut  = (TTree*)InFile->Get("SHMS_Pions_Without_HGC_Cuts"); Long64_t nEntries_Pion_No_HGC_Cut  = (Long64_t)Pion_No_HGC_Cut->GetEntries();
  Double_t P_CTime_ePion;Pion_No_HGC_Cut->SetBranchAddress("CTime_ePiCoinTime_ROC1",&P_CTime_ePion);
  Double_t P_RF_tdcTime;Pion_No_HGC_Cut->SetBranchAddress("P_RF_tdcTime", &P_RF_tdcTime);
  Double_t P_hgcer_xAtCer;Pion_No_HGC_Cut->SetBranchAddress("P_hgcer_xAtCer", &P_hgcer_xAtCer);
  Double_t P_hgcer_yAtCer;Pion_No_HGC_Cut->SetBranchAddress("P_hgcer_yAtCer", &P_hgcer_yAtCer);
  Double_t P_aero_yAtCer;Pion_No_HGC_Cut->SetBranchAddress("P_aero_yAtCer", &P_aero_yAtCer);
  Double_t P_gtr_dp; Pion_No_HGC_Cut->SetBranchAddress("P_gtr_dp", &P_gtr_dp);
  Double_t Pion_npeSum;Pion_No_HGC_Cut->SetBranchAddress("P_hgcer_npeSum", &Pion_npeSum);
  Double_t Pion_aero_npeSum;Pion_No_HGC_Cut->SetBranchAddress("P_aero_npeSum", &Pion_aero_npeSum);
  Double_t Pion_gtr_p; Pion_No_HGC_Cut->SetBranchAddress("P_gtr_p", &Pion_gtr_p);
  Double_t Pion_e_miss;Pion_No_HGC_Cut->SetBranchAddress("emiss", &Pion_e_miss);
  Double_t Pion_p_miss;Pion_No_HGC_Cut->SetBranchAddress("pmiss", &Pion_p_miss);

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

  //Histograms for missing masses plots
  
  TH1D *h1_MM_Pi_IN_TCutG1     = new TH1D("h1_MM_Pi_IN_TCutG1","Pion Missing Mass; Missing Mass (Pion); Events;", 300, 0.5, 2.0 ); 
  TH1D *h1_MM_Pi_IN_TCutG12    = new TH1D("h1_MM_Pi_IN_TCutG12","Pion Missing Mass; Missing Mass (Pion); Events;", 300, 0.5, 2.0 );
  TH1D *h1_MM_Pi_OUT_TCutG2    = new TH1D("h1_MM_Pi_OUT_TCutG2","Pion Missing Mass; Missing Mass (Pion); Events;", 300, 0.5, 2.0 );

  // Histogrms for Coin and RF timing info
  TH1D *h1_CTime_ePion_IN_TCutG1         = new TH1D("h1_CTime_ePion_IN_TCutG1","Electron Pion Coin Time; CTime_ePiCoinTime_ROC1; Events;", 300, 0.0, 100.0 ); 
  TH1D *h1_CTime_ePion_IN_TCutG12        = new TH1D("h1_CTime_ePion_IN_TCutG12","Electron Pion Coin Time; CTime_ePiCoinTime_ROC1; Events;", 300, 0.0, 100.0 ); 
  TH1D *h1_CTime_ePion_OUT_TCutG2        = new TH1D("h1_CTime_ePion_OUT_TCutG2","Electron Pion Coin Time; CTime_ePiCoinTime_ROC1; Events;", 300, 0.0, 100.0 ); 
  TH1D *h1_RF_tdc_Time_IN_TCutG1        = new TH1D("h1_RF_tdc_Time_IN_TCutG1","RF Timing Info; P_RF_tdcTime; Events;", 300, -100, 100 ); 
  TH1D *h1_RF_tdc_Time_IN_TCutG12        = new TH1D("h1_RF_tdc_Time_IN_TCutG12","RF Timing Info; P_RF_tdcTime; Events;", 300, -100, 100 ); 
  TH1D *h1_RF_tdc_Time_OUT_TCutG2        = new TH1D("h1_RF_tdc_Time_OUT_TCutG2","RF Timing Info; P_RF_tdcTime; Events;", 300, -100, 100); 

  //Fill entries for missing masses

  for(Long64_t i = 0; i < nEntries_Pion_No_HGC_Cut; i++){
    Pion_No_HGC_Cut->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(Pion_npeSum <1.0 || Pion_aero_npeSum <1.0 || P_aero_yAtCer >31) continue;
    h1_MM_Pi_IN_TCutG1->Fill(sqrt(pow((Pion_e_miss + (sqrt((MK*MK) + (Pion_gtr_p*Pion_gtr_p))) - (sqrt((MPi*MPi) + (Pion_gtr_p*Pion_gtr_p)))), 2) - (Pion_p_miss*Pion_p_miss)));
    h1_CTime_ePion_IN_TCutG1->Fill(P_CTime_ePion);
    h1_RF_tdc_Time_IN_TCutG1->Fill(P_RF_tdcTime);

  }
  
  //Fill entry outside the TCutG2
  
  for(Long64_t i = 0; i < nEntries_Pion_No_HGC_Cut; i++){
    Pion_No_HGC_Cut->GetEntry(i);
    if (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(Pion_npeSum < 3.5 || Pion_aero_npeSum <1.0 || P_aero_yAtCer >31) continue;
    h1_MM_Pi_OUT_TCutG2->Fill(sqrt(pow((Pion_e_miss + (sqrt((MK*MK) + (Pion_gtr_p*Pion_gtr_p))) - (sqrt((MPi*MPi) + (Pion_gtr_p*Pion_gtr_p)))), 2) - (Pion_p_miss*Pion_p_miss)));
    h1_CTime_ePion_OUT_TCutG2->Fill(P_CTime_ePion);
    h1_RF_tdc_Time_OUT_TCutG2->Fill(P_RF_tdcTime);
  }  
 
  //Fill entry between TCutG1 & 2
  
  for(Long64_t i = 0; i < nEntries_Pion_No_HGC_Cut; i++){
    Pion_No_HGC_Cut->GetEntry(i);
    if(!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;   
    if (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(Pion_npeSum < 1.0 || Pion_aero_npeSum <1.0 || P_aero_yAtCer >31) continue;
    h1_MM_Pi_IN_TCutG12->Fill(sqrt(pow((Pion_e_miss + (sqrt((MK*MK) + (Pion_gtr_p*Pion_gtr_p))) - (sqrt((MPi*MPi) + (Pion_gtr_p*Pion_gtr_p)))), 2) - (Pion_p_miss*Pion_p_miss)));
    h1_CTime_ePion_IN_TCutG12->Fill(P_CTime_ePion);
    h1_RF_tdc_Time_IN_TCutG12->Fill(P_RF_tdcTime);

  }

  //Write the info in the root format

  TFile *OutHisto_file = new TFile(foutname,"RECREATE");
  TDirectory *PION_MM = OutHisto_file->mkdir("PION_MM");
  PION_MM->cd();
  h1_MM_Pi_IN_TCutG1->Write();
  h1_MM_Pi_IN_TCutG12->Write();
  h1_MM_Pi_OUT_TCutG2->Write();
  h1_CTime_ePion_IN_TCutG1->Write();
  h1_RF_tdc_Time_IN_TCutG1->Write(); 
  h1_CTime_ePion_IN_TCutG12->Write();
  h1_RF_tdc_Time_IN_TCutG12->Write(); 
  h1_CTime_ePion_OUT_TCutG2->Write();
  h1_RF_tdc_Time_OUT_TCutG2->Write(); 

  OutHisto_file->Close();

  // TString RunNumStr = TInFilename(0,4); Int_t RunNum=(RunNumStr.Atoi());
  //TString OutputStr = Form("%i,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f", RunNum, PionFit->GetParameter(1), PionFit->GetParError(1), PionFWHM, PionFWHMErr, KaonFit->GetParameter(1), KaonFit->GetParError(1), KaonFWHM, KaonFWHMErr, ProtonFit->GetParameter(1), ProtonFit->GetParError(1), ProtonFWHM, ProtonFWHMErr);
    //cout << OutputStr << endl;
}
