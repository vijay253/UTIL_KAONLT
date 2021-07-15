// .... This script has created to pid study....
// .... Created Date: JULY 15, 2021 ....
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
void SCRIP_REFTime_PLOTS(string InFilename = "", string OutFilename = "")
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
  Double_t T_coin_pFADC_TREF_ROC2_adcPulseTimeRaw; SHMS_EVENTS->SetBranchAddress("T_coin_pFADC_TREF_ROC2_adcPulseTimeRaw", &T_coin_pFADC_TREF_ROC2_adcPulseTimeRaw);
  
  // Hist for filling up the REFTime
  TH1D *H1_REFTime      = new TH1D("H1_REFTime","REFTime; T_coin_pFADC_TREF_ROC2_adcPulseTimeRaw;", 300, 0.0, 8000);
  
  for(Long64_t i = 0; i < nEntries_SHMS_EVENTS; i++)
    {
      SHMS_EVENTS->GetEntry(i);
      
      {
	H1_REFTime->Fill(T_coin_pFADC_TREF_ROC2_adcPulseTimeRaw);
      }
      
    }
  TCanvas *c = new TCanvas ("c");
  c->cd(1);
  // H1_REFTime->Setlogy();
  H1_REFTime->Draw("");
  //Now save the TCanvas
   c->SetLogy();
  c->Print(foutpdf);
}
