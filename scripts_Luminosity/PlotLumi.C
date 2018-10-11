#include <iostream>

void PlotLumi()
{
  //Define structure for input                                                                        
  struct input_t                                                                                      
  {                                                                                                   
    Int_t   run_num;                                                                                    
    Float_t HMS_EVENTS;
    Float_t HMS_EVENTSun;
    Float_t SHMS_EVENTS;
    Float_t SHMS_EVENTSun;
    Float_t HMS_track;                                                                                    
    Float_t HMS_trackun;
    Float_t HMS_etrack;                                                                                    
    Float_t HMS_etrackun;
    Float_t SHMS_track;                                                                                    
    Float_t SHMS_trackun;
    Float_t SHMS_hadtrack;                                                                                    
    Float_t SHMS_hadtrackun;
    Float_t SHMS_pitrack;                                                                                    
    Float_t SHMS_pitrackun;
    Float_t SHMS_Ktrack;                                                                                    
    Float_t SHMS_Ktrackun;
    Float_t SHMS_ptrack;                                                                                    
    Float_t SHMS_ptrackun;
    Float_t ACC_EDTM;
    Float_t TIME;
    Float_t BCM4B;
    Float_t PS1;
    Float_t PS3;
    Float_t comp_time;                                                                                
    Float_t comp_uncer;                                                                               
    Float_t HMS_elec;                                                                                
    Float_t HMS_elecun;                                                                               
    Float_t SHMS_elec;                                                                                
    Float_t SHMS_elecun;
    Float_t SENT_EDTM;
  };                                                                                                  
                                                                                                        
  input_t input;                                                                                      
                                                                                                                                                                              
  //Read Yield Data                                                                                   
  FILE *fp = fopen("Yield_Data.dat","r");                                
  char line[400];                                                                                     
                                                                                                       
  // Create TGraph for data                                                                           
  TGraphErrors *HMS_Current_Old = new TGraphErrors();                                                            
  HMS_Current_Old->SetTitle("HMS Normalized Yield NOT Using EDTM");  

  TGraphErrors *HMS_Current_EDTM = new TGraphErrors();                                                            
  HMS_Current_EDTM->SetTitle("HMS Normalized Yield Using EDTM"); 

  TGraphErrors *SHMS_Current_Old = new TGraphErrors();                                                            
  SHMS_Current_Old->SetTitle("SHMS Normalized Yield NOT Using EDTM");  

  TGraphErrors *SHMS_Current_EDTM = new TGraphErrors();                                                            
  SHMS_Current_EDTM->SetTitle("SHMS Normalized Yield Using EDTM"); 

  TGraphErrors *HMS_Rate_Old = new TGraphErrors();                                                            
  HMS_Rate_Old->SetTitle("HMS Normalized Yield NOT Using EDTM");  

  TGraphErrors *HMS_Rate_EDTM = new TGraphErrors();                                                            
  HMS_Rate_EDTM->SetTitle("HMS Normalized Yield Using EDTM"); 

  TGraphErrors *SHMS_Rate_Old = new TGraphErrors();                                                            
  SHMS_Rate_Old->SetTitle("SHMS Normalized Yield NOT Using EDTM");  

  TGraphErrors *SHMS_Rate_EDTM = new TGraphErrors();                                                            
  SHMS_Rate_EDTM->SetTitle("SHMS Normalized Yield Using EDTM"); 


  // Fill graph from .dat file                                                                        
 
  while (fgets(&line[0],500,fp)) {
    if (line[0] == '#')
      {
	continue;
      }
    else
      {                                                                                             
	sscanf(&line[0],"%d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
	       &input.run_num,
	       &input.HMS_EVENTS,
	       &input.HMS_EVENTSun,
	       &input.SHMS_EVENTS,
	       &input.SHMS_EVENTSun,
	       &input.HMS_track,
	       &input.HMS_trackun,
	       &input.HMS_etrack,
	       &input.HMS_etrackun,
	       &input.SHMS_track,
	       &input.SHMS_trackun,
	       &input.SHMS_hadtrack,
	       &input.SHMS_hadtrackun,
	       &input.SHMS_pitrack,
	       &input.SHMS_pitrackun,
	       &input.SHMS_Ktrack,
	       &input.SHMS_Ktrackun,
	       &input.SHMS_ptrack,
	       &input.SHMS_ptrackun,
	       &input.ACC_EDTM,
	       &input.TIME,
	       &input.BCM4B,
	       &input.PS1,
	       &input.PS3,
	       &input.comp_time,
	       &input.comp_uncer,
	       &input.HMS_elec,
	       &input.HMS_elecun,
	       &input.SHMS_elec,
	       &input.SHMS_elecun,
	       &input.SENT_EDTM);   
	//cout << (input.BCM4B / input.TIME) << "   " << input.HMS_EVENTS << "   " << (input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.HMS_etrack) << endl;
	HMS_Current_Old->SetPoint(HMS_Current_Old->GetN(),(input.BCM4B / input.TIME),input.HMS_EVENTS/(input.BCM4B*input.comp_time*input.HMS_elec*input.HMS_etrack)); 
	HMS_Current_Old->SetPointError(HMS_Current_Old->GetN()-1,0.0,(input.HMS_EVENTS/(input.BCM4B*input.comp_time*input.HMS_elec*input.HMS_etrack)) * sqrt(pow(input.HMS_EVENTSun/input.HMS_EVENTS,2)+pow(input.comp_uncer/input.comp_time,2) + pow(input.HMS_elecun/input.HMS_elec,2) + pow(input.HMS_etrackun/input.HMS_etrack,2))); 

	HMS_Current_EDTM->SetPoint(HMS_Current_EDTM->GetN(),(input.BCM4B / input.TIME),input.HMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.HMS_etrack)); 
	HMS_Current_EDTM->SetPointError(HMS_Current_EDTM->GetN()-1,0.0,(input.HMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.HMS_etrack)) * sqrt(pow(input.HMS_EVENTSun/input.HMS_EVENTS,2)+(1.0/input.ACC_EDTM) + (1.0/input.SENT_EDTM) + pow(input.HMS_etrackun/input.HMS_etrack,2))); 

	SHMS_Current_Old->SetPoint(SHMS_Current_Old->GetN(),(input.BCM4B / input.TIME),input.SHMS_EVENTS/(input.BCM4B*input.comp_time*input.SHMS_elec*input.SHMS_hadtrack)); 
	SHMS_Current_Old->SetPointError(SHMS_Current_Old->GetN()-1,0.0,(input.SHMS_EVENTS/(input.BCM4B*input.comp_time*input.SHMS_elec*input.SHMS_hadtrack)) * sqrt(pow(input.SHMS_EVENTSun/input.SHMS_EVENTS,2)+pow(input.comp_uncer/input.comp_time,2) + pow(input.SHMS_elecun/input.SHMS_elec,2) + pow(input.SHMS_hadtrackun/input.SHMS_hadtrack,2))); 

	SHMS_Current_EDTM->SetPoint(SHMS_Current_EDTM->GetN(),(input.BCM4B / input.TIME),input.SHMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.SHMS_hadtrack)); 
	SHMS_Current_EDTM->SetPointError(SHMS_Current_EDTM->GetN()-1,0.0,(input.SHMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.SHMS_hadtrack)) * sqrt(pow(input.SHMS_EVENTSun/input.SHMS_EVENTS,2)+(1.0/input.ACC_EDTM) + (1.0/input.SENT_EDTM) + pow(input.SHMS_hadtrackun/input.SHMS_hadtrack,2))); 

	HMS_Rate_Old->SetPoint(HMS_Rate_Old->GetN(),(input.PS3 / input.TIME) / 1000.0,input.HMS_EVENTS/(input.BCM4B*input.comp_time*input.HMS_elec*input.HMS_etrack)); 
	HMS_Rate_Old->SetPointError(HMS_Rate_Old->GetN()-1,0.0,(input.HMS_EVENTS/(input.BCM4B*input.comp_time*input.HMS_elec*input.HMS_etrack)) * sqrt(pow(input.HMS_EVENTSun/input.HMS_EVENTS,2)+pow(input.comp_uncer/input.comp_time,2) + pow(input.HMS_elecun/input.HMS_elec,2) + pow(input.HMS_etrackun/input.HMS_etrack,2))); 

	HMS_Rate_EDTM->SetPoint(HMS_Rate_EDTM->GetN(),(input.PS3 / input.TIME) / 1000.0,input.HMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.HMS_etrack)); 
	HMS_Rate_EDTM->SetPointError(HMS_Rate_EDTM->GetN()-1,0.0,(input.HMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.HMS_etrack)) * sqrt(pow(input.HMS_EVENTSun/input.HMS_EVENTS,2)+(1.0/input.ACC_EDTM) + (1.0/input.SENT_EDTM) + pow(input.HMS_etrackun/input.HMS_etrack,2))); 

	SHMS_Rate_Old->SetPoint(SHMS_Rate_Old->GetN(),(input.PS1 / input.TIME) / 1000.0,input.SHMS_EVENTS/(input.BCM4B*input.comp_time*input.SHMS_elec*input.SHMS_hadtrack)); 
	SHMS_Rate_Old->SetPointError(SHMS_Rate_Old->GetN()-1,0.0,(input.SHMS_EVENTS/(input.BCM4B*input.comp_time*input.SHMS_elec*input.SHMS_hadtrack)) * sqrt(pow(input.SHMS_EVENTSun/input.SHMS_EVENTS,2)+pow(input.comp_uncer/input.comp_time,2) + pow(input.SHMS_elecun/input.SHMS_elec,2) + pow(input.SHMS_hadtrackun/input.SHMS_hadtrack,2))); 

	SHMS_Rate_EDTM->SetPoint(SHMS_Rate_EDTM->GetN(),(input.PS1 / input.TIME) / 1000.0,input.SHMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.SHMS_hadtrack)); 
	SHMS_Rate_EDTM->SetPointError(SHMS_Rate_EDTM->GetN()-1,0.0,(input.SHMS_EVENTS/(input.BCM4B*(input.ACC_EDTM/input.SENT_EDTM)*input.SHMS_hadtrack)) * sqrt(pow(input.SHMS_EVENTSun/input.SHMS_EVENTS,2)+(1.0/input.ACC_EDTM) + (1.0/input.SENT_EDTM) + pow(input.SHMS_hadtrackun/input.SHMS_hadtrack,2))); 
      }
  }
  fclose(fp);
  
  //Normalize yield to first entry
  Double_t Normalization_Factor;
  Double_t X;
  Double_t Y;
  Double_t EY;

  HMS_Current_Old->GetPoint(0, X, Normalization_Factor);
  for (Int_t i = 0; i < HMS_Current_Old->GetN(); i++) {
      HMS_Current_Old->GetPoint(i,X,Y);
      HMS_Current_Old->SetPoint(i,X,Y/Normalization_Factor);
      HMS_Current_Old->SetPointError(i,0.0,HMS_Current_Old->GetEY()[i]/Normalization_Factor);

      HMS_Rate_Old->GetPoint(i,X,Y);
      HMS_Rate_Old->SetPoint(i,X,Y/Normalization_Factor);
      HMS_Rate_Old->SetPointError(i,0.0,HMS_Rate_Old->GetEY()[i]/Normalization_Factor);
    }
  
  HMS_Current_EDTM->GetPoint(0, X, Normalization_Factor); 
  for (Int_t i = 0; i < HMS_Current_EDTM->GetN(); i++) {
      HMS_Current_EDTM->GetPoint(i,X,Y);
      HMS_Current_EDTM->SetPoint(i,X,Y/Normalization_Factor);
      HMS_Current_EDTM->SetPointError(i,0.0,HMS_Current_EDTM->GetEY()[i]/Normalization_Factor);

      HMS_Rate_EDTM->GetPoint(i,X,Y);
      HMS_Rate_EDTM->SetPoint(i,X,Y/Normalization_Factor);
      HMS_Rate_EDTM->SetPointError(i,0.0,HMS_Rate_EDTM->GetEY()[i]/Normalization_Factor);
    }

   SHMS_Current_Old->GetPoint(0, X, Normalization_Factor); 
  for (Int_t i = 0; i < SHMS_Current_Old->GetN(); i++) {
      SHMS_Current_Old->GetPoint(i,X,Y);
      SHMS_Current_Old->SetPoint(i,X,Y/Normalization_Factor);
      SHMS_Current_Old->SetPointError(i,0.0,SHMS_Current_Old->GetEY()[i]/Normalization_Factor);

      SHMS_Rate_Old->GetPoint(i,X,Y);
      SHMS_Rate_Old->SetPoint(i,X,Y/Normalization_Factor);
      SHMS_Rate_Old->SetPointError(i,0.0,SHMS_Rate_Old->GetEY()[i]/Normalization_Factor);
    }
  
  SHMS_Current_EDTM->GetPoint(0, X, Normalization_Factor);
  for (Int_t i = 0; i < SHMS_Current_EDTM->GetN(); i++) {
      SHMS_Current_EDTM->GetPoint(i,X,Y);
      SHMS_Current_EDTM->SetPoint(i,X,Y/Normalization_Factor);
      SHMS_Current_EDTM->SetPointError(i,0.0,SHMS_Current_EDTM->GetEY()[i]/Normalization_Factor);

      SHMS_Rate_EDTM->GetPoint(i,X,Y);
      SHMS_Rate_EDTM->SetPoint(i,X,Y/Normalization_Factor);
      SHMS_Rate_EDTM->SetPointError(i,0.0,SHMS_Rate_EDTM->GetEY()[i]/Normalization_Factor);
    }

  //Make it look nice
  HMS_Current_Old->SetMarkerColor(1);
  HMS_Current_Old->SetMarkerStyle(20);
  HMS_Current_Old->SetMarkerSize(1);
  HMS_Current_Old->GetXaxis()->SetTitle("Current uA");
  HMS_Current_Old->GetYaxis()->SetTitle("Normalized Yield");

  HMS_Current_EDTM->SetMarkerColor(1);
  HMS_Current_EDTM->SetMarkerStyle(20);
  HMS_Current_EDTM->SetMarkerSize(1);
  HMS_Current_EDTM->GetXaxis()->SetTitle("Current uA");
  HMS_Current_EDTM->GetYaxis()->SetTitle("Normalized Yield");

  SHMS_Current_Old->SetMarkerColor(1);
  SHMS_Current_Old->SetMarkerStyle(20);
  SHMS_Current_Old->SetMarkerSize(1);
  SHMS_Current_Old->GetXaxis()->SetTitle("Current uA");
  SHMS_Current_Old->GetYaxis()->SetTitle("Normalized Yield");

  SHMS_Current_EDTM->SetMarkerColor(1);
  SHMS_Current_EDTM->SetMarkerStyle(20);
  SHMS_Current_EDTM->SetMarkerSize(1);
  SHMS_Current_EDTM->GetXaxis()->SetTitle("Current uA");
  SHMS_Current_EDTM->GetYaxis()->SetTitle("Normalized Yield");

  HMS_Rate_Old->SetMarkerColor(1);
  HMS_Rate_Old->SetMarkerStyle(20);
  HMS_Rate_Old->SetMarkerSize(1);
  HMS_Rate_Old->GetXaxis()->SetTitle("Rate kHz");
  HMS_Rate_Old->GetYaxis()->SetTitle("Normalized Yield");

  HMS_Rate_EDTM->SetMarkerColor(1);
  HMS_Rate_EDTM->SetMarkerStyle(20);
  HMS_Rate_EDTM->SetMarkerSize(1);
  HMS_Rate_EDTM->GetXaxis()->SetTitle("Rate kHz");
  HMS_Rate_EDTM->GetYaxis()->SetTitle("Normalized Yield");

  SHMS_Rate_Old->SetMarkerColor(1);
  SHMS_Rate_Old->SetMarkerStyle(20);
  SHMS_Rate_Old->SetMarkerSize(1);
  SHMS_Rate_Old->GetXaxis()->SetTitle("Rate kHz");
  SHMS_Rate_Old->GetYaxis()->SetTitle("Normalized Yield");

  SHMS_Rate_EDTM->SetMarkerColor(1);
  SHMS_Rate_EDTM->SetMarkerStyle(20);
  SHMS_Rate_EDTM->SetMarkerSize(1);
  SHMS_Rate_EDTM->GetXaxis()->SetTitle("Rate kHz");
  SHMS_Rate_EDTM->GetYaxis()->SetTitle("Normalized Yield");
  
  //Reference Line
  TLine *reference = new TLine(0,1,50,1);
  reference->SetLineColor(kRed);
  
  //Draw everything
  TCanvas *HMS_old = new TCanvas("HMS_old","Normalized Yield for HMS using pTRIG and L1ACC");
  HMS_old->Divide(2,1);
  HMS_old->cd(1);
  HMS_Current_Old->Draw("AEP");
  HMS_Current_Old->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();  
  HMS_old->cd(2);
  HMS_Rate_Old->Draw("AEP");
  HMS_Rate_Old->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();

  TCanvas *HMS_EDTM = new TCanvas("HMS_EDTM","Normalized Yield for HMS using EDTM");
  HMS_EDTM->Divide(2,1);
  HMS_EDTM->cd(1);
  HMS_Current_EDTM->Draw("AEP");
  HMS_Current_EDTM->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();
  HMS_EDTM->cd(2);
  HMS_Rate_EDTM->Draw("AEP");
  HMS_Rate_EDTM->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();

  TCanvas *SHMS_old = new TCanvas("SHMS_old","Normalized Yield for SHMS using pTRIG and L1ACC");
  SHMS_old->Divide(2,1);
  SHMS_old->cd(1);
  SHMS_Current_Old->Draw("AEP");
  SHMS_Current_Old->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw(); 
  SHMS_old->cd(2);
  SHMS_Rate_Old->Draw("AEP");
  SHMS_Rate_Old->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();

  TCanvas *SHMS_EDTM = new TCanvas("SHMS_EDTM","Normalized Yield for SHMS using EDTM");
  SHMS_EDTM->Divide(2,1);
  SHMS_EDTM->cd(1);
  SHMS_Current_EDTM->Draw("AEP");
  SHMS_Current_EDTM->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();
  SHMS_EDTM->cd(2);
  SHMS_Rate_EDTM->Draw("AEP");
  SHMS_Rate_EDTM->GetYaxis()->SetTitleOffset(1.5);
  reference->Draw();

  TF1 *linear = new TF1("linear","[0] + [1]*(x)",0,100);
  linear->SetParName(0,"Intercept");
  linear->SetParName(1,"Slope");
  linear->FixParameter(0,1);
  HMS_Current_Old->Fit("linear","R");
  HMS_Current_Old->GetFunction("linear")->SetLineColor(kBlue);
  gPad->Update();
}
