// .... This script has created to pid study....
// .... Created Date: Dec 10, 2021 ....
// .... Author: Vijay Kumar ....
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
#define HGC_pid_cxx
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
void SHMS_pid(string InFilename = "", string OutFilename = "")
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
  Double_t P_hgcer_xAtCer; SHMS_EVENTS->SetBranchAddress("P_hgcer_xAtCer", &P_hgcer_xAtCer);
  Double_t P_hgcer_yAtCer; SHMS_EVENTS->SetBranchAddress("P_hgcer_yAtCer", &P_hgcer_yAtCer);
  Double_t P_aero_xAtCer; SHMS_EVENTS->SetBranchAddress("P_aero_xAtCer", &P_aero_xAtCer);
  Double_t P_aero_yAtCer; SHMS_EVENTS->SetBranchAddress("P_aero_yAtCer", &P_aero_yAtCer);
  Double_t P_cal_etotnorm; SHMS_EVENTS->SetBranchAddress("P_cal_etotnorm", &P_cal_etotnorm);
  Double_t P_gtr_beta; SHMS_EVENTS->SetBranchAddress("P_gtr_beta", &P_gtr_beta);
  Double_t P_gtr_p; SHMS_EVENTS->SetBranchAddress("P_gtr_p", &P_gtr_p);
  Double_t P_gtr_dp; SHMS_EVENTS->SetBranchAddress("P_gtr_dp", &P_gtr_dp);
  Double_t e_miss; SHMS_EVENTS->SetBranchAddress("emiss", &e_miss);
  Double_t p_miss; SHMS_EVENTS->SetBranchAddress("pmiss", &p_miss);
  Double_t P_CTime_ePion;SHMS_EVENTS->SetBranchAddress("CTime_ePiCoinTime_ROC1",&P_CTime_ePion);
  Double_t P_CTime_eKaon;SHMS_EVENTS->SetBranchAddress("CTime_eKCoinTime_ROC1",&P_CTime_eKaon);
  Double_t P_CTime_eProton;SHMS_EVENTS->SetBranchAddress("CTime_epCoinTime_ROC1",&P_CTime_eProton);
  Double_t P_RF_time;SHMS_EVENTS->SetBranchAddress("RF_time", &P_RF_time);

  //  Double_t K_mm = sqrt(abs(e_miss*e_miss - p_miss*p_miss));

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

  // ######################### Geometrical Cuts for selecting Kaon  #################### 
  TCutG *Kaon_cutg = new TCutG("Kaon_cutg",5);
  /*Kaon_cutg->SetVarX("sqrt(abs(e_miss*e_miss - p_miss*p_miss))");
  Kaon_cutg->SetVarY("P_RF_time");  Kaon_cutg->SetPoint(0,0.77,1.50);  Kaon_cutg->SetPoint(1,1.019,1.50);  Kaon_cutg->SetPoint(2,1.019,3.033);  Kaon_cutg->SetPoint(3,0.77,3.033); Kaon_cutg->SetPoint(4,0.77,1.50); Kaon_cutg->SetLineColor(kRed);  Kaon_cutg->SetLineWidth(3);
  */
  
  //##############################################################################

  // Defined histograms for TCutGs
  TH2D *h2_XYAtCer1                    = new TH2D("h2_XYAtCer1","HGC, P_hgcer_npeSum => 1.5; P_hgcer_yAtCer; P_hgcer_xAtCer;", 300, -40, 40, 300, -40, 40 );
  TH2D *h2_XYAtCer2                    = new TH2D("h2_XYAtCer2","HGC, P_hgcer_npeSum => 5.0; P_hgcer_yAtCer; P_hgcer_xAtCer;", 300, -40, 40, 300, -40, 40 );
  TH3D *h3_aero_XYAtCer_npeSum         = new TH3D("h3_aero_XYAtCer_npeSum","Aero; P_aero_yAtAero; P_aero_xAtAero; P_aero_npeSum", 300, -50, 50, 300, -50, 50, 300, 0, 30);
  TH3D *h3_aero_XYAtCer_nocut_npeSum   = new TH3D("h3_aero_XYAtCer_nocut_npeSum","Aero; P_aero_yAtAero; P_aero_xAtAero; P_aero_npeSum", 300, -50, 50, 300, -50, 50, 300, 0, 30);
  TH3D *h3_XYAtCer_npeSum1             = new TH3D("h3_XYAtCer_npeSum1","HGC, P_hgcer_npeSum => 1.5; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
  TH3D *h3_XYAtCer_npeSum2             = new TH3D("h3_XYAtCer_npeSum2","HGC, P_hgcer_npeSum => 5.0; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
  TH3D *h3_XYAtCer_npeSum3             = new TH3D("h3_XYAtCer_npeSum3","HGC, P_hgcer_npeSum => 7.0; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
  TH2D *h2_npeSum_IN_TCutG1            = new TH2D("h2_npeSum_IN_TCutG1","HGC, Entries Inside 1st Region; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 40, 300, 0.0, 30);
  TH2D *h2_npeSum_IN_TCutG12           = new TH2D("h2_npeSum_IN_TCutG12","HGC, Entries b/w 1st & 2nd Regions; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 40, 300, 0.0, 30);
  TH2D *h2_npeSum_IN_TCutG23           = new TH2D("h2_npeSum_IN_TCutG23","HGC, Entries b/w 2nd & 3rd Regions; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 40, 300, 0.0, 30);
  TH2D *h2_npeSum_OUT_TCutG3           = new TH2D("h2_npeSum_OUT_TCutG3","HGC, Entries outside 3rd Region; HGC NPE; Aerogel NPE;", 300, 0.0, 40, 300, 0.0, 30);
  TH2D *h2_npeSum                      = new TH2D("h2_npeSum","HGC vs Aero ; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 40, 300, 0.0, 30);

  //##############################################################################

  // Defined histograms for scanning efficiecny 
  TH2D *h2_Eff_Pos1    = new TH2D("h2_Eff_Pos1","Efficiency vs Position; Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *h2_Eff_Pos2    = new TH2D("h2_Eff_Pos2","Efficiency vs Position; Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *h2_Eff_Pos3    = new TH2D("h2_Eff_Pos3","Efficiency vs Position; Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 

  TH1D *h1_Eff_Del1    = new TH1D("h1_Eff_Del1","Efficieny vs Delta; Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *h1_Eff_Del2    = new TH1D("h1_Eff_Del2","Efficiency vs Delta; Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *h1_Eff_Del3    = new TH1D("h1_Eff_Del3","Efficiency vs Delta; Delta (%); Efficiency;", 60, -10, 20.0); 

  TH1D *h1_Eff1_xAtCer    = new TH1D("h1_Eff1_xAtCer","xAtCer vs Efficiency; xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *h1_Eff2_xAtCer    = new TH1D("h1_Eff2_xAtCer","xAtCer vs Efficiency; xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *h1_Eff3_xAtCer    = new TH1D("h1_Eff3_xAtCer","xAtCer vs Efficiecny; xAtCer; Efficiency;", 80, -40, 40.0); 

  //##############################################################################
 
  //Fill xyAtCer entry
      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.5) continue;
    if (P_aero_yAtCer < -30 || P_aero_yAtCer > 31) continue;
    h2_XYAtCer1->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 5) continue;
    if (P_aero_yAtCer < -30 || P_aero_yAtCer > 31) continue;
    h2_XYAtCer2->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }
  //Fill entry for 3D

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.5 || P_aero_yAtCer < -30 || P_aero_yAtCer > 31) continue;   //P_hgcer_npeSum < 1.5 || removed
    h3_XYAtCer_npeSum1->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer,P_hgcer_npeSum);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 5 || P_aero_yAtCer < -30 || P_aero_yAtCer > 31) continue;    // P_hgcer_npeSum < 5 || removed
    h3_XYAtCer_npeSum2->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer,P_hgcer_npeSum);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 7 || P_aero_yAtCer < -30 || P_aero_yAtCer > 31) continue;   // P_hgcer_npeSum < 7 || removed
    h3_XYAtCer_npeSum3->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer,P_hgcer_npeSum);
  }

  //Fill entry for Aero

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    h3_aero_XYAtCer_nocut_npeSum->Fill(P_aero_yAtCer, P_aero_xAtCer, P_aero_npeSum);
    if(P_aero_yAtCer < -30 || P_aero_yAtCer > 31) continue;
    h3_aero_XYAtCer_npeSum->Fill(P_aero_yAtCer, P_aero_xAtCer, P_aero_npeSum);
  }

  // Project 3D histogram on XY

  TProfile2D *h3_aero_XYAtCer_npeSum_pyx = new TProfile2D("h3_aero_XYAtCer_npeSum_pyx","Aero; P_aero_yAtAero; P_aero_xAtAero ",300,-50,50, 300,-50,50, 0, 30);
  h3_aero_XYAtCer_npeSum->Project3DProfile("yx");

  TProfile2D *h3_aero_XYAtCer_nocut_npeSum_pyx = new TProfile2D("h3_aero_XYAtCer_nocut_npeSum_pyx","Aero; P_aero_yAtAero; P_aero_xAtAero ",300,-50,50, 300,-50,50, 0, 30);
  h3_aero_XYAtCer_nocut_npeSum->Project3DProfile("yx");

  TProfile2D *h3_XYAtCer_npeSum1_pyx = new TProfile2D("h3_XYAtCer_npeSum1_pyx","HGC,P_hgcer_npeSum => 1.5; P_hgcer_yAtCer; P_hgcer_xAtCer ",300,-40,40, 300,-40,40, 0, 30);
  h3_XYAtCer_npeSum1->Project3DProfile("yx");

  TProfile2D *h3_XYAtCer_npeSum2_pyx = new TProfile2D("h3_XYAtCer_npeSum2_pyx","HGC, P_hgcer_npeSum => 5.0; P_hgcer_yAtCer; P_hgcer_xAtCer ",300,-40,40, 300,-40,40, 0, 30);
  h3_XYAtCer_npeSum2->Project3DProfile("yx");
  TProfile2D *h3_XYAtCer_npeSum3_pyx = new TProfile2D("h3_XYAtCer_npeSum3_pyx","HGC, P_hgcer_npeSum => 7.0; P_hgcer_yAtCer; P_hgcer_xAtCer ",300,-40,40, 300,-40,40, 0, 30);
  h3_XYAtCer_npeSum3->Project3DProfile("yx");

  //Fill NPEs entries which are inside 1st Region      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if ((!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (P_hgcer_npeSum < 0.1 || P_aero_yAtCer < -30 || P_aero_yAtCer > 31)) continue;
    h2_npeSum_IN_TCutG1->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }
  //Fill entries b/w 1st & 2nd Regions      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if ((!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) ||(cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (P_hgcer_npeSum < 0.1 || P_aero_yAtCer < -30 || P_aero_yAtCer > 31)) continue;
    h2_npeSum_IN_TCutG12->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }

  //Fill entries b/w 2st & 3nd Regions      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if ((!cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (P_hgcer_npeSum < 0.1 || P_aero_yAtCer < -30 || P_aero_yAtCer > 31))  continue;
    h2_npeSum_IN_TCutG23->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }

  //Fill entries outside 3nd Region      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer) || P_hgcer_npeSum < 0.13 || P_aero_npeSum < 0.10 || (P_aero_yAtCer < -30 || P_aero_yAtCer > 31)) continue;  
    h2_npeSum_OUT_TCutG3->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }

  /* TCanvas *c;
  c = new TCanvas("c", "NPE Information", 500, 500);
  h2_npeSum_OUT_TCutG3->Draw("COLZ 9");  // 9 is used for high resolution plot
  h2_npeSum_OUT_TCutG3->SetStats(0);
  c->Print(foutpdf);
  */
  //Fill all entries      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.13 || P_aero_npeSum < 0.10 || P_aero_yAtCer < -30 || P_aero_yAtCer > 31) continue;
    h2_npeSum->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }

  //##############################################################################
  //Efficiency scanning process

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    h2_Eff_Pos1->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    h2_Eff_Pos2->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  h2_Eff_Pos3 = (TH2D*)h2_Eff_Pos2->Clone("h2_Eff_Pos3");
  h2_Eff_Pos3->Divide(h2_Eff_Pos1);
 
 // From delta variable

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    h1_Eff_Del1->Fill(P_gtr_dp);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    h1_Eff_Del2->Fill(P_gtr_dp);
  }

  // Take Efficiency scanning 
  h1_Eff_Del3 = (TH1D*)h1_Eff_Del2->Clone();
  h1_Eff_Del3->Sumw2();
  h1_Eff_Del3->Divide(h1_Eff_Del1);
  h1_Eff_Del3->GetYaxis()->SetRangeUser(0.6,1.4);

  // From xAtCer 
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    h1_Eff1_xAtCer->Fill(P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    h1_Eff2_xAtCer->Fill(P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  h1_Eff3_xAtCer = (TH1D*)h1_Eff2_xAtCer->Clone();
  h1_Eff3_xAtCer->Sumw2();
  h1_Eff3_xAtCer->Divide(h1_Eff1_xAtCer);

 //##############################################################################

  // Histograms for efficieny in each region
  
  // Inside 1st region
  //From Delta 1-D
  TH1D *Eff1_Del_IN_TCutG1    = new TH1D("Eff1_Del_IN_TCutG1","Efficieny vs Delta (inside 1st region);  Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *Eff2_Del_IN_TCutG1    = new TH1D("Eff2_Del_IN_TCutG1","Efficiency vs Delta (inside 1st region); Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *Eff3_Del_IN_TCutG1    = new TH1D("Eff3_Del_IN_TCutG1","Efficiency vs Delta (inside 1st region); Delta (%); Efficiency;", 60, -10, 20.0); 
  //From postion 1-D
  TH1D *Eff1_xAtCer_IN_TCutG1    = new TH1D("Eff1_xAtCer_IN_TCutG1","Efficieny vs  xAtCer (inside 1st region);  xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *Eff2_xAtCer_IN_TCutG1    = new TH1D("Eff2_xAtCer_IN_TCutG1","Efficiency vs xAtCer (inside 1st region);  xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *Eff3_xAtCer_IN_TCutG1    = new TH1D("Eff3_xAtCer_IN_TCutG1","Efficiency vs xAtCer (inside 1st region);  xAtCer; Efficiency;", 80, -40, 40.0); 
  //From positions 2-D
  TH2D *Eff1_Pos_IN_TCutG1      = new TH2D("Eff1_Pos_IN_TCutG1","Efficiency vs Position (inside 1st region); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *Eff2_Pos_IN_TCutG1      = new TH2D("Eff2_Pos_IN_TCutG1","Efficiency vs Position (inside 1st region); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *Eff3_Pos_IN_TCutG1      = new TH2D("Eff3_Pos_IN_TCutG1","Efficiency vs Position (inside 1st region); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum <0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_Del_IN_TCutG1->Fill(P_gtr_dp);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum <1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_Del_IN_TCutG1->Fill(P_gtr_dp);
  }

  // Take Efficiency scanning 
  Eff3_Del_IN_TCutG1 = (TH1D*)Eff2_Del_IN_TCutG1->Clone();
  Eff3_Del_IN_TCutG1->Sumw2();
  Eff3_Del_IN_TCutG1->Divide(Eff1_Del_IN_TCutG1);
  Eff3_Del_IN_TCutG1->GetYaxis()->SetRangeUser(0.6,1.4);

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum <0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_xAtCer_IN_TCutG1->Fill(P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum <1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_xAtCer_IN_TCutG1->Fill(P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  Eff3_xAtCer_IN_TCutG1 = (TH1D*)Eff2_xAtCer_IN_TCutG1->Clone();
  Eff3_xAtCer_IN_TCutG1->Sumw2();
  Eff3_xAtCer_IN_TCutG1->Divide(Eff1_xAtCer_IN_TCutG1);
  Eff3_xAtCer_IN_TCutG1->GetYaxis()->SetRangeUser(0.6,1.4);

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum <0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_Pos_IN_TCutG1->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum <1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_Pos_IN_TCutG1->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  Eff3_Pos_IN_TCutG1 = (TH2D*)Eff2_Pos_IN_TCutG1->Clone("Eff3_Pos_IN_TCutG1");
  Eff3_Pos_IN_TCutG1->Sumw2();
  Eff3_Pos_IN_TCutG1->Divide(Eff1_Pos_IN_TCutG1);

  
  // Inside 1st & 2nd regions
  //From Delta 1 -D
  TH1D *Eff1_Del_IN_TCutG12      = new TH1D("Eff1_Del_IN_TCutG12","Efficieny vs Delta (b/w 1st & 2nd regions);  Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *Eff2_Del_IN_TCutG12      = new TH1D("Eff2_Del_IN_TCutG12","Efficiency vs Delta (b/w 1st & 2nd regions); Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *Eff3_Del_IN_TCutG12      = new TH1D("Eff3_Del_IN_TCutG12","Efficiency vs Delta (b/w 1st & 2nd regions); Delta (%); Efficiency;", 60, -10, 20.0); 
  //From position 1 -D
  TH1D *Eff1_xAtCer_IN_TCutG12   = new TH1D("Eff1_xAtCer_IN_TCutG12","Efficieny vs  xAtCer (b/w 1st & 2nd regions);  xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *Eff2_xAtCer_IN_TCutG12   = new TH1D("Eff2_xAtCer_IN_TCutG12","Efficiency vs xAtCer (b/w 1st & 2nd regions);  xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *Eff3_xAtCer_IN_TCutG12   = new TH1D("Eff3_xAtCer_IN_TCutG12","Efficiency vs xAtCer (b/w 1st & 2nd regions);  xAtCer; Efficiency;", 80, -40, 40.0); 
  //From positions 2 -D
  TH2D *Eff1_Pos_IN_TCutG12      = new TH2D("Eff1_Pos_IN_TCutG12","Efficiency vs Position (b/w 1st & 2nd regions); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *Eff2_Pos_IN_TCutG12      = new TH2D("Eff2_Pos_IN_TCutG12","Efficiency vs Position (b/w 1st & 2nd regions); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *Eff3_Pos_IN_TCutG12      = new TH2D("Eff3_Pos_IN_TCutG12","Efficiency vs Position (b/w 1st & 2nd regions); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 


  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_Del_IN_TCutG12->Fill(P_gtr_dp);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_Del_IN_TCutG12->Fill(P_gtr_dp);
  }

  // Take Efficiency scanning 
  Eff3_Del_IN_TCutG12 = (TH1D*)Eff2_Del_IN_TCutG12->Clone();
  Eff3_Del_IN_TCutG12->Sumw2();
  Eff3_Del_IN_TCutG12->Divide(Eff1_Del_IN_TCutG12);
  Eff3_Del_IN_TCutG12->GetYaxis()->SetRangeUser(0.6,1.4);

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_xAtCer_IN_TCutG12->Fill(P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_xAtCer_IN_TCutG12->Fill(P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  Eff3_xAtCer_IN_TCutG12 = (TH1D*)Eff2_xAtCer_IN_TCutG12->Clone();
  Eff3_xAtCer_IN_TCutG12->Sumw2();
  Eff3_xAtCer_IN_TCutG12->Divide(Eff1_xAtCer_IN_TCutG12);
  Eff3_xAtCer_IN_TCutG12->GetYaxis()->SetRangeUser(0.6,1.4);
  
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_Pos_IN_TCutG12->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_Pos_IN_TCutG12->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  Eff3_Pos_IN_TCutG12 = (TH2D*)Eff2_Pos_IN_TCutG12->Clone("Eff3_Pos_IN_TCutG12");
  Eff3_Pos_IN_TCutG12->Sumw2();
  Eff3_Pos_IN_TCutG12->Divide(Eff1_Pos_IN_TCutG12);

  // Inside 2nd & 3rd  regions
  //From Delat 1- D
  TH1D *Eff1_Del_IN_TCutG23    = new TH1D("Eff1_Del_IN_TCutG23","Efficieny vs Delta  (b/w 2nd & 3rd regions); Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *Eff2_Del_IN_TCutG23    = new TH1D("Eff2_Del_IN_TCutG23","Efficiency vs Delta (b/w 2nd & 3rd regions); Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *Eff3_Del_IN_TCutG23    = new TH1D("Eff3_Del_IN_TCutG23","Efficiency vs Delta (b/w 2nd & 3rd regions); Delta (%); Efficiency;", 60, -10, 20.0); 
  //From postion 1- D
  TH1D *Eff1_xAtCer_IN_TCutG23    = new TH1D("Eff1_xAtCer_IN_TCutG23","Efficieny vs  xAtCer (b/w 2nd & 3rd regions);  xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *Eff2_xAtCer_IN_TCutG23    = new TH1D("Eff2_xAtCer_IN_TCutG23","Efficiency vs xAtCer (b/w 2nd & 3rd regions);  xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *Eff3_xAtCer_IN_TCutG23    = new TH1D("Eff3_xAtCer_IN_TCutG23","Efficiency vs xAtCer (b/w 2nd & 3rd regions);  xAtCer; Efficiency;", 80, -40, 40.0); 
  //From positions 2 -D
  TH2D *Eff1_Pos_IN_TCutG23      = new TH2D("Eff1_Pos_IN_TCutG23","Efficiency vs Position (b/w 2nd & 3rd regions); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *Eff2_Pos_IN_TCutG23      = new TH2D("Eff2_Pos_IN_TCutG23","Efficiency vs Position (b/w 2nd & 3rd regions); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *Eff3_Pos_IN_TCutG23      = new TH2D("Eff3_Pos_IN_TCutG23","Efficiency vs Position (b/w 2nd & 3rd regions); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_Del_IN_TCutG23->Fill(P_gtr_dp);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_Del_IN_TCutG23->Fill(P_gtr_dp);
  }

  // Take Efficiency scanning 
  Eff3_Del_IN_TCutG23 = (TH1D*)Eff2_Del_IN_TCutG23->Clone();
  Eff3_Del_IN_TCutG23->Sumw2();
  Eff3_Del_IN_TCutG23->Divide(Eff1_Del_IN_TCutG23);
  Eff3_Del_IN_TCutG23->GetYaxis()->SetRangeUser(0.6,1.4);

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_xAtCer_IN_TCutG23->Fill(P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_xAtCer_IN_TCutG23->Fill(P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  Eff3_xAtCer_IN_TCutG23 = (TH1D*)Eff2_xAtCer_IN_TCutG23->Clone();
  Eff3_xAtCer_IN_TCutG23->Sumw2();
  Eff3_xAtCer_IN_TCutG23->Divide(Eff1_xAtCer_IN_TCutG23);
  Eff3_xAtCer_IN_TCutG23->GetYaxis()->SetRangeUser(0.6,1.4);
 
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_Pos_IN_TCutG23->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_Pos_IN_TCutG23->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  Eff3_Pos_IN_TCutG23 = (TH2D*)Eff2_Pos_IN_TCutG23->Clone("Eff3_Pos_IN_TCutG23");
  Eff3_Pos_IN_TCutG23->Sumw2(); 
  Eff3_Pos_IN_TCutG23->Divide(Eff1_Pos_IN_TCutG23);


  // Outside 3rd region
  //From Delta 1 -D
  TH1D *Eff1_Del_OUT_TCutG3    = new TH1D("Eff1_Del_OUT_TCutG3","Efficieny vs Delta  (outside 3rd region); Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *Eff2_Del_OUT_TCutG3    = new TH1D("Eff2_Del_OUT_TCutG3","Efficiency vs Delta (outside 3rd region); Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *Eff3_Del_OUT_TCutG3    = new TH1D("Eff3_Del_OUT_TCutG3","Efficiency vs Delta (outside 3rd region); Delta (%); Efficiency;", 60, -10, 20.0); 
  //From position 1 -D
  TH1D *Eff1_xAtCer_OUT_TCutG3    = new TH1D("Eff1_xAtCer_OUT_TCutG3","Efficieny vs  xAtCer (outside 3rd region);  xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *Eff2_xAtCer_OUT_TCutG3    = new TH1D("Eff2_xAtCer_OUT_TCutG3","Efficiency vs xAtCer (outside 3rd region);  xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *Eff3_xAtCer_OUT_TCutG3    = new TH1D("Eff3_xAtCer_OUT_TCutG3","Efficiency vs xAtCer (outside 3rd region);  xAtCer; Efficiency;", 80, -40, 40.0); 
  //From positions 2 -D
  TH2D *Eff1_Pos_OUT_TCutG3      = new TH2D("Eff1_Pos_OUT_TCutG3","Efficiency vs Position (outside 3rd region); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *Eff2_Pos_OUT_TCutG3      = new TH2D("Eff2_Pos_OUT_TCutG3","Efficiency vs Position (outside 3rd region); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *Eff3_Pos_OUT_TCutG3      = new TH2D("Eff3_Pos_OUT_TCutG3","Efficiency vs Position (outside 3rd region); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_Del_OUT_TCutG3->Fill(P_gtr_dp);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_Del_OUT_TCutG3->Fill(P_gtr_dp);
  }

  // Take Efficiency scanning 
  Eff3_Del_OUT_TCutG3 = (TH1D*)Eff2_Del_OUT_TCutG3->Clone("Eff3_Del_OUT_TCutG3");
  Eff3_Del_OUT_TCutG3->Sumw2();
  Eff3_Del_OUT_TCutG3->Divide(Eff1_Del_OUT_TCutG3);
  Eff3_Del_OUT_TCutG3->GetYaxis()->SetRangeUser(0.6,1.4);

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_xAtCer_OUT_TCutG3->Fill(P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_xAtCer_OUT_TCutG3->Fill(P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  Eff3_xAtCer_OUT_TCutG3 = (TH1D*)Eff2_xAtCer_OUT_TCutG3->Clone("Eff3_xAtCer_OUT_TCutG3");
  Eff3_xAtCer_OUT_TCutG3->Sumw2();
  Eff3_xAtCer_OUT_TCutG3->Divide(Eff1_xAtCer_OUT_TCutG3);
  Eff3_xAtCer_OUT_TCutG3->GetYaxis()->SetRangeUser(0.6,1.4);

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff1_Pos_OUT_TCutG3->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Eff2_Pos_OUT_TCutG3->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  Eff3_Pos_OUT_TCutG3 = (TH2D*)Eff2_Pos_OUT_TCutG3->Clone("Eff3_Pos_OUT_TCutG3");
  Eff3_Pos_OUT_TCutG3->Sumw2();
  Eff3_Pos_OUT_TCutG3->Divide(Eff1_Pos_OUT_TCutG3);

  // Now sum of all four histograms in each case
  //For Delta
  TH1D *h1   = new TH1D("h1","Efficiency vs Delta (after adding all four hist); Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *h2   = new TH1D("h2","Efficiency vs Delta (after adding all four hist); Delta (%); Efficiency;", 60, -10, 20.0); 
  TH1D *Eff3_Del_All_TCutG  = new TH1D("Eff3_Del_All_TCutG","Efficiency vs Delta (after adding four regions); Delta (%); Efficiency;", 60, -10, 20.0); 
  //For position 1 -D
  TH1D *h4   = new TH1D("h4","Efficiency vs xAtCer (after adding all four hist); xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *h5   = new TH1D("h5","Efficiency vs xAtCer (after adding all four hist); xAtCer; Efficiency;", 80, -40, 40.0); 
  TH1D *Eff3_xAtCer_All_TCutG  = new TH1D("Eff3_xAtCer_All_TCutG","Efficiency vs xAtCer (after adding four regions); xAtCer; Efficiency;", 80, -40, 40.0); 
  //For positions 2 -D
  TH2D * h6  = new TH2D("h6","Efficiency (after adding all four hist); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D * h3  = new TH2D("h3","Efficiency (after adding all four hist); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D * h7  = new TH2D("h7","Efficiency (after adding all four hist); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D * h8  = new TH2D("h8","Efficiency (after adding all four hist); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D * h9  = new TH2D("h9","Efficiency (after adding all four hist); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D * h10  = new TH2D("h10","Efficiency (after adding all four hist); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 
  TH2D *Eff3_Pos_All_TCutG  = new TH2D("Eff3_Pos_All_TCutG","Efficiency (after adding all four hist); Y Position (cm); X Position (cm);", 60, -30, 30.0, 80, -40, 40.0 ); 

  // For effi vs Delta 
  (*h1) = (*Eff1_Del_IN_TCutG1) + (*Eff1_Del_IN_TCutG12) + (*Eff1_Del_IN_TCutG23) + (*Eff1_Del_OUT_TCutG3); 
  (*h2) = (*Eff2_Del_IN_TCutG1) + (*Eff2_Del_IN_TCutG12) + (*Eff2_Del_IN_TCutG23) + (*Eff2_Del_OUT_TCutG3); 

  Eff3_Del_All_TCutG = (TH1D*)h2->Clone("Eff3_Del_All_TCutG");
  Eff3_Del_All_TCutG->Sumw2();
  Eff3_Del_All_TCutG->Divide(h1);
  Eff3_Del_All_TCutG->GetYaxis()->SetRangeUser(0.6,1.4);
  Eff3_Del_All_TCutG->SetTitle("Efficiency vs Delta (after adding four regions)");
  // For effi vs xAtCer
  (*h4) = (*Eff1_xAtCer_IN_TCutG1) + (*Eff1_xAtCer_IN_TCutG12) + (*Eff1_xAtCer_IN_TCutG23) + (*Eff1_xAtCer_OUT_TCutG3); 
  (*h5) = (*Eff2_xAtCer_IN_TCutG1) + (*Eff2_xAtCer_IN_TCutG12) + (*Eff2_xAtCer_IN_TCutG23) + (*Eff2_xAtCer_OUT_TCutG3); 

  Eff3_xAtCer_All_TCutG = (TH1D*)h5->Clone("Eff3_xAtCer_All_TCutG");
  Eff3_xAtCer_All_TCutG->Sumw2();
  Eff3_xAtCer_All_TCutG->Divide(h4);
  Eff3_xAtCer_All_TCutG->GetYaxis()->SetRangeUser(0.6,1.4);
  Eff3_xAtCer_All_TCutG->SetTitle("Efficiency vs xAtCer (after adding four regions)");
  //For eff positions 2 -D
  (*h6) =  (*Eff1_Pos_IN_TCutG1) + (*Eff1_Pos_IN_TCutG12);  (*h3) =  (*Eff1_Pos_IN_TCutG23) + (*Eff1_Pos_OUT_TCutG3); (*h9) = (*h6) + (*h3);
  (*h7) = (*Eff2_Pos_IN_TCutG1) + (*Eff2_Pos_IN_TCutG12);   (*h8) =  (*Eff2_Pos_IN_TCutG23) + (*Eff2_Pos_OUT_TCutG3); (*h10) = (*h7) + (*h8);

  Eff3_Pos_All_TCutG = (TH2D*)h10->Clone("Eff3_Pos_All_TCutG");
  Eff3_Pos_All_TCutG->Sumw2();
  Eff3_Pos_All_TCutG->Divide(h9);
  Eff3_Pos_All_TCutG->SetTitle("Efficiency vs Positions(after adding four regions)");


 //############################################################################
  // Missing mass calculations in each region
  // For Pion
  TH1D *Pi_mm_IN_TCutG1     = new TH1D("Pi_mm_IN_TCutG1","Pion Missing Mass Inside 1st Region; Missing Mass (Pion); Events;", 300, 0.5, 2.0 ); 
  TH1D *Pi_mm_IN_TCutG12    = new TH1D("Pi_mm_IN_TCutG12","Pion Missing Mass b/w 1st & 2nd Regions; Missing Mass (Pion); Events;", 300, 0.5, 2.0 );
  TH1D *Pi_mm_IN_TCutG23    = new TH1D("Pi_mm_OUT_TCutG23","Pion Missing Mass b/w 2nd & 3rd Regions; Missing Mass (Pion); Events;", 300, 0.5, 2.0);   // old ramge 0.5 to 2.0
  TH1D *Pi_mm_OUT_TCutG3    = new TH1D("Pi_mm_OUT_TCutG3","Pion Missing Mass outside 3rd Region; Missing Mass (Pion); Events;", 300, 0.5, 2.0);  // old value 0.5 to 2.0
  TH1D *Pi_mm_random_OUT_TCutG3    = new TH1D("Pi_mm_random_OUT_TCutG3","Pion Missing Mass outside 3rd Region (Random); Missing Mass (Pion); Events;", 300, 0.5, 2.0);
  TH1D *Pi_mm_norandom_OUT_TCutG3    = new TH1D("Pi_mm_norandom_OUT_TCutG3","Pion Missing Mass outside 3rd Region (No Random); Missing Mass (Pion); Events;", 300, 0.5, 2.0);

  TH1D *h1_CTime_ePion_OUT_TCutG3        = new TH1D("h1_CTime_ePion_OUT_TCutG3","Electron-Pion Coin Time; CTime_ePiCoinTime_ROC1; Events;", 300, 0.0, 100.0 ); 
  TH1D *h1_RF_tdc_Time_OUT_TCutG3        = new TH1D("h1_RF_tdc_Time_OUT_TCutG3","RFtime = (P_RF_tdcTime-P_hod_fpHitsTime+RF_Offset)%(BunchSpacing); RFtime (ns); Events;", 300, -2, 6); 
  TH2D *coin_Pi_mm_OUT_TCutG3            = new TH2D("coin_Pi_mm_OUT_TCutG3","Pion mm vs Coin time (outside 3rd region); Pion mm; CTime_ePiCoinTime_ROC1", 300, 0.5, 2.0, 300, 0.0, 100); 
  TH2D *RF_Pi_mm_OUT_TCutG3              = new TH2D("RF_Pi_mm_OUT_TCutG3","Pion mm (outside 3rd region) vs FRtime; Pion mm; RFtime (ns)", 300, 0.0, 2.0, 300, 0.0, 4.0); 
  TH2D *coin_Pi_beta_OUT_TCutG3          = new TH2D("coin_Pi_beta_OUT_TCutG3","Coin time vs Beta (outside 3rd region); CTime_ePiCoinTime_ROC1; P_gtr_beta", 300, 0.0, 100.0,  300, 0.6, 1.4); 

  // Pion misssing mass inside 1st region
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum <1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Pi_mm_IN_TCutG1->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)));
  }

  // Pion misssing mass b/w 1st & 2nd regions     
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Pi_mm_IN_TCutG12->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)));
  }

  // Pion misssing mass b/w 2nd & 3rd regions
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    Pi_mm_IN_TCutG23->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)));
  }

  // Pion misssing mass outside 3rd region  
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer) || P_hgcer_npeSum < 3.0 || P_aero_npeSum  < 1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    if(P_CTime_ePion > 42 && P_CTime_ePion < 46) // select promt peak
      {
	Pi_mm_OUT_TCutG3->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)));
	RF_Pi_mm_OUT_TCutG3->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)), P_RF_time);
	h1_RF_tdc_Time_OUT_TCutG3->Fill(P_RF_time);     	
      }
    
    if((P_CTime_ePion > 30 && P_CTime_ePion < 38) || (P_CTime_ePion > 50 && P_CTime_ePion < 66))  // select random bunches
      {
	Pi_mm_random_OUT_TCutG3->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)));
      }
    h1_CTime_ePion_OUT_TCutG3->Fill(P_CTime_ePion);
    coin_Pi_mm_OUT_TCutG3->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((MPi*MPi) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)), P_CTime_ePion);
    coin_Pi_beta_OUT_TCutG3->Fill(P_CTime_ePion, P_gtr_beta); 
    // h1_RF_tdc_Time_OUT_TCutG3->Fill(P_RF_time);     	
 
   
  }  
  
  Double_t pi_scale;
  pi_scale = 1.0/6.0;  // No of background peaks selected to remove the random background
  Pi_mm_random_OUT_TCutG3->Scale(pi_scale); 
  Pi_mm_norandom_OUT_TCutG3 = (TH1D*)Pi_mm_OUT_TCutG3->Clone("Pi_mm_norandom_OUT_TCutG3");
  Pi_mm_norandom_OUT_TCutG3->Add(Pi_mm_random_OUT_TCutG3, -1); // Substraction of random background from prompt peak

  /*  TAxis *MMAxis = Pi_mm_norandom_OUT_TCutG3->GetXaxis();
  Int_t BinLow = MMAxis->FindBin(1.1);
  Int_t BinHigh = MMAxis->FindBin(1.15);
  Double_t BinIntegral = Pi_mm_norandom_OUT_TCutG3->Integral(BinLow, BinHigh);
  TH1F* Pi_mm_norandom_OUT_TCutG3_Colour = (TH1F*)Pi_mm_norandom_OUT_TCutG3->Clone();
  Pi_mm_norandom_OUT_TCutG3_Colour->SetFillColor(2); Pi_mm_norandom_OUT_TCutG3_Colour->SetFillStyle(3014); Pi_mm_norandom_OUT_TCutG3_Colour->GetXaxis()->SetRange(BinLow, BinHigh);
  TCanvas *c1;
  c1 = new TCanvas("c1", "Pion missing mass", 700, 500);
  Pi_mm_norandom_OUT_TCutG3->Draw();
  Pi_mm_norandom_OUT_TCutG3_Colour->Draw("HIST SAME C");  // 9 is used for high resolution plot
  c1->Print(foutpdf);
    
  TCanvas *c1;
  c1 = new TCanvas("c1", "Pion missing mass", 700, 500);
  Pi_mm_norandom_OUT_TCutG3->Draw("HIST SAME C 9");  // 9 is used for high resolution plot
  Pi_mm_norandom_OUT_TCutG3->SetStats(0);
  Pi_mm_norandom_OUT_TCutG3->SetFillColor(kRed);
  // c1->SaveAs("pi_mm.png");  // This will save in python output directory 
  c1->Print(foutpdf);
  */
  /* TCanvas *c2;
  c2 = new TCanvas("c2", "Coin time", 700, 500);
  h1_CTime_ePion_OUT_TCutG3->Draw("COLZ 9");  // 9 is used for high resolution plot
  h1_CTime_ePion_OUT_TCutG3->SetStats(0);
  h1_CTime_ePion_OUT_TCutG3->SetFillColor(kRed);
  c2->SaveAs("coin.png"); // This will save in python output directory 
  c2->Print(foutpdf + ')');
  */

  // For Kaon
  TH1D *K_mm_IN_TCutG1        = new TH1D("K_mm_IN_TCutG1","Kaon Missing Mass Inside 1st Region; Missing Mass (Kaon); Events;", 300, 0.5, 2.0 );
  TH1D *K_mm_IN_TCutG12       = new TH1D("K_mm_IN_TCutG12","Kaon Missing Mass b/w 1st & 2nd Regions; Missing Mass (Kaon); Events;", 300, 0.5, 2.0 );
  TH1D *K_mm_IN_TCutG23       = new TH1D("K_mm_IN_TCutG23","Kaon Missing Mass b/w 2nd & 3rd Regions; Missing Mass (Kaon); Events;", 300, 0.5, 2.0 );
  TH1D *K_mm_OUT_TCutG3       = new TH1D("K_mm_OUT_TCutG3","Kaon Missing Mass outside 3rd Region; Missing Mass (Kaon); Events;", 300, 0.5, 2.0);  // old 0.5 to 2.0
  TH1D *K_mm_random_OUT_TCutG3       = new TH1D("K_mm_random_OUT_TCutG3","Kaon Missing Mass outside 3rd Region (Random); Missing Mass (Kaon); Events;", 300, 0.5, 2.0);
  TH1D *K_mm_norandom_OUT_TCutG3       = new TH1D("K_mm_norandom_OUT_TCutG3","Kaon Missing Mass outside 3rd Region (No Random); Missing Mass (Kaon); Events;", 300, 0.5, 2.0);

  TH1D *h1_CTime_eKaon_OUT_TCutG3        = new TH1D("h1_CTime_eKaon_OUT_TCutG3","Electron-Kaon Coin Time; CTime_eKCoinTime_ROC1; Events;", 300, 0.0, 100.0 );
  TH1D *h1_RF_tdc_TimeK_OUT_TCutG3       = new TH1D("h1_RF_tdc_TimeK_OUT_TCutG3","RFtime = (P_RF_tdcTime-P_hod_fpHitsTime+RF_Offset)%(BunchSpacing); RFtime (ns); Events;", 100, -2, 6);
  TH2D *coin_K_mm_OUT_TCutG3             = new TH2D("coin_K_mm_OUT_TCutG3","Kaon mm vs Coin time (outside 3rd region); Kaon mm; CTime_eKCoinTime_ROC1", 300, 0.5, 2.0, 300, 0.0, 100.0); 
  TH2D *RF_K_mm_OUT_TCutG3               = new TH2D("RF_K_mm_OUT_TCutG3","Kaon mm (outside 3rd region) vs FRtime; Kaon mm; RFtime (ns)", 300, 0.0, 2.0, 300, 0.0, 4.0); 
  TH2D *coin_K_beta_OUT_TCutG3           = new TH2D("coin_K_beta_OUT_TCutG3","Coin time vs Beta (outside 3rd region); CTime_eKCoinTime_ROC1; P_gtr_beta", 300, 0.0, 100.0,  300, 0.6, 1.4); 

  // Kaon missing mass inside 1st region  
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum > 1.0 || P_aero_npeSum < 1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    K_mm_IN_TCutG1->Fill(sqrt(abs(e_miss*e_miss - p_miss*p_miss)));
  }
  //Kaon missing mass b/w 1st & 2nd regions
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))|| (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;
    if(P_hgcer_npeSum > 1.0 || P_aero_npeSum < 1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    K_mm_IN_TCutG12->Fill(sqrt(abs(e_miss*e_miss - p_miss*p_miss)));
  }

  //Kaon missing mass b/w 2nd & 3rd regions
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))|| (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;
    if(P_hgcer_npeSum > 1.0 || P_aero_npeSum < 1.0 || P_aero_yAtCer >31) continue;
    K_mm_IN_TCutG23->Fill(sqrt(abs(e_miss*e_miss - p_miss*p_miss)));

  }
  //Kaon missing mass outside 3rd region
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if(P_hgcer_npeSum > 1.5 || P_aero_npeSum < 3.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    if(P_CTime_ePion > 42.0 && P_CTime_ePion < 46.0)  // select promt peak 
      { 
       K_mm_OUT_TCutG3->Fill(sqrt(abs(e_miss*e_miss - p_miss*p_miss)));
       h1_RF_tdc_TimeK_OUT_TCutG3->Fill(P_RF_time); 
       //  TCutG *Kaon_cutg = new TCutG("Kaon_cutg",5);
       Kaon_cutg->SetVarX("sqrt(abs(e_miss*e_miss - p_miss*p_miss))");
       Kaon_cutg->SetVarY("P_RF_time");  Kaon_cutg->SetPoint(0,0.77,1.50);  Kaon_cutg->SetPoint(1,1.019,1.50);  Kaon_cutg->SetPoint(2,1.019,3.033);  Kaon_cutg->SetPoint(3,0.77,3.033); Kaon_cutg->SetPoint(4,0.77,1.50); Kaon_cutg->SetLineColor(kRed);  Kaon_cutg->SetLineWidth(3);
       RF_K_mm_OUT_TCutG3->Fill(sqrt(abs(e_miss*e_miss - p_miss*p_miss)), P_RF_time);         
       
       if (!Kaon_cutg->IsInside(sqrt(abs(e_miss*e_miss - p_miss*p_miss)), P_RF_time))   // select Kaon
	 {
	   K_mm_OUT_TCutG3->Fill(sqrt(abs(e_miss*e_miss - p_miss*p_miss)));
	 }  
       // RF_K_mm_OUT_TCutG3->Fill(K_mm, P_RF_time);         
      }
    
    if((P_CTime_eKaon > 30 && P_CTime_eKaon < 38) || (P_CTime_eKaon > 50 && P_CTime_eKaon < 66) || (P_RF_time > 0.0 && P_RF_time < 0.2))  //select random bunches
      {
	K_mm_random_OUT_TCutG3->Fill(sqrt(abs(e_miss*e_miss - p_miss*p_miss)));	
      }
    h1_CTime_eKaon_OUT_TCutG3->Fill(P_CTime_eKaon);
    coin_K_mm_OUT_TCutG3->Fill(sqrt(abs(e_miss*e_miss - p_miss*p_miss)), P_CTime_eKaon);
    coin_K_beta_OUT_TCutG3->Fill(P_CTime_eKaon, P_gtr_beta);
    // h1_RF_tdc_TimeK_OUT_TCutG3->Fill(P_RF_time);             
    
  }
  Double_t K_scale;
  K_scale = 1.0/6.0;
  K_mm_random_OUT_TCutG3->Scale(K_scale);
  K_mm_norandom_OUT_TCutG3 = (TH1D*)K_mm_OUT_TCutG3->Clone("K_mm_norandom_OUT_TCutG3");
  K_mm_norandom_OUT_TCutG3->Add(K_mm_random_OUT_TCutG3, -1);

  /*  TAxis *MMAxis = K_mm_norandom_OUT_TCutG3->GetXaxis();
  Int_t BinLowK   = MMAxis->FindBin(1.1);    // select Kaon peak
  Int_t BinHighK  = MMAxis->FindBin(1.15);
  Int_t BinLowPi  = MMAxis->FindBin(0.91);   // select pion peak
  Int_t BinHighPi = MMAxis->FindBin(0.95);
  Double_t BinIntegralK = K_mm_norandom_OUT_TCutG3->Integral(BinLowK, BinHighK);
  Double_t BinIntegralPi = K_mm_norandom_OUT_TCutG3->Integral(BinLowPi, BinHighPi);
  TH1F* K_mm_norandom_OUT_TCutG3_ColourK = (TH1F*)K_mm_norandom_OUT_TCutG3->Clone();
  K_mm_norandom_OUT_TCutG3_ColourK->SetFillColor(2); K_mm_norandom_OUT_TCutG3_ColourK->SetFillStyle(3014); K_mm_norandom_OUT_TCutG3_ColourK->GetXaxis()->SetRange(BinLowK, BinHighK);
  TH1F* K_mm_norandom_OUT_TCutG3_ColourPi = (TH1F*)K_mm_norandom_OUT_TCutG3->Clone();
  K_mm_norandom_OUT_TCutG3_ColourPi->SetFillColor(2); K_mm_norandom_OUT_TCutG3_ColourPi->SetFillStyle(3014); K_mm_norandom_OUT_TCutG3_ColourPi->GetXaxis()->SetRange(BinLowPi, BinHighPi);
  
  TPaveText *NoKaonEvt = new TPaveText(0.48934,0.615354,0.85,0.71576,"NDC");
  NoKaonEvt->AddText(Form("No of Kaon: %.0f", BinIntegralK)); 
  NoKaonEvt->AddText(Form("No of Pion: %.0f", BinIntegralPi)); 
  TCanvas *c1;
  c1 = new TCanvas("c1", "Kaon missing mass", 700, 500);
  K_mm_norandom_OUT_TCutG3->Draw();
  K_mm_norandom_OUT_TCutG3_ColourPi->Draw("HIST SAME C");
  K_mm_norandom_OUT_TCutG3_ColourK->Draw("HIST SAME C");  // 9 is used for high resolution plot
  NoKaonEvt->Draw("same"); 
  c1->Print(foutpdf);
  */
  /*  TCanvas *c1;
  c1 = new TCanvas("c1", " Kaon missing mass", 700, 500);
  K_mm_norandom_OUT_TCutG3->Draw("HIST SAME C 9");  // 9 is used for high resolution plot
  K_mm_norandom_OUT_TCutG3->SetStats(0);
  K_mm_norandom_OUT_TCutG3->SetFillColor(kRed);
  // c1->SaveAs("pi_mm.png");  // This will save in python output directory 
  c1->Print(foutpdf);
  */ 
 
  // For Proton

  TH1D *P_mm_IN_TCutG1        = new TH1D("P_mm_IN_TCutG1","Proton Missing Mass Inside 1st Region; Missing Mass (Proton); Events;", 300, 0.1, 2.0 ); 
  TH1D *P_mm_IN_TCutG12       = new TH1D("P_mm_IN_TCutG12 ","Proton Missing Mass b/w 1st & 2nd Regions; Missing Mass (Proton); Events;", 300, 0.1, 2.0 ); 
  TH1D *P_mm_IN_TCutG23       = new TH1D("P_mm_IN_TCutG23","Proton Missing Mass b/w 2nd & 3rd Regions; Missing Mass (Proton); Events;", 300, 0.1, 2.0 );
  TH1D *P_mm_OUT_TCutG3       = new TH1D("P_mm_OUT_TCutG3","Proton Missing Mass outside 3rd Region; Missing Mass (Proton); Events;", 300, 0.5, 2.0);  //old range 0.1 to 2.0
  TH1D *P_mm_random_OUT_TCutG3       = new TH1D("P_mm_random_OUT_TCutG3","Proton Missing Mass outside 3rd Region (Random); Missing Mass (Proton); Events;", 300, 0.5, 2.0 );
  TH1D *P_mm_norandom_OUT_TCutG3       = new TH1D("P_mm_norandom_OUT_TCutG3","Proton Missing Mass outside 3rd Region (No Random); Missing Mass (Proton); Events;", 300, 0.5, 2.0 );

  TH1D *h1_CTime_eProton_OUT_TCutG3        = new TH1D("h1_CTime_eProton_OUT_TCutG3","Electron-Proton Coin Time; CTime_epCoinTime_ROC1; Events;", 300, 0.0, 100.0 ); 
  TH1D *h1_RF_tdc_TimeP_OUT_TCutG3         = new TH1D("h1_RF_tdc_TimeP_OUT_TCutG3","RFtime = (P_RF_tdcTime-P_hod_fpHitsTime+RF_Offset)%(BunchSpacing); RFtime (ns); Events;", 300, -2,6); 
  TH2D *coin_P_mm_OUT_TCutG3               = new TH2D("coin_P_mm_OUT_TCutG3","Proton mm vs Coin time (outside 3rd region); Proton mm; CTime_epCoinTime_ROC1", 300, 0.5, 2.0, 300, 0.0, 100.0); 
  TH2D *RF_P_mm_OUT_TCutG3                 = new TH2D("RF_P_mm_OUT_TCutG3","Proton mm (outside 3rd region) vs FRtime; Proton mm; RFtime (ns)", 300, 0.0, 2.0, 300, 0.0, 4.0); 

  TH2D *coin_P_beta_OUT_TCutG3             = new TH2D("coin_P_beta_OUT_TCutG3","Coin time vs Beta (outside 3rd region); CTime_epCoinTime_ROC1; P_gtr_beta", 300, 0.0, 100.0,  300, 0.6, 1.4); 

  // Proton missing mass inside 1st region
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if (P_hgcer_npeSum > 1.5 || P_aero_npeSum > 1.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    P_mm_IN_TCutG1->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((Mp*Mp) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)));
  }
  
  //Proton missing mass b/w 1st & 2nd regions
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if (P_hgcer_npeSum > 1.5 || P_aero_npeSum > 2.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    P_mm_IN_TCutG12->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((Mp*Mp) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)));
  }
  //Proton missing mass b/w 2nd & 3rd regions
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if((!cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) || (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer))) continue;   
    if (P_hgcer_npeSum > 1.5 || P_aero_npeSum > 2.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31) continue;
    P_mm_IN_TCutG23->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((Mp*Mp) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)));
  }

  //Proton missing mass outside 3rd region
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg3->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    if (P_hgcer_npeSum > 1.34 || P_aero_npeSum > 3.0 || P_aero_yAtCer < -30 || P_aero_yAtCer >31 || P_RF_time >1.6) continue;
    if(P_CTime_ePion > 42 && P_CTime_ePion < 46)  //select promt peak 
     { 
       P_mm_OUT_TCutG3->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((Mp*Mp) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)));
       h1_RF_tdc_TimeP_OUT_TCutG3->Fill(P_RF_time);
       RF_P_mm_OUT_TCutG3->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((Mp*Mp) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)), P_RF_time);       
     } 
    
    if((P_CTime_eProton > 30 && P_CTime_eProton < 38) || (P_CTime_eProton > 50 && P_CTime_eProton < 66))  // select random bunches
       {
	 P_mm_random_OUT_TCutG3->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((Mp*Mp) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)));
       }

    h1_CTime_eProton_OUT_TCutG3->Fill(P_CTime_eProton);
    coin_P_mm_OUT_TCutG3->Fill(sqrt(pow((e_miss + (sqrt((MK*MK) + (P_gtr_p*P_gtr_p))) - (sqrt((Mp*Mp) + (P_gtr_p*P_gtr_p)))), 2) - (p_miss*p_miss)), P_CTime_eProton); 
    coin_P_beta_OUT_TCutG3->Fill(P_CTime_eProton, P_gtr_beta);
    //  h1_RF_tdc_TimeP_OUT_TCutG3->Fill(P_RF_time);
  
  }
		       
		       Double_t P_scale;
  P_scale = 1.0/6.0;
  P_mm_random_OUT_TCutG3->Scale(P_scale);
  P_mm_norandom_OUT_TCutG3 = (TH1D*)P_mm_OUT_TCutG3->Clone("P_mm_norandom_OUT_TCutG3");
  P_mm_norandom_OUT_TCutG3->Add(P_mm_random_OUT_TCutG3, -1);
  
  /* TCanvas *c1;
  c1 = new TCanvas("c1", " Proton missing mass", 700, 500);
  P_mm_norandom_OUT_TCutG3->Draw("HIST SAME C 9");  // 9 is used for high resolution plot
  P_mm_norandom_OUT_TCutG3->SetStats(0);
  P_mm_norandom_OUT_TCutG3->SetFillColor(kRed);
  // c1->SaveAs("pi_mm.png");  // This will save in python output directory 
  c1->Print(foutpdf);
  */ 
 
  //Write the info in the root format
		       
  TFile *OutHisto_file = new TFile(foutname,"RECREATE");
  TDirectory *TCutG_Plots = OutHisto_file->mkdir("TCutG_Plots");
  TCutG_Plots->cd();
  h2_XYAtCer1->GetListOfFunctions()->Add(cutg1,"L"); 
  h2_XYAtCer1->Write();
  h2_XYAtCer1->GetListOfFunctions()->Clear("L"); 
  h2_XYAtCer2->GetListOfFunctions()->Add(cutg2,"L"); 
  h2_XYAtCer2->Write();
  h2_XYAtCer2->GetListOfFunctions()->Clear("L"); 
  h3_XYAtCer_npeSum1_pyx->GetListOfFunctions()->Add(cutg1,"L"); 
  h3_XYAtCer_npeSum1_pyx->Write();
  h3_XYAtCer_npeSum2_pyx->GetListOfFunctions()->Add(cutg2,"L"); 
  h3_XYAtCer_npeSum2_pyx->Write();
  h3_XYAtCer_npeSum3_pyx->GetListOfFunctions()->Add(cutg3,"L"); 
  h3_XYAtCer_npeSum3_pyx->Write();  
  h2_npeSum_IN_TCutG1->Write();
  h2_npeSum_IN_TCutG12->Write();
  h2_npeSum_IN_TCutG23->Write();
  h2_npeSum_OUT_TCutG3->Write();
  h2_npeSum->Write();
  h3_aero_XYAtCer_nocut_npeSum_pyx->Write();  
  h3_aero_XYAtCer_npeSum_pyx->Write();
  TDirectory *Pi_mm_tim_Plots = OutHisto_file->mkdir("Pi_mm_tim_Plots");
  Pi_mm_tim_Plots->cd();
  h1_CTime_ePion_OUT_TCutG3->Write();
  h1_RF_tdc_Time_OUT_TCutG3->Write();
  coin_Pi_mm_OUT_TCutG3->Write();
  RF_Pi_mm_OUT_TCutG3->Write();
  coin_Pi_beta_OUT_TCutG3->Write(); 
  Pi_mm_OUT_TCutG3->Write();
  Pi_mm_random_OUT_TCutG3->Write();
  Pi_mm_norandom_OUT_TCutG3->Write();
  Pi_mm_IN_TCutG23->Write();
  Pi_mm_IN_TCutG12->Write();
  Pi_mm_IN_TCutG1->Write();
  TDirectory *K_mm_tim_Plots = OutHisto_file->mkdir("K_mm__tim_Plots");
  K_mm_tim_Plots->cd();
  h1_CTime_eKaon_OUT_TCutG3->Write();
  h1_RF_tdc_TimeK_OUT_TCutG3->Write();
  coin_K_mm_OUT_TCutG3->Write();
  RF_K_mm_OUT_TCutG3->GetListOfFunctions()->Add(Kaon_cutg,"L"); 
  RF_K_mm_OUT_TCutG3->Write();
  RF_K_mm_OUT_TCutG3->GetListOfFunctions()->Clear("L");
  coin_K_beta_OUT_TCutG3->Write();
  K_mm_OUT_TCutG3->Write();
  K_mm_random_OUT_TCutG3->Write(); 
  K_mm_norandom_OUT_TCutG3->Write();
  K_mm_IN_TCutG23->Write(); 
  K_mm_IN_TCutG12->Write(); 
  K_mm_IN_TCutG1->Write(); 
  TDirectory *P_mm_tim_Plots = OutHisto_file->mkdir("P_mm_tim_Plots");
  P_mm_tim_Plots->cd();
  h1_CTime_eProton_OUT_TCutG3->Write();
  h1_RF_tdc_TimeP_OUT_TCutG3->Write();
  coin_P_mm_OUT_TCutG3->Write();
  RF_P_mm_OUT_TCutG3->Write();
  coin_P_beta_OUT_TCutG3->Write();
  P_mm_OUT_TCutG3->Write();
  P_mm_random_OUT_TCutG3->Write();
  P_mm_norandom_OUT_TCutG3->Write();
  P_mm_IN_TCutG23->Write();
  P_mm_IN_TCutG12->Write();
  P_mm_IN_TCutG1->Write();
  TDirectory *Eff_Plots = OutHisto_file->mkdir("Eff_Plots");
  Eff_Plots->cd();
  Eff3_Del_IN_TCutG1->Write(); 
  Eff3_Del_IN_TCutG12->Write(); 
  Eff3_Del_IN_TCutG23->Write(); 
  Eff3_Del_OUT_TCutG3->Write();
  Eff3_Del_All_TCutG->Write();
  Eff3_xAtCer_IN_TCutG1->Write(); 
  Eff3_xAtCer_IN_TCutG12->Write(); 
  Eff3_xAtCer_IN_TCutG23->Write(); 
  Eff3_xAtCer_OUT_TCutG3->Write();
  Eff3_xAtCer_All_TCutG->Write(); 
  Eff3_Pos_IN_TCutG1->Write();
  Eff3_Pos_IN_TCutG12->Write();
  Eff3_Pos_IN_TCutG23->Write();
  Eff3_Pos_OUT_TCutG3->Write();
  Eff3_Pos_All_TCutG->Write();
  h2_Eff_Pos3->Write(); 
  h1_Eff_Del3->Write();
  h1_Eff3_xAtCer->Write();
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
