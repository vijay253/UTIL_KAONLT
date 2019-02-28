#define TrackingTest_cxx
// The class definition in TrackingTest.h has been generated automatically
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
// root> T->Process("TrackingTest.C")
// root> T->Process("TrackingTest..C","some options")
// root> T->Process("TrackingTest..C+")
//


#include "TrackingTest.h"
#include <fstream>
#include <TStyle.h>
#include "TProof.h"

void TrackingTest::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).
    printf("\n\n");

    TString option = GetOption();
    Info("Begin", "Starting tracking test for carbon target");
    Info("Begin", "Options entered: %s", option.Data());
    printf("\n\n");

    fFullShow = kTRUE;
}

void TrackingTest::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();

    // Event and timing histograms
    EventType   = new TH1F("Event_Type" ,"Counts for each Event Type",20,0,10);
    EDTM  = new TH1F("EDTM","EDTM counts",4000,-1000.0,2000.0);
    HMS_EDTM  = new TH1F("HMS_EDTM","HMS EDTM counts",4000,-1000.0,1000.0); // After cuts on HMS EDTM
    SHMS_EDTM = new TH1F("SHMS_EDTM","SHMS EDTM counts",4000,-1000.0,2000.0);
    TRIG1     = new TH1F("TRIG1","pTRIG1 counts",4000,-1000.0,2000.0); //SHMS TDC time
    TRIG3     = new TH1F("TRIG3","pTRIG3 counts",4000,-1000.0,2000.0); // HMS TDC time
    TRIG5     = new TH1F("TRIG5","pTRIG5 counts",4000,0.0,1000.0); // Coin (?) TDC time
    TRIG1_cut = new TH1F("TRIG1_cut","pTRIG1 counts",4000,-1000.0,1000.0); // SHMS TDC time after cut
    TRIG3_cut = new TH1F("TRIG3_cut","pTRIG3 counts",4000,0.0,1000.0); // HMS TDC time after cut

    SHMS_nHits_Ch1_Pass = new TH1F*[6];
    SHMS_nHits_Ch2_Pass = new TH1F*[6];
    SHMS_nHits_Ch1_Fail = new TH1F*[6];
    SHMS_nHits_Ch2_Fail = new TH1F*[6];

    HMS_nHits_Ch1_Pass = new TH1F*[6];
    HMS_nHits_Ch2_Pass = new TH1F*[6];
    HMS_nHits_Ch1_Fail = new TH1F*[6];
    HMS_nHits_Ch2_Fail = new TH1F*[6];

    for(Int_t i = 0; i < 6; i++){
        SHMS_nHits_Ch1_Pass[i] = new TH1F(Form("SHMS_nHits_Ch1P%i_Pass", i+1), Form("SHMS CH1P%i n_{Hit} Distribution (Passing n_{HitTot} < n_{max})", i+1), 20, 0, 20);
        SHMS_nHits_Ch2_Pass[i] = new TH1F(Form("SHMS_nHits_Ch2P%i_Pass", i+1), Form("SHMS CH2P%i n_{Hit} Distribution (Passing n_{HitTot} < n_{max})", i+1), 20, 0, 20);
        SHMS_nHits_Ch1_Fail[i] = new TH1F(Form("SHMS_nHits_Ch1P%i_Fail", i+1), Form("SHMS CH1P%i n_{Hit} Distribution (Failing n_{HitTot} < n_{max})", i+1), 50, 0, 50);
        SHMS_nHits_Ch2_Fail[i] = new TH1F(Form("SHMS_nHits_Ch2P%i_Fail", i+1), Form("SHMS CH2P%i n_{Hit} Distribution (Failing n_{HitTot} < n_{max})", i+1), 50, 0, 50);

        fOutput->Add(SHMS_nHits_Ch1_Pass[i]);
        fOutput->Add(SHMS_nHits_Ch2_Pass[i]);
        fOutput->Add(SHMS_nHits_Ch1_Fail[i]);
        fOutput->Add(SHMS_nHits_Ch2_Fail[i]);

        HMS_nHits_Ch1_Pass[i] = new TH1F(Form("HMS_nHits_Ch1P%i_Pass", i+1), Form("HMS CH1P%i n_{Hit} Distribution (Passing n_{HitTot} < n_{max})", i+1), 20, 0, 20);
        HMS_nHits_Ch2_Pass[i] = new TH1F(Form("HMS_nHits_Ch2P%i_Pass", i+1), Form("HMS CH2P%i n_{Hit} Distribution (Passing n_{HitTot} < n_{max})", i+1), 20, 0, 20);
        HMS_nHits_Ch1_Fail[i] = new TH1F(Form("HMS_nHits_Ch1P%i_Fail", i+1), Form("HMS CH1P%i n_{Hit} Distribution (Failing n_{HitTot} < n_{max})", i+1), 50, 0, 50);
        HMS_nHits_Ch2_Fail[i] = new TH1F(Form("HMS_nHits_Ch2P%i_Fail", i+1), Form("HMS CH2P%i n_{Hit} Distribution (Failing n_{HitTot} < n_{max})", i+1), 50, 0, 50);

        fOutput->Add(HMS_nHits_Ch1_Pass[i]);
        fOutput->Add(HMS_nHits_Ch2_Pass[i]);
        fOutput->Add(HMS_nHits_Ch1_Fail[i]);
        fOutput->Add(HMS_nHits_Ch2_Fail[i]);
    }

    HMS_Ch1_nHits_Pass = new TH2F("HMS_Ch1_nHits_Pass", "HMS Ch1 nHits(DC Plane) (Passing n_{HitTot} < n_{max})", 6, 0, 6, 20, 0, 20);
    HMS_Ch1_nHits_Fail = new TH2F("HMS_Ch1_nHits_Fail", "HMS Ch1 nHits(DC Plane) (Failing n_{HitTot} < n_{max})", 6, 0, 6, 50, 0, 50);
    HMS_Ch2_nHits_Pass = new TH2F("HMS_Ch2_nHits_Pass", "HMS Ch2 nHits(DC Plane) (Passing n_{HitTot} < n_{max})", 6, 0, 6, 20, 0, 20);
    HMS_Ch2_nHits_Fail = new TH2F("HMS_Ch2_nHits_Fail", "HMS Ch2 nHits(DC Plane) (Failing n_{HitTot} < n_{max})", 6, 0, 6, 50, 0, 50);

    SHMS_Ch1_nHits_Pass = new TH2F("SHMS_Ch1_nHits_Pass", "SHMS Ch1 nHits(DC Plane) (Passing n_{HitTot} < n_{max})", 6, 0, 6, 20, 0, 20);
    SHMS_Ch1_nHits_Fail = new TH2F("SHMS_Ch1_nHits_Fail", "SHMS Ch1 nHits(DC Plane) (Failing n_{HitTot} < n_{max})", 6, 0, 6, 50, 0, 50);
    SHMS_Ch2_nHits_Pass = new TH2F("SHMS_Ch2_nHits_Pass", "SHMS Ch2 nHits(DC Plane) (Passing n_{HitTot} < n_{max})", 6, 0, 6, 20, 0, 20);
    SHMS_Ch2_nHits_Fail = new TH2F("SHMS_Ch2_nHits_Fail", "SHMS Ch2 nHits(DC Plane) (Failing n_{HitTot} < n_{max})", 6, 0, 6, 50, 0, 50);

    fOutput->Add(EventType);
    fOutput->Add(EDTM);
    fOutput->Add(HMS_EDTM);
    fOutput->Add(SHMS_EDTM);
    fOutput->Add(TRIG1);
    fOutput->Add(TRIG3);
    fOutput->Add(TRIG5);
    fOutput->Add(TRIG1_cut);
    fOutput->Add(TRIG3_cut);

    fOutput->Add(HMS_Ch1_nHits_Pass);
    fOutput->Add(HMS_Ch2_nHits_Pass);
    fOutput->Add(HMS_Ch1_nHits_Fail);
    fOutput->Add(HMS_Ch2_nHits_Fail);

    fOutput->Add(SHMS_Ch1_nHits_Pass);
    fOutput->Add(SHMS_Ch2_nHits_Pass);
    fOutput->Add(SHMS_Ch1_nHits_Fail);
    fOutput->Add(SHMS_Ch2_nHits_Fail);

}

Bool_t TrackingTest::Process(Long64_t entry)
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

    if (*T_coin_pEDTM_tdcTime!=0.0) EDTM->Fill(*T_coin_pEDTM_tdcTime);
    if (*T_coin_pTRIG1_ROC2_tdcTime!=0.0) TRIG1->Fill(*T_coin_pTRIG1_ROC2_tdcTime);
    if (*T_coin_pTRIG3_ROC2_tdcTime!=0.0) TRIG3->Fill(*T_coin_pTRIG3_ROC2_tdcTime);
    if (*T_coin_pTRIG5_ROC2_tdcTime!=0.0) TRIG5->Fill(*T_coin_pTRIG5_ROC2_tdcTime);
    EventType->Fill(*EvtType);
    if (*EvtType==1/*T_coin_pTRIG1_ROC2_tdcTime>=388.0 &&
      *T_coin_pTRIG1_ROC2_tdcTime<=395.0 && *EvtType==1 &&
      (*T_coin_pEDTM_tdcTime<140.0 || *T_coin_pEDTM_tdcTime>144.0)*/) // Event was an SHMS Single
    {
        TRIG1_cut->Fill(*T_coin_pTRIG1_ROC2_tdcTime);
        // Require a hit in each chamber plane for now! Look at each chamber seperately
        if(P_dc_1u1_nhit[0] != 0 && P_dc_1u2_nhit[0] != 0 && P_dc_1v1_nhit[0] != 0 &&  P_dc_1v2_nhit[0] != 0 && P_dc_1x1_nhit[0] != 0 && P_dc_1x2_nhit[0] != 0){
            // Fill histograms for events with acceptable # hits or too many hits separately (per plane)
            if(P_dc_Ch1_maxhits[0]>P_dc_Ch1_nhit[0]){
                SHMS_nHits_Ch1_Pass[0]->Fill(P_dc_1u1_nhit[0]);
                SHMS_nHits_Ch1_Pass[1]->Fill(P_dc_1u2_nhit[0]);
                SHMS_nHits_Ch1_Pass[2]->Fill(P_dc_1v1_nhit[0]);
                SHMS_nHits_Ch1_Pass[3]->Fill(P_dc_1v2_nhit[0]);
                SHMS_nHits_Ch1_Pass[4]->Fill(P_dc_1x1_nhit[0]);
                SHMS_nHits_Ch1_Pass[5]->Fill(P_dc_1x2_nhit[0]);
                SHMS_Ch1_nHits_Pass->Fill(0., P_dc_1u1_nhit[0]);
                SHMS_Ch1_nHits_Pass->Fill(1., P_dc_1u2_nhit[0]);
                SHMS_Ch1_nHits_Pass->Fill(2., P_dc_1v1_nhit[0]);
                SHMS_Ch1_nHits_Pass->Fill(3., P_dc_1v2_nhit[0]);
                SHMS_Ch1_nHits_Pass->Fill(4., P_dc_1x1_nhit[0]);
                SHMS_Ch1_nHits_Pass->Fill(5., P_dc_1x2_nhit[0]);
            }
            else{
                SHMS_nHits_Ch1_Fail[0]->Fill(P_dc_1u1_nhit[0]);
                SHMS_nHits_Ch1_Fail[1]->Fill(P_dc_1u2_nhit[0]);
                SHMS_nHits_Ch1_Fail[2]->Fill(P_dc_1v1_nhit[0]);
                SHMS_nHits_Ch1_Fail[3]->Fill(P_dc_1v2_nhit[0]);
                SHMS_nHits_Ch1_Fail[4]->Fill(P_dc_1x1_nhit[0]);
                SHMS_nHits_Ch1_Fail[5]->Fill(P_dc_1x2_nhit[0]);
                SHMS_Ch1_nHits_Fail->Fill(0., P_dc_1u1_nhit[0]);
                SHMS_Ch1_nHits_Fail->Fill(1., P_dc_1u2_nhit[0]);
                SHMS_Ch1_nHits_Fail->Fill(2., P_dc_1v1_nhit[0]);
                SHMS_Ch1_nHits_Fail->Fill(3., P_dc_1v2_nhit[0]);
                SHMS_Ch1_nHits_Fail->Fill(4., P_dc_1x1_nhit[0]);
                SHMS_Ch1_nHits_Fail->Fill(5., P_dc_1x2_nhit[0]);
            }
        }

        if(P_dc_2u1_nhit[0] != 0 && P_dc_2u2_nhit[0] != 0 && P_dc_2v1_nhit[0] != 0 &&  P_dc_2v2_nhit[0] != 0 && P_dc_2x1_nhit[0] != 0 && P_dc_2x2_nhit[0] != 0){
            if(P_dc_Ch2_maxhits[0]>P_dc_Ch2_nhit[0]){
                SHMS_nHits_Ch2_Pass[0]->Fill(P_dc_2u1_nhit[0]);
                SHMS_nHits_Ch2_Pass[1]->Fill(P_dc_2u2_nhit[0]);
                SHMS_nHits_Ch2_Pass[2]->Fill(P_dc_2v1_nhit[0]);
                SHMS_nHits_Ch2_Pass[3]->Fill(P_dc_2v2_nhit[0]);
                SHMS_nHits_Ch2_Pass[4]->Fill(P_dc_2x1_nhit[0]);
                SHMS_nHits_Ch2_Pass[5]->Fill(P_dc_2x2_nhit[0]);
                SHMS_Ch2_nHits_Pass->Fill(0., P_dc_2u1_nhit[0]);
                SHMS_Ch2_nHits_Pass->Fill(1., P_dc_2u2_nhit[0]);
                SHMS_Ch2_nHits_Pass->Fill(2., P_dc_2v1_nhit[0]);
                SHMS_Ch2_nHits_Pass->Fill(3., P_dc_2v2_nhit[0]);
                SHMS_Ch2_nHits_Pass->Fill(4., P_dc_2x1_nhit[0]);
                SHMS_Ch2_nHits_Pass->Fill(5., P_dc_2x2_nhit[0]);
            }
            else{
                SHMS_nHits_Ch2_Fail[0]->Fill(P_dc_2u1_nhit[0]);
                SHMS_nHits_Ch2_Fail[1]->Fill(P_dc_2u2_nhit[0]);
                SHMS_nHits_Ch2_Fail[2]->Fill(P_dc_2v1_nhit[0]);
                SHMS_nHits_Ch2_Fail[3]->Fill(P_dc_2v2_nhit[0]);
                SHMS_nHits_Ch2_Fail[4]->Fill(P_dc_2x1_nhit[0]);
                SHMS_nHits_Ch2_Fail[5]->Fill(P_dc_2x2_nhit[0]);
                SHMS_Ch2_nHits_Fail->Fill(0., P_dc_2u1_nhit[0]);
                SHMS_Ch2_nHits_Fail->Fill(1., P_dc_2u2_nhit[0]);
                SHMS_Ch2_nHits_Fail->Fill(2., P_dc_2v1_nhit[0]);
                SHMS_Ch2_nHits_Fail->Fill(3., P_dc_2v2_nhit[0]);
                SHMS_Ch2_nHits_Fail->Fill(4., P_dc_2x1_nhit[0]);
                SHMS_Ch2_nHits_Fail->Fill(5., P_dc_2x2_nhit[0]);
            }
        }

    }

    if (/* *T_coin_pTRIG3_ROC2_tdcTime>=830.0 &&
    *T_coin_pTRIG3_ROC2_tdcTime<=870.0 &&*/ *EvtType==2) // Event was an HMS Single
    {
        TRIG3_cut->Fill(*T_coin_pTRIG3_ROC2_tdcTime);
        if(H_dc_1u1_nhit[0] != 0 && H_dc_1u2_nhit[0] != 0 && H_dc_1v1_nhit[0] != 0 &&  H_dc_1v2_nhit[0] != 0 && H_dc_1x1_nhit[0] != 0 && H_dc_1x2_nhit[0] != 0){
            if(H_dc_Ch1_maxhits[0]>H_dc_Ch1_nhit[0]){
                HMS_nHits_Ch1_Pass[0]->Fill(H_dc_1u1_nhit[0]);
                HMS_nHits_Ch1_Pass[1]->Fill(H_dc_1u2_nhit[0]);
                HMS_nHits_Ch1_Pass[2]->Fill(H_dc_1v1_nhit[0]);
                HMS_nHits_Ch1_Pass[3]->Fill(H_dc_1v2_nhit[0]);
                HMS_nHits_Ch1_Pass[4]->Fill(H_dc_1x1_nhit[0]);
                HMS_nHits_Ch1_Pass[5]->Fill(H_dc_1x2_nhit[0]);
                HMS_Ch1_nHits_Pass->Fill(0., H_dc_1u1_nhit[0]);
                HMS_Ch1_nHits_Pass->Fill(1., H_dc_1u2_nhit[0]);
                HMS_Ch1_nHits_Pass->Fill(2., H_dc_1v1_nhit[0]);
                HMS_Ch1_nHits_Pass->Fill(3., H_dc_1v2_nhit[0]);
                HMS_Ch1_nHits_Pass->Fill(4., H_dc_1x1_nhit[0]);
                HMS_Ch1_nHits_Pass->Fill(5., H_dc_1x2_nhit[0]);
            }
            else{
                HMS_nHits_Ch1_Fail[0]->Fill(H_dc_1u1_nhit[0]);
                HMS_nHits_Ch1_Fail[1]->Fill(H_dc_1u2_nhit[0]);
                HMS_nHits_Ch1_Fail[2]->Fill(H_dc_1v1_nhit[0]);
                HMS_nHits_Ch1_Fail[3]->Fill(H_dc_1v2_nhit[0]);
                HMS_nHits_Ch1_Fail[4]->Fill(H_dc_1x1_nhit[0]);
                HMS_nHits_Ch1_Fail[5]->Fill(H_dc_1x2_nhit[0]);
                HMS_Ch1_nHits_Fail->Fill(0., H_dc_1u1_nhit[0]);
                HMS_Ch1_nHits_Fail->Fill(1., H_dc_1u2_nhit[0]);
                HMS_Ch1_nHits_Fail->Fill(2., H_dc_1v1_nhit[0]);
                HMS_Ch1_nHits_Fail->Fill(3., H_dc_1v2_nhit[0]);
                HMS_Ch1_nHits_Fail->Fill(4., H_dc_1x1_nhit[0]);
                HMS_Ch1_nHits_Fail->Fill(5., H_dc_1x2_nhit[0]);
            }
        }

        if(H_dc_2u1_nhit[0] != 0 && H_dc_2u2_nhit[0] != 0 && H_dc_2v1_nhit[0] != 0 &&  H_dc_2v2_nhit[0] != 0 && H_dc_2x1_nhit[0] != 0 && H_dc_2x2_nhit[0] != 0){
            if(H_dc_Ch2_maxhits[0]>H_dc_Ch2_nhit[0]){
                HMS_nHits_Ch2_Pass[0]->Fill(H_dc_2u1_nhit[0]);
                HMS_nHits_Ch2_Pass[1]->Fill(H_dc_2u2_nhit[0]);
                HMS_nHits_Ch2_Pass[2]->Fill(H_dc_2v1_nhit[0]);
                HMS_nHits_Ch2_Pass[3]->Fill(H_dc_2v2_nhit[0]);
                HMS_nHits_Ch2_Pass[4]->Fill(H_dc_2x1_nhit[0]);
                HMS_nHits_Ch2_Pass[5]->Fill(H_dc_2x2_nhit[0]);
                HMS_Ch2_nHits_Pass->Fill(0., H_dc_2u1_nhit[0]);
                HMS_Ch2_nHits_Pass->Fill(1., H_dc_2u2_nhit[0]);
                HMS_Ch2_nHits_Pass->Fill(2., H_dc_2v1_nhit[0]);
                HMS_Ch2_nHits_Pass->Fill(3., H_dc_2v2_nhit[0]);
                HMS_Ch2_nHits_Pass->Fill(4., H_dc_2x1_nhit[0]);
                HMS_Ch2_nHits_Pass->Fill(5., H_dc_2x2_nhit[0]);
            }
            else{
                HMS_nHits_Ch2_Fail[0]->Fill(H_dc_2u1_nhit[0]);
                HMS_nHits_Ch2_Fail[1]->Fill(H_dc_2u2_nhit[0]);
                HMS_nHits_Ch2_Fail[2]->Fill(H_dc_2v1_nhit[0]);
                HMS_nHits_Ch2_Fail[3]->Fill(H_dc_2v2_nhit[0]);
                HMS_nHits_Ch2_Fail[4]->Fill(H_dc_2x1_nhit[0]);
                HMS_nHits_Ch2_Fail[5]->Fill(H_dc_2x2_nhit[0]);
                HMS_Ch2_nHits_Fail->Fill(0., H_dc_2u1_nhit[0]);
                HMS_Ch2_nHits_Fail->Fill(1., H_dc_2u2_nhit[0]);
                HMS_Ch2_nHits_Fail->Fill(2., H_dc_2v1_nhit[0]);
                HMS_Ch2_nHits_Fail->Fill(3., H_dc_2v2_nhit[0]);
                HMS_Ch2_nHits_Fail->Fill(4., H_dc_2x1_nhit[0]);
                HMS_Ch2_nHits_Fail->Fill(5., H_dc_2x2_nhit[0]);
            }
        }
    }

  return kTRUE;
}

void TrackingTest::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
}

void TrackingTest::Terminate()
{
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.
    cout << "Finished processing" << endl;
    printf("\n\n");
    TString option = GetOption();


//    for(Int_t i = 0; i < 6; i++){
//        for(Int_t j = 0; j < 10; j++){
//        PeakRatio[i][j] = ->GetBinContent(2)/->GetBinContent(j+3);
//        }
//    }

    TFile *Histogram_file = new TFile(Form("../HISTOGRAMS/TrackingTest_Run%i.root",option.Atoi()),"RECREATE");
    EventType->Write();
    EDTM->Write();
    HMS_EDTM->Write();
    SHMS_EDTM->Write();
    TRIG1->Write();
    TRIG3->Write();
    TRIG5->Write();

    // To access histogram arrays have to do this slightly stupid process
    for(Int_t i = 0; i < 6; i++){ //6 planes per chamber, could actually be one array of histograms tbh
        // Sets some temp TH1F to be equal to the object grabbed from the output list
        TH1F *SHMS1 = dynamic_cast<TH1F *>(TProof::GetOutput(Form("SHMS_nHits_Ch1P%i_Pass",i+1), fOutput));
        TH1F *SHMS2 = dynamic_cast<TH1F *>(TProof::GetOutput(Form("SHMS_nHits_Ch2P%i_Pass",i+1), fOutput));
        TH1F *SHMS3 = dynamic_cast<TH1F *>(TProof::GetOutput(Form("SHMS_nHits_Ch1P%i_Fail",i+1), fOutput));
        TH1F *SHMS4 = dynamic_cast<TH1F *>(TProof::GetOutput(Form("SHMS_nHits_Ch2P%i_Fail",i+1), fOutput));
        TH1F *HMS1 = dynamic_cast<TH1F *>(TProof::GetOutput(Form("HMS_nHits_Ch1P%i_Pass", i+1), fOutput));
        TH1F *HMS2 = dynamic_cast<TH1F *>(TProof::GetOutput(Form("HMS_nHits_Ch2P%i_Pass", i+1), fOutput));
        TH1F *HMS3 = dynamic_cast<TH1F *>(TProof::GetOutput(Form("HMS_nHits_Ch1P%i_Fail", i+1), fOutput));
        TH1F *HMS4 = dynamic_cast<TH1F *>(TProof::GetOutput(Form("HMS_nHits_Ch2P%i_Fail", i+1), fOutput));
        // Calculate ratio of frequency of single hits in each chamber to other numbers of hits for nHits between 1 and 11
        // Do this for each chamber and on pass/fail condition
        // Plot this later as a graph
        for(Int_t j = 0; j < 10; j++){ //Bin 2 is nTracks = 1, 1 is 0 and bin 0 is undeflow
            SHMSCh1_Pass_PeakRatio[i][j] = SHMS1->GetBinContent(2)/SHMS1->GetBinContent(j+3);
            SHMSCh1_Fail_PeakRatio[i][j] = SHMS3->GetBinContent(2)/SHMS3->GetBinContent(j+3);
            SHMSCh2_Pass_PeakRatio[i][j] = SHMS2->GetBinContent(2)/SHMS2->GetBinContent(j+3);
            SHMSCh2_Fail_PeakRatio[i][j] = SHMS4->GetBinContent(2)/SHMS4->GetBinContent(j+3);
            HMSCh1_Pass_PeakRatio[i][j] = HMS1->GetBinContent(2)/HMS1->GetBinContent(j+3);
            HMSCh1_Fail_PeakRatio[i][j] = HMS3->GetBinContent(2)/HMS3->GetBinContent(j+3);
            HMSCh2_Pass_PeakRatio[i][j] = HMS2->GetBinContent(2)/HMS2->GetBinContent(j+3);
            HMSCh2_Fail_PeakRatio[i][j] = HMS4->GetBinContent(2)/HMS4->GetBinContent(j+3);
        }
        SHMS1->Write();
        SHMS2->Write();
        SHMS3->Write();
        SHMS4->Write();
        HMS1->Write();
        HMS2->Write();
        HMS3->Write();
        HMS4->Write();
    }

    double RatioPoints[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    for(Int_t i = 0; i < 2; i++){ //Loop over each detector
        for(Int_t j = 0; j < 2; j++){// Loop over each chamber
            for(Int_t k = 0; k < 2; k++){ // Loop over pass/fail conditions
                RatioPlotsPCh[i][j][k] = new TMultiGraph();
                for(Int_t m = 0; m < 6; m++){ //Loop over each chamber
                    if (i==0){
                        if(j==0){
                            if(k==0){
                            RatioPlots[i][j][k][m] = new TGraphErrors(10, RatioPoints, SHMSCh1_Pass_PeakRatio[m]);
                            }
                            if(k==1){
                            RatioPlots[i][j][k][m] = new TGraphErrors(10, RatioPoints, SHMSCh1_Pass_PeakRatio[m]);
                            }
                        }
                        if(j==1){
                            if(k==0){
                            RatioPlots[i][j][k][m] = new TGraphErrors(10, RatioPoints, SHMSCh2_Pass_PeakRatio[m]);
                            }
                            if(k==1){
                            RatioPlots[i][j][k][m] = new TGraphErrors(10, RatioPoints, SHMSCh2_Fail_PeakRatio[m]);
                            }
                        }
                    }
                    if (i==1){
                        if(j==0){
                            if(k==0){
                            RatioPlots[i][j][k][m] = new TGraphErrors(10, RatioPoints, HMSCh1_Pass_PeakRatio[m]);
                            }
                            if(k==1){
                            RatioPlots[i][j][k][m] = new TGraphErrors(10, RatioPoints, HMSCh1_Pass_PeakRatio[m]);
                            }
                        }
                        if(j==1){
                            if(k==0){
                            RatioPlots[i][j][k][m] = new TGraphErrors(10, RatioPoints, HMSCh2_Pass_PeakRatio[m]);
                            }
                            if(k==1){
                            RatioPlots[i][j][k][m] = new TGraphErrors(10, RatioPoints, HMSCh2_Fail_PeakRatio[m]);
                            }
                        }
                    }
                    RatioPlots[i][j][k][m]->SetMarkerColor(m+1);
                    RatioPlots[i][j][k][m]->SetMarkerStyle(4);
                    RatioPlots[i][j][k][m]->SetMarkerSize(2);
                    RatioPlotsPCh[i][j][k]->Add(RatioPlots[i][j][k][m]);
                }
                RatioPlotsPCh[i][j][k]->SetTitle("Test");
                //RatioPlotsPCh[i][j][k]->SetName("Test");
                RatioPlotsPCh[i][j][k]->Write();
                RatioPlotsPCh[i][j][k]->Draw("AP");
            }
        }
    }

    HMS_Ch1_nHits_Pass->Write();
    HMS_Ch2_nHits_Pass->Write();
    HMS_Ch1_nHits_Fail->Write();
    HMS_Ch2_nHits_Fail->Write();

    SHMS_Ch1_nHits_Pass->Write();
    SHMS_Ch2_nHits_Pass->Write();
    SHMS_Ch1_nHits_Fail->Write();
    SHMS_Ch2_nHits_Fail->Write();

    Histogram_file->Close();

}
