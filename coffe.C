#define coffe_cxx
#include "coffe.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
////coffee for village dummies..


void coffe::Loop()
{
	if (fChain == 0) return;
	//float muonpdgmass=0.10565837; 
	float muonpdgmass=0.1057; 

	EventDumpFile.open("EventDump.txt");
	//EventDumpFile2.open("EventDump2.txt");
	EventDumpFile<< setw(10) << "#run"<<"\t"<< setw(10) << "#lumi "<<"\t"<< setw(10) <<"#evt"<<"\t"<< setw(10) << "DoubleJpsi"<<"\t"<< setw(10) << "4MuMass"<<"\n";
	//EventDumpFile2<<"#run"<<"\t"<<"lumiNum "<<"\t"<< "evtNo"<<"\t"<<"4MuMass"<<"\n";

	TH1F *hfourMuMass_aftercut_0p04 = new TH1F("hfourMuMass_aftercut_0p04","hfourMuMass_aftercut_0p04",75,6,9);
	hfourMuMass_aftercut_0p04->GetXaxis()->SetTitle("4 muon mass [GeV]");
	hfourMuMass_aftercut_0p04->GetYaxis()->SetTitle("Candidates / 0.04 GeV");
	hfourMuMass_aftercut_0p04->SetLineColor(kRed);



	Long64_t nentries = fChain->GetEntries();

	Long64_t nbytes = 0, nb = 0;
	
	for (Long64_t jentry=0; jentry<nentries;jentry++) 
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		if(jentry%1000==0) std::cout<<'\r'<<"Number of events:  "<<jentry<<" / "<<nentries<<std::endl;
		
		//for (unsigned i=0;i<MyFourMuonMass->size();++i) {
		for (unsigned i=0;i<My1234Mass->size();++i) {
			TLorentzVector mymup4,mu1,mu2,mu3,mu4,mu12,mu34;
		
		
		//	mu1.SetXYZM( (*muPx)[0], (*muPy)[0], (*muPz)[0], muonpdgmass);
		//	mu2.SetXYZM( (*muPx)[1], (*muPy)[1], (*muPz)[1], muonpdgmass);
		//	mu3.SetXYZM( (*muPx)[2], (*muPy)[2], (*muPz)[2], muonpdgmass);
		//	mu4.SetXYZM( (*muPx)[3], (*muPy)[3], (*muPz)[3], muonpdgmass);
		
		//if(!((*muIsGoodLooseMuon)[0]>0 && mu1.Pt()>=2.0 && fabs(mu1.Eta())<=2.4)) continue;
		//if(!((*muIsGoodLooseMuon)[1]>0 && mu2.Pt()>=2.0 && fabs(mu2.Eta())<=2.4)) continue;
		//if(!((*muIsGoodLooseMuon)[2]>0 && mu3.Pt()>=2.0 && fabs(mu3.Eta())<=2.4)) continue;
		//if(!((*muIsGoodLooseMuon)[3]>0 && mu4.Pt()>=2.0 && fabs(mu4.Eta())<=2.4)) continue;
		 
		


			mu1.SetXYZM(MyFourMuonMu1Px->at(i),MyFourMuonMu1Py->at(i),MyFourMuonMu1Pz->at(i), muonpdgmass); 
			mu2.SetXYZM(MyFourMuonMu2Px->at(i),MyFourMuonMu2Py->at(i),MyFourMuonMu2Pz->at(i), muonpdgmass);
			mu3.SetXYZM(MyFourMuonMu3Px->at(i),MyFourMuonMu3Py->at(i),MyFourMuonMu3Pz->at(i), muonpdgmass);
			mu4.SetXYZM(MyFourMuonMu4Px->at(i),MyFourMuonMu4Py->at(i),MyFourMuonMu4Pz->at(i), muonpdgmass);
			
			//if(!(muIsPatSoftMuon->at(0)+ muIsPatSoftMuon->at(1)+muIsPatSoftMuon->at(2)+muIsPatSoftMuon->at(3))) continue;
			//cout<<"muIsPatSoftMuon 3 == "<< muIsPatSoftMuon->at(3) << endl;

			if (mu1.Pt()<2 || mu2.Pt()<2 || mu3.Pt()<2 || mu4.Pt()<2) continue;
			//if (fabs(mu1.Eta())>2.4 ||fabs(mu2.Eta())>2.4 ||fabs(mu3.Eta())>2.4 ||fabs(mu4.Eta())>2.4) continue;

			/*if(!(MyFourMuonOverlap12->at(i)==0
						&& MyFourMuonOverlap13->at(i)==0
						&& MyFourMuonOverlap14->at(i)==0
						&& MyFourMuonOverlap23->at(i)==0
						&& MyFourMuonOverlap24->at(i)==0
						&& MyFourMuonOverlap34->at(i)==0
				 )) continue;
*/
				//EventDumpFile2<<runNum<<"\t"<<lumiNum<<"\t"<<evtNum<<"\t"<<MyFourMuonMass->at(i)<<"\n";
			
			
			float myEBEscale=1.16; //jpsi
			//float myEBEscale=1.105;//upsilon
			float mysigma=3.0;
			float phi_mass = 1.01946;
			float w_mass = 0.78265;
			float Y_2S_mass =3.6861;
			if (fabs(MyJpsi3Mass_Mu13->at(i)-phi_mass)< myEBEscale*mysigma*MyJpsi3MassErr_Mu13->at(i)) continue;
			if (fabs(MyJpsi4Mass_Mu24->at(i)-phi_mass)< myEBEscale*mysigma*MyJpsi4MassErr_Mu24->at(i)) continue;
			if (fabs(MyJpsi3Mass_Mu13->at(i)-w_mass)< myEBEscale*mysigma*MyJpsi3MassErr_Mu13->at(i)) continue;
			if (fabs(MyJpsi4Mass_Mu24->at(i)-w_mass)< myEBEscale*mysigma*MyJpsi4MassErr_Mu24->at(i)) continue;
			if (fabs(MyJpsi3Mass_Mu13->at(i)-Y_2S_mass)< myEBEscale*mysigma*MyJpsi3MassErr_Mu13->at(i)) continue;
			if (fabs(MyJpsi4Mass_Mu24->at(i)-Y_2S_mass)< myEBEscale*mysigma*MyJpsi4MassErr_Mu24->at(i)) continue;

			if (fabs(MyJpsi5Mass_Mu14->at(i)-phi_mass)< myEBEscale*mysigma*MyJpsi5MassErr_Mu14->at(i)) continue;
			if (fabs(MyJpsi6Mass_Mu23->at(i)-phi_mass)< myEBEscale*mysigma*MyJpsi6MassErr_Mu23->at(i)) continue;
			if (fabs(MyJpsi5Mass_Mu14->at(i)-w_mass)< myEBEscale*mysigma*MyJpsi5MassErr_Mu14->at(i)) continue;
			if (fabs(MyJpsi6Mass_Mu23->at(i)-w_mass)< myEBEscale*mysigma*MyJpsi6MassErr_Mu23->at(i)) continue;
			if (fabs(MyJpsi5Mass_Mu14->at(i)-Y_2S_mass)< myEBEscale*mysigma*MyJpsi5MassErr_Mu14->at(i)) continue;
			if (fabs(MyJpsi6Mass_Mu23->at(i)-Y_2S_mass)< myEBEscale*mysigma*MyJpsi6MassErr_Mu23->at(i)) continue;
			//cout <<" 1---  "  << MyJpsi3Mass_Mu13->at(i)-phi_mass << "  2 ----- " << mysigma*MyJpsi3MassErr_Mu13->at(i) <<endl;
		   
			//ama bunlardan supheliyim ben 
			if (MyFourMuonVtxCL->at(i)>0.01 && MyJpsi1ChiProb_Mu12->at(i)>0.001 && MyJpsi2ChiProb_Mu34->at(i)>0.001){
			//cout<< " MyFourMuonMass == "<<MyFourMuonMass->at(i)<<endl; 
			hfourMuMass_aftercut_0p04->Fill(My1234Mass->at(i));
			
			EventDumpFile<< setw(10) << runNum<<"\t"<< setw(10) <<lumiNum<<"\t"<< setw(10) << evtNum<<"\t"<< setw(10) << My1234Mass->at(i)<<"\t"<< setw(10) << MyFourMuonMass->at(i)<<"\n";
			}// vertex cut

		}//4muon mass loop
		
	}//event loop

	TCanvas *c4muon = new TCanvas("c4muon","c4muon");
    gStyle->SetEndErrorSize(3);
    gStyle->SetErrorX(1.);
	hfourMuMass_aftercut_0p04->Draw("E1");
	hfourMuMass_aftercut_0p04->SetMarkerStyle(20);
	c4muon->SaveAs("plots4muon/4muonMass.C");
	c4muon->SaveAs("plots4muon/4muonMass.pdf");

EventDumpFile.close();
//EventDumpFile2.close();
}

