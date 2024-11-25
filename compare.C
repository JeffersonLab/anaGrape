{
  gROOT->Reset();
// gStyle->SetPalette(1);
gStyle->SetOptStat(0);

  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);  
  
  gStyle->SetPadColor(0);

  gStyle->SetLabelSize(0.04,"xyz"); // size of axis values
  gStyle->SetTitleSize(0.04,"xyz");   
  gStyle->SetTitleSize(0.07,"t");    
  gStyle->SetPaintTextFormat("4.1f");   

char hstname[100],title[500],outname[100]; 

// const int n=4;
// char *name[n]={"BHinterNO","BHinter","Compton","QED"};

// char *name[n]={"BH_muon_3fold_decaypairproton_deg5-50","BH_muon_3fold_decaypairelectron_deg5-50","BH_muon_4fold_deg5-50"};
// char *label[n]={"recoil proton and decay pair","scattered e- and decay pair","all 4 particles"};
// sprintf(hstname,"lepIM1_3");

// const int n=2;
// char *filename[n]={
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/FA_yessmear/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_quasi_deg5-50/FA_yessmear/output.root",
// };
// // char *label[n]={"elastic","quasi-elastic"};
// char *label[n]={"BH","BH+pi0"};
// sprintf(hstname,"MM");
// sprintf(title,"missing mass of proton");
// int color[n]={0,1};

/*
const int n=2;
char *filename[n]={
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/FA_nosmear_emumup/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_22_BH_muon_3fold_decaypairelectron_deg5-50/FA_nosmear_emumup/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/FALA_nosmear_emumup/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_22_BH_muon_3fold_decaypairelectron_deg5-50/FALA_nosmear_emumup/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/FA_nosmear_emumu/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_22_BH_muon_3fold_decaypairelectron_deg5-50/FA_nosmear_emumu/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/FALA_nosmear_emumu/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_22_BH_muon_3fold_decaypairelectron_deg5-50/FALA_nosmear_emumu/output.root",

// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairproton_deg5-50/FA_nosmear_mumup/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_22_BH_muon_3fold_decaypairproton_deg5-50/FA_nosmear_mumup/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairproton_deg5-50/FALA_nosmear_mumup/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_22_BH_muon_3fold_decaypairproton_deg5-50/FALA_nosmear_mumup/output.root",

"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_ele_3fold_decaypairelectron_deg5-50_noISR/output.root",    
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_muon_3fold_decaypairelectron_deg5-50_noISR/output.root",
};
// char *label[n]={"11GeV","22GeV"};
char *label[n]={"ele pair","muon pair"};
sprintf(hstname,"lepIM1_0");
// sprintf(title,"count/50MeV;l^{+}l^{-} InvM (GeV);");
sprintf(title,"grape-dilepton elastic,11GeV e- beam on p,with cut e,mu+,mu- angle 5-50deg;l^{+}l^{-} InvM (GeV);crossection(pb/50MeV)");
sprintf(outname,"compare_solid_ddvcs_11GeV_22GeV_InvM_FALA_nosmear_mumup");
int color[n]={1,2};
*/


const int n=14;
char *filename[n]={ 
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_muon_3fold_decaypairelectron_deg5-50/output.root",
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/output.root",
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_ele_3fold_decaypairelectron_deg5-50/output.root",
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_ele_3fold_decaypairelectron_deg5-50/output.root",    
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_ele_3fold_decaypairelectron_deg5-50/output.root",    
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_ele_3fold_decaypairelectron_deg5-50/output.root",    
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BHdirect_ele_3fold_decaypairelectron_deg5-50/output.root",     

"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_muon_3fold_decaypairelectron_deg5-50_noISR/output.root",
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50_noISR/output.root",
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_ele_3fold_decaypairelectron_deg5-50_noISR/output.root",    
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_ele_3fold_decaypairelectron_deg5-50_noISR/output.root",    
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_ele_3fold_decaypairelectron_deg5-50_noISR/output.root",    
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_ele_3fold_decaypairelectron_deg5-50_noISR/output.root",    
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BHdirect_ele_3fold_decaypairelectron_deg5-50_noISR/output.root",  
};
char *label[n]={"ISRon QED muon","ISRon BH muon","ISRon QED ele(highPt)","ISRon QED ele(lowPt)","ISRon BH ele(highPt)","ISRon BH ele(lowPt)","ISRon BHdirect ele","ISRoff QED muon","ISRoff BH muon","ISRoff QED ele(highPt)","ISRoff QED ele(lowPt)","ISRoff BH ele(highPt)","ISRoff BH ele(lowPt)","ISRoff BHdirect ele"};
sprintf(hstname,"lepIM1_0");
// sprintf(title,"count/50MeV;l^{+}l^{-} InvM (GeV);");
sprintf(title,"grape-dilepton elastic,11GeV e- beam on p,with cut e-,mu+,mu- or e-,e+,e- angle 5-50deg;l^{+}l^{-} InvM (GeV);crossection(pb/50MeV)");
sprintf(outname,"compare_solid_ddvcs_11GeV_22GeV_InvM_FALA_nosmear_mumup");
int color[n]={1,2,3,4,6,7,8,1,2,3,4,6,7,8};
int style[n]={1,1,1,1,1,1,1,2,2,2,2,2,2,2};

// const int n=8;
// char *filename[n]={
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_CO_muon_3fold_decaypairelectron_deg5-50/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_muon_3fold_decaypairelectron_deg5-50/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_EW_muon_3fold_decaypairelectron_deg5-50/output.root",
// 
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50_noISR/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_CO_muon_3fold_decaypairelectron_deg5-50_noISR/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_muon_3fold_decaypairelectron_deg5-50_noISR/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_EW_muon_3fold_decaypairelectron_deg5-50_noISR/output.root",
// 
// // "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_EW_muon_3fold_decaypairelectron_deg5-50/output.root",
// // "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_EW_muon_3fold_decaypairelectron_deg5-50_noISR/output.root",
// 
// // "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_QED_muon_3fold_decaypairelectron_deg1-50/output.root",
// 
// 
// // JLab_11_BH_muon_3fold_decaypairelectron_deg5-50
// // JLab_11_CO_muon_3fold_decaypairelectron_deg5-50
// // JLab_11_QED_muon_3fold_decaypairelectron_deg5-50
// // JLab_11_EW_muon_3fold_decaypairelectron_deg5-50
// };
// char *label[n]={"ISRon BH(a)","ISRon Compton(b)","ISRon QED(a+b)","ISRon EW(a+b+c)","ISRoff BH(a)","ISRoff Compton(b)","ISRoff QED(a+b)","ISRoff EW(a+b+c)"};
// sprintf(hstname,"lepIM1_0");
// sprintf(title,"grape-dilepton elastic,11GeV e- beam on p,with cut e,mu+,mu- angle 5-50deg;l^{+}l^{-} InvM (GeV);crossection(pb/50MeV)");
// // sprintf(title,"count/50MeV;l^{+}l^{-} InvM (GeV);");
// // sprintf(outname,"compare_ddvcs_grape_emumu");
// int color[n]={1,2,3,4,1,2,3,4};
// int style[n]={1,1,1,1,2,2,2,2};

// const int n=4;
// char *filename[n]={
// "acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_pim_theta12_1e6_output_final_1D_direct.root",
// "acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_pim_theta12_1e6_output_final_1D_all.root",
// "acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_pim_theta12_1e6_output_final_1D_directdecay.root",
// "acc_solid_JPsi_DDVCS_LH2/solid_JPsi_DDVCS_LH2_moved_full_even_pim_theta12_1e6_output_final_1D_alldecay.root",
// };
// char *label[n]={"primary pion","primary and secondary pion","muon from primary pion decay","muon from primary and secondary pion decay"};
// sprintf(hstname,"acceptance_P_0");
// sprintf(title,"surviving probability at forward angle muon detector");
// int color[n]={0,1,2,3};

TFile *file[n];
TH1F *h[n];
TH1F *hadd_ISRon,*hadd_ISRoff;
TCanvas *c = new TCanvas("c","c",1200,800);
TLegend* leg = new TLegend(0.5, 0.5, 0.9, 0.9);
// TLegend* leg = new TLegend(0.7, 0.7, 0.9, 0.9);
for (Int_t i=0;i<n;i++) {
//   if (i>2) continue;
//     if (i==3) sprintf(hstname,"lepIM1_2");
  cout << i << endl;
  
//   cout << Form("%s/grp_out.root",name[i]) << endl;
//   file[i]=new TFile(Form("%s/acceptance_forward/grp_out.root",name[i]));  
//   file[i]=new TFile(Form("%s/acceptance_forwardandlarge/grp_out.root",name[i]));    
//   file[i]=new TFile(Form("%s/grp_out.root",name[i]));
  file[i]=new TFile(Form("%s",filename[i]));        

  h[i]=(TH1F*) file[i]->Get(hstname);  
  if (i==3||i==5||i==10||i==12) h[i]=(TH1F*) file[i]->Get("lepIM2_0");
  else h[i]=(TH1F*) file[i]->Get(hstname);
  
  if (i==2||i==3||i==9||i==10) h[i]->Scale(0.5);
//   hacceptance_P[i]=(TH1F*) file[i]->Get("acceptance_P");
//   hacceptance_Theta[i]=(TH1F*) file[i]->Get("acceptance_Theta");
//   hacceptance_Q2[i]=(TH1F*) file[i]->Get("acceptance_Q2");
//  h[i]->SetLineColor(i+1); 
   h[i]->SetLineColor(color[i]);
   h[i]->SetLineStyle(style[i]);  
//  h[i]->SetMaximum(5e5); 
//  h[i]->SetMaximum(1.5e-5); 
//  h[i]->SetMaximum(0.05);  
//  h[i]->SetMaximum(0.12);   
 h[i]->SetMaximum(0.4);   
 h[i]->SetTitle(title);
 if (i==0) h[i]->Draw("H");
 else h[i]->Draw("H same");
  cout << "count " << h[i]->Integral() << endl;
 
//  if (i==0) hadd_ISRon=(TH1F*)h[i]->Clone();
//  if (i==1) hadd_ISRon->Add(h[i]); 
//  if (i==4) hadd_ISRoff=(TH1F*)h[i]->Clone();
//  if (i==5) hadd_ISRoff->Add(h[i]); 
 
// label = new TText(0.5,8e-6+i*2e-6,name[i]);
// label = new TText(0.5,8e-6+i*2e-6,name[i]); 
// label->SetTextColor(i+1);
// label->SetTextSize(0.05);
// label->Draw();
//   leg->AddEntry(h[i],label[i],"l");  
  leg->AddEntry(h[i],Form("%s, integral %1.2f",label[i],h[i]->Integral()),"l");   
}

//   hadd_ISRon->SetLineColor(6);
//   hadd_ISRon->SetLineStyle(1);  
//   hadd_ISRon->Draw("H same");
//   hadd_ISRoff->SetLineColor(6);
//   hadd_ISRoff->SetLineStyle(2);  
//   hadd_ISRoff->Draw("H same");
//   leg->AddEntry(hadd_ISRon,Form("ISRon BH+Compton, integral %1.2f",hadd_ISRon->Integral()),"l");   
//   leg->AddEntry(hadd_ISRoff,Form("ISRoff BH+Compton, integral %1.2f",hadd_ISRoff->Integral()),"l");   
  
  leg->Draw();
  
// c->SaveAs(Form("%s.png",outname));
// c->SaveAs(Form("%s.pdf",outname));

return;

for (Int_t i=3;i<6;i++) {
//   cout << Form("%s/grp_out.root",name[i]) << endl;
//   file[i]=new TFile(Form("%s/acceptance_forward/grp_out.root",name[i]));  
  file[i]=new TFile(Form("%s/acceptance_forwardandlarge/grp_out.root",name[i-3]));    
//   file[i]=new TFile(Form("%s/grp_out.root",name[i]));      

  h[i]=(TH1F*) file[i]->Get("lepIM1_3");
//   hacceptance_P[i]=(TH1F*) file[i]->Get("acceptance_P");
//   hacceptance_Theta[i]=(TH1F*) file[i]->Get("acceptance_Theta");
//   hacceptance_Q2[i]=(TH1F*) file[i]->Get("acceptance_Q2");
//  h[i]->SetLineColor(i+1); 
   h[i]->SetLineColor(color[i-3]);
   h[i]->SetLineStyle(2);   
 h[i]->SetMaximum(5e5); 
//  h[i]->SetMaximum(1.5e-5);  
 cout << i << endl;
  h[i]->Draw("same");
 
// label = new TText(0.5,8e-6+i*2e-6,name[i]);
// label = new TText(0.5,8e-6+i*2e-6,name[i]); 
// label->SetTextColor(i+1);
// label->SetTextSize(0.05);
// label->Draw();
  leg->AddEntry(h[i], label[i-3],"l");  
 
}

leg->Draw();

/*
TH2F *h=(TH2F*) h1->Clone();
h->Divide(h1,h2);

TCanvas *c_acceptance_eDIS_1D = new TCanvas("acceptance_eDIS_1D","acceptance_eDIS_1D",1800,900);
c_acceptance_eDIS_1D->Divide(2,2);
c_acceptance_eDIS_1D->cd(1);
gPad->SetGrid();
for (Int_t i=0;i<4;i++) {
hacceptance_P[i]->SetMinimum(0);
hacceptance_P[i]->SetMaximum(0.6);
hacceptance_P[i]->SetLineColor(i+1);
if (i==0) hacceptance_P[i]->Draw();
else hacceptance_P[i]->Draw("same");
}
c_acceptance_eDIS_1D->cd(2);
gPad->SetGrid();
for (Int_t i=0;i<4;i++) {
hacceptance_Theta[i]->SetMinimum(0);
hacceptance_Theta[i]->SetMaximum(0.1);
hacceptance_Theta[i]->SetLineColor(i+1);
if (i==0) hacceptance_Theta[i]->Draw();
else hacceptance_Theta[i]->Draw("same");
}
c_acceptance_eDIS_1D->cd(3);
gPad->SetGrid();
for (Int_t i=0;i<4;i++) {
hacceptance_x[i]->SetMinimum(0);
hacceptance_x[i]->SetMaximum(0.6);
hacceptance_x[i]->SetLineColor(i+1);
if (i==0) hacceptance_x[i]->Draw();
else hacceptance_x[i]->Draw("same");
}
c_acceptance_eDIS_1D->cd(4);
gPad->SetGrid();
for (Int_t i=0;i<4;i++) {
hacceptance_Q2[i]->SetMinimum(0);
hacceptance_Q2[i]->SetMaximum(0.6);
hacceptance_Q2[i]->SetLineColor(i+1);
if (i==0) hacceptance_Q2[i]->Draw();
else hacceptance_Q2[i]->Draw("same");
}*/

// // gPad->SetLogz(1);
// gPad->SetGrid();
// h1->SetMarkerColor(kBlack);
// h1->SetMarkerStyle(6);
// h1->Draw();
// h2->SetMarkerColor(kRed);
// h2->SetMarkerStyle(6);
// h2->Draw("same");
// h3->SetMarkerColor(kBlue);
// h3->SetMarkerStyle(6);
// h3->Draw("same");
// 
// // h1->SetTitle("hits behind 11th baffle (black(-),red(0),blue(+)) ;x (cm);y (cm)");
// h1->SetTitle("hits before FAEC (black(-),red(0),blue(+)) ;x (cm);y (cm)");

// h->Scale(1e-3);
// h->SetAxisRange(20,44,"X");
// h->SetAxisRange(0,7,"Y");
// h->SetAxisRange(5,35,"X");
// h->SetAxisRange(0,11,"Y");
// h->SetTitle("#pi^{-}/e- ;#theta (deg);P (GeV)");
// h->SetTitle("#pi^{-}/K^{-} ;#theta (deg);P (GeV)");
// h->SetTitle("#pi^{+}/K^{+} ;#theta (deg);P (GeV)");
// h->Draw("colz text");

}