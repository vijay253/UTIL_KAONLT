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

// Input should be the input root file name (including suffix) and an output file name string (without any suffix)
void HGC_TCutG(string InFilename = "", string OutFilename = "")
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
  
  TTree* SHMS_EVENTS  = (TTree*)InFile->Get("SHMS_cut_no_Cal_HGC_Aero"); Long64_t nEntries_SHMS_EVENTS  = (Long64_t)SHMS_EVENTS->GetEntries();

  Double_t P_hgcer_npeSum;SHMS_EVENTS->SetBranchAddress("P_hgcer_npeSum", &P_hgcer_npeSum);
  Double_t P_aero_npeSum; SHMS_EVENTS->SetBranchAddress("P_aero_npeSum", &P_aero_npeSum);
  Double_t P_hgcer_xAtCer; SHMS_EVENTS->SetBranchAddress("P_hgcer_xAtCer", &P_hgcer_xAtCer);
  Double_t P_hgcer_yAtCer; SHMS_EVENTS->SetBranchAddress("P_hgcer_yAtCer", &P_hgcer_yAtCer);
  Double_t P_aero_xAtCer; SHMS_EVENTS->SetBranchAddress("P_aero_xAtCer", &P_aero_xAtCer);
  Double_t P_aero_yAtCer; SHMS_EVENTS->SetBranchAddress("P_aero_yAtCer", &P_aero_yAtCer);
  Double_t P_cal_etotnorm; SHMS_EVENTS->SetBranchAddress("P_cal_etotnorm", &P_cal_etotnorm);

  // Defined Geometrical Cuts
  TCutG *cutg = new TCutG("cutg",21);
  cutg->SetVarX("P_hgcer_yAtCer");
  cutg->SetVarY("P_hgcer_xAtCer");
  cutg->SetPoint(0,-25,2);
  cutg->SetPoint(1,-2,2);
  cutg->SetPoint(2,-1,2.5);
  cutg->SetPoint(3,0,3);
  cutg->SetPoint(4,1,3);
  cutg->SetPoint(5,2,3.3);
  cutg->SetPoint(6,3,3.0);
  cutg->SetPoint(7,4,2.5);
  cutg->SetPoint(8,5,2);
  cutg->SetPoint(9,25,2);
  cutg->SetPoint(10,25,0.5);
  cutg->SetPoint(11,5,0.5);
  cutg->SetPoint(12,4,1);
  cutg->SetPoint(13,3,-1);
  cutg->SetPoint(14,2,-2);
  cutg->SetPoint(15,1,-2.3);
  cutg->SetPoint(16,0,-1.5);
  cutg->SetPoint(17,-1,-1);
  cutg->SetPoint(18,-2,0.5);
  cutg->SetPoint(19,-25,0.5);
  cutg->SetPoint(20,-25,2);
  cutg->SetLineColor(kRed);
  cutg->SetLineWidth(5);

  //Histograms 
 
  TH2D *h2_XYAtCer                  = new TH2D("h2_XYAtCer","HGC; P_hgcer_yAtCer; P_hgcer_xAtCer;", 300, -40, 40, 300, -40, 40 );
  TH3D *h3_XYAtCer_npeSum           = new TH3D("h3_XYAtCer_npeSum","HGC; P_hgcer_yAtCer; P_hgcer_xAtCer; P_hgcer_npeSum;", 300, -40, 40, 300, -40, 40, 300, 0, 30);
  TH2D *h2_npeSum                   = new TH2D("h2_npeSum","HGC; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 30, 300, 0.0, 30);
  TH2D *h2_npeSum_TCutG_IN          = new TH2D("h2_npeSum_TCutG_IN","HGC; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 30, 300, 0.0, 30);
  TH2D *h2_npeSum_TCutG_OUT         = new TH2D("h2_npeSum_TCutG_OUT","HGC; P_hgcer_npeSum; P_aero_npeSum;", 300, 0.0, 30, 300, 0.0, 30);


  //Fill xyAtCer entry
      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.5) continue;
    h2_XYAtCer->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer);
  }

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if(P_hgcer_npeSum < 1.5) continue;
    h3_XYAtCer_npeSum->Fill(P_hgcer_yAtCer, P_hgcer_xAtCer,P_hgcer_npeSum);
  }

  // Project 3D histogram on XY

  TProfile2D *h3_XYAtCer_npeSum_pyx = new TProfile2D("h3_XYAtCer_npeSum_pyx","HGC; P_hgcer_yAtCer; P_hgcer_xAtCer ",300,-40,40, 300,-40,40, 0, 30);
  h3_XYAtCer_npeSum->Project3DProfile("yx");

  //Fill NPE entry inside the TCutG      
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (cutg->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    h2_npeSum_TCutG_OUT->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }
  //Fill entry outside the TCutG

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    if (!cutg->IsInside(P_hgcer_yAtCer, P_hgcer_xAtCer)) continue;
    h2_npeSum_TCutG_IN->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }

  //Fill entry without TCutG

  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++){
    SHMS_EVENTS->GetEntry(i);
    h2_npeSum->Fill(P_hgcer_npeSum, P_aero_npeSum);
  }


    // TCanvas *c_CT = new TCanvas("c_CT", "XY Cherenkov", 100, 0, 1000, 900);
    // c_CT->cd();   
    // Pions->Draw("P_hgcer_xAtCer:P_hgcer_yAtCer>>hxy(300,0,30,300,0,30)", "cutg",  "colz");
    // c_CT->SaveAs("v.png");
    // h2_Pions_XYAtCer->Draw("cutg");
    // h1_CT_Kaons->Draw();
    // c_CT->cd(3);
    // h1_CT_Protons->Draw();
    //c_CT->Print(foutpdf);
    
    TFile *OutHisto_file = new TFile(foutname,"RECREATE");
    TDirectory *TCutG_Info = OutHisto_file->mkdir("TCutG_Info");
    TCutG_Info->cd();
    h2_XYAtCer->GetListOfFunctions()->Add(cutg,"L"); 
    h2_XYAtCer->Write();
    h3_XYAtCer_npeSum_pyx->GetListOfFunctions()->Add(cutg,"L"); 
    h3_XYAtCer_npeSum_pyx->Write();
    h2_npeSum_TCutG_IN->Write();
    h2_npeSum_TCutG_OUT->Write();
    h2_npeSum->Write();
    OutHisto_file->Close();
    // TString RunNumStr = TInFilename(0,4); Int_t RunNum=(RunNumStr.Atoi());
    //TString OutputStr = Form("%i,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f", RunNum, PionFit->GetParameter(1), PionFit->GetParError(1), PionFWHM, PionFWHMErr, KaonFit->GetParameter(1), KaonFit->GetParError(1), KaonFWHM, KaonFWHMErr, ProtonFit->GetParameter(1), ProtonFit->GetParError(1), ProtonFWHM, ProtonFWHMErr);
    //cout << OutputStr << endl;
}
