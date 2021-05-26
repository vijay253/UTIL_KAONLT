// ............. CODE TO CHAIN THE ROOT FILES................
// Vijay Kumar, UofR, Regina, Canada
// Feb 6 2021
// vijay36361@gmail.com

#include <TProof.h>
#include <iostream>
#include <fstream>
#include <string>
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

  TChain ch("SHMS_PION_SAMPLE");
  TString rootfile1 = Rootpath + Form("pid_%i_%i.root", 8039, -1);
  ch.Add(rootfile1); 
  TString rootfile2 = Rootpath + Form("pid_%i_%i.root", 8040, -1);
  ch.Add(rootfile2);
  TString rootfile3 = Rootpath + Form("pid_%i_%i.root", 8041, -1);
  ch.Add(rootfile3);
  TString rootfile4 = Rootpath + Form("pid_%i_%i.root", 8042, -1);
  ch.Add(rootfile4);
  TString rootfile5 = Rootpath + Form("pid_%i_%i.root", 8044, -1);
  ch.Add(rootfile5);
  TString rootfile6 = Rootpath + Form("pid_%i_%i.root", 8045, -1);
  ch.Add(rootfile6);
  TString rootfile7 = Rootpath + Form("pid_%i_%i.root", 8046, -1);
  ch.Add(rootfile7);
  TString rootfile8 = Rootpath + Form("pid_%i_%i.root", 8047, -1);
  ch.Add(rootfile8);
  TString rootfile9 = Rootpath + Form("pid_%i_%i.root", 8048, -1);
  ch.Add(rootfile9);
  TString rootfile10 = Rootpath + Form("pid_%i_%i.root", 8050, -1);
  ch.Add(rootfile10);
  TString rootfile11 = Rootpath + Form("pid_%i_%i.root", 8051, -1);
  ch.Add(rootfile11);
  TString rootfile12 = Rootpath + Form("pid_%i_%i.root", 8052, -1);
  ch.Add(rootfile12);
  TString rootfile13 = Rootpath + Form("pid_%i_%i.root", 8053, -1);
  ch.Add(rootfile13);
  TString rootfile14 = Rootpath + Form("pid_%i_%i.root", 8055, -1);
  ch.Add(rootfile14);
  TString rootfile15 = Rootpath + Form("pid_%i_%i.root", 8056, -1);
  ch.Add(rootfile15);
  TString rootfile16 = Rootpath + Form("pid_%i_%i.root", 8057, -1);
  ch.Add(rootfile16);
  TString rootfile17 = Rootpath + Form("pid_%i_%i.root", 8058, -1);
  ch.Add(rootfile17);
  TString rootfile18 = Rootpath + Form("pid_%i_%i.root", 8059, -1);
  ch.Add(rootfile18);
  TString rootfile19 = Rootpath + Form("pid_%i_%i.root", 8060, -1);
  ch.Add(rootfile19);

  TString rootfile20 = Rootpath + Form("pid_%i_%i.root", 8061, -1);
  ch.Add(rootfile20);
  TString rootfile21 = Rootpath + Form("pid_%i_%i.root", 8063, -1);
  ch.Add(rootfile21);
  TString rootfile22 = Rootpath + Form("pid_%i_%i.root", 8064, -1);
  ch.Add(rootfile22);
  TString rootfile23 = Rootpath + Form("pid_%i_%i.root", 8065, -1);
  ch.Add(rootfile23);
  TString rootfile24 = Rootpath + Form("pid_%i_%i.root", 8067, -1);
  ch.Add(rootfile24);
  TString rootfile25 = Rootpath + Form("pid_%i_%i.root", 8068, -1);
  ch.Add(rootfile25);
  TString rootfile26 = Rootpath + Form("pid_%i_%i.root", 8069, -1);
  ch.Add(rootfile26);
  TString rootfile27 = Rootpath + Form("pid_%i_%i.root", 8070, -1);
  ch.Add(rootfile27);

  TString rootfile28 = Rootpath + Form("pid_%i_%i.root", 8071, -1);
  ch.Add(rootfile28);
  TString rootfile29 = Rootpath + Form("pid_%i_%i.root", 8073, -1);
  ch.Add(rootfile29);
  TString rootfile30 = Rootpath + Form("pid_%i_%i.root", 8074, -1);
  ch.Add(rootfile30);
  TString rootfile31 = Rootpath + Form("pid_%i_%i.root", 8075, -1);
  ch.Add(rootfile31);
  TString rootfile32 = Rootpath + Form("pid_%i_%i.root", 8076, -1);
  ch.Add(rootfile32);
  TString rootfile33 = Rootpath + Form("pid_%i_%i.root", 8077, -1);
  ch.Add(rootfile33);
  TString rootfile34 = Rootpath + Form("pid_%i_%i.root", 8078, -1);
  ch.Add(rootfile34);
  TString rootfile35 = Rootpath + Form("pid_%i_%i.root", 8079, -1);
  ch.Add(rootfile35);
  TString rootfile36 = Rootpath + Form("pid_%i_%i.root", 8080, -1);
  ch.Add(rootfile36);

  TString rootfile37 = Rootpath + Form("pid_%i_%i.root", 8081, -1);
  ch.Add(rootfile37);
  TString rootfile38 = Rootpath + Form("pid_%i_%i.root", 8082, -1);
  ch.Add(rootfile38);
  TString rootfile39 = Rootpath + Form("pid_%i_%i.root", 8083, -1);
  ch.Add(rootfile39);
  TString rootfile40 = Rootpath + Form("pid_%i_%i.root", 8084, -1);
  ch.Add(rootfile40);
  TString rootfile41 = Rootpath + Form("pid_%i_%i.root", 8088, -1);
  ch.Add(rootfile41);
  TString rootfile42 = Rootpath + Form("pid_%i_%i.root", 8089, -1);
  ch.Add(rootfile42);
  TString rootfile43 = Rootpath + Form("pid_%i_%i.root", 8090, -1);
  ch.Add(rootfile43);

  TString rootfile44 = Rootpath + Form("pid_%i_%i.root", 8091, -1);
  ch.Add(rootfile44);
  TString rootfile45 = Rootpath + Form("pid_%i_%i.root", 8092, -1);
  ch.Add(rootfile45);
  TString rootfile46 = Rootpath + Form("pid_%i_%i.root", 8093, -1);
  ch.Add(rootfile46);
  TString rootfile47 = Rootpath + Form("pid_%i_%i.root", 8094, -1);
  ch.Add(rootfile47);
  TString rootfile48 = Rootpath + Form("pid_%i_%i.root", 8095, -1);
  ch.Add(rootfile48);
  TString rootfile49 = Rootpath + Form("pid_%i_%i.root", 8096, -1);
  ch.Add(rootfile49);
  TString rootfile50 = Rootpath + Form("pid_%i_%i.root", 8097, -1);
  ch.Add(rootfile50);
  TString rootfile51 = Rootpath + Form("pid_%i_%i.root", 8098, -1);
  ch.Add(rootfile51);
  TString rootfile52 = Rootpath + Form("pid_%i_%i.root", 8099, -1);
  ch.Add(rootfile52);
  TString rootfile53 = Rootpath + Form("pid_%i_%i.root", 8100, -1);
  ch.Add(rootfile53);

  TString rootfile54 = Rootpath + Form("pid_%i_%i.root", 8101, -1);
  ch.Add(rootfile54);
  TString rootfile55 = Rootpath + Form("pid_%i_%i.root", 8102, -1);
  ch.Add(rootfile55);
  TString rootfile56 = Rootpath + Form("pid_%i_%i.root", 8103, -1);
  ch.Add(rootfile56);
  TString rootfile57 = Rootpath + Form("pid_%i_%i.root", 8104, -1);
  ch.Add(rootfile57);
  TString rootfile58 = Rootpath + Form("pid_%i_%i.root", 8105, -1);
  ch.Add(rootfile58);
  TString rootfile59 = Rootpath + Form("pid_%i_%i.root", 8106, -1);
  ch.Add(rootfile59);
  TString rootfile60 = Rootpath + Form("pid_%i_%i.root", 8107, -1);
  ch.Add(rootfile60);
  TString rootfile61 = Rootpath + Form("pid_%i_%i.root", 8108, -1);
  ch.Add(rootfile61);
  TString rootfile62 = Rootpath + Form("pid_%i_%i.root", 8109, -1);
  ch.Add(rootfile62);
  TString rootfile63 = Rootpath + Form("pid_%i_%i.root", 8110, -1);
  ch.Add(rootfile63);

  // Set name of the output root file 
  TString PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon;
  TString foutname = Rootpath+"/" + "PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon" + ".root";   
  ch.Merge(foutname);
  
}
