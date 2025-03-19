#include <iostream> 
#include <fstream> 
#include <iomanip>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TRandom3.h>

#include "tracking_resolution/Lresolution.h"

using namespace std;

// void anaGrape(string input_filedir,string detector=""){
// void anaGrape(string detector="",bool Is_inter=false){
// void anaGrape(string detector="",bool Is_res=false){
void ana_grape_twopeg(string evgen="",string detector="",string input_filedir="",int windex=3,double Ebeam=11,bool Is_res=false,string decaypair="e",int decaymode=0)  
//windex to select weight, Ebeam to set beam energy
//Is_res and decaypair are needed for track smearing
//decaymode are needed for twopeg generator
{
//  set_style();
gROOT->Reset();
//   gStyle->SetPalette(1);
// // gStyle->SetPalette(kBird);
// gStyle->SetOptStat(11111111);
gStyle->SetOptStat(0);
gStyle->SetOptFit(1);

  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);  
  
  gStyle->SetPadColor(0);

  gStyle->SetLabelSize(0.05,"xyz"); // size of axis values
  gStyle->SetTitleSize(0.06,"xyz");  
  gStyle->SetTitleOffset(0.7,"y");
  gStyle->SetTitleOffset(1,"x");    
  gStyle->SetTitleSize(0.07,"t"); 

cout << "load reack resolution" << endl;
Lresolution track("JPsi");
TRandom3 rnd;  

int Pmax,Q2max,Qp2max;
if (Ebeam==11){
  Pmax=11;Q2max=10;Qp2max=10;
}
else{ //Ebeam 22 
  Pmax=22;Q2max=20;Qp2max=20;
}  
  
double count_convert;
double rate_convert;
double thetamin,thetamax;
TH3F *hacceptance_PThetaPhi_positive,*hacceptance_PThetaPhi_negative;
TH2F *hacceptance_ThetaP_forwardangle,*hacceptance_ThetaP_largeangle;
TH2F *hacceptance_ThetaP_forwardangle_muon,*hacceptance_ThetaP_largeangle_muon,*hacceptance_ThetaP_barrel_muon;
TH2F *hacceptance_ThetaP_forwardangle_muonm,*hacceptance_ThetaP_largeangle_muonm;
TH2F *hacceptance_ThetaP_forwardangle_muonp,*hacceptance_ThetaP_largeangle_muonp;
TH1F *hacceptance_pion_FA,*hacceptance_pion_LA,*hacceptance_pion_barrel;
TH1F *hacceptance_pion_FA_decay,*hacceptance_pion_LA_decay,*hacceptance_pion_barrel_decay;
if (detector=="CLAS12"){
//   TFile *acceptancefile=new TFile("clas12_acceptance_pipele.root");
//   TFile *acceptancefile=new TFile("clas12_acceptance_pipele_largebin.root");
  TFile *acceptancefile=new TFile("clasev_acceptance.root");
  
  hacceptance_PThetaPhi_positive=(TH3F*) acceptancefile->Get("acceptance_PThetaPhi_pip");  
  hacceptance_PThetaPhi_negative=(TH3F*) acceptancefile->Get("acceptance_PThetaPhi_ele");

  TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
  c_acceptance->Divide(2,1);
  c_acceptance->cd(1);
  hacceptance_PThetaPhi_positive->Draw();
  c_acceptance->cd(2);
  hacceptance_PThetaPhi_negative->Draw(); 
  
  thetamin=0;    
  thetamax=180;  

//      pb = 1e-36 cm2, lumi 1e35/cm2/s, 120 days, 0.85 eff
      rate_convert = 1e-36*1e35*0.85;  
      count_convert = rate_convert*3600*24*120;      
  
//   target.SetPxPyPzE(0.,0.,0.,0.938);  
//   Pmax=3; 
//   smin=10;
//   smax=25;
//   etamin=0.;  
//   etamax=0.5;
//   tmin=0;    
//   tmax=4;
//   index=4; 
//   thetamin=0;    
//   thetamax=60;  
//resolution mom 1%, theta 1mr, phi 4mr   
//   resolution_p[0]=0.01;resolution_theta[0]=1e-3;resolution_phi[0]=4e-3;
//   resolution_p[1]=0.05;resolution_theta[1]=10e-3;resolution_phi[1]=5e-3;   
}
else if (detector=="SoLID_JPsi"){  
//   TFile *acceptancefile=new TFile("acceptance_solid_JPsi_electron_target315_output.root");  
  TFile *acceptancefile=new TFile("acceptance_solid_JPsi_target315_24GeV_electron_1e7_201501_output_final.root");    
  
  hacceptance_ThetaP_forwardangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_forwardangle");  
  hacceptance_ThetaP_largeangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_largeangle");
  
  TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
  c_acceptance->Divide(2,1);
  c_acceptance->cd(1);
  hacceptance_ThetaP_forwardangle->Draw("colz");
  c_acceptance->cd(2);
  hacceptance_ThetaP_largeangle->Draw("colz");  
  
  thetamin=0;    
  thetamax=60;  
  
//      pb = 1e-36 cm2, lumi 1.2e37/cm2/s, 50 days, 0.85 eff
      rate_convert = 1e-36*1.2e37*0.85;  
      count_convert = rate_convert*3600*24*50;      
  
//   target.SetPxPyPzE(0.,0.,0.,0.938);  
//   Pmax=3; 
//   smin=10;
//   smax=25;
//   etamin=0.;  
//   etamax=0.5;
//   tmin=0;    
//   tmax=4;
//   index=4; 
//   thetamin=0;    
//   thetamax=60;  
//resolution mom 1%, theta 1mr, phi 4mr   
//   resolution_p[0]=0.01;resolution_theta[0]=1e-3;resolution_phi[0]=4e-3;
//   resolution_p[1]=0.05;resolution_theta[1]=10e-3;resolution_phi[1]=5e-3;     
}
else if (detector=="SoLID_DDVCS_JPsi"){  
//   TFile *acceptancefile=new TFile("acceptance_solid_JPsi_electron_target315_output.root");  
  TFile *acceptancefile=new TFile("acceptance_solid_JPsi_target315_24GeV_electron_1e7_201501_output_final.root");    
  
  hacceptance_ThetaP_forwardangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_forwardangle");  
  hacceptance_ThetaP_largeangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_largeangle");
  
  TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
  c_acceptance->Divide(2,1);
  c_acceptance->cd(1);
  hacceptance_ThetaP_forwardangle->Draw("colz");
  hacceptance_ThetaP_forwardangle->SetTitle(";#theta (deg); P (GeV/c)");
  hacceptance_ThetaP_forwardangle->GetXaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_forwardangle->GetXaxis()->SetTitleSize(0.06);
  hacceptance_ThetaP_forwardangle->GetYaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_forwardangle->GetYaxis()->SetTitleSize(0.06);
  hacceptance_ThetaP_forwardangle->GetZaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_forwardangle->GetZaxis()->SetTitleSize(0.06);
  
  c_acceptance->cd(2);
  hacceptance_ThetaP_largeangle->Draw("colz");  
  hacceptance_ThetaP_largeangle->SetTitle(";#theta (deg); P (GeV/c)");
  hacceptance_ThetaP_largeangle->GetXaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_largeangle->GetXaxis()->SetTitleSize(0.06);
  hacceptance_ThetaP_largeangle->GetYaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_largeangle->GetYaxis()->SetTitleSize(0.06);
  hacceptance_ThetaP_largeangle->GetZaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_largeangle->GetZaxis()->SetTitleSize(0.06);

//   TFile *acceptancefile_muon=new TFile("anaGrape/acceptance_solid_DDVCS_JPsi_LH2_muonm_target315_output.root");             
//   TFile *acceptancefile_muon=new TFile("anaGrape/acceptance_solid_DDVCS_JPsi_LH2_muonp_target315_output.root");       
// TFile *acceptancefile_muon=new TFile("anaGrape/acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_1stFAMD_1stLAMD.root");             
// TFile *acceptancefile_muon=new TFile("anaGrape/acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_2ndFAMD_1stLAMD.root");             
// TFile *acceptancefile_muon=new TFile("anaGrape/acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_3rdFAMD_1stLAMD.root");             
// TFile *acceptancefile_muon=new TFile("anaGrape/acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_4thFAMD_1stLAMD.root");             
TFile *acceptancefile_muon=new TFile("acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_mum_9e6_output_final.root");             
  
  hacceptance_ThetaP_forwardangle_muon=(TH2F*) acceptancefile_muon->Get("acceptance_ThetaP_forwardangle");  
  hacceptance_ThetaP_largeangle_muon=(TH2F*) acceptancefile_muon->Get("acceptance_ThetaP_largeangle");
  hacceptance_ThetaP_barrel_muon=(TH2F*) acceptancefile_muon->Get("acceptance_ThetaP_barrel");
  
  TCanvas *c_acceptance_muon = new TCanvas("acceptance_muon","acceptance_muon",1200,900);
  c_acceptance_muon->Divide(2,1);
  c_acceptance_muon->cd(1);
  hacceptance_ThetaP_forwardangle_muon->Draw("colz");
  hacceptance_ThetaP_forwardangle_muon->SetTitle(";#theta (deg); P (GeV/c)");
  hacceptance_ThetaP_forwardangle_muon->GetXaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_forwardangle_muon->GetXaxis()->SetTitleSize(0.06);
  hacceptance_ThetaP_forwardangle_muon->GetYaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_forwardangle_muon->GetYaxis()->SetTitleSize(0.06);
  hacceptance_ThetaP_forwardangle_muon->GetZaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_forwardangle_muon->GetZaxis()->SetTitleSize(0.06);
  c_acceptance_muon->cd(2);
  hacceptance_ThetaP_largeangle_muon->Draw("colz");   
  hacceptance_ThetaP_largeangle_muon->SetTitle(";#theta (deg); P (GeV/c)");  
  hacceptance_ThetaP_largeangle_muon->GetXaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_largeangle_muon->GetXaxis()->SetTitleSize(0.06);
  hacceptance_ThetaP_largeangle_muon->GetYaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_largeangle_muon->GetYaxis()->SetTitleSize(0.06);
  hacceptance_ThetaP_largeangle_muon->GetZaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_largeangle_muon->GetZaxis()->SetTitleSize(0.06);
  c_acceptance_muon->cd(3);
  hacceptance_ThetaP_barrel_muon->Draw("colz");   
  hacceptance_ThetaP_barrel_muon->SetTitle(";#theta (deg); P (GeV/c)");  
  hacceptance_ThetaP_barrel_muon->GetXaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_barrel_muon->GetXaxis()->SetTitleSize(0.06);
  hacceptance_ThetaP_barrel_muon->GetYaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_barrel_muon->GetYaxis()->SetTitleSize(0.06);
  hacceptance_ThetaP_barrel_muon->GetZaxis()->SetLabelSize(0.06);
  hacceptance_ThetaP_barrel_muon->GetZaxis()->SetTitleSize(0.06);  
  
  TFile *acceptancefile_pion_FA,*acceptancefile_pion_LA,*acceptancefile_pion_barrel;
  TFile *acceptancefile_pion_FA_decay,*acceptancefile_pion_LA_decay,*acceptancefile_pion_barrel_decay;
  acceptancefile_pion_FA=new TFile("acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_pim_theta12_1e6_output_final_1D_direct.root");
  acceptancefile_pion_LA=new TFile("acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_pim_theta20_1e6_output_final_1D_direct.root");
  acceptancefile_pion_barrel=new TFile("acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_pim_theta35_1e6_output_final_1D_direct.root");   
  acceptancefile_pion_FA_decay=new TFile("acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_pim_theta12_1e6_output_final_1D_directdecay.root");
  acceptancefile_pion_LA_decay=new TFile("acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_pim_theta20_1e6_output_final_1D_directdecay.root");
  acceptancefile_pion_barrel_decay=new TFile("acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_pim_theta35_1e6_output_final_1D_directdecay.root");   
      
      hacceptance_pion_FA=(TH1F*) acceptancefile_pion_FA->Get("acceptance_P_0");
      hacceptance_pion_LA=(TH1F*) acceptancefile_pion_LA->Get("acceptance_P_1");
      hacceptance_pion_barrel=(TH1F*) acceptancefile_pion_barrel->Get("acceptance_P_2");    
      
      TCanvas *c_acceptance_pion = new TCanvas("acceptance_pion","acceptance_pion",1200,900);
      hacceptance_pion_FA->SetLineColor(kBlack);
      hacceptance_pion_LA->SetLineColor(kRed);
      hacceptance_pion_barrel->SetLineColor(kBlue);
      hacceptance_pion_FA->Draw();
      hacceptance_pion_LA->Draw("same");
      hacceptance_pion_barrel->Draw("same");
      hacceptance_pion_FA->SetTitle("pion;P (GeV/c);acceptance");
      hacceptance_pion_FA->SetMaximum(0.01);
      TLegend* leg1 = new TLegend(0.7, 0.7, 0.95, 0.99);  
      leg1->AddEntry(hacceptance_pion_FA,"FA","l");
      leg1->AddEntry(hacceptance_pion_LA,"LA","l");     
      leg1->AddEntry(hacceptance_pion_barrel,"barrel","l");       
      leg1->Draw();  
      
      hacceptance_pion_FA_decay=(TH1F*) acceptancefile_pion_FA_decay->Get("acceptance_P_0");
      hacceptance_pion_LA_decay=(TH1F*) acceptancefile_pion_LA_decay->Get("acceptance_P_1");
      hacceptance_pion_barrel_decay=(TH1F*) acceptancefile_pion_barrel_decay->Get("acceptance_P_2");    
      
      TCanvas *c_acceptance_pion_decay = new TCanvas("acceptance_pion_decay","acceptance_pion_decay",1200,900);
      hacceptance_pion_FA_decay->SetLineColor(kBlack);
      hacceptance_pion_LA_decay->SetLineColor(kRed);
      hacceptance_pion_barrel_decay->SetLineColor(kBlue);
      hacceptance_pion_FA_decay->Draw();
      hacceptance_pion_LA_decay->Draw("same");
      hacceptance_pion_barrel_decay->Draw("same");
      hacceptance_pion_FA_decay->SetTitle("muon from pion decay;P (GeV/c);acceptance");
      hacceptance_pion_FA_decay->SetMaximum(0.1);  
      TLegend* leg1_decay = new TLegend(0.7, 0.7, 0.95, 0.99);  
      leg1_decay->AddEntry(hacceptance_pion_FA_decay,"FA","l");
      leg1_decay->AddEntry(hacceptance_pion_LA_decay,"LA","l");     
      leg1_decay->AddEntry(hacceptance_pion_barrel_decay,"barrel","l");       
      leg1_decay->Draw();        
    
  thetamin=0;    
  thetamax=90;  
  
  if(evgen=="grape"){
//  grape generator output unit pb = 1e-36 cm2, lumi 1.2e37/cm2/s, 50 days, 0.85 eff
//       rate_convert = 1e-36*1.2e37*0.85;  
      rate_convert = 1e-36*1.2e37*0.7;      
      count_convert = rate_convert*3600*24*50;   
  }
  else if(evgen=="twopeg"){
// twopeg generator output unit ub = 1e-30 cm2, lumi 1.2e37/cm2/s, 50 days, 0.85 eff
//       rate_convert = 1e-30*1.2e37*0.85;
      rate_convert = 1e-30*1.2e37*0.7;    
      count_convert = rate_convert*3600*24*50;   
  }
  else {cout << "not supported evgen " << evgen << endl; return;}
 
//   target.SetPxPyPzE(0.,0.,0.,0.938);  
//   Pmax=3; 
//   smin=10;
//   smax=25;
//   etamin=0.;  
//   etamax=0.5;
//   tmin=0;    
//   tmax=4;
//   index=4; 
//   thetamin=0;    
//   thetamax=60;  
//resolution mom 1%, theta 1mr, phi 4mr   
//   resolution_p[0]=0.01;resolution_theta[0]=1e-3;resolution_phi[0]=4e-3;
//   resolution_p[1]=0.05;resolution_theta[1]=10e-3;resolution_phi[1]=5e-3;   
}
else if (detector=="SoLID_DDVCS_PVDIS"){
  TFile *acceptancefile=new TFile("acceptance_solid_PVDIS_electron_output.root");  
  
  hacceptance_ThetaP_forwardangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_forwardangle");  
    
  TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1000,900);
  c_acceptance->Divide(1,1);
  c_acceptance->cd(1);
  hacceptance_ThetaP_forwardangle->Draw("colz");
  
//    TFile *acceptancefile_muonm=new TFile("anaGrape/acceptance_solid_DDVCS_PVDIS_LH2_full_muonm_1e5_output_1stFAMD.root");             
//    TFile *acceptancefile_muonp=new TFile("anaGrape/acceptance_solid_DDVCS_PVDIS_LH2_full_muonp_1e5_output_1stFAMD.root");             
   TFile *acceptancefile_muonm=new TFile("acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_4thFAMD_1stLAMD.root");             
   TFile *acceptancefile_muonp=new TFile("acceptance_solid_DDVCS_JPsi_LH2_full_muonm_1e6_output_4thFAMD_1stLAMD.root");             
   
   hacceptance_ThetaP_forwardangle_muonm=(TH2F*) acceptancefile_muonm->Get("acceptance_ThetaP_forwardangle"); 
   hacceptance_ThetaP_forwardangle_muonp=(TH2F*) acceptancefile_muonp->Get("acceptance_ThetaP_forwardangle");    
  
  TCanvas *c_acceptance_muon = new TCanvas("acceptance_muon","acceptance_muon",1200,900);
  c_acceptance_muon->Divide(2,1);
  c_acceptance_muon->cd(1);
  hacceptance_ThetaP_forwardangle_muonm->Draw("colz");
  c_acceptance_muon->cd(2);
  hacceptance_ThetaP_forwardangle_muonp->Draw("colz");  
   
  thetamin=0;    
  thetamax=90;  
  
//      pb = 1e-36 cm2, lumi 0.53e39/cm2/s, 120 days, 0.85 eff
      rate_convert = 1e-36*0.53e39*0.85;  
      count_convert = rate_convert*3600*24*120;
}
else if (detector=="JLEIC"){
//   TFile *acceptancefile=new TFile("anaGrape/acceptance_solid_PVDIS_electron_output.root");  
//   
//   hacceptance_ThetaP_forwardangle=(TH2F*) acceptancefile->Get("acceptance_ThetaP_forwardangle");  
//     
//   TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1000,900);
//   c_acceptance->Divide(1,1);
//   c_acceptance->cd(1);
//   hacceptance_ThetaP_forwardangle->Draw("colz");
//   
//    TFile *acceptancefile_muonm=new TFile("anaGrape/acceptance_solid_DDVCS_PVDIS_LH2_full_muonm_1e5_output_1stFAMD.root");             
//    TFile *acceptancefile_muonp=new TFile("anaGrape/acceptance_solid_DDVCS_PVDIS_LH2_full_muonp_1e5_output_1stFAMD.root");             
//    
//    hacceptance_ThetaP_forwardangle_muonm=(TH2F*) acceptancefile_muonm->Get("acceptance_ThetaP_forwardangle"); 
//    hacceptance_ThetaP_forwardangle_muonp=(TH2F*) acceptancefile_muonp->Get("acceptance_ThetaP_forwardangle");    
//   
//   TCanvas *c_acceptance_muon = new TCanvas("acceptance_muon","acceptance_muon",1200,900);
//   c_acceptance_muon->Divide(2,1);
//   c_acceptance_muon->cd(1);
//   hacceptance_ThetaP_forwardangle_muonm->Draw("colz");
//   c_acceptance_muon->cd(2);
//   hacceptance_ThetaP_forwardangle_muonp->Draw("colz");  
   
  thetamin=0;    
  thetamax=180;  
  
//      pb = 1e-36 cm2, lumi 1e34/cm2/s, 365 days, 0.85 eff
      rate_convert = 1e-36*1e34*0.85;  
      count_convert = rate_convert*3600*24*365;
}
else {cout << "wrong detector" << endl; return;}

  
//   TFile *acceptancefile=new TFile("accep.root");
// TH2F *h2_acc=(TH2F*) acceptancefile->Get("h2");
// TH2F *h3_acc=(TH2F*) acceptancefile->Get("h3");
//   TCanvas *c_acceptance = new TCanvas("acceptance","acceptance",1200,900);
//   c_acceptance->Divide(2,1);
//   c_acceptance->cd(1);
//   h2_acc->Draw("colz");
//   c_acceptance->cd(2);
//   h3_acc->Draw("colz");

//  bool conf_4fold=false,conf_3fold_NOp=false,conf_3fold_NOe=false;
//  bool conf_validation=false;
// if (input_filedir.find("4fold",0) != string::npos)  conf_4fold=true;
// if (input_filedir.find("3fold_NOp",0) != string::npos)  conf_3fold_NOp=true; 
// if (input_filedir.find("3fold_NOe",0) != string::npos)  conf_3fold_NOe=true;
// if (input_filedir.find("validation",0) != string::npos)  conf_validation=true; 

// sprintf(output_filename, "out.root");
// char output_filename[200];
// sprintf(output_filename, "%s/output.root",input_filedir.c_str());
// cout << output_filename << endl;
// TFile *outputfile=new TFile(output_filename, "recreate");

string output_filename=input_filedir+"/output.root";
TFile *outputfile=new TFile(output_filename.c_str(), "recreate");

TH1F *hPlog_plus_FA = new TH1F("Plog_plus_FA","mu+ FA;log(P) GeV;kHz",50,-6,1.3);
TH1F *hPlog_plus_LA = new TH1F("Plog_plus_LA","mu+ LA;log(P) GeV;kHz",50,-6,1.3);
TH1F *hPlog_minus_FA = new TH1F("Plog_minus_FA","mu- FA;log(P) GeV;kHz",50,-6,1.3);
TH1F *hPlog_minus_LA = new TH1F("Plog_minus_LA","mu- LA;log(P) GeV;kHz",50,-6,1.3);

TH2F *hepscat = new TH2F("hepscat","",50,-1.0,1.0,60,-1.0,1.0);
TH2F *hemscat = new TH2F("hemscat","",50,-1.0,1.0,60,-1.0,1.0);

TH1F *hW = new TH1F("W","",50,4,4.5);
TH1F *hWstat = new TH1F("Wstat","",50,4,4.5);

TH1F *hkpth = new TH1F("hkpth","",100, 0.0, 40.0);
TH1F *hprth = new TH1F("hprth","",100, 0.0, 40.0);

TH1F *hkpph = new TH1F("hkpph","",100, -180., 180.);
TH1F *hprph = new TH1F("hprph","",100, -180., 180.);

TH1F *hkpp = new TH1F("hkpp","",100,0, 5);
TH1F *hprp = new TH1F("hprp","",100,0, 5);

TH1F *hMM = new TH1F("MM",";MM (GeV)",150,0.5,2);
TH2F *hMM_Q2 = new TH2F("MM_Q2","; MM (GeV);Q^{2}(GeV^{2})",150,0.5,2,100,0,10);
TH2F *hMM_Qp2 = new TH2F("MM_Qp2","; MM (GeV);Q'^{2}(GeV^{2})",150,0.5,2,100,0,10);
TH2F *hMM_t = new TH2F("MM_t","; MM (GeV);-t (GeV^{2})",150,0.5,2,100,0,2);

TH1F *ht = new TH1F("t","t",600,0,6);

TH2F *ht_Q2Qp2 = new TH2F("t_Q2Qp2",";-t (GeV^{2});Q2+Q'^{2}(GeV^{2})",100,0,2,(Q2max+Qp2max)*10,0,Q2max+Qp2max);
TH2F *ht_Qp2 = new TH2F("t_Qp2",";-t (GeV^{2});Q'^{2}(GeV^{2})",100,0,2,Qp2max*10,0,Qp2max);
TH2F *ht_W = new TH2F("t_W",";-t (GeV^{2});W (GeV)",100,0,2,100,0,10);
TH2F *hQ2_W = new TH2F("Q2_W",";Q^{2}(GeV^{2});W (GeV)",Q2max*10,0,Q2max,100,0,10);
TH2F *ht_Q2 = new TH2F("t_Q2",";-t (GeV^{2});Q^{2}(GeV^{2})",100,0,2,Q2max*10,0,Q2max);
TH2F *ht_xip = new TH2F("t_xip",";-t (GeV^{2});#xi'",100,0,2,200,-1,1);
TH2F *ht_xi = new TH2F("t_xi",";-t(GeV^{2});#xi",100,0,2,100,0,1);

TH2F *hxbj_xip = new TH2F("xbj_xip",";x_{B};#xi'",100,0,1,200,-1,1);
TH2F *hxbj_xi = new TH2F("xbj_xi",";x_{B};#xi",100,0,1,100,0,1);
TH2F *hxbj_Q2= new TH2F("xbj_Q2",";x_{B};Q^{2}(GeV^{2})",100,0,1,Q2max*10,0,Q2max);
TH2F *hxip_xi = new TH2F("xip_xi",";#xi';#xi;",100,-1,1,100,0,1);
TH2F *hQ2_Qp2 = new TH2F("Q2_Qp2",";Q^{2}(GeV^{2});Q'^{2}(GeV^{2})",Q2max*10,0,Q2max,Qp2max*10,0,Qp2max);

TH2F *htmin_W = new TH2F("tmin_W",";tmin (GeV^{2});W (GeV)",100,0,5,100,0,10);
TH2F *htmax_W = new TH2F("tmax_W",";tmax (GeV^{2});W (GeV)",100,0,5,100,0,10);	

//count for projection plot
const int n=10;
TH1F *hcount[n];
for(int i=0;i<n;i++){  
//   hcount[i]=new TH1F(Form("hcount%i",i),"SoLID DDVCS,lumi 1e37/cm2/s,50 days,eff 70\%;#phi (deg);count",12,0,360);
    hcount[i]=new TH1F(Form("hcount%i",i),"BH crosssection;#phi (deg);crosssection (pb/30deg)",12,0,360);
}

// const int m=4;
const int m=5;

char *title[4]={"scattered lepton","recoil p","decay lepton^{-}","decay lepton^{+}"};
TH3F *ht_Qp2_xip[m];
TH2F *hQp2_xip[m],*hQp2_t[m];
TH1F *hlepIM1[m],*hlepIM2[m],*hlepIM[m];
TH1F *hlepIM1_error[m],*hlepIM2_error[m],*hlepIM_error[m];
TH2F *hlepIM_2D[m];
TH2F *hdecaymom1[m],*hdecaymom2[m];
TH2F *hdecayangle1_theta[m],*hdecayangle2_theta[m],*hdecayangle3_theta[m];
TH2F *hdecayangle1_phi[m],*hdecayangle2_phi[m],*hdecayangle3_phi[m];
TH2F *hdecayangle1_thetaphi[m],*hdecayangle2_thetaphi[m],*hdecayangle3_thetaphi[m];
TH2F *hThetaP[4][m],*hThetaPhi[4][m];
TH1F *hnew_p[m],*hnew_theta[m],*hnew_phi[m];
for(int k=0;k<m;k++){
  char hstname[100];
  for(int l=0;l<4;l++){  
   sprintf(hstname,"ThetaP_%i_%i",l,k);
   hThetaP[l][k]=new TH2F(hstname,Form("%s;#theta_{lab} (deg);P (GeV)",title[l]),180,0,180,Pmax*10,0,Pmax);
   sprintf(hstname,"ThetaPhi_%i_%i",l,k);
   hThetaPhi[l][k]=new TH2F(hstname,";#theta_{lab} (deg);#phi_{lab} (deg)",180,0,180,100,-180.,180.);   
  }

  sprintf(hstname,"new_p_%i",k);
  hnew_p[k] = new TH1F(hstname,hstname,100,-0.1,0.1);
  sprintf(hstname,"new_theta_%i",k);
  hnew_theta[k] = new TH1F(hstname,hstname,100,-0.5,0.5);
  sprintf(hstname,"new_phi_%i",k);
  hnew_phi[k] = new TH1F(hstname,hstname,100,-1,1);
  
  sprintf(hstname,"decaymom1_%i",k);
  hdecaymom1[k] = new TH2F(hstname,";l^{+} P (GeV);l^{-} P (GeV)",100,0,10,100,0,10);
  sprintf(hstname,"decaymom2_%i",k);
  hdecaymom2[k] = new TH2F(hstname,";l^{+} P (GeV);l^{-} P (GeV)",100,0,10,100,0,10);

  sprintf(hstname,"decayangle1_phi_%i",k);
  hdecayangle1_phi[k] = new TH2F(hstname,";decay lepton^{+} #phi (deg);decay lepton^{-} #phi (deg)",180,-180,180,180,-180,180);
  sprintf(hstname,"decayangle2_phi_%i",k);
  hdecayangle2_phi[k] = new TH2F(hstname,";decay lepton^{+} #phi (deg);scattered lepton #phi (deg)",180,-180,180,180,-180,180);
  sprintf(hstname,"decayangle3_phi_%i",k);
  hdecayangle3_phi[k] = new TH2F(hstname,";decay lepton^{-} #phi (deg);scattered lepton #phi (deg)",180,-180,180,180,-180,180);

  sprintf(hstname,"decayangle1_theta_%i",k);
  hdecayangle1_theta[k] = new TH2F(hstname,";decay lepton^{+} #theta (deg);decay lepton^{-} #theta (deg)",90,0,90,90,0,90);
  sprintf(hstname,"decayangle2_theta_%i",k);
  hdecayangle2_theta[k] = new TH2F(hstname,";decay lepton^{+} #theta (deg);scattered lepton #theta (deg)",90,0,90,90,0,90);
  sprintf(hstname,"decayangle3_theta_%i",k);
  hdecayangle3_theta[k] = new TH2F(hstname,";decay lepton^{-} #theta (deg);scattered lepton #theta (deg)",90,0,90,90,0,90);

  sprintf(hstname,"decayangle1_thetaphi_%i",k);
  hdecayangle1_thetaphi[k] = new TH2F(hstname,";decay lepton^{+} #theta*180+#phi (deg);decay lepton^{-} #theta*180+#phi (deg)",2*18*9,-180*90,90*180,2*180*90,-180*90,90*180);
  sprintf(hstname,"decayangle2_thetaphi_%i",k);
  hdecayangle2_thetaphi[k] = new TH2F(hstname,";decay lepton^{+} #theta*180+#phi (deg);scattered lepton #theta*180+#phi (deg)",2*18*9,-180*90,90*180,2*180*90,-180*90,90*180);
  sprintf(hstname,"decayangle3_thetaphi_%i",k);
  hdecayangle3_thetaphi[k] = new TH2F(hstname,";decay lepton^{-} #theta*180+#phi (deg);scattered lepton #theta*180+#phi (deg)",2*18*9,-180*90,90*180,2*180*90,-180*90,90*180);
  
  sprintf(hstname,"lepIM_2D_%i",k);
  hlepIM_2D[k] = new TH2F(hstname,";e+ e-(1st) Inv Mass (GeV);e+ e-(2nd) Inv Mass (GeV)",100,0,5.0,100,0,5.0);   
  
  sprintf(hstname,"lepIM1_%i",k);
  hlepIM1[k] = new TH1F(hstname,hstname,100,0,5);   
//   hlepIM1[k] = new TH1F(hstname,hstname,95,5,100);     
  sprintf(hstname,"lepIM2_%i",k);
  hlepIM2[k] = new TH1F(hstname,hstname,100,0,5);   
  sprintf(hstname,"lepIM_%i",k);
  hlepIM[k] = new TH1F(hstname,hstname,100,0,5);

  sprintf(hstname,"lepIM1_error_%i",k);
  hlepIM1_error[k] = new TH1F(hstname,hstname,20,0,4.0);   
  sprintf(hstname,"lepIM2_error_%i",k);
  hlepIM2_error[k] = new TH1F(hstname,hstname,20,0,4.0);   
  sprintf(hstname,"lepIM_error_%i",k);
  hlepIM_error[k] = new TH1F(hstname,hstname,20,0,4.0);
  
  sprintf(hstname,"t_Qp2_xip_%i",k);
  ht_Qp2_xip[k]=new TH3F(hstname,hstname,100,0,1,Qp2max*10,0,Qp2max,100,0,5);
  ht_Qp2_xip[k]->SetTitle(";#eta;Q'^{2}(GeV^{2});t(GeV^{2})");      
  sprintf(hstname,"Qp2_xip_%i",k);
  hQp2_xip[k]=new TH2F(hstname,hstname,100,0,1,Qp2max*10,0,Qp2max);
  hQp2_xip[k]->SetTitle(";#eta;Q'^{2}(GeV^{2})");
  sprintf(hstname,"Qp2_t_%i",k);  
  hQp2_t[k]=new TH2F(hstname,hstname,100,0,5,Qp2max*10,0,Qp2max);
  hQp2_t[k]->SetTitle(";t(GeV^{2});Q'^{2}(GeV^{2})");  
}

double weight[m];

Double_t pi1 = TMath::Pi();
//   cout << pi1 << endl;

Double_t D2R = 3.1415/180.;

Double_t DEG = 180./3.1415;

char input_filename[200];
// sprintf(input_filename,"%s",input.c_str());

//for both
Double_t effxsec;  
Int_t nevent;
//for grape
TChain *h11,*h1;
Double_t xsec[20];  
Float_t px[20],py[20],pz[20],pe[20],pm[20],kf[20],sta[20],npy[20],mot[20];
//for twopeg
ifstream infile;
if(evgen=="grape"){
// char* input_filename[5]={"grp.root_1","grp.root_2","grp.root_3","grp.root_4","grp.root_5"};
// char* input_filename[1]={"grp.root_1"};
// char* input_filename[1]={"grp.root"};
  sprintf(input_filename, "%s/grp.root",input_filedir.c_str());
//   sprintf(input_filename, "grp.root");
  
  h11 = new TChain("h11");
  h1 = new TChain("h1");
  for(Int_t i=0; i < 1; i++){
//     h11->Add(input_filename[i]);
//     h1->Add(input_filename[i]);  
	if(!h11->Add(input_filename,0)) return;    
        h11->Add(input_filename);
	h1->Add(input_filename);  
  }

  h11->SetBranchStatus("*",0);
  h11->SetBranchStatus("xsec",1);
  h11->SetBranchAddress("xsec",&xsec);
  h11->GetEntry(0);

  cout << "total Cross Section " << xsec[0] << " pb" << endl;
  // total Cross Section also can be found in the spring output on screen

  h1->SetBranchStatus("*",0);
  h1->SetBranchStatus("px",1);
  h1->SetBranchAddress("px",&px);
  h1->SetBranchStatus("py",1);
  h1->SetBranchAddress("py",&py);
  h1->SetBranchStatus("pz",1);
  h1->SetBranchAddress("pz",&pz);
  h1->SetBranchStatus("pe",1);
  h1->SetBranchAddress("pe",&pe);
  h1->SetBranchStatus("pm",1);
  h1->SetBranchAddress("pm",&pm);
  h1->SetBranchStatus("kf",1);
  h1->SetBranchAddress("kf",&kf);
  h1->SetBranchStatus("sta",1);
  h1->SetBranchAddress("sta",&sta);
  h1->SetBranchStatus("npy",1);
  h1->SetBranchAddress("npy",&npy);
  h1->SetBranchStatus("mot",1);
  h1->SetBranchAddress("mot",&mot);
  
  nevent = h1->GetEntries();
  
  effxsec = xsec[0]/(double)nevent;  
}
else if(evgen=="twopeg"){
  sprintf(input_filename, "%s/twopeg.dat",input_filedir.c_str());  
//   sprintf(input_filename, "twopeg.dat");
  
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(input_filename);
    if(!myfile.good()) {cout << "file exist?" << endl; return;}    
    while (std::getline(myfile, line)) ++number_of_lines;
    myfile.close();
//     std::cout << "Number of lines in text file: " << number_of_lines << endl;  
  
    nevent=int(number_of_lines/5);
    
//   nevent = gSystem->Exec(Form("wc %s",input_filename[i]));
//   std::string nevent_string = system(Form("wc -l < %s",input_filename));
//     int nevent_string = system(Form("wc -l < %s",input_filename));
//   cout << " nevent_string " << nevent_string << endl;
//   if(Nsim>0)  nevent = Nsim;
//   nevent = int(atoi(nevent_string)/5);
//   if(Nsim>0)  nevent = int(nevent_string/5);  
//   else {cout << "twopeg needs Nsim" << endl; return;}
  
  infile.open(input_filename);
}
else {cout << "not supported evgen " << evgen << endl; return;}

  cout << "nevent " << nevent << endl;

  TLorentzVector kp, prot, ep, em, ki, targ;

//   Bool_t scatPhiBool, scat_e_calo;

  int counter1=0,counter2=0,counter3=0,counter4=0,counter5=0,counter6=0;
  
  Int_t counter;
  Int_t countd = 1;
  cout << "|___________________|" << endl;
  cout << "|" << flush;
  
//     double xsec_thisbin=0;  
  
  for(Int_t i=0; i < nevent; i++){
//     for(Int_t i=0; i < 10; i++){
    Double_t id = i;
    Double_t neventd = nevent;
    if(floor(id/neventd*20) == countd){
   
      cout << "=" << flush;
      countd++;
      if(countd == 20){
	cout << "|" << endl;
      }
    }
//     cout << i << endl;

  if(evgen=="grape"){
    h1->GetEvent(i);

    //all entry http://research.kek.jp/people/tabe/grape/CPC/node8.html
    if(i<10) {
      cout << "*****event " << i+1 << "******************************"<< endl;              
        TLorentzVector par_tmp_sum;        
//       for (Int_t j=0; j < 14; j++) {
      for (Int_t j=0; j < 30; j++) {   //elastic has 14 entries, quasi-elastic has more than 14 entries
//         if (pm[j]=0 && pe[j]==0) break;  //skip meaningless entries
        if (pm[j]<0.0001 && pe[j]<0.0001) break;  //skip meaningless entries
        
        TLorentzVector par_tmp;
        par_tmp.SetXYZT(px[j],py[j],pz[j],pe[j]);
          
	cout << j+1 << setw(15)  << pm[j] << setw(15)  << par_tmp.M() << setw(15)  << px[j] <<  setw(15)  << py[j] <<  setw(15)  << pz[j] <<  setw(15)  << pe[j] <<  setw(15)  << setw(15)  << kf[j] <<  setw(15)  << sta[j] <<  setw(15)  << npy[j] << setw(15)  << mot[j] <<endl;

        if (14<=j && j<=30) par_tmp_sum=par_tmp_sum+par_tmp;
      }      
      if (par_tmp_sum.M()!=0) cout << par_tmp_sum.M()  << " is mass of line 14+ for quasi-elastic " << endl;
    }

    
// https://research.kek.jp/people/tabe/grape/CPC/node8.html
// pe is not very accurate for electron, use pm instead
// beam particle 
//     targ.SetXYZM(px[0],py[0],pz[0],pm[0]);    
//     ki.SetXYZM(px[1],py[1],pz[1],pm[1]);    
// Partons before ISR(initial state radiation)  
//     targ.SetXYZM(px[2],py[2],pz[2],pm[2]);
//     ki.SetXYZM(px[3],py[3],pz[3],pm[3]);
// Partons after ISR(initial state radiation)  
    targ.SetXYZM(px[4],py[4],pz[4],pm[4]);
    ki.SetXYZM(px[5],py[5],pz[5],pm[5]); 
// cout <<  targ.P()  << " " <<  ki.P() << endl;

    //particle before FSR   
    prot.SetXYZM(px[6],py[6],pz[6],pm[6]);    
    kp.SetXYZM(px[7],py[7],pz[7],pm[7]);
    ep.SetXYZM(px[8],py[8],pz[8],pm[8]);
    em.SetXYZM(px[9],py[9],pz[9],pm[9]);    
    //particle after FSR (not effective for leptons for elastic)
//     prot.SetXYZM(px[10],py[10],pz[10],pm[10]);    
//     kp.SetXYZM(px[11],py[11],pz[11],pm[11]);
//     ep.SetXYZM(px[12],py[12],pz[12],pm[12]);
//     em.SetXYZM(px[13],py[13],pz[13],pm[13]);
// cout <<  prot.M()  << " " <<  kp.M() << " " << ep.M() << " " << em.M() << endl;
    
    //grape-dilepton use coordinate where electron beam goes along -z
    //for SoLID, it need a rotation
    if (detector != "JLEIC"){
    ki.RotateY(pi1);
    targ.RotateY(pi1);    
    prot.RotateY(pi1);    
    kp.RotateY(pi1);
    ep.RotateY(pi1);
    em.RotateY(pi1);  
    }    
  }
  else if(evgen=="twopeg"){
    double Ebeam=11;
    targ.SetXYZT(0, 0, 0, 0.938272);
    ki.SetXYZT(0,0,Ebeam,sqrt(Ebeam*Ebeam + 0.511e-3 * 0.511e-3));

// 4  1.  1.  0  0  4  0  1.889796  6.553975  0.000018
//  1  -1.  1  11  0  0  -1.877907  -0.057927  5.775509  6.073417  0.0005  0.0000  0.0000  -316.194641
//  2  1.  1  2212  0  0  0.764642  0.325740  2.667097  2.946955  0.9383  0.0000  0.0000  -316.194641
//  3  1.  1  211  0  0  0.979805  -0.355153  2.477497  2.691398  0.1396  0.0000  0.0000  -316.194641
//  4  -1.  1  -211  0  0  0.133459  0.087341  0.079897  0.226502  0.1396  0.0000  0.0000  -316.194641
    
    
    double temp, px_tmp, py_tmp, pz_tmp, E_tmp, W_tmp, Q2_tmp, weight_tmp;    
    infile >> temp >> temp >> temp >> temp >> temp >> temp >> temp >> W_tmp >> Q2_tmp >> weight_tmp;  
    infile >> temp >> temp >> temp >> temp >> temp >> temp >> px_tmp >> py_tmp >> pz_tmp >> E_tmp >> temp >> temp >> temp >> temp;
    kp.SetXYZT(px_tmp, py_tmp, pz_tmp, E_tmp);
    infile >> temp >> temp >> temp >> temp >> temp >> temp >> px_tmp >> py_tmp >> pz_tmp >> E_tmp >> temp >> temp >> temp >> temp;
    prot.SetXYZT(px_tmp, py_tmp, pz_tmp, E_tmp);
    infile >> temp >> temp >> temp >> temp >> temp >> temp >> px_tmp >> py_tmp >> pz_tmp >> E_tmp >> temp >> temp >> temp >> temp;
//     ep.SetXYZT(px_tmp, py_tmp, pz_tmp, E_tmp);
    ep.SetXYZM(px_tmp, py_tmp, pz_tmp, 0.1056);    //pion as muon
    infile >> temp >> temp >> temp >> temp >> temp >> temp >> px_tmp >> py_tmp >> pz_tmp >> E_tmp >> temp >> temp >> temp >> temp;
//     em.SetXYZT(px_tmp, py_tmp, pz_tmp, E_tmp);
    em.SetXYZM(px_tmp, py_tmp, pz_tmp, 0.1056);    //pion as muon       
    
    if(i<3) {
      	cout << i << "\t"  << W_tmp << "\t"  << Q2_tmp  << "\t"  << weight_tmp << endl;
	cout << kp.Px() << "\t"  << kp.Py() << "\t"  << kp.Pz() << endl;
	cout << prot.Px() << "\t"  << prot.Py() << "\t"  << prot.Pz() << endl;
	cout << ep.Px() << "\t"  << ep.Py() << "\t"  << ep.Pz() << endl;
	cout << em.Px() << "\t"  << em.Py() << "\t"  << em.Pz() << endl;	
    }

// from twopeg generator, this is max allowed W and Q2 range for Ebeam=11 and no limit on scattered e-
// Minimum W  has been changed to 1.2375
// Minimum Q2 has been changed to 5e-05
// Maximum W  has been changed to 4.63921
// W^2=M^2+2M(E-E')-Q2
    double W_min=1.2375,W_max=sqrt(0.938*0.938+2*0.938*Ebeam-Q2_tmp);
    double Q2_min=5e-5,Q2_max=0.938*0.938+2*0.938*Ebeam-W_tmp*W_tmp;
    effxsec=(W_max-W_min)*(Q2_max-Q2_min)*weight_tmp/double(nevent);
  }
  else {cout << "not supported evgen " << evgen << endl; return;}
  
    //get acceptance
      int whichone=0;      
      double acc=0;      
      double acc_prot=0,acc_kp=0,acc_em=0,acc_ep=0;
      double acc_em_FA=0,acc_em_LA=0,acc_em_barrel=0,acc_ep_FA=0,acc_ep_LA=0,acc_ep_barrel=0;
      double acc_kp_FA=0,acc_kp_LA=0,acc_prot_FA=0,acc_prot_LA=0;      
      if (detector=="CLAS12"){
	  //note CLAS12 acceptance phi (0,360), TLonrenzvector.Phi (-180,180) 	
	  acc_prot=hacceptance_PThetaPhi_positive->GetBinContent(hacceptance_PThetaPhi_positive->FindBin(prot.Phi()*DEG+180,prot.Theta()*DEG,prot.P()));
	  acc_ep=hacceptance_PThetaPhi_positive->GetBinContent(hacceptance_PThetaPhi_positive->FindBin(ep.Phi()*DEG+180,ep.Theta()*DEG,ep.P()));
	  acc_kp=hacceptance_PThetaPhi_negative->GetBinContent(hacceptance_PThetaPhi_negative->FindBin(kp.Phi()*DEG+180,kp.Theta()*DEG,kp.P()));	  
	  acc_em=hacceptance_PThetaPhi_negative->GetBinContent(hacceptance_PThetaPhi_negative->FindBin(em.Phi()*DEG+180,em.Theta()*DEG,em.P()));	  	  
	  
// 	  if (acc_prot > 0) cout << "acc_prot " << acc_prot << endl;
// 	  if (acc_ep > 0) cout << "acc_ep " << acc_ep << endl;
// 	  if (acc_kp > 0) cout << "acc_kp " << acc_kp << endl;
// 	  if (acc_em > 0) cout << "acc_em " << acc_em << endl; 

// 	  //cut away unsure low acceptance		  
// 	  if (acc_prot < 0.9) acc_prot=0;
// 	  if (acc_ep < 0.9) acc_ep=0;
// 	  if (acc_kp < 0.9) acc_kp=0;
// 	  if (acc_em < 0.9) acc_em=0; 
	    	  
	  //lepton has no detection at central detector, nor when higher than 4.9GeV HTCC threshold at forward detetor
	  if (ep.Theta()*DEG>36 || (ep.Theta()*DEG<=36 && ep.P() > 4.9)) acc_ep=0;
	  if (em.Theta()*DEG>36 || (em.Theta()*DEG<=36 && em.P() > 4.9)) acc_em=0;
	  if (kp.Theta()*DEG>36 || (kp.Theta()*DEG<=36 && kp.P() > 4.9)) acc_kp=0;
	  
	  //for both electron
	  if (acc_ep>0 && acc_em>0 && acc_kp>0)	{acc=acc_ep*acc_em*acc_kp; whichone=1;}  //both in main detector
	  else if (acc_ep>0 && acc_em>0 && (2.5 <=kp.Theta()*DEG && kp.Theta()*DEG<=4.5)) {acc=acc_ep*acc_em*1; whichone=2;} //one in forard tagger
	  else if (acc_ep>0 && (2.5 <=em.Theta()*DEG && em.Theta()*DEG<=4.5) && acc_kp>0) {acc=acc_ep*1*acc_kp; whichone=3;}	//the other in forard tagger  
	  else if (acc_ep>0 && (2.5 <=em.Theta()*DEG && em.Theta()*DEG<=4.5) && (2.5 <=kp.Theta()*DEG && kp.Theta()*DEG<=4.5)) {acc=acc_ep*1*1; whichone=4;}	 //both in forard tagger 
	  else if (acc_ep>0) {acc=0; whichone=5;} //positron detected, but not both electron detected
	  else {acc=0; whichone=0;}  //all other cases
	  	    
// 	  if (prot.Theta()*DEG>36 && prot.P() > 1) acc_prot=0;
// 	  if (prot.Theta()*DEG<36 && prot.P() > 4) acc_prot=0;
	  
// 	  acc=acc_prot*acc_ep*acc_kp*acc_em;
// 	  acc=acc_ep*acc_kp*acc_em;	  

	  if (acc>0){
	    if (whichone==1) {counter1++; }
	    else if (whichone==2) counter2++;
	    else if (whichone==3) counter3++;
	    else if (whichone==4) counter4++;	    
	    else cout << "something wrong" << endl;
	  }
	  else {
	    if (whichone==5) counter5++;
	    else counter6++;
	  }
// 	  if (acc==0 && whichone!=4) cout << "kkkkkkkkkkkkkk" << endl;
	  
// 	  if (e_theta<=36) res_index_electron=0;
// 	  if (e_theta >36) res_index_electron=1;
// 	  if (ep.Theta()*DEG<=36) res_index_positron=0;
// 	  if (ep.Theta()*DEG >36) res_index_positron=1;
// 	  if (prot.Theta()*DEG<=36) res_index_proton=0;
// 	  if (prot.Theta()*DEG >36) res_index_proton=1;
	   
      }
      else if (detector=="SoLID_JPsi"){
	  //sim phi (-180,180)	
	  acc_prot_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(prot.Theta()*DEG,prot.P()));
	  acc_kp_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(kp.Theta()*DEG,kp.P()));	  
	  
	  acc_ep_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(ep.Theta()*DEG,ep.P()));	  
	  acc_em_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(em.Theta()*DEG,em.P()));	  
	
	  acc_prot_LA = hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(prot.Theta()*DEG,prot.P()));
	  acc_kp_LA = hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(kp.Theta()*DEG,kp.P()));	  
	  
	  acc_ep_LA = hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(ep.Theta()*DEG,ep.P()));  
	  acc_em_LA = hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(em.Theta()*DEG,em.P()));	
	   
	  acc_prot = acc_prot_FA+acc_prot_LA;
	  acc_kp= acc_kp_LA+acc_kp_FA;	  	  
	  acc_ep= acc_ep_LA+acc_ep_FA;
	  acc_em= acc_em_LA+acc_em_FA;
	  
	  //3fold_decaypairelectron
// 	  acc=acc_kp*acc_em*acc_ep;
// 	  if (acc_kp_FA>0 && acc_em_LA>0) acc=acc_kp_FA*acc_em_LA*acc_ep;
	  if (acc_kp_LA>0 && acc_em_FA>0) acc=acc_kp_LA*acc_em_FA*acc_ep;	  

	  //4fold
//  	  if (acc_kp_FA>0 && acc_em_LA>0) acc=acc_kp_FA*acc_em_LA*acc_ep*acc_prot;
// 	  if (acc_kp_LA>0 && acc_em_FA>0) acc=acc_kp_LA*acc_em_FA*acc_ep*acc_prot;	  
//  	  if (acc_kp_FA>0 && acc_em_LA>0) acc=acc_kp_FA*acc_em_LA*acc_ep*acc_prot_FA;
// 	  if (acc_kp_LA>0 && acc_em_FA>0) acc=acc_kp_LA*acc_em_FA*acc_ep*acc_prot_FA;	  

	  
// 	  acc=acc_prot*acc_ep*acc_kp*acc_em;	  
// 	  acc=acc_kp*acc_ep*acc_em;	  	  	  
// 	  acc=acc_prot*acc_ep*acc_em;	  	  	  	  
	  
// 	  if (acc_kp_FA>0 && acc_em_LA>0)  {acc=acc_kp_FA*acc_ep*acc_em_LA;}
// 	  if (acc_kp_LA>0 && acc_em_FA>0)  {
// 	    acc=acc_kp_LA*acc_ep*acc_em_FA;
// // 	    cout << kp.P() << " " << em.P() << endl;
// 	    TLorentzVector v_tmp=kp;
// 	    kp=em;
// 	    em=v_tmp;
// // 	    cout << em.P() << " " << kp.P() << endl;	    
// 	  }		  
	  
// 	  if (acc>0){
// 	    if (whichone==1) {counter1++; acc=0;}
// 	    else if (whichone==2) counter2++;
// 	    else if (whichone==3) counter3++;
// 	    else cout << "something wrong" << endl;
// 	  }
// 	  else {
// 	    if (whichone==4) counter4++;
// 	    else counter5++;
// 	  }
      }            
      else if (detector=="SoLID_DDVCS_JPsi"){
	  //sim phi (-180,180)	
	  acc_prot_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(prot.Theta()*DEG,prot.P()));
	  acc_kp_FA=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(kp.Theta()*DEG,kp.P()));	  
	  
	  acc_ep_FA=hacceptance_ThetaP_forwardangle_muon->GetBinContent(hacceptance_ThetaP_forwardangle_muon->FindBin(ep.Theta()*DEG,ep.P()));	  
	  acc_em_FA=hacceptance_ThetaP_forwardangle_muon->GetBinContent(hacceptance_ThetaP_forwardangle_muon->FindBin(em.Theta()*DEG,em.P()));	 
	
	  acc_prot_LA= hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(prot.Theta()*DEG,prot.P()));
	  acc_kp_LA= hacceptance_ThetaP_largeangle->GetBinContent(hacceptance_ThetaP_largeangle->FindBin(kp.Theta()*DEG,kp.P()));	  
	  
	  acc_ep_LA = hacceptance_ThetaP_largeangle_muon->GetBinContent(hacceptance_ThetaP_largeangle_muon->FindBin(ep.Theta()*DEG,ep.P()));  
	  acc_em_LA = hacceptance_ThetaP_largeangle_muon->GetBinContent(hacceptance_ThetaP_largeangle_muon->FindBin(em.Theta()*DEG,em.P()));	

	  acc_ep_barrel = hacceptance_ThetaP_barrel_muon->GetBinContent(hacceptance_ThetaP_barrel_muon->FindBin(ep.Theta()*DEG,ep.P()));  
	  acc_em_barrel = hacceptance_ThetaP_barrel_muon->GetBinContent(hacceptance_ThetaP_barrel_muon->FindBin(em.Theta()*DEG,em.P()));	
	  
	  acc_prot = acc_prot_FA+acc_prot_LA;
	  acc_kp= acc_kp_FA+acc_kp_LA;
 
	  if(evgen=="grape"){
// 	    acc_ep= acc_ep_FA+acc_ep_LA+acc_ep_barrel;
// 	    acc_em= acc_em_FA+acc_em_LA+acc_em_barrel;	
// 	    acc_ep= acc_ep_FA+acc_ep_LA;
// 	    acc_em= acc_em_FA+acc_em_LA;	
	    acc_ep= acc_ep_FA;
	    acc_em= acc_em_FA;
	    
//	     if (acc_ep_FA>0 && ep.P()>2) acc_ep=acc_ep_FA;
//	     if (acc_em_FA>0 && em.P()>2) acc_em=acc_em_FA;	    
//	     if (kp.Theta()*DEG <30 && kp.Theta()*DEG>7 && kp.P()>1) acc_kp=1;
//	     if (em.Theta()*DEG <50 && em.Theta()*DEG>7 && em.P()>1) acc_em=1;
//	     if (ep.Theta()*DEG <50 && ep.Theta()*DEG>7 && ep.P()>1) acc_ep=1;	    
	    
// 	    cout << "phi " << kp.Phi()*DEG << endl;
// 	    if (kp.Theta()*DEG <20 && kp.Theta()*DEG>5 && kp.P()>1) acc_kp=1;	    
// 	    if (kp.Theta()*DEG <20 && kp.Theta()*DEG>5 && kp.Phi()*DEG<20 && kp.Phi()*DEG>5 && kp.P()>1) acc_kp=1;
// 	    if (em.Theta()*DEG <30 && em.Theta()*DEG>7 && em.P()>1) acc_em=1;
// 	    if (ep.Theta()*DEG <50 && ep.Theta()*DEG>7 && ep.P()>1) acc_ep=1;	        
// 	    acc_ep=1;
// 	    acc_em=1;
	    
// 	    cout << kp.Theta()*DEG << " "  << endl;	    
// 	    if (kp.Theta()*DEG>5) acc_kp=1;
// 	    if (em.Theta()*DEG>5) acc_em=1;
// 	    if (ep.Theta()*DEG>5) acc_ep=1;
	    
// 	    cout << em.P() << " " << em.Pt() << endl;
// 	    acc_kp=1;
// 	    if (em.Theta()*DEG <160 && em.Theta()*DEG>20 && em.Pt()>2) acc_em=1; 
// 	    if (ep.Theta()*DEG <160 && ep.Theta()*DEG>20 && ep.Pt()>1.75) acc_ep=1;	    
	    
	  }    
	  else if(evgen=="twopeg"){
	    double acc_pim_FA_p,acc_pim_LA_p,acc_pim_barrel_p,acc_pip_FA_p,acc_pip_LA_p,acc_pip_barrel_p;
	    if(decaymode==0){ //decayno
	    acc_pip_FA_p = hacceptance_pion_FA->GetBinContent(hacceptance_pion_FA->FindBin(ep.P()));
	    acc_pip_LA_p = hacceptance_pion_LA->GetBinContent(hacceptance_pion_LA->FindBin(ep.P()));  	      
	    acc_pip_barrel_p = hacceptance_pion_barrel->GetBinContent(hacceptance_pion_barrel->FindBin(ep.P()));  	   
	    acc_pim_FA_p = hacceptance_pion_FA->GetBinContent(hacceptance_pion_FA->FindBin(em.P()));
	    acc_pim_LA_p = hacceptance_pion_LA->GetBinContent(hacceptance_pion_LA->FindBin(em.P()));  	      
	    acc_pim_barrel_p = hacceptance_pion_barrel->GetBinContent(hacceptance_pion_barrel->FindBin(em.P()));  	        
	    }
	    else if(decaymode==1){//decaypim
	    acc_pip_FA_p = hacceptance_pion_FA->GetBinContent(hacceptance_pion_FA->FindBin(ep.P()));
	    acc_pip_LA_p = hacceptance_pion_LA->GetBinContent(hacceptance_pion_LA->FindBin(ep.P()));  	      
	    acc_pip_barrel_p = hacceptance_pion_barrel->GetBinContent(hacceptance_pion_barrel->FindBin(ep.P()));  	   
	    acc_pim_FA_p = hacceptance_pion_FA_decay->GetBinContent(hacceptance_pion_FA_decay->FindBin(em.P()));
	    acc_pim_LA_p = hacceptance_pion_LA_decay->GetBinContent(hacceptance_pion_LA_decay->FindBin(em.P()));  	      
	    acc_pim_barrel_p = hacceptance_pion_barrel_decay->GetBinContent(hacceptance_pion_barrel_decay->FindBin(em.P()));  	
	    }
	    else if(decaymode==2){//decaypip
	    acc_pip_FA_p = hacceptance_pion_FA_decay->GetBinContent(hacceptance_pion_FA_decay->FindBin(ep.P()));
	    acc_pip_LA_p = hacceptance_pion_LA_decay->GetBinContent(hacceptance_pion_LA_decay->FindBin(ep.P()));  	      
	    acc_pip_barrel_p = hacceptance_pion_barrel_decay->GetBinContent(hacceptance_pion_barrel_decay->FindBin(ep.P()));  	
	    acc_pim_FA_p = hacceptance_pion_FA->GetBinContent(hacceptance_pion_FA->FindBin(em.P()));
	    acc_pim_LA_p = hacceptance_pion_LA->GetBinContent(hacceptance_pion_LA->FindBin(em.P()));  	      
	    acc_pim_barrel_p = hacceptance_pion_barrel->GetBinContent(hacceptance_pion_barrel->FindBin(em.P()));
	    }
	    else if(decaymode==3){//decayboth
	    acc_pip_FA_p = hacceptance_pion_FA_decay->GetBinContent(hacceptance_pion_FA_decay->FindBin(ep.P()));
	    acc_pip_LA_p = hacceptance_pion_LA_decay->GetBinContent(hacceptance_pion_LA_decay->FindBin(ep.P()));  	      
	    acc_pip_barrel_p = hacceptance_pion_barrel_decay->GetBinContent(hacceptance_pion_barrel_decay->FindBin(ep.P()));  	
	    acc_pim_FA_p = hacceptance_pion_FA_decay->GetBinContent(hacceptance_pion_FA_decay->FindBin(em.P()));
	    acc_pim_LA_p = hacceptance_pion_LA_decay->GetBinContent(hacceptance_pion_LA_decay->FindBin(em.P()));  	      
	    acc_pim_barrel_p = hacceptance_pion_barrel_decay->GetBinContent(hacceptance_pion_barrel_decay->FindBin(em.P()));  	
	    }
	    else {cout << "wrong decay mode" << endl; return;}

// 	    acc_ep= acc_ep_FA*acc_pip_FA_p+acc_ep_LA*acc_pip_LA_p+acc_ep_barrel*acc_pip_barrel_p;
// 	    acc_em= acc_em_FA*acc_pim_FA_p+acc_em_LA*acc_pim_LA_p+acc_em_barrel*acc_pim_barrel_p;
	    acc_ep= acc_ep_FA*acc_pip_FA_p;
	    acc_em= acc_em_FA*acc_pim_FA_p;
// 	    acc_ep= acc_ep_LA+acc_ep_FA+acc_ep_barrel;
// 	    acc_em= acc_em_LA+acc_em_FA+acc_em_barrel;	
	  }	
	  else {cout << "not supported evgen " << evgen << endl; return;}

// 	  cout << acc_kp << " " << acc_ep << " " << acc_em << " " << endl;
	  
	  //cut 60 deg to form LA300
// 	  if (-120<ep.Phi()*DEG && ep.Phi()*DEG<-60) acc_ep_LA=0;
// 	  if (-120<em.Phi()*DEG && em.Phi()*DEG<-60) acc_em_LA=0;
	  
// 	  acc_ep= acc_ep_FA;
// 	  acc_em= acc_em_FA;		  
// 	  acc_ep= acc_ep_LA;
// 	  acc_em= acc_em_LA;		  
	  
	  //for barrel muon 
// 	  if (ep.P()>=1 && (28<=ep.Theta()*DEG && ep.Theta()*DEG <45)) acc_ep=1;	  
// 	  if (em.P()>=1 && (28<=em.Theta()*DEG && em.Theta()*DEG <45)) acc_em=1;
// 	  if (ep.P()>=1 && (28<=ep.Theta()*DEG && ep.Theta()*DEG <70)) acc_ep=1;	  
// 	  if (em.P()>=1 && (28<=em.Theta()*DEG && em.Theta()*DEG <70)) acc_em=1;
	  
	  //for 22gev beam
// 	  if (prot.P()>=11 && (8<=prot.Theta()*DEG && prot.Theta()*DEG <28)) acc_prot=1;
// 	  if (kp.P()>=11 && (8<=kp.Theta()*DEG && kp.Theta()*DEG <28)) acc_kp=1;
// 	  if (em.P()>=11 && (8<=em.Theta()*DEG && em.Theta()*DEG <28)) acc_em=1;
// 	  if (ep.P()>=11 && (8<=ep.Theta()*DEG && ep.Theta()*DEG <28)) acc_ep=1;	  
// 	  if (prot.P()>=11 && (8<=prot.Theta()*DEG && prot.Theta()*DEG <28)) acc_prot=1;
// 	  if (kp.P()>=11 && (8<=kp.Theta()*DEG && kp.Theta()*DEG <28)) acc_kp=1;
// 	  if (em.P()>=11 && (8<=em.Theta()*DEG && em.Theta()*DEG <70)) acc_em=1;
// 	  if (ep.P()>=11 && (8<=ep.Theta()*DEG && ep.Theta()*DEG <70)) acc_ep=1;	  

// 	  acc=acc_kp*acc_ep*acc_em*acc_prot;	  
	  acc=acc_kp*acc_ep*acc_em;
// 	  acc=acc_ep*acc_em*acc_prot;
	  
// 	  acc=acc_prot*acc_ep*acc_kp*acc_em;	  
// 	  acc=acc_prot*acc_ep*acc_em;	  	  	  	  
	  
// 	  if (acc>0){
// 	    if (whichone==1) {counter1++; acc=0;}
// 	    else if (whichone==2) counter2++;
// 	    else if (whichone==3) counter3++;
// 	    else cout << "something wrong" << endl;
// 	  }
// 	  else {
// 	    if (whichone==4) counter4++;
// 	    else counter5++;
// 	  }
      }      
      else if (detector=="SoLID_DDVCS_PVDIS"){
	  //sim phi (-180,180)	

// 	  acc_prot=0;
// 	  acc_prot=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(prot.Theta()*DEG,prot.P()));	  
// 	  if (22<prot.Theta()*DEG && prot.Theta()*DEG<35) acc_prot=1;	
	

	  acc_kp=hacceptance_ThetaP_forwardangle->GetBinContent(hacceptance_ThetaP_forwardangle->FindBin(kp.Theta()*DEG,kp.P()));	  

// 	  acc_ep_FA=hacceptance_ThetaP_forwardangle_muonp->GetBinContent(hacceptance_ThetaP_forwardangle_muonp->FindBin(ep.Theta()*DEG,ep.P()));	
// 	  acc_em_FA=hacceptance_ThetaP_forwardangle_muonm->GetBinContent(hacceptance_ThetaP_forwardangle_muonm->FindBin(em.Theta()*DEG,em.P()));	

	  if (ep.P()>=1 && (22<=ep.Theta()*DEG && ep.Theta()*DEG <35)) acc_ep_FA=1;	  	  
	  if (em.P()>=1 && (22<=em.Theta()*DEG && em.Theta()*DEG <35)) acc_em_FA=1;
	  
	  acc_ep= acc_ep_FA;
	  acc_em= acc_em_FA;	  
	  
// 	  if (22<ep.Theta()*DEG && ep.Theta()*DEG<35) acc_ep=1;
// 	  if (22<em.Theta()*DEG && em.Theta()*DEG<35) acc_em=1;
	  
// 	  	cout << acc_kp << "\t" << acc_ep << "\t" << acc_em << endl;
		
// 	  acc=acc_prot*acc_ep*acc_kp*acc_em;	  
	  acc=acc_kp;	  
// 	  acc=acc_kp*acc_ep*acc_em;	  	  	  
// 	  	  acc=acc_ep*acc_em;	  	  	  
// 	  	  acc=acc_prot;	  	  	  	  
// 	  acc=acc_prot*acc_ep*acc_em;	  	  	  	  
	  
      }     
      else if (detector == "JLEIC"){
	if(5<ep.Theta()*DEG && ep.Theta()*DEG<175) acc_ep=1;
	if(5<em.Theta()*DEG && em.Theta()*DEG<175) acc_em=1;	
	acc=acc_ep*acc_em;
	
// 	if(5<ep.Theta()*DEG && ep.Theta()*DEG<175) acc_ep=1;
// 	if(5<em.Theta()*DEG && em.Theta()*DEG<175) acc_em=1;
// 	if(5<kp.Theta()*DEG && kp.Theta()*DEG<175) acc_kp=1;		
// 	acc=acc_ep*acc_em*acc_kp;	
      }
      else {cout << "wrong detector" << endl;}

      
//=== get resolution from tracking and apply it ==========================
/* Get resolution to res: p/GeV, theta/Deg, phi/Deg, vertexz/cm
  Kinematic variables kin: p/GeV, theta/Deg, phi/Deg
  Particle: e+(1), e-(-1), mu+(2), mu-(-2), pi+(3), pi-(-3), K+(4), K-(-4), p(5). Default with e-(-1)
  Return O:normal, 1:error */    
if (Is_res &&  acc>0){
//     Lresolution track("JPsi");
    double new_p,new_theta,new_phi;    
    double kin[3];
    double res[4];
    double res_factor=1;
    
    //scattered electron
    kin[0]=kp.P();
    kin[1]=kp.Theta()*DEG;
    kin[2]=kp.Phi()*DEG;
//       cout << "begin" << endl;
//       cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
    if (track.GetResolution(kin,res,"e-")) {
      cout << "e-" << endl;            
      cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
      cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << endl;  
    }
    new_p=rnd.Gaus(kin[0],res_factor*kin[0]*res[0]);
    new_theta=rnd.Gaus(kin[1],res_factor*res[1]);
    new_phi=rnd.Gaus(kin[2],res_factor*res[2]);
    hnew_p[0]->Fill(new_p/kin[0]-1);
    hnew_theta[0]->Fill(new_theta-kin[1]);
    hnew_phi[0]->Fill(new_phi-kin[2]);    
//       cout << new_p << " " << new_theta << " " << new_phi << endl;            
    kp.SetXYZM(new_p*sin(new_theta/DEG)*cos(new_phi/DEG),new_p*sin(new_theta/DEG)*sin(new_phi/DEG),new_p*cos(new_theta/DEG),kp.M());
//       cout << kp.P() << " " << kp.Theta()*DEG << " " << kp.Phi()*DEG << endl;    
//       cout << "end" << endl;   
    res[0]=0;    res[1]=0;    res[2]=0;    res[3]=0;    
    
    //recoil proton
    kin[0]=prot.P();
    kin[1]=prot.Theta()*DEG;
    kin[2]=prot.Phi()*DEG;
//       cout << "begin" << endl;
//       cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
    if (track.GetResolution(kin,res,"p")) {
      cout << "p" << endl;      
      cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
      cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << endl;  
    }
    new_p=rnd.Gaus(kin[0],res_factor*kin[0]*res[0]);
    new_theta=rnd.Gaus(kin[1],res_factor*res[1]);
    new_phi=rnd.Gaus(kin[2],res_factor*res[2]);
    hnew_p[1]->Fill(new_p/kin[0]-1);
    hnew_theta[1]->Fill(new_theta-kin[1]);
    hnew_phi[1]->Fill(new_phi-kin[2]);        
//       cout << new_p << " " << new_theta << " " << new_phi << endl;            
    prot.SetXYZM(new_p*sin(new_theta/DEG)*cos(new_phi/DEG),new_p*sin(new_theta/DEG)*sin(new_phi/DEG),new_p*cos(new_theta/DEG),prot.M());
//       cout << prot.P() << " " << prot.Theta()*DEG << " " << prot.Phi()*DEG << endl;    
//       cout << "end" << endl;   
    res[0]=0;    res[1]=0;    res[2]=0;    res[3]=0;
    
     //decay neg
    kin[0]=em.P();
    kin[1]=em.Theta()*DEG;
    kin[2]=em.Phi()*DEG;
//       cout << "begin" << endl;
//       cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
    if (track.GetResolution(kin,res,Form("%s-",decaypair.c_str()))) {
      cout << Form("%s-",decaypair.c_str())<< endl;
      cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
      cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << endl;  
    }
    new_p=rnd.Gaus(kin[0],res_factor*kin[0]*res[0]);
    new_theta=rnd.Gaus(kin[1],res_factor*res[1]);
    new_phi=rnd.Gaus(kin[2],res_factor*res[2]);
    hnew_p[2]->Fill(new_p/kin[0]-1);
    hnew_theta[2]->Fill(new_theta-kin[1]);
    hnew_phi[2]->Fill(new_phi-kin[2]);        
//       cout << new_p << " " << new_theta << " " << new_phi << endl;            
    em.SetXYZM(new_p*sin(new_theta/DEG)*cos(new_phi/DEG),new_p*sin(new_theta/DEG)*sin(new_phi/DEG),new_p*cos(new_theta/DEG),em.M());
//       cout << em.P() << " " << em.Theta()*DEG << " " << em.Phi()*DEG << endl;    
//       cout << "end" << endl;   
    res[0]=0;    res[1]=0;    res[2]=0;    res[3]=0;
    
    //decay pos
    kin[0]=ep.P();
    kin[1]=ep.Theta()*DEG;
    kin[2]=ep.Phi()*DEG;
//       cout << "begin" << endl;
//       cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
    if (track.GetResolution(kin,res,Form("%s+",decaypair.c_str()))) {
      cout << Form("%s+",decaypair.c_str())<< endl;
      cout << kin[0] << " " << kin[1] << " " << kin[2] << endl;    
      cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << endl;  
    }
    new_p=rnd.Gaus(kin[0],res_factor*kin[0]*res[0]);
    new_theta=rnd.Gaus(kin[1],res_factor*res[1]);
    new_phi=rnd.Gaus(kin[2],res_factor*res[2]);
    hnew_p[3]->Fill(new_p/kin[0]-1);
    hnew_theta[3]->Fill(new_theta-kin[1]);
    hnew_phi[3]->Fill(new_phi-kin[2]);        
//       cout << new_p << " " << new_theta << " " << new_phi << endl;            
    ep.SetXYZM(new_p*sin(new_theta/DEG)*cos(new_phi/DEG),new_p*sin(new_theta/DEG)*sin(new_phi/DEG),new_p*cos(new_theta/DEG),ep.M());
//       cout << ep.P() << " " << ep.Theta()*DEG << " " << ep.Phi()*DEG << endl;    
//       cout << "end" << endl;   
    res[0]=0;    res[1]=0;    res[2]=0;    res[3]=0;
    
}
    
// =========end of get resolution ==========================================     
    
    double MM=(ki+targ-kp-ep-em).M();
    
    double InvM_epm1=(ep+em).M();
    double InvM_epm2=(ep+kp).M();	
    double Qp2=InvM_epm1*InvM_epm1;  
    
//     if (InvM_epm1<0.2) {
//       cout << "strange " << MM << "\t" << InvM_epm1 << "\t" << InvM_epm2 << endl;
//       cout << ki.M() << "\t" << ki.Px() << "\t" << ki.Py() << "\t" << ki.Pz() << "\t" << ki.P() << "\t" << ki.E() << endl;
//       cout << targ.M() << "\t" << targ.Px() << "\t" << targ.Py() << "\t" << targ.Pz() << "\t" << targ.P() << "\t" << targ.E() << endl;      
//       cout << prot.M() << "\t" << prot.Px() << "\t" << prot.Py() << "\t" << prot.Pz() << "\t" << prot.P() << "\t" << prot.E() << endl;
//       cout << kp.M() << "\t" << kp.Px() << "\t" << kp.Py() << "\t" << kp.Pz() << "\t" << kp.P() << "\t" << kp.E() << endl;
//       cout << ep.M() << "\t" << ep.Px() << "\t" << ep.Py() << "\t" << ep.Pz() << "\t" << ep.P() << "\t" << ep.E() << endl;
//       cout << em.M() << "\t" << em.Px() << "\t" << em.Py() << "\t" << em.Pz() << "\t" << em.P() << "\t" << em.E() << endl; 
//       cout << (ep+em).M() << "\t" << (ep+em).Px() << "\t" << (ep+em).Py() << "\t" << (ep+em).Pz() << "\t" << (ep+em).P() << "\t" << (ep+em).E() << endl; 
//     }
      
    double Q2=-(ki-kp).M2();
    double W=(ki-kp+targ).M();
//         double W=(prot+ep+em).M();    
    //     double xbj=Q2/2/(ki*(ep+em)); ///wrong !!!!!!!
    double xbj=Q2/2./(targ*(ki-kp));
    
//     if(i<3) cout << " W " << W <<" Q2 " << Q2 << endl; 
   
    double t=(prot-targ).M2();
    double delta2=t;    
    double m1=(ki-kp).M(),m2=targ.M(),m3=3.097,m4=prot.M();
    double s=W*W;
    
    double E1cm=(s+m1*m1-m2*m2)/(2*sqrt(s)),E3cm=(s+m3*m3-m4*m4)/(2*sqrt(s));
    double p1cm=sqrt(E1cm*E1cm-m1*m1),p3cm=sqrt(E3cm*E3cm-m3*m3);
    double tmin= -(pow(E1cm-E3cm,2) - pow(p1cm-p3cm,2));
    double tmax= -(pow(E1cm-E3cm,2) - pow(p1cm+p3cm,2));    
    
//      double tau=Qp2*Qp2/(s-targ.M()*targ.M());
//       double eta=tau/(2-tau);   
//       double eta=Qp2/(2*s-2*M*M-Qp2);   //       tau/(2-tau)=Qp2/(2*s-2*M*M-Qp2)
//       double eta=Qp2/(2*(s-M*M)-Qp2-t);  //this is detailed defination  
//      double eta=Qp2/(2*s-Qp2);       //eta in TCS is similar to xi in DVCS 

         //according to ???
//      double xi=(Q2-Qp2+delta2/2.)/(2.*Q2/xbj-Q2-Qp2+delta2);
//      double eta=-(Q2+Qp2)/(2.*Q2/xbj-Q2-Qp2+delta2);     
     //according to e+ DDVCS paper
     double xi=(Q2+Qp2)/(2.*Q2/xbj-Q2-Qp2+delta2);     
     double xip=(Q2-Qp2+delta2/2.)/(2.*Q2/xbj-Q2-Qp2+delta2);
      
// cout << W << endl;
// cout << (kp+prot+ep+em).P() <<  " " << (kp+prot+ep+em).Theta() << endl;

    TLorentzVector LV_Recoil_lab=prot,LV_minus_lab=em,LV_plus_lab=ep,LV_el_in=ki,LV_el_out=kp;

    //incoming virtual photon,outgoing virtual photon and recoil proton are all on the same hadron plane
    //phi angle is from lepton plane to recoil proton, kinda like trento convention for SIDIS at PhysRevD.70.117504 which has phi angle from lepton plane to outgoing hadron
    TVector3 Tang_plane_lab=((LV_minus_lab+LV_plus_lab).Vect().Unit()).Cross((LV_Recoil_lab.Vect().Unit())).Unit();    
    TVector3 Tang_el=((LV_el_in.Vect().Unit()).Cross(LV_el_out.Vect().Unit())).Unit();	
    double Phi_LH= TMath::ACos(Tang_el*Tang_plane_lab); //same result as Tang_el.Angle(Tang_plane_lab)
    if ((Tang_el*(LV_minus_lab+LV_plus_lab).Vect())>0.)Phi_LH=2*TMath::Pi()-Phi_LH;

// phi angle is from lepton plane to outgoing virtual photon, like Belitsky PhysRevD.68.116005, differ by pi than the one above
//     TVector3 Tang_plane_lab=((LV_Recoil_lab.Vect().Unit()).Cross((LV_minus_lab+LV_plus_lab).Vect().Unit())).Unit();
//     TVector3 Tang_el=((LV_el_in.Vect().Unit()).Cross(LV_el_out.Vect().Unit())).Unit();	
//     double Phi_LH= TMath::ACos(Tang_el*Tang_plane_lab);
//     if ((Tang_el*(LV_minus_lab+LV_plus_lab).Vect())<0.)Phi_LH=2*TMath::Pi()-Phi_LH;

    //     cout << " Phi_LH " <<  Tang_el.Angle(Tang_plane_lab) << " " << Phi_LH << endl;
		
    TLorentzVector LV_gamma_lab=LV_minus_lab+LV_plus_lab;    
    TLorentzVector LV_plus_CMV=LV_plus_lab;
    LV_plus_CMV.Boost(-LV_gamma_lab.BoostVector());
    TLorentzVector LV_minus_CMV=LV_minus_lab;
    LV_minus_CMV.Boost(-LV_gamma_lab.BoostVector());

//     cout << "CMV " << LV_minus_CMV.Theta()*DEG << " " << 180-LV_plus_CMV.Theta()*DEG << " " << LV_minus_CMV.Phi()*DEG << " " << LV_plus_CMV.Phi()*DEG << endl;
    
    double Theta_CMV=LV_minus_CMV.Theta()*DEG;
    double Phi_CMV=LV_minus_CMV.Phi()*DEG;
    if (Phi_CMV<0) Phi_CMV=360+Phi_CMV;
           
// 4 Xbj (0.1-0.4), 6 tt (0.1-0.8), 6 Q^{2}(1-7), 6 Qp2 (2-9), 8 Phi_LH (0-2pi), 6 Theta_CMV(45-135),8 Phi_CMV(0-2pi),

    //scatPhiBool = TMath::Abs(kp.Phi()/D2R) < 40. && (TMath::Abs(prot.Phi()/D2R) < 30.);

    //scatPhiBool = TMath::Abs(kp.Phi()/D2R) < 40. && (TMath::Abs(prot.Phi()/D2R) > 150.);

    //scat_e_calo = ep.Angle(ki.Vect())/D2R < 45. && ep.Angle(ki.Vect())/D2R > 10.0 && em.Angle(ki.Vect())/D2R < 45. && em.Angle(ki.Vect())/D2R > 10.0;

    //   cout << em.Angle(ki.Vect())/D2R << endl;

//    if(scatPhiBool && scat_e_calo){

  //    if(kp.Angle(prot.Vect())/D2R > 25. || kp.Angle(prot.Vect())/D2R < 10.){
//	cout << "bad" << endl;
//      }

//      prot.RotateZ(pi1);

      //  hang_dist_scat_e->Fill(-(180.0 -kp.Theta()/D2R), kp.Phi()/D2R);
      //  hang_dist_scat_p->Fill(180.0 - prot.Theta()/D2R, prot.Phi()/D2R);

   // h2 is solid forward angle acceptance, h3 is largeangle
// 	double accet_cut=0;
// 	bool kp_accept_forwardangle=h2_acc->GetBinContent(h2_acc->FindBin(kp.Theta()/D2R,kp.P())) > accet_cut;
// 	bool kp_accept_largeangle=h3_acc->GetBinContent(h3_acc->FindBin(kp.Theta()/D2R,kp.P())) > accet_cut;	
// 	bool ep_accept_forwardangle=h2_acc->GetBinContent(h2_acc->FindBin(ep.Theta()/D2R,ep.P())) > accet_cut;
// 	bool ep_accept_largeangle=h3_acc->GetBinContent(h3_acc->FindBin(ep.Theta()/D2R,ep.P())) > accet_cut;
// 	bool em_accept_forwardangle=h2_acc->GetBinContent(h2_acc->FindBin(em.Theta()/D2R,em.P())) > accet_cut;
// 	bool em_accept_largeangle=h3_acc->GetBinContent(h3_acc->FindBin(em.Theta()/D2R,em.P())) > accet_cut;
// 	bool prot_accept_forwardangle=h2_acc->GetBinContent(h2_acc->FindBin(prot.Theta()/D2R,prot.P())) > accet_cut;
// 	bool prot_accept_largeangle=h3_acc->GetBinContent(h3_acc->FindBin(prot.Theta()/D2R,prot.P())) > accet_cut;	

// 	bool triggercut = true;
// 	if ((ep_accept_largeangle && ep.P() < 2.5) || (em_accept_largeangle && em.P() < 2.5) || (kp_accept_largeangle && kp.P() < 2.5)) triggercut=false;
// 
// 	    bool othercut= W < 4.44;
// 	    
// 	    bool cut=false;
// 	  if (conf_validation && ( (kp_accept_forwardangle || kp_accept_largeangle) && (ep_accept_forwardangle || ep_accept_largeangle) && (em_accept_forwardangle || em_accept_largeangle))) cut=true;
// 	  if (conf_4fold && (kp_accept_forwardangle && (ep_accept_forwardangle || ep_accept_largeangle) && (em_accept_forwardangle || em_accept_largeangle) && prot_accept_forwardangle) && othercut)  cut=true;
// 	  if (conf_3fold_NOp && (kp_accept_forwardangle && (ep_accept_forwardangle || ep_accept_largeangle) && (em_accept_forwardangle || em_accept_largeangle)) && othercut) cut=true;
// 	  if (conf_3fold_NOe && ((ep_accept_forwardangle || ep_accept_largeangle) && (em_accept_forwardangle || em_accept_largeangle) && prot_accept_forwardangle) && othercut) cut=true;
    
//     if (fabs(xbj-0.1)<0.05 && fabs(-t-0.45)<0.1 && fabs(Q2-1.5)<0.1 && fabs(Qp2-4)<0.1){
// //     cout << "bin " << xbj << " " << -t << " " << Q2 << " " << Qp2  << " " << Phi_LH << " " << Theta_CMV  << " " << Phi_CMV << endl;     
//     xsec_thisbin += acc*effxsec;    
// //       if(fabs(Phi_LH-1)<0.05 && fabs(Theta_CMV-30)<10 && fabs(Phi_CMV-30)<10) xsec_thisbin++;    
//     }
      
//       weight[0]=effxsec*count_convert;
      weight[0]=effxsec;
      weight[1]=acc;
      weight[2]=acc*effxsec;
      weight[3]=acc*effxsec*count_convert;
//       weight[3]=effxsec*(0.05<Q2 && Q2<10)*(2<Qp2 && Qp2<10)*(-1.2<t && t<0)*(0.001<xi && xi<0.7);
//       weight[4]=acc*effxsec*count_convert*(-t<Q2); //-t<Q2+Q'2 factorization condition is better      
      weight[4]=acc*effxsec*count_convert*(-t<Q2+Qp2); //-t<Q2+Q'2 factorization condition is better      
//       weight[4]=acc*effxsec*count_convert*(1<InvM_epm1 && InvM_epm1<3);      
//       weight[4]=acc*effxsec*count_convert*(1<InvM_epm1);
//       weight[4]=acc*effxsec*count_convert*(W>2 && 0.05<Q2 && Q2<10 && 1e-4<-t && -t<1);
      
      
//      if (Q2<1) continue;     
//      if (Qp2<1) continue;          
//      if (Q2<Qp2) continue;     
//      if (W>3) continue;          
     
// 	if ( 3 < Qp2 && Qp2 < 9 ) {      
// 	if (3.0 < InvM_epm1 && InvM_epm1 < 3.25) || (Is_inter && (3.0 < InvM_epm2 && InvM_epm2 < 3.25)) ) {
      
	for(Int_t k=0; k < m; k++){  
	  if(k>0 && acc==0) continue;
	  
	  ht_Qp2_xip[k]->Fill(xip,Qp2,-t,weight[k]);
	  hQp2_xip[k]->Fill(xip,Qp2,weight[k]);
	  hQp2_t[k]->Fill(-t,Qp2,weight[k]);
	  
	  hThetaP[0][k]->Fill(kp.Theta()*DEG,kp.P(),weight[k]);
	  hThetaP[1][k]->Fill(prot.Theta()*DEG,prot.P(),weight[k]);	
	  hThetaP[2][k]->Fill(em.Theta()*DEG,em.P(),weight[k]);
	  hThetaP[3][k]->Fill(ep.Theta()*DEG,ep.P(),weight[k]);

	  hThetaPhi[0][k]->Fill(kp.Theta()*DEG,kp.Phi()*DEG,weight[k]);
	  hThetaPhi[1][k]->Fill(prot.Theta()*DEG,prot.Phi()*DEG,weight[k]);	
	  hThetaPhi[2][k]->Fill(em.Theta()*DEG,em.Phi()*DEG,weight[k]);
	  hThetaPhi[3][k]->Fill(ep.Theta()*DEG,ep.Phi()*DEG,weight[k]);

	  hdecayangle1_phi[k]->Fill(ep.Phi()*DEG,em.Phi()*DEG,weight[k]);
	  hdecayangle2_phi[k]->Fill(ep.Phi()*DEG,kp.Phi()*DEG,weight[k]);
	  hdecayangle3_phi[k]->Fill(em.Phi()*DEG,kp.Phi()*DEG,weight[k]);		
	  
	  hdecayangle1_theta[k]->Fill(ep.Theta()*DEG,em.Theta()*DEG,weight[k]);
	  hdecayangle2_theta[k]->Fill(ep.Theta()*DEG,kp.Theta()*DEG,weight[k]);
	  hdecayangle3_theta[k]->Fill(em.Theta()*DEG,kp.Theta()*DEG,weight[k]);			
	  
	  hdecayangle1_thetaphi[k]->Fill(ep.Phi()/fabs(ep.Phi())*ep.Theta()*DEG*180+ep.Phi()*DEG,em.Phi()/fabs(em.Phi())*em.Theta()*DEG*180+em.Phi()*DEG,weight[k]);
	  hdecayangle2_thetaphi[k]->Fill(ep.Phi()/fabs(ep.Phi())*ep.Theta()*DEG*180+ep.Phi()*DEG,kp.Phi()/fabs(kp.Phi())*kp.Theta()*DEG*180+kp.Phi()*DEG,weight[k]);
	  hdecayangle3_thetaphi[k]->Fill(em.Phi()/fabs(em.Phi())*em.Theta()*DEG*180+em.Phi()*DEG,kp.Phi()/fabs(kp.Phi())*kp.Theta()*DEG*180+kp.Phi()*DEG,weight[k]);
	  
  // 	if (Is_inter) hdecayangle2[k]->Fill(ep.Theta()*DEG,kp.Theta()*DEG,weight[k]);	

	  hdecaymom1[k]->Fill(ep.P(),em.P(),weight[k]);
	  hdecaymom2[k]->Fill(ep.P(),kp.P(),weight[k]);		
  // 	if (Is_inter) hdecaymom2[k]->Fill(ep.P(),kp.P(),weight[k]);	
	  
	  hlepIM_2D[k]->Fill(InvM_epm1,InvM_epm2,weight[k]);
	  
	  hlepIM1[k]->Fill(InvM_epm1,weight[k]);
	  hlepIM2[k]->Fill(InvM_epm2,weight[k]);		
	  hlepIM[k]->Fill(InvM_epm1,weight[k]);
	  hlepIM[k]->Fill(InvM_epm2,weight[k]);

	  hlepIM1_error[k]->Fill(InvM_epm1,weight[k]);
	  hlepIM2_error[k]->Fill(InvM_epm2,weight[k]);		
	  hlepIM_error[k]->Fill(InvM_epm1,weight[k]);
	  hlepIM_error[k]->Fill(InvM_epm2,weight[k]);
	  
  // 	if (whichone==2) hlepIM[k]->Fill(InvM_epm1,weight[k]);
  // 	else if (whichone==3) hlepIM[k]->Fill(InvM_epm2,weight[k]);
	}
	  
 	  if (acc_ep_FA>0) hPlog_plus_FA->Fill(log10(ep.P()),weight[2]*rate_convert/1e3);	  
 	  if (acc_em_FA>0) hPlog_minus_FA->Fill(log10(em.P()),weight[2]*rate_convert/1e3);
 	  if (acc_ep_LA>0) hPlog_plus_LA->Fill(log10(ep.P()),weight[2]*rate_convert/1e3);	  
	  if (acc_em_LA>0) hPlog_minus_LA->Fill(log10(em.P()),weight[2]*rate_convert/1e3);
      
	  hW->Fill(W,weight[windex]);	  
	  hWstat->Fill(W,weight[windex]);	    
	  htmin_W->Fill(W,tmin,weight[windex]);    
	  htmax_W->Fill(W,tmax,weight[windex]);
	  ht->Fill(-t,weight[windex]);	  
	  
	  ht_Q2Qp2->Fill(-t,Q2+Qp2,weight[windex]);
	  ht_Qp2->Fill(-t,Qp2,weight[windex]);
	  ht_W->Fill(-t,W,weight[windex]);
	  hQ2_W->Fill(Q2,W,weight[windex]);	  
	  ht_Q2->Fill(-t,Q2,weight[windex]);    	  	  
	  ht_xip->Fill(-t,xip,weight[windex]);  
	  ht_xi->Fill(-t,xi,weight[windex]);	  
	  hxip_xi->Fill(xip,xi,weight[windex]);  
	  hxbj_xip->Fill(xbj,xip,weight[windex]);  
	  hxbj_xi->Fill(xbj,xi,weight[windex]);
	  hxbj_Q2->Fill(xbj,Q2,weight[windex]);
	  hQ2_Qp2->Fill(Q2,Qp2,weight[windex]);

// 	  cout << "MM " << MM << endl;
	  hMM->Fill(MM,weight[windex]);	  	  
	  hMM_Q2->Fill(MM,Q2,weight[windex]);		  
	  hMM_Qp2->Fill(MM,Qp2,weight[windex]);	
	  hMM_t->Fill(MM,-t,weight[windex]);
	  
	  //bin data as positron EPJA paper
// 	    if(abs(xi-0.135)<0.015 && abs(-t-0.25)<0.05){
// 	      if(abs(xip+0.06)<0.03 && abs(Q2-1.25)<0.25) {hcount1->Fill(Phi_LH*DEG,weight[windex]);}
// 	      if(abs(xip-0.075)<0.015 && abs(Q2-1.25)<0.25) {hcount2->Fill(Phi_LH*DEG,weight[windex]);}
// 	      if(abs(xip-0.075)<0.015 && abs(Q2-1.875)<0.375) {hcount3->Fill(Phi_LH*DEG,weight[windex]);}
// // 	      cout << "range " << xip << " " << Q2 << " " << InvM_epm1<<endl;
// 	    }

// 	    if(abs(xi-0.135)<0.015 && abs(-t-0.25)<0.05){
// 	      if(abs(xip+0.06)<0.03 && abs(Q2-1.25)<0.25) {hcount[0]->Fill(Phi_LH*DEG,weight[windex]);}
// 	      if(abs(xip-0.075)<0.05 && abs(Q2-2.5)<1) {hcount[1]->Fill(Phi_LH*DEG,weight[windex]);}
// // 	      cout << "range " << xip << " " << Q2 << " " << InvM_epm1<<endl;
// 	    }
	  
	    if(Qp2>2 && Q2+Qp2>1 && W>2) hcount[0]->Fill(Phi_LH*DEG,weight[windex]);
	  
// 	    if (weight[windex]>0) hcount[0]->Fill(Phi_LH*DEG,weight[windex]);

// 	    if(0<=xi && xi<0.05) && (0<=-t && -t<0.1){
// 	      hxip_Q2[0]->Fill(xip,Q2,weight[windex]);	
// 	    }
// 	    else if(0.05<=xi && xi<0.1) && (0.1<=-t && -t<0.2){
// 	      hxip_Q2[1]->Fill(xip,Q2,weight[windex]);	
// 	    }
// 	    else if(0.1<=xi && xi<0.15) && (0.2<=-t && -t<0.4){
// 	      hxip_Q2[1]->Fill(xip,Q2,weight[windex]);	
// 	    }
// 	    else if(0.2<=xi && xi<0.2) && (0.2<=-t && -t<0.4){
// 	      hxip_Q2[1]->Fill(xip,Q2,weight[windex]);	
// 	    }
	    
	  //      hkpth->Fill(180.0 -kp.Theta()/D2R, effxsec);
	  //   hprth->Fill(180.0 -prot.Theta()/D2R, effxsec);
// 	  hkpth->Fill(kp.Theta()/D2R, effxsec);
// 	  hprth->Fill(prot.Theta()/D2R, effxsec);
// 
// 	  hkpph->Fill(kp.Phi()/D2R, effxsec);
// 	  hprph->Fill(prot.Phi()/D2R, effxsec);
// 	  hkpp->Fill(kp.Vect().Mag(), effxsec);
// 	  hprp->Fill(prot.Vect().Mag(), effxsec);
// 
// 	  hepscat->Fill(sin(ep.Theta())*cos(ep.Phi()), sin(ep.Theta())*sin(ep.Phi()));
// 	  hemscat->Fill(sin(em.Theta())*cos(em.Phi()), sin(em.Theta())*sin(em.Phi()));   
 
  }//end of looping events
  
  cout << "counter " << counter1 << " " << counter2 << " " << counter3 << " " << counter4 << " " << counter5 << " " << counter6 <<  endl;

//   cout << "xsec_thisbin " << xsec_thisbin << endl;
  
  TCanvas *c_ThetaP = new TCanvas("ThetaP","ThetaP",1200,900);
  c_ThetaP->Divide(4,m);
  for(int k=0;k<m;k++){
    for(int l=0;l<4;l++){
      c_ThetaP->cd(k*4+l+1);
      hThetaP[l][k]->Draw("colz");
      hThetaP[l][k]->SetAxisRange(thetamin,thetamax,"X");      
      gPad->SetLogz(1);      
    }
  }
  
  TCanvas *c_ThetaP_final = new TCanvas("ThetaP_final","ThetaP_final",1200,900);
  c_ThetaP_final->Divide(2,2);
    for(int l=0;l<4;l++){
      c_ThetaP_final->cd(l+1);
      gPad->SetLogz(1);      
      hThetaP[l][windex]->Draw("colz");
      hThetaP[l][windex]->SetAxisRange(thetamin,thetamax,"X");
      cout << hThetaP[l][windex]->Integral() << endl;
    }
  c_ThetaP_final->SaveAs(Form("%s/ThetaP_final.png",input_filedir.c_str()));
  c_ThetaP_final->SaveAs(Form("%s/ThetaP_final.pdf",input_filedir.c_str()));      
  
  TCanvas *c_Plog = new TCanvas("Plog","Plog",1200,900);
  c_Plog->Divide(2,2);
  c_Plog->cd(1);  
  gPad->SetLogy(1);
  hPlog_plus_FA->Draw("colz");
TLegend* leg1 = new TLegend(0.7, 0.9-0.05*m, 0.95, 0.95);  
leg1->AddEntry(hPlog_plus_FA, Form("%02f",hPlog_plus_FA->Integral()),"l");  
leg1->Draw();    
  c_Plog->cd(2);  
  gPad->SetLogy(1);
  hPlog_minus_FA->Draw("colz");
TLegend* leg2 = new TLegend(0.7, 0.9-0.05*m, 0.95, 0.95);    
leg2->AddEntry(hPlog_minus_FA, Form("%02f",hPlog_minus_FA->Integral()),"l");  
leg2->Draw();    
  c_Plog->cd(3);  
  gPad->SetLogy(1);  
  hPlog_plus_LA->Draw("colz");
TLegend* leg3 = new TLegend(0.7, 0.9-0.05*m, 0.95, 0.95);    
leg3->AddEntry(hPlog_plus_LA, Form("%02f",hPlog_plus_LA->Integral()),"l");  
leg3->Draw();      
  c_Plog->cd(4);  
  gPad->SetLogy(1);
  hPlog_minus_LA->Draw("colz");
TLegend* leg4 = new TLegend(0.7, 0.9-0.05*m, 0.95, 0.95);    
leg4->AddEntry(hPlog_minus_LA, Form("%02f",hPlog_minus_LA->Integral()),"l");  
leg4->Draw();    

  TCanvas *c_ThetaPhi = new TCanvas("ThetaPhi","ThetaPhi",1200,900);
  c_ThetaPhi->Divide(4,m);
  for(int k=0;k<m;k++){
    for(int l=0;l<4;l++){
      gPad->SetLogz(1);
      c_ThetaPhi->cd(k*4+l+1);
      hThetaPhi[l][k]->Draw("colz");
      hThetaPhi[l][k]->SetAxisRange(thetamin,thetamax,"X");      
    }
  }
  
  TCanvas *c_decayangle_theta = new TCanvas("decayangle_theta","decayangle_theta",1200,300);
  c_decayangle_theta->Divide(3,1);
  c_decayangle_theta->cd(1);
  hdecayangle1_theta[3]->Draw("colz");
  c_decayangle_theta->cd(2);
  hdecayangle2_theta[3]->Draw("colz");
  c_decayangle_theta->cd(3);
  hdecayangle3_theta[3]->Draw("colz");
  
  TCanvas *c_decayangle_phi = new TCanvas("decayangle_phi","decayangle_phi",1200,300);
  c_decayangle_phi->Divide(3,1);
  c_decayangle_phi->cd(1);
  hdecayangle1_phi[3]->Draw("colz");
  c_decayangle_phi->cd(2);
  hdecayangle2_phi[3]->Draw("colz");
  c_decayangle_phi->cd(3);
  hdecayangle3_phi[3]->Draw("colz");

  TCanvas *c_decaymom1 = new TCanvas("decaymom1","decaymom1",1200,900);
  hdecaymom1[3]->Draw("colz");
  TCanvas *c_decaymom2 = new TCanvas("decaymom2","decaymom2",1200,900);
  hdecaymom2[3]->Draw("colz");  

//   for (Int_t i=1;i<hlepIM1[3]->GetNbinsX();i++) {
//     if (hlepIM1[3]->GetBinContent(i)>0){
//       double error=1./sqrt(hlepIM1[3]->GetBinContent(i));
//       cout << error << " " << hlepIM1[3]->GetBinError(i) << endl;
//       hlepIM1[3]->SetBinError(i,error);
//     }
//   }
 
  TCanvas *c_lepIM1_count = new TCanvas("lepIM1_count","lepIM1_count",1200,900);
  hlepIM1[windex]->Draw("HIST");
  hlepIM1[windex]->SetTitle("count/50MeV;l^{+}l^{-} InvM (GeV);");
//   hlepIM1[windex]->SetTitle("HERA H1 e 27.6GeV p 920GeV;l^{+}l^{-} InvM (GeV);d#sigma/dM(pb/GeV)");
//   gPad->SetLogy(1);
//   gPad->SetLogx(1);  
  c_lepIM1_count->SaveAs(Form("%s/lepIM1_count.png",input_filedir.c_str()));
  c_lepIM1_count->SaveAs(Form("%s/lepIM1_count.pdf",input_filedir.c_str()));        
  

//   TCanvas *c_lepIM2_count = new TCanvas("lepIM2_count","lepIM2_count",1200,900);
//   hlepIM2[3]->SetTitle(";l^{+}l^{-} InvM (GeV);count/50MeV");    
//   hlepIM2[3]->Draw();  
//   
// 
//   TCanvas *c_lepIM_count = new TCanvas("lepIM_count","lepIM_count",1200,900);
//   hlepIM[3]->SetTitle(";l^{+}l^{-} InvM (GeV);count/50MeV");    
//   hlepIM[3]->Draw();

  TCanvas *c_lepIM = new TCanvas("lepIM","lepIM",1200,900);
  c_lepIM->Divide(4,m);
  for(int k=0;k<m;k++){
      c_lepIM->cd(k*4+1);
      hlepIM1[k]->Draw();
      c_lepIM->cd(k*4+2);
      hlepIM2[k]->Draw();
      c_lepIM->cd(k*4+3);
      hlepIM[k]->Draw();
      c_lepIM->cd(k*4+4);
      gPad->SetLogz(1);
      hlepIM_2D[k]->Draw("colz");   
  }    
  
  cout << "BH " <<  hlepIM[3]->Integral() << endl;
  
  TCanvas *c_lepIM1_error = new TCanvas("lepIM1_error","lepIM1_error",1200,900);
  hlepIM1_error[3]->SetTitle(";l^{+}l^{-} InvM (GeV);error(1/sqrt(N))/200MeV");    
  for (Int_t i=1;i<hlepIM1_error[3]->GetNbinsX();i++) {
    if (hlepIM1_error[3]->GetBinContent(i)>0){
      double error=1./sqrt(hlepIM1_error[3]->GetBinContent(i));
      hlepIM1_error[3]->SetBinContent(i,error);
    }
  }  
  hlepIM1_error[3]->Draw();  
  
TCanvas *c_t_Qp2_xip = new TCanvas("t_Qp2_xip","t_Qp2_xip",1600,800);
c_t_Qp2_xip->Divide(3,1);
c_t_Qp2_xip->cd(1);
gPad->SetLogz();
ht_Qp2_xip[0]->SetTitle("generated");
ht_Qp2_xip[0]->Draw("box");
c_t_Qp2_xip->cd(2);
gPad->SetLogz();
ht_Qp2_xip[1]->SetTitle("detected");
ht_Qp2_xip[1]->Draw("box");
c_t_Qp2_xip->cd(3);
gPad->SetLogz();
TH3F *hacc_t_Qp2_xip=(TH3F*)ht_Qp2_xip[1]->Clone();
hacc_t_Qp2_xip->Divide(ht_Qp2_xip[0]);
hacc_t_Qp2_xip->SetMinimum(0);
hacc_t_Qp2_xip->SetMaximum(1);
hacc_t_Qp2_xip->SetNameTitle("acc_t_Qp2_xip","acceptance");
hacc_t_Qp2_xip->Draw("box");

TCanvas *c_Qp2_xip = new TCanvas("Qp2_xip","Qp2_xip",1600,800);
c_Qp2_xip->Divide(3,1);
c_Qp2_xip->cd(1);
gPad->SetLogz();
hQp2_xip[0]->SetTitle("generated");
hQp2_xip[0]->Draw("colz");
c_Qp2_xip->cd(2);
gPad->SetLogz();
hQp2_xip[1]->SetTitle("detected");
hQp2_xip[1]->Draw("colz");
c_Qp2_xip->cd(3);
gPad->SetLogz();
TH2F *hacc_Qp2_xip=(TH2F*)hQp2_xip[1]->Clone();
hacc_Qp2_xip->Divide(hQp2_xip[0]);
hacc_Qp2_xip->SetMinimum(0);
hacc_Qp2_xip->SetMaximum(1);
hacc_Qp2_xip->SetNameTitle("acc_Qp2_xip","acceptance");
hacc_Qp2_xip->Draw("colz");

TCanvas *c_Qp2_t = new TCanvas("Qp2_t","Qp2_t",1600,800);
c_Qp2_t->Divide(3,1);
c_Qp2_t->cd(1);
gPad->SetLogz();
hQp2_t[0]->SetTitle("generated");
hQp2_t[0]->Draw("colz");
c_Qp2_t->cd(2);
gPad->SetLogz();
hQp2_t[1]->SetTitle("detected");
hQp2_t[1]->Draw("colz");
c_Qp2_t->cd(3);
gPad->SetLogz();
TH2F *hacc_Qp2_t=(TH2F*)hQp2_t[1]->Clone();
hacc_Qp2_t->Divide(hQp2_t[0]);
hacc_Qp2_t->SetMinimum(0);
hacc_Qp2_t->SetMaximum(1);
hacc_Qp2_t->SetNameTitle("acc_Qp2_t","acceptance");
hacc_Qp2_t->Draw("colz");

  TCanvas *c_kinematics = new TCanvas("kinematics","kinematics",1600,900);
  c_kinematics ->Divide(5,2);  
  c_kinematics ->cd(1);
  gPad->SetLogz(1);    
  ht_Qp2->Draw("colz");
  c_kinematics ->cd(2);
  gPad->SetLogz(1);    
  ht_W->Draw("colz");
  c_kinematics ->cd(3);
  gPad->SetLogz(1);    
  ht_Q2Qp2->Draw("colz");
  c_kinematics ->cd(4);
  gPad->SetLogz(1);    
  ht_xip->Draw("colz");
  c_kinematics ->cd(5);  
  gPad->SetLogz(1);  
  ht_xi->Draw("colz");
  c_kinematics ->cd(6);  
  gPad->SetLogz(1);  
  hxbj_Q2->Draw("colz");
  c_kinematics ->cd(7);  
  gPad->SetLogz(1);  
  hxbj_xip->Draw("colz");
  c_kinematics ->cd(8);  
  gPad->SetLogz(1);  
  hxbj_xi->Draw("colz");
  c_kinematics ->cd(9);  
  gPad->SetLogz(1);  
  hxip_xi->Draw("colz");
  c_kinematics ->cd(10);  
  gPad->SetLogz(1);  
  hQ2_Qp2->Draw("colz");
  c_kinematics->SaveAs(Form("%s/kinematics.png",input_filedir.c_str()));
  c_kinematics->SaveAs(Form("%s/kinematics.pdf",input_filedir.c_str()));        
  
  TCanvas *c_kinematics_final = new TCanvas("kinematics_final","kinematics_final",1200,900);
  c_kinematics_final->Divide(2,2);   
  c_kinematics_final->cd(1);  
  gPad->SetLogz(1);  
  hxbj_Q2->Draw("colz");
  c_kinematics_final->cd(2);  
  gPad->SetLogz(1);  
  ht_Q2Qp2->Draw("colz");  
  c_kinematics_final->cd(3);  
  gPad->SetLogz(1);  
  hQ2_Qp2->Draw("colz");
  c_kinematics_final->cd(4);  
  gPad->SetLogz(1);  
  hxip_xi->Draw("colz");
  c_kinematics_final->SaveAs(Form("%s/kinematics_final.png",input_filedir.c_str()));
  c_kinematics_final->SaveAs(Form("%s/kinematics_final.pdf",input_filedir.c_str()));        
  
  TCanvas *c_Q2_W = new TCanvas("Q2_W","Q2_W",1200,900);
  gPad->SetLogz(1);    
  hQ2_W->Draw("colz"); 

  TCanvas *c_resolution = new TCanvas("resolution","resolution",1600,900);
  c_resolution->Divide(3,4);
  for(int k=0;k<m;k++){
      c_resolution->cd(k*3+1);
      hnew_p[k]->Draw();
      c_resolution->cd(k*3+2);
      hnew_theta[k]->Draw();
      c_resolution->cd(k*3+3);
      hnew_phi[k]->Draw();      
  }
  
  TCanvas *c_MM = new TCanvas("MM","MM",1600,900);
  c_MM->Divide(2,2);    
  c_MM->cd(1); 
  hMM->Draw();
//   hMM->Fit("gaus");
  c_MM->cd(2);  
  hMM_t->Draw("colz");  
  c_MM->cd(3);  
  hMM_Q2->Draw("colz");    
  c_MM->cd(4);  
  hMM_Qp2->Draw("colz");  

  TCanvas *c_MM_only = new TCanvas("MM_only","MM_only",1600,900);
  c_MM_only->cd(1);
  hMM->Draw();

//   TCanvas *c_countproj = new TCanvas("c_countproj","c_countproj",1600,900);
//   c_countproj->Divide(3,1); 
//   c_countproj->cd(1);  
//   hcount1->SetLineColor(kBlack);
//   hcount1->SetMinimum(0);    
//   hcount1->Draw();
//   c_countproj->cd(2);    
//   hcount2->SetLineColor(kRed);
//   hcount2->SetMinimum(0);  
//   hcount2->Draw();
//   c_countproj->cd(3);    
//   hcount3->SetLineColor(kBlue);
//   hcount3->SetMinimum(0);
//   hcount3->Draw();
//   c_countproj->SaveAs(Form("%s/countproj.png",input_filedir.c_str()));      

  TCanvas *c_countproj = new TCanvas("c_countproj","c_countproj",1600,900);
  hcount[0]->SetLineColor(kBlack);
  hcount[0]->SetMinimum(0);    
//   hcount[0]->SetMaximum(1e3);      
  hcount[0]->Draw("HIST");
//   hcount[1]->SetLineColor(kRed);
//   hcount[1]->SetMinimum(0);    
//   hcount[1]->SetMaximum(1e3);    
//   hcount[1]->Draw("HIST same");
  c_countproj->SaveAs(Form("%s/countproj.png",input_filedir.c_str()));      
  
//   TCanvas *can12 = new TCanvas("can12","",1200,900);
//   gStyle->SetOptStat(0);  
//   gStyle->SetTitleSize(0.1,"X");
//   gStyle->SetTitleSize(0.1,"Y");
//   can12->SetFillColor(10);
//   hlepIM_count->SetTitle("BH event counts VS e+ e- Inv Mass");
//   hlepIM_count->GetXaxis()->SetTitle("e+ e- Inv Mass (GeV)");
//   hlepIM_count->GetYaxis()->SetTitle("counts /50 MeV for 50 days");
// //   hlepIM_count->SetTitleSize(0.1);
//   hlepIM_count->Rebin(5);  
//   hlepIM_count->Draw();
//   hlepIM_count->SetLineWidth(3.5);

//   TCanvas *can = new TCanvas("can","can",1200,900);
//   can->Divide(3,2);  
//   can->cd(1);
//   hW->GetXaxis()->SetTitle("W");
//   hW->GetYaxis()->SetTitle("d#sigma (pb/10 MeV)");
//   hW->Draw();  
//   can->cd(2);
//   hWstat->GetXaxis()->SetTitle("Wstat");
//   hWstat->GetYaxis()->SetTitle("number of event per day/ 10MeV");
//   hWstat->Draw();   
//   can->cd(3);
//   hQp2W->Draw("colz");
//   can->cd(4);
//   htW->Draw("colz");
//   can->cd(5);
//   htminW->Draw("colz");
//   htmaxW->Draw("colz same");  
//   can->cd(6);
//   ht->Draw();
  
//   TCanvas *can4 = new TCanvas("can4","can4",1200,800);
//   can4->Divide(3,2);
//   can4->cd(1);
//   hkpth->GetXaxis()->SetTitle("scattered electron #theta_{SHRS} (deg)");
//   hkpth->Draw();
//   can4->cd(4);
//   hprth->GetXaxis()->SetTitle("recoiling proton #theta_{HRS} (deg)");
//   hprth->Draw();
//   can4->cd(2);
//   hkpph->GetXaxis()->SetTitle("scattered electron #phi_{lab} (deg)");
//   hkpph->Draw();
//   can4->cd(5);
//   hprph->GetXaxis()->SetTitle("recoiling proton #phi_{lab} (deg)");
//   hprph->Draw();
//   can4->cd(3);
//   hkpp->GetXaxis()->SetTitle("scattered electron momentum (GeV)");
//   hkpp->Draw();
//   can4->cd(6);
//   hprp->GetXaxis()->SetTitle("recoiling proton momentum (GeV)");
//   hprp->Draw();
//   
//   TCanvas *can5 = new TCanvas("can5","",900,900);
//   hemscat->SetMarkerColor(kRed);
//   hepscat->SetMarkerColor(kBlue);
//   hepscat->GetXaxis()->SetTitle("x_{lab}");
//   hepscat->GetXaxis()->SetTitle("y_{lab}");
//   hepscat->Draw();
//   hemscat->Draw("same");

//   cout << "BH 3-3.25 GeV " <<  hlepIM2->Integral(20,45) << endl;  //pure count and no width
  cout << "BH events counts at 2<InvM1<3 GeV " <<  hlepIM1[windex]->Integral(40,60) << endl;  //pure count and no width
  cout << "BH events counts at 1<InvM1<3 GeV " <<  hlepIM1[windex]->Integral(20,60) << endl;  //pure count and no width  
  cout << "BH events counts at 0<InvM1<3 GeV " <<  hlepIM1[windex]->Integral(0,60) << endl;  //pure count and no width
  cout << "BH events counts at 0<InvM1<4 GeV " <<  hlepIM1[windex]->Integral(0,80) << endl;  //pure count and no width      
//   cout << "BH events counts at 2<InvM1<3 GeV and additional cut " <<  hlepIM1[4]->Integral(40,60) << endl;  //pure count and no width    

outputfile->Write();
outputfile->Flush();
outputfile->Close();      

exit(0);
}
