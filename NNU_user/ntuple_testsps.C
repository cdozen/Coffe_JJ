#include "myntuple.C"
void ntuple_testsps()
 {
	 //gSystem->Load("myntuple_C.so");
//	 TChain * chain = new TChain("X_data","");
       TChain * chain = new TChain("/mkcands/X_data","");

//the bove seems width is >20 MeV, it has the threshold effect there.
	chain->Add("mymultilep_SPS_test.root");



	 myntuple a(chain);
	 a.Loop("ntuple_testsps.root");

 }
