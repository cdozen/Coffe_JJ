#define myntuple_cxx
#include "myntuple.h"
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TLorentzVector.h"
#include "TPoint.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//#define muon_mass  0.105658
#define muon_mass 0.10565837
#define jpsi_mass 3.0967


//float raw_muM  =0.10565837; 

//order mode, 1--order by higer mass, m(11)>m(12), m(21)>m(22),  m(11)>m(21), 
//order mode, 2--order by higher mass for each combination,  (m(11)-mymV)<(m(21)-mymV), 
//order ==3 for by mV mass, (m(11)-mV)<(m(12)-mV), (m(21)-mV)<(m(22)-mV),  (m(11)-mymV)< (m(21)-mymV),
#define myordermode 1  //default is 1

//11=Y(1S) mumu <Y(1S), 
//#define mychannel 11

//12=Y(1S), no  mumu <Y(1S) cut
//#define mychannel 12


//13=test virtual Y*Y*
//#define mychannel 13


//21=J/psi mumu <m(Jpsi), 
//#define mychannel 21

//22=J/psi no mumu mass cut 
//#define mychannel 22


//55=Y1sY1s 
//#define mychannel 55

//66=JpsiJpsi
#define mychannel 66


//test VV choice
//#define mychannel 99
//Y1s V
//#define mychannel 991
//Jpsi V
//#define mychannel 992


//test VV choice + Y1s+ Y1s*
//#define mychannel 999


struct PairedMuonIdx {
  int p11;
  int p12;
  int p21;
  int p22;
};

void swap_two_paired_pair( PairedMuonIdx & myp1,  PairedMuonIdx & myp2 )
{
  int mytmp1, mytmp2;
  mytmp1=myp1.p11;  mytmp2=myp1.p12; 
  myp1.p11=myp2.p11;  myp1.p12=myp2.p12;
  myp2.p11=mytmp1;  myp2.p12=mytmp2;

  mytmp1=myp1.p21;  mytmp2=myp1.p22; 
  myp1.p21=myp2.p21;  myp1.p22=myp2.p22;
  myp2.p21=mytmp1;  myp2.p22=mytmp2;
}

void swap_one_paired_pair( PairedMuonIdx & myp )
{
  int mytmp1, mytmp2;
  mytmp1=myp.p11;  mytmp2=myp.p12; 
  myp.p11=myp.p21;  myp.p12=myp.p22;
  myp.p21=mytmp1;  myp.p22=mytmp2;
}

void swap_one_pair( PairedMuonIdx & myp, int whichpair )
{
  int mytmp;
  if( whichpair==1 ) {
    mytmp=myp.p11; 
    myp.p11=myp.p12; myp.p12=mytmp;
  }
  else if( whichpair==2 ) {
    mytmp=myp.p21; 
    myp.p21=myp.p22; myp.p22=mytmp;
  }//else

}


//added by hwen

void arange(float* arr, int num)
{
    for(int i=0; i<num-1; i++){
    if(arr[i]>arr[i+1])
        {
        float temp;
        temp = arr[i];arr[i]=arr[i+1];
        arr[i+1] =temp;
        }

    }

}
//end added by hwen
 
void myntuple::Loop(TString outputname)
{  

ofstream eventselection("selected_eventlist.txt");
eventselection << "#run"<<":"<< "#lumi "<<":"<<"#event"<<":"<< "DoubleJpsi"<<":"<<"4MuMass"<<"\n";
//eventselection << setw(10) << "#run"<<"\t"<< setw(10) << "#lumi "<<"\t"<< setw(10) <<"#evt"<<"\t"<< setw(10) << "DoubleJpsi"<<"\t"<< setw(10) << "4MuMass"<<"\n";

 TFile* myhbk = new TFile (outputname,"recreate");

  TH2F* myM12VsM34 = new TH2F("myM12VsM34","myM12VsM34",200, 0,20, 200, 0,20);  

  TH2F* myxJHUm12vsm34 = new TH2F("myxJHUm12vsm34","myxJHUm12vsm34",2000, 0,20,2000, 0,20);
  TH2F* myxJHUm14vsm23 = new TH2F("myxJHUm14vsm23","myxJHUm14vsm23",2000, 0,20,2000, 0,20);

  TH2F* myxJHUEtaVsRap = new TH2F("myxJHUEtaVsRap","myxJHUEtaVsRap",210, -10.5,10.5, 210, -10.5,10.5);  
  TH1F* myxJHUEta = new TH1F("myxJHUEta","myxJHUEta",210, -10.5,10.5); 
  TH1F* mydau1JHUEta = new TH1F("mydau1JHUEta","mydau1JHUEta",210, -10.5,10.5); 
  TH1F* mydau2JHUEta = new TH1F("mydau2JHUEta","mydau2JHUEta",210, -10.5,10.5); 
  TH1F* mydau1mupJHUEta = new TH1F("mydau1mupJHUEta","mydau1mupJHUEta",210, -10.5,10.5); 
  TH1F* mydau1mumJHUEta = new TH1F("mydau1mumJHUEta","mydau1mumJHUEta",210, -10.5,10.5); 
  TH1F* mydau2mupJHUEta = new TH1F("mydau2mupJHUEta","mydau2mupJHUEta",210, -10.5,10.5); 
  TH1F* mydau2mumJHUEta = new TH1F("mydau2mumJHUEta","mydau2mumJHUEta",210, -10.5,10.5); 


  TH1F* myJHUXmass = new TH1F("myJHUXmass","myJHUXmass",2600, 0,26);
  TH1F* myJHUXMuon12mass = new TH1F("myJHUXMuon12mass","myJHUXMuon12mass",2000, 0,20);
  TH1F* myJHUXMuon34mass = new TH1F("myJHUXMuon34mass","myJHUXMuon34mass",2000, 0,20);
  TH1F* myJHUXMuon14mass = new TH1F("myJHUXMuon14mass","myJHUXMuon14mass",2000, 0,20);
  TH1F* myJHUXMuon23mass = new TH1F("myJHUXMuon23mass","myJHUXMuon23mass",2000, 0,20);
  TH1F* myJHUXMuon13mass = new TH1F("myJHUXMuon13mass","myJHUXMuon13mass",2000, 0,20);
  TH1F* myJHUXMuon24mass = new TH1F("myJHUXMuon24mass","myJHUXMuon24mass",2000, 0,20);

  TH1F* myJHUXMuon14DeltaR = new TH1F("myJHUXMuon14DeltaR","myJHUXMuon14DeltaR",1100, -0.5,10.5); 
  TH1F* myJHUXMuon13DeltaR = new TH1F("myJHUXMuon13DeltaR","myJHUXMuon13DeltaR",1100, -0.5,10.5); 
  TH1F* myJHUXMuon24DeltaR = new TH1F("myJHUXMuon24DeltaR","myJHUXMuon24DeltaR",1100, -0.5,10.5); 
  TH1F* myJHUXMuon23DeltaR = new TH1F("myJHUXMuon23DeltaR","myJHUXMuon23DeltaR",1100, -0.5,10.5); 
  TH1F* myJHUXMuon12DeltaR = new TH1F("myJHUXMuon12DeltaR","myJHUXMuon12DeltaR",1100, -0.5,10.5); 
  TH1F* myJHUXMuon34DeltaR = new TH1F("myJHUXMuon34DeltaR","myJHUXMuon34DeltaR",1100, -0.5,10.5); 
  TH1F* mydau1mupJHUpt = new TH1F("mydau1mupJHUpt","mydau1mupJHUpt",1100, -0.5,10.5); 
  TH1F* mydau1mumJHUpt = new TH1F("mydau1mumJHUpt","mydau1mumJHUpt",1100, -0.5,10.5); 
  TH1F* mydau2mupJHUpt = new TH1F("mydau2mupJHUpt","mydau2mupJHUpt",1100, -0.5,10.5); 
  TH1F* mydau2mumJHUpt = new TH1F("mydau2mumJHUpt","mydau2mumJHUpt",1100, -0.5,10.5); 
  TH1F* myxJHUpt = new TH1F("myxJHUpt","myxJHUpt",2100, -0.5,20.5); 
  TH1F* mydau1JHUpt = new TH1F("mydau1JHUpt","mydau1JHUpt",2100, -0.5,20.5); 
  TH1F* mydau2JHUpt = new TH1F("mydau2JHUpt","mydau2JHUpt",2100, -0.5,20.5); 
  TH1F* myxJHUp = new TH1F("myxJHUp","myxJHUp",501, -0.5,500.5);
  //Reco kinematic distribution
  TH1F* recomuonpt1st = new TH1F("recomuonpt1st","recomuonpt1st",210, -0.5,20.5);
  TH1F* recomuonpt2nd = new TH1F("recomuonpt2nd","recomuonpt2nd",210, -0.5,20.5);
  TH1F* recomuonpt3rd = new TH1F("recomuonpt3rd","recomuonpt3rd",210, -0.5,20.5);
  TH1F* recomuonpt4th = new TH1F("recomuonpt4th","recomuonpt4th",210, -0.5,20.5);
  TH1F* recohdaupt1st = new TH1F("recohdaupt1st","recohdaupt1st",210,-0.5,20.5);
  TH1F* recohdaupt2nd = new TH1F("recohdaupt2nd","recohdaupt2nd",210,-0.5,20.5);
  TH1F* recohdaueta1st = new TH1F("recohdaueta1st","recohdaueta1st",210,-10.5,10.5);
  TH1F* recohdaueta2nd = new TH1F("recohdaueta2nd","recohdaueta2nd",210,-10.5,10.5);
  TH1F* recomuoneta1st = new TH1F("recomuoneta1st","recomuoneta1st",210,-10.5,10.5);
  TH1F* recomuoneta2nd = new TH1F("recomuoneta2nd","recomuoneta2nd",210,-10.5,10.5);
  TH1F* recomuoneta3rd = new TH1F("recomuoneta3rd","recomuoneta3rd",210,-10.5,10.5);
  TH1F* recomuoneta4th = new TH1F("recomuoneta4th","recomuoneta4th",210,-10.5,10.5);

  TH1F* myrecoMuon14DeltaR = new TH1F("myrecoMuon14DeltaR","myrecoMuon14DeltaR",210, -0.5,20.5);
  TH1F* myrecoMuon13DeltaR = new TH1F("myrecoMuon13DeltaR","myrecoMuon13DeltaR",210, -0.5,20.5);
  TH1F* myrecoMuon24DeltaR = new TH1F("myrecoMuon24DeltaR","myrecoMuon24DeltaR",210, -0.5,20.5);
  TH1F* myrecoMuon23DeltaR = new TH1F("myrecoMuon23DeltaR","myrecoMuon23DeltaR",210, -0.5,20.5);
  TH1F* myrecoMuon12DeltaR = new TH1F("myrecoMuon12DeltaR","myrecoMuon12DeltaR",210, -0.5,20.5);
  TH1F* myrecoMuon34DeltaR = new TH1F("myrecoMuon34DeltaR","myrecoMuon34DeltaR",210, -0.5,20.5);
  TH1F* myrecodau1muppt = new TH1F("myrecodau1muppt","myrecodau1muppt",210, -0.5,20.5);
  TH1F* myrecodau1mumpt = new TH1F("myrecodau1mumpt","myrecodau1mumpt",210, -0.5,20.5);
  TH1F* myrecodau2muppt = new TH1F("myrecodau2muppt","myrecodau2muppt",210, -0.5,20.5);
  TH1F* myrecodau2mumpt = new TH1F("myrecodau2mumpt","myrecodau2mumpt",210, -0.5,20.5);

  TH1F* myrecodau1mupEta = new TH1F("myrecodau1mupEta","myrecodau1mupEta",210, -10.5,10.5);
  TH1F* myrecodau1mumEta = new TH1F("myrecodau1mumEta","myrecodau1mumEta",210, -10.5,10.5);
  TH1F* myrecodau2mupEta = new TH1F("myrecodau2mupEta","myrecodau2mupEta",210, -10.5,10.5);
  TH1F* myrecodau2mumEta = new TH1F("myrecodau2mumEta","myrecodau2mumEta",210, -10.5,10.5);


  TH1F* myrecodau1pt = new TH1F("myrecodau1pt","myrecodau1pt",210, -0.5,20.5);
  TH1F* myrecodau2pt = new TH1F("myrecodau2pt","myrecodau2pt",210, -0.5,20.5);
  TH1F* myrecopt = new TH1F("myrecopt","myrecopt",310, -0.5,30.5);
  TH1F* myrecoEta = new TH1F("myrecoEta","myrecoEta",210, -10.5,10.5);
//low mass sample histograms
  TH1F* myM12forLowMassOS = new TH1F("myM12forLowMassOS","myM12forLowMassOS",4000,0,20.0);
  myM12forLowMassOS->GetXaxis()->SetTitle("m(#mu^{+}_{1}#mu^{-}_{2}) for Low Mass OS+SS [GeV]");
  TH1F* myM12masserrforLowMassOS = new TH1F("myM12masserrforLowMassOS","myM12masserrforLowMassOS",500,0,0.5);
  myM12masserrforLowMassOS->GetXaxis()->SetTitle("#sigma_{m(#mu^{+}_{1}#mu^{-}_{2})} for Low Mass OS+SS [GeV]");
  TH1F* myMu1EtaforLowMassOS = new TH1F("myMu1EtaforLowMassOS","myMu1EtaforLowMassOS",60,-3,3);
  myMu1EtaforLowMassOS->GetXaxis()->SetTitle("#eta(#mu_{1})");
  TH1F* myMu2EtaforLowMassOS = new TH1F("myMu2EtaforLowMassOS","myMu2EtaforLowMassOS",60,-3,3);
  myMu2EtaforLowMassOS->GetXaxis()->SetTitle("#eta(#mu_{2})");
  TH1F* my4mumasswithm12atlowside = new TH1F("my4mumasswithm12atlowside","my4mumasswithm12atlowside",130,13,26.0);
  my4mumasswithm12atlowside->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* my4mumasswithm12atlowsideshift = new TH1F("my4mumasswithm12atlowsideshift","my4mumasswithm12atlowsideshift",130,13,26.0);
  my4mumasswithm12atlowsideshift->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* my4mumasswithm12athighside = new TH1F("my4mumasswithm12athighside","my4mumasswithm12athighside",130,13,26.0);
  my4mumasswithm12athighside->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");  
  TH1F* my4mumasswithm12athighsideshift = new TH1F("my4mumasswithm12athighsideshift","my4mumasswithm12athighsideshift",130,13,26.0);
  my4mumasswithm12athighsideshift->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* my4mumasswithm12atmiddleside = new TH1F("my4mumasswithm12atmiddleside","my4mumasswithm12atmiddleside",130,13,26.0);
  my4mumasswithm12atmiddleside->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* my4mumasswithm12atmiddlesidedefault = new TH1F("my4mumasswithm12atmiddlesidedefault","my4mumasswithm12atmiddlesidedefault",130,13,26.0);
  my4mumasswithm12atmiddlesidedefault->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");  


 TH1F* myRunNum=new TH1F("myRunNum","myRunNum",500,306000,306500);
 TH1F* myARCDimuMassPullUpsi=new TH1F("myARCDimuMassPullUpsi","myARCDimuMassPullUpsi",1000,-5,5.0);
 TH1F* myARCDimuMassPullJpsi=new TH1F("myARCDimuMassPullJpsi","myARCDimuMassPullJpsi",1000,-5,5.0);
 TH1F* myARCDimuMassPullUpsiScaled=new TH1F("myARCDimuMassPullUpsiScaled","myARCDimuMassPullUpsiScaled",1000,-5,5.0);
 TH1F* myARCDimuMassPullJpsiScaled=new TH1F("myARCDimuMassPullJpsiScaled","myARCDimuMassPullJpsiScaled",1000,-5,5.0);
 TH1F* myARCDimuMass=new TH1F("myARCDimuMass","myARCDimuMass",100000,0,500.0);
  TH1F* myMuMuChg0ARCmass = new TH1F("myMuMuChg0ARCmass","myMuMuChg0ARCmass",100000,0,500.0);  
  myMuMuChg0ARCmass->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuChgp2ARCmass = new TH1F("myMuMuChgp2ARCmass","myMuMuChgp2ARCmass",100000,0,500.0);  
  myMuMuChgp2ARCmass->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");  
  TH1F* myMuMuChgm2ARCmass = new TH1F("myMuMuChgm2ARCmass","myMuMuChgm2ARCmass",100000,0,500.0);  
  myMuMuChgm2ARCmass->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
  TH1F* myARCMuMuHighmasserr = new TH1F("myARCMuMuHighmasserr","myARCMuMuHighmasserr",500,0,0.5);  
  myARCMuMuHighmasserr->GetXaxis()->SetTitle("#sigma_{m(#mu^{+}#mu^{-})}(Rapidity) GeV");
  TH1F* myARCMuMuHighmasserrEBE = new TH1F("myARCMuMuHighmasserrEBE","myARCMuMuHighmasserrEBE",500,0,0.5);  
  myARCMuMuHighmasserrEBE->GetXaxis()->SetTitle("#sigma_{m(#mu^{+}#mu^{-})}(EBE) GeV");
  TH1F* myMuMu01Chgp2ARCmassafterselection = new TH1F("myMuMu01Chgp2ARCmassafterselection","myMuMu01Chgp2ARCmassafterselection",100000,0,500.0);  
  myMuMu01Chgp2ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMu02Chgm2ARCmassafterselection = new TH1F("myMuMu02Chgm2ARCmassafterselection","myMuMu02Chgm2ARCmassafterselection",100000,0,500.0);  
  myMuMu02Chgm2ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMu11Chg0ARCmassafterselection = new TH1F("myMuMu11Chg0ARCmassafterselection","myMuMu11Chg0ARCmassafterselection",100000,0,500.0);  
  myMuMu11Chg0ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMu12Chg0ARCmassafterselection = new TH1F("myMuMu12Chg0ARCmassafterselection","myMuMu12Chg0ARCmassafterselection",100000,0,500.0);  
  myMuMu12Chg0ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMu21Chg0ARCmassafterselection = new TH1F("myMuMu21Chg0ARCmassafterselection","myMuMu21Chg0ARCmassafterselection",100000,0,500.0);  
  myMuMu21Chg0ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMu22Chg0ARCmassafterselection = new TH1F("myMuMu22Chg0ARCmassafterselection","myMuMu22Chg0ARCmassafterselection",100000,0,500.0);  
  myMuMu22Chg0ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");

 TH1F* myMuMuwith2tightmuChg0ARCmassafterselection = new TH1F("myMuMuwith2tightmuChg0ARCmassafterselection","myMuMuwith2tightmuChg0ARCmassafterselection",100000,0,500.0);  

 TH1F* myNY1swith2tightmusARCafterselection = new TH1F("myNY1swith2tightmusARCafterselection","myNY1swith2tightmusARCafterselection",11,-0.5,10.5);  

  TH1F* myMuMuChg0ARCmasswith2tightmuEE = new TH1F("myMuMuChg0ARCmasswith2tightmuEE","myMuMuChg0ARCmasswith2tightmuEE",100000,0,500.0);  
  TH1F* myMuMuChg0ARCmasswith2tightmuEB = new TH1F("myMuMuChg0ARCmasswith2tightmuEB","myMuMuChg0ARCmasswith2tightmuEB",100000,0,500.0);  
  TH1F* myMuMuChg0ARCmasswith2tightmuBB = new TH1F("myMuMuChg0ARCmasswith2tightmuBB","myMuMuChg0ARCmasswith2tightmuBB",100000,0,500.0);  
 
  TH1F* myAnotherMuMuChg0ARCwithY1sonthismumumass = new TH1F("myAnotherMuMuChg0ARCwithY1sonthismumumass","myAnotherMuMuChg0ARCwithY1sonthismumumass",100000,0,500.0);  
  TH1F* myFourmuChg0ARCmass = new TH1F("myFourmuChg0ARCmass","myFourmuChg0ARCmass",5000,0,500.0);  
  TH1F* myFourmuChg0ARCmassWithanotherdimult9dot2 = new TH1F("myFourmuChg0ARCmassWithanotherdimult9dot2","myFourmuChg0ARCmassWithanotherdimult9dot2",5000,0,500.0);  

 TH1F* myFourmuChg0ARCmassandanotherdimultY1s = new TH1F("myFourmuChg0ARCmassandanotherdimultY1s","myFourmuChg0ARCmassandanotherdimultY1s",5000,0,500.0);  
  TH1F* myFourmuChg0ARCmassandanotherdimultY1sEBE = new TH1F("myFourmuChg0ARCmassandanotherdimultY1sEBE","myFourmuChg0ARCmassandanotherdimultY1sEBE",5000,0,500.0);  
  

  TH1F* myMuMuonlymass = new TH1F("myMuMuonlymass","myMuMuonlymass",100000,0,500.0);  
  myMuMuonlymass->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuOnlyIso = new TH1F("myMuMuOnlyIso","myMuMuOnlyIso",50,0,5.0);


  TH1F* myMuMumassforV1highpair = new TH1F("myMuMumassforV1highpair","myMuMumassforV1highpair",100000,0,500.0);  
  myMuMumassforV1highpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{hh} GeV");
  TH1F* myMuMumassforV1lowpair = new TH1F("myMuMumassforV1lowpair","myMuMumassforV1lowpair",100000,0,500.0);  
  myMuMumassforV1lowpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{lh} GeV");
  TH1F* myMuMumassformumulowpair = new TH1F("myMuMumassformumulowpair","myMuMumassformumulowpair",100000,0,500.0);  
  myMuMumassformumulowpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{ll} GeV");
  TH1F* myMuMumassformumuhighpair = new TH1F("myMuMumassformumuhighpair","myMuMumassformumuhighpair",100000,0,500.0);  
  myMuMumassformumuhighpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{hl} GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1 = new TH1F("myMuMuMuMumassV1mumubelowV1","myMuMuMuMumassV1mumubelowV1",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");


  TH1F* myMuMuMuMumassV1mumubelowV1ifSecondOption = new TH1F("myMuMuMuMumassV1mumubelowV1ifSecondOption","myMuMuMuMumassV1mumubelowV1ifSecondOption",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1ifSecondOption->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1ifSecondOptionDiff = new TH1F("myMuMuMuMumassV1mumubelowV1ifSecondOptionDiff","myMuMuMuMumassV1mumubelowV1ifSecondOptionDiff",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1ifSecondOptionDiff->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumMaxDeltaEta =new TH1F("myMuMuMuMumMaxDeltaEta","myMuMuMuMumMaxDeltaEta",50,0,5);
 TH1F* myMuMuMuMumassConstraintV1mumubelowV1nolightmeson = new TH1F("myMuMuMuMumassConstraintV1mumubelowV1nolightmeson","myMuMuMuMumassConstraintV1mumubelowV1nolightmeson",100000,0.0,1000.0);

  TH1F* myMuMuMuMumassV1mumubelowV1nolightmeson = new TH1F("myMuMuMuMumassV1mumubelowV1nolightmeson","myMuMuMuMumassV1mumubelowV1nolightmeson",100000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1nolightmeson->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1withlightmeson = new TH1F("myMuMuMuMumassV1mumubelowV1withlightmeson","myMuMuMuMumassV1mumubelowV1withlightmeson",100000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1withlightmeson->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1mumubelowV1nolightmesonDiff = new TH1F("myMuMuMuMumassV1mumubelowV1nolightmesonDiff","myMuMuMuMumassV1mumubelowV1nolightmesonDiff",100000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1nolightmesonDiff->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1withlightmesonDiff = new TH1F("myMuMuMuMumassV1mumubelowV1withlightmesonDiff","myMuMuMuMumassV1mumubelowV1withlightmesonDiff",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1withlightmesonDiff->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuPPDeltapxpypz = new TH1F("myMuPPDeltapxpypz","myMuPPDeltapxpypz",10000,0,1000.0);
  myMuPPDeltapxpypz->GetXaxis()->SetTitle("|#Delta Px|+|#Delta Py|+|#Delta Pz| between #mu^{+}#mu^{+} [GeV]");
  TH1F* myMuMMDeltapxpypz = new TH1F("myMuMMDeltapxpypz","myMuMMDeltapxpypz",10000,0,1000.0);
  myMuMMDeltapxpypz->GetXaxis()->SetTitle("|#Delta Px|+|#Delta Py|+|#Delta Pz| between #mu^{-}#mu^{-} [GeV]");


  TH1F* myMuMuMuMumassV1mumubelowV1cowboyVscowboy = new TH1F("myMuMuMuMumassV1mumubelowV1cowboyVscowboy","myMuMuMuMumassV1mumubelowV1cowboyVscowboy",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1cowboyVscowboy->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1cowboyVsseagull = new TH1F("myMuMuMuMumassV1mumubelowV1cowboyVsseagull","myMuMuMuMumassV1mumubelowV1cowboyVsseagull",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1cowboyVsseagull->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1seagullVscowboy = new TH1F("myMuMuMuMumassV1mumubelowV1seagullVscowboy","myMuMuMuMumassV1mumubelowV1seagullVscowboy",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1seagullVscowboy->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1seagullVsseagull = new TH1F("myMuMuMuMumassV1mumubelowV1seagullVsseagull","myMuMuMuMumassV1mumubelowV1seagullVsseagull",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1seagullVsseagull->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1mumuWithVIso0dot1belowV1 = new TH1F("myMuMuMuMumassV1mumuWithVIso0dot1belowV1","myMuMuMuMumassV1mumuWithVIso0dot1belowV1",10000,0,1000.0);
  myMuMuMuMumassV1mumuWithVIso0dot1belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1mumuWithVIso0dot2belowV1 = new TH1F("myMuMuMuMumassV1mumuWithVIso0dot2belowV1","myMuMuMuMumassV1mumuWithVIso0dot2belowV1",10000,0,1000.0);
  myMuMuMuMumassV1mumuWithVIso0dot2belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1mumuWithVIso0dot5belowV1 = new TH1F("myMuMuMuMumassV1mumuWithVIso0dot5belowV1","myMuMuMuMumassV1mumuWithVIso0dot5belowV1",10000,0,1000.0);
  myMuMuMuMumassV1mumuWithVIso0dot5belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1highestmuWithVIso0dot1belowV1 = new TH1F("myMuMuMuMumassV1highestmuWithVIso0dot1belowV1","myMuMuMuMumassV1highestmuWithVIso0dot1belowV1",10000,0,1000.0);
  myMuMuMuMumassV1highestmuWithVIso0dot1belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1highestmuWithVIso0dot2belowV1 = new TH1F("myMuMuMuMumassV1highestmuWithVIso0dot2belowV1","myMuMuMuMumassV1highestmuWithVIso0dot2belowV1",10000,0,1000.0);
  myMuMuMuMumassV1highestmuWithVIso0dot2belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1highestmuWithVIso0dot5belowV1 = new TH1F("myMuMuMuMumassV1highestmuWithVIso0dot5belowV1","myMuMuMuMumassV1highestmuWithVIso0dot5belowV1",10000,0,1000.0);
  myMuMuMuMumassV1highestmuWithVIso0dot5belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1mumubelowV1LowSide = new TH1F("myMuMuMuMumassV1mumubelowV1LowSide","myMuMuMuMumassV1mumubelowV1LowSide",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1LowSide->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1HighSide = new TH1F("myMuMuMuMumassV1mumubelowV1HighSide","myMuMuMuMumassV1mumubelowV1HighSide",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1HighSide->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1mumubelowV1NolightmesonLowSide = new TH1F("myMuMuMuMumassV1mumubelowV1NolightmesonLowSide","myMuMuMuMumassV1mumubelowV1NolightmesonLowSide",10000,0,1000.0); 
  myMuMuMuMumassV1mumubelowV1NolightmesonLowSide->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1NolightmesonHighSide = new TH1F("myMuMuMuMumassV1mumubelowV1NolightmesonHighSide","myMuMuMuMumassV1mumubelowV1NolightmesonHighSide",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1NolightmesonHighSide->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1mumubelowV1LowSideShift = new TH1F("myMuMuMuMumassV1mumubelowV1LowSideShift","myMuMuMuMumassV1mumubelowV1LowSideShift",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1LowSideShift->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1HighSideShift = new TH1F("myMuMuMuMumassV1mumubelowV1HighSideShift","myMuMuMuMumassV1mumubelowV1HighSideShift",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1HighSideShift->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1NolightmesonLowSideShift = new TH1F("myMuMuMuMumassV1mumubelowV1NolightmesonLowSideShift","myMuMuMuMumassV1mumubelowV1NolightmesonLowSideShift",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1NolightmesonLowSideShift->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1NolightmesonHighSideShift = new TH1F("myMuMuMuMumassV1mumubelowV1NolightmesonHighSideShift","myMuMuMuMumassV1mumubelowV1NolightmesonHighSideShift",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1NolightmesonHighSideShift->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

 TH1F* myMuMuMuMumassDiffV1mumubelowV1nolightmesoninaonthercombination = new TH1F("myMuMuMuMumassDiffV1mumubelowV1nolightmesoninaonthercombination","myMuMuMuMumassDiffV1mumubelowV1nolightmesoninaonthercombination",10000,0,1000.0);

  TH1F* myMuMuMuMumassDiffV1mumubelowV1 = new TH1F("myMuMuMuMumassDiffV1mumubelowV1","myMuMuMuMumassDiffV1mumubelowV1",10000,0,1000.0);
  TH1F* myMuMu1MassWithoutlightmesonatunselectedcombination = new TH1F("myMuMu1MassWithoutlightmesonatunselectedcombination","myMuMu1MassWithoutlightmesonatunselectedcombination",400,0,20.0);
  TH1F* myMuMu2MassWithoutlightmesonatunselectedcombination = new TH1F("myMuMu2MassWithoutlightmesonatunselectedcombination","myMuMu2MassWithoutlightmesonatunselectedcombination",400,0,20.0);

  TH1F* myMuMu1MassWithlightmesonatunselectedcombination = new TH1F("myMuMu1MassWithlightmesonatunselectedcombination","myMuMu1MassWithlightmesonatunselectedcombination",400,0,20.0);
  TH1F* myMuMu2MassWithlightmesonatunselectedcombination = new TH1F("myMuMu2MassWithlightmesonatunselectedcombination","myMuMu2MassWithlightmesonatunselectedcombination",400,0,20.0);

  TH1F* myMuMu1Massat18dot5GeV = new TH1F("myMuMu1Massat18dot5GeV","myMuMu1Massat18dot5GeV",400,0,20.0);
  TH1F* myMuMu1MassatSideband = new TH1F("myMuMu1MassatSideband","myMuMu1MassatSideband",400,0,20.0);
  TH1F* myMuMu2Massat18dot5GeV = new TH1F("myMuMu2Massat18dot5GeV","myMuMu2Massat18dot5GeV",200,0,10.0);
  TH1F* myMuMu2MassatSideband = new TH1F("myMuMu2MassatSideband","myMuMu2MassatSideband",200,0,10.0);

  TH1F* myFourMuPtat18dot5GeV = new TH1F("myFourMuPtat18dot5GeV","myFourMuPtat18dot5GeV",50,0,50.0);
  TH1F* myFourMuPtatSideband = new TH1F("myFourMuPtatSideband","myFourMuPtatSideband",50,0,50.0);
  TH1F* myFourMuPat18dot5GeV = new TH1F("myFourMuPat18dot5GeV","myFourMuPat18dot5GeV",100,0,100.0);
  TH1F* myFourMuPatSideband = new TH1F("myFourMuPatSideband","myFourMuPatSideband",100,0,50.0);

  TH1F* myFourMuRapidityat18dot5GeV = new TH1F("myFourMuRapidityat18dot5GeV","myFourMuRapidityat18dot5GeV",32,-3.2,3.2);
  TH1F* myFourMuRapidityatSideband = new TH1F("myFourMuRapidityatSideband","myFourMuRapidityatSideband",32,-3.2,3.2);
  TH1F* myMu1Isoat18dot5GeV = new TH1F("myMu1Isoat18dot5GeV","myMu1Isoat18dot5GeV",50,0,5.0);
  TH1F* myMu2Isoat18dot5GeV = new TH1F("myMu2Isoat18dot5GeV","myMu2Isoat18dot5GeV",50,0,5.0);
  TH1F* myMu3Isoat18dot5GeV = new TH1F("myMu3Isoat18dot5GeV","myMu3Isoat18dot5GeV",50,0,5.0);
  TH1F* myMu4Isoat18dot5GeV = new TH1F("myMu4Isoat18dot5GeV","myMu4Isoat18dot5GeV",50,0,5.0);
  TH1F* myDeltaR4minOppositeMuat18dot5GeV = new TH1F("myDeltaR4minOppositeMuat18dot5GeV","myDeltaR4minOppositeMuat18dot5GeV",500,0,5.0);
  TH1F* myDeltaR4minSameSignMuat18dot5GeV = new TH1F("myDeltaR4minSameSignMuat18dot5GeV","myDeltaR4minSameSignMuat18dot5GeV",500,0,5.0);

  TH1F* myMu1Ptat18dot5GeV = new TH1F("myMu1Ptat18dot5GeV","myMu1Ptat18dot5GeV",50,0,50.0);
  TH1F* myMu1PtatSideband = new TH1F("myMu1PtatSideband","myMu1PtatSideband",50,0,50.0);
  TH1F* myMu2Ptat18dot5GeV = new TH1F("myMu2Ptat18dot5GeV","myMu2Ptat18dot5GeV",50,0,50.0);
  TH1F* myMu2PtatSideband = new TH1F("myMu2PtatSideband","myMu2PtatSideband",50,0,50.0);
  TH1F* myMu3Ptat18dot5GeV = new TH1F("myMu3Ptat18dot5GeV","myMu3Ptat18dot5GeV",50,0,50.0);
  TH1F* myMu3PtatSideband = new TH1F("myMu3PtatSideband","myMu3PtatSideband",50,0,50.0);
  TH1F* myMu4Ptat18dot5GeV = new TH1F("myMu4Ptat18dot5GeV","myMu4Ptat18dot5GeV",50,0,50.0);
  TH1F* myMu4PtatSideband = new TH1F("myMu4PtatSideband","myMu4PtatSideband",50,0,50.0);
  TH1F* myMuMu1Ptat18dot5GeV = new TH1F("myMuMu1Ptat18dot5GeV","myMuMu1Ptat18dot5GeV",50,0,50.0);
  TH1F* myMuMu1PtatSideband = new TH1F("myMuMu1PtatSideband","myMuMu1PtatSideband",50,0,50.0);
  TH1F* myMuMu2Ptat18dot5GeV = new TH1F("myMuMu2Ptat18dot5GeV","myMuMu2Ptat18dot5GeV",50,0,50.0);
  TH1F* myMuMu2PtatSideband = new TH1F("myMuMu2PtatSideband","myMuMu2PtatSideband",50,0,50.0);
  TH1F* myFourMuFLSigat18dot5GeV = new TH1F("myFourMuFLSigat18dot5GeV","myFourMuFLSigat18dot5GeV",50,-25.0,25.0);
  TH1F* myFourMuFLSigatSideband = new TH1F("myFourMuFLSigatSideband","myFourMuFLSigatSideband",50,-25.0,25.0);  
  TH1F* myMuMu1Ctauat18dot5GeV = new TH1F("myMuMu1Ctauat18dot5GeV","myMuMu1Ctauat18dot5GeV",2000,-0.5,0.5);
  TH1F* myMuMu1CtauatSideband = new TH1F("myMuMu1CtauatSideband","myMuMu1CtauatSideband",2000,-0.5,0.5);
  TH1F* myMuMu2Ctauat18dot5GeV = new TH1F("myMuMu2Ctauat18dot5GeV","myMuMu2Ctauat18dot5GeV",2000,-0.5,0.5);
  TH1F* myMuMu2CtauatSideband = new TH1F("myMuMu2CtauatSideband","myMuMu2CtauatSideband",2000,-0.5,0.5);

  TH1F* my4MuCtauat18dot5GeV = new TH1F("my4MuCtauat18dot5GeV","my4MuCtauat18dot5GeV",2000,-0.5,0.5);
  TH1F* my4MuCtauatSideband = new TH1F("my4MuCtauatSideband","my4MuCtauatSideband",2000,-0.5,0.5);

  TH1F* myMuMuPairsDihedralat18dot5GeV = new TH1F("myMuMuPairsDihedralat18dot5GeV","myMuMuPairsDihedralat18dot5GeV",20,0,3.142);
  TH1F* myMuMuPairsDihedralatSideband = new TH1F("myMuMuPairsDihedralatSideband","myMuMuPairsDihedralatSideband",20,0,3.142);
  TH1F* myMuMuPairsHelicityat18dot5GeV = new TH1F("myMuMuPairsHelicityat18dot5GeV","myMuMuPairsHelicityat18dot5GeV",22,-1.1,1.1);
  TH1F* myMuMuPairsHelicityatSideband = new TH1F("myMuMuPairsHelicityatSideband","myMuMuPairsHelicityatSideband",22,-1.1,1.1);

  TH1F* myMupmumu1Helicityat18dot5GeVfine = new TH1F("myMupmumu1Helicityat18dot5GeVfine","myMupmumu1Helicityat18dot5GeVfine",2200,-1.1,1.1);
  TH1F* myMupmumu1HelicityatSidebandfine = new TH1F("myMupmumu1HelicityatSidebandfine","myMupmumu1HelicityatSidebandfine",2200,-1.1,1.1);
  TH1F* myMupmumu1Helicityfine = new TH1F("myMupmumu1Helicityfine","myMupmumu1Helicityfine",2200,-1.1,1.1);

  TH1F* myMupmumu1Helicityat18dot5GeV = new TH1F("myMupmumu1Helicityat18dot5GeV","myMupmumu1Helicityat18dot5GeV",22,-1.1,1.1);
  TH1F* myMupmumu1HelicityatSideband = new TH1F("myMupmumu1HelicityatSideband","myMupmumu1HelicityatSideband",22,-1.1,1.1);
  TH1F* myMupmumu2Helicityat18dot5GeV = new TH1F("myMupmumu2Helicityat18dot5GeV","myMupmumu2Helicityat18dot5GeV",22,-1.1,1.1);
  TH1F* myMupmumu2HelicityatSideband = new TH1F("myMupmumu2HelicityatSideband","myMupmumu2HelicityatSideband",22,-1.1,1.1);

  TH1F* myMuMuPairsabscosDihedralat18dot5GeV = new TH1F("myMuMuPairsabscosDihedralat18dot5GeV","myMuMuPairsabscosDihedralat18dot5GeV",10,0,1);
myMuMuPairsabscosDihedralat18dot5GeV->GetXaxis()->SetTitle("|cos(dohedral)|");
  TH1F* myMuMuPairsabscosDihedralatSideband = new TH1F("myMuMuPairsabscosDihedralatSideband","myMuMuPairsabscosDihedralatSideband",10,0,1.0);
myMuMuPairsabscosDihedralatSideband->GetXaxis()->SetTitle("|cos(dohedral)|");

  TH1F* myMuMu2Massat15dot7GeV = new TH1F("myMuMu2Massat15dot7GeV","myMuMu2Massat15dot7GeV",200,0,10.0);
 TH1F* myMu21Ptstartat18dot5GeV = new TH1F("myMu21Ptstartat18dot5GeV","myMu21Ptstartat18dot5GeV",50,0,50.0);
 TH1F* myMu21PtstartatSideband = new TH1F("myMu21PtstartatSideband","myMu21PtstartatSideband",50,0,50.0);
 TH1F* myMu22Ptstartat18dot5GeV = new TH1F("myMu22Ptstartat18dot5GeV","myMu22Ptstartat18dot5GeV",50,0,50.0);
 TH1F* myMu22PtstartatSideband = new TH1F("myMu22PtstartatSideband","myMu22PtstartatSideband",50,0,50.0);

 //asked 2d histogram
 TH2F* myDalitzmY1smupmasssqVsmmumumasssqat18GeV = new TH2F("myDalitzmY1smupmasssqVsmmumumasssqat18GeV","myDalitzmY1smupmasssqVsmmumumasssqat18GeV",4000,0,400.0, 4000, 0, 400.0); 
 myDalitzmY1smupmasssqVsmmumumasssqat18GeV->GetXaxis()->SetTitle("m^{2}(#Upsilon(1S)#mu^{+})  [GeV^{2}]");
 myDalitzmY1smupmasssqVsmmumumasssqat18GeV->GetYaxis()->SetTitle("m^{2}(#Upsilon(1S)#mu^{-})  [GeV^{2}]");

 TH2F* myFourMumassVssecondDimuMass = new TH2F("myFourMumassVssecondDimuMass","myFourMumassVssecondDimuMass",280,9,27.0, 320, 0, 16.0); 
 myFourMumassVssecondDimuMass->GetXaxis()->SetTitle("m(#Upsilon(1S)#mu^{+}#mu^{-})  [GeV]");
 myFourMumassVssecondDimuMass->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})  [GeV]");
 
 TH2F* mym3musqVssecondDimuMasssq = new TH2F("mym3musqVssecondDimuMasssq","mym3musqVssecondDimuMasssq", 4000,0,400.0, 4000, 0, 400.0); 
 mym3musqVssecondDimuMasssq->GetXaxis()->SetTitle("m^{2}(#Upsilon(1S)#mu^{+})  [GeV^{2}]");
 mym3musqVssecondDimuMasssq->GetYaxis()->SetTitle("m^{2}(#mu^{+}#mu^{-})  [GeV^{2}]");

 //plots for Greg
 TH1F* myWrongdimu1signal = new TH1F("myWrongdimu1signal","myWrongdimu1signal",2500,0,25.0);
 TH1F* myWrongdimu1sideband = new TH1F("myWrongdimu1sideband","myWrongdimu1sideband",2500,0,25.0);
 TH1F* myWrongdimu2signal = new TH1F("myWrongdimu2signal","myWrongdimu2signal",2500,0,25.0);
 TH1F* myWrongdimu2sideband = new TH1F("myWrongdimu2sideband","myWrongdimu2sideband",2500,0,25.0);
 
 //plot the six dimuon mass, mu1+mu2- -> Y, mu3+mu4- ->Y*
 TH2F* myMu12vsMu34 = new TH2F("myMu12vsMu34","myMu12vsMu34",2000, 0,20,2000, 0,20);
 TH2F* myMu14vsMu23 = new TH2F("myMu14vsMu23","myMu14vsMu23",2000, 0,20,2000, 0,20);
//add by hwen
TH1F* rapdiff = new TH1F("Rapdiff","Rapdiff",1000,0,10);
//end added by hwen

 TH1F* myMu12mass = new TH1F("myMu12mass","myMu12mass",2500,0,25.0);
 TH1F* myMu34mass = new TH1F("myMu34mass","myMu34mass",2500,0,25.0);
 TH1F* myMu14mass = new TH1F("myMu14mass","myMu14mass",2500,0,25.0);
 TH1F* myMu23mass = new TH1F("myMu23mass","myMu23mass",2500,0,25.0);
 TH1F* myMu13mass = new TH1F("myMu13mass","myMu13mass",2500,0,25.0);
 TH1F* myMu24mass = new TH1F("myMu24mass","myMu24mass",2500,0,25.0);
 myMu24mass->GetXaxis()->SetTitle("m(#mu^{-}_{2}#mu^{-}_{4}) GeV");
 myMu13mass->GetXaxis()->SetTitle("m(#mu^{+}_{1}#mu^{+}_{3}) GeV");
 myMu12mass->GetXaxis()->SetTitle("m(#mu^{+}_{1}#mu^{-}_{2}) GeV");
 myMu34mass->GetXaxis()->SetTitle("m(#mu^{+}_{3}#mu^{-}_{4}) GeV");
 myMu14mass->GetXaxis()->SetTitle("m(#mu^{+}_{1}#mu^{-}_{4}) GeV");
 myMu23mass->GetXaxis()->SetTitle("m(#mu^{-}_{2}#mu^{+}_{3}) GeV");

  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntries();
  cout<<"Total entries="<<nentries<<endl;

  int NumxJHUTotal=0;
  int NumxJHUinsideLHCbFid=0;
  int NumxJHUTotalwith4mu=0;
  int NumxJHUTotalwith2mu=0;
  int NumxJHUTotalwith0mu=0;
  int NlowmassOS=0;
  int NlowmassSS=0;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(jentry%10000==0) cout<<"I am running "<<jentry<<"th entries out of "<<nentries<<" total entries"<<endl;

    bool TrigThreeMuon=false;
    bool TrigThreeMuonJpsi=false;
    bool TrigThreeMuonUpsi=false;

    bool TrigThreeMuonJpsi3p5mu2=false;
   bool TrigThreeOpenMuonUpsi=false;
   bool TrigThreemuonMu2Upsilon5=false; 
   bool TrigThreemuon5_3dot5_2=false;
   bool TrigThreeOpenmuon5_3dot5_2=false;
   bool TrigPsiprime=false;
   bool TrigTripleMu5=false;
   bool TrigDoubleMu5IsoMu5=false;
   bool TrigMu8=false;
   bool TrigDiMu7Upsi=false;
   bool TrigDiMu5Upsi=false;
   bool TrigDiMu10BarrelUpsi=false;
   bool TrigDiMu12Eta1p5Upsi=false;
   bool TrigDiMu8BarrelUpsi=false;

    for(int i=0; i!=TrigRes->size(); ++i){ 
      //if(TrigNames->at(i).find("HLT_Trimuon")!=string::npos) cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;

      if(TrigNames->at(i).find("HLT_Trimuon5_3p5_2_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1)
        {
        // cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
           TrigThreemuon5_3dot5_2=true;
        }

     if( (TrigNames->at(i).find("HLT_Dimuon0_Jpsi3p5_Muon2_")!=string::npos && TrigRes->at(i)==1)
          )
        {
          TrigThreeMuonJpsi3p5mu2 = true;
          //cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
        }//if( (TrigNames->at(i).find("HLT_Dimuon7_Upsilon_")!=string::npos && TrigRes->at(i)==1)
   
  
      if(TrigNames->at(i).find("HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1)
        {
	//cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
         TrigThreeOpenmuon5_3dot5_2 =true;
        }

      if(TrigNames->at(i).find("HLT_Trimuon2_Upsilon5_Muon")!=string::npos && TrigRes->at(i)==1)
        {
          TrigThreemuonMu2Upsilon5=true;
          //cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
        }

      if((TrigNames->at(i).find("HLT_Dimuon0_Jpsi_Muon_")!=string::npos && TrigRes->at(i)==1) || (TrigNames->at(i).find("HLT_Dimuon0_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1 ))
	{
	  TrigThreeMuon=true;
	  //cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
	}
      if(TrigNames->at(i).find("HLT_Dimuon0_Jpsi_Muon_")!=string::npos && TrigRes->at(i)==1)
        {
          TrigThreeMuonJpsi=true;
        }
      if(TrigNames->at(i).find("HLT_Dimuon0_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1)
      //if(TrigNames->at(i).find("HLT_Trimuon5_3p5_2_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1)
        { 
	// cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
          TrigThreeMuonUpsi=true;
        }
      if(TrigNames->at(i).find("HLT_TrimuonOpen_5_3p5_2_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1)
        {
 	//cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
          TrigThreeOpenMuonUpsi=true;
        }
      if( (TrigNames->at(i).find("HLT_Dimuon5_PsiPrime_")!=string::npos && TrigRes->at(i)==1)     
	  || (TrigNames->at(i).find("HLT_Dimuon7_PsiPrime_")!=string::npos && TrigRes->at(i)==1) 
	  )
        { 
         TrigPsiprime = true;
        }//if( (TrigNames->at(i).find("HLT_Dimuon5_PsiPrime_")!=string::npos && TrigRes->at(i)==1)  
      if( (TrigNames->at(i).find("HLT_TripleMu5_")!=string::npos && TrigRes->at(i)==1)     
	  )
        { 
	  TrigTripleMu5 = true;
        }//if( (TrigNames->at(i).find("HLT_TripleMu5_")!=string::npos && TrigRes->at(i)==1) 
      if( (TrigNames->at(i).find("HLT_DoubleMu5_IsoMu5")!=string::npos && TrigRes->at(i)==1)     
	  )
        { 
	  TrigDoubleMu5IsoMu5 = true;
        }//if( (TrigNames->at(i).find("HLT_DoubleMu5_IsoMu5")!=string::npos && TrigRes->at(i)==1) 
      if( (TrigNames->at(i).find("HLT_Mu8_v")!=string::npos && TrigRes->at(i)==1)     
	  )
        { 
	  TrigMu8 = true;
        }//if( (TrigNames->at(i).find("HLT_Mu8_v")!=string::npos && TrigRes->at(i)==1)     
      if( (TrigNames->at(i).find("HLT_Dimuon7_Upsilon_")!=string::npos && TrigRes->at(i)==1)     
	  )
        { 
	  TrigDiMu7Upsi = true;
        }//if( (TrigNames->at(i).find("HLT_Dimuon7_Upsilon_")!=string::npos && TrigRes->at(i)==1)
     if( (TrigNames->at(i).find("HLT_Dimuon5_Upsilon_")!=string::npos && TrigRes->at(i)==1)     
	  )
        { 
	  TrigDiMu5Upsi = true;
	  //cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
        }//if( (TrigNames->at(i).find("HLT_Dimuon7_Upsilon_")!=string::npos && TrigRes->at(i)==1)
     if( (TrigNames->at(i).find("HLT_Dimuon10_Upsilon_Barrel_")!=string::npos && TrigRes->at(i)==1)
          )
        {
          TrigDiMu10BarrelUpsi = true;
          //cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
        }//if( (TrigNames->at(i).find("HLT_Dimuon10_Upsilon_Barrel_Seagulls_")
     if( (TrigNames->at(i).find("HLT_Dimuon12_Upsilon_eta1p5_")!=string::npos && TrigRes->at(i)==1)
          )
        {
          TrigDiMu12Eta1p5Upsi = true;
          //cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
        }//if( (TrigNames->at(i).find("HLT_Dimuon12_Upsilon_eta1p5_")!=string::npos && TrigRes->at(i)==1)

     if( (TrigNames->at(i).find("HLT_Dimuon8_Upsilon_Barrel_")!=string::npos && TrigRes->at(i)==1)
          )
        {
          TrigDiMu8BarrelUpsi = true;
	//cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
        }//if( (TrigNames->at(i).find("HLT_Dimuon10_Upsilon_Barrel_Seagulls_")

    }

    //ARC suggestion
    int myGoodSoftMu=0;
    int myTotalChg=0;
    int mySoftMuIdx[100];  //assume maximum good muon is 100
    if(TrigThreeMuonUpsi) {
      for(int mymui=0; mymui<nMu; mymui++)
	{
	  TLorentzVector mymup4;
	  mymup4.SetXYZM( (*muPx)[mymui], (*muPy)[mymui], (*muPz)[mymui], muon_mass); 
	  //cout<<"(*muPx)[mymui]="<<(*muPx)[mymui]<<","<<mymup4.Px()<<endl;
	  if( (*muIsGoodLooseMuon)[mymui]>0  
	      && mymup4.Pt()>=2.0 && fabs( mymup4.Eta() ) <=2.4
	      ) 
	    {
	      myTotalChg+=(*muCharge)[mymui];
	      mySoftMuIdx[myGoodSoftMu]=mymui;
	      myGoodSoftMu++;
	    }//if( (*muIsGoodLooseMuon)[mymui]>0 ) 	  	  
	}//for(int mymui=0; mymui<nMu; mymui++)
    }//if(TrigThreeMuonUpsi) {
    if(myGoodSoftMu>=4) {  
      //cout<<runNum<<" "<<evtNum<<" "<<lumiNum<<" "<<myGoodSoftMu<<" "<<myTotalChg<<endl;
      //myARCoutNmuTCHG<<runNum<<" "<<lumiNum<<" "<<evtNum<<" "<<myGoodSoftMu<<" "<<myTotalChg<<endl;

      for(int myi=0; myi<myGoodSoftMu; myi++) 
	for(int myj=myi+1; myj<myGoodSoftMu; myj++) 
	  {
	    TLorentzVector mymuip4,mymujp4;
	    mymuip4.SetXYZM( (*muPx)[ mySoftMuIdx[myi] ], (*muPy)[ mySoftMuIdx[myi] ], (*muPz)[ mySoftMuIdx[myi] ], muon_mass); 
	    mymujp4.SetXYZM( (*muPx)[ mySoftMuIdx[myj] ], (*muPy)[ mySoftMuIdx[myj] ], (*muPz)[ mySoftMuIdx[myj] ], muon_mass); 
	    if(  (*muCharge)[ mySoftMuIdx[myi] ]+(*muCharge)[ mySoftMuIdx[myj] ]==0 )	      
	      {
		myMuMuChg0ARCmass->Fill( (mymuip4+mymujp4).M() );
	      }//if(  (*muCharge)[ mySoftMuIdx[myi] ]+(*muCharge)[ mySoftMuIdx[myj] ]==0 )
	    if(  (*muCharge)[ mySoftMuIdx[myi] ]+(*muCharge)[ mySoftMuIdx[myj] ]==2 )	      
	      {
		myMuMuChgp2ARCmass->Fill( (mymuip4+mymujp4).M() );
	      }//if(  (*muCharge)[ mySoftMuIdx[myi] ]+(*muCharge)[ mySoftMuIdx[myj] ]==2 )
	    if(  (*muCharge)[ mySoftMuIdx[myi] ]+(*muCharge)[ mySoftMuIdx[myj] ]== -2 )	      
	      {
		myMuMuChgm2ARCmass->Fill( (mymuip4+mymujp4).M() );
	      }//if(  (*muCharge)[ mySoftMuIdx[myi] ]+(*muCharge)[ mySoftMuIdx[myj] ]== -2 )

	  }//for(myi=0; myi<myGoodSoftMu; myi++) 
    }//if(myGoodSoftMu>=4) {
    //ARC suggestion
    
    for(int myi=0; myi<nmumuonly; myi++) {
      int myNumGoodLooseMuon= (*muIsGoodLooseMuon)[ (*mumuonlymu1Idx)[myi]] + (*muIsGoodLooseMuon)[ (*mumuonlymu2Idx)[myi]];
      int myNumGoodTightMuon= (*muIsGoodTightMuon)[ (*mumuonlymu1Idx)[myi]] + (*muIsGoodTightMuon)[ (*mumuonlymu2Idx)[myi]];
      TLorentzVector rawMu1p4vect, rawMu2p4vect;
      float raw_muPx = (*muPx)[ (*mumuonlymu1Idx)[myi] ];
      float raw_muPy = (*muPy)[ (*mumuonlymu1Idx)[myi] ];
      float raw_muPz = (*muPz)[ (*mumuonlymu1Idx)[myi] ];
      
      rawMu1p4vect.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);    
      raw_muPx = (*muPx)[ (*mumuonlymu2Idx)[myi] ]; raw_muPy = (*muPy)[ (*mumuonlymu2Idx)[myi] ]; raw_muPz = (*muPz)[ (*mumuonlymu2Idx)[myi] ];
      rawMu2p4vect.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);    
      
      if(1
	 //	 && (TrigThreeMuonJpsi || TrigThreeMuonUpsi)
	 //&& (TrigThreeMuonUpsi)
	 && (*mumuonlyVtxCL)[myi]>0.005
	 && myNumGoodLooseMuon>=2
	 //&& myNumGoodTightMuon>=2
	 && fabs(rawMu1p4vect.Eta())<=2.4 && fabs(rawMu2p4vect.Eta())<=2.4
	 && rawMu1p4vect.Pt()>=2.0 && rawMu2p4vect.Pt()>=2.0
	 && ( (*muCharge)[ (*mumuonlymu1Idx)[myi] ] + (*muCharge)[ (*mumuonlymu2Idx)[myi] ] ) ==0
	 ) {

	myMuMuonlymass->Fill( (*mumuonlyMass)[myi] ); 

	if(  (*mumuonlyMass)[myi]>9.2 &&  (*mumuonlyMass)[myi]<9.75 )
	  {
	    myMuMuOnlyIso->Fill( (*muIsoratio)[ (*mumuonlymu1Idx)[myi] ]   );
	    myMuMuOnlyIso->Fill( (*muIsoratio)[ (*mumuonlymu2Idx)[myi] ]   ); 
	  }
	
      } // if(1
    } // for(int myi=0; myi<nmumuonly; myi++) {
    
    float myexclnsigma=2.0;
    //four muon signal
    for (int myFourMuIdx = 0; myFourMuIdx <nMyFourMuon; myFourMuIdx++) 
      {
	//assign the right information for the decay daughters
	TLorentzVector myFourMuonP4;
	myFourMuonP4.SetXYZM( (*MyFourMuonPx)[myFourMuIdx],(*MyFourMuonPy)[myFourMuIdx], (*MyFourMuonPz)[myFourMuIdx], (*MyFourMuonMass)[myFourMuIdx] );
	
	vector<int> fitMuCharge;
	fitMuCharge.push_back( (*muCharge)[(*MyFourMuonMu1Idx)[myFourMuIdx]] );
	fitMuCharge.push_back( (*muCharge)[(*MyFourMuonMu2Idx)[myFourMuIdx]] );
	fitMuCharge.push_back( (*muCharge)[(*MyFourMuonMu3Idx)[myFourMuIdx]] );
	fitMuCharge.push_back( (*muCharge)[(*MyFourMuonMu4Idx)[myFourMuIdx]] );

	vector<TLorentzVector> rawMup4vect, rawMuinFourMuFMp4vect;
	TLorentzVector Rawmu, RawmuinFourMuFM;
	float raw_muPx = (*muPx)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ];
	float raw_muPy = (*muPy)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ];
	float raw_muPz = (*muPz)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ];
	//float raw_muM  =0.10565837; 
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);   
	RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
	rawMup4vect.push_back( Rawmu ); rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );
	raw_muPx = (*muPx)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ];
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);  rawMup4vect.push_back( Rawmu );
	RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
	rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );
	raw_muPx = (*muPx)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ];
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);  rawMup4vect.push_back( Rawmu );
	RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
	rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );
	raw_muPx = (*muPx)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ];
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);  rawMup4vect.push_back( Rawmu );
	RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
	rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );

	vector<TLorentzVector> fitMup4vect;
	TLorentzVector Fitmu;
	//Muon From X Fit:        
	//Fit Muon 1
	float fit_muPx = (*MyFourMuonMu1Px)[myFourMuIdx];
	float fit_muPy = (*MyFourMuonMu1Py)[myFourMuIdx];
	float fit_muPz = (*MyFourMuonMu1Pz)[myFourMuIdx];
	float fit_muM  =0.10565837; 
	Fitmu.SetXYZM( fit_muPx, fit_muPy,fit_muPz, fit_muM);    
	fitMup4vect.push_back( Fitmu );
	
	fit_muPx = (*MyFourMuonMu2Px)[myFourMuIdx]; fit_muPy = (*MyFourMuonMu2Py)[myFourMuIdx]; fit_muPz = (*MyFourMuonMu2Pz)[myFourMuIdx];
	Fitmu.SetXYZM( fit_muPx, fit_muPy,fit_muPz, fit_muM);  fitMup4vect.push_back( Fitmu );
	fit_muPx = (*MyFourMuonMu3Px)[myFourMuIdx]; fit_muPy = (*MyFourMuonMu3Py)[myFourMuIdx]; fit_muPz = (*MyFourMuonMu3Pz)[myFourMuIdx];
	Fitmu.SetXYZM( fit_muPx, fit_muPy,fit_muPz, fit_muM);  fitMup4vect.push_back( Fitmu );
	fit_muPx = (*MyFourMuonMu4Px)[myFourMuIdx]; fit_muPy = (*MyFourMuonMu4Py)[myFourMuIdx]; fit_muPz = (*MyFourMuonMu4Pz)[myFourMuIdx];
	Fitmu.SetXYZM( fit_muPx, fit_muPy,fit_muPz, fit_muM);  fitMup4vect.push_back( Fitmu );
	
	PairedMuonIdx myCombIdx[3];   
	//double mymV[2]={9.46,3.0967};
	double mymV;   //3.096919 for jpsi, 3.686 for psi2s, 9.46 for Y(1s),10.02326,10.3552
	//code with simplest and safest way to make sure 
	if( mychannel==11) {  mymV=9.46; } 
	if( mychannel==12) {  mymV=9.46; } 
	if( mychannel==13) {  mymV=9.46; } 

	if( mychannel==21) {  mymV=3.096919; } 
	if( mychannel==22) {  mymV=3.096919; } 

	if( mychannel==55) {  mymV=9.46; } 
	if( mychannel==66) {  mymV=3.096919; } 

	if( mychannel==99) {  mymV=0.0; } 
	if( mychannel==991) {  mymV=0.0; } 
	if( mychannel==992) {  mymV=0.0; } 

	if( mychannel==999) {  mymV=0.0; } 

 	myCombIdx[0].p11=0; myCombIdx[0].p12=1; myCombIdx[0].p21=2; myCombIdx[0].p22=3; 
	myCombIdx[1].p11=0; myCombIdx[1].p12=2; myCombIdx[1].p21=1; myCombIdx[1].p22=3; 
	myCombIdx[2].p11=0; myCombIdx[2].p12=3; myCombIdx[2].p21=1; myCombIdx[2].p22=2; 
	
	if( (fitMuCharge[ myCombIdx[1].p11 ]+fitMuCharge[ myCombIdx[1].p12 ])!=0 )  swap_two_paired_pair( myCombIdx[0],  myCombIdx[1] );
	if( (fitMuCharge[ myCombIdx[2].p11 ]+fitMuCharge[ myCombIdx[2].p12 ])!=0 )  swap_two_paired_pair( myCombIdx[0],  myCombIdx[2] );
	//now the  myCombIdx[0] is 2++ charged pair, but we want the first pair to be 2++
	if( (fitMuCharge[ myCombIdx[0].p11 ]+fitMuCharge[ myCombIdx[0].p12 ])!=2 )  swap_one_paired_pair( myCombIdx[0] );
	
	if(myordermode==1)  //sort to make m11>m12, m21>m22, m21>m11
	  {
	    for(int i=1; i<3; i++) {
	      if( (fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()<(fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()  ) swap_one_paired_pair( myCombIdx[i] ); //for have first pair to have bigger mass
	    }	
	    //sort to have first pair to have bigger mass
	    if( ((fitMup4vect[ myCombIdx[1].p11 ]+ fitMup4vect[ myCombIdx[1].p12 ]).M()) < ((fitMup4vect[ myCombIdx[2].p11 ]+ fitMup4vect[ myCombIdx[2].p12 ]).M() ) ) 
	      swap_two_paired_pair( myCombIdx[1],  myCombIdx[2] );	    
	  }
	else if(myordermode==2)
	  {
	    for(int i=1; i<3; i++) {
	      if( (fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()<(fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()  ) swap_one_paired_pair( myCombIdx[i] ); //for have first pair to have bigger mass
	    }	
	//sort to make sure that |myCombIdx[i][1]-pair1 mass - m(V)| < |myCombIdx[i][2]-pair1- m(V)| ,  V=Y(1S), J/psi
	    if( fabs((fitMup4vect[ myCombIdx[1].p11 ]+ fitMup4vect[ myCombIdx[1].p12 ]).M()-mymV )> fabs((fitMup4vect[ myCombIdx[2].p11 ]+ fitMup4vect[ myCombIdx[2].p12 ]).M()-mymV ) ) 
	      swap_two_paired_pair( myCombIdx[1],  myCombIdx[2] );
	  }	
        else if(myordermode==3)
          {
            for(int i=1; i<3; i++) {
              if( fabs((fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()-mymV) > fabs((fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()-mymV)  ) swap_one_paired_pair( myCombIdx[i] ); //for 
            }
        //sort to make sure that |myCombIdx[i][1]-pair1 mass - m(V)| < |myCombIdx[i][2]-pair1- m(V)| ,  V=Y(1S), J/psi
            if( fabs((fitMup4vect[ myCombIdx[1].p11 ]+ fitMup4vect[ myCombIdx[1].p12 ]).M()-mymV )> fabs((fitMup4vect[ myCombIdx[2].p11 ]+ fitMup4vect[ myCombIdx[2].p12 ]).M()-mymV ) )
              swap_two_paired_pair( myCombIdx[1],  myCombIdx[2] );
          }

	  for(int i=1; i<3; i++) {
	    if( fitMuCharge[ myCombIdx[i].p11 ] !=1 ) swap_one_pair( myCombIdx[i], 1 );
	    if( fitMuCharge[ myCombIdx[i].p21 ] !=1 ) swap_one_pair( myCombIdx[i], 2 );
	  }

	float myMupMumVtxProb[3][2];   //[2]-> V=Y1s, J/psi; 3-> 3 combinations; 2->pair 1 & pair 2
	myMupMumVtxProb[0][0]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[0][1]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[0].p11==2 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==2) )
	  { myMupMumVtxProb[0][1]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[0][0]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMupMumVtxProb[0][0]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[0][1]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMupMumVtxProb[0][1]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[0][0]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMupMumVtxProb[0][0]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[0][1]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMupMumVtxProb[0][1]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[0][0]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	myMupMumVtxProb[1][0]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[1][1]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[1].p11==2 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==2) )
	  { myMupMumVtxProb[1][1]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[1][0]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMupMumVtxProb[1][0]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[1][1]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMupMumVtxProb[1][1]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[1][0]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMupMumVtxProb[1][0]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[1][1]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMupMumVtxProb[1][1]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[1][0]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	myMupMumVtxProb[2][0]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[2][1]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[2].p11==2 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==2) )
	  { myMupMumVtxProb[2][1]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[2][0]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMupMumVtxProb[2][0]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[2][1]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMupMumVtxProb[2][1]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[2][0]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMupMumVtxProb[2][0]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[2][1]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMupMumVtxProb[2][1]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[2][0]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	

	
	float myMupMumCTau[3][2]; //[2]-> V=Y1s, J/psi; 3-> 3 combinations; 2->pair 1 & pair 2
	myMupMumCTau[0][0]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[0][1]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[0].p11==2 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==2) )
	  { myMupMumCTau[0][1]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[0][0]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMupMumCTau[0][0]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[0][1]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMupMumCTau[0][1]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[0][0]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMupMumCTau[0][0]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[0][1]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMupMumCTau[0][1]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[0][0]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	myMupMumCTau[1][0]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[1][1]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[1].p11==2 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==2) )
	  { myMupMumCTau[1][1]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[1][0]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMupMumCTau[1][0]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[1][1]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMupMumCTau[1][1]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[1][0]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMupMumCTau[1][0]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[1][1]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMupMumCTau[1][1]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[1][0]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	myMupMumCTau[2][0]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[2][1]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[2].p11==2 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==2) )
	  { myMupMumCTau[2][1]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[2][0]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMupMumCTau[2][0]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[2][1]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMupMumCTau[2][1]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[2][0]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMupMumCTau[2][0]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[2][1]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMupMumCTau[2][1]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[2][0]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	

	float myMupMumCTauErr[3][2];
	myMupMumCTauErr[0][0]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[0][1]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[0].p11==2 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==2) )
	  { myMupMumCTauErr[0][1]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[0][0]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMupMumCTauErr[0][0]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[0][1]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMupMumCTauErr[0][1]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[0][0]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMupMumCTauErr[0][0]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[0][1]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMupMumCTauErr[0][1]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[0][0]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	myMupMumCTauErr[1][0]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[1][1]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[1].p11==2 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==2) )
	  { myMupMumCTauErr[1][1]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[1][0]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMupMumCTauErr[1][0]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[1][1]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMupMumCTauErr[1][1]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[1][0]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMupMumCTauErr[1][0]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[1][1]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMupMumCTauErr[1][1]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[1][0]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	myMupMumCTauErr[2][0]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[2][1]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[2].p11==2 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==2) )
	  { myMupMumCTauErr[2][1]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[2][0]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMupMumCTauErr[2][0]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[2][1]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMupMumCTauErr[2][1]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[2][0]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMupMumCTauErr[2][0]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[2][1]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMupMumCTauErr[2][1]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[2][0]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	


        float my4mumassConstraint[3];
        my4mumassConstraint[0]=(*My1234Mass)[myFourMuIdx];
        if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
          { my4mumassConstraint[0]=(*My1324Mass)[myFourMuIdx];  }
        if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) )
          { my4mumassConstraint[0]=(*My1324Mass)[myFourMuIdx];  }
        if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) )
          { my4mumassConstraint[0]=(*My1423Mass)[myFourMuIdx];  }
        if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) )
          { my4mumassConstraint[0]=(*My1423Mass)[myFourMuIdx];  }
        my4mumassConstraint[1]=(*My1234Mass)[myFourMuIdx];
        if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) )
          { my4mumassConstraint[1]=(*My1324Mass)[myFourMuIdx];  }
        if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) )
          { my4mumassConstraint[1]=(*My1324Mass)[myFourMuIdx];  }
        if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) )
          { my4mumassConstraint[1]=(*My1423Mass)[myFourMuIdx];  }
        if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) )
          { my4mumassConstraint[1]=(*My1423Mass)[myFourMuIdx];  }
        my4mumassConstraint[2]=(*My1234Mass)[myFourMuIdx];
        if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) )
          { my4mumassConstraint[2]=(*My1324Mass)[myFourMuIdx];  }
        if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) )
          { my4mumassConstraint[2]=(*My1324Mass)[myFourMuIdx];  }
        if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) )
          { my4mumassConstraint[2]=(*My1423Mass)[myFourMuIdx];  }
        if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) )
          { my4mumassConstraint[2]=(*My1423Mass)[myFourMuIdx];  }
	//Two dimuon vertex distancexy
	float myMumu1Mumu2DisXY[3];
	myMumu1Mumu2DisXY[0]=(*My1234JpsiDisXY)[myFourMuIdx]; 
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMumu1Mumu2DisXY[0]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMumu1Mumu2DisXY[0]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMumu1Mumu2DisXY[0]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMumu1Mumu2DisXY[0]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	myMumu1Mumu2DisXY[1]=(*My1234JpsiDisXY)[myFourMuIdx]; 
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMumu1Mumu2DisXY[1]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMumu1Mumu2DisXY[1]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMumu1Mumu2DisXY[1]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMumu1Mumu2DisXY[1]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	myMumu1Mumu2DisXY[2]=(*My1234JpsiDisXY)[myFourMuIdx]; 
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMumu1Mumu2DisXY[2]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMumu1Mumu2DisXY[2]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMumu1Mumu2DisXY[2]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMumu1Mumu2DisXY[2]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	//Two dimuon vertex distanceZ
	float myMumu1Mumu2DisZ[3];
	myMumu1Mumu2DisZ[0]=(*My1234JpsiDisZ)[myFourMuIdx]; 
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMumu1Mumu2DisZ[0]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMumu1Mumu2DisZ[0]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMumu1Mumu2DisZ[0]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMumu1Mumu2DisZ[0]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	myMumu1Mumu2DisZ[1]=(*My1234JpsiDisZ)[myFourMuIdx]; 
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMumu1Mumu2DisZ[1]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMumu1Mumu2DisZ[1]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMumu1Mumu2DisZ[1]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMumu1Mumu2DisZ[1]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	myMumu1Mumu2DisZ[2]=(*My1234JpsiDisZ)[myFourMuIdx]; 
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMumu1Mumu2DisZ[2]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMumu1Mumu2DisZ[2]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMumu1Mumu2DisZ[2]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMumu1Mumu2DisZ[2]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	//dimuon mass from the fit
	float myMupMumMass[3][2];   //[2]-> V=Y1s, J/psi; 3-> 3 combinations; 2->pair 1 & pair 2
	myMupMumMass[0][0]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[0][1]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[0].p11==2 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==2) )
	  { myMupMumMass[0][1]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[0][0]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMupMumMass[0][0]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[0][1]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMupMumMass[0][1]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[0][0]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMupMumMass[0][0]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[0][1]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMupMumMass[0][1]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[0][0]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
	myMupMumMass[1][0]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[1][1]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[1].p11==2 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==2) )
	  { myMupMumMass[1][1]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[1][0]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMupMumMass[1][0]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[1][1]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMupMumMass[1][1]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[1][0]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMupMumMass[1][0]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[1][1]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMupMumMass[1][1]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[1][0]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
	myMupMumMass[2][0]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[2][1]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[2].p11==2 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==2) )
	  { myMupMumMass[2][1]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[2][0]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMupMumMass[2][0]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[2][1]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMupMumMass[2][1]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[2][0]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMupMumMass[2][0]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[2][1]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMupMumMass[2][1]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[2][0]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
	//dimuon mass error
	float myMupMumMassErr[3][2];   //[2]-> V=Y1s, J/psi; 3-> 3 combinations; 2->pair 1 & pair 2
	myMupMumMassErr[0][0]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[0][1]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[0].p11==2 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==2) )
	  { myMupMumMassErr[0][1]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[0][0]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMupMumMassErr[0][0]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[0][1]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMupMumMassErr[0][1]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[0][0]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMupMumMassErr[0][0]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[0][1]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMupMumMassErr[0][1]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[0][0]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
	myMupMumMassErr[1][0]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[1][1]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[1].p11==2 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==2) )
	  { myMupMumMassErr[1][1]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[1][0]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMupMumMassErr[1][0]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[1][1]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMupMumMassErr[1][1]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[1][0]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMupMumMassErr[1][0]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[1][1]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMupMumMassErr[1][1]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[1][0]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
	myMupMumMassErr[2][0]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[2][1]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[2].p11==2 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==2) )
	  { myMupMumMassErr[2][1]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[2][0]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMupMumMassErr[2][0]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[2][1]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMupMumMassErr[2][1]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[2][0]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMupMumMassErr[2][0]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[2][1]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMupMumMassErr[2][1]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[2][0]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
	//added by yik to check EBE fro ARC
        for(int i=1; i<3; i++) 
         for (int j=0;j<2;j++)
         {
           int mymuidx1,mymuidx2;
	if(j==0) {mymuidx1=myCombIdx[i].p11; mymuidx2=myCombIdx[i].p12; }
	if(j==1) {mymuidx1=myCombIdx[i].p21; mymuidx2=myCombIdx[i].p22; }


         if(myMupMumVtxProb[i][j]>0.001   //impl the total chg==0 for this cut because it will be negative otherwise
              && (*muIsGoodLooseMuon)[mymuidx1] && (*muIsGoodLooseMuon)[mymuidx2]
              && (*muIsGoodTightMuon)[mymuidx1] && (*muIsGoodTightMuon)[mymuidx2]
              && rawMup4vect[mymuidx1].Pt()>=2.0 && rawMup4vect[mymuidx2].Pt()>=2.0
              && rawMup4vect[mymuidx1].Eta()<=2.4 && rawMup4vect[mymuidx2].Eta()<=2.4
	     ) 
	   {
             //cout<<"(i,j)=("<<i<<","<<j<<"),"<<myMupMumMass[i][j]<<","<<myMupMumMassErr[i][j]<<endl;
             myARCDimuMass->Fill( myMupMumMass[i][j] );
             myARCDimuMassPullUpsi->Fill( (myMupMumMass[i][j]-9.46)/myMupMumMassErr[i][j] );
             myARCDimuMassPullJpsi->Fill( (myMupMumMass[i][j]-3.096919)/myMupMumMassErr[i][j] );

             myARCDimuMassPullUpsiScaled->Fill( (myMupMumMass[i][j]-9.46)/(myMupMumMassErr[i][j]*1.0576) );
             myARCDimuMassPullJpsiScaled->Fill( (myMupMumMass[i][j]-3.096919)/(myMupMumMassErr[i][j]*1.125) );

           }
         }

       float mymuonpulldYdZ[4], mymuonpulldXdZ[4];
        
	//muon ID 
	int isTightMuon[4], isLooseMuon[4], myMuIso[4];
	//new default muon id					
	//test new soft muonID 
	isLooseMuon[0]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isLooseMuon[1]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
	isLooseMuon[2]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isLooseMuon[3]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
	       
	isTightMuon[0]=(*muIsGoodTightMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isTightMuon[1]=(*muIsGoodTightMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
	isTightMuon[2]=(*muIsGoodTightMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isTightMuon[3]=(*muIsGoodTightMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];

	float myfourmuonmass= (fitMup4vect[0]+fitMup4vect[1]+fitMup4vect[2]+fitMup4vect[3]).M();
	
	int myNumGoodLooseMuon=isLooseMuon[0]+isLooseMuon[1]+isLooseMuon[2]+isLooseMuon[3];
	int myNumGoodTightMuon= (*muIsGoodTightMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[(*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
	TLorentzVector myRaw4Mup4=rawMup4vect[0]+rawMup4vect[1]+rawMup4vect[2]+rawMup4vect[3];
	float myetacut=2.4;   //1.6, there is a bump at 31 GeV for Y(1S) mumu, default 2.4
	float minMuPt=2.0; //2.0--default 1.5;2,5;3.0;3.5;  2.2

	float myEBEscale=1.16;  //1.105--run I,  1.16--run II 
	//float myEBEscale=1.2;

///1. candan/// the below cuts effect the total event number (myNumGoodLooseMuon,OverlappMuons,MyFourMuonVtxCL,Trigger (TrigThreeMuonJpsi3p5mu2,..),rwaMu eta cuts, )
	if(1 //&& myNumGoodLooseMuon>=4 //comment out by candan
 	   /* && //comment out by candan
	   ( (*MyFourMuonOverlap12)[myFourMuIdx]==0
	     && (*MyFourMuonOverlap13)[myFourMuIdx]==0
	     && (*MyFourMuonOverlap14)[myFourMuIdx]==0
	     && (*MyFourMuonOverlap23)[myFourMuIdx]==0
	     && (*MyFourMuonOverlap24)[myFourMuIdx]==0
	     && (*MyFourMuonOverlap34)[myFourMuIdx]==0
	     )*///comment out by candan

	   //&& (*MyFourMuonVtxCL)[myFourMuIdx]>=0.01   //0.05,0.0001	//comment out by candan
	   //&& TrigThreeMuonJpsi3p5mu2   //2017 & 2018 Jpsi trigger    //comment out by candan (trigger for 2017/2018HLT_Dimuon0_Jpsi3p5_Muon2_)
	   //&& TrigThreeMuonJpsi   //2016  Jpsi trigger    //candan trigger for 2016 : HLT_Dimuon0_Jpsi_Muon_
	   //&& fabs(rawMup4vect[0].Eta())<=myetacut && fabs(rawMup4vect[1].Eta())<=myetacut //comment out by candan
	   //&& fabs(rawMup4vect[2].Eta())<=myetacut && fabs(rawMup4vect[3].Eta())<=myetacut  //comment out by candan  	   
	   //&& (fitMuCharge[0]+fitMuCharge[1]+fitMuCharge[2]+fitMuCharge[3])==0  //comment out by candan
	   //&& myfourmuonmass>=13.0 && myfourmuonmass<=26.0
	   //MuOnia data
	   //&& ( TrigThreeMuonJpsi || TrigThreeMuonUpsi )    //for three muon trigger, default trigger, remove it for Higgs test
	   //&& TrigThreeMuonUpsi   
	   //&& ( TrigThreeMuonUpsi || TrigThreemuon5_3dot5_2 )
	   //&& runNum>=306011
	   //&& TrigThreeOpenMuonUpsi
	   //&& TrigThreeMuonUpsi
	   //&& TrigThreemuonMu2Upsilon5
	   //&& (TrigThreemuon5_3dot5_2 || TrigThreeOpenmuon5_3dot5_2 ||  TrigThreemuonMu2Upsilon5 )
	   //&& TrigThreemuon5_3dot5_2
	   //&& TrigThreeOpenmuon5_3dot5_2
	   //&& (TrigThreeMuonUpsi || TrigTripleMu5)
	   //&& TrigTripleMu5
	   //&& TrigDiMu10BarrelUpsi 
	   //&& (TrigDiMu12Eta1p5Upsi || TrigDiMu10BarrelUpsi )
	   //&& TrigDiMu8BarrelUpsi
	   //&& TrigDiMu7Upsi
	   //&& TrigThreeMuonUpsi
	   //&& TrigDiMu7Upsi
	   //&& TrigDiMu5Upsi
	   //&& (TrigTripleMu5 || TrigDoubleMu5IsoMu5)    //for double muon dataset
	   //&& TrigDoubleMu5IsoMu5
	   //&& TrigTripleMu5
	   //&& TrigMu8
	   //&& (matchUpsiTrig>=3 || matchJpsiTrig>=3)
	   )///candan end// when the cuts are removed (uncommented ones by candan) the total event number is: 958 
	  {	
	    int NumCanforKamuranCHK=0;
	    int NumCanforMaksatCHK=0;

	    int NumDupARC=0; 

	    int NumDupMiddleDefault=0;
	    int NumDupLowSide=0;
	    int NumDupHighSide=0;  

	    int NumDupARCEBE=0;
	    int NumDup=0;   //we have two pairs, but only fill one time if at least one pair satisfy it
	    for(int mypidx=1; mypidx<3; mypidx++) //loop over the two combinations with zero chg
	      {
		int muIdxp11, muIdxp12, muIdxp21, muIdxp22;
		muIdxp11=myCombIdx[mypidx].p11; muIdxp12=myCombIdx[mypidx].p12; muIdxp21=myCombIdx[mypidx].p21; muIdxp22=myCombIdx[mypidx].p22;
		//this part is to investigate the another combination--to see if there are anything strange.
		int myanotherpidx; 
		if( mypidx==1 ) {myanotherpidx=2;}  if( mypidx==2 ) {myanotherpidx=1;} 
		int muanotherIdxp11, muanotherIdxp12, muanotherIdxp21, muanotherIdxp22;
		muanotherIdxp11=myCombIdx[myanotherpidx].p11; muanotherIdxp12=myCombIdx[myanotherpidx].p12; 
		muanotherIdxp21=myCombIdx[myanotherpidx].p21; muanotherIdxp22=myCombIdx[myanotherpidx].p22;
		//end this part is to investigate the another combination--to see if there are anything strange.
		
		//for this selected pair
		TLorentzVector mymumu1p4=rawMup4vect[ muIdxp11 ]+ rawMup4vect[ muIdxp12 ];
		TLorentzVector mymumu2p4=rawMup4vect[ muIdxp21 ]+ rawMup4vect[ muIdxp22 ];
		double myrap1=fabs(0.5*log( (mymumu1p4.E() + mymumu1p4.Pz())/(mymumu1p4.E() - mymumu1p4.Pz()) ) );
		double myrap2=fabs(0.5*log( (mymumu2p4.E() + mymumu2p4.Pz())/(mymumu2p4.E() - mymumu2p4.Pz()) ) );
		//obtained from data
		double myY1sResp1=0.0572+0.03602*myrap1;
		double myY2sResp1=0.05745+0.03926*myrap1;   
		double myJpsiResp1=0.01598+0.01562*myrap1;
		double myPsi2sResp1=0.01849+0.01906*myrap1;
		double myPhiResp1=0.006984+0.004505*myrap1+0.00426;  //0.00426 is its intrisince width
		double myOmegaResp1=0.006366+0.003277*myrap1+0.00849;  //+0.00849 is for its intrisic width
		
		double myY1sResp2=0.0572+0.03602*myrap2;
		double myY2sResp2=0.05745+0.03926*myrap2;   
		double myJpsiResp2=0.01598+0.01562*myrap2;
		double myPsi2sResp2=0.01849+0.01906*myrap2;
		double myPhiResp2=0.006984+0.004505*myrap2+0.00426;   //0.00426 is its intrisince width
		double myOmegaResp2=0.006366+0.003277*myrap2+0.00849;  //+0.00849 is for its intrisic width
		
		//mass resolution for another pair
		TLorentzVector myanothermumu1p4=rawMup4vect[ muanotherIdxp11 ]+ rawMup4vect[ muanotherIdxp12 ];
		TLorentzVector myanothermumu2p4=rawMup4vect[ muanotherIdxp21 ]+ rawMup4vect[ muanotherIdxp22 ];
		double myanotherrap1=fabs(0.5*log( (myanothermumu1p4.E() + myanothermumu1p4.Pz())/(myanothermumu1p4.E() - myanothermumu1p4.Pz()) ) );
		double myanotherrap2=fabs(0.5*log( (myanothermumu2p4.E() + myanothermumu2p4.Pz())/(myanothermumu2p4.E() - myanothermumu2p4.Pz()) ) );
		//obtained from data
		double myanotherY1sResp1=0.0572+0.03602*myanotherrap1;
		double myanotherY2sResp1=0.05745+0.03926*myanotherrap1;   
		double myanotherJpsiResp1=0.01598+0.01562*myanotherrap1;
		double myanotherPsi2sResp1=0.01849+0.01906*myanotherrap1;
		double myanotherPhiResp1=0.006984+0.004505*myanotherrap1+0.00426;  //0.00426 is its intrisince width
		double myanotherOmegaResp1=0.006366+0.003277*myanotherrap1+0.00849;  //+0.00849 is for its intrisic width
		
		double myanotherY1sResp2=0.0572+0.03602*myanotherrap2;
		double myanotherY2sResp2=0.05745+0.03926*myanotherrap2;   
		double myanotherJpsiResp2=0.01598+0.01562*myanotherrap2;
		double myanotherPsi2sResp2=0.01849+0.01906*myanotherrap2;
		double myanotherPhiResp2=0.006984+0.004505*myanotherrap2+0.00426;  //0.00426 is its intrisince width
		double myanotherOmegaResp2=0.006366+0.003277*myanotherrap2+0.00849;  //+0.00849 is for its intrisic width
		
		//2.  ///candan/// the below cuts effect the total event number (DimuonVtx (cut myMupMumVtxProb[mypidx] ),rwaMu Pt cuts, ) 
		if(1
                 //&& myMupMumVtxProb[mypidx][0]>=0.001 && myMupMumVtxProb[mypidx][1]>=0.001  //comment out by candan
		 //&& rawMup4vect[ muIdxp11 ].Pt()>=minMuPt && rawMup4vect[ muIdxp12 ].Pt()>=minMuPt  //comment out by candan
		 //&& rawMup4vect[ muIdxp21 ].Pt()>=minMuPt && rawMup4vect[ muIdxp22 ].Pt()>=minMuPt  //comment out by candan
		//&& isLooseMuon[ muIdxp11 ] &&  isLooseMuon[ muIdxp12 ] //check tomorrow
		//&& isLooseMuon[ muIdxp21 ] &&  isLooseMuon[ muIdxp22 ] //check tomorrow
		//&& myNumGoodTightMuon>=4  //comment out by candan
		//&& rawMup4vect[ 3 ].Pt() >=4.0
		//2. candan end /// when the cuts are removed (uncommented ones by candan) the total event number is:9441 
		   ) {
		  if( mypidx==1 ) {
		    myMuMumassforV1highpair->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()  );
		    myMuMumassformumuhighpair->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
		    
		  }
		  if( mypidx==2 ) {
		    myMuMumassforV1lowpair->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );		      
		    myMuMumassformumulowpair->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
		  }
		  //apply mass cut 
		  float mynsigma=3.0;	//default 3.0	  
		  bool myVVmasscut;
		  if( mychannel==11 ) {  //Y(1S) mumu
		    
		    //used EBE error
		    myVVmasscut= 1 
		    && fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0]  
		    && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma*myEBEscale*myMupMumMassErr[mypidx][1] )
		    && myNumGoodTightMuon>=2
		      ; //if one of the V is Upsilon		    
		  }

		  if( mychannel==12 ) {  //Y(1S) mumu
		    //used EBE error
		    myVVmasscut= 1 
		     && fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0]  
		     && myNumGoodTightMuon>=2; //if one of the V is Upsilon		    
		  }

		  if( mychannel==13 ) {  //test virtual Y*Y*
		    //used EBE error
		    myVVmasscut= 1 
		      &&  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() >9.1 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() <11.4
		      && myNumGoodTightMuon>=2
		      ; //if one of the V is Upsilon		    
		  }


		  if( mychannel==21 ) {  //J/psi mumu, m(mumu)<m(Jpsi)
		    //used EBE error
		    myVVmasscut= 1 
		      && fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0]  
		      && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma*myEBEscale*myMupMumMassErr[mypidx][1] )
		      ;
		  }

		  if( mychannel==22 ) {  //J/psi mumu, m(mumu)<m(Jpsi)
		    //used EBE error
		    myVVmasscut= 1 
		      && fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0]  
		      && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma*myEBEscale*myMupMumMassErr[mypidx][1] )
		      ;
		  }

		  if( mychannel==55 ) {  //Y(1S) Y(1S)		    
		    //used EBE error
		    myVVmasscut= 1 

		      ; //if one of the V is Upsilon		    
		  }

		  if( mychannel==66 ) {  //JJ		    
		    myVVmasscut= 1 
		      ; //if one of the V is Upsilon		    
		  
//eventselection << setw(10) <<runNum<<"\t"<< setw(10) <<lumiNum<<"\t"<< setw(10) << evtNum<<"\t"<< setw(10) <<my4mumassConstraint[ mypidx ]<<"\t"<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]+fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<"\n";
}

		  //mychannel==99, test of VV choice
		  if( mychannel==99 ) {  //VV 
		    //used EBE error
		    myVVmasscut= 1 

		      && 
		      ( fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() - 9.4603 ) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0] //&& myNumGoodTightMuon>=2
		      && ( 
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.686109) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.096916) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-1.019461) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-0.78265) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  )		
			)
		      ||

		      ( 
                        fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() - 3.096916 ) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0] 
		         && ( 
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.686109) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.096916) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-1.019461) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-0.78265) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  )		
			)
		      ; //if one of the V is Upsilon		    
		  }
		  //mychannel==991, test of Y1sV choice
		  if( mychannel==991 ) {  //Y1sV 
		    //used EBE error
		    myVVmasscut= 1 
		      && 
		      ( fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() - 9.4603 ) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0] //&& myNumGoodTightMuon>=2
			&& ( 
			    fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.686109) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			    ||
			    fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.096916) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			    ||
			    fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-1.019461) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			    ||
			    fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-0.78265) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			    )		
			)
		      ; //if one of the V is Upsilon		    
		  }
		  //mychannel==992, test of Jpsi V choice
		  if( mychannel==992 ) {  //Jpsi V 
		    //used EBE error
		    myVVmasscut= 1 
		      && 
			( fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() - 3.096916 ) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0] 
			&& ( 
			fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.686109) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			||
			fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.096916) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			||
			fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-1.019461) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			||
			fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-0.78265) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			)		
			)
		      
		      ; //if one of the V is Upsilon		    
		  }


		  //mychannel==999, test of VV+VV* choice
		  if( mychannel==999 ) {  //+Y(1S) mumu 
		    //used EBE error
		    myVVmasscut= 1 
		      && 
(
                      (
                      fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -9.4603 )<= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0]  
		      && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( 9.4603-mynsigma*myEBEscale*myMupMumMassErr[mypidx][1] )
		      && myNumGoodTightMuon>=2
                      )
                      ||
                      (
                      fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() - 9.4603 ) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0]
                      &&
                        (
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.686109) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.096916) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-1.019461) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-0.78265) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
                        )
                      )
                     ||
                     (
                      fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() - 3.096916 ) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0] 
		      && ( 
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.686109) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.096916) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-1.019461) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  ||
			  fabs((fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-0.78265) <= mynsigma*myEBEscale*myMupMumMassErr[mypidx][1]
			  )		
                     )

) 
                     ; 		    

		  }
		  

		  //define low/high Y(1S) sidebands
		  float lowsidel=8.6, lowsideh=9.2, highsidel=9.75, highsideh=9.85;
		  if(mychannel==11) {
		    if(  myNumGoodTightMuon>=2  //if one of the V is Upsilon
			 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() >lowsidel 
			 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() <lowsideh
			 ){
		      myMuMuMuMumassV1mumubelowV1LowSide->Fill( myfourmuonmass );

		      if( fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-3.096919)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-3.096919)>  myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  ) {
			myMuMuMuMumassV1mumubelowV1NolightmesonLowSide->Fill( myfourmuonmass );
		      }
		      else {  }
		      

		      //shift the band to Y(1s)
		      TLorentzVector mylowsidedimuonp4=(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]);
		      TLorentzVector myYstardimuonp4=(fitMup4vect[ muIdxp21 ]+fitMup4vect[ muIdxp22 ]);		      
		      float mytmpmass=mylowsidedimuonp4.M(); mytmpmass=mytmpmass+ (9.46-(lowsidel+lowsideh)/2);
		      float mynewE=mylowsidedimuonp4.Vect().Mag2() + mytmpmass*mytmpmass; 
		      mynewE=sqrt(mynewE );  mylowsidedimuonp4.SetE( mynewE  );
		      mytmpmass=myYstardimuonp4.M()+(9.46-mylowsidedimuonp4.M());
		      mynewE=myYstardimuonp4.Vect().Mag2()+ mytmpmass*mytmpmass; 
		      mynewE=sqrt(mynewE ); myYstardimuonp4.SetE( mynewE  );
		      myMuMuMuMumassV1mumubelowV1LowSideShift->Fill( (mylowsidedimuonp4+myYstardimuonp4).M()  );		      

		      if( fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-3.096919)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-3.096919)>  myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  ) {
			myMuMuMuMumassV1mumubelowV1NolightmesonLowSideShift->Fill( (mylowsidedimuonp4+myYstardimuonp4).M()  );
		      }



		    }//if(  myNumGoodTightMuon>=2  //if one of the V is Upsilon

		    if(  myNumGoodTightMuon>=2  //if one of the V is Upsilon
			 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() > highsidel
			 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() < highsideh
			 ){		      
		      myMuMuMuMumassV1mumubelowV1HighSide->Fill( myfourmuonmass );
		      if( fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-3.096919)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-3.096919)>  myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  ) {
			myMuMuMuMumassV1mumubelowV1NolightmesonHighSide->Fill( myfourmuonmass );
		      }

		      //shift the band to Y(1s)
		      TLorentzVector mylowsidedimuonp4=(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]);
		      TLorentzVector myYstardimuonp4=(fitMup4vect[ muIdxp21 ]+fitMup4vect[ muIdxp22 ]);		      
		      float mytmpmass=mylowsidedimuonp4.M(); mytmpmass=mytmpmass+ (9.46-(highsidel+highsideh)/2);
		      float mynewE=mylowsidedimuonp4.Vect().Mag2() + mytmpmass*mytmpmass; 
		      mynewE=sqrt(mynewE );  mylowsidedimuonp4.SetE( mynewE  );
		      mytmpmass=myYstardimuonp4.M()+(9.46-mylowsidedimuonp4.M());
		      mynewE=myYstardimuonp4.Vect().Mag2()+ mytmpmass*mytmpmass; 
		      mynewE=sqrt(mynewE ); myYstardimuonp4.SetE( mynewE  );
		      myMuMuMuMumassV1mumubelowV1HighSideShift->Fill(  (mylowsidedimuonp4+myYstardimuonp4).M()  );
		      if( fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-3.096919)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-3.096919)>  myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][0]*myexclnsigma
			  && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][1]*myexclnsigma
			  ) {
			myMuMuMuMumassV1mumubelowV1NolightmesonHighSideShift->Fill( (mylowsidedimuonp4+myYstardimuonp4).M()  );
		      }


		    }//if(  myNumGoodTightMuon>=2  //if one of the V is Upsilon
		  }
		  

		  //dealing ARC comments		 
		  if( mypidx==1 
//		      && TrigThreeMuonUpsi
		      && myNumGoodTightMuon>=2
		      ) {
		    int mu01p11=myCombIdx[0].p11,mu01p12=myCombIdx[0].p12,mu11p11=myCombIdx[1].p11,mu11p12=myCombIdx[1].p12,  mu21p11=myCombIdx[2].p11,mu21p12=myCombIdx[2].p12;
		    int mu02p11=myCombIdx[0].p21,mu02p12=myCombIdx[0].p22,mu12p11=myCombIdx[1].p21,mu12p12=myCombIdx[1].p22,  mu22p11=myCombIdx[2].p21,mu22p12=myCombIdx[2].p22;
		    myMuMu01Chgp2ARCmassafterselection->Fill( (fitMup4vect[ mu01p11 ]+fitMup4vect[ mu01p12 ]).M() );
		    myMuMu02Chgm2ARCmassafterselection->Fill( (fitMup4vect[ mu02p11 ]+fitMup4vect[ mu02p12 ]).M() );
		    myMuMu11Chg0ARCmassafterselection->Fill( (fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M() );
		    myMuMu12Chg0ARCmassafterselection->Fill( (fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M() );
		    myMuMu21Chg0ARCmassafterselection->Fill( (fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M() );
		    myMuMu22Chg0ARCmassafterselection->Fill( (fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M() );
		    //cout<<myNumGoodTightMuon<<endl;
		    int nY1Comination2Tightmu=0;
		    if(isTightMuon[mu11p11]>0 && isTightMuon[mu11p12]>0)
		      {
			if( fabs(rawMup4vect[mu11p11].Eta()) > 1.0 && fabs(rawMup4vect[mu11p12].Eta()) >1.0 )			   
			  {
			    //cout<<", ee m="<<(fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()<<endl;
			    myMuMuChg0ARCmasswith2tightmuEE->Fill( (fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M() ); 
			  } else 
			  if( fabs(rawMup4vect[mu11p11].Eta()) > 1.0 || fabs(rawMup4vect[mu11p12].Eta()) >1.0 ) 
			    {
			      //cout<<", eb m="<<(fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()<<endl;
			      myMuMuChg0ARCmasswith2tightmuEB->Fill( (fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M() );
			    } else 
			    {
			      //cout<<", bb m="<<(fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()<<endl;
			      myMuMuChg0ARCmasswith2tightmuBB->Fill( (fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M() );
			    } 
			//cout<<"11,"<<(fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()<<endl;	
			if( fabs((fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()-9.46)<0.25 ) 
			  {nY1Comination2Tightmu++;
			  }
			myMuMuwith2tightmuChg0ARCmassafterselection->Fill( (fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M() );
		      }
		    if(isTightMuon[mu12p11]>0 && isTightMuon[mu12p12]>0)
		      {
			if( fabs(rawMup4vect[mu12p11].Eta()) > 1.0 && fabs(rawMup4vect[mu12p12].Eta()) >1.0 )			   
			  {
			    //cout<<", ee m="<<(fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()<<endl;
			    myMuMuChg0ARCmasswith2tightmuEE->Fill( (fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M() ); 
			  } else 
			  if( fabs(rawMup4vect[mu12p11].Eta()) > 1.0 || fabs(rawMup4vect[mu12p12].Eta()) >1.0 ) 
			    {
			      //cout<<", eb m="<<(fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()<<endl;
			      myMuMuChg0ARCmasswith2tightmuEB->Fill( (fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M() );
			    } else 
			    {
			      //cout<<", bb m="<<(fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()<<endl;
			      myMuMuChg0ARCmasswith2tightmuBB->Fill( (fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M() );
			    } 			

			if( fabs((fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()-9.46)<0.25 ) 
			  {nY1Comination2Tightmu++;
			  }
			myMuMuwith2tightmuChg0ARCmassafterselection->Fill( (fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M() );
			//cout<<"12,"<<(fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()<<endl;			
		      }
		    if(isTightMuon[mu21p11]>0 && isTightMuon[mu21p12]>0)
		      {
			if( fabs(rawMup4vect[mu21p11].Eta()) > 1.0 && fabs(rawMup4vect[mu21p12].Eta()) >1.0 )			   
			  {
			    //cout<<", ee m="<<(fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()<<endl;
			    myMuMuChg0ARCmasswith2tightmuEE->Fill( (fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M() ); 
			  } else 
			  if( fabs(rawMup4vect[mu21p11].Eta()) > 1.0 || fabs(rawMup4vect[mu21p12].Eta()) >1.0 ) 
			    {
			      //cout<<", eb m="<<(fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()<<endl;
			      myMuMuChg0ARCmasswith2tightmuEB->Fill( (fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M() );
			    } else 
			    {
			      //cout<<", bb m="<<(fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()<<endl;
			      myMuMuChg0ARCmasswith2tightmuBB->Fill( (fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M() );
			    } 

			if( fabs((fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()-9.46)<0.25 ) 
			  {nY1Comination2Tightmu++;
			  }
			myMuMuwith2tightmuChg0ARCmassafterselection->Fill( (fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M() );
			//cout<<"21,"<<(fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()<<endl;			
		      }
		    if(isTightMuon[mu22p11]>0 && isTightMuon[mu22p12]>0)
		      {
			if( fabs(rawMup4vect[mu22p11].Eta()) > 1.0 && fabs(rawMup4vect[mu22p12].Eta()) >1.0 )			   
			  {
			    //cout<<", ee m="<<(fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()<<endl;
			    myMuMuChg0ARCmasswith2tightmuEE->Fill( (fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M() ); 
			  } else 
			  if( fabs(rawMup4vect[mu22p11].Eta()) > 1.0 || fabs(rawMup4vect[mu22p12].Eta()) >1.0 ) 
			    {
			      //cout<<", eb m="<<(fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()<<endl;
			      myMuMuChg0ARCmasswith2tightmuEB->Fill( (fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M() );
			    } else 
			    {
			      //cout<<", bb m="<<(fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()<<endl;
			      myMuMuChg0ARCmasswith2tightmuBB->Fill( (fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M() );
			    } 
			
			if( fabs((fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()-9.46)<0.25 ) 
			  {nY1Comination2Tightmu++;
			  }
			myMuMuwith2tightmuChg0ARCmassafterselection->Fill( (fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M() );
			//cout<<"22,"<<(fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()<<endl;			
		      }
		    
		    myNY1swith2tightmusARCafterselection->Fill( nY1Comination2Tightmu );

		    for(int myi=1; myi<3; myi++) {
		      for (int myj=0;myj<2; myj++) {
			int myjanother=1; if(myj==1) { myjanother=0; }
			int muIdxthisARCp11, muIdxthisARCp12, muIdxanotherARCp11, muIdxanotherARCp12;
			if(myj==0) {
			  muIdxthisARCp11=myCombIdx[myi].p11; muIdxthisARCp12=myCombIdx[myi].p12; 
			  muIdxanotherARCp11=myCombIdx[myi].p21; muIdxanotherARCp12=myCombIdx[myi].p22;
			}
			if(myj==1) {
			  muIdxthisARCp11=myCombIdx[myi].p21; muIdxthisARCp12=myCombIdx[myi].p22; 
			  muIdxanotherARCp11=myCombIdx[myi].p11; muIdxanotherARCp12=myCombIdx[myi].p12;
			}
			TLorentzVector mymumuthisp4=rawMup4vect[ muIdxthisARCp11 ]+ rawMup4vect[ muIdxthisARCp12 ];
			TLorentzVector mymumuanotherp4=rawMup4vect[ muIdxanotherARCp11 ]+ rawMup4vect[ muIdxanotherARCp12 ];
			double myrapthis=fabs(0.5*log( (mymumuthisp4.E() + mymumuthisp4.Pz())/(mymumuthisp4.E() - mymumuthisp4.Pz()) ) );
			double myrapanother=fabs(0.5*log( (mymumuanotherp4.E() + mymumuanotherp4.Pz())/(mymumuanotherp4.E() - mymumuanotherp4.Pz()) ) );
			//obtained from data
			double myY1sResthis=0.0572+0.03602*myrapthis;
			double myY1sRespanother=0.0572+0.03602*myrapanother; 
			
			if( fabs((fitMup4vect[ muIdxthisARCp11 ]+ fitMup4vect[ muIdxthisARCp12 ]).M()-9.46)<0.25 )
			  {
			    myARCMuMuHighmasserr->Fill( myY1sResthis ); 
			    myARCMuMuHighmasserrEBE->Fill( myMupMumMassErr[myi][myj] );
			    myAnotherMuMuChg0ARCwithY1sonthismumumass->Fill( (fitMup4vect[ muIdxanotherARCp11 ]+ fitMup4vect[ muIdxanotherARCp12 ]).M() );
			    myFourmuChg0ARCmass->Fill( myfourmuonmass );
			    if( (fitMup4vect[ muIdxanotherARCp11 ]+ fitMup4vect[ muIdxanotherARCp12 ]).M()<9.2 )
			      {myFourmuChg0ARCmassWithanotherdimult9dot2->Fill( myfourmuonmass ); }

			  }//if( fabs(myMupMumMass[myi][myj]-9.46)<0.25 )
		      }//for (int myj=0;myj<2; myj++) {
		    }// for(int myi=1; myi<3; myi++) {
		  }//if( mypidx==1 

		  if(1
		 //    &&TrigThreeMuonUpsi
		     && fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myY1sResp1 
		     && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma*myY1sResp2 )
		     && myNumGoodTightMuon>=2 //if one of the V is Upsilon	
		     && NumDupARC<1
		     ) 
		    {
		      myFourmuChg0ARCmassandanotherdimultY1s->Fill( myfourmuonmass ); 
		      NumDupARC++;
		    }
		  //with EBE
		  if(1
		     //&&TrigThreeMuonUpsi
		     && fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myMupMumMassErr[mypidx][0]
		     && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma* myMupMumMassErr[mypidx][1] )
		     && myNumGoodTightMuon>=2 //if one of the V is Upsilon	
		     && NumDupARCEBE<1
		     ) 
		    {
		      myFourmuChg0ARCmassandanotherdimultY1sEBE->Fill( myfourmuonmass ); 
		      if( myfourmuonmass>18.0 && myfourmuonmass<19.0) {
		      }
		      NumDupARCEBE++;
		    }

//to get the m12 mass distribution for low mass OS sample
if((((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp22 ]).M()<4.0 &&  (fitMup4vect[ muIdxp12 ]+ fitMup4vect[ muIdxp21 ]).M()<4.0)
  ||
  ((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp21 ]).M()<4.0 &&  (fitMup4vect[ muIdxp12 ]+ fitMup4vect[ muIdxp22 ]).M()<4.0))
  && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma*myEBEscale*myMupMumMassErr[mypidx][1] )
  && myNumGoodTightMuon>=2
)
{
myM12forLowMassOS->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()  );

if(
(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() >=9.1 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() <=9.7 
)
{
myM12masserrforLowMassOS->Fill( myMupMumMassErr[mypidx][0] );
myMu1EtaforLowMassOS->Fill( fitMup4vect[ muIdxp11 ].Eta() );
myMu2EtaforLowMassOS->Fill( fitMup4vect[ muIdxp12 ].Eta() );
}
//cout<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<<endl;


if( 1
 && fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0]
// && NumDupMiddleDefault<1
)
{
my4mumasswithm12atmiddlesidedefault->Fill( myfourmuonmass );
NumDupMiddleDefault++;
}

if( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() >=9.2 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<=9.7  )
{
my4mumasswithm12atmiddleside->Fill( myfourmuonmass );
}

if( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() >=8.6 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<=9.2  
//&& NumDupLowSide<1
)
{
my4mumasswithm12atlowside->Fill( myfourmuonmass  ); 
my4mumasswithm12atlowsideshift->Fill( myfourmuonmass - (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() + 9.46 );
NumDupLowSide++;
}
if( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() >=9.9 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<=11.4  
//&& NumDupHighSide<1
)
{
my4mumasswithm12athighside->Fill( myfourmuonmass  );
my4mumasswithm12athighsideshift->Fill( myfourmuonmass - (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() + 9.46   );
NumDupHighSide++;
}
}
//end to get the m12 mass distribution for low mass OS sample

		  if(1
		     
		     && myVVmasscut		     
		     ) 
		    {
		      if(NumDup<1) //need to uncomment it for default
                      {			
			//dihedral angle
			TLorentzVector myfourmuonp4=fitMup4vect[0]+fitMup4vect[1]+fitMup4vect[2]+fitMup4vect[3];
			TLorentzVector fitMu11bosstedp4, fitMu12bosstedp4, fitMu21bosstedp4, fitMu22bosstedp4;
			fitMu11bosstedp4=fitMup4vect[ muIdxp11 ]; fitMu12bosstedp4=fitMup4vect[ muIdxp12 ];
			fitMu21bosstedp4=fitMup4vect[ muIdxp21 ]; fitMu22bosstedp4=fitMup4vect[ muIdxp22 ];
			fitMu11bosstedp4.Boost( -myfourmuonp4.BoostVector() ); fitMu12bosstedp4.Boost( -myfourmuonp4.BoostVector() );
			fitMu21bosstedp4.Boost( -myfourmuonp4.BoostVector() ); fitMu22bosstedp4.Boost( -myfourmuonp4.BoostVector() );
			TVector3 OrthMupMum1=fitMu11bosstedp4.Vect().Cross( fitMu12bosstedp4.Vect()  );
			TVector3 OrthMupMum2=fitMu21bosstedp4.Vect().Cross( fitMu22bosstedp4.Vect()  );
			float myDihedral=  TMath::ACos(OrthMupMum1.Unit().Dot(OrthMupMum2.Unit() ) );
			//cout<<"myDihedral="<<myDihedral<<endl;
			//helicity angle of two mumu pairs			  
			TLorentzVector mymupmum1p4=fitMu11bosstedp4+ fitMu12bosstedp4;
			TLorentzVector mymupmum1p4boosted=fitMu11bosstedp4+ fitMu12bosstedp4;
			//mymupmum1p4boosted.Boost( -myfourmuonp4.BoostVector() );
			float mymupmum1CosHelicity= cos( mymupmum1p4boosted.Vect().Angle( myfourmuonp4.Vect() ) );
			//cout<<"mymupmum1CosHelicity="<<mymupmum1CosHelicity<<endl;
			//helicity of mu+mu- for each pair
			TLorentzVector mymupmum2p4=fitMu21bosstedp4+fitMu22bosstedp4;
			//mymupmum2p4.Boost( -myfourmuonp4.BoostVector() );
			TLorentzVector mymupmum1mupboosted; 
			mymupmum1mupboosted=fitMu11bosstedp4; 
			TLorentzVector mymupmum2mupboosted; 
			mymupmum2mupboosted=fitMu21bosstedp4; 
			mymupmum1mupboosted.Boost( -mymupmum1p4.BoostVector() );
			mymupmum2mupboosted.Boost( -mymupmum2p4.BoostVector() );
			float mymupmum1mupCosHelicity= cos( mymupmum1mupboosted.Vect().Angle( mymupmum1p4.Vect() ) );
			float mymupmum2mupCosHelicity= cos( mymupmum2mupboosted.Vect().Angle( mymupmum2p4.Vect() ) );
int theotherdimuidx=2; if(mypidx==2) {theotherdimuidx=1;}

 if(  
//    myfourmuonmass>=18.0 && myfourmuonmass<=19.5 
   myfourmuonmass>=18.1 && myfourmuonmass<=18.7

      )
   {
     myWrongdimu1signal->Fill( (fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M() );
     myWrongdimu2signal->Fill( (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );

   }
 
 if((
    (myfourmuonmass>=17.7 && myfourmuonmass<=18.0 )
    ||
    (myfourmuonmass>=19.5 && myfourmuonmass<=19.8 )))
   {
     myWrongdimu1sideband->Fill( (fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M() );
     myWrongdimu2sideband->Fill( (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );
   }
 
 if( fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-3.096919)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
     && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-3.096919)>  myMupMumMassErr[myanotherpidx][1]*myexclnsigma
     //&& fabs( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.096919)> myMupMumMassErr[mypidx][1]*myexclnsigma
     && fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
     && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][1]*myexclnsigma
     //&& fabs( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-1.01946)> myMupMumMassErr[mypidx][1]*myexclnsigma
     && fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][0]*myexclnsigma
     && fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][1]*myexclnsigma
     //&& fabs( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-0.78265)> myMupMumMassErr[mypidx][1]*myexclnsigma
     ) {

float mymassdiff=-9;  

if(   //to blind the signal region for 2016, 2017 & 2018 dataset
	1	
)
   {
     myMuMuMuMumassV1mumubelowV1nolightmeson->Fill( myfourmuonmass );

     myMuMuMuMumassConstraintV1mumubelowV1nolightmeson->Fill( my4mumassConstraint[ mypidx ] );

	TLorentzVector myRecop4, myRecodau1mupp4, myRecodau1mump4, myRecodau2mupp4, myRecodau2mump4, mytmpp4;
	
	myRecodau1mupp4 = fitMup4vect[ muIdxp11 ];
	myRecodau1mump4 = fitMup4vect[ muIdxp12 ];
	myRecodau2mupp4 = fitMup4vect[ muIdxp21 ];
	myRecodau2mump4 = fitMup4vect[ muIdxp22 ];


	float eta_mu1 = myRecodau1mupp4.Eta();
    float pt_mu1 =  myRecodau1mupp4.Pt();
    float m_mu1 =   myRecodau1mupp4.M();
    float re_mu1 =  myRecodau1mupp4.Rapidity();

    float eta_mu2 = myRecodau1mump4.Eta();
    float pt_mu2 =  myRecodau1mump4.Pt();
    float m_mu2 =   myRecodau1mump4.M();
    float re_mu2 =  myRecodau1mump4.Rapidity();

    float eta_mu3 = myRecodau2mupp4.Eta();
    float pt_mu3 =  myRecodau2mupp4.Pt();
    float m_mu3 =   myRecodau2mupp4.M();
    float re_mu3 =  myRecodau2mupp4.Rapidity();

    float eta_mu4 = myRecodau2mump4.Eta();
    float pt_mu4 =  myRecodau2mump4.Pt();
    float m_mu4 =   myRecodau2mump4.M();
    float re_mu4 =  myRecodau2mump4.Rapidity();

    float dau1_pt = (myRecodau1mupp4+myRecodau1mump4).Pt();
    float dau2_pt = (myRecodau2mupp4+myRecodau2mump4).Pt();

    float dau1_eta = fabs( (myRecodau1mupp4+myRecodau1mump4).Eta() );
    float dau2_eta = fabs( (myRecodau2mupp4+myRecodau2mump4).Eta() );

	float temppt[4]={pt_mu1,pt_mu2,pt_mu3,pt_mu4};
    float pt1st,pt2nd,pt3rd,pt4th;
    int num=4;
    for(int j = num; j>=1; j--){
            arange(temppt,num);

    }

	float tempeta[4]={fabs(eta_mu1),fabs(eta_mu2),fabs(eta_mu3),fabs(eta_mu4)};
    float eta1st,eta2nd,eta3rd,eta4th;
    int hwen=4;
    for(int m = hwen; m>=1; m--){
            arange(tempeta,hwen);

    }

    float tmppt[2]={dau1_pt,dau2_pt};
    float daupt1st,daupt2nd;
    int dau=2;
    for(int n = dau; n>=1; n--){
            arange(tmppt,dau);

    }

    float tmpeta[2]={dau1_eta,dau2_eta};
    float daueta1st,daueta2nd;
    int eta=2;
    for(int n = eta; n>=1; n--){
            arange(tmpeta,eta);

    }


	pt1st=temppt[0];
    pt2nd=temppt[1];
    pt3rd=temppt[2];
    pt4th=temppt[3];

	eta1st=tempeta[0];
    eta2nd=tempeta[1];
    eta3rd=tempeta[2];
    eta4th=tempeta[3];

    daupt1st=tmppt[0];
    daupt2nd=tmppt[1];

    daueta1st=tmpeta[0];
    daueta2nd=tmpeta[1];



	recomuonpt1st->Fill(pt1st);
    recomuonpt2nd->Fill(pt2nd);
    recomuonpt3rd->Fill(pt3rd);
    recomuonpt4th->Fill(pt4th);

    recomuoneta1st->Fill(eta1st);
    recomuoneta2nd->Fill(eta2nd);
    recomuoneta3rd->Fill(eta3rd);
    recomuoneta4th->Fill(eta4th);

    recohdaupt1st->Fill(daupt1st);
    recohdaupt2nd->Fill(daupt2nd);

    recohdaueta1st->Fill(daueta1st);
    recohdaueta2nd->Fill(daueta2nd);
	

	myrecoMuon14DeltaR->Fill(myRecodau1mupp4.DeltaR(myRecodau2mump4));
	myrecoMuon13DeltaR->Fill(myRecodau1mupp4.DeltaR(myRecodau2mupp4));
	myrecoMuon24DeltaR->Fill(myRecodau1mump4.DeltaR(myRecodau2mump4));
	myrecoMuon23DeltaR->Fill(myRecodau1mump4.DeltaR(myRecodau2mupp4));
	myrecoMuon12DeltaR->Fill(myRecodau1mupp4.DeltaR(myRecodau1mump4));
	myrecoMuon34DeltaR->Fill(myRecodau2mupp4.DeltaR(myRecodau2mump4));

	myrecodau1muppt->Fill( (myRecodau1mupp4).Pt() );
	myrecodau1mumpt->Fill( (myRecodau1mump4).Pt() );
	myrecodau2muppt->Fill( (myRecodau2mupp4).Pt() );
	myrecodau2mumpt->Fill( (myRecodau2mump4).Pt() );

	myrecodau1mupEta->Fill( (myRecodau1mupp4).Eta() );
	myrecodau1mumEta->Fill( (myRecodau1mump4).Eta() );
	myrecodau2mupEta->Fill( (myRecodau2mupp4).Eta() );
	myrecodau2mumEta->Fill( (myRecodau2mump4).Eta() );


	myrecodau1pt->Fill( (myRecodau1mupp4+myRecodau1mump4).Pt() );
	myrecodau2pt->Fill( (myRecodau2mupp4+myRecodau2mump4).Pt() );

	myrecopt->Fill( (myRecodau1mupp4+myRecodau1mump4+myRecodau2mupp4+myRecodau2mump4).Pt() );
	myrecoEta->Fill( (myRecodau1mupp4+myRecodau1mump4+myRecodau2mupp4+myRecodau2mump4).Eta() );

	rapdiff->Fill( fabs( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Rapidity() - (fitMup4vect[ muIdxp21 ]+  fitMup4vect[ muIdxp22 ]).Rapidity() ) );


     myM12VsM34->Fill( (fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M(), (fitMup4vect[ muIdxp21 ]+fitMup4vect[ muIdxp22 ]).M() );

     myMupmumu1Helicityfine->Fill( mymupmum1mupCosHelicity );


     //if(mychannel==55 || mychannel==66 )
     if(mychannel==66 )
       {
mymassdiff=myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()-(fitMup4vect[ muIdxp21 ]+fitMup4vect[ muIdxp22 ]).M()+2.0*mymV; 
//	 myMuMuMuMumassV1mumubelowV1nolightmesonDiff->Fill( myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()-(fitMup4vect[ muIdxp21 ]+fitMup4vect[ muIdxp22 ]).M()+2.0*mymV );
       
//eventselection << setw(10) <<runNum<<"\t"<< setw(10) <<lumiNum<<"\t"<< setw(10) << evtNum<<"\t"<< setw(10) <<my4mumassConstraint[ mypidx ]<<"\t"<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]+fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<"\n";
}
     else 
       {
mymassdiff=myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV; 
//	 myMuMuMuMumassV1mumubelowV1nolightmesonDiff->Fill( myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV );
       }
myMuMuMuMumassV1mumubelowV1nolightmesonDiff->Fill( mymassdiff );
     
     
   }
   

 myRunNum->Fill( runNum );
myMuMuMuMumassDiffV1mumubelowV1nolightmesoninaonthercombination->Fill(  myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV );
//myoutfilesignal1<<myfourmuonmass<<" "<<( myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV)<<" "<<(*MyFourMuonMassErr)[myFourMuIdx]<<endl;


if(  myfourmuonmass>=18.1 && myfourmuonmass<=18.7 )
 {
   myMu12vsMu34->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M(),(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
   myMu14vsMu23->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp22 ]).M(),(fitMup4vect[ muIdxp12 ]+ fitMup4vect[ muIdxp21 ]).M() );
			
   myMu12mass->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );
   myMu34mass->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
   myMu14mass->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp22 ]).M() );
   myMu23mass->Fill( (fitMup4vect[ muIdxp12 ]+ fitMup4vect[ muIdxp21 ]).M() );
   myMu13mass->Fill( (fitMup4vect[ myCombIdx[0].p11 ]+ fitMup4vect[ myCombIdx[0].p12 ]).M() );
   myMu24mass->Fill( (fitMup4vect[ myCombIdx[0].p21 ]+ fitMup4vect[ myCombIdx[0].p22 ]).M() );

   if(
      (fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()<=4.0 && (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()<=4.0
      )
     {NlowmassOS++;}
   if(
       (fitMup4vect[ myCombIdx[0].p11 ]+ fitMup4vect[ myCombIdx[0].p12 ]).M()<=4.0 && (fitMup4vect[ myCombIdx[0].p21 ]+ fitMup4vect[ myCombIdx[0].p22 ]).M()<=4.0
      )
     {NlowmassSS++;}

 }

if(   //to blind the signal region for 2016, 2017 & 2018 dataset
	1	
//(my4mumassConstraint[ mypidx ]<6.26 )
//(lumiNum==6756 )
//||
//(lumiNum==6734 )
//||
//(lumiNum==6697 )
//||
//(lumiNum==6641 )
//||
//(lumiNum==6647 )
//||
//(my4mumassConstraint[ mypidx ]>6.7 && my4mumassConstraint[ mypidx ]<6.8 ) 
//||
//(my4mumassConstraint[ mypidx ]>7.1 && my4mumassConstraint[ mypidx ]<7.2 )  
//||
//(my4mumassConstraint[ mypidx ]>7.8 )
)

{

eventselection <<runNum<<":"<<lumiNum<<":"<< evtNum<<":"<<my4mumassConstraint[ mypidx ]<<":"<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]+fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<"\n";
}
//eventselection << setw(10) <<runNum<<"\t"<< setw(10) <<lumiNum<<"\t"<< setw(10) << evtNum<<"\t"<< setw(10) <<my4mumassConstraint[ mypidx ]<<"\t"<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]+fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<"\n";


 myMuMu1MassWithoutlightmesonatunselectedcombination->Fill(  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()  );
 myMuMu2MassWithoutlightmesonatunselectedcombination->Fill(  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()  );
 
 if(
    myfourmuonmass>=18.0 && myfourmuonmass<=19.0
    )
   {
     myDalitzmY1smupmasssqVsmmumumasssqat18GeV->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ]  ).M2(),(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp22 ]  ).M2() );

     mym3musqVssecondDimuMasssq->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ]  ).M2(),(fitMup4vect[ muIdxp21 ] + fitMup4vect[ muIdxp22 ]  ).M2() );

   } 

 myFourMumassVssecondDimuMass->Fill( myfourmuonmass,  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
}
else {
myMuMuMuMumassV1mumubelowV1withlightmeson->Fill( myfourmuonmass );
myMuMuMuMumassV1mumubelowV1withlightmesonDiff->Fill( myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV );

 myMuMu1MassWithlightmesonatunselectedcombination->Fill(  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()  );
 myMuMu2MassWithlightmesonatunselectedcombination->Fill(  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()  );

}
 
 myMuMuMuMumassV1mumubelowV1->Fill( myfourmuonmass );
 myMuMuMuMumassDiffV1mumubelowV1->Fill( myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV  );

 if(NumDup>0) {
   myMuMuMuMumassV1mumubelowV1ifSecondOption->Fill( myfourmuonmass ); 
   myMuMuMuMumassV1mumubelowV1ifSecondOptionDiff->Fill( myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV ); 

 }

//dr means deltaeta
float dr12,dr13,dr14,dr23,dr24,dr34, mymaxdeta;
dr12=fabs(rawMup4vect[0].Eta()-rawMup4vect[1].Eta());
dr13=fabs(rawMup4vect[0].Eta()-rawMup4vect[2].Eta()); 
dr14=fabs(rawMup4vect[0].Eta()-rawMup4vect[3].Eta()); 
dr23=fabs(rawMup4vect[1].Eta()-rawMup4vect[2].Eta()); 
dr24=fabs(rawMup4vect[1].Eta()-rawMup4vect[3].Eta()); 
dr34=fabs(rawMup4vect[2].Eta()-rawMup4vect[3].Eta()); 

mymaxdeta=std::max(dr12,dr13); mymaxdeta=std::max(mymaxdeta,dr14 ); mymaxdeta=std::max(mymaxdeta,dr23 );
mymaxdeta=std::max(mymaxdeta,dr24 ); mymaxdeta=std::max(mymaxdeta,dr34 );

myMuMuMuMumMaxDeltaEta->Fill(mymaxdeta); 

			float mytmpdp=fabs((*muPx)[ myCombIdx[0].p11 ]-(*muPx)[ myCombIdx[0].p12 ])+fabs((*muPy)[ myCombIdx[0].p11 ]-(*muPy)[ myCombIdx[0].p12 ])+fabs((*muPz)[ myCombIdx[0].p11 ]-(*muPz)[ myCombIdx[0].p12 ]);
			myMuPPDeltapxpypz->Fill( mytmpdp );
			mytmpdp=fabs((*muPx)[ myCombIdx[0].p21 ]-(*muPx)[ myCombIdx[0].p22 ])+fabs((*muPy)[ myCombIdx[0].p21 ]-(*muPy)[ myCombIdx[0].p22 ])+fabs((*muPz)[ myCombIdx[0].p21 ]-(*muPz)[ myCombIdx[0].p22 ]);
			myMuMMDeltapxpypz->Fill( mytmpdp );
			float deltaPhi1=rawMup4vect[ muIdxp12 ].Phi()-rawMup4vect[ muIdxp11 ].Phi();
			float deltaPhi2=rawMup4vect[ muIdxp22 ].Phi()-rawMup4vect[ muIdxp21 ].Phi();
			if(deltaPhi1 > TMath::Pi()) deltaPhi1 -= 2.*TMath::Pi();
			else if(deltaPhi1 < -TMath::Pi()) deltaPhi1 += 2.*TMath::Pi();
			if(deltaPhi2 > TMath::Pi()) deltaPhi2 -= 2.*TMath::Pi();
			else if(deltaPhi2 < -TMath::Pi()) deltaPhi2 += 2.*TMath::Pi();

			if( deltaPhi1<0 && deltaPhi2<0 ) myMuMuMuMumassV1mumubelowV1cowboyVscowboy->Fill( myfourmuonmass );
			if( deltaPhi1<0 && deltaPhi2>0 ) myMuMuMuMumassV1mumubelowV1cowboyVsseagull->Fill( myfourmuonmass );
			if( deltaPhi1>0 && deltaPhi2<0 ) myMuMuMuMumassV1mumubelowV1seagullVscowboy->Fill( myfourmuonmass );
			if( deltaPhi1>0 && deltaPhi2>0 ) {
			  myMuMuMuMumassV1mumubelowV1seagullVsseagull->Fill( myfourmuonmass );
			  if(myfourmuonmass>15.2 && myfourmuonmass<16.2) {
			    myMuMu2Massat15dot7GeV->Fill(  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
			  }
			}
			
			
			if( 
			   (*muIsoratio)[ muIdxp11 ]<0.1 && (*muIsoratio)[ muIdxp12 ]<0.1
			   )
			  {
			    myMuMuMuMumassV1mumuWithVIso0dot1belowV1->Fill( myfourmuonmass );
			  }

			if( 
			   (*muIsoratio)[ muIdxp11 ]<0.2 && (*muIsoratio)[ muIdxp12 ]<0.2
			   )
			  {
			    myMuMuMuMumassV1mumuWithVIso0dot2belowV1->Fill( myfourmuonmass );
			  }
			if( 
			   (*muIsoratio)[ muIdxp11 ]<0.5 && (*muIsoratio)[ muIdxp12 ]<0.5
			   )
			  {
			    myMuMuMuMumassV1mumuWithVIso0dot5belowV1->Fill( myfourmuonmass );
			  }

			if( 
			   (*muIsoratio)[  (*MyFourMuonMu1Idx)[myFourMuIdx] ]<0.1 
			   )
			  {
			    myMuMuMuMumassV1highestmuWithVIso0dot1belowV1->Fill( myfourmuonmass );
			  }
			if( 
			   (*muIsoratio)[  (*MyFourMuonMu1Idx)[myFourMuIdx] ]<0.2 
			   )
			  {
			    myMuMuMuMumassV1highestmuWithVIso0dot2belowV1->Fill( myfourmuonmass );
			  }
			if( 
			   (*muIsoratio)[  (*MyFourMuonMu1Idx)[myFourMuIdx] ]<0.5 
			   )
			  {
			    myMuMuMuMumassV1highestmuWithVIso0dot5belowV1->Fill( myfourmuonmass );
			  }



			if( myfourmuonmass>=18.0 && myfourmuonmass<=19.0 ) {

			  myDeltaR4minOppositeMuat18dot5GeV->Fill( rawMup4vect[ muIdxp11 ].DeltaR( rawMup4vect[ muIdxp12 ]) );
			  myDeltaR4minOppositeMuat18dot5GeV->Fill( rawMup4vect[ muIdxp21 ].DeltaR( rawMup4vect[ muIdxp22 ]) );
			  myDeltaR4minOppositeMuat18dot5GeV->Fill( rawMup4vect[ muanotherIdxp11 ].DeltaR( rawMup4vect[ muanotherIdxp12 ]) );
			  myDeltaR4minOppositeMuat18dot5GeV->Fill( rawMup4vect[ muanotherIdxp21 ].DeltaR( rawMup4vect[ muanotherIdxp22 ]) );
			  myDeltaR4minSameSignMuat18dot5GeV->Fill( rawMup4vect[ muIdxp11 ].DeltaR( rawMup4vect[ muIdxp21 ]) );
			  myDeltaR4minSameSignMuat18dot5GeV->Fill( rawMup4vect[ muIdxp12 ].DeltaR( rawMup4vect[ muIdxp22 ]) );

			  myMu1Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] );
			  myMu2Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu2Idx)[myFourMuIdx]] );
			  myMu3Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] );
			  myMu4Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu4Idx)[myFourMuIdx]] );
			  
			  myMuMu1Massat18dot5GeV->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );
 			  myMuMu2Massat18dot5GeV->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
			  myFourMuPtat18dot5GeV->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
			  myFourMuRapidityat18dot5GeV->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Rapidity() );

			  myFourMuPat18dot5GeV->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).P() );

			  if ( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() >= 8.0 ) {
			    //myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );
			  }
			  
			  myMu1Ptat18dot5GeV->Fill( rawMup4vect[0].Pt() );
			  myMu2Ptat18dot5GeV->Fill( rawMup4vect[1].Pt() );
			  myMu3Ptat18dot5GeV->Fill( rawMup4vect[2].Pt() );
			  myMu4Ptat18dot5GeV->Fill( rawMup4vect[3].Pt() );

 			  myMu21Ptstartat18dot5GeV->Fill( rawMuinFourMuFMp4vect[muIdxp21].Pt() ); 
 			  myMu22Ptstartat18dot5GeV->Fill( rawMuinFourMuFMp4vect[muIdxp22].Pt() ); 

			  myMuMu1Ptat18dot5GeV->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Pt() );
			  myMuMu2Ptat18dot5GeV->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Pt() );
			  myMuMuPairsDihedralat18dot5GeV->Fill( myDihedral );

myMuMuPairsabscosDihedralat18dot5GeV->Fill( fabs(cos(myDihedral)) );

			  myMuMuPairsHelicityat18dot5GeV->Fill( mymupmum1CosHelicity );
			  myMupmumu1Helicityat18dot5GeV->Fill( mymupmum1mupCosHelicity );
                          myMupmumu1Helicityat18dot5GeVfine->Fill( mymupmum1mupCosHelicity );

			  myMupmumu2Helicityat18dot5GeV->Fill( mymupmum2mupCosHelicity );
			  myFourMuFLSigat18dot5GeV->Fill( (*MyFourMuonFLSig)[myFourMuIdx] );

			  my4MuCtauat18dot5GeV->Fill(  (*MyFourMuonCTau)[ myFourMuIdx ] );

			  myMuMu1Ctauat18dot5GeV->Fill( myMupMumCTau[mypidx][0] );    //there is a problem here, could be mixed between 1 &2, 1&2 did not swith when we change it 
			  myMuMu2Ctauat18dot5GeV->Fill( myMupMumCTau[mypidx][1] );    //there is a problem here, could be mixed between 1 &2, should be ok if put 1&2 together
			}
			if( (myfourmuonmass>=16.0 && myfourmuonmass<=17.0)   //background in signal area is 1/1.8 of sideband
			    ||
			    (myfourmuonmass>=20.0 && myfourmuonmass<=21.0)
			    ) {

			  //myDalitzmY1smupmasssqVsmmumumasssqatSideband->Fill(  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ]  ).M2(), (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M2()  );


			  myMuMu1MassatSideband->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );

			  myMuMu2MassatSideband->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
			  myFourMuPtatSideband->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
			  myFourMuRapidityatSideband->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Rapidity() );
			  myFourMuPatSideband->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).P() );


			  if ( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() >= 8.0 ) {
			    //myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );
			  }

			  myMu1PtatSideband->Fill( rawMup4vect[0].Pt() );
			  myMu2PtatSideband->Fill( rawMup4vect[1].Pt() );
			  myMu3PtatSideband->Fill( rawMup4vect[2].Pt() );
			  myMu4PtatSideband->Fill( rawMup4vect[3].Pt() );

 			  myMu21PtstartatSideband->Fill( rawMuinFourMuFMp4vect[ muIdxp21 ].Pt() ); 
 			  myMu22PtstartatSideband->Fill( rawMuinFourMuFMp4vect[ muIdxp22].Pt() ); 

			  myMuMu1PtatSideband->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Pt() );
			  myMuMu2PtatSideband->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Pt() );
			  myMuMuPairsDihedralatSideband->Fill( myDihedral );

                          myMuMuPairsabscosDihedralatSideband->Fill( fabs(cos(myDihedral)) ); 

			  myMuMuPairsHelicityatSideband->Fill( mymupmum1CosHelicity );
			  myMupmumu1HelicityatSideband->Fill( mymupmum1mupCosHelicity );
                          myMupmumu1HelicityatSidebandfine->Fill( mymupmum1mupCosHelicity ); 

			  myMupmumu2HelicityatSideband->Fill( mymupmum2mupCosHelicity );
			  myFourMuFLSigatSideband->Fill(  (*MyFourMuonFLSig)[myFourMuIdx] );
			  my4MuCtauatSideband->Fill(  (*MyFourMuonCTau)[ myFourMuIdx ] );

			  myMuMu1CtauatSideband->Fill( myMupMumCTau[mypidx][0] );    //there is a problem here, could be mixed between 1 &2
			  myMuMu2CtauatSideband->Fill( myMupMumCTau[mypidx][1] );    //there is a problem here, could be mixed between 1 &2
			}//if( (myfourmuonmass>=16.0 && myfourmuonmass<=17.0) 
			
			//to remove duplicate
			NumDup++;
		      }//if(NumDup<1) {
		    }//if(fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )< 3.0*myY1sResp1
		  
		}//if(1
	      }//for(mycombi=1; myCombi<3; myCombi++)
	    //}//for(int myVi=0;myVi<1;myVi++)	    
	  }//if(1			
		
      }//for (int myFourMuIdx = 0; myFourMuIdx <nJ; myFourMuIdx++)
    
       
  }//for (Long64_t jentry=0;
  //cout<<"NumxJHUTotalwith4mu="<<NumxJHUTotalwith4mu<<",NumxJHUTotalwith2mu="<<NumxJHUTotalwith2mu<<",NumxJHUTotalwith0mu="<<NumxJHUTotalwith0mu<<endl;
  //cout<<"NumxJHUTotal="<<NumxJHUTotal<<", NumxJHUTotalwith4mu="<<NumxJHUTotalwith4mu<<",NumxJHUinsideLHCbFid="<<NumxJHUinsideLHCbFid<<", the totel effieicny in all phase psace region is:"<<myMuMuMuMumassV1mumubelowV1nolightmeson->GetEntries()/NumxJHUTotalwith4mu<<",NlowmassOS="<<NlowmassOS<<",NlowmassSS="<<NlowmassSS<<endl;

  myhbk->Write();
 
}
