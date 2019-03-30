#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q5p5W3p02center_lowe()
{
  TChain ch("T");

  
  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/home/cdaq/hallc-online/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/KaonYield_all.C+","1");
  proof->Close();
  
}
