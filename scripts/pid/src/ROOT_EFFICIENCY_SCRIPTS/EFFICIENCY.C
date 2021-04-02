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
void EFFICIENCY(string InFilename = "", string OutFilename = "")
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
  
  
  
//#################################################################### 
  
  Double_t Mp    = 0.93828;      // Mass of Proton
  Double_t MPi   = 0.13957018;  // Mass of Pion
  Double_t MK    = 0.493677;   // Mass of Kaon
  
  //#################################################################### 
  
  // Particles information with acceptnce cuts ONLY...
  
  TTree* SHMS_EVENTS  = (TTree*)InFile->Get("SHMS_Events_wCuts"); Long64_t nEntries_SHMS_EVENTS  = (Long64_t)SHMS_EVENTS->GetEntries();   // InFile

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
  Double_t P_RF_time;SHMS_EVENTS->SetBranchAddress("RF_time", &P_RF_time);

 
  // ######################### First set of Geometrical Cuts #################### 
  TCutG *cutg1 = new TCutG("cutg1",21);
  cutg1->SetVarX("P_hgcer_yAtCer");
  cutg1->SetVarY("P_hgcer_xAtCer");
  cutg1->SetPoint(0,-25,2); cutg1->SetPoint(1,-2,2);  cutg1->SetPoint(2,-1,2.5); cutg1->SetPoint(3,0,3); cutg1->SetPoint(4,1,3); cutg1->SetPoint(5,2,3.3);
  cutg1->SetPoint(6,3,3.0); cutg1->SetPoint(7,4,2.5); cutg1->SetPoint(8,5,2); cutg1->SetPoint(9,25,2); cutg1->SetPoint(10,25,0.5); cutg1->SetPoint(11,5,0.5);
  cutg1->SetPoint(12,4,1); cutg1->SetPoint(13,3,-1); cutg1->SetPoint(14,2,-2); cutg1->SetPoint(15,1,-2.3); cutg1->SetPoint(16,0,-1.5); cutg1->SetPoint(17,-1,-1);
  cutg1->SetPoint(18,-2,0.5); cutg1->SetPoint(19,-25,0.5); cutg1->SetPoint(20,-25,2); cutg1->SetLineColor(kRed); cutg1->SetLineWidth(3);

  // ######################### Second set of Geometrical Cuts #################### 

  TCutG *cutg2 = new TCutG("cutg2",19);
  cutg2->SetVarX("P_hgcer_yAtCer");
  cutg2->SetVarY("P_hgcer_xAtCer");  cutg2->SetPoint(0,-25,2);  cutg2->SetPoint(1,-2,2);  cutg2->SetPoint(2,0,3.5);  cutg2->SetPoint(3,2,5.5);  cutg2->SetPoint(4,4,5);
  cutg2->SetPoint(5,6,4.5);  cutg2->SetPoint(6,8,4);  cutg2->SetPoint(7,10,2);  cutg2->SetPoint(8,25,2);  cutg2->SetPoint(9,25,0.5);  cutg2->SetPoint(10,6,0.5);
  cutg2->SetPoint(11,4,-1);  cutg2->SetPoint(12,2,-3);  cutg2->SetPoint(13,0,-3.5);  cutg2->SetPoint(14,-2,-2);  cutg2->SetPoint(15,-4,-0.75);  cutg2->SetPoint(16,-6,-0.5);
  cutg2->SetPoint(17,-25,0.5);  cutg2->SetPoint(18,-25,2);  cutg2->SetLineColor(kRed);  cutg2->SetLineWidth(3);

  // ######################### Third set of Geometrical Cuts #################### 
  TCutG *cutg3 = new TCutG("cutg3",14);
  cutg3->SetVarX("P_hgcer_yAtCer");
  cutg3->SetVarY("P_hgcer_xAtCer");  cutg3->SetPoint(0,-20,3);  cutg3->SetPoint(1,-3,3);  cutg3->SetPoint(2,-1,4);  cutg3->SetPoint(3,2,5);  cutg3->SetPoint(4,4,3);
  cutg3->SetPoint(5,20,3);  cutg3->SetPoint(6,20,1.70);  cutg3->SetPoint(7,6,1.70);  cutg3->SetPoint(8,3.75,0);  cutg3->SetPoint(9,2,-2.1);  cutg3->SetPoint(10,-1,0);  cutg3->SetPoint(11,-3,1.70);
  cutg3->SetPoint(12,-20,1.70);  cutg3->SetPoint(13,-20,3);  cutg3->SetLineColor(kRed);  cutg3->SetLineWidth(3);

  // ######################### Geometrical Cuts for selecting Pion  #################### 
  TCutG *Pion_cutg = new TCutG("Pion_cutg",5);
  Double_t PI_X_VARIABLE = sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss));
  Double_t PI_Y_VARIABLE  = P_RF_time;

  Pion_cutg->SetVarX("PI_X_VARIABLE");
  Pion_cutg->SetVarY("PI_Y_VARIABLE");  Pion_cutg->SetPoint(0,0.901,1.469);  Pion_cutg->SetPoint(1,1.054,1.469);  Pion_cutg->SetPoint(2,1.054,2.603);  Pion_cutg->SetPoint(3,0.901,2.603); Pion_cutg->SetPoint(4,0.901,1.469); Pion_cutg->SetLineColor(kRed);  Pion_cutg->SetLineWidth(3);
  /*  
  Pion_cutg->SetVarX("sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss))");
  Pion_cutg->SetVarY("P_RF_time");  Pion_cutg->SetPoint(0,0.901,1.469);  Pion_cutg->SetPoint(1,1.054,1.469);  Pion_cutg->SetPoint(2,1.054,2.603);  Pion_cutg->SetPoint(3,0.901,2.603); Pion_cutg->SetPoint(4,0.901,1.469); Pion_cutg->SetLineColor(kRed);  Pion_cutg->SetLineWidth(3);
  */

  // ######################### Geometrical Cuts for selecting Kaon  #################### 
  TCutG *Kaon_cutg = new TCutG("Kaon_cutg",5);
  
  //##############################################################################

  //.................................................................................................. 
  // Efficiency calculations of the HGC and Aerogel detectors for Pion, Kaon and Proton candidates
  //..................................................................................................  
  
  //.... First HGC detector...........................................................................
  //...Sample of the each particle selected without HGC detector......................................
  TH1D *h1_npeSum_nohgc_cuts    = new TH1D("h1_npeSum_nohgc_cuts","HGC NPE NO HGC CUTS; HGC NPE;", 300, 0.0, 40);
  TH2D *h2_XY_cherenkov_DENO     = new TH2D("h2_XY_cherenkov_DENO","Efficiency; Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH1D *h1_NPE_1_CUT        = new TH1D("h1_NPE_1_CUT","HGC CUT = > 1.5; HGC NPE;", 300, 0.0, 40);
  TH2D *h2_XY_cherenkov_NUM        = new TH2D("h2_XY_cherenkov_NUM","Efficiency; Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 );   
  TH1D *h1_P_cal_etottracknorm = new TH1D("h1_P_cal_etottracknorm","P_cal_etottracknorm; P_cal_etottracknorm;", 300, 0.0, 2.0);
  TH1D *h1_test1 = new TH1D("h1_test1"," Zero bin entry of HGC; Pion MM;", 300, 0.0, 2.0);
  TH1D *h1_test2 = new TH1D("h1_test2"," Zero bin entry of HGC; Kaon MM;", 300, 0.0, 2.0);
  TH1D *h1_test3 = new TH1D("h1_tes3"," Zero bin entry of HGC; Proton MM;", 300, 0.0, 2.0);
  TH1D *h1_test = new TH1D("h1_test"," After zero bin entry of HGC; Pion MM;", 300, 0.0, 2.0);

  Double_t PI_DENO_HGC;
  Double_t PI_NUM_HGC;
  
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++)
    {
      SHMS_EVENTS->GetEntry(i);
      //CUTS      
      Double_t HGC_CUT1;              // FIXED VARIABLES
      Double_t HGC_CUT2;             // COIN TIME AND CAL CUTS      
      Double_t HGC_CUT3;            // RFTIME & PION MM CUTS
      Double_t HGC_CUT4;           // CHERENKOV CUTS
      Double_t HGC_CUT5;          // AEROGEL POSITON CUTS

      Double_t Pi_mm = sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss));
      Double_t K_mm = sqrt(abs(e_miss*e_miss - p_miss*p_miss));
      Double_t P_mm = sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((Mp*Mp) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss));  

      HGC_CUT1 = P_hod_goodscinhit == 1 && P_hod_goodstarttime == 1 && P_dc_InsideDipoleExit == 1;
      HGC_CUT2 = P_CTime_ePion > 42 && P_CTime_ePion < 46 && P_cal_etottracknorm <0.7; 
      HGC_CUT3 = P_RF_time > 1.469 && Pi_mm > 0.901 && P_RF_time < 2.603 && Pi_mm < 1.054;
      HGC_CUT4 = P_hgcer_npeSum > pow(10,-6) && P_aero_npeSum  > 1.5;
      HGC_CUT5 = P_aero_yAtCer > -30 && P_aero_yAtCer < 31;

      PI_DENO_HGC = HGC_CUT1 && HGC_CUT2 && HGC_CUT3 && HGC_CUT4 && HGC_CUT5; 
      PI_NUM_HGC  =  P_hgcer_npeSum > 1.5 && PI_DENO_HGC;


      if(PI_DENO_HGC)
	{
	  h1_npeSum_nohgc_cuts->Fill(P_hgcer_npeSum);
	  h2_XY_cherenkov_DENO->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
	  h1_P_cal_etottracknorm->Fill(P_cal_etottracknorm);

	}      
      if(PI_NUM_HGC)
	{
	  h1_NPE_1_CUT->Fill(P_hgcer_npeSum);
	  h2_XY_cherenkov_NUM->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
	}
     
      if(HGC_CUT1&&HGC_CUT2&&P_hgcer_npeSum < pow(10,-6) && P_aero_npeSum  > 1.5&&HGC_CUT5)	
	{
	  h1_test1->Fill(Pi_mm);
	  h1_test2->Fill(K_mm);
	  h1_test3->Fill(P_mm);
	}
      if(HGC_CUT1&&HGC_CUT2&&P_hgcer_npeSum > pow(10,-6) && P_aero_npeSum  > 1.5&&HGC_CUT5)	
	{
	  h1_test->Fill(Pi_mm);
	}
    }
  
  // PION EFFICIECNY

  Double_t PI_X =  h1_NPE_1_CUT->GetEntries(); 
  Double_t PI_Y =  h1_npeSum_nohgc_cuts->GetEntries(); 

  cout<< "PION EFF HGC = " << (PI_X/PI_Y)*100 << " +/- "<< sqrt(1/(PI_X) + 1/(PI_Y))*100<<endl;
  //Error calcualtions
  
  /*Double_t pi_sc;
  pi_sc = 1.0/6.0;  // No. of background peaks selected to remove the random background
  h1_pion_mm_random->Scale(pi_sc); 
  h1_pion_mm_norandom = (TH1D*)h1_pion_mm->Clone("h1_pion_mm_norandom");
  h1_pion_mm_norandom->Add(h1_pion_mm_random, -1); // Subtraction of random background from prompt peak
  
  // Integrate the selected range to get the pions inside the pion peak
  TAxis *MMAxis = h1_pion_mm_norandom->GetXaxis();
  Int_t Lowx   = MMAxis->FindBin(0.935);    // select pion peak
  Int_t Highx  = MMAxis->FindBin(0.963);
  Double_t Pi_mm_BinIntegral = h1_pion_mm_norandom->Integral(Lowx, Highx);
  cout<<" Number of Pions = "<<Pi_mm_BinIntegral<<endl;
  */

  
  //... Efficiecny ...................................................................................
  TH2D *h2_EFF     = new TH2D("h2_EFF","Efficiency; Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 );   
  h2_EFF    = (TH2D*)h2_XY_cherenkov_NUM->Clone("h2_EFF");
  h2_EFF->Sumw2();
  h2_EFF->Divide(h2_XY_cherenkov_DENO);
  //  h2_efficiency->GetYaxis()->SetRangeUser(0.6,1.4);

  //.... Now  Aerogel detector...........................................................................
  //...Sample of the each particle selected without Aerogel detector......................................

  

  //...Sample of the each particle selected with Aerogel detector.........................................



  //... Efficiecny .......................................................................................

 
  //.......................................................................................................

 
  //Write the info in the root format
		       
  TFile *OutHisto_file = new TFile(foutname,"RECREATE");
  TDirectory *PION_EFFICIECNY = OutHisto_file->mkdir("PION_EFFICIECNY");
  PION_EFFICIECNY->cd();
  h1_npeSum_nohgc_cuts->Write();
  h1_NPE_1_CUT->Write();
  // h1_pion_mm->Write();
  //  h1_pion_mm_norandom->Write();
  h2_EFF->Write();
  h1_P_cal_etottracknorm->Write();
  h1_test1->Write();
  h1_test2->Write();
  h1_test3->Write();
  h1_test->Write();
  OutHisto_file->Close();
  //Save the TCutGs open this when needed 
  /*  cutg1->SaveAs(Outpath1+"/" + "TCutG1_" + TOutFilename  +".txt");
      cutg2->SaveAs(Outpath1+"/" + "TCutG2_" + TOutFilename  +".txt");
      cutg3->SaveAs(Outpath1+"/" + "TCutG3_" + TOutFilename  +".txt");
  */
  // TString RunNumStr = TInFilename(0,4); Int_t RunNum=(RunNumStr.Atoi());
  //TString OutputStr = Form("%i,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f", RunNum, PionFit->GetParameter(1), PionFit->GetParError(1), PionFWHM, PionFWHMErr, KaonFit->GetParameter(1), KaonFit->GetParError(1), KaonFWHM, KaonFWHMErr, ProtonFit->GetParameter(1), ProtonFit->GetParError(1), ProtonFWHM, ProtonFWHMErr);
  //cout << OutputStr << endl;
}
