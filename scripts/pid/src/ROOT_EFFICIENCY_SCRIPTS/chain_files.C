// Vijay Kumar, Univerity of Regina - 24/07/20
// vijay36361@gmail.com

#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
// ............. CODE TO CHAIN THE ROOT FILES................
// AUTHOR: Vijay
// Created Dated: Feb 6 2021

#include <stdio.h>

void chain_files()
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

  TChain ch("SHMS_Events_wCuts");
  TString rootfile1 = Rootpath + Form("pid_%i_%i.root", 8045, -1);
  ch.Add(rootfile1); 
  TString rootfile2 = Rootpath + Form("pid_%i_%i.root", 8045, -1);
  ch.Add(rootfile2);
  TString rootfile3 = Rootpath + Form("pid_%i_%i.root", 8045, -1);
  ch.Add(rootfile3);

  // Set name of the output root file 
  TString PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon;
  TString foutname = Rootpath+"/" + "PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilo" + ".root";   
  ch.Merge(foutname);
  
}
