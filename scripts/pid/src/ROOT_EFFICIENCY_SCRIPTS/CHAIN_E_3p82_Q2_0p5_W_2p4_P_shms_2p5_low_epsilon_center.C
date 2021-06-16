// ............. CODE TO CHAIN THE ROOT FILES................
// Vijay Kumar, UofR, Regina, Canada
// Feb 6 2021
// vijay36361@gmail.com

#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

void CHAIN_E_3p82_Q2_0p5_W_2p4_P_shms_2p5_low_epsilon_center()
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
  TString rootfile1 = Rootpath + Form("pid_%i_%i.root", 6638, -1);
  ch.Add(rootfile1); 
  TString rootfile2 = Rootpath + Form("pid_%i_%i.root", 6639, -1);
  ch.Add(rootfile2);
  TString rootfile3 = Rootpath + Form("pid_%i_%i.root", 6640, -1);
  ch.Add(rootfile3);
  TString rootfile4 = Rootpath + Form("pid_%i_%i.root", 6641, -1);
  ch.Add(rootfile4);
  TString rootfile5 = Rootpath + Form("pid_%i_%i.root", 6642, -1);
  ch.Add(rootfile5);
  TString rootfile6 = Rootpath + Form("pid_%i_%i.root", 6643, -1);
  ch.Add(rootfile6);
  TString rootfile7 = Rootpath + Form("pid_%i_%i.root", 6644, -1);
  ch.Add(rootfile7);
  TString rootfile8 = Rootpath + Form("pid_%i_%i.root", 6645, -1);
  ch.Add(rootfile8);
  TString rootfile9 = Rootpath + Form("pid_%i_%i.root", 6646, -1);
  ch.Add(rootfile9);
  TString rootfile10 = Rootpath + Form("pid_%i_%i.root", 6647, -1);
  ch.Add(rootfile10);
  TString rootfile11 = Rootpath + Form("pid_%i_%i.root", 6648, -1);
  ch.Add(rootfile11);
  TString rootfile12 = Rootpath + Form("pid_%i_%i.root", 6649, -1);
  ch.Add(rootfile12);
  TString rootfile13 = Rootpath + Form("pid_%i_%i.root", 6650, -1);
  ch.Add(rootfile13);
  TString rootfile14 = Rootpath + Form("pid_%i_%i.root", 6651, -1);
  ch.Add(rootfile14);
  TString rootfile15 = Rootpath + Form("pid_%i_%i.root", 6652, -1);
  ch.Add(rootfile15);
  TString rootfile16 = Rootpath + Form("pid_%i_%i.root", 6653, -1);
  ch.Add(rootfile16);
  TString rootfile17 = Rootpath + Form("pid_%i_%i.root", 6654, -1);
  ch.Add(rootfile17);
  TString rootfile18 = Rootpath + Form("pid_%i_%i.root", 6655, -1);
  ch.Add(rootfile18);
  TString rootfile19 = Rootpath + Form("pid_%i_%i.root", 6656, -1);
  ch.Add(rootfile19);
  TString rootfile20 = Rootpath + Form("pid_%i_%i.root", 6657, -1);
  ch.Add(rootfile20);
  TString rootfile21 = Rootpath + Form("pid_%i_%i.root", 6658, -1);
  ch.Add(rootfile21);
  TString rootfile22 = Rootpath + Form("pid_%i_%i.root", 6659, -1);
  ch.Add(rootfile22);
  TString rootfile23 = Rootpath + Form("pid_%i_%i.root", 6661, -1);
  ch.Add(rootfile23);
  TString rootfile24 = Rootpath + Form("pid_%i_%i.root", 6662, -1);
  ch.Add(rootfile24);
  TString rootfile25 = Rootpath + Form("pid_%i_%i.root", 6663, -1);
  ch.Add(rootfile25);
  TString rootfile26 = Rootpath + Form("pid_%i_%i.root", 6664, -1);
  ch.Add(rootfile26);
  TString rootfile27 = Rootpath + Form("pid_%i_%i.root", 6665, -1);
  ch.Add(rootfile27);
  TString rootfile28 = Rootpath + Form("pid_%i_%i.root", 6666, -1);
  ch.Add(rootfile28);
  TString rootfile29 = Rootpath + Form("pid_%i_%i.root", 6667, -1);
  ch.Add(rootfile29);
  TString rootfile30 = Rootpath + Form("pid_%i_%i.root", 6668, -1);
  ch.Add(rootfile30);
  TString rootfile31 = Rootpath + Form("pid_%i_%i.root", 6669, -1);
  ch.Add(rootfile31);
  TString rootfile32 = Rootpath + Form("pid_%i_%i.root", 6671, -1);
  ch.Add(rootfile32);
  TString rootfile33 = Rootpath + Form("pid_%i_%i.root", 6672, -1);
  ch.Add(rootfile33);
  TString rootfile34 = Rootpath + Form("pid_%i_%i.root", 6673, -1);
  ch.Add(rootfile34);
  TString rootfile35 = Rootpath + Form("pid_%i_%i.root", 6674, -1);
  ch.Add(rootfile35);
  TString rootfile36 = Rootpath + Form("pid_%i_%i.root", 6675, -1);
  ch.Add(rootfile36);
  TString rootfile37 = Rootpath + Form("pid_%i_%i.root", 6676, -1);
  ch.Add(rootfile37);
  TString rootfile38 = Rootpath + Form("pid_%i_%i.root", 6680, -1);
  ch.Add(rootfile38);
  TString rootfile39 = Rootpath + Form("pid_%i_%i.root", 6681, -1);
  ch.Add(rootfile39);
  TString rootfile40 = Rootpath + Form("pid_%i_%i.root", 6682, -1);
  ch.Add(rootfile40);
  TString rootfile41 = Rootpath + Form("pid_%i_%i.root", 6683, -1);
  ch.Add(rootfile41);
  TString rootfile42 = Rootpath + Form("pid_%i_%i.root", 6684, -1);
  ch.Add(rootfile42);
  TString rootfile43 = Rootpath + Form("pid_%i_%i.root", 6685, -1);
  ch.Add(rootfile43);
  TString rootfile44 = Rootpath + Form("pid_%i_%i.root", 6687, -1);
  ch.Add(rootfile44);
  TString rootfile45 = Rootpath + Form("pid_%i_%i.root", 6688, -1);
  ch.Add(rootfile45);
  TString rootfile46 = Rootpath + Form("pid_%i_%i.root", 6689, -1);
  ch.Add(rootfile46);
  TString rootfile47 = Rootpath + Form("pid_%i_%i.root", 6690, -1);
  ch.Add(rootfile47);
  TString rootfile48 = Rootpath + Form("pid_%i_%i.root", 6691, -1);
  ch.Add(rootfile48);
  TString rootfile49 = Rootpath + Form("pid_%i_%i.root", 6692, -1);
  ch.Add(rootfile49);
  TString rootfile50 = Rootpath + Form("pid_%i_%i.root", 6694, -1);
  ch.Add(rootfile50);
  TString rootfile51 = Rootpath + Form("pid_%i_%i.root", 6695, -1);
  ch.Add(rootfile51);
  TString rootfile52 = Rootpath + Form("pid_%i_%i.root", 6696, -1);
  ch.Add(rootfile52);
  TString rootfile53 = Rootpath + Form("pid_%i_%i.root", 6697, -1);
  ch.Add(rootfile53);
  TString rootfile54 = Rootpath + Form("pid_%i_%i.root", 6704, -1);
  ch.Add(rootfile54);
  TString rootfile55 = Rootpath + Form("pid_%i_%i.root", 6705, -1);
  ch.Add(rootfile55);
  TString rootfile56 = Rootpath + Form("pid_%i_%i.root", 6706, -1);
  ch.Add(rootfile56);
  TString rootfile57 = Rootpath + Form("pid_%i_%i.root", 6707, -1);
  ch.Add(rootfile57);
  TString rootfile58 = Rootpath + Form("pid_%i_%i.root", 6708, -1);
  ch.Add(rootfile58);

  // Set name of the output root file 
  TString PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon;
  TString foutname = Rootpath+"/" + "PID_E_3p82_Q2_0p5_W_2p4_P_shms_2p5_low_epsilon_center" + ".root";   
  ch.Merge(foutname);
  
}
