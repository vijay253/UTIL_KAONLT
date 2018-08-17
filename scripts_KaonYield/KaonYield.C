#define KaonYield_cxx
// The class definition in KaonYield.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("KaonYield.C")
// root> T->Process("KaonYield.C","some options")
// root> T->Process("KaonYield.C+")
//


#include "KaonYield.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TPaveText.h>

void KaonYield::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  Info("Begin", "Starting Good particle Selection");

  
}

void KaonYield::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

  h2ROC1_Coin_Beta_noID_kaon = new TH2F("ROC1_Coin_Beta_noID_kaon","Kaon Coincident Time vs #beta for ROC1 (no particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_kaon = new TH2F("ROC1_Coin_Beta_kaon","Kaon Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_noID_pion = new TH2F("ROC1_Coin_Beta_noID_pion","Pion Coincident Time vs #beta for ROC1 (no particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_pion = new TH2F("ROC1_Coin_Beta_pion","Pion Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_noID_proton = new TH2F("ROC1_Coin_Beta_noID_proton","Proton Coincident Time vs #beta for ROC1 (no particle ID);Time (ns);#beta",800,-40,40,200,0.0,2.0);
  h2ROC1_Coin_Beta_proton = new TH2F("ROC1_Coin_Beta_proton","Proton Coincident Time vs #beta for ROC1;Time (ns);#beta",800,-40,40,200,0.0,2.0);

  h1HMS_electron        = new TH1F("HMS_electron","Normalized HMS Calorimeter Energy;Normalized Energy;Counts",200,0.01,1.5);
  h1HMS_electron_cut    = new TH1F("HMS_electron_cut","Normalized HMS Calorimeter Energy, Electrons Selected;Normalized Energy;Counts",200,0.01,1.5);

  h1SHMS_electron        = new TH1F("SHMS_electron","Normalized SHMS Calorimeter Energy;Normalized Energy;Counts",200,0.01,1.5);
  h1SHMS_electron_cut    = new TH1F("SHMS_electron_cut","Normalized SHM Calorimeter Energy, Electrons Removed;Normalized Energy;Counts",200,0.01,1.5);

  h2SHMSK_kaon            = new TH2F("SHMSK_kaon","NPE in SHMS Aerogel and Heavy Gas;Aerogel NPE;HGC NPE",50,0.1,25,50,0.1,10);
  h2SHMSK_kaon_cut        = new TH2F("SHMSK_kaon_cut","NPE in SHMS Aerogel and Heavy Gas, Kaons Selected;Aerogel NPE;HGC NPE",50,0.0,25,50,0.0,10);
  h2SHMSK_pion            = new TH2F("SHMSK_pion","NPE in SHMS Noble and Heavy Gas;Noble NPE;HGC NPE",50,0.1,25,50,0.1,10);
  h2SHMSK_pion_cut        = new TH2F("SHMSK_pion_cut","NPE in SHMS Noble and Heavy Gas, Pions Selected;Noble NPE;HGC NPE",50,0.0,25,50,0.0,10);

  h2SHMSpi_kaon            = new TH2F("SHMSpi_kaon","NPE in SHMS Aerogel and Heavy Gas;Aerogel NPE;HGC NPE",50,0.1,25,150,0.1,30);
  h2SHMSpi_kaon_cut        = new TH2F("SHMSpi_kaon_cut","NPE in SHMS Aerogel and Heavy Gas, Kaons Selected;Aerogel NPE;HGC NPE",50,0.0,25,150,0.0,30);
  h2SHMSpi_pion            = new TH2F("SHMSpi_pion","NPE in SHMS Noble and Heavy Gas;Noble NPE;HGC NPE",50,0.1,25,150,0.1,30);
  h2SHMSpi_pion_cut        = new TH2F("SHMSpi_pion_cut","NPE in SHMS Noble and Heavy Gas, Pions Selected;Noble NPE;HGC NPE",50,0.0,25,150,0.0,30);

  h2SHMSp_kaon            = new TH2F("SHMSp_kaon","NPE in SHMS Aerogel and Heavy Gas;Aerogel NPE;HGC NPE",50,0.1,25,50,0.1,10);
  h2SHMSp_kaon_cut        = new TH2F("SHMSp_kaon_cut","NPE in SHMS Aerogel and Heavy Gas, Kaons Selected;Aerogel NPE;HGC NPE",50,0.0,25,50,0.0,10);
  h2SHMSp_pion            = new TH2F("SHMSp_pion","NPE in SHMS Noble and Heavy Gas;Noble NPE;HGC NPE",50,0.1,25,50,0.1,10);
  h2SHMSp_pion_cut        = new TH2F("SHMSp_pion_cut","NPE in SHMS Noble and Heavy Gas, Pions Selected;Noble NPE;HGC NPE",50,0.0,25,50,0.0,10);

  h1SHMS_delta           = new TH1F("SHMS_delta","SHMS #delta;#delta;Counts",100,-50,50);
  h1SHMS_delta_cut       = new TH1F("SHMS_delta_cut","SHMS #delta Cut;#delta;Counts",100,-50,50);
  h1HMS_delta            = new TH1F("HMS_delta","HMS #delta;#delta;Counts",100,-50,50);
  h1HMS_delta_cut        = new TH1F("HMS_delta_cut","HMS #delta Cut;#delta;Counts",100,-50,50);

  h1SHMS_th              = new TH1F("SHMS_th","SHMS Theta Acceptance;#theta;Counts",100,-0.1,0.1);
  h1SHMS_th_cut          = new TH1F("SHMS_th_cut","SHMS Theta Acceptance with Cut;#theta;Counts",100,-0.1,0.1);
  h1SHMS_ph              = new TH1F("SHMS_ph","SHMS Theta Acceptance;#phi;Counts",100,-0.1,0.1);
  h1SHMS_ph_cut          = new TH1F("SHMS_ph_cut","SHMS Theta Acceptance with Cut;#phi;Counts",100,-0.1,0.1);

  h1HMS_th              = new TH1F("HMS_th","HMS Theta Acceptance;#theta;Counts",100,-0.1,0.1);
  h1HMS_th_cut          = new TH1F("HMS_th_cut","HMS Theta Acceptance with Cut;#theta;Counts",100,-0.1,0.1);
  h1HMS_ph              = new TH1F("HMS_ph","HMS Theta Acceptance;#phi;Counts",100,-0.1,0.1);
  h1HMS_ph_cut          = new TH1F("HMS_ph_cut","HMS Theta Acceptance with Cut;#phi;Counts",100,-0.1,0.1);

  h1mmissK                = new TH1F("mmissK","Kaon Missing mass;Mass (GeV/c^{2});Counts",200,0.8,1.8);
  h1mmissK_rand           = new TH1F("mmissK_rand","Kaon Missing mass from Random Coincidence;Mass (GeV/c^{2});Counts",200,0.8,1.8);
  h1mmissK_cut            = new TH1F("mmissK_cut","Kaon Missing mass with Cuts;Mass (GeV/c^{2});Counts",200,0.8,1.8);
  h1mmissK_remove         = new TH1F("mmissK_remove","Kaon Missing mass with Cuts (inc. Rand);Mass (GeV/c^{2});Counts",200,0.8,1.8);

  h1mmisspi               = new TH1F("mmisspi","Pion Missing mass;Mass (GeV/c^{2});Counts",200,0,2.0);
  h1mmisspi_rand          = new TH1F("mmisspi_rand","Pion Missing mass from Random Coincidence;Mass (GeV/c^{2});Counts",200,0.8,1.8);
  h1mmisspi_cut           = new TH1F("mmisspi_cut","Pion Missing mass with Cuts;Mass (GeV/c^{2});Counts",200,0.8,1.8);
  h1mmisspi_remove        = new TH1F("mmisspi_remove","Pion Missing mass with Cuts (inc. Rand);Mass (GeV/c^{2});Counts",200,0.8,1.8);

  h1mmissp                = new TH1F("mmissp","Proton Missing mass;Mass (GeV/c^{2});Counts",200,-0.5,2.0);
  h1mmissp_rand           = new TH1F("mmissp_rand","Proton Missing mass from Random Coincidence;Mass (GeV/c^{2});Counts",200,-0.5,2.0);
  h1mmissp_cut            = new TH1F("mmissp_cut","Proton Missing mass with Cuts;Mass (GeV/c^{2});Counts",200,-0.5,2.0);
  h1mmissp_remove         = new TH1F("mmissp_remove","Proton Missing mass with Cuts (inc. Rand);Mass (GeV/c^{2});Counts",200,-0.5,2.0);

  h2WvsQ2                 = new TH2F("WvsQ2","Q2 vs W;Q2;W",375,0.5,8.0,100,2.0,4.0);
  h2tvsph_q                = new TH2F("tvsph_q",";#phi;t",25,-1.0,1.0,10,-1.0,1.0);
  h1epsilon               = new TH1F("epsilon","Plot of Epsilon;#epsilon;Counts",100,0.0,1.0);

  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_kaon);
  GetOutputList()->Add(h2ROC1_Coin_Beta_kaon);
  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_pion);
  GetOutputList()->Add(h2ROC1_Coin_Beta_pion);
  GetOutputList()->Add(h2ROC1_Coin_Beta_noID_proton);
  GetOutputList()->Add(h2ROC1_Coin_Beta_proton);
  GetOutputList()->Add(h1HMS_electron);
  GetOutputList()->Add(h1HMS_electron_cut);
  GetOutputList()->Add(h1SHMS_electron);
  GetOutputList()->Add(h1SHMS_electron_cut);
  GetOutputList()->Add(h2SHMSK_kaon);
  GetOutputList()->Add(h2SHMSK_kaon_cut);
  GetOutputList()->Add(h2SHMSK_pion);
  GetOutputList()->Add(h2SHMSK_pion_cut);
  GetOutputList()->Add(h2SHMSpi_kaon);
  GetOutputList()->Add(h2SHMSpi_kaon_cut);
  GetOutputList()->Add(h2SHMSpi_pion);
  GetOutputList()->Add(h2SHMSpi_pion_cut);
  GetOutputList()->Add(h2SHMSp_kaon);
  GetOutputList()->Add(h2SHMSp_kaon_cut);
  GetOutputList()->Add(h2SHMSp_pion);
  GetOutputList()->Add(h2SHMSp_pion_cut);
  GetOutputList()->Add(h1SHMS_delta);
  GetOutputList()->Add(h1SHMS_delta_cut);
  GetOutputList()->Add(h1HMS_delta);
  GetOutputList()->Add(h1HMS_delta_cut);
  GetOutputList()->Add(h1SHMS_th);
  GetOutputList()->Add(h1SHMS_th_cut);
  GetOutputList()->Add(h1SHMS_ph);
  GetOutputList()->Add(h1SHMS_ph_cut);
  GetOutputList()->Add(h1HMS_th);
  GetOutputList()->Add(h1HMS_th_cut);
  GetOutputList()->Add(h1HMS_ph);
  GetOutputList()->Add(h1HMS_ph_cut);
  GetOutputList()->Add(h1mmissK);
  GetOutputList()->Add(h1mmissK_rand);
  GetOutputList()->Add(h1mmissK_cut);
  GetOutputList()->Add(h1mmissK_remove);
  GetOutputList()->Add(h1mmisspi);
  GetOutputList()->Add(h1mmisspi_rand);
  GetOutputList()->Add(h1mmisspi_cut);
  GetOutputList()->Add(h1mmisspi_remove);
  GetOutputList()->Add(h1mmissp);
  GetOutputList()->Add(h1mmissp_rand);
  GetOutputList()->Add(h1mmissp_cut);
  GetOutputList()->Add(h1mmissp_remove);
  GetOutputList()->Add(h2WvsQ2);
  GetOutputList()->Add(h2tvsph_q);
  GetOutputList()->Add(h1epsilon);
}

Bool_t KaonYield::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // When processing keyed objects with PROOF, the object is already loaded
  // and is available via the fObject pointer.
  //
  // This function should contain the \"body\" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fReader.SetEntry(entry);

  //if (*fEvtType != 4) return kTRUE;
  
  h1HMS_electron->Fill(H_cal_etotnorm[0]);
  h1SHMS_electron->Fill(P_cal_etotnorm[0]);

  h2SHMSK_kaon->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
  h2SHMSK_pion->Fill(P_ngcer_npeSum[0],P_hgcer_npeSum[0]);
  h2SHMSpi_kaon->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
  h2SHMSpi_pion->Fill(P_ngcer_npeSum[0],P_hgcer_npeSum[0]);
  h2SHMSp_kaon->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
  h2SHMSp_pion->Fill(P_ngcer_npeSum[0],P_hgcer_npeSum[0]);
  
  h1SHMS_delta->Fill(P_gtr_dp[0]);
  h1HMS_delta->Fill(H_gtr_dp[0]);

  h1SHMS_th->Fill(P_gtr_th[0]);
  h1SHMS_ph->Fill(P_gtr_ph[0]);
  h1HMS_th->Fill(H_gtr_th[0]);
  h1HMS_ph->Fill(H_gtr_ph[0]);

  h1mmissK->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
  h1mmisspi->Fill(sqrt(pow(emiss[0] + sqrt(pow(0.493677,2) + pow(P_gtr_p[0],2)) - sqrt(pow(0.13957018,2) + pow(P_gtr_p[0],2)),2)-pow(pmiss[0],2)));
  h1mmissp->Fill(sqrt(pow(emiss[0] + sqrt(pow(0.493677,2) + pow(P_gtr_p[0],2)) - sqrt(pow(0.93828,2) + pow(P_gtr_p[0],2)),2)-pow(pmiss[0],2)));

  if (H_cal_etotnorm[0] < 0.9) return kTRUE;
  if (P_cal_etotnorm[0] > 0.6) return kTRUE;

  if (TMath::Abs(H_gtr_dp[0]) > 10.0) return kTRUE;
  if (P_gtr_dp[0] > 10.0 || P_gtr_dp[0] < -22.0) return kTRUE;

  if (TMath::Abs(P_gtr_th[0]) > 0.040) return kTRUE;
  if (TMath::Abs(P_gtr_ph[0]) > 0.024) return kTRUE;
  if (TMath::Abs(H_gtr_th[0]) > 0.080) return kTRUE;
  if (TMath::Abs(H_gtr_ph[0]) > 0.035) return kTRUE;

  h1HMS_electron_cut->Fill(H_cal_etotnorm[0]);
  h1SHMS_electron_cut->Fill(P_cal_etotnorm[0]);
  
  h1SHMS_delta_cut->Fill(P_gtr_dp[0]);
  h1HMS_delta_cut->Fill(H_gtr_dp[0]);

  h1SHMS_th_cut->Fill(P_gtr_th[0]);
  h1SHMS_ph_cut->Fill(P_gtr_ph[0]);
  h1HMS_th_cut->Fill(H_gtr_th[0]);
  h1HMS_ph_cut->Fill(H_gtr_ph[0]);

  if (P_aero_npeSum[0] > 1.5 && P_hgcer_npeSum[0] < 1.5) { //Event identified as Kaon
    h2ROC1_Coin_Beta_noID_kaon->Fill((CTime_eKCoinTime_ROC1[0] - 10.0),P_gtr_beta[0]); 

    if (abs(P_gtr_beta[0]-1.00) > 0.1) return kTRUE;
  
    if (abs((CTime_eKCoinTime_ROC1[0] - 10.0)) < 2.0) {
      h2ROC1_Coin_Beta_kaon->Fill((CTime_eKCoinTime_ROC1[0] - 10.0),P_gtr_beta[0]);
      h2SHMSK_kaon_cut->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
      h2SHMSK_pion_cut->Fill(P_ngcer_npeSum[0],P_hgcer_npeSum[0]);
      h1mmissK_cut->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));

      h2WvsQ2->Fill(Q2[0],W[0]);
      h2tvsph_q->Fill(ph_q[0],-MandelT[0]);
      h1epsilon->Fill(epsilon[0]);
    }

    if (abs((CTime_eKCoinTime_ROC1[0] - 10.0)) > 3.0 && abs((CTime_eKCoinTime_ROC1[0] - 10.0)) < 15.0) {
      h1mmissK_rand->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
      h1mmissK_remove->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
    }
  }

  if (P_ngcer_npeSum[0] < 1.5 && P_hgcer_npeSum[0] > 1.5) { //Event identified as Pion
    h2ROC1_Coin_Beta_noID_pion->Fill((CTime_ePiCoinTime_ROC1[0] - 10.0),P_gtr_beta[0]);
    
    if (abs(P_gtr_beta[0]-1.00) > 0.1) return kTRUE;
  
    if (abs((CTime_ePiCoinTime_ROC1[0] - 10.0)) < 2.0) {
      h2ROC1_Coin_Beta_pion->Fill((CTime_ePiCoinTime_ROC1[0] - 10.0),P_gtr_beta[0]);
      h2SHMSpi_kaon_cut->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
      h2SHMSpi_pion_cut->Fill(P_ngcer_npeSum[0],P_hgcer_npeSum[0]);
      h1mmisspi_cut->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
    }

     if (abs((CTime_ePiCoinTime_ROC1[0] - 10.0)) > 3.0 && abs((CTime_ePiCoinTime_ROC1[0] - 10.0)) < 15.0) {
      h1mmisspi_rand->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
      h1mmisspi_remove->Fill(sqrt(pow(emiss[0],2)-pow(pmiss[0],2)));
    }
  }

  if (P_aero_npeSum[0] < 1.5 && P_hgcer_npeSum[0] < 1.5) { //Event identified as Proton
    h2ROC1_Coin_Beta_noID_proton->Fill((CTime_epCoinTime_ROC1[0] - 10.0),P_gtr_beta[0]);
    
    if (abs(P_gtr_beta[0]-1.00) > 0.1) return kTRUE;
  
    if (abs((CTime_epCoinTime_ROC1[0] - 10.0)) < 2.0) {
      h2ROC1_Coin_Beta_proton->Fill((CTime_epCoinTime_ROC1[0] - 10.0),P_gtr_beta[0]);
      h2SHMSp_kaon_cut->Fill(P_aero_npeSum[0],P_hgcer_npeSum[0]);
      h2SHMSp_pion_cut->Fill(P_ngcer_npeSum[0],P_hgcer_npeSum[0]);
      h1mmissp_cut->Fill(sqrt(pow(emiss[0] + sqrt(pow(0.13957018,2) + pow(P_gtr_p[0],2)) - sqrt(pow(0.93828,2) + pow(P_gtr_p[0],2)),2)-pow(pmiss[0],2)));
    }

    if (abs((CTime_epCoinTime_ROC1[0] - 10.0)) > 3.0 && abs((CTime_epCoinTime_ROC1[0] - 10.0)) < 15.0) {
      h1mmissp_rand->Fill(sqrt(pow(emiss[0] + sqrt(pow(0.13957018,2) + pow(P_gtr_p[0],2)) - sqrt(pow(0.93828,2) + pow(P_gtr_p[0],2)),2)-pow(pmiss[0],2)));
      h1mmissp_remove->Fill(sqrt(pow(emiss[0] + sqrt(pow(0.13957018,2) + pow(P_gtr_p[0],2)) - sqrt(pow(0.93828,2) + pow(P_gtr_p[0],2)),2)-pow(pmiss[0],2)));
    }
  }

  return kTRUE;
}

void KaonYield::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void KaonYield::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  Info("Terminate", "Outputting Good Kaon Selection");

  //Perform Random Subtraction
  h1mmissK_rand->Scale(1.0/3.0);
  h1mmisspi_rand->Scale(1.0/3.0);
  h1mmissp_rand->Scale(1.0/3.0);
  h1mmissK_remove->Add(h1mmissK_cut,h1mmissK_rand,1,-1);
  h1mmisspi_remove->Add(h1mmisspi_cut,h1mmisspi_rand,1,-1);
  h1mmissp_remove->Add(h1mmissp_cut,h1mmissp_rand,1,-1);

  //Perform Background Subtraction
  TF1 *Back_Fit = new TF1("Back_Fit","[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",1.3,1.8);
  Back_Fit->SetParName(0,"Amplitude");
  Back_Fit->SetParName(1,"Mean");
  Back_Fit->SetParName(2,"Sigma");
  Back_Fit->SetParLimits(0,0.0,10000.0);
  Back_Fit->SetParLimits(1,1.3,1.8);
  Back_Fit->SetParLimits(2,0.0,1.0);
  Back_Fit->SetParameter(0,20);
  Back_Fit->SetParameter(1,1.44);
  Back_Fit->SetParameter(2,0.16);
  h1mmissK_remove->Fit("Back_Fit","RMQN");
  TH1F *h1mmissK_noback = (TH1F*) h1mmissK_remove->Clone();
  h1mmissK_noback->Add(Back_Fit,-1);

  //Fit the Lambda Missing Mass
  TF1 *Lambda_Fit = new TF1("Lambda_Fit","[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",1.105,1.15);
  Lambda_Fit->SetParName(0,"Amplitude");
  Lambda_Fit->SetParName(1,"Mean");
  Lambda_Fit->SetParName(2,"Sigma");
  Lambda_Fit->SetParLimits(0,0.0,10000.0);
  Lambda_Fit->SetParLimits(1,1.115,1.13);
  Lambda_Fit->SetParLimits(2,0.0,0.1);
  Lambda_Fit->SetParameter(0,100);
  Lambda_Fit->SetParameter(1,1.1156);
  Lambda_Fit->SetParameter(2,0.011);
  h1mmissK_remove->Fit("Lambda_Fit","RMQN");
  TF1 *Lambda_Fit_Full = new TF1("Lambda_Fit_Full","[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",1.0,1.25);
  Lambda_Fit_Full->SetParName(0,"Amplitude");
  Lambda_Fit_Full->SetParName(1,"Mean");
  Lambda_Fit_Full->SetParName(2,"Sigma");
  Lambda_Fit_Full->SetParameter(0,Lambda_Fit->GetParameter(0));
  Lambda_Fit_Full->SetParameter(1,Lambda_Fit->GetParameter(1));
  Lambda_Fit_Full->SetParameter(2,Lambda_Fit->GetParameter(2));

  
  //Start of Canvas Painting
  
  TCanvas *cCuts = new TCanvas("Cuts","Summary of Common Cuts");
  cCuts->Divide(2,4);
  cCuts->cd(1); h1HMS_delta->Draw();
  cCuts->cd(2); h1HMS_delta_cut->Draw();
  cCuts->cd(3); h1SHMS_delta->Draw();
  cCuts->cd(4); h1SHMS_delta_cut->Draw();
  cCuts->cd(5); h1HMS_electron->Draw();
  cCuts->cd(6); h1HMS_electron_cut->Draw();
  cCuts->cd(7); h1SHMS_electron->Draw();
  cCuts->cd(8); h1SHMS_electron_cut->Draw();

  TCanvas *cAngles = new TCanvas("Angles","Summary of Angular Cuts");
  cAngles->Divide(2,4);
  cAngles->cd(1); h1HMS_th->Draw();
  cAngles->cd(2); h1HMS_th_cut->Draw();
  cAngles->cd(3); h1HMS_ph->Draw();
  cAngles->cd(4); h1HMS_ph_cut->Draw();
  cAngles->cd(5); h1SHMS_th->Draw();
  cAngles->cd(6); h1SHMS_th_cut->Draw();
  cAngles->cd(7); h1SHMS_ph->Draw();
  cAngles->cd(8); h1SHMS_ph_cut->Draw();
  
  TCanvas *cRand = new TCanvas("Rand","Summary of Random Correction");
  cRand->Divide(3,3);
  cRand->cd(1); h1mmissK_cut->Draw();
  cRand->cd(2); h1mmisspi_cut->Draw();
  cRand->cd(3); h1mmissp_cut->Draw();
  cRand->cd(4); h1mmissK_rand->Draw("hist");
  cRand->cd(5); h1mmisspi_rand->Draw("hist");
  cRand->cd(6); h1mmissp_rand->Draw("hist");
  cRand->cd(7); h1mmissK_remove->Draw("hist");
  cRand->cd(8); h1mmisspi_remove->Draw("hist");
  cRand->cd(9); h1mmissp_remove->Draw("hist");
  

  //TCanvas *cBack = new TCanvas("Back","Summary of Background Removal");
  //cBack->Divide(2,1);
  //cBack->cd(1); h1mmissK_remove->Draw("hist");
  //Back_Fit->Draw("same");
  //cBack->cd(2); h1mmissK_noback->Draw("hist");

  
  TCanvas *cID = new TCanvas("ID","Summary of Kaon Particle ID Cuts");
  cID->Divide(2,4);
  cID->cd(1); h2SHMSK_kaon->Draw("Colz");
  cID->cd(2); h2SHMSK_kaon_cut->Draw("Colz");
  cID->cd(3); h2SHMSK_pion->Draw("Colz");
  cID->cd(4); h2SHMSK_pion_cut->Draw("Colz");
  cID->cd(5); h2ROC1_Coin_Beta_noID_kaon->Draw("Colz");
  cID->Update();
  TLine *LowerRand = new TLine(3.0,gPad->GetUymin(),3.0,gPad->GetUymax()); 
  LowerRand->SetLineColor(kRed); LowerRand->SetLineWidth(1); LowerRand->Draw();
  TLine *UpperRand = new TLine(15.0,gPad->GetUymin(),15.0,gPad->GetUymax()); 
  UpperRand->SetLineColor(kRed); UpperRand->SetLineWidth(1); UpperRand->Draw();
  cID->cd(6); h2ROC1_Coin_Beta_kaon->Draw("Colz");
  cID->cd(7); h1mmissK->Draw();
  cID->cd(8); h1mmissK_remove->Draw("hist");
  cID->Update();
  TLine *LambdaMass = new TLine(1.1156,0,1.1156,gPad->GetUymax()); 
  LambdaMass->SetLineColor(kBlack); LambdaMass->SetLineWidth(3);
  LambdaMass->Draw();
  Lambda_Fit_Full->Draw("same");

  TCanvas *cpiID = new TCanvas("piID","Summary of Pion Particle ID Cuts");
  cpiID->Divide(2,4);
  cpiID->cd(1); h2SHMSpi_kaon->Draw("Colz");
  cpiID->cd(2); h2SHMSpi_kaon_cut->Draw("Colz");
  cpiID->cd(3); h2SHMSpi_pion->Draw("Colz");
  cpiID->cd(4); h2SHMSpi_pion_cut->Draw("Colz");
  cpiID->cd(5); h2ROC1_Coin_Beta_noID_pion->Draw("Colz");
  LowerRand->Draw(); UpperRand->Draw();
  cpiID->cd(6); h2ROC1_Coin_Beta_pion->Draw("Colz");
  cpiID->cd(7); h1mmisspi->Draw();
  cpiID->cd(8); h1mmisspi_remove->Draw("hist");
  cpiID->Update();
  TLine *NeutronMass = new TLine(0.93957,0,0.93957,gPad->GetUymax()); 
  NeutronMass->SetLineColor(kBlack); NeutronMass->SetLineWidth(3);
  NeutronMass->Draw();
  TF1 *Neutron_Fit = new TF1("Neutron_Fit","[0]*exp(-0.5*((x-[1])/[2])*((x-[1])/[2]))",0.8,1.0);
  Neutron_Fit->SetParName(0,"Amplitude");
  Neutron_Fit->SetParName(1,"Mean");
  Neutron_Fit->SetParName(2,"Sigma");
  Neutron_Fit->SetParLimits(0,0.0,10000.0);
  Neutron_Fit->SetParLimits(1,0.9,1.0);
  Neutron_Fit->SetParLimits(2,0.0,1.0);
  Neutron_Fit->SetParameter(0,100);
  Neutron_Fit->FixParameter(1,0.93957);
  Neutron_Fit->SetParameter(2,0.011);
  h1mmisspi_remove->Fit("Neutron_Fit","RMQ");
  Neutron_Fit->Draw("same");

  TCanvas *cpID = new TCanvas("pID","Summary of Proton Particle ID Cuts");
  cpID->Divide(2,4);
  cpID->cd(1); h2SHMSp_kaon->Draw("Colz");
  cpID->cd(2); h2SHMSp_kaon_cut->Draw("Colz");
  cpID->cd(3); h2SHMSp_pion->Draw("Colz");
  cpID->cd(4); h2SHMSp_pion_cut->Draw("Colz");
  cpID->cd(5); h2ROC1_Coin_Beta_noID_proton->Draw("Colz");
  LowerRand->Draw(); UpperRand->Draw();
  cpID->cd(6); h2ROC1_Coin_Beta_proton->Draw("Colz");
  cpID->cd(7); h1mmissp->Draw();
  cpID->cd(8); h1mmissp_remove->Draw("hist");
  

  TCanvas *cKine = new TCanvas("Kine","Summary of Higher Order Kinemaics");
  cKine->Divide(2,2);
  cKine->cd(1); h2WvsQ2->Draw("Colz"); 
  h2WvsQ2->SetTitleOffset(1.0,"Y");
  cKine->cd(3); h2tvsph_q->Draw("SURF1 POL");
  gPad->SetTheta(90); gPad->SetPhi(180);
  TPaveText *tvsphi_title = new TPaveText(0.0277092,0.89779,0.096428,0.991854,"NDC");
  tvsphi_title->AddText("t vs #phi"); tvsphi_title->Draw();
  TLine *phizero = new TLine(0,0,1,0); 
  phizero->SetLineColor(kBlack); phizero->SetLineWidth(2); phizero->Draw();  
  TPaveText *ptphizero = new TPaveText(0.923951,0.513932,0.993778,0.574551,"NDC");
  ptphizero->AddText("#phi = 0"); ptphizero->Draw();
  TLine *phihalfpi = new TLine(0,0,0,1); 
  phihalfpi->SetLineColor(kBlack); phihalfpi->SetLineWidth(2); phihalfpi->Draw();  
  TPaveText *ptphihalfpi = new TPaveText(0.417855,0.901876,0.486574,0.996358,"NDC");
  ptphihalfpi->AddText("#phi = #frac{#pi}{2}"); ptphihalfpi->Draw();
  TLine *phipi = new TLine(0,0,-1,0); 
  phipi->SetLineColor(kBlack); phipi->SetLineWidth(2); phipi->Draw();  
  TPaveText *ptphipi = new TPaveText(0.0277092,0.514217,0.096428,0.572746,"NDC");
  ptphipi->AddText("#phi = #pi"); ptphipi->Draw();
  TLine *phithreepi = new TLine(0,0,0,-1); 
  phithreepi->SetLineColor(kBlack); phithreepi->SetLineWidth(2); phithreepi->Draw();  
  TPaveText *ptphithreepi = new TPaveText(0.419517,0.00514928,0.487128,0.0996315,"NDC");
  ptphithreepi->AddText("#phi = #frac{3#pi}{2}"); ptphithreepi->Draw();
  cKine->cd(2); h1epsilon->Draw();
  h1epsilon->SetTitleOffset(1.0,"Y");
  cKine->cd(4); h1mmissK_remove->Draw("hist"); Lambda_Fit_Full->Draw("same");
  cKine->Update();
  h1mmissK_remove->SetTitleOffset(1.0,"Y"); /*h1mmissK_remove->SetAxisRange(1.0,1.25,"X");*/ h1mmissK_remove->SetAxisRange(0.0,gPad->GetUymax(),"Y");
  cKine->Update();
  TLine *LambdaMass_Full = new TLine(1.1156,gPad->GetUymin(),1.1156,gPad->GetUymax()); 
  LambdaMass_Full->SetLineColor(kBlack); LambdaMass_Full->SetLineWidth(3);
  LambdaMass_Full->Draw();
  TPaveText *ptLambdaEvt = new TPaveText(0.527698,0.652567,0.738421,0.791456,"NDC");
  ptLambdaEvt->AddText(Form("# of #Lambda Events: %.0f",200*Lambda_Fit_Full->Integral(1.0,1.25))); ptLambdaEvt->Draw();

  //Start output of .root file with all histograms
  TString option = GetOption();
  TFile *Histogram_file = new TFile(Form("../Histograms/KaonLT_Run%i.root",option.Atoi()),"RECREATE");
  TDirectory *DCuts = Histogram_file->mkdir("Spectrometer Delta and Calorimeter Cuts"); DCuts->cd();
  h1HMS_delta->Write("HMS Delta Before Cuts"); h1HMS_delta_cut->Write("HMS Delta After Cuts");
  h1SHMS_delta->Write("SHMS Delta Before Cuts"); h1SHMS_delta_cut->Write("SHMS Delta After Cuts");
  h1HMS_electron->Write("HMS Calorimeter Before Cuts"); h1HMS_electron_cut->Write("HMS Calorimeter After Cuts");
  h1SHMS_electron->Write("SHMS Calorimeter Before Cuts"); h1SHMS_electron_cut->Write("SHMS Calorimeter After Cuts");

  TDirectory *DAngles = Histogram_file->mkdir("Spectrometer Angular Cuts"); DAngles->cd();
  h1HMS_th->Write("HMS Theta Before Cuts"); h1HMS_th_cut->Write("HMS Theta After Cuts");
  h1SHMS_th->Write("SHMS Theta Before Cuts"); h1SHMS_th_cut->Write("SHMS Theta After Cuts");
  h1HMS_ph->Write("HMS Phi Before Cuts"); h1HMS_ph_cut->Write("HMS Phi After Cuts");
  h1SHMS_ph->Write("SHMS Phi Before Cuts"); h1SHMS_ph_cut->Write("SHMS Phi After Cuts");

  TDirectory *DRand = Histogram_file->mkdir("Random Subtraction Summary"); DRand->cd();
  h1mmissK_cut->Write("Kaon Missing Mass, with Randoms");
  h1mmissK_rand->Write("Kaon Missing Mass, only Randoms");
  h1mmissK_remove->Write("Kaon Missing Mass, Randoms Removed");
  h1mmisspi_cut->Write("Pion Missing Mass, with Randoms");
  h1mmisspi_rand->Write("Pion Missing Mass, only Randoms");
  h1mmisspi_remove->Write("Pion Missing Mass, Randoms Removed");
  h1mmissp_cut->Write("Proton Missing Mass, with Randoms");
  h1mmissp_rand->Write("Proton Missing Mass, only Randoms");
  h1mmissp_remove->Write("Proton Missing Mass, Randoms Removed");

  TDirectory *DKaon = Histogram_file->mkdir("Kaon Identification Summary"); DKaon->cd();
  h2SHMSK_kaon->Write("SHMS HGC vs Aerogel, no cuts");
  h2SHMSK_kaon_cut->Write("SHMS HGC vs Aerogel, with cuts");
  h2SHMSK_pion->Write("SHMS HGC vs NGC, no cuts");
  h2SHMSK_pion_cut->Write("SHMS HGC vs NGC, with cuts");
  h2ROC1_Coin_Beta_noID_kaon->Write("Kaon-Electron Coincidence Time, no cuts");
  h2ROC1_Coin_Beta_kaon->Write("Kaon-Electron Coincidence Time, with cuts");
  h1mmissK->Write("Kaon Missing Mass, no cuts");
  h1mmissK_remove->Write("Kaon Missing Mass, with cuts");

  TDirectory *DPion = Histogram_file->mkdir("Pion Identification Summary"); DPion->cd();
  h2SHMSpi_kaon->Write("SHMS HGC vs Aerogel, no cuts");
  h2SHMSpi_kaon_cut->Write("SHMS HGC vs Aerogel, with cuts");
  h2SHMSpi_pion->Write("SHMS HGC vs NGC, no cuts");
  h2SHMSpi_pion_cut->Write("SHMS HGC vs NGC, with cuts");
  h2ROC1_Coin_Beta_noID_kaon->Write("Pion-Electron Coincidence Time, no cuts");
  h2ROC1_Coin_Beta_kaon->Write("Pion-Electron Coincidence Time, with cuts");
  h1mmisspi->Write("Pion Missing Mass, no cuts");
  h1mmisspi_remove->Write("Pion Missing Mass, with cuts");

  TDirectory *DProton = Histogram_file->mkdir("Proton Identification Summary"); DProton->cd();
  h2SHMSp_kaon->Write("SHMS HGC vs Aerogel, no cuts");
  h2SHMSp_kaon_cut->Write("SHMS HGC vs Aerogel, with cuts");
  h2SHMSp_pion->Write("SHMS HGC vs NGC, no cuts");
  h2SHMSp_pion_cut->Write("SHMS HGC vs NGC, with cuts");
  h2ROC1_Coin_Beta_noID_kaon->Write("Proton-Electron Coincidence Time, no cuts");
  h2ROC1_Coin_Beta_kaon->Write("Proton-Electron Coincidence Time, with cuts");
  h1mmissp->Write("Proton Missing Mass, no cuts");
  h1mmissp_remove->Write("Proton Missing Mass, with cuts");

  TDirectory *DKine = Histogram_file->mkdir("Higher Order Kinematics Summary"); DKine->cd();
  h2WvsQ2->Write("W vs Q2");
  h2tvsph_q->Write("t vs phi");
  h1epsilon->Write("epsilon");
  h1mmissK_remove->Write("Kaon Missing Mass, with cuts");
  Histogram_file->Close();
  
  cout << Form("Number of good kaon events: %.0f +/- %.0f\n",200*Lambda_Fit_Full->Integral(1.0,1.25),sqrt(200*Lambda_Fit_Full->Integral(1.0,1.25)));

  // values for controlling format
  const string sep = "	" ;
  const int total_width = 154;
  const string line = sep + string( total_width-1, '-' ) + '|' ;


  ofstream myfile1;
  myfile1.open ("kaonyieldVar", fstream::app);
  myfile1 <<
    left << 200*Lambda_Fit_Full->Integral(1.0,1.25) << "\n";
  myfile1.close();
}
