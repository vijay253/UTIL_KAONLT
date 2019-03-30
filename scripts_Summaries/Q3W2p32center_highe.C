#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q3W2p32center_highe()
{
  TChain ch("T");
  ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4871_-1.root");
  ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4873_-1.root");
  ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4874_-1.root");
  ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4875_-1.root");
  ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4876_-1.root");
  ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4877_-1.root");
  ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4878_-1.root");
  ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4879_-1.root");

  TProof *proof = TProof::Open("workers=4");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/home/cdaq/hallc-online/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/KaonYield_allfall.C+","1");
  proof->Close();
  
}
