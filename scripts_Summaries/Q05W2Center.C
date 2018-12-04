#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void Q05W2Center(Int_t current = 0)
{

  if(current == 0) {
    cout << "Enter current for set of runs (-1 for all runs): ";
    cin >> current;
    //if( current<=0 ) return;
  }
  TChain ch("T");
  TString option = Form("%i",current);
  if(current == 12){
      /////////////////////////////////////////////////////////////////////////////////////
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6694_-1.root"); // 12 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6695_-1.root"); // 12 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6696_-1.root"); // 12 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6697_-1.root"); // 12 uA 
  }
  if(current == 16){
    /////////////////////////////////////////////////////////////////////////////////////  
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6638_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6642_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6643_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6648_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6649_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6654_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6655_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6661_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6662_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6667_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6668_-1.root"); // 16 uA
  }
  if(current == 18){
      ////////////////////////////////////////////////////////////////////////////////////
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6684_-1.root"); // 18 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6685_-1.root"); // 18 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6687_-1.root"); // 18 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6688_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6689_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6690_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6691_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6692_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6704_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6705_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6706_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6707_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6708_-1.root"); // 18 uA 
  }
  if(current == 20){
    /////////////////////////////////////////////////////////////////////////////////////
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6674_-1.root"); // 20 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6675_-1.root"); // 20 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6676_-1.root"); // 20 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6680_-1.root"); // 20 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6681_-1.root"); // 20 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6682_-1.root"); // 20 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6683_-1.root"); // 20 uA 
  }
  if(current == 24){
    /////////////////////////////////////////////////////////////////////////////////////
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6644_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6645_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6650_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6651_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6656_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6657_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6663_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6664_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6669_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6671_-1.root"); // 24 uA
  }
  if(current == 32){
    /////////////////////////////////////////////////////////////////////////////////////
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6646_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6647_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6652_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6653_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6658_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6659_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6665_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6666_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6672_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6673_-1.root"); // 32 uA
  }
  if(current == 35){
    ///////////////////////////////////////////////////////////////////////////////////// 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6639_-1.root"); // 35 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6640_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6641_-1.root"); // 35 uA 
  }
  if(current <= 0){
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6694_-1.root"); // 12 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6695_-1.root"); // 12 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6696_-1.root"); // 12 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6697_-1.root"); // 12 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6638_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6642_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6643_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6648_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6649_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6654_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6655_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6661_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6662_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6667_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6668_-1.root"); // 16 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6684_-1.root"); // 18 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6685_-1.root"); // 18 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6687_-1.root"); // 18 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6688_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6689_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6690_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6691_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6692_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6704_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6705_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6706_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6707_-1.root"); // 18 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6708_-1.root"); // 18 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6674_-1.root"); // 20 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6675_-1.root"); // 20 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6676_-1.root"); // 20 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6680_-1.root"); // 20 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6681_-1.root"); // 20 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6682_-1.root"); // 20 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6683_-1.root"); // 20 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6644_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6645_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6650_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6651_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6656_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6657_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6663_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6664_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6669_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6671_-1.root"); // 24 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6646_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6647_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6652_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6653_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6658_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6659_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6665_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6666_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6672_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6673_-1.root"); // 32 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6639_-1.root"); // 35 uA
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6640_-1.root"); // 35 uA 
    ch.Add("/home/cdaq/hallc-online/hallc_replay/UTIL_KAONLT/ROOTfiles/KaonLT_coin_replay_production_6641_-1.root"); // 35 uA
  }
  
  TProof *proof = TProof::Open("workers=8");
  //proof->SetProgressDialog(0);  
  ch.SetProof();
  ch.Process("/home/cdaq/hallc-online/hallc_replay_kaonlt/UTIL_KAONLT/scripts_KaonYield/KaonYield_all.C+",option);
  proof->Close();
  
}
