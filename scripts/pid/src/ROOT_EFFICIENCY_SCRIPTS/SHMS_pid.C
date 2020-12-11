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
  TString foutpdf = Outpath1+"/" + TOutFilename + ".pdf";

  // Particles information with acceptnce cuts ONLY... 
  
  TTree* SHMS_EVENTS  = (TTree*)InFile->Get("SHMS_Events_wCuts"); Long64_t nEntries_SHMS_EVENTS  = (Long64_t)SHMS_EVENTS->GetEntries();

  Double_t P_hgcer_npeSum;SHMS_EVENTS->SetBranchAddress("P_hgcer_npeSum", &P_hgcer_npeSum);
  Double_t P_aero_npeSum; SHMS_EVENTS->SetBranchAddress("P_aero_npeSum", &P_aero_npeSum);
  Double_t P_hgcer_xAtCer; SHMS_EVENTS->SetBranchAddress("P_hgcer_xAtCer", &P_hgcer_xAtCer);
  Double_t P_hgcer_yAtCer; SHMS_EVENTS->SetBranchAddress("P_hgcer_yAtCer", &P_hgcer_yAtCer);
  Double_t P_aero_xAtCer; SHMS_EVENTS->SetBranchAddress("P_aero_xAtCer", &P_aero_xAtCer);
  Double_t P_aero_yAtCer; SHMS_EVENTS->SetBranchAddress("P_aero_yAtCer", &P_aero_yAtCer);
  Double_t P_cal_etotnorm; SHMS_EVENTS->SetBranchAddress("P_cal_etotnorm", &P_cal_etotnorm);
  Double_t P_gtr_p; SHMS_EVENTS->SetBranchAddress("P_gtr_p", &P_gtr_p);
  Double_t P_gtr_dp; SHMS_EVENTS->SetBranchAddress("P_gtr_dp", &P_gtr_dp);
  Double_t e_miss; SHMS_EVENTS->SetBranchAddress("emiss", &e_miss);
  Double_t p_miss; SHMS_EVENTS->SetBranchAddress("pmiss", &p_miss);


  // ######################### First set of Geometrical Cuts #################### 
  TCutG *cutg1 = new TCutG("cutg1",21);
  cutg1->SetVarX("P_hgcer_yAtCer");
  cutg1->SetVarY("P_hgcer_xAtCer");
  cutg1->SetPoint(0,-25,2); cutg1->SetPoint(1,-2,2);  cutg1->SetPoint(2,-1,2.5); cutg1->SetPoint(3,0,3); cutg1->SetPoint(4,1,3); cutg1->SetPoint(5,2,3.3);
  cutg1->SetPoint(6,3,3.0); cutg1->SetPoint(7,4,2.5); cutg1->SetPoint(8,5,2); cutg1->SetPoint(9,25,2); cutg1->SetPoint(10,25,0.5); cutg1->SetPoint(11,5,0.5);
  cutg1->SetPoint(12,4,1); cutg1->SetPoint(13,3,-1); cutg1->SetPoint(14,2,-2); cutg1->SetPoint(15,1,-2.3); cutg1->SetPoint(16,0,-1.5); cutg1->SetPoint(17,-1,-1);
  cutg1->SetPoint(18,-2,0.5); cutg1->SetPoint(19,-25,0.5); cutg1->SetPoint(20,-25,2); cutg1->SetLineColor(kRed); cutg1->SetLineWidth(5);

  // ######################### Second set of Geometrical Cuts #################### 

  TCutG *cutg2 = new TCutG("cutg2",19);
  cutg2->SetVarX("P_hgcer_yAtCer");
  cutg2->SetVarY("P_hgcer_xAtCer");  cutg2->SetPoint(0,-25,2);  cutg2->SetPoint(1,-2,2);  cutg2->SetPoint(2,0,3.5);  cutg2->SetPoint(3,2,5.5);  cutg2->SetPoint(4,4,5);
  cutg2->SetPoint(5,6,4.5);  cutg2->SetPoint(6,8,4);  cutg2->SetPoint(7,10,2);  cutg2->SetPoint(8,25,2);  cutg2->SetPoint(9,25,0.5);  cutg2->SetPoint(10,6,0.5);
  cutg2->SetPoint(11,4,-1);  cutg2->SetPoint(12,2,-3);  cutg2->SetPoint(13,0,-3.5);  cutg2->SetPoint(14,-2,-2);  cutg2->SetPoint(15,-4,-0.75);  cutg2->SetPoint(16,-6,-0.5);
  cutg2->SetPoint(17,-25,0.5);  cutg2->SetPoint(18,-25,2);  cutg2->SetLineColor(kRed);  cutg2->SetLineWidth(5);

  // ######################### Third set of Geometrical Cuts #################### 

  TCutG *cutg3 = new TCutG("cutg3",25);
  cutg3->SetVarX("P_hgcer_yAtCer");
  cutg3->SetVarY("P_hgcer_xAtCer");  cutg3->SetPoint(0,-25,2);  cutg3->SetPoint(1,-8,2);  cutg3->SetPoint(2,-6,2);  cutg3->SetPoint(3,-4,2);  cutg3->SetPoint(4,-2,3);
  cutg3->SetPoint(5,0,4);  cutg3->SetPoint(6,2,9);  cutg3->SetPoint(7,4,7);  cutg3->SetPoint(8,6,5);  cutg3->SetPoint(9,8,5);  cutg3->SetPoint(10,10,2);  cutg3->SetPoint(11,25,2);
  cutg3->SetPoint(12,25,-1);  cutg3->SetPoint(13,10,-1);  cutg3->SetPoint(14,8,-1);  cutg3->SetPoint(15,6,-1);  cutg3->SetPoint(16,4,-1);  cutg3->SetPoint(17,2,-4);  
  cutg3->SetPoint(18,1,-4.70);  cutg3->SetPoint(19,0,-4);  cutg3->SetPoint(20,-2,-1);  cutg3->SetPoint(21,-4,-1);  cutg3->SetPoint(22,-6,-1);   cutg3->SetPoint(23,-25,-1);
  cutg3->SetPoint(24,-25,2);  cutg3->SetLineColor(kRed);  cutg3->SetLineWidth(5);
  
  //##############################################################################

  // Defined histograms for TCutGs
  TH2D *h2_XYAtCer                     = new TH2D("h2_XYAtCer","HGC, P_hgcer_npeSum => 1.5; P_hgcer_yAtCer; P_hgcer_xAtCer;", 300, -40, 40, 300, -40, 40 );
  TH2D *h2_XYAtCer2                    = new TH2D("h2_XYAtCer2","HGC, P_hgcer_npeSum => 5.0; P_hgcer_yAtCer; P_hgcer_xAtCer;", 300, -40, 40, 300, -40, 40 );
  TH3D *h3_aero_XYAtCer_npeSum         = new TH3D("h3_aero_XYAtCer_npeSum","Aero; P_aero_yAtAero; P_aero_xAtAero; P_aero_npeSum", 300, -50, 50, 300, -50, 50, 300, 0, 30);
  TH3D *h3_aero_XYAtCer_nocut_npeSum   = new TH3D("h3_aero_XYAtCer_nocut_npeSum","Aero; P_aero_yAtAero; P_aero_xAtAero; P_aero_npeSum", 300, -50, 50, 300, -50, 50, 300, 0, 30);
  TH3D *h3_XYAtCer_npeSum              = new TH3D("h3_XYAtCer_npeSum","HGC, P_hgcer_npeSum => 1.5; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
  TH3D *h3_XYAtCer_npeSum2             = new TH3D("h3_XYAtCer_npeSum2","HGC, P_hgcer_npeSum => 5.0; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
  TH3D *h3_XYAtCer_npeSum3             = new TH3D("h3_XYAtCer_npeSum3","HGC, P_hgcer_npeSum => 7.0; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
  TH2D *h2_npeSum                      = new TH2D("h2_npeSum","HGC; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 40, 300, 0.0, 30);
  TH2D *h2_npeSum_TCutG1_IN            = new TH2D("h2_npeSum_TCutG1_IN","HGC; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 40, 300, 0.0, 30);
  TH2D *h2_npeSum_TCutG1_OUT           = new TH2D("h2_npeSum_TCutG1_OUT","HGC; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 40, 300, 0.0, 30);
  TH2D *h2_npeSum_TCutG2_IN            = new TH2D("h2_npeSum_TCutG2_IN","HGC; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 40, 300, 0.0, 30);
  TH2D *h2_npeSum_TCutG2_OUT           = new TH2D("h2_npeSum_TCutG2_OUT","HGC; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 40, 300, 0.0, 30);
  TH2D *h2_npeSum_TCutG12_IN           = new TH2D("h2_npeSum_TCutG12_IN","HGC; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 40, 300, 0.0, 30);

  //##############################################################################

  // Defined histograms for scanning efficiecny 
  TH2D *h2_Eff_Pos1    = new TH2D("h2_Eff_Pos1","Efficiency vs Position; Y Position (cm); X Position (cm);", 300, -40, 40.0, 300, -40, 40.0 ); 
  TH2D *h2_Eff_Pos2    = new TH2D("h2_Eff_Pos2","Efficiency vs Position; Y Position (cm); X Position (cm);", 300, -40, 40.0, 300, -40, 40.0 ); 
  TH2D *h2_Eff_Pos3    = new TH2D("h2_Eff_Pos3","Efficiency vs Position; Y Position (cm); X Position (cm);", 300, -40, 40.0, 300, -40, 40.0 ); 

  TH1D *h1_Eff_Del1    = new TH1D("h1_Eff_Del1","Efficieny vs Delta; Delta (%); Efficiency (%);", 300, -10, 20.0); 
  TH1D *h1_Eff_Del2    = new TH1D("h1_Eff_Del2","Efficiency vs Delta; Delta (%); Efficiency (%);", 300, -10, 20.0); 
  TH1D *h1_Eff_Del3    = new TH1D("h1_Eff_Del3","Efficiency vs Delta; Delta (%); Efficiency (%);", 300, -10, 20.0); 

  TH1D *h1_Eff1_xAtCer    = new TH1D("h1_Eff1_xAtCer","xAtCer vs Efficiency; xAtCer; Efficiency (%);", 200, -40, 40.0); 
  TH1D *h1_Eff2_xAtCer    = new TH1D("h1_Eff2_xAtCer","xAtCer vs Efficiency; xAtCer; Efficiency (%);", 200, -40, 40.0); 
  TH1D *h1_Eff3_xAtCer    = new TH1D("h1_Eff3_xAtCer","xAtCer vs Efficiecny; xAtCer; Efficiency (%);", 200, -40, 40.0); 

  //##############################################################################
 
  //Fill xyAtCer entry
      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.5) continue;
    if (P_aero_yAtCer > 31) continue;
    h2_XYAtCer->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 5) continue;
    if (P_aero_yAtCer > 31) continue;
    h2_XYAtCer2->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }
  //Fill entry for 3D

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.5 || P_aero_yAtCer > 31) continue;
    h3_XYAtCer_npeSum->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer,P_hgcer_npeSum);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 5 || P_aero_yAtCer > 31) continue;
    h3_XYAtCer_npeSum2->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer,P_hgcer_npeSum);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 7 || P_aero_yAtCer > 31) continue;
    h3_XYAtCer_npeSum3->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer,P_hgcer_npeSum);
  }

  //Fill entry for Aero

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    h3_aero_XYAtCer_nocut_npeSum->Fill(P_aero_yAtCer, P_aero_xAtCer, P_aero_npeSum);
    if(P_aero_yAtCer>31) continue;
    h3_aero_XYAtCer_npeSum->Fill(P_aero_yAtCer, P_aero_xAtCer, P_aero_npeSum);
  }

  // Project 3D histogram on XY

  TProfile2D *h3_aero_XYAtCer_npeSum_pyx = new TProfile2D("h3_aero_XYAtCer_npeSum_pyx","Aero; P_aero_yAtAero; P_aero_xAtAero ",300,-50,50, 300,-50,50, 0, 30);
  h3_aero_XYAtCer_npeSum->Project3DProfile("yx");

  TProfile2D *h3_aero_XYAtCer_nocut_npeSum_pyx = new TProfile2D("h3_aero_XYAtCer_nocut_npeSum_pyx","Aero; P_aero_yAtAero; P_aero_xAtAero ",300,-50,50, 300,-50,50, 0, 30);
  h3_aero_XYAtCer_nocut_npeSum->Project3DProfile("yx");

  TProfile2D *h3_XYAtCer_npeSum_pyx = new TProfile2D("h3_XYAtCer_npeSum_pyx","HGC,P_hgcer_npeSum => 1.5; P_hgcer_yAtCer; P_hgcer_xAtCer ",300,-40,40, 300,-40,40, 0, 30);
  h3_XYAtCer_npeSum->Project3DProfile("yx");

  TProfile2D *h3_XYAtCer_npeSum2_pyx = new TProfile2D("h3_XYAtCer_npeSum2_pyx","HGC, P_hgcer_npeSum => 5.0; P_hgcer_yAtCer; P_hgcer_xAtCer ",300,-40,40, 300,-40,40, 0, 30);
  h3_XYAtCer_npeSum2->Project3DProfile("yx");
  TProfile2D *h3_XYAtCer_npeSum3_pyx = new TProfile2D("h3_XYAtCer_npeSum3_pyx","HGC, P_hgcer_npeSum => 7.0; P_hgcer_yAtCer; P_hgcer_xAtCer ",300,-40,40, 300,-40,40, 0, 30);
  h3_XYAtCer_npeSum3->Project3DProfile("yx");

  //Fill NPE entry inside the TCutG1      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_yAtCer > 31) continue;
   if (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    h2_npeSum_TCutG1_OUT->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }
  //Fill entry outside the TCutG1

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_yAtCer > 31) continue;
    if (!cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    h2_npeSum_TCutG1_IN->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }

  //Fill NPE entry inside the TCutG2      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_yAtCer > 31) continue;
   if (cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    h2_npeSum_TCutG2_OUT->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }
  //Fill entry outside the TCutG2

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_yAtCer > 31) continue;
    if (!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    h2_npeSum_TCutG2_IN->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }

  //Fill entry between TCutG1 & 2
  
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_yAtCer > 31) continue;
    if(!cutg2->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;   
    if (cutg1->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    h2_npeSum_TCutG12_IN->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }

  //Fill entry without TCutG

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_yAtCer > 31) continue;
    h2_npeSum->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }
 
  //##############################################################################
  //Efficiency scanning process

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer >31) continue;
    h2_Eff_Pos1->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer >31) continue;
    h2_Eff_Pos2->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  h2_Eff_Pos3 = (TH2D*)h2_Eff_Pos2->Clone();
  h2_Eff_Pos3->Divide(h2_Eff_Pos1);
 
 // From delta variable

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer >31) continue;
    h1_Eff_Del1->Fill(P_gtr_dp);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer >31) continue;
    h1_Eff_Del2->Fill(P_gtr_dp);
  }

  // Take Efficiency scanning 
  h1_Eff_Del3 = (TH1D*)h1_Eff_Del2->Clone();
  h1_Eff_Del3->Sumw2();
  h1_Eff_Del3->Divide(h1_Eff_Del1);
  h1_Eff_Del3->GetYaxis()->SetRangeUser(0.0,2.0);

  // From xAtCer 
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 0.1 || P_aero_npeSum <1.0 || P_aero_yAtCer >31) continue;
    h1_Eff1_xAtCer->Fill(P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.0 || P_aero_npeSum <1.0 || P_aero_yAtCer >31) continue;
    h1_Eff2_xAtCer->Fill(P_hgcer_xAtCer);
  }

  // Take Efficiency scanning 
  h1_Eff3_xAtCer = (TH1D*)h1_Eff2_xAtCer->Clone();
  h1_Eff3_xAtCer->Sumw2();
  h1_Eff3_xAtCer->Divide(h1_Eff1_xAtCer);

  //##############################################################################


 
  //Write the info in the root format

  TFile *OutHisto_file = new TFile(foutname,"RECREATE");
  TDirectory *TCutG_Plots = OutHisto_file->mkdir("TCutG_Plots");
  TCutG_Plots->cd();
  h2_XYAtCer->GetListOfFunctions()->Add(cutg1,"L"); 
  h2_XYAtCer->Write();
  h2_XYAtCer->GetListOfFunctions()->Clear("L"); 
  h2_XYAtCer2->GetListOfFunctions()->Add(cutg2,"L"); 
  h2_XYAtCer2->Write();
  h2_XYAtCer2->GetListOfFunctions()->Clear("L"); 
  h3_XYAtCer_npeSum_pyx->GetListOfFunctions()->Add(cutg1,"L"); 
  h3_XYAtCer_npeSum_pyx->Write();
  h3_XYAtCer_npeSum2_pyx->GetListOfFunctions()->Add(cutg2,"L"); 
  h3_XYAtCer_npeSum2_pyx->Write();
  h3_XYAtCer_npeSum3_pyx->GetListOfFunctions()->Add(cutg3,"L"); 
  h3_XYAtCer_npeSum3_pyx->Write();  
  h2_npeSum_TCutG1_IN->Write();
  h2_npeSum_TCutG1_OUT->Write();
  h2_npeSum_TCutG2_IN->Write();
  h2_npeSum_TCutG2_OUT->Write();
  h2_npeSum_TCutG12_IN->Write();
  h2_npeSum->Write();
  h3_aero_XYAtCer_nocut_npeSum_pyx->Write();  
  h3_aero_XYAtCer_npeSum_pyx->Write();
  TDirectory *MM_Plots = OutHisto_file->mkdir("MM_Plots");
  MM_Plots->cd();
  TDirectory *Eff_Plots = OutHisto_file->mkdir("Eff_Plots");
  Eff_Plots->cd();
  h2_Eff_Pos3->Write(); 
  h1_Eff_Del3->Write();
  h1_Eff3_xAtCer->Write();
  OutHisto_file->Close();
  // TFile g("cutg1.root","recreate");
  //  cutg1->Write();
  //  cutg1->SaveAs("cutg1.root");
  // TString RunNumStr = TInFilename(0,4); Int_t RunNum=(RunNumStr.Atoi());
  //TString OutputStr = Form("%i,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f", RunNum, PionFit->GetParameter(1), PionFit->GetParError(1), PionFWHM, PionFWHMErr, KaonFit->GetParameter(1), KaonFit->GetParError(1), KaonFWHM, KaonFWHMErr, ProtonFit->GetParameter(1), ProtonFit->GetParError(1), ProtonFWHM, ProtonFWHMErr);
    //cout << OutputStr << endl;
}
