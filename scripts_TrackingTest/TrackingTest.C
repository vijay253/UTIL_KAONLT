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

    HMS_DCnHits = new TH1F("HMS_DCnHits", "nHits in HMS DCs", 200, 0, 200);
    HMS_DCnHitsCut = new TH1F("HMS_DCnHitsCut", "nHits in HMS DCs post ECal cut", 200, 0, 200);
    HMS_DCnTracks = new TH1F("HMS_DCnTracks", "nTracks in HMS DCs",20, 0, 20);
    HMS_DCnTracksCut = new TH1F("HMS_DCnTracksCut", "nTracks in HMS DCs post ECal cut",20, 0, 20);
    SHMS_DCnHits = new TH1F("SHMS_DCnHits", "nHits in SHMS DCs", 200, 0, 200);
    SHMS_DCnHitsCut = new TH1F("SHMS_DCnHitsCut", "nHits in SHMS DCs post ECal cut", 200, 0, 200);
    SHMS_DCnTracks = new TH1F("SHMS_DCnTracks", "nTracks in SHMS DCs",20, 0, 20);
    SHMS_DCnTracksCut = new TH1F("SHMS_DCnTracksCut", "nTracks in SHMS DCs post ECal cut",20, 0, 20);

    HMS_nHits_nTr = new TH2F("HMS_nHits_nTr", "HMS n_{Hits}(n_{Tr})", 15, 0, 15, 200, 0, 200);
    HMS_nHitsCh1_nTr = new TH2F("HMS_nHitsCh1_nTr", "HMS n_{HitsCh1}(n_{Tr})", 15, 0, 15, 100, 0, 100);
    HMS_nHitsCh2_nTr = new TH2F("HMS_nHitsCh2_nTr", "HMS n_{HitsCh2}(n_{Tr})", 15, 0, 15, 100, 0, 100);
    SHMS_nHits_nTr = new TH2F("SHMS_nHits_nTr", "SHMS n_{Hits}(n_{Tr})", 15, 0, 15, 200, 0, 200);
    SHMS_nHitsCh1_nTr = new TH2F("SHMS_nHitsCh1_nTr", "SHMS n_{HitsCh1}(n_{Tr})", 15, 0, 15, 100, 0, 100);
    SHMS_nHitsCh2_nTr = new TH2F("SHMS_nHitsCh2_nTr", "SHMS n_{HitsCh2}(n_{Tr})", 15, 0, 15, 100, 0, 100);

    //TH2F* nHits_nPlane[2][2][5];
    TString detector;
    TString histname;
    TString histtitle;

    for(Int_t i = 0; i < 2; i++){
        if(i == 0) detector = "HMS";
        if(i == 1) detector = "SHMS";
        for(Int_t j = 0; j < 2; j++){
            for(Int_t k = 0; k < 5; k++){
                histname = detector + Form("_Ch%i_nTracks_%i", j+1, k);
                histtitle = detector + Form(" Ch%i n_{Hits}(n_{Plane}) for n_{tr} = %i", j+1, k);
                nHits_nPlane[i][j][k] = new TH2F(histname, histtitle, 6, 0, 6, 50, 0, 50);
                fOutput->Add(nHits_nPlane[i][j][k]);
            }
        }
    }

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

    fOutput->Add(HMS_DCnHits);
    fOutput->Add(HMS_DCnHitsCut);
    fOutput->Add(SHMS_DCnHits);
    fOutput->Add(SHMS_DCnHitsCut);
    fOutput->Add(HMS_DCnTracks);
    fOutput->Add(HMS_DCnTracksCut);
    fOutput->Add(SHMS_DCnTracks);
    fOutput->Add(SHMS_DCnTracksCut);
    fOutput->Add(HMS_nHits_nTr);
    fOutput->Add(HMS_nHitsCh1_nTr);
    fOutput->Add(HMS_nHitsCh2_nTr);
    fOutput->Add(SHMS_nHits_nTr);
    fOutput->Add(SHMS_nHitsCh1_nTr);
    fOutput->Add(SHMS_nHitsCh2_nTr);

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
        SHMS_DCnHits->Fill(P_dc_nhit[0]);
        SHMS_DCnTracks->Fill(P_dc_ntrack[0]);
        if(P_cal_etotnorm[0] < 0.8) return kTRUE;
        SHMS_DCnHitsCut->Fill(P_dc_nhit[0]);
        SHMS_DCnTracksCut->Fill(P_dc_ntrack[0]);
        SHMS_nHits_nTr->Fill(P_dc_ntrack[0], P_dc_nhit[0]);
        SHMS_nHitsCh1_nTr->Fill(P_dc_ntrack[0],P_dc_Ch1_nhit[0]);
        SHMS_nHitsCh2_nTr->Fill(P_dc_ntrack[0],P_dc_Ch2_nhit[0]);
        Int_t nTrack = P_dc_ntrack[0];
        if(nTrack < 5){
            nHits_nPlane[1][0][nTrack]->Fill(0., P_dc_1u1_nhit[0]);
            nHits_nPlane[1][0][nTrack]->Fill(1., P_dc_1u2_nhit[0]);
            nHits_nPlane[1][0][nTrack]->Fill(2., P_dc_1v1_nhit[0]);
            nHits_nPlane[1][0][nTrack]->Fill(3., P_dc_1v2_nhit[0]);
            nHits_nPlane[1][0][nTrack]->Fill(4., P_dc_1x1_nhit[0]);
            nHits_nPlane[1][0][nTrack]->Fill(5., P_dc_1x2_nhit[0]);
            nHits_nPlane[1][1][nTrack]->Fill(0., P_dc_2u1_nhit[0]);
            nHits_nPlane[1][1][nTrack]->Fill(1., P_dc_2u2_nhit[0]);
            nHits_nPlane[1][1][nTrack]->Fill(2., P_dc_2v1_nhit[0]);
            nHits_nPlane[1][1][nTrack]->Fill(3., P_dc_2v2_nhit[0]);
            nHits_nPlane[1][1][nTrack]->Fill(4., P_dc_2x1_nhit[0]);
            nHits_nPlane[1][1][nTrack]->Fill(5., P_dc_2x2_nhit[0]);
        }
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
        HMS_DCnHits->Fill(H_dc_nhit[0]);
        HMS_DCnTracks->Fill(H_dc_ntrack[0]);
        if(H_cal_etotnorm[0] < 0.8) return kTRUE;
        HMS_DCnHitsCut->Fill(H_dc_nhit[0]);
        HMS_DCnTracksCut->Fill(H_dc_ntrack[0]);
        HMS_nHits_nTr->Fill(H_dc_ntrack[0], H_dc_nhit[0]);
        HMS_nHitsCh1_nTr->Fill(H_dc_ntrack[0],H_dc_Ch1_nhit[0]);
        HMS_nHitsCh2_nTr->Fill(H_dc_ntrack[0],H_dc_Ch2_nhit[0]);
        Int_t nTrack = H_dc_ntrack[0];
        if(nTrack < 5){
                nHits_nPlane[0][0][nTrack]->Fill(0., H_dc_1u1_nhit[0]);
                nHits_nPlane[0][0][nTrack]->Fill(1., H_dc_1u2_nhit[0]);
                nHits_nPlane[0][0][nTrack]->Fill(2., H_dc_1v1_nhit[0]);
                nHits_nPlane[0][0][nTrack]->Fill(3., H_dc_1v2_nhit[0]);
                nHits_nPlane[0][0][nTrack]->Fill(4., H_dc_1x1_nhit[0]);
                nHits_nPlane[0][0][nTrack]->Fill(5., H_dc_1x2_nhit[0]);
                nHits_nPlane[0][1][nTrack]->Fill(0., H_dc_2u1_nhit[0]);
                nHits_nPlane[0][1][nTrack]->Fill(1., H_dc_2u2_nhit[0]);
                nHits_nPlane[0][1][nTrack]->Fill(2., H_dc_2v1_nhit[0]);
                nHits_nPlane[0][1][nTrack]->Fill(3., H_dc_2v2_nhit[0]);
                nHits_nPlane[0][1][nTrack]->Fill(4., H_dc_2x1_nhit[0]);
                nHits_nPlane[0][1][nTrack]->Fill(5., H_dc_2x2_nhit[0]);
        }

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

    TDirectory *DEvent = Histogram_file->mkdir("Event Information"); DEvent->cd();
    EventType->Write();
    EDTM->Write();
    HMS_EDTM->Write();
    SHMS_EDTM->Write();
    TRIG1->Write();
    TRIG3->Write();
    TRIG5->Write();

    TDirectory *DDCInfo = Histogram_file->mkdir("DC Hit and Track Information"); DDCInfo->cd();
    HMS_DCnHits->Write();
    HMS_DCnHitsCut->Write();
    SHMS_DCnHits->Write();
    SHMS_DCnHitsCut->Write();
    HMS_DCnTracks->Write();
    HMS_DCnTracksCut->Write();
    SHMS_DCnTracks->Write();
    SHMS_DCnTracksCut->Write();

    HMS_nHits_nTr->Write();
    HMS_nHitsCh1_nTr->Write();
    HMS_nHitsCh2_nTr->Write();
    SHMS_nHits_nTr->Write();
    SHMS_nHitsCh1_nTr->Write();
    SHMS_nHitsCh2_nTr->Write();

    TDirectory *DDCChPl = Histogram_file->mkdir("DC Chamber Information by Plane"); DDCChPl->cd();
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
        SHMS1->Write();
        SHMS2->Write();
        SHMS3->Write();
        SHMS4->Write();
        HMS1->Write();
        HMS2->Write();
        HMS3->Write();
        HMS4->Write();
    }

    TDirectory *DDCCh = Histogram_file->mkdir("DC Chamber Information"); DDCCh->cd();

    HMS_Ch1_nHits_Pass->GetXaxis()->SetTitle("DC Plane");
    HMS_Ch1_nHits_Pass->GetXaxis()->CenterTitle();
    HMS_Ch1_nHits_Pass->GetYaxis()->SetTitle("nHits/Plane");
    HMS_Ch1_nHits_Pass->GetYaxis()->SetTitleOffset(0.7);
    HMS_Ch1_nHits_Pass->GetYaxis()->CenterTitle();
    HMS_Ch1_nHits_Pass->Write();

    HMS_Ch2_nHits_Pass->GetXaxis()->SetTitle("DC Plane");
    HMS_Ch2_nHits_Pass->GetXaxis()->CenterTitle();
    HMS_Ch2_nHits_Pass->GetYaxis()->SetTitle("nHits/Plane");
    HMS_Ch2_nHits_Pass->GetYaxis()->SetTitleOffset(0.7);
    HMS_Ch2_nHits_Pass->GetYaxis()->CenterTitle();
    HMS_Ch2_nHits_Pass->Write();

    HMS_Ch1_nHits_Fail->GetXaxis()->SetTitle("DC Plane");
    HMS_Ch1_nHits_Fail->GetXaxis()->CenterTitle();
    HMS_Ch1_nHits_Fail->GetYaxis()->SetTitle("nHits/Plane");
    HMS_Ch1_nHits_Fail->GetYaxis()->SetTitleOffset(0.7);
    HMS_Ch1_nHits_Fail->GetYaxis()->CenterTitle();
    HMS_Ch1_nHits_Fail->Write();

    HMS_Ch2_nHits_Fail->GetXaxis()->SetTitle("DC Plane");
    HMS_Ch2_nHits_Fail->GetXaxis()->CenterTitle();
    HMS_Ch2_nHits_Fail->GetYaxis()->SetTitle("nHits/Plane");
    HMS_Ch2_nHits_Fail->GetYaxis()->SetTitleOffset(0.7);
    HMS_Ch2_nHits_Fail->GetYaxis()->CenterTitle();
    HMS_Ch2_nHits_Fail->Write();

    SHMS_Ch1_nHits_Pass->GetXaxis()->SetTitle("DC Plane");
    SHMS_Ch1_nHits_Pass->GetXaxis()->CenterTitle();
    SHMS_Ch1_nHits_Pass->GetYaxis()->SetTitle("nHits/Plane");
    SHMS_Ch1_nHits_Pass->GetYaxis()->SetTitleOffset(0.7);
    SHMS_Ch1_nHits_Pass->GetYaxis()->CenterTitle();
    SHMS_Ch1_nHits_Pass->Write();

    SHMS_Ch2_nHits_Pass->GetXaxis()->SetTitle("DC Plane");
    SHMS_Ch2_nHits_Pass->GetXaxis()->CenterTitle();
    SHMS_Ch2_nHits_Pass->GetYaxis()->SetTitle("nHits/Plane");
    SHMS_Ch2_nHits_Pass->GetYaxis()->SetTitleOffset(0.7);
    SHMS_Ch2_nHits_Pass->GetYaxis()->CenterTitle();
    SHMS_Ch2_nHits_Pass->Write();

    SHMS_Ch1_nHits_Fail->GetXaxis()->SetTitle("DC Plane");
    SHMS_Ch1_nHits_Fail->GetXaxis()->CenterTitle();
    SHMS_Ch1_nHits_Fail->GetYaxis()->SetTitle("nHits/Plane");
    SHMS_Ch1_nHits_Fail->GetYaxis()->SetTitleOffset(0.7);
    SHMS_Ch1_nHits_Fail->GetYaxis()->CenterTitle();
    SHMS_Ch1_nHits_Fail->Write();

    SHMS_Ch2_nHits_Fail->GetXaxis()->SetTitle("DC Plane");
    SHMS_Ch2_nHits_Fail->GetXaxis()->CenterTitle();
    SHMS_Ch2_nHits_Fail->GetYaxis()->SetTitle("nHits/Plane");
    SHMS_Ch2_nHits_Fail->GetYaxis()->SetTitleOffset(0.7);
    SHMS_Ch2_nHits_Fail->GetYaxis()->CenterTitle();
    SHMS_Ch2_nHits_Fail->Write();

    TString detector;
    TString histname;

    TDirectory *DDCChTr = Histogram_file->mkdir("DC Chamber Information by nTracks"); DDCChTr->cd();
    for(Int_t i = 0; i < 2; i++){
        if(i == 0) detector = "HMS";
        if(i == 1) detector = "SHMS";
        for(Int_t j = 0; j < 2; j++){
            for(Int_t k = 0; k < 5; k++){
                histname = detector + Form("_Ch%i_nTracks_%i", j+1, k);
                TH2F* nHnP = dynamic_cast<TH2F *>(TProof::GetOutput(histname, fOutput));
                nHnP->GetXaxis()->SetTitle("DC Plane");
                nHnP->GetXaxis()->CenterTitle();
                nHnP->GetYaxis()->SetTitle("nHits/Plane");
                nHnP->GetYaxis()->SetTitleOffset(0.7);
                nHnP->GetYaxis()->CenterTitle();
                nHnP->Write();
            }
        }
    }

    Histogram_file->Close();

}
