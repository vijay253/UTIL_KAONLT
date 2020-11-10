// 19/10/20 - Stephen Kay, University of Regina

// root .c macro plotting script, reads in desired trees from analysed root file and plots some stuff
// Saves  pdf file with plots and a .root file
#define Cherenkov_plots_cxx

// Include relevant stuff
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

// Input should be the input root file name (including suffix) and an output file name string (without any suffix)
void Cherenkov_plots(string InFilename = "", string OutFilename = "")
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
    // Output path for output file
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

  // Particles information with HGC cuts
  
  TTree* Pions     = (TTree*)InFile->Get("SHMS_Pions")  ; Long64_t nEntries_Pions = (Long64_t)Pions->GetEntries();
  TTree* Kaons     = (TTree*)InFile->Get("SHMS_Kaons")  ; Long64_t nEntries_Kaons = (Long64_t)Kaons->GetEntries();
  TTree* Protons   = (TTree*)InFile->Get("SHMS_Protons"); Long64_t nEntries_Protons = (Long64_t)Protons->GetEntries();

 // Particles information no HGC cuts
  
  TTree* Pions_No_HGC_Cuts     = (TTree*)InFile->Get("SHMS_Pions_Without_HGC_Cuts")  ; Long64_t nEntries_Pions_No_HGC_Cuts = (Long64_t)Pions_No_HGC_Cuts->GetEntries();
  TTree* Kaons_No_HGC_Cuts     = (TTree*)InFile->Get("SHMS_Kaons_Without_HGC_Cuts")  ; Long64_t nEntries_Kaons_No_HGC_Cuts = (Long64_t)Kaons_No_HGC_Cuts->GetEntries();
  TTree* Protons_No_HGC_Cuts   = (TTree*)InFile->Get("SHMS_Protons_Without_HGC_Cuts"); Long64_t nEntries_Protons_No_HGC_Cuts = (Long64_t)Protons_No_HGC_Cuts->GetEntries();
  TTree* Pions_No_Aero_Cuts   = (TTree*)InFile->Get("SHMS_Pions_Aero_Without_Aero_Cuts"); Long64_t nEntries_Pions_No_Aero_Cuts = (Long64_t)Pions_No_Aero_Cuts->GetEntries();
  TTree* Pions_No_Cal_Cuts   = (TTree*)InFile->Get("SHMS_Pions_Cal_Without_Cal_Cuts"); Long64_t nEntries_Pions_No_Cal_Cuts = (Long64_t)Pions_No_Cal_Cuts->GetEntries();

 // Particles information no cuts
  
  TTree* SHMS_Events = (TTree*)InFile->Get("SHMS_Events")  ; Long64_t nEntries_SHMS_Events = (Long64_t)SHMS_Events->GetEntries();


  Double_t aero_npeSum; Pions_No_Aero_Cuts->SetBranchAddress("P_aero_npeSum", &aero_npeSum);
  Double_t cal_etotnorm; Pions_No_Cal_Cuts->SetBranchAddress("P_cal_etotnorm", &cal_etotnorm);



  // Set branch address for no cuts
 
  Double_t XAtCer; SHMS_Events->SetBranchAddress("P_hgcer_xAtCer", &XAtCer);
  Double_t YAtCer; SHMS_Events->SetBranchAddress("P_hgcer_yAtCer", &YAtCer);
  Double_t Prshower; SHMS_Events->SetBranchAddress("P_cal_pr_eplane", &Prshower);
  Double_t Cal; SHMS_Events->SetBranchAddress("P_cal_fly_earray", &Cal);
  Double_t gtr_x; SHMS_Events->SetBranchAddress("P_gtr_x", &gtr_x);
  Double_t gtr_y; SHMS_Events->SetBranchAddress("P_gtr_y", &gtr_y);
  Double_t gtr_beta; SHMS_Events->SetBranchAddress("P_gtr_beta", &gtr_beta);
  Double_t gtr_p; SHMS_Events->SetBranchAddress("P_gtr_p", &gtr_p);
  Double_t gtr_dp; SHMS_Events->SetBranchAddress("P_gtr_dp", &gtr_dp);
  Double_t gtr_xp; SHMS_Events->SetBranchAddress("P_gtr_xp", &gtr_xp);
  Double_t gtr_yp; SHMS_Events->SetBranchAddress("P_gtr_yp", &gtr_yp);
  Double_t hgcer_npeSum; SHMS_Events->SetBranchAddress("P_hgcer_npeSum", &hgcer_npeSum);
  Double_t P_cal_etot; SHMS_Events->SetBranchAddress("P_cal_etotnorm", &P_cal_etot);
  Double_t CTime_ePi_ROC1; SHMS_Events->SetBranchAddress("CTime_ePiCoinTime_ROC1", &CTime_ePi_ROC1);
  Double_t CTime_eK_ROC1; SHMS_Events->SetBranchAddress("CTime_eKCoinTime_ROC1", &CTime_eK_ROC1);
  Double_t CTime_eP_ROC1; SHMS_Events->SetBranchAddress("CTime_epCoinTime_ROC1", &CTime_eP_ROC1);

  // Set branch address for no HGC cuts


  Double_t XAtCer_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_hgcer_xAtCer", &XAtCer_no_HGC_cut);
  Double_t YAtCer_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_hgcer_yAtCer", &YAtCer_no_HGC_cut);
  Double_t Prshower_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_cal_pr_eplane", &Prshower_no_HGC_cut);
  Double_t Cal_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_cal_fly_earray", &Cal_no_HGC_cut);
  Double_t gtr_x_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_gtr_x", &gtr_x_no_HGC_cut);
  Double_t gtr_y_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_gtr_y", &gtr_y_no_HGC_cut);
  Double_t gtr_beta_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_gtr_beta", &gtr_beta_no_HGC_cut);
  Double_t gtr_p_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_gtr_p", &gtr_p_no_HGC_cut);
  Double_t gtr_dp_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_gtr_dp", &gtr_dp_no_HGC_cut);
  Double_t gtr_xp_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_gtr_xp", &gtr_xp_no_HGC_cut);
  Double_t gtr_yp_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_gtr_yp", &gtr_yp_no_HGC_cut);
  Double_t hgcer_npeSum_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_hgcer_npeSum", &hgcer_npeSum_no_HGC_cut);
  Double_t P_cal_etot_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("P_cal_etotnorm", &P_cal_etot_no_HGC_cut);
  Double_t CTime_ePi_ROC1_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("CTime_ePiCoinTime_ROC1", &CTime_ePi_ROC1_no_HGC_cut);
  Double_t CTime_eK_ROC1_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("CTime_eKCoinTime_ROC1", &CTime_eK_ROC1_no_HGC_cut);
  Double_t CTime_eP_ROC1_no_HGC_cut; Pions_No_HGC_Cuts->SetBranchAddress("CTime_epCoinTime_ROC1", &CTime_eP_ROC1_no_HGC_cut);

 // Set branch address for Pions with HGC cuts

 //Pions
  Double_t Pions_XAtCer; Pions->SetBranchAddress("P_hgcer_xAtCer", &Pions_XAtCer);
  Double_t Pions_YAtCer; Pions->SetBranchAddress("P_hgcer_yAtCer", &Pions_YAtCer);
  Double_t Pions_Cal_Pr_Shower; Pions->SetBranchAddress("P_cal_pr_eplane", &Pions_Cal_Pr_Shower);
  Double_t Pions_Cal_Shower; Pions->SetBranchAddress("P_cal_fly_earray", &Pions_Cal_Shower);
  Double_t Pions_SHMS_gtr_x; Pions->SetBranchAddress("P_gtr_x", &Pions_SHMS_gtr_x);
  Double_t Pions_SHMS_gtr_y; Pions->SetBranchAddress("P_gtr_y", &Pions_SHMS_gtr_y);
  Double_t Pions_SHMS_hgcer_npeSum; Pions->SetBranchAddress("P_hgcer_npeSum", &Pions_SHMS_hgcer_npeSum);
  Double_t Pions_SHMS_aero_npeSum; Pions->SetBranchAddress("P_aero_npeSum", &Pions_SHMS_hgcer_npeSum);

 // Set branch address for Kaons with HGC cuts

  //Kaons
  Double_t Kaons_XAtCer; Kaons->SetBranchAddress("P_hgcer_xAtCer", &Kaons_XAtCer);
  Double_t Kaons_YAtCer; Kaons->SetBranchAddress("P_hgcer_yAtCer", &Kaons_YAtCer);
  Double_t Kaons_Cal_Pr_Shower; Kaons->SetBranchAddress("P_cal_pr_eplane", &Kaons_Cal_Pr_Shower);
  Double_t Kaons_Cal_Shower; Kaons->SetBranchAddress("P_cal_fly_earray", &Kaons_Cal_Shower);
  Double_t Kaons_SHMS_gtr_x; Kaons->SetBranchAddress("P_gtr_x", &Kaons_SHMS_gtr_x);
  Double_t Kaons_SHMS_gtr_y; Kaons->SetBranchAddress("P_gtr_y", &Kaons_SHMS_gtr_y);
  Double_t Kaons_SHMS_hgcer_npeSum; Kaons->SetBranchAddress("P_hgcer_npeSum", &Kaons_SHMS_hgcer_npeSum);

 // Set branch address for Protons with HGC cuts
 
 //Protons
  Double_t Protons_XAtCer; Protons->SetBranchAddress("P_hgcer_xAtCer", &Protons_XAtCer);
  Double_t Protons_YAtCer; Protons->SetBranchAddress("P_hgcer_yAtCer", &Protons_YAtCer);
  Double_t Protons_Cal_Pr_Shower; Protons->SetBranchAddress("P_cal_pr_eplane", &Protons_Cal_Pr_Shower);
  Double_t Protons_Cal_Shower; Protons->SetBranchAddress("P_cal_fly_earray", &Protons_Cal_Shower);
  Double_t Protons_SHMS_gtr_x; Protons->SetBranchAddress("P_gtr_x", &Protons_SHMS_gtr_x);
  Double_t Protons_SHMS_gtr_y; Protons->SetBranchAddress("P_gtr_y", &Protons_SHMS_gtr_y);
  Double_t Protons_SHMS_hgcer_npeSum; Protons->SetBranchAddress("P_hgcer_npeSum", &Protons_SHMS_hgcer_npeSum);
  
  // Set branch address for Pions with no HGC cuts

  //Pions
  Double_t Pions_No_HGC_Cuts_XAtCer; Pions_No_HGC_Cuts->SetBranchAddress("P_hgcer_xAtCer", &Pions_No_HGC_Cuts_XAtCer);
  Double_t Pions_No_HGC_Cuts_YAtCer; Pions_No_HGC_Cuts->SetBranchAddress("P_hgcer_yAtCer", &Pions_No_HGC_Cuts_YAtCer);
  Double_t Pions_No_HGC_Cuts_Cal_Pr_Shower; Pions_No_HGC_Cuts->SetBranchAddress("P_cal_pr_eplane", &Pions_No_HGC_Cuts_Cal_Pr_Shower);
  Double_t Pions_No_HGC_Cuts_Cal_Shower; Pions_No_HGC_Cuts->SetBranchAddress("P_cal_fly_earray", &Pions_No_HGC_Cuts_Cal_Shower);
  Double_t Pions_No_HGC_Cuts_SHMS_gtr_x; Pions_No_HGC_Cuts->SetBranchAddress("P_gtr_x", &Pions_No_HGC_Cuts_SHMS_gtr_x);
  Double_t Pions_No_HGC_Cuts_SHMS_gtr_y; Pions_No_HGC_Cuts->SetBranchAddress("P_gtr_y", &Pions_No_HGC_Cuts_SHMS_gtr_y);
  Double_t Pions_No_HGC_Cuts_SHMS_hgcer_npeSum; Pions_No_HGC_Cuts->SetBranchAddress("P_hgcer_npeSum", &Pions_No_HGC_Cuts_SHMS_hgcer_npeSum);
  
 // Set branch address for Kaons with no HGC cuts

  //Kaons
  Double_t Kaons_No_HGC_Cuts_XAtCer; Kaons_No_HGC_Cuts->SetBranchAddress("P_hgcer_xAtCer", &Kaons_No_HGC_Cuts_XAtCer);
  Double_t Kaons_No_HGC_Cuts_YAtCer; Kaons_No_HGC_Cuts->SetBranchAddress("P_hgcer_yAtCer", &Kaons_No_HGC_Cuts_YAtCer);
  Double_t Kaons_No_HGC_Cuts_Cal_Pr_Shower; Kaons_No_HGC_Cuts->SetBranchAddress("P_cal_pr_eplane", &Kaons_No_HGC_Cuts_Cal_Pr_Shower);
  Double_t Kaons_No_HGC_Cuts_Cal_Shower; Kaons_No_HGC_Cuts->SetBranchAddress("P_cal_fly_earray", &Kaons_No_HGC_Cuts_Cal_Shower);
  Double_t Kaons_No_HGC_Cuts_SHMS_gtr_x; Kaons_No_HGC_Cuts->SetBranchAddress("P_gtr_x", &Kaons_No_HGC_Cuts_SHMS_gtr_x);
  Double_t Kaons_No_HGC_Cuts_SHMS_gtr_y; Kaons_No_HGC_Cuts->SetBranchAddress("P_gtr_y", &Kaons_No_HGC_Cuts_SHMS_gtr_y);
  Double_t Kaons_No_HGC_Cuts_SHMS_hgcer_npeSum; Kaons_No_HGC_Cuts->SetBranchAddress("P_hgcer_npeSum", &Kaons_No_HGC_Cuts_SHMS_hgcer_npeSum);
  
 // Set branch address for Protons with no HGC cuts

 //Protons
  Double_t Protons_No_HGC_Cuts_XAtCer; Protons_No_HGC_Cuts->SetBranchAddress("P_hgcer_xAtCer", &Protons_No_HGC_Cuts_XAtCer);
  Double_t Protons_No_HGC_Cuts_YAtCer; Protons_No_HGC_Cuts->SetBranchAddress("P_hgcer_yAtCer", &Protons_No_HGC_Cuts_YAtCer);
  Double_t Protons_No_HGC_Cuts_Cal_Pr_Shower; Protons_No_HGC_Cuts->SetBranchAddress("P_cal_pr_eplane", &Protons_No_HGC_Cuts_Cal_Pr_Shower);
  Double_t Protons_No_HGC_Cuts_Cal_Shower; Protons_No_HGC_Cuts->SetBranchAddress("P_cal_fly_earray", &Protons_No_HGC_Cuts_Cal_Shower);
  Double_t Protons_No_HGC_Cuts_SHMS_gtr_x; Protons_No_HGC_Cuts->SetBranchAddress("P_gtr_x", &Protons_No_HGC_Cuts_SHMS_gtr_x);
  Double_t Protons_No_HGC_Cuts_SHMS_gtr_y; Protons_No_HGC_Cuts->SetBranchAddress("P_gtr_y", &Protons_No_HGC_Cuts_SHMS_gtr_y);
  Double_t Protons_No_HGC_Cuts_SHMS_hgcer_npeSum; Protons_No_HGC_Cuts->SetBranchAddress("P_hgcer_npeSum", &Protons_No_HGC_Cuts_SHMS_hgcer_npeSum);
 

  // Define Histograms for with HGC cuts
  
  // For 1D histos, can easily create directly from the corresponding branch
  //Pions->Draw("P_hgcer_npeSum >> h1_CT_Pions", "", "goff"); 
  //Kaons->Draw("CTime_eKCoinTime_ROC1 >> h1_CT_Kaons", "", "goff"); 
  //Protons->Draw("CTime_eKCoinTime_ROC1 >> h1_CT_Protons", "", "goff"); 

 //Histograms for aerogel and Cal
  TH1D *h1_aero_npeSum = new TH1D("h1_aero_npeSum","NPE vs Events; NPE; Events;", 300, 0.0, 30);

  for(Long64_t i = 0; i <nEntries_Pions_No_Aero_Cuts; i++){
    Pions_No_Aero_Cuts->GetEntry(i);
    h1_aero_npeSum->Fill(aero_npeSum);
  }

    TH1D *h1_cal_etot = new TH1D("h1_cal_etot","Calorimeter; Cal; Events;", 300, 0.0, 30);
      
    for(Long64_t i = 0; i <nEntries_Pions_No_Cal_Cuts; i++){
      Pions_No_Cal_Cuts->GetEntry(i);
      h1_cal_etot->Fill(cal_etotnorm); 
    }

  //Histograms for not  cuts

  TH1D *h1_hgcer_npeSum = new TH1D("h1_hgcer_npeSum","NPE vs Events; NPE; Events;", 300, 0.0, 30);
  TH1D *h1_XAtCer = new TH1D("h1_XAtCer","XAtCer; XAtCer; Events;", 300, -40, 40);
  TH1D *h1_YAtCer = new TH1D("h1_YAtCer","YAtCer; YAtCer; Events;", 300, -40, 40);
  TH1D *h1_Cal = new TH1D("h1_Cal","Calorimeter; Cal; Events;", 300, 0.0, 10.0);
  TH1D *h1_Prshower = new TH1D("h1_Prshower","Preshower; Prshower; Events;", 300, 0.0, 10.0);
  TH1D *h1_Xgtr = new TH1D("h1_Xgtr","X gtr; X gtr ; Events;", 300, -3.0, 3.0);
  TH1D *h1_Ygtr = new TH1D("h1_Ygtr","Y gtr; Y gtr ; Events;", 300, -3.0, 3.0);
  TH1D *h1_P_etot = new TH1D("h1_P_etot","P_cal_etotnorm; P_cal_etotnorm; Events;", 300, 0.0, 10.0);
  TH1D *h1_gtr_beta = new TH1D("h1_gtr_beta","P_gtr_beta; P_gtr_beta; Events;", 300, 0.0, 10.0);
  TH1D *h1_gtr_p = new TH1D("h1_gtr_p","P_gtr_p; P_gtr_p; Events;", 300, -10.0, 10.0);
  TH1D *h1_gtr_dp = new TH1D("h1_gtr_dp","P_gtr_dp; P_gtr_dp; Events;", 300, -30.0, 30.0);
  TH1D *h1_gtr_xp = new TH1D("h1_gtr_xp","P_gtr_xp; P_gtr_xp; Events;", 300, -40.0, 40.0);
  TH1D *h1_gtr_yp = new TH1D("h1_gtr_yp","P_gtr_yp; P_gtr_yp; Events;", 300, -40.0, 40.0);
  TH1D *h1_CTime_ePi_ROC1 = new TH1D("h1_CTime_ePi_ROC1","CTime_ePiCoinTime_ROC1; CTime_ePiCoinTime_ROC1; Events;", 300, -10.0, 100.0);
  TH1D *h1_CTime_eK_ROC1 = new TH1D("h1_CTime_eK_ROC1","CTime_eKCoinTime_ROC1; CTime_eKCoinTime_ROC1; Events;", 300, -10.0, 100.0);
  TH1D *h1_CTime_eP_ROC1 = new TH1D("h1_CTime_eP_ROC1","CTime_epCoinTime_ROC1; CTime_epCoinTime_ROC1; Events;", 300, -10.0, 100.0);
  
    for(Long64_t i = 0; i <nEntries_SHMS_Events; i++){
      SHMS_Events->GetEntry(i);
      h1_hgcer_npeSum->Fill(hgcer_npeSum);
      h1_XAtCer->Fill(XAtCer);
      h1_YAtCer->Fill(YAtCer);
      h1_Cal->Fill(Cal);
      h1_Prshower->Fill(Prshower);
      h1_Xgtr->Fill(gtr_x);
      h1_Ygtr->Fill(gtr_y);
      h1_P_etot->Fill(P_cal_etot);  
      h1_gtr_beta->Fill(gtr_beta);  
      h1_gtr_p->Fill(gtr_p);
      h1_gtr_dp->Fill(gtr_dp);
      h1_gtr_xp->Fill(gtr_xp);
      h1_gtr_yp->Fill(gtr_yp);
      h1_CTime_ePi_ROC1->Fill(CTime_ePi_ROC1);
      h1_CTime_eK_ROC1->Fill(CTime_eK_ROC1);
      h1_CTime_eP_ROC1->Fill(CTime_eP_ROC1);
  }

    //Histograms for cuts + HGC cuts
    //Pions
    TH1D *h1_Pions_hgcer_npeSum = new TH1D("h1_Pion_hgcer_npeSum","NPE vs Events; NPE; Events;", 300, 0.0, 40);
    TH2D *h2_Pions_XYAtCer = new TH2D("h2_Pions_XYAtCer","YAtCer vs XAtCer; YAtCer; XAtCer;", 200, -40, 40, 200, -40, 40);
    TH2D *h2_Pions_Cal_Showers = new TH2D("h2_Pions_Cal_Showers","Cal vs Pr-Shower; Cal; Pr-Shower;", 300, 0.0, 2.0, 300, 0.0, 1.0);
    TH2D *h2_Pions_XYgtr = new TH2D("h2_Pions_XYgtr","XY gtr; X gtr ; Y gtr;", 300, -3.0, 3.0, 300, -10, 10);
    TH2D *h2_Pions_Eff = new TH2D("h2_Pions_Eff","Efficiency VS Position; X gtr ; Y gtr;", 200, -40, 40, 200, -40, 40);
    TH1D *h1_Pions_aero_npeSum = new TH1D("h1_Pion_aero_npeSum","NPE vs Events; NPE; Events;", 300, 0.0, 40);
   
    for(Long64_t i = 0; i < nEntries_Pions; i++){
      Pions->GetEntry(i);
      h2_Pions_XYAtCer->Fill(Pions_YAtCer, Pions_XAtCer);
      h2_Pions_Cal_Showers->Fill(Pions_Cal_Shower/6.053, Pions_Cal_Pr_Shower/6.053);
      h2_Pions_XYgtr->Fill(Pions_SHMS_gtr_x, Pions_SHMS_gtr_y);
      h1_Pions_hgcer_npeSum->Fill(Pions_SHMS_hgcer_npeSum);
      h1_Pions_aero_npeSum->Fill(Pions_SHMS_aero_npeSum);   
    }

    //Histograms for cuts + HGC cuts
    //Kaons
    TH1D *h1_Kaons_hgcer_npeSum = new TH1D("h1_Kaons_hgcer_npeSum","NPE vs Events; NPE; Events;", 300, 0.0, 40);
    TH2D *h2_Kaons_XYAtCer = new TH2D("h2_Kaons_XYAtCer","YAtCer vs XAtCer; YAtCer; XAtCer;", 200, -40, 40, 200, -40, 40);
    TH2D *h2_Kaons_Cal_Showers = new TH2D("h2_Kaons_Cal_Showers","Cal vs Pr-Shower; Cal; Pr-Shower;", 300, 0.0, 2.0, 300, 0.0, 1.0);
    TH2D *h2_Kaons_XYgtr = new TH2D("h2_Kaons_XYgtr","XY gtr; X gtr ; Y gtr;", 300, -3.0, 3.0, 300, -10, 10);

    for(Long64_t i = 0; i < nEntries_Kaons; i++){
      Kaons->GetEntry(i);
      h2_Kaons_XYAtCer->Fill(Kaons_YAtCer, Kaons_XAtCer);
      h2_Kaons_Cal_Showers->Fill(Kaons_Cal_Shower/6.053, Kaons_Cal_Pr_Shower/6.053);
      h2_Kaons_XYgtr->Fill(Kaons_SHMS_gtr_x, Kaons_SHMS_gtr_y);
      h1_Kaons_hgcer_npeSum->Fill(Kaons_SHMS_hgcer_npeSum);
    }

    //Histograms for cuts + HGC cuts
    //Protons
    TH1D *h1_Protons_hgcer_npeSum = new TH1D("h1_Protons_hgcer_npeSum","NPE vs Events; NPE; Events;", 300, 0.0, 40);
    TH2D *h2_Protons_XYAtCer = new TH2D("h2_Protons_XYAtCer","YAtCer vs XAtCer; YAtCer; XAtCer;", 200, -40, 40, 200, -40, 40);
    TH2D *h2_Protons_Cal_Showers = new TH2D("h2_Protons_Cal_Showers","Cal vs Pr-Shower; Cal; Pr-Shower;", 300, 0.0, 2.0, 300, 0.0, 1.0);
    TH2D *h2_Protons_XYgtr = new TH2D("h2_Protons_XYgtr","XY gtr; X gtr ; Y gtr;", 300, -3.0, 3.0, 300, -10, 10);

    for(Long64_t i = 0; i < nEntries_Protons; i++){
      Protons->GetEntry(i);
      h2_Protons_XYAtCer->Fill(Protons_YAtCer, Protons_XAtCer);
      h2_Protons_Cal_Showers->Fill(Protons_Cal_Shower/6.053, Protons_Cal_Pr_Shower/6.053);
      h2_Protons_XYgtr->Fill(Protons_SHMS_gtr_x, Protons_SHMS_gtr_y);
      h1_Protons_hgcer_npeSum->Fill(Protons_SHMS_hgcer_npeSum);

    }

    //Histograms for cuts + no HGC cuts
    //Pions
    TH1D *h1_Pi_hgcer_npeSum = new TH1D("h1_Pi_hgcer_npeSum","NPE vs Events; NPE; Events;", 300, 0.0, 30);
    TH1D *h1_Pi_XAtCer = new TH1D("h1_Pi_XAtCer","XAtCer; XAtCer; Events;", 300, -40, 40);
    TH1D *h1_Pi_YAtCer = new TH1D("h1_Pi_YAtCer","YAtCer; YAtCer; Events;", 300, -40, 40);
    TH1D *h1_Pi_Cal = new TH1D("h1_Pi_Cal","Calorimeter; Cal; Events;", 300, 0.0, 10.0);
    TH1D *h1_Pi_Prshower = new TH1D("h1_Pi_Prshower","Preshower; Prshower; Events;", 300, 0.0, 10.0);
    TH1D *h1_Pi_Xgtr = new TH1D("h1_Pi_Xgtr","X gtr; X gtr ; Events;", 300, -3.0, 3.0);
    TH1D *h1_Pi_Ygtr = new TH1D("h1_Pi_Ygtr","Y gtr; Y gtr ; Events;", 300, -3.0, 3.0);
    TH1D *h1_Pi_P_etot = new TH1D("h1_Pi_P_etot","P_cal_etotnorm; P_cal_etotnorm; Events;", 300, 0.0, 10.0);
    TH1D *h1_Pi_gtr_beta = new TH1D("h1_Pi_gtr_beta","P_gtr_beta; P_gtr_beta; Events;", 300, 0.0, 10.0);
    TH1D *h1_Pi_gtr_p = new TH1D("h1_Pi_gtr_p","P_gtr_p; P_gtr_p; Events;", 300, -10.0, 10.0);
    TH1D *h1_Pi_gtr_dp = new TH1D("h1_Pi_gtr_dp","P_gtr_dp; P_gtr_dp; Events;", 300, -30.0, 30.0);
    TH1D *h1_Pi_gtr_xp = new TH1D("h1_Pi_gtr_xp","P_gtr_xp; P_gtr_xp; Events;", 300, -40.0, 40.0);
    TH1D *h1_Pi_gtr_yp = new TH1D("h1_Pi_gtr_yp","P_gtr_yp; P_gtr_yp; Events;", 300, -40.0, 40.0);
    TH1D *h1_Pi_CTime_ePi_ROC1 = new TH1D("h1_Pi_CTime_ePi_ROC1","CTime_ePiCoinTime_ROC1; CTime_ePiCoinTime_ROC1; Events;", 300, -10.0, 100.0);
    TH1D *h1_Pi_CTime_eK_ROC1 = new TH1D("h1_Pi_CTime_eK_ROC1","CTime_eKCoinTime_ROC1; CTime_eKCoinTime_ROC1; Events;", 300, -10.0, 100.0);
    TH1D *h1_Pi_CTime_eP_ROC1 = new TH1D("h1_Pi_CTime_eP_ROC1","CTime_epCoinTime_ROC1; CTime_epCoinTime_ROC1; Events;", 300, -10.0, 100.0);

    TH1D *h1_Pions_No_HGC_Cuts_hgcer_npeSum = new TH1D("h1_Pions_No_HGC_Cuts_hgcer_npeSum","NPE vs Events; NPE; Events;", 300, 0.0, 40);
    TH2D *h2_Pions_No_HGC_Cuts_XYAtCer = new TH2D("h2_Pions_No_HGC_Cuts_XYAtCer","YAtCer vs XAtCer; YAtCer; XAtCer;", 200, -40, 40, 200, -40, 40);
    TH2D *h2_Pions_No_HGC_Cuts_Cal_Showers = new TH2D("h2_Pions_No_HGC_Cuts_Cal_Showers","Cal vs Pr-Shower; Cal; Pr-Shower;", 300, 0.0, 2.0, 300, 0.0, 1.0);
    TH2D *h2_Pions_No_HGC_Cuts_XYgtr = new TH2D("h2_Pions_No_HGC_Cuts_XYgtr","XY gtr; X gtr ; Y gtr;", 300, -3.0, 3.0, 300, -10, 10);
  
    for(Long64_t i = 0; i < nEntries_Pions_No_HGC_Cuts; i++){
      Pions_No_HGC_Cuts->GetEntry(i);
      h2_Pions_No_HGC_Cuts_XYAtCer->Fill(Pions_No_HGC_Cuts_YAtCer, Pions_No_HGC_Cuts_XAtCer);
      h2_Pions_No_HGC_Cuts_Cal_Showers->Fill(Pions_No_HGC_Cuts_Cal_Shower/6.053, Pions_No_HGC_Cuts_Cal_Pr_Shower/6.053);
      h2_Pions_No_HGC_Cuts_XYgtr->Fill(Pions_No_HGC_Cuts_SHMS_gtr_x, Pions_No_HGC_Cuts_SHMS_gtr_y);
      h1_Pions_No_HGC_Cuts_hgcer_npeSum->Fill(Pions_No_HGC_Cuts_SHMS_hgcer_npeSum);     

      h1_Pi_hgcer_npeSum->Fill(hgcer_npeSum_no_HGC_cut);
      h1_Pi_XAtCer->Fill(XAtCer_no_HGC_cut);
      h1_Pi_YAtCer->Fill(YAtCer_no_HGC_cut);
      h1_Pi_Cal->Fill(Cal_no_HGC_cut);
      h1_Pi_Prshower->Fill(Prshower_no_HGC_cut);
      h1_Pi_Xgtr->Fill(gtr_x_no_HGC_cut);
      h1_Pi_Ygtr->Fill(gtr_y_no_HGC_cut);
      h1_Pi_P_etot->Fill(P_cal_etot_no_HGC_cut);  
      h1_Pi_gtr_beta->Fill(gtr_beta_no_HGC_cut);  
      h1_Pi_gtr_p->Fill(gtr_p_no_HGC_cut);
      h1_Pi_gtr_dp->Fill(gtr_dp_no_HGC_cut);
      h1_Pi_gtr_xp->Fill(gtr_xp_no_HGC_cut);
      h1_Pi_gtr_yp->Fill(gtr_yp_no_HGC_cut);
      h1_Pi_CTime_ePi_ROC1->Fill(CTime_ePi_ROC1_no_HGC_cut);
      h1_Pi_CTime_eK_ROC1->Fill(CTime_eK_ROC1_no_HGC_cut);
      h1_Pi_CTime_eP_ROC1->Fill(CTime_eP_ROC1_no_HGC_cut);

    }
    TH1D *h1_Kaons_No_HGC_Cuts_hgcer_npeSum = new TH1D("h1_Kaons_No_HGC_Cuts_hgcer_npeSum","NPE vs Events; NPE; Events;", 300, 0.0, 40);
    TH2D *h2_Kaons_No_HGC_Cuts_XYAtCer = new TH2D("h2_Kaons_No_HGC_Cuts_XYAtCer","YAtCer vs XAtCer; YAtCer; XAtCer;", 200, -40, 40, 200, -40, 40);
    TH2D *h2_Kaons_No_HGC_Cuts_Cal_Showers = new TH2D("h2_Kaons_No_HGC_Cuts_Cal_Showers","Cal vs Pr-Shower; Cal; Pr-Shower;", 300, 0.0, 2.0, 300, 0.0, 1.0);
    TH2D *h2_Kaons_No_HGC_Cuts_XYgtr = new TH2D("h2_Kaons_No_HGC_Cuts_XYgtr","XY gtr; X gtr ; Y gtr;", 300, -3.0, 3.0, 300, -10, 10);
    
    for(Long64_t i = 0; i < nEntries_Kaons_No_HGC_Cuts; i++){
      Kaons_No_HGC_Cuts->GetEntry(i);
      h2_Kaons_No_HGC_Cuts_XYAtCer->Fill(Kaons_No_HGC_Cuts_YAtCer, Kaons_No_HGC_Cuts_XAtCer);
      h2_Kaons_No_HGC_Cuts_Cal_Showers->Fill(Kaons_No_HGC_Cuts_Cal_Shower/6.053, Kaons_No_HGC_Cuts_Cal_Pr_Shower/6.053);
      h2_Kaons_No_HGC_Cuts_XYgtr->Fill(Kaons_No_HGC_Cuts_SHMS_gtr_x, Kaons_No_HGC_Cuts_SHMS_gtr_y);
      h1_Kaons_No_HGC_Cuts_hgcer_npeSum->Fill(Kaons_No_HGC_Cuts_SHMS_hgcer_npeSum);

    }
    TH1D *h1_Protons_No_HGC_Cuts_hgcer_npeSum = new TH1D("h1_Protons_No_HGC_Cuts_hgcer_npeSum","NPE vs Events; NPE; Events;", 300, 0.0, 40);
    TH2D *h2_Protons_No_HGC_Cuts_XYAtCer = new TH2D("h2_Protons_No_HGC_Cuts_XYAtCer","YAtCer vs XAtCer; YAtCer; XAtCer;", 200, -40, 40, 200, -40, 40);
    TH2D *h2_Protons_No_HGC_Cuts_Cal_Showers = new TH2D("h2_Protons_No_HGC_Cuts_Cal_Showers","Cal vs Pr-Shower; Cal; Pr-Shower;", 300, 0.0, 2.0, 300, 0.0, 1.0);
    TH2D *h2_Protons_No_HGC_Cuts_XYgtr = new TH2D("h2_Protons_No_HGC_Cuts_XYgtr","XY gtr; X gtr ; Y gtr;", 300, -3.0, 3.0, 300, -10, 10);

    for(Long64_t i = 0; i < nEntries_Protons_No_HGC_Cuts; i++){
      Protons_No_HGC_Cuts->GetEntry(i);
      h2_Protons_No_HGC_Cuts_XYAtCer->Fill(Protons_No_HGC_Cuts_YAtCer, Protons_No_HGC_Cuts_XAtCer);
      h2_Protons_No_HGC_Cuts_Cal_Showers->Fill(Protons_No_HGC_Cuts_Cal_Shower/6.053, Protons_No_HGC_Cuts_Cal_Pr_Shower/6.053);
      h2_Protons_No_HGC_Cuts_XYgtr->Fill(Protons_No_HGC_Cuts_SHMS_gtr_x, Protons_No_HGC_Cuts_SHMS_gtr_y);
      h1_Protons_No_HGC_Cuts_hgcer_npeSum->Fill(Kaons_No_HGC_Cuts_SHMS_hgcer_npeSum);

    }


    TCanvas *c_CT = new TCanvas("c_CT", "XY Cherenkov", 100, 0, 1000, 900);
    //h1_CT_Pions->Draw();
    c_CT->cd();
    h2_Pions_XYAtCer->Draw("COLZ");
    // h1_CT_Kaons->Draw();
    // c_CT->cd(3);
    // h1_CT_Protons->Draw();
    //c_CT->Print(foutpdf);
    
    TFile *OutHisto_file = new TFile(foutname,"RECREATE");
    TDirectory *Pions_info = OutHisto_file->mkdir("Pions_info");
    
    Pions_info->cd();
    h2_Pions_XYAtCer->Write();
    h2_Pions_Cal_Showers->Write();
    h2_Pions_XYgtr->Write();
    h1_Pions_hgcer_npeSum->Write();
    h1_Pions_aero_npeSum->Write();
    //    h2_Pions_Eff->Write();
    TDirectory *Kaons_info = OutHisto_file->mkdir("Kaons_info");
    
    Kaons_info->cd();
    h2_Kaons_XYAtCer->Write();
    h2_Kaons_Cal_Showers->Write();
    h2_Kaons_XYgtr->Write();
    h1_Kaons_hgcer_npeSum->Write();

    TDirectory *Protons_info = OutHisto_file->mkdir("Protons_info");
    
    Protons_info->cd();
    h2_Protons_XYAtCer->Write();
    h2_Protons_Cal_Showers->Write();
    h2_Protons_XYgtr->Write();
    h1_Protons_hgcer_npeSum->Write();

    TDirectory *Pions_No_HGC_Cuts_info = OutHisto_file->mkdir("Pions_No_HGC_Cuts_info");
    
    Pions_No_HGC_Cuts_info->cd();
    h2_Pions_No_HGC_Cuts_XYAtCer->Write();
    h2_Pions_No_HGC_Cuts_Cal_Showers->Write();
    h2_Pions_No_HGC_Cuts_XYgtr->Write();
    h1_Pions_No_HGC_Cuts_hgcer_npeSum->Write();
   
    h1_Pi_XAtCer->Write();
    h1_Pi_YAtCer->Write();
    h1_Pi_Cal->Write();
    h1_Pi_Prshower->Write();
    h1_Pi_Xgtr->Write();
    h1_Pi_Ygtr->Write();
    h1_Pi_hgcer_npeSum->Write();
    h1_Pi_P_etot->Write();
    h1_Pi_gtr_beta->Write();
    h1_Pi_gtr_p->Write();
    h1_Pi_gtr_dp->Write();
    h1_Pi_gtr_xp->Write();  
    h1_Pi_gtr_yp->Write();  
    h1_Pi_CTime_ePi_ROC1->Write();  
    h1_Pi_CTime_eK_ROC1->Write();  
    h1_Pi_CTime_eP_ROC1->Write();  
   


    TDirectory *Kaons_No_HGC_Cuts_info = OutHisto_file->mkdir("Kaons_No_HGC_Cuts_info");
    
    Kaons_No_HGC_Cuts_info->cd();
    h2_Kaons_No_HGC_Cuts_XYAtCer->Write();
    h2_Kaons_No_HGC_Cuts_Cal_Showers->Write();
    h2_Kaons_No_HGC_Cuts_XYgtr->Write();
    h1_Kaons_No_HGC_Cuts_hgcer_npeSum->Write();
    TDirectory *Protons_No_HGC_Cuts_info = OutHisto_file->mkdir("Protons_No_HGC_Cuts_info");
    
    Protons_No_HGC_Cuts_info->cd();
    h2_Protons_No_HGC_Cuts_XYAtCer->Write();
    h2_Protons_No_HGC_Cuts_Cal_Showers->Write();
    h2_Protons_No_HGC_Cuts_XYgtr->Write();
    h1_Protons_No_HGC_Cuts_hgcer_npeSum->Write();

 TDirectory *SHMS_Events_No_Cuts = OutHisto_file->mkdir("SHMS_Events_No_Cuts");
    
    SHMS_Events_No_Cuts->cd();
    h1_XAtCer->Write();
    h1_YAtCer->Write();
    h1_Cal->Write();
    h1_Prshower->Write();
    h1_Xgtr->Write();
    h1_Ygtr->Write();
    h1_hgcer_npeSum->Write();
    h1_P_etot->Write();
    h1_gtr_beta->Write();
    h1_gtr_p->Write();
    h1_gtr_dp->Write();
    h1_gtr_xp->Write();  
    h1_gtr_yp->Write();  
    h1_CTime_ePi_ROC1->Write();  
    h1_CTime_eK_ROC1->Write();  
    h1_CTime_eP_ROC1->Write();  

    TDirectory *SHMS_Events_No_Aero_Cuts = OutHisto_file->mkdir("SHMS_Events_No_Aero_Cuts");
    
    SHMS_Events_No_Aero_Cuts->cd();
     
    h1_aero_npeSum->Write();

    TDirectory *SHMS_Events_No_Cal_Cuts = OutHisto_file->mkdir("SHMS_Events_No_Cal_Cuts");
    SHMS_Events_No_Cal_Cuts->cd();
     
    h1_cal_etot->Write();

    OutHisto_file->Close();
    // TString RunNumStr = TInFilename(0,4); Int_t RunNum=(RunNumStr.Atoi());
    //TString OutputStr = Form("%i,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f", RunNum, PionFit->GetParameter(1), PionFit->GetParError(1), PionFWHM, PionFWHMErr, KaonFit->GetParameter(1), KaonFit->GetParError(1), KaonFWHM, KaonFWHMErr, ProtonFit->GetParameter(1), ProtonFit->GetParError(1), ProtonFWHM, ProtonFWHMErr);
    //cout << OutputStr << endl;
}
