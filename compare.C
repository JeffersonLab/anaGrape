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

char hstname[100],title[100],outname[100]; 

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

// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_22_BH_muon_3fold_decaypairelectron_deg5-50/output.root",

// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairproton_deg5-50/FA_nosmear_mumup/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_22_BH_muon_3fold_decaypairproton_deg5-50/FA_nosmear_mumup/output.root",
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairproton_deg5-50/FALA_nosmear_mumup/output.root",
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_22_BH_muon_3fold_decaypairproton_deg5-50/FALA_nosmear_mumup/output.root",
};
char *label[n]={"11GeV","22GeV"};
sprintf(hstname,"lepIM1_3");
// sprintf(hstname,"lepIM1_4");
sprintf(title,"count/50MeV;l^{+}l^{-} InvM (GeV);");
sprintf(outname,"compare_solid_ddvcs_11GeV_22GeV_InvM_FALA_nosmear_mumup");
int color[n]={0,1};


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
TCanvas *c = new TCanvas("c","c",1100,800);
TLegend* leg = new TLegend(0.8, 0.8, 0.95, 0.95);
// TLegend* leg = new TLegend(0.6, 0.7, 0.95, 0.95);
for (Int_t i=0;i<n;i++) {
//   if (i==2) continue;
  cout << i << endl;
  
//   cout << Form("%s/grp_out.root",name[i]) << endl;
//   file[i]=new TFile(Form("%s/acceptance_forward/grp_out.root",name[i]));  
//   file[i]=new TFile(Form("%s/acceptance_forwardandlarge/grp_out.root",name[i]));    
//   file[i]=new TFile(Form("%s/grp_out.root",name[i]));
  file[i]=new TFile(Form("%s",filename[i]));        

  h[i]=(TH1F*) file[i]->Get(hstname);
//   hacceptance_P[i]=(TH1F*) file[i]->Get("acceptance_P");
//   hacceptance_Theta[i]=(TH1F*) file[i]->Get("acceptance_Theta");
//   hacceptance_Q2[i]=(TH1F*) file[i]->Get("acceptance_Q2");
 h[i]->SetLineColor(i+1); 
//    h[i]->SetLineColor(color[i]);
//  h[i]->SetMaximum(5e5); 
//  h[i]->SetMaximum(1.5e-5); 
//  h[i]->SetMaximum(0.05);  
 h[i]->SetTitle(title);
 if (i==0) h[i]->Draw();
 else h[i]->Draw("same");
  cout << "count " << h[i]->Integral() << endl;
 
// label = new TText(0.5,8e-6+i*2e-6,name[i]);
// label = new TText(0.5,8e-6+i*2e-6,name[i]); 
// label->SetTextColor(i+1);
// label->SetTextSize(0.05);
// label->Draw();
  leg->AddEntry(h[i], label[i],"l");  
 
}

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