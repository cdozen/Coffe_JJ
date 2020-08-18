#define coffe_cxx
#include "coffe.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>

void coffe::Loop()
{
	if (fChain == 0) return;
	const bool blind_signal = false;


	Long64_t nentries = fChain->GetEntries();

	Long64_t nbytes = 0, nb = 0;
	//for (Long64_t jentry=0; jentry<100000;jentry++) 
	for (Long64_t jentry=0; jentry<nentries;jentry++) 
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		if(jentry%1000==0) std::cout<<'\r'<<"Number of events:  "<<jentry<<" / "<<nentries<<std::endl;
		
		for (unsigned i=0;i<MyFourMuonMass->size();++i) {
			//if(!(muIsPatSoftMuon[0]+ muIsPatSoftMuon[1]+muIsPatSoftMuon[2]+muIsPatSoftMuon[3])) continue;
			cout<<"muIsPatSoftMuon 0 == "<< muIsPatSoftMuon->at(0) << endl;

			}//4muon mass loop
	}//event loop

}
