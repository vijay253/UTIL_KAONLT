#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q3W2Right()
{
  TChain ch("T");
  ch.Add("/group/c-kaonlt/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4865_-1.root");
  ch.Add("/group/c-kaonlt/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4866_-1.root");
  ch.Add("/group/c-kaonlt/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4867_-1.root");
  ch.Add("/group/c-kaonlt/hallc_replay_lt/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_4868_-1.root");

  TProof *proof = TProof::Open("workers=4");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/group/c-kaonlt/hallc_replay_lt/UTIL_KAONLT/scripts_KaonYield/KaonYield_Q3W2.C+","1");
  proof->Close();
  
}
