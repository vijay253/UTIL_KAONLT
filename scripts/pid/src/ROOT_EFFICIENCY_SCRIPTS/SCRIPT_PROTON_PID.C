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
void SCRIPT_PROTON_PID(string InFilename = "", string OutFilename = "")
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

  Double_t hgcerAdcTdcDiffTi_PMT1; SHMS_EVENTS->SetBranchAddress("P_hgcer_goodAdcTdcDiffTime_PMT1", &hgcerAdcTdcDiffTi_PMT1);
  Double_t hgcerAdcTdcDiffTi_PMT2; SHMS_EVENTS->SetBranchAddress("P_hgcer_goodAdcTdcDiffTime_PMT2", &hgcerAdcTdcDiffTi_PMT2);
  Double_t hgcerAdcTdcDiffTi_PMT3; SHMS_EVENTS->SetBranchAddress("P_hgcer_goodAdcTdcDiffTime_PMT3", &hgcerAdcTdcDiffTi_PMT3);
  Double_t hgcerAdcTdcDiffTi_PMT4; SHMS_EVENTS->SetBranchAddress("P_hgcer_goodAdcTdcDiffTime_PMT4", &hgcerAdcTdcDiffTi_PMT4);

 
  // ######################### First set of Geometrical Cuts #################### 
  TCutG *cutg1 = new TCutG("cutg1",21);
  cutg1->SetVarX("P_hgcer_yAtCer");
  cutg1->SetVarY("P_hgcer_xAtCer");
  cutg1->SetPoint(0,-2,2); cutg1->SetPoint(1,-2,2);  cutg1->SetPoint(2,-1,2.5); cutg1->SetPoint(3,0,3); cutg1->SetPoint(4,1,3); cutg1->SetPoint(5,2,3.3);
  cutg1->SetPoint(6,3,3.0); cutg1->SetPoint(7,4,2.5); cutg1->SetPoint(8,4,2); cutg1->SetPoint(9,4,2); cutg1->SetPoint(10,4,0.5); cutg1->SetPoint(11,4,0.5);
  cutg1->SetPoint(12,4,1); cutg1->SetPoint(13,3,-1); cutg1->SetPoint(14,2,-2); cutg1->SetPoint(15,1,-2.3); cutg1->SetPoint(16,0,-1.5); cutg1->SetPoint(17,-1,-1);
  cutg1->SetPoint(18,-2,0.5); cutg1->SetPoint(19,-2,0.5); cutg1->SetPoint(20,-2,2); cutg1->SetLineColor(kRed); cutg1->SetLineWidth(3);

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
  Double_t PI_X_VARIABLE  = P_kin_secondary_MMp;
  Double_t PI_Y_VARIABLE  = RFTime_SHMS_RFtimeDist;

  Pion_cutg->SetVarX("PI_X_VARIABLE");
  Pion_cutg->SetVarY("PI_Y_VARIABLE");  Pion_cutg->SetPoint(0, 1.07,2.43);  Pion_cutg->SetPoint(1,1.23,2.43);  Pion_cutg->SetPoint(2,1.23,1.50);  Pion_cutg->SetPoint(3,1.07,1.50); Pion_cutg->SetPoint(4,1.07,2.43); Pion_cutg->SetLineColor(kRed);  Pion_cutg->SetLineWidth(3);
  
  // ######################### Geometrical Cuts for selecting Kaon  #################### 
  TCutG *Kaon_cutg = new TCutG("Kaon_cutg",5);
  
  //##############################################################################

  //.... HGC DETECTOR...........................................................................
  TH2D *H2_HG_AERO_NPE                 = new TH2D("H2_HG_AERO_NPE"," HG AERO NPE; HG NPE; AERO NPE;", 80, 0, 40.0, 80, 0, 40.0); 
  TH2D *H2_MM_RFTime                   = new TH2D("H2_MM_RFTime"," Kaon MM vs RFTime; P_kin_secondary_MMK; RFTime_SHMS_RFtimeDist;", 300, 0, 2.0, 300, 0, 4.5); 
  TH1D *H1_HG_NPE_DENO1                = new TH1D("H1_HG_NPE_DENO1","HG NPE ; HG NPE;", 300, 0.0, 40);
  TH1D *H1_HG_NPE_NUM1                 = new TH1D("H1_HG_NPE_NUM1","HG NPE; HG NPE;", 300, 0.0, 40);
  TH1D *H1_HG_NPE_DENO2                = new TH1D("H1_HG_NPE_DENO2","HG NPE (MM CUT); HG NPE;", 300, 0.0, 40);
  TH1D *H1_HG_NPE_NUM2                 = new TH1D("H1_HG_NPE_NUM2","HG NPE (MM CUT); HG NPE;", 300, 0.0, 40);
  TH2D *H2_HG_XY_CHER_DENO1            = new TH2D("H2_HG_XY_CHER_DENO1","XY CHER; P_hgcer_yAtCer; P_hgcer_xAtCer;", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *H2_HG_XY_CHER_NUM1             = new TH2D("H2_HG_XY_CHER_NUM1","XY CHER; P_hgcer_yAtCer; P_hgcer_xAtCer;", 60, -30, 30.0, 80, -40, 40.0 );   
  TH2D *H2_HG_XY_CHER_DENO2            = new TH2D("H2_HG_XY_CHER_DENO2","XY CHER (MM CUT); P_hgcer_yAtCer; P_hgcer_xAtCer;", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *H2_HG_XY_CHER_NUM2             = new TH2D("H2_HG_XY_CHER_NUM2","XY CHER (MM CUT); P_hgcer_yAtCer; P_hgcer_xAtCer;", 60, -30, 30.0, 80, -40, 40.0 );   
  TH1D *H1_MM1                         = new TH1D("H1_MM1"," PROTON MM ; P_kin_secondary_MMp;", 300, 0.0, 2.0);
  TH1D *H1_MM2                         = new TH1D("H1_MM2"," PROTON MM (HOLE CUT OFF); P_kin_secondary_MMp;", 300, 0.0, 2.0);
  TH1D *H1_EPROTON_COIN                = new TH1D("H1_EPROTON_COIN"," EPROTON COIN TIME; P_CTime_eProton;", 300, -40.0, 40.0);
  TH1D *H1_RFTime                      = new TH1D("H1_RFTime"," RFTime; RFTime_SHMS_RFtimeDist;", 300, 0.0, 4.5);


  Double_t PI_DENO_HGC;
  Double_t PI_NUM_HGC;
  
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
   
      HGC_CUT1 = P_hod_goodscinhit == 1 && P_hod_goodstarttime == 1 && P_dc_InsideDipoleExit == 1 && P_hod_betanotrack > 0.5 && P_hod_betanotrack < 1.4;
      HGC_CUT2 = P_CTime_eProton > -2.0 && P_CTime_eProton < 2.0 && P_cal_etottracknorm <0.7; 
      HGC_CUT3 = P_kin_secondary_MMp > 0.988 && P_kin_secondary_MMp < 1.115;
      HGC_CUT4 = P_aero_npeSum  < 2.0;
      HGC_CUT5 = P_aero_yAtCer > -30 && P_aero_yAtCer < 31;
      HGC_CUT6 = (Pion_cutg->IsInside(PI_X_VARIABLE, PI_Y_VARIABLE));
      HGC_CUT7 = RFTime_SHMS_RFtimeDist > 0.0 && RFTime_SHMS_RFtimeDist < 4.0;
     
      PI_DENO_HGC = HGC_CUT1 && HGC_CUT2 && HGC_CUT3 && HGC_CUT4 && HGC_CUT5 && HGC_CUT7; 
      PI_NUM_HGC  =  P_hgcer_npeSum < 0.1 && PI_DENO_HGC;
    
      if(P_hgcer_npeSum > pow(10, -6) && HGC_CUT1 && HGC_CUT2)
	{
	  H2_HG_AERO_NPE->Fill(P_hgcer_npeSum, P_aero_npeSum);
	}

      if(HGC_CUT1 && HGC_CUT2 && HGC_CUT4 && HGC_CUT5 && HGC_CUT7)
	{
	  H1_MM2->Fill(P_kin_secondary_MMp);	
	}


      // PROTON sample without the MM cut
      if(HGC_CUT1 && HGC_CUT2 && HGC_CUT4 && HGC_CUT5 && HGC_CUT7)
	{
	  H1_HG_NPE_DENO1->Fill(P_hgcer_npeSum);
	  H2_HG_XY_CHER_DENO1->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
	  //	  H1_KAON_MM1->Fill(P_kin_secondary_MMK);	
	}      	
	  
      if(P_hgcer_npeSum < 0.1 && HGC_CUT1 && HGC_CUT2 && HGC_CUT4 && HGC_CUT5 && HGC_CUT7)
	{
	  H1_HG_NPE_NUM1->Fill(P_hgcer_npeSum);
	  H2_HG_XY_CHER_NUM1->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
	  H1_MM1->Fill(P_kin_secondary_MMp);	
	  H1_EPROTON_COIN->Fill(P_CTime_eProton);
	  H1_RFTime->Fill(RFTime_SHMS_RFtimeDist);
	  H2_MM_RFTime->Fill(P_kin_secondary_MMp, RFTime_SHMS_RFtimeDist);
	}
	  
      
      // Pion sample with the MM cut      
      if(PI_DENO_HGC)
	{
	      
	  H2_HG_XY_CHER_DENO2->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
	  H1_HG_NPE_DENO2->Fill(P_hgcer_npeSum);
	}      

      if(PI_NUM_HGC)
	{
	  H2_HG_XY_CHER_NUM2->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
	  H1_HG_NPE_NUM2->Fill(P_hgcer_npeSum);
	}
      
	
    }
  
  // PION EFFICIECNY

  Double_t PI_HGC_X1 =  H1_HG_NPE_NUM1->GetEntries(); 
  Double_t PI_HGC_Y1 =  H1_HG_NPE_DENO1->GetEntries(); 

  cout<< "HGC PROTON EFF          = " << (PI_HGC_X1/PI_HGC_Y1)*100 << " +/- "<< sqrt(1/(PI_HGC_X1) + 1/(PI_HGC_Y1))*100<<endl;

  Double_t PI_HGC_X2 =  H1_HG_NPE_NUM2->GetEntries(); 
  Double_t PI_HGC_Y2 =  H1_HG_NPE_DENO2->GetEntries(); 

  cout<< "HGC PROTON EFF (MM CUT) = " << (PI_HGC_X2/PI_HGC_Y2)*100 << " +/- "<< sqrt(1/(PI_HGC_X2) + 1/(PI_HGC_Y2))*100<<endl;

  //Error calcualtions
  
  /*Double_t pi_sc;
    pi_sc = 1.0/6.0;  // No. of background peaks selected to remove the random background
    h1_pion_mm_random->Scale(pi_sc); 
    h1_pion_mm_norandom = (TH1D*)h1_pion_mm->Clone("h1_pion_mm_norandom");
    h1_pion_mm_norandom->Add(h1_pion_mm_random, -1); // Subtraction of random background from prompt peak
  */

  //  Integrate the selected range to get the pions inside the pion peak
  TAxis *MMAxis1 = H1_MM2->GetXaxis();
  Int_t Lowx1   = MMAxis1->FindBin(0.901);    // select pion peak
  Int_t Highx1  = MMAxis1->FindBin(1.054);
  Double_t Pi_mm_BinIntegral1 = H1_MM2->Integral(Lowx1, Highx1);

  TAxis *MMAxis2 = H1_MM1->GetXaxis();
  Int_t Lowx2   = MMAxis2->FindBin(0.901);    // select pion peak
  Int_t Highx2  = MMAxis2->FindBin(1.054);
  Double_t Pi_mm_BinIntegral2 = H1_MM1->Integral(Lowx2, Highx2);
  
  cout<<" NO. OF PROTON                = "<<Pi_mm_BinIntegral1<<endl;
  cout<<" NO. OF PROTON (HOLE CUT OFF) = "<<Pi_mm_BinIntegral2<<endl;
  
  //... Efficiecny ...................................................................................
  TH2D *H2_HGC_EFF1     = new TH2D("H2_HGC_EFF1","Efficiency; Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 );   
  H2_HGC_EFF1    = (TH2D*)H2_HG_XY_CHER_NUM1->Clone("H2_HGC_EFF1");
  H2_HGC_EFF1->Sumw2();
  H2_HGC_EFF1->Divide(H2_HG_XY_CHER_DENO1);
  H2_HGC_EFF1->SetTitle("EFFICIENCY");

  TH2D *H2_HGC_EFF2     = new TH2D("H2_HGC_EFF2","Efficiency; Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 );   
  H2_HGC_EFF2       = (TH2D*)H2_HG_XY_CHER_NUM2->Clone("H2_HGC_EFF2");
  H2_HGC_EFF2->Sumw2();
  H2_HGC_EFF2->Divide(H2_HG_XY_CHER_DENO2);
  H2_HGC_EFF2->SetTitle("EFFICIENCY (MM CUT)");

  //  h2_efficiency->GetYaxis()->SetRangeUser(0.6,1.4);

  //.... AEROGEL DETECTOR...........................................................................

  TH1D *H1_AERO_NPE_DENO                = new TH1D("H1_AERO_NPE_DENO","AERO NPE ; AERO NPE;", 300, 0.0, 40);
  TH1D *H1_AERO_NPE_NUM                 = new TH1D("H1_AERO_NPE_NUM","AERO NPE; AERO NPE;", 300, 0.0, 40);
  TH2D *H2_AERO_XY_CHER_DENO            = new TH2D("H2_AERO_XY_CHER_DENO","XY AERO CHER; P_aero_yAtCer; P_aero_xAtCer;", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *H2_AERO_XY_CHER_NUM             = new TH2D("H2_AERO_XY_CHER_NUM","XY AERO CHER; P_aero_yAtCer; P_aero_xAtCer;", 60, -30, 30.0, 80, -40, 40.0 );   

  Double_t PI_DENO_AERO;
  Double_t PI_NUM_AERO;
  
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++)
    {
      SHMS_EVENTS->GetEntry(i);
      //CUTS      
      Double_t AERO_CUT1;              // FIXED VARIABLES
      Double_t AERO_CUT2;             // COIN TIME AND CAL CUTS      
      Double_t AERO_CUT3;            //  PION MM CUTS
      Double_t AERO_CUT4;           // CHERENKOV CUTS
      Double_t AERO_CUT5;          // AEROGEL POSITON CUTS
 
      Double_t Pi_mm = sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss));
      Double_t K_mm = sqrt(abs(e_miss*e_miss - p_miss*p_miss));
      Double_t P_mm = sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((Mp*Mp) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss));  

      AERO_CUT1 = P_hod_goodscinhit == 1 && P_hod_goodstarttime == 1 && P_dc_InsideDipoleExit == 1 && P_hod_betanotrack > 0.5 && P_hod_betanotrack < 1.4;
      AERO_CUT2 = P_CTime_eProton > -2.0 && P_CTime_eProton < 2.0 && P_cal_etottracknorm <0.7;  
      AERO_CUT3 = RFTime_SHMS_RFtimeDist > 0.0 && RFTime_SHMS_RFtimeDist < 4.0;
      AERO_CUT4 = P_hgcer_npeSum  < 0.1;
      AERO_CUT5 = P_aero_yAtCer > -30 && P_aero_yAtCer < 31;
     
      PI_DENO_AERO = AERO_CUT1 && AERO_CUT2 && AERO_CUT3 && AERO_CUT4; 
      PI_NUM_AERO  =  P_aero_npeSum < 2.0 && PI_DENO_AERO;

      if(PI_DENO_AERO)
	{
	  H1_AERO_NPE_DENO->Fill(P_aero_npeSum);
	  H2_AERO_XY_CHER_DENO->Fill(P_aero_yAtCer, P_aero_xAtCer);
	}      

      if(PI_NUM_AERO)
	{
	  H1_AERO_NPE_NUM->Fill(P_aero_npeSum);
	  H2_AERO_XY_CHER_NUM->Fill(P_aero_yAtCer, P_aero_xAtCer);
	}
    }

  //... Efficiecny ...................................................................................
  Double_t PI_AERO_X1 =  H1_AERO_NPE_NUM->GetEntries(); 
  Double_t PI_AERO_Y1 =  H1_AERO_NPE_DENO->GetEntries(); 

  cout<< "AEROGEL PROTON EFF = " << (PI_AERO_X1/PI_AERO_Y1)*100 << " +/- "<< sqrt(1/(PI_AERO_X1) + 1/(PI_AERO_Y1))*100<<endl;


  TH2D *H2_AERO_EFF     = new TH2D("H2_AERO_EFF","Efficiency; Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 );   
  H2_AERO_EFF    = (TH2D*)H2_AERO_XY_CHER_NUM->Clone("H2_AERO_EFF");
  H2_AERO_EFF->Sumw2();
  H2_AERO_EFF->Divide(H2_AERO_XY_CHER_DENO);
  H2_AERO_EFF->SetTitle("EFFICIENCY");
    

  //Write the info in the root format

  TFile *OutHisto_file = new TFile(foutname,"RECREATE");
  TDirectory *HGC_PROTON_EFF = OutHisto_file->mkdir("HGC_PROTON_EFF");
  HGC_PROTON_EFF->cd();
  H2_MM_RFTime->GetListOfFunctions()->Add(Pion_cutg,"L");
  H2_MM_RFTime->Write();
  H2_MM_RFTime->GetListOfFunctions()->Clear("L");
  H1_EPROTON_COIN->Write();
  H1_RFTime->Write();
  H2_HG_AERO_NPE->Write();
  H1_MM1->Write();
  H1_HG_NPE_DENO1->Write();
  H1_HG_NPE_NUM1->Write();
  H2_HGC_EFF1->GetListOfFunctions()->Add(cutg1,"L");
  H2_HGC_EFF1->Write();
  H2_HGC_EFF1->GetListOfFunctions()->Clear("L");
  H1_HG_NPE_DENO2->Write();
  H2_HG_XY_CHER_DENO2->Write();
  H2_HGC_EFF2->Write();
  TDirectory *AERO_PROTON_EFF = OutHisto_file->mkdir("AERO_PROTON_EFF");
  AERO_PROTON_EFF->cd();
  H2_AERO_EFF->Write();

  OutHisto_file->Close();

  // TString RunNumStr = TInFilename(0,4); Int_t RunNum=(RunNumStr.Atoi());
  //TString OutputStr = Form("%i,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f", RunNum, PionFit->GetParameter(1), PionFit->GetParError(1), PionFWHM, PionFWHMErr, KaonFit->GetParameter(1), KaonFit->GetParError(1), KaonFWHM, KaonFWHMErr, ProtonFit->GetParameter(1), ProtonFit->GetParError(1), ProtonFWHM, ProtonFWHMErr);
  //cout << OutputStr << endl;
}
