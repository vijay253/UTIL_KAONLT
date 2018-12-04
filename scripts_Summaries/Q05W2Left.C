#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q05W2Left(Int_t current = 0)
{

  if(current == 0) {
    cout << "Enter current for set of runs (-1 for all runs): ";
    cin >> current;
    //if( current<=0 ) return;
  }
  TChain ch("T");
  TString option = Form("%i",current);
  if(current == 24){
    /////////////////////////////////////////////////////////////////////////////////////
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6709_-1.root"); // 24 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6710_-1.root"); // 24 uA 
  }
  if(current == 35){
    ///////////////////////////////////////////////////////////////////////////////////// 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6711_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6712_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6713_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6714_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6715_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6716_-1.root"); // 35 uA 
  }
  if(current == 40){
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6723_-1.root"); // 40 uA 
  }
  if(current == 50){
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6718_-1.root"); // 50 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6719_-1.root"); // 50 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6720_-1.root"); // 50 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6721_-1.root"); // 50 uA 
  }
  if(current <= 0){
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6709_-1.root"); // 24 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6710_-1.root"); // 24 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6711_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6712_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6713_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6714_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6715_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6716_-1.root"); // 35 uA
  }
  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/home/cdaq/hallc-online/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/KaonYield_all.C+",option);
  proof->Close();
  
}
