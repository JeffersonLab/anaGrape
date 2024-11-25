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

const int n=2;
char *filename[n]={
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/output.root",

"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/output.root_etheta5-20mom1",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/output.root_etheta5-20phi5-20mom1",
  
"/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_22_BH_muon_3fold_decaypairelectron_deg5-50/FA_nosmear_emumu/output.root",
  
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/FALA_nosmear_22gev/output.root",
// "/work/halla/solid/zwzhao/BH/grape-dilepton_work/JLab_11_BH_muon_3fold_decaypairelectron_deg5-50/FA_nosmear_emumu/output.root",

};
char *label[n]={"22GeV","11GeV"};
// sprintf(hstname,"xbj_Q2");
// sprintf(hstname,"decayangle1_theta_3");
// sprintf(hstname,"decayangle1_phi_3");
sprintf(hstname,"decayangle1_thetaphi_3");
sprintf(outname,"compare_solid_ddvcs_11GeV_22GeV_Q2xbj_FA_nosmear_mumup");
// sprintf(hstname,"Q2_Qp2");
// sprintf(outname,"compare_solid_ddvcs_11GeV_22GeV_Q2Qp2_FA_nosmear_emumu");
// sprintf(title,"count/50MeV;l^{+}l^{-} InvM (GeV);");
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
TH2F *h[n];
TCanvas *c = new TCanvas("c","c",1000,800);
TLegend* leg = new TLegend(0.8, 0.8, 0.95, 0.95);
// TLegend* leg = new TLegend(0.6, 0.7, 0.95, 0.95);
for (Int_t i=0;i<n;i++) {
  if (i==1) continue;
  cout << i << endl;
  
//   cout << Form("%s/grp_out.root",name[i]) << endl;
//   file[i]=new TFile(Form("%s/acceptance_forward/grp_out.root",name[i]));  
//   file[i]=new TFile(Form("%s/acceptance_forwardandlarge/grp_out.root",name[i]));    
//   file[i]=new TFile(Form("%s/grp_out.root",name[i]));
  file[i]=new TFile(Form("%s",filename[i]));        

  h[i]=(TH2F*) file[i]->Get(hstname);
//   hacceptance_P[i]=(TH1F*) file[i]->Get("acceptance_P");
//   hacceptance_Theta[i]=(TH1F*) file[i]->Get("acceptance_Theta");
//   hacceptance_Q2[i]=(TH1F*) file[i]->Get("acceptance_Q2");
//  h[i]->SetLineColor(i+1); 
//    h[i]->SetLineColor(color[i]);
//    h[i]->SetFillColor(color[i]);   
//      h[i]->SetFillColor(kRed);   
//  h[i]->SetMaximum(5e5); 
//  h[i]->SetMaximum(1.5e-5); 
//  h[i]->SetMaximum(0.05);  
//  h[i]->SetTitle(title);
 if (i==0) h[i]->Draw("colz");
 else h[i]->Draw("box same");
 gPad->SetLogz(1);
 
// label = new TText(0.5,8e-6+i*2e-6,name[i]);
// label = new TText(0.5,8e-6+i*2e-6,name[i]); 
// label->SetTextColor(i+1);
// label->SetTextSize(0.05);
// label->Draw();
//   leg->AddEntry(h[i], label[i],"l");  
 
}

// leg->Draw();

// c->SaveAs(Form("%s.png",outname));
// c->SaveAs(Form("%s.pdf",outname));
}