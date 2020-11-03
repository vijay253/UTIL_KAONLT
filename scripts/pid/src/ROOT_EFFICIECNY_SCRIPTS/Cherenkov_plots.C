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
  TString rootFile;
  gStyle->SetPalette(55);

  // Set paths depending on system you're running on
  if(Hostname.Contains("farm")){
    Replaypath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt";
    Outpath = Replaypath+"/UTIL_KAONLT/scripts/pid/src/OUTPUT";
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
  TString foutname = Outpath + "/" + TOutFilename + ".root";
  TString foutpdf = Outpath + "/" + TOutFilename + ".pdf";
  
  TTree* Pions = (TTree*)InFile->Get("SHMS_Pions"); Long64_t nEntries_Pions = (Long64_t)Pions->GetEntries();
  //TTree* Kaons = (TTree*)InFile->Get("SHMS_Events_Cut1_(wHGC)"); Long64_t nEntries_Kaons = (Long64_t)Kaons->GetEntries();
  //TTree* Protons = (TTree*)InFile->Get("Protons_All"); Long64_t nEntries_Protons = (Long64_t)Protons->GetEntries();
  // Set branch address -> Need this to ensure event info is entangled correctly for 2D plots
  Double_t XAtCer; Pions->SetBranchAddress("P_hgcer_xAtCer", &XAtCer);
  Double_t YAtCer; Pions->SetBranchAddress("P_hgcer_yAtCer", &YAtCer);
  Double_t Cal_Pr_Shower; Pions->SetBranchAddress("P_cal_pr_eplane", &Cal_Pr_Shower);
  Double_t Cal_Shower; Pions->SetBranchAddress("P_cal_fly_earray", &Cal_Shower);
  Double_t SHMS_gtr_x; Pions->SetBranchAddress("P_gtr_x", &SHMS_gtr_x);
  Double_t SHMS_gtr_y; Pions->SetBranchAddress("P_gtr_y", &SHMS_gtr_y);
  //Double_t CT_kaon; Pions->SetBranchAddress("P_hgcer_npeSum", &CT_kaons);
  // Double_t CT_protons; Protons->SetBranchAddress("CTime_eKCoinTime_ROC1", &CT_protons);

  // Define Histograms
  
  // For 1D histos, can easily create directly from the corresponding branch
  //Pions->Draw("P_hgcer_npeSum >> h1_CT_Pions", "", "goff"); 
  //Kaons->Draw("CTime_eKCoinTime_ROC1 >> h1_CT_Kaons", "", "goff"); 
  //Protons->Draw("CTime_eKCoinTime_ROC1 >> h1_CT_Protons", "", "goff"); 
  TH2D *h2_XYAtCer = new TH2D("h2_XYAtCer","YAtCer vs XAtCer; YAtCer; XAtCer;", 200, -40, 40, 200, -40, 40);
  TH2D *h2_Cal_Showers = new TH2D("h2_Cal_Showers","Cal vs Pr-Shower; Cal; Pr-Shower;", 300, 0.0, 2.0, 300, 0.0, 1.0);
  TH2D *h2_XYgtr = new TH2D("h2_XYgtr","XY gtr; X gtr ; Y gtr;", 300, -3.0, 3.0, 300, -10, 10);

    for(Long64_t i = 0; i < nEntries_Pions; i++){
      Pions->GetEntry(i);
      h2_XYAtCer->Fill(YAtCer, XAtCer);
      h2_Cal_Showers->Fill(Cal_Shower/6.053, Cal_Pr_Shower/6.053);
      h2_XYgtr->Fill(SHMS_gtr_x, SHMS_gtr_y);
    }

  /* Double_t PionMaxEnt=h1_CT_Pions->GetBinContent(h1_CT_Pions->GetMaximumBin());
  Double_t PionMaxVal=h1_CT_Pions->GetBinCenter(h1_CT_Pions->GetMaximumBin());
  Double_t KaonMaxEnt=h1_CT_Kaons->GetBinContent(h1_CT_Kaons->GetMaximumBin());
  Double_t KaonMaxVal=h1_CT_Kaons->GetBinCenter(h1_CT_Kaons->GetMaximumBin());
  Double_t ProtonMaxEnt=h1_CT_Protons->GetBinContent(h1_CT_Protons->GetMaximumBin());
  Double_t ProtonMaxVal=h1_CT_Protons->GetBinCenter(h1_CT_Protons->GetMaximumBin());
  // Define fitting functions, simple Gaussian for each, [0] is amp, [1] is mean, [2] is sigma
  TF1 *PionFit = new TF1("PionFit","([0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2])))");
  PionFit->SetParName(0, "Amplitude");
  PionFit->SetParName(1, "Mean");
  PionFit->SetParName(2, "Sigma");
  PionFit->SetParLimits(0, (PionMaxEnt/2), (PionMaxEnt*2)); PionFit->SetParameter(0, PionMaxEnt);
  PionFit->SetParLimits(1, (PionMaxVal-0.5), (PionMaxVal+0.5)); PionFit->SetParameter(1, PionMaxVal);
  PionFit->SetParLimits(2, 0.1, 2); PionFit->SetParameter(2, 0.2);
  PionFit->SetRange(PionMaxVal-1, PionMaxVal+1);
  TF1 *KaonFit = new TF1("KaonFit","([0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2])))");
  KaonFit->SetParName(0, "Amplitude");
  KaonFit->SetParName(1, "Mean");
  KaonFit->SetParName(2, "Sigma");
  KaonFit->SetParLimits(0, (KaonMaxEnt/2), (KaonMaxEnt*2)); KaonFit->SetParameter(0, KaonMaxEnt);
  KaonFit->SetParLimits(1, (KaonMaxVal-0.5), (KaonMaxVal+0.5)); KaonFit->SetParameter(1, KaonMaxVal);
  KaonFit->SetParLimits(2, 0.1, 2); KaonFit->SetParameter(2, 0.2);
  KaonFit->SetRange(KaonMaxVal-1, KaonMaxVal+1);
  TF1 *ProtonFit = new TF1("ProtonFit","([0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2])))");
  ProtonFit->SetParName(0, "Amplitude");
  ProtonFit->SetParName(1, "Mean");
  ProtonFit->SetParName(2, "Sigma");
  ProtonFit->SetParLimits(0, (ProtonMaxEnt/2), (ProtonMaxEnt*2)); ProtonFit->SetParameter(0, ProtonMaxEnt);
  ProtonFit->SetParLimits(1, (ProtonMaxVal-0.5), (ProtonMaxVal+0.5)); ProtonFit->SetParameter(1, ProtonMaxVal);
  ProtonFit->SetParLimits(2, 0.1, 2); ProtonFit->SetParameter(2, 0.2);
  ProtonFit->SetRange(ProtonMaxVal-1, ProtonMaxVal+1);
  h1_CT_Pions->Fit("PionFit", "RMQ");
  h1_CT_Kaons->Fit("KaonFit", "RMQ");
  h1_CT_Protons->Fit("ProtonFit", "RMQ");
  Double_t PionFWHM=abs(2.355*(PionFit->GetParameter(2))); Double_t PionFWHMErr = abs(2.355*(PionFit->GetParError(2)));
  Double_t KaonFWHM=abs(2.355*(KaonFit->GetParameter(2))); Double_t KaonFWHMErr = abs(2.355*(KaonFit->GetParError(2)));
  Double_t ProtonFWHM=abs(2.355*(ProtonFit->GetParameter(2))); Double_t ProtonFWHMErr = abs(2.355*(ProtonFit->GetParError(2)));
  */
    TCanvas *c_CT = new TCanvas("c_CT", "XY Cherenkov", 100, 0, 1000, 900);
    //h1_CT_Pions->Draw();
    c_CT->cd();
    h2_XYAtCer->Draw("COLZ");
    // h1_CT_Kaons->Draw();
    // c_CT->cd(3);
    // h1_CT_Protons->Draw();
    //c_CT->Print(foutpdf);
    
    TFile *OutHisto_file = new TFile(foutname,"RECREATE");
    TDirectory *XYAtCer = OutHisto_file->mkdir("XYAtCer");
    
    XYAtCer->cd();
    h2_XYAtCer->Write();
    TDirectory *Cal_Showers = OutHisto_file->mkdir("Cal_Showers");

    Cal_Showers->cd();
    h2_Cal_Showers->Write();
   
    TDirectory *XYPOSITIONS = OutHisto_file->mkdir("XY_Positions");
    
    XYPOSITIONS->cd();
    h2_XYgtr->Write();
    //h1_CT_Protons->Write();
  
    OutHisto_file->Close();
    // TString RunNumStr = TInFilename(0,4); Int_t RunNum=(RunNumStr.Atoi());
    //TString OutputStr = Form("%i,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f,%3.3f", RunNum, PionFit->GetParameter(1), PionFit->GetParError(1), PionFWHM, PionFWHMErr, KaonFit->GetParameter(1), KaonFit->GetParError(1), KaonFWHM, KaonFWHMErr, ProtonFit->GetParameter(1), ProtonFit->GetParError(1), ProtonFWHM, ProtonFWHMErr);
    //cout << OutputStr << endl;
}
