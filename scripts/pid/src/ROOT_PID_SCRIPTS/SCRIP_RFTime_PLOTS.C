// .... This script has created to pid study....
// .... Created Date: March 23, 2021 ....
// .... Author: Vijay Kumar ....
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#define EFFICIENCY_cxx
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
void SCRIP_RFTime_PLOTS(string InFilename = "", string OutFilename = "")
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
    Outpath = Replaypath+"/ROOTfiles/PYTHON_OUTPUT";
    // Output path for output files (pdf or root )
    Outpath1 = Replaypath+"/ROOTfiles/ROOT_OUTPUT";
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
    cout << "Enter a Filename to output to: ";
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
  TString fouttxt  = Outpath1+"/" + TOutFilename + ".txt";
  TString foutpdf = Outpath1+"/" + TOutFilename + ".pdf";
  
  // Particles information with acceptnce cuts ONLY...
  
  TTree* SHMS_EVENTS  = (TTree*)InFile->Get("SHMS_PION_SAMPLE"); Long64_t nEntries_SHMS_EVENTS  = (Long64_t)SHMS_EVENTS->GetEntries();   // InFile
  Double_t RFTime_SHMS_RFtimeDist ;SHMS_EVENTS->SetBranchAddress("RFTime_SHMS_RFtimeDist", &RFTime_SHMS_RFtimeDist);
  Double_t P_kin_secondary_MMpi ;SHMS_EVENTS->SetBranchAddress("P_kin_secondary_MMpi", &P_kin_secondary_MMpi);
  Double_t P_kin_secondary_MMK ;SHMS_EVENTS->SetBranchAddress("P_kin_secondary_MMK", &P_kin_secondary_MMK);
  Double_t P_kin_secondary_MMp ;SHMS_EVENTS->SetBranchAddress("P_kin_secondary_MMp", &P_kin_secondary_MMp);
  Double_t P_hgcer_npeSum;SHMS_EVENTS->SetBranchAddress("P_hgcer_npeSum", &P_hgcer_npeSum);
  Double_t P_aero_npeSum; SHMS_EVENTS->SetBranchAddress("P_aero_npeSum", &P_aero_npeSum);
  Double_t P_hod_goodscinhit; SHMS_EVENTS->SetBranchAddress("P_hod_goodscinhit", &P_hod_goodscinhit);
  Double_t P_hod_betanotrack; SHMS_EVENTS->SetBranchAddress("P_hod_betanotrack", &P_hod_betanotrack);
  Double_t P_hod_goodstarttime; SHMS_EVENTS->SetBranchAddress("P_hod_goodstarttime", &P_hod_goodstarttime);
  Double_t P_dc_InsideDipoleExit; SHMS_EVENTS->SetBranchAddress("P_dc_InsideDipoleExit", &P_dc_InsideDipoleExit);
  Double_t P_hgcer_xAtCer; SHMS_EVENTS->SetBranchAddress("P_hgcer_xAtCer", &P_hgcer_xAtCer);
  Double_t P_hgcer_yAtCer; SHMS_EVENTS->SetBranchAddress("P_hgcer_yAtCer", &P_hgcer_yAtCer);
  Double_t P_aero_xAtCer; SHMS_EVENTS->SetBranchAddress("P_aero_xAtCer", &P_aero_xAtCer);
  Double_t P_aero_yAtCer; SHMS_EVENTS->SetBranchAddress("P_aero_yAtCer", &P_aero_yAtCer);
  Double_t P_cal_etotnorm; SHMS_EVENTS->SetBranchAddress("P_cal_etotnorm", &P_cal_etotnorm);
  Double_t P_cal_etottracknorm; SHMS_EVENTS->SetBranchAddress("P_cal_etottracknorm", &P_cal_etottracknorm);
  Double_t P_gtr_beta; SHMS_EVENTS->SetBranchAddress("P_gtr_beta", &P_gtr_beta);
  Double_t P_gtr_p; SHMS_EVENTS->SetBranchAddress("P_gtr_p", &P_gtr_p);
  Double_t P_gtr_dp; SHMS_EVENTS->SetBranchAddress("P_gtr_dp", &P_gtr_dp);
  Double_t e_miss; SHMS_EVENTS->SetBranchAddress("emiss", &e_miss);
  Double_t p_miss; SHMS_EVENTS->SetBranchAddress("pmiss", &p_miss);
  Double_t P_CTime_ePion;SHMS_EVENTS->SetBranchAddress("CTime_ePiCoinTime_ROC1",&P_CTime_ePion);
  Double_t P_CTime_eKaon;SHMS_EVENTS->SetBranchAddress("CTime_eKCoinTime_ROC1",&P_CTime_eKaon);
  Double_t P_CTime_eProton;SHMS_EVENTS->SetBranchAddress("CTime_epCoinTime_ROC1",&P_CTime_eProton);
  
  // Hist for filling up the RFTime
  TH1D *H1_RFTime_ACCEP_CUTS      = new TH1D("H1_RFTime_ACCEP_CUTS","RFTime with acceptance cuts; RFTime_SHMS_RFtimeDist;", 300, 0.0, 4.5);
  TH1D *H1_RFTime_PION_PID        = new TH1D("H1_RFTime_PION_PID","RFTime with PION PID; RFTime_SHMS_RFtimeDist;", 300, 0.0, 4.5);
  TH1D *H1_RFTime_KAON_PID        = new TH1D("H1_RFTime_KAON_PID","RFTime with KAON PID; RFTime_SHMS_RFtimeDist;", 300, 0.0, 4.5);
  TH1D *H1_RFTime_PROTON_PID      = new TH1D("H1_RFTime_PROTON_PID","RFTime with PROTON PID; RFTime_SHMS_RFtimeDist;", 300, 0.0, 4.5);
  
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++)
    {
      SHMS_EVENTS->GetEntry(i);
     //CUTS      
      Double_t HGC_CUT1;              // FIXED VARIABLES
      Double_t HGC_CUT2;             // COIN TIME AND CAL CUTS      
      Double_t HGC_CUT3;            //  PION MM CUTS
      Double_t HGC_CUT4;           // CHERENKOV CUTS
      Double_t HGC_CUT5;          // AEROGEL POSITON CUTS
      Double_t HGC_CUT6;         // OUTSIDE REGION OF THE HOLE
      Double_t HGC_CUT7;        //  RFTIME CUT
      Double_t HGC_CUT8;        

      HGC_CUT1 = P_hod_goodscinhit == 1 && P_hod_goodstarttime == 1 && P_dc_InsideDipoleExit == 1;
      HGC_CUT2 = P_hod_betanotrack > 0.5 && P_hod_betanotrack < 1.4 && P_cal_etottracknorm <0.7;
      HGC_CUT3 = P_CTime_ePion > 0.0 && P_CTime_ePion < 2.0; 
      HGC_CUT4 = P_CTime_eKaon > 0.0 && P_CTime_eKaon < 2.0;  
      HGC_CUT5 = P_CTime_eProton > 0.0 && P_CTime_eProton < 2.0; 
      HGC_CUT6 = P_kin_secondary_MMK > 1.07 && P_kin_secondary_MMK < 1.23;
      HGC_CUT7 = P_aero_npeSum  > 0.0;
      HGC_CUT8 = P_aero_yAtCer > -30 && P_aero_yAtCer < 31;

      if(HGC_CUT1 && HGC_CUT2)
	{
	  H1_RFTime_ACCEP_CUTS->Fill(RFTime_SHMS_RFtimeDist);
	}
      if(P_hgcer_npeSum > 1.5 && P_aero_npeSum  > 1.5 && HGC_CUT1 && HGC_CUT2 && HGC_CUT3 && HGC_CUT8)
	{
	  H1_RFTime_PION_PID->Fill(RFTime_SHMS_RFtimeDist);
	}
      if(P_hgcer_npeSum < 1.5 && P_aero_npeSum  > 1.5 && HGC_CUT1 && HGC_CUT2 && HGC_CUT3 && HGC_CUT8)
	{
	  H1_RFTime_KAON_PID->Fill(RFTime_SHMS_RFtimeDist);
	}
      if(P_hgcer_npeSum < 1.5 && P_aero_npeSum  < 1.5 && HGC_CUT1 && HGC_CUT2 && HGC_CUT3 && HGC_CUT8)
	{
	  H1_RFTime_PROTON_PID->Fill(RFTime_SHMS_RFtimeDist);
	}
            
    }
      TCanvas *c = new TCanvas ("c");
      c->Divide(2,2); 
      c->cd(1);
      H1_RFTime_ACCEP_CUTS->SetLineColor(kRed);
      H1_RFTime_ACCEP_CUTS->Draw("");
      c->cd(2);
      H1_RFTime_PION_PID->SetLineColor(kBlack);
      H1_RFTime_PION_PID->Draw("");
      c->cd(3);
      H1_RFTime_KAON_PID->SetLineColor(kBlue);
      H1_RFTime_KAON_PID->Draw("");
      c->cd(4);
      H1_RFTime_PROTON_PID->SetLineColor(kGreen);
      H1_RFTime_PROTON_PID->Draw("");
      //Now save the TCanvas
      c->Print(foutpdf);
}
