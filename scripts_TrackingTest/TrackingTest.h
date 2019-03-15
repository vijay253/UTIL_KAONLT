#ifndef TrackingTest_h
#define TrackingTest_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>

// Headers needed by this particular selector

class TrackingTest : public TSelector {
 public :
    TTreeReader     fReader;  //!the tree reader
    TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

    Bool_t          fFullShow = kFALSE;

    Double_t        PS1;
    Double_t        PS3;

    TH1F           *EventType;
    TH1F           *EDTM;
    TH1F           *HMS_EDTM;
    TH1F           *SHMS_EDTM;
    TH1F           *TRIG1;
    TH1F           *TRIG3;
    TH1F           *TRIG5;
    TH1F           *TRIG1_cut;
    TH1F           *TRIG3_cut;
    TH1F           *HMS_DCnHits;
    TH1F           *HMS_DCnHitsCut;
    TH1F           *SHMS_DCnHits;
    TH1F           *SHMS_DCnHitsCut;
    TH1F           *HMS_DCnTracks;
    TH1F           *HMS_DCnTracksCut;
    TH1F           *SHMS_DCnTracks;
    TH1F           *SHMS_DCnTracksCut;

    TH2F           *HMS_nHits_nTr;
    TH2F           *HMS_nHitsCh1_nTr;
    TH2F           *HMS_nHitsCh2_nTr;
    TH2F           *SHMS_nHits_nTr;
    TH2F           *SHMS_nHitsCh1_nTr;
    TH2F           *SHMS_nHitsCh2_nTr;
    TH2F           *nHits_nPlane[2][2][5];

    TH1F           **SHMS_nHits_Ch1_Pass;
    TH1F           **SHMS_nHits_Ch2_Pass;
    TH1F           **SHMS_nHits_Ch1_Fail;
    TH1F           **SHMS_nHits_Ch2_Fail;

    TH1F           **HMS_nHits_Ch1_Pass;
    TH1F           **HMS_nHits_Ch2_Pass;
    TH1F           **HMS_nHits_Ch1_Fail;
    TH1F           **HMS_nHits_Ch2_Fail;

    TH2F           *HMS_Ch1_nHits_Pass;
    TH2F           *HMS_Ch1_nHits_Fail;
    TH2F           *HMS_Ch2_nHits_Pass;
    TH2F           *HMS_Ch2_nHits_Fail;

    TH2F           *SHMS_Ch1_nHits_Pass;
    TH2F           *SHMS_Ch1_nHits_Fail;
    TH2F           *SHMS_Ch2_nHits_Pass;
    TH2F           *SHMS_Ch2_nHits_Fail;

    // Readers to access the data (delete the ones you do not need).

    // Could this be done in a nicer way for our dc planes?
    TTreeReaderArray<Double_t> H_cal_etotnorm          = {fReader, "H.cal.etotnorm"};
    TTreeReaderArray<Double_t> H_cer_npeSum            = {fReader, "H.cer.npeSum"};
    TTreeReaderArray<Double_t> H_gtr_dp                = {fReader, "H.gtr.dp"};
    TTreeReaderArray<Double_t> H_dc_ntrack             = {fReader, "H.dc.ntrack"};
    TTreeReaderArray<Double_t> H_dc_nhit               = {fReader, "H.dc.nhit"};
    TTreeReaderArray<Double_t> H_dc_1u1_nhit           = {fReader, "H.dc.1u1.nhit"};
    TTreeReaderArray<Double_t> H_dc_1u2_nhit           = {fReader, "H.dc.1u2.nhit"};
    TTreeReaderArray<Double_t> H_dc_1v1_nhit           = {fReader, "H.dc.1v1.nhit"};
    TTreeReaderArray<Double_t> H_dc_1v2_nhit           = {fReader, "H.dc.1v2.nhit"};
    TTreeReaderArray<Double_t> H_dc_1x1_nhit           = {fReader, "H.dc.1x1.nhit"};
    TTreeReaderArray<Double_t> H_dc_1x2_nhit           = {fReader, "H.dc.1x2.nhit"};
    TTreeReaderArray<Double_t> H_dc_2u1_nhit           = {fReader, "H.dc.2u1.nhit"};
    TTreeReaderArray<Double_t> H_dc_2u2_nhit           = {fReader, "H.dc.2u2.nhit"};
    TTreeReaderArray<Double_t> H_dc_2v1_nhit           = {fReader, "H.dc.2v1.nhit"};
    TTreeReaderArray<Double_t> H_dc_2v2_nhit           = {fReader, "H.dc.2v2.nhit"};
    TTreeReaderArray<Double_t> H_dc_2x1_nhit           = {fReader, "H.dc.2x1.nhit"};
    TTreeReaderArray<Double_t> H_dc_2x2_nhit           = {fReader, "H.dc.2x2.nhit"};
    TTreeReaderArray<Double_t> H_dc_Ch1_nhit           = {fReader, "H.dc.Ch1.nhit"};
    TTreeReaderArray<Double_t> H_dc_Ch2_nhit           = {fReader, "H.dc.Ch2.nhit"};
    TTreeReaderArray<Double_t> H_dc_Ch1_maxhits        = {fReader, "H.dc.Ch1.maxhits"};
    TTreeReaderArray<Double_t> H_dc_Ch2_maxhits        = {fReader, "H.dc.Ch2.maxhits"};

    TTreeReaderArray<Double_t> P_cal_etotnorm          = {fReader, "P.cal.etotnorm"};
    TTreeReaderArray<Double_t> P_hgcer_npeSum          = {fReader, "P.hgcer.npeSum"};
    TTreeReaderArray<Double_t> P_aero_npeSum           = {fReader, "P.aero.npeSum"};
    TTreeReaderArray<Double_t> P_gtr_dp                = {fReader, "P.gtr.dp"};
    TTreeReaderArray<Double_t> P_dc_ntrack             = {fReader, "P.dc.ntrack"};
    TTreeReaderArray<Double_t> P_dc_nhit               = {fReader, "P.dc.nhit"};
    TTreeReaderArray<Double_t> P_dc_1u1_nhit           = {fReader, "P.dc.1u1.nhit"};
    TTreeReaderArray<Double_t> P_dc_1u2_nhit           = {fReader, "P.dc.1u2.nhit"};
    TTreeReaderArray<Double_t> P_dc_1v1_nhit           = {fReader, "P.dc.1v1.nhit"};
    TTreeReaderArray<Double_t> P_dc_1v2_nhit           = {fReader, "P.dc.1v2.nhit"};
    TTreeReaderArray<Double_t> P_dc_1x1_nhit           = {fReader, "P.dc.1x1.nhit"};
    TTreeReaderArray<Double_t> P_dc_1x2_nhit           = {fReader, "P.dc.1x2.nhit"};
    TTreeReaderArray<Double_t> P_dc_2u1_nhit           = {fReader, "P.dc.2u1.nhit"};
    TTreeReaderArray<Double_t> P_dc_2u2_nhit           = {fReader, "P.dc.2u2.nhit"};
    TTreeReaderArray<Double_t> P_dc_2v1_nhit           = {fReader, "P.dc.2v1.nhit"};
    TTreeReaderArray<Double_t> P_dc_2v2_nhit           = {fReader, "P.dc.2v2.nhit"};
    TTreeReaderArray<Double_t> P_dc_2x1_nhit           = {fReader, "P.dc.2x1.nhit"};
    TTreeReaderArray<Double_t> P_dc_2x2_nhit           = {fReader, "P.dc.2x2.nhit"};
    TTreeReaderArray<Double_t> P_dc_Ch1_nhit           = {fReader, "P.dc.Ch1.nhit"};
    TTreeReaderArray<Double_t> P_dc_Ch2_nhit           = {fReader, "P.dc.Ch2.nhit"};
    TTreeReaderArray<Double_t> P_dc_Ch1_maxhits        = {fReader, "P.dc.Ch1.maxhits"};
    TTreeReaderArray<Double_t> P_dc_Ch2_maxhits        = {fReader, "P.dc.Ch2.maxhits"};

    TTreeReaderValue<Double_t> T_coin_pTRIG1_ROC1_tdcTime   = {fReader, "T.coin.pTRIG1_ROC1_tdcTime"};
    TTreeReaderValue<Double_t> T_coin_pTRIG3_ROC1_tdcTime   = {fReader, "T.coin.pTRIG3_ROC1_tdcTime"};
    TTreeReaderValue<Double_t> T_coin_pTRIG5_ROC1_tdcTime   = {fReader, "T.coin.pTRIG5_ROC1_tdcTime"};
    TTreeReaderValue<Double_t> T_coin_pTRIG1_ROC2_tdcTime   = {fReader, "T.coin.pTRIG1_ROC2_tdcTime"};
    TTreeReaderValue<Double_t> T_coin_pTRIG3_ROC2_tdcTime   = {fReader, "T.coin.pTRIG3_ROC2_tdcTime"};
    TTreeReaderValue<Double_t> T_coin_pTRIG5_ROC2_tdcTime   = {fReader, "T.coin.pTRIG5_ROC2_tdcTime"};
    TTreeReaderValue<Double_t> T_coin_pEDTM_tdcTime         = {fReader, "T.coin.pEDTM_tdcTime"};

    TTreeReaderValue<Int_t> EvtType                    = {fReader, "fEvtHdr.fEvtType"};

    TrackingTest(TTree * /*tree*/ =0 ) {HMS_EDTM = 0, SHMS_EDTM =0, TRIG1_cut = 0, TRIG3_cut = 0, EventType=0, EDTM=0,TRIG1=0,TRIG3=0,TRIG5=0,SHMS_Ch1_nHits_Pass =0, SHMS_Ch1_nHits_Fail = 0, SHMS_Ch2_nHits_Pass =0, SHMS_Ch2_nHits_Fail = 0, HMS_Ch1_nHits_Pass = 0, HMS_Ch1_nHits_Fail = 0, HMS_Ch2_nHits_Pass =0, HMS_Ch2_nHits_Fail = 0;}
    virtual ~TrackingTest() { }
    virtual Int_t   Version() const { return 2; }
    virtual void    Begin(TTree *tree);
    virtual void    SlaveBegin(TTree *tree);
    virtual void    Init(TTree *tree);
    virtual Bool_t  Notify();
    virtual Bool_t  Process(Long64_t entry);
    virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
    virtual void    SetOption(const char *option) { fOption = option; }
    virtual void    SetObject(TObject *obj) { fObject = obj; }
    virtual void    SetInputList(TList *input) { fInput = input; }
    virtual TList  *GetOutputList() const { return fOutput; }
    virtual void    SlaveTerminate();
    virtual void    Terminate();

    ClassDef(TrackingTest,0);

};

#endif

#ifdef TrackingTest_cxx
void TrackingTest::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the reader is initialized.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  fReader.SetTree(tree);
}

Bool_t TrackingTest::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}


#endif // #ifdef TrackingTest_cxx
