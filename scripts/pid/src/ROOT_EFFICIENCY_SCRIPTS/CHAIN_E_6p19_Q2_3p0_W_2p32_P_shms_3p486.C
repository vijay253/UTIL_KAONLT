// ............. CODE TO CHAIN THE ROOT FILES................
// Vijay Kumar, UofR, Regina, Canada
// Feb 6 2021
// vijay36361@gmail.com

#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void CHAIN_E_6p19_Q2_3p0_W_2p32_P_shms_3p486()
{
  TString Hostname = gSystem->HostName();
  TString User = (gSystem->GetUserInfo())->fUser;
  TString Rootpath;

  cout<< "Please enter to process the script" <<endl;  
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  // Change or add your own paths as needed!
  if(Hostname.Contains("farm"))
    { 
      Rootpath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt/UTIL_KAONLT/scripts/pid/src/PYTHON_EFFICIENCY_SCRIPTS/OUTPUT/";  // path for the root files
    }
  else if(Hostname.Contains("qcd"))
    {
      Rootpath = "/group/c-kaonlt/USERS/"+User+"/hallc_replay_lt/ROOTfilesMKJTest";
    }
  else if (Hostname.Contains("phys.uregina.ca"))
    {
      Rootpath = "/dsk3/"+User+"/JLab/ROOTfiles/";
    }
  
  // start chaining

  TChain ch("SHMS_PION_SAMPLE");
  TString rootfile1 = Rootpath + Form("pid_%i_%i.root", 7882, -1);
  ch.Add(rootfile1); 
  TString rootfile2 = Rootpath + Form("pid_%i_%i.root", 7883, -1);
  ch.Add(rootfile2);
  TString rootfile3 = Rootpath + Form("pid_%i_%i.root", 7884, -1);
  ch.Add(rootfile3);
  TString rootfile4 = Rootpath + Form("pid_%i_%i.root", 7885, -1);
  ch.Add(rootfile4);
  TString rootfile5 = Rootpath + Form("pid_%i_%i.root", 7886, -1);
  ch.Add(rootfile5);
  TString rootfile6 = Rootpath + Form("pid_%i_%i.root", 7887, -1);
  ch.Add(rootfile6);
  //  TString rootfile7 = Rootpath + Form("pid_%i_%i.root", 7888, -1);
  //ch.Add(rootfile7);

  // Set name of the output root file 
  TString PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon;
  TString foutname = Rootpath+"/" + "PID_E_6p19_Q2_3p0_W_2p32_P_shms_3p486_low_epsilon" + ".root";   
  ch.Merge(foutname);
  
}
