#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>


// Just add run numbers for this setting like below then in Analysis 2 tab run 
// > ./run_chainQ5p5W3p02.sh low center
void Q5p5W3p02center_lowe()
{
  TChain ch("T");
  ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_8252_-1.root")
  ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_8253_-1.root");

  
  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/home/cdaq/hallc-online/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/KaonYield_all.C+","1");
  proof->Close();
  
}
