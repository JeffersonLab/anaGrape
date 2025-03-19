#include <iostream> 
#include <sstream>
#include <fstream>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TRandom2.h>

using namespace std;

// void root2lund(string input_filedir="")
void root2lund()
{
//  remember to change vertex value for your experiment and PID for your decay channel
// and you can adjust header line also, refer to https://gemc.jlab.org/gemc/html/documentation/generator/lund.html
    
//  set_style();
// gROOT->Reset();
gStyle->SetPalette(1);
gStyle->SetOptStat(1000011);
//   gStyle->SetOptStat(1);

Double_t pi1 = TMath::Pi();
//   cout << pi1 << endl;

Double_t D2R = 3.1415/180.;

Double_t DEG = 180./3.1415;
   
char input_filename[80];
// sprintf(input_filename, "%s/grp.root",input_filedir.c_str());
sprintf(input_filename, "grp.root");

  TChain *h11 = new TChain("h11");
  h11->Add(input_filename);

  Double_t xsec[20];

  h11->SetBranchStatus("*",0);
  h11->SetBranchStatus("xsec",1);
  h11->SetBranchAddress("xsec",&xsec);
  h11->GetEntry(0);

  cout << "total Cross Section " << xsec[0] << " pb" << endl;
  // total Cross Section also can be found in the spring output on screen
  
  TChain *h1 = new TChain("h1");
  h1->Add(input_filename);  
  
  Float_t px[20];
  Float_t py[20];
  Float_t pz[20];
  Float_t pe[20];
  Float_t pm[20];
//   Short_t kf[15];
//   Bool_t sta[20];
//   Int_t npy;
  Float_t kf[20];  
  Float_t sta[20];
  Float_t npy[20];

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

  Int_t nevent = h1->GetEntries();

  cout << nevent << endl;
  TLorentzVector kp, prot, ep, em, ki, targ;

//   Double_t effxsec = xsec[0]/(double)nevent; //this is not good normalization with multiple files and we need to further divide by number of files
  Double_t effxsec = xsec[0];  //this makes it easy for normalization with multiple files, just need to divide by nevents from all files

  Bool_t scatPhiBool, scat_e_calo;

  int counter1=0,counter2=0,counter3=0,counter4=0,counter5=0;
  
  Int_t counter;
  Int_t countd = 1;
  cout << "|___________________|" << endl;
  cout << "|" << flush;
  
  TRandom2 *rand = new TRandom2();
  rand->SetSeed(0);      
    
  ofstream OUT("grp.lund");
  
  for(Int_t i=0; i < nevent; i++){
//     for(Int_t i=0; i < 1000; i++){
    Double_t id = i;
    Double_t neventd = nevent;
    if(floor(id/neventd*20) == countd){
   
      cout << "=" << flush;
      countd++;
      if(countd == 20){
	cout << "|" << endl;
      }
    }

    h1->GetEvent(i);

//     if(i<3) {
//       for (Int_t j=0; j < 14; j++) {
// 	cout << j << "\t"  << px[j] <<  "\t"  << py[j] <<  "\t"  << pz[j] <<  "\t"  << pe[j] <<  "\t"  << pm[j] <<  "\t"  << kf[j] <<  "\t"  << sta[j] <<  "\t"  << npy[j] << endl; 
//       }
//       cout << "******************************"<< endl;
//     }

// https://research.kek.jp/people/tabe/grape/CPC/node8.html
// pe is not very accurate, use pm instead
// before ISR(initial state radiation)  
//     targ.SetXYZM(px[0],py[0],pz[0],pm[0]);    
//     ki.SetXYZM(px[1],py[1],pz[1],pm[1]);    
//     targ.SetXYZM(px[2],py[2],pz[2],pm[2]);
//     ki.SetXYZM(px[3],py[3],pz[3],pm[3]);
// after ISR(initial state radiation)  
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
    
    ki.RotateY(pi1);
    targ.RotateY(pi1);    
    prot.RotateY(pi1);    
    kp.RotateY(pi1);
    ep.RotateY(pi1);
    em.RotateY(pi1);
    
    double InvM_epm1=(ep+em).M();
    double InvM_epm2=(ep+kp).M();	
	  
    double Q2=-(ki-kp).M2();
    double W=(ki-kp+targ).M();
//         double W=(prot+ep+em).M();    
    double t=-(prot-targ).M2();
    double m1=(ki-kp).M(),m2=targ.M(),m3=3.097,m4=prot.M();
    double s=W*W;
    double E1cm=(s+m1*m1-m2*m2)/(2*sqrt(s)),E3cm=(s+m3*m3-m4*m4)/(2*sqrt(s));
    double p1cm=sqrt(E1cm*E1cm-m1*m1),p3cm=sqrt(E3cm*E3cm-m3*m3);
    double tmin= -(pow(E1cm-E3cm,2) - pow(p1cm-p3cm,2));
    double tmax= -(pow(E1cm-E3cm,2) - pow(p1cm+p3cm,2));  
    
    double mu=ki.E()-kp.E();
    double x=Q2/2./targ.M()/mu;
    double y=mu/ki.E();

    double vertexX=0,vertexY=0;
//     double vertexZ=0;    
    double vertexZ=rand->Uniform(-322.5,-307.5);
//     double PID_decay=11; //for e-e+
    double PID_decay=13; //for mu-mu+    
      
//       double count_convert = 1e-36*1e35*3600*24*120*0.85;

//     you can adjust this header line
      OUT << "4" << " \t " << 0  << " \t " << 0  << " \t " << 0  << " \t " << "0" << " \t "  << 0 << " \t " << 0  << " \t " << W  << " \t " << Q2  << " \t " << effxsec << endl;
      
      OUT << " \t " << "1" << " \t " << 1 << " \t " << "1" << " \t " << 2212 << " \t " << "0" << " \t " << "0" << " \t " << prot.Px() << " \t " << prot.Py() << " \t " << prot.Pz() << " \t " << prot.E() << " \t " << prot.M() << " \t " << vertexX  << " \t " << vertexY << " \t " << vertexZ << endl;      
      
      OUT << " \t " << "2" << " \t " << -1 << " \t " << "1" << " \t " << 11 << " \t " << "0" << " \t " << "0" << " \t " << kp.Px() << " \t " << kp.Py() << " \t " << kp.Pz() << " \t " << kp.E() << " \t " << kp.M() << " \t " << vertexX  << " \t " << vertexY << " \t " << vertexZ << endl;      
      
      OUT << " \t " << "3" << " \t " << 1 << " \t " << "1" << " \t " << -PID_decay << " \t " << "0" << " \t " << "0" << " \t " << ep.Px() << " \t " << ep.Py() << " \t " << ep.Pz() << " \t " << ep.E() << " \t " << ep.M() << " \t " << vertexX  << " \t " << vertexY << " \t " << vertexZ << endl;      
      
      OUT << " \t " << "4" << " \t " << -1 << " \t " << "1" << " \t " << PID_decay << " \t " << "0" << " \t " << "0" << " \t " << em.Px() << " \t " << em.Py() << " \t " << em.Pz() << " \t " << em.E() << " \t " << em.M() << " \t " << vertexX  << " \t " << vertexY << " \t " << vertexZ << endl;      
      
  }
  
//   cout << counter1 << " " << counter2 << " " << counter3 << " " << counter4 << " " << counter5 << endl;
      
        OUT.close(); 
}