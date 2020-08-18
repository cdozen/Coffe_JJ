//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 31 09:19:23 2020 by ROOT version 6.21/01
// from TTree X_data/X(3872) Data
// found on file: mymultilep_SPS_test.root
//////////////////////////////////////////////////////////

#ifndef coffe_h
#define coffe_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"
#include "vector"
#include "vector"
#include <fstream>
#include <iostream>

using namespace std;


class coffe {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   ofstream EventDumpFile;
   ofstream EventDumpFile2;
   // Declaration of leaf types
   vector<unsigned int> *TrigRes;
   vector<string>  *TrigNames;
   vector<string>  *MatchTriggerNames;
   vector<unsigned int> *L1TrigRes;
   UInt_t          evtNum;
   UInt_t          runNum;
   UInt_t          lumiNum;
   UInt_t          nGoodPrimVtx;
   Float_t         mybxlumicorr;
   Float_t         myrawbxlumi;
   Float_t         priVtxX;
   Float_t         priVtxY;
   Float_t         priVtxZ;
   Float_t         priVtxXE;
   Float_t         priVtxYE;
   Float_t         priVtxZE;
   Float_t         priVtxChiNorm;
   Float_t         priVtxChi;
   Float_t         priVtxCL;
   vector<float>   *PriVtxXCorrX;
   vector<float>   *PriVtxXCorrY;
   vector<float>   *PriVtxXCorrZ;
   vector<double>  *PriVtxXCorrEX;
   vector<double>  *PriVtxXCorrEY;
   vector<double>  *PriVtxXCorrEZ;
   vector<float>   *PriVtxXCorrC2;
   vector<float>   *PriVtxXCorrCL;
   vector<float>   *gedphotonPt;
   vector<float>   *gedphotonEta;
   vector<float>   *gedphotonPhi;
   vector<float>   *gedphotonLoose;
   vector<float>   *gedphotonMedium;
   vector<float>   *gedphotonTight;
   vector<float>   *gedphotonhOverE;
   vector<int>     *gedphotonhasPixelSeed;
   vector<float>   *gedphotonfull5x5_sigmaIetaIeta;
   vector<float>   *gedphotonisoChargedHadrons;
   vector<float>   *gedphotonisoNeutralHadrons;
   vector<float>   *gedphotonisoPhotons;
   vector<float>   *gedphotonmvaValue;
   vector<int>     *gedphotonmvaCategory;
   vector<float>   *pfphotonPx;
   vector<float>   *pfphotonPy;
   vector<float>   *pfphotonPz;
   vector<float>   *pfphotonEnergy;
   vector<float>   *elePx;
   vector<float>   *elePy;
   vector<float>   *elePz;
   vector<float>   *eleE;
   vector<float>   *eleGsfTrkPt;
   vector<float>   *eleGsfTrkEta;
   vector<float>   *eleGsfTrkPhi;
   vector<float>   *eleTrkatVtxPt;
   vector<float>   *eleTrkatVtxEta;
   vector<float>   *eleTrkatVtxPhi;
   vector<float>   *eleCftTrkPt;
   vector<float>   *eleCftTrkEta;
   vector<float>   *eleCftTrkPhi;
   vector<int>     *eleNDF;
   vector<int>     *eleChi;
   vector<int>     *elePhits;
   vector<int>     *eleShits;
   vector<float>   *eleD0;
   vector<float>   *eleD0E;
   vector<float>   *eleZ0;
   vector<float>   *eleZ0E;
   vector<int>     *eleCharge;
   vector<int>     *eleIsTightEle;
   vector<int>     *eleIsLooseEle;
   vector<float>   *elemvaValue;
   vector<int>     *elemvaCategory;
   UInt_t          nMu;
   vector<float>   *muPx;
   vector<float>   *muPy;
   vector<float>   *muPz;
   vector<float>   *muD0;
   vector<float>   *muD0E;
   vector<float>   *muDz;
   vector<float>   *muChi2;
   vector<float>   *muGlChi2;
   vector<float>   *mufHits;
   vector<bool>    *muFirstBarrel;
   vector<bool>    *muFirstEndCap;
   vector<float>   *muDzVtx;
   vector<float>   *muDxyVtx;
   vector<int>     *muNDF;
   vector<int>     *muGlNDF;
   vector<int>     *muPhits;
   vector<int>     *muShits;
   vector<int>     *muGlMuHits;
   vector<int>     *muType;
   vector<int>     *muQual;
   vector<int>     *muTrack;
   vector<float>   *muCharge;
   vector<float>   *muIsoratio;
   vector<int>     *munMatchedSeg;
   vector<int>     *muIsGoodSoftMuonNewIlseMod;
   vector<int>     *muIsGoodSoftMuonNewIlse;
   vector<int>     *muIsGoodLooseMuonNew;
   vector<int>     *muIsGoodLooseMuon;
   vector<int>     *muIsGoodTightMuon;
   vector<int>     *muIsPatLooseMuon;
   vector<int>     *muIsPatTightMuon;
   vector<int>     *muIsPatSoftMuon;
   vector<int>     *muIsPatMediumMuon;
   vector<int>     *muIsJpsiTrigMatch;
   vector<int>     *muIsUpsTrigMatch;
   vector<float>   *muMVAMuonID;
   vector<float>   *musegmentCompatibility;
   vector<float>   *mupulldXdZ_pos_noArb;
   vector<float>   *mupulldYdZ_pos_noArb;
   vector<float>   *mupulldXdZ_pos_ArbDef;
   vector<float>   *mupulldYdZ_pos_ArbDef;
   vector<float>   *mupulldXdZ_pos_ArbST;
   vector<float>   *mupulldYdZ_pos_ArbST;
   vector<float>   *mupulldXdZ_pos_noArb_any;
   vector<float>   *mupulldYdZ_pos_noArb_any;
   vector<int>     *muUpsVrtxMatch;
   vector<int>     *muL3TriggerMatch;
   UInt_t          nMyFourMuon;
   vector<bool>    *MyFourMuonTrigMatch;
   vector<int>     *MyFourMuonChg;
   vector<float>   *MyFourMuonMass;
   vector<float>   *MyFourMuonMassErr;
   vector<float>   *MyFourMuonCTau;
   vector<float>   *MyFourMuonCTauErr;
   vector<int>     *MyHitBeforeVrtx;
   vector<int>     *MyMissAfterVrtx;
   vector<float>   *My1234Mass;
   vector<float>   *My1324Mass;
   vector<float>   *My1423Mass;
   vector<double>  *My1234JpsiDisXY;
   vector<double>  *My1324JpsiDisXY;
   vector<double>  *My1423JpsiDisXY;
   vector<double>  *My1234JpsiDisZ;
   vector<double>  *My1324JpsiDisZ;
   vector<double>  *My1423JpsiDisZ;
   vector<double>  *MyJpsi1CTau_Mu12;
   vector<double>  *MyJpsi1CTauErr_Mu12;
   vector<double>  *MyJpsi1ChiProb_Mu12;
   vector<int>     *MyJpsi1HitsBeforeMu12;
   vector<int>     *MyJpsi1MissAfterMu12;
   vector<double>  *MyJpsi2CTau_Mu34;
   vector<double>  *MyJpsi2CTauErr_Mu34;
   vector<double>  *MyJpsi2ChiProb_Mu34;
   vector<int>     *MyJpsi2HitsBeforeMu34;
   vector<int>     *MyJpsi2MissAfterMu34;
   vector<double>  *MyJpsi3CTau_Mu13;
   vector<double>  *MyJpsi3CTauErr_Mu13;
   vector<double>  *MyJpsi3ChiProb_Mu13;
   vector<int>     *MyJpsi3HitsBeforeMu13;
   vector<int>     *MyJpsi3MissAfterMu13;
   vector<double>  *MyJpsi4CTau_Mu24;
   vector<double>  *MyJpsi4CTauErr_Mu24;
   vector<double>  *MyJpsi4ChiProb_Mu24;
   vector<int>     *MyJpsi4HitsBeforeMu24;
   vector<int>     *MyJpsi4MissAfterMu24;
   vector<double>  *MyJpsi5CTau_Mu14;
   vector<double>  *MyJpsi5CTauErr_Mu14;
   vector<double>  *MyJpsi5ChiProb_Mu14;
   vector<int>     *MyJpsi5HitsBeforeMu14;
   vector<int>     *MyJpsi5MissAfterMu14;
   vector<double>  *MyJpsi6CTau_Mu23;
   vector<double>  *MyJpsi6CTauErr_Mu23;
   vector<double>  *MyJpsi6ChiProb_Mu23;
   vector<int>     *MyJpsi6HitsBeforeMu23;
   vector<int>     *MyJpsi6MissAfterMu23;
   vector<float>   *MyJpsi1Mass_Mu12;
   vector<float>   *MyJpsi1MassErr_Mu12;
   vector<float>   *MyJpsi2Mass_Mu34;
   vector<float>   *MyJpsi2MassErr_Mu34;
   vector<float>   *MyJpsi3Mass_Mu13;
   vector<float>   *MyJpsi3MassErr_Mu13;
   vector<float>   *MyJpsi4Mass_Mu24;
   vector<float>   *MyJpsi4MassErr_Mu24;
   vector<float>   *MyJpsi5Mass_Mu14;
   vector<float>   *MyJpsi5MassErr_Mu14;
   vector<float>   *MyJpsi6Mass_Mu23;
   vector<float>   *MyJpsi6MassErr_Mu23;
   vector<int>     *MyFourMuonOverlap12;
   vector<int>     *MyFourMuonOverlap13;
   vector<int>     *MyFourMuonOverlap14;
   vector<int>     *MyFourMuonOverlap23;
   vector<int>     *MyFourMuonOverlap24;
   vector<int>     *MyFourMuonOverlap34;
   vector<int>     *MyFourMuonSharedSeg12;
   vector<int>     *MyFourMuonSharedSeg13;
   vector<int>     *MyFourMuonSharedSeg14;
   vector<int>     *MyFourMuonSharedSeg23;
   vector<int>     *MyFourMuonSharedSeg24;
   vector<int>     *MyFourMuonSharedSeg34;
   vector<float>   *MyFourMuonVtxCL;
   vector<float>   *MyFourMuonVtxC2;
   vector<float>   *MyFourMuonPx;
   vector<float>   *MyFourMuonPy;
   vector<float>   *MyFourMuonPz;
   vector<float>   *MyFourMuonDecayVtxX;
   vector<float>   *MyFourMuonDecayVtxY;
   vector<float>   *MyFourMuonDecayVtxZ;
   vector<float>   *MyFourMuonDecayVtxXE;
   vector<float>   *MyFourMuonDecayVtxYE;
   vector<float>   *MyFourMuonDecayVtxZE;
   vector<int>     *MyFourMuonMu1Idx;
   vector<int>     *MyFourMuonMu2Idx;
   vector<float>   *MyFourMuonMu2Px;
   vector<float>   *MyFourMuonMu2Py;
   vector<float>   *MyFourMuonMu2Pz;
   vector<float>   *MyFourMuonMu1Px;
   vector<float>   *MyFourMuonMu1Py;
   vector<float>   *MyFourMuonMu1Pz;
   vector<float>   *MyFourMuonMu2fChi2;
   vector<int>     *MyFourMuonMu2fNDF;
   vector<float>   *MyFourMuonMu1fChi2;
   vector<int>     *MyFourMuonMu1fNDF;
   vector<float>   *MyFourMuoncosAlpha;
   vector<float>   *MyFourMuonFLSig;
   vector<float>   *MyFourMuonrVtxMag2D;
   vector<float>   *MyFourMuonsigmaRvtxMag2D;
   vector<float>   *MyFourMuonTrkIsoOverFourMuSumpt;
   vector<float>   *MyFourMuonTrkIsoOverFourMuVectpt;
   vector<int>     *MyFourMuonMu3fNDF;
   vector<int>     *MyFourMuonMu3Idx;
   vector<float>   *MyFourMuonMu3Px;
   vector<float>   *MyFourMuonMu3Py;
   vector<float>   *MyFourMuonMu3Pz;
   vector<float>   *MyFourMuonMu3fChi2;
   vector<int>     *MyFourMuonMu4fNDF;
   vector<int>     *MyFourMuonMu4Idx;
   vector<float>   *MyFourMuonMu4Px;
   vector<float>   *MyFourMuonMu4Py;
   vector<float>   *MyFourMuonMu4Pz;
   vector<float>   *MyFourMuonMu4fChi2;
   UInt_t          nmumuonly;
   vector<float>   *mumuonlyMass;
   vector<float>   *mumuonlyMassErr;
   vector<float>   *mumuonlyVtxCL;
   vector<float>   *mumuonlyPx;
   vector<float>   *mumuonlyPy;
   vector<float>   *mumuonlyPz;
   vector<float>   *mumuonlymu1Idx;
   vector<float>   *mumuonlymu2Idx;
   vector<float>   *mumuonlyctau;
   vector<float>   *mumuonlyctauerr;
   vector<int>     *mumuonlymuoverlapped;
   vector<int>     *mumuonlyChg;
   vector<int>     *mumuonlynsharedSeg;

   // List of branches
   TBranch        *b_TrigRes;   //!
   TBranch        *b_TrigNames;   //!
   TBranch        *b_MatchTriggerNames;   //!
   TBranch        *b_L1TrigRes;   //!
   TBranch        *b_evtNum;   //!
   TBranch        *b_runNum;   //!
   TBranch        *b_lumiNum;   //!
   TBranch        *b_nGoodPrimVtx;   //!
   TBranch        *b_mybxlumicorr;   //!
   TBranch        *b_myrawbxlumi;   //!
   TBranch        *b_priVtxX;   //!
   TBranch        *b_priVtxY;   //!
   TBranch        *b_priVtxZ;   //!
   TBranch        *b_priVtxXE;   //!
   TBranch        *b_priVtxYE;   //!
   TBranch        *b_priVtxZE;   //!
   TBranch        *b_priVtxChiNorm;   //!
   TBranch        *b_priVtxChi;   //!
   TBranch        *b_priVtxCL;   //!
   TBranch        *b_PriVtxXCorrX;   //!
   TBranch        *b_PriVtxXCorrY;   //!
   TBranch        *b_PriVtxXCorrZ;   //!
   TBranch        *b_PriVtxXCorrEX;   //!
   TBranch        *b_PriVtxXCorrEY;   //!
   TBranch        *b_PriVtxXCorrEZ;   //!
   TBranch        *b_PriVtxXCorrC2;   //!
   TBranch        *b_PriVtxXCorrCL;   //!
   TBranch        *b_gedphotonPt;   //!
   TBranch        *b_gedphotonEta;   //!
   TBranch        *b_gedphotonPhi;   //!
   TBranch        *b_gedphotonLoose;   //!
   TBranch        *b_gedphotonMedium;   //!
   TBranch        *b_gedphotonTight;   //!
   TBranch        *b_gedphotonhOverE;   //!
   TBranch        *b_gedphotonhasPixelSeed;   //!
   TBranch        *b_gedphotonfull5x5_sigmaIetaIeta;   //!
   TBranch        *b_gedphotonisoChargedHadrons;   //!
   TBranch        *b_gedphotonisoNeutralHadrons;   //!
   TBranch        *b_gedphotonisoPhotons;   //!
   TBranch        *b_gedphotonmvaValue;   //!
   TBranch        *b_gedphotonmvaCategory;   //!
   TBranch        *b_pfphotonPx;   //!
   TBranch        *b_pfphotonPy;   //!
   TBranch        *b_pfphotonPz;   //!
   TBranch        *b_pfphotonEnergy;   //!
   TBranch        *b_elePx;   //!
   TBranch        *b_elePy;   //!
   TBranch        *b_elePz;   //!
   TBranch        *b_eleE;   //!
   TBranch        *b_eleGsfTrkPt;   //!
   TBranch        *b_eleGsfTrkEta;   //!
   TBranch        *b_eleGsfTrkPhi;   //!
   TBranch        *b_eleTrkatVtxPt;   //!
   TBranch        *b_eleTrkatVtxEta;   //!
   TBranch        *b_eleTrkatVtxPhi;   //!
   TBranch        *b_eleCftTrkPt;   //!
   TBranch        *b_eleCftTrkEta;   //!
   TBranch        *b_eleCftTrkPhi;   //!
   TBranch        *b_eleNDF;   //!
   TBranch        *b_eleChi;   //!
   TBranch        *b_elePhits;   //!
   TBranch        *b_eleShits;   //!
   TBranch        *b_eleD0;   //!
   TBranch        *b_eleD0E;   //!
   TBranch        *b_eleZ0;   //!
   TBranch        *b_eleZ0E;   //!
   TBranch        *b_eleCharge;   //!
   TBranch        *b_eleIsTightEle;   //!
   TBranch        *b_eleIsLooseEle;   //!
   TBranch        *b_elemvaValue;   //!
   TBranch        *b_elemvaCategory;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_muPx;   //!
   TBranch        *b_muPy;   //!
   TBranch        *b_muPz;   //!
   TBranch        *b_muD0;   //!
   TBranch        *b_muD0E;   //!
   TBranch        *b_muDz;   //!
   TBranch        *b_muChi2;   //!
   TBranch        *b_muGlChi2;   //!
   TBranch        *b_mufHits;   //!
   TBranch        *b_muFirstBarrel;   //!
   TBranch        *b_muFirstEndCap;   //!
   TBranch        *b_muDzVtx;   //!
   TBranch        *b_muDxyVtx;   //!
   TBranch        *b_muNDF;   //!
   TBranch        *b_muGlNDF;   //!
   TBranch        *b_muPhits;   //!
   TBranch        *b_muShits;   //!
   TBranch        *b_muGlMuHits;   //!
   TBranch        *b_muType;   //!
   TBranch        *b_muQual;   //!
   TBranch        *b_muTrack;   //!
   TBranch        *b_muCharge;   //!
   TBranch        *b_muIsoratio;   //!
   TBranch        *b_munMatchedSeg;   //!
   TBranch        *b_muIsGoodSoftMuonNewIlseMod;   //!
   TBranch        *b_muIsGoodSoftMuonNewIlse;   //!
   TBranch        *b_muIsGoodLooseMuonNew;   //!
   TBranch        *b_muIsGoodLooseMuon;   //!
   TBranch        *b_muIsGoodTightMuon;   //!
   TBranch        *b_muIsPatLooseMuon;   //!
   TBranch        *b_muIsPatTightMuon;   //!
   TBranch        *b_muIsPatSoftMuon;   //!
   TBranch        *b_muIsPatMediumMuon;   //!
   TBranch        *b_muIsJpsiTrigMatch;   //!
   TBranch        *b_muIsUpsTrigMatch;   //!
   TBranch        *b_muMVAMuonID;   //!
   TBranch        *b_musegmentCompatibility;   //!
   TBranch        *b_mupulldXdZ_pos_noArb;   //!
   TBranch        *b_mupulldYdZ_pos_noArb;   //!
   TBranch        *b_mupulldXdZ_pos_ArbDef;   //!
   TBranch        *b_mupulldYdZ_pos_ArbDef;   //!
   TBranch        *b_mupulldXdZ_pos_ArbST;   //!
   TBranch        *b_mupulldYdZ_pos_ArbST;   //!
   TBranch        *b_mupulldXdZ_pos_noArb_any;   //!
   TBranch        *b_mupulldYdZ_pos_noArb_any;   //!
   TBranch        *b_muUpsVrtxMatch;   //!
   TBranch        *b_muL3TriggerMatch;   //!
   TBranch        *b_nMyFourMuon;   //!
   TBranch        *b_MyFourMuonTrigMatch;   //!
   TBranch        *b_MyFourMuonChg;   //!
   TBranch        *b_MyFourMuonMass;   //!
   TBranch        *b_MyFourMuonMassErr;   //!
   TBranch        *b_MyFourMuonCTau;   //!
   TBranch        *b_MyFourMuonCTauErr;   //!
   TBranch        *b_MyHitBeforeVrtx;   //!
   TBranch        *b_MyMissAfterVrtx;   //!
   TBranch        *b_My1234Mass;   //!
   TBranch        *b_My1324Mass;   //!
   TBranch        *b_My1423Mass;   //!
   TBranch        *b_My1234JpsiDisXY;   //!
   TBranch        *b_My1324JpsiDisXY;   //!
   TBranch        *b_My1423JpsiDisXY;   //!
   TBranch        *b_My1234JpsiDisZ;   //!
   TBranch        *b_My1324JpsiDisZ;   //!
   TBranch        *b_My1423JpsiDisZ;   //!
   TBranch        *b_MyJpsi1CTau_Mu12;   //!
   TBranch        *b_MyJpsi1CTauErr_Mu12;   //!
   TBranch        *b_MyJpsi1ChiProb_Mu12;   //!
   TBranch        *b_MyJpsi1HitsBeforeMu12;   //!
   TBranch        *b_MyJpsi1MissAfterMu12;   //!
   TBranch        *b_MyJpsi2CTau_Mu34;   //!
   TBranch        *b_MyJpsi2CTauErr_Mu34;   //!
   TBranch        *b_MyJpsi2ChiProb_Mu34;   //!
   TBranch        *b_MyJpsi2HitsBeforeMu34;   //!
   TBranch        *b_MyJpsi2MissAfterMu34;   //!
   TBranch        *b_MyJpsi3CTau_Mu13;   //!
   TBranch        *b_MyJpsi3CTauErr_Mu13;   //!
   TBranch        *b_MyJpsi3ChiProb_Mu13;   //!
   TBranch        *b_MyJpsi3HitsBeforeMu13;   //!
   TBranch        *b_MyJpsi3MissAfterMu13;   //!
   TBranch        *b_MyJpsi4CTau_Mu24;   //!
   TBranch        *b_MyJpsi4CTauErr_Mu24;   //!
   TBranch        *b_MyJpsi4ChiProb_Mu24;   //!
   TBranch        *b_MyJpsi4HitsBeforeMu24;   //!
   TBranch        *b_MyJpsi4MissAfterMu24;   //!
   TBranch        *b_MyJpsi5CTau_Mu14;   //!
   TBranch        *b_MyJpsi5CTauErr_Mu14;   //!
   TBranch        *b_MyJpsi5ChiProb_Mu14;   //!
   TBranch        *b_MyJpsi5HitsBeforeMu14;   //!
   TBranch        *b_MyJpsi5MissAfterMu14;   //!
   TBranch        *b_MyJpsi6CTau_Mu23;   //!
   TBranch        *b_MyJpsi6CTauErr_Mu23;   //!
   TBranch        *b_MyJpsi6ChiProb_Mu23;   //!
   TBranch        *b_MyJpsi6HitsBeforeMu23;   //!
   TBranch        *b_MyJpsi6MissAfterMu23;   //!
   TBranch        *b_MyJpsi1Mass_Mu12;   //!
   TBranch        *b_MyJpsi1MassErr_Mu12;   //!
   TBranch        *b_MyJpsi2Mass_Mu34;   //!
   TBranch        *b_MyJpsi2MassErr_Mu34;   //!
   TBranch        *b_MyJpsi3Mass_Mu13;   //!
   TBranch        *b_MyJpsi3MassErr_Mu13;   //!
   TBranch        *b_MyJpsi4Mass_Mu24;   //!
   TBranch        *b_MyJpsi4MassErr_Mu24;   //!
   TBranch        *b_MyJpsi5Mass_Mu14;   //!
   TBranch        *b_MyJpsi5MassErr_Mu14;   //!
   TBranch        *b_MyJpsi6Mass_Mu23;   //!
   TBranch        *b_MyJpsi6MassErr_Mu23;   //!
   TBranch        *b_MyFourMuonOverlap12;   //!
   TBranch        *b_MyFourMuonOverlap13;   //!
   TBranch        *b_MyFourMuonOverlap14;   //!
   TBranch        *b_MyFourMuonOverlap23;   //!
   TBranch        *b_MyFourMuonOverlap24;   //!
   TBranch        *b_MyFourMuonOverlap34;   //!
   TBranch        *b_MyFourMuonSharedSeg12;   //!
   TBranch        *b_MyFourMuonSharedSeg13;   //!
   TBranch        *b_MyFourMuonSharedSeg14;   //!
   TBranch        *b_MyFourMuonSharedSeg23;   //!
   TBranch        *b_MyFourMuonSharedSeg24;   //!
   TBranch        *b_MyFourMuonSharedSeg34;   //!
   TBranch        *b_MyFourMuonVtxCL;   //!
   TBranch        *b_MyFourMuonVtxC2;   //!
   TBranch        *b_MyFourMuonPx;   //!
   TBranch        *b_MyFourMuonPy;   //!
   TBranch        *b_MyFourMuonPz;   //!
   TBranch        *b_MyFourMuonDecayVtxX;   //!
   TBranch        *b_MyFourMuonDecayVtxY;   //!
   TBranch        *b_MyFourMuonDecayVtxZ;   //!
   TBranch        *b_MyFourMuonDecayVtxXE;   //!
   TBranch        *b_MyFourMuonDecayVtxYE;   //!
   TBranch        *b_MyFourMuonDecayVtxZE;   //!
   TBranch        *b_MyFourMuonMu1Idx;   //!
   TBranch        *b_MyFourMuonMu2Idx;   //!
   TBranch        *b_MyFourMuonMu2Px;   //!
   TBranch        *b_MyFourMuonMu2Py;   //!
   TBranch        *b_MyFourMuonMu2Pz;   //!
   TBranch        *b_MyFourMuonMu1Px;   //!
   TBranch        *b_MyFourMuonMu1Py;   //!
   TBranch        *b_MyFourMuonMu1Pz;   //!
   TBranch        *b_MyFourMuonMu2fChi2;   //!
   TBranch        *b_MyFourMuonMu2fNDF;   //!
   TBranch        *b_MyFourMuonMu1fChi2;   //!
   TBranch        *b_MyFourMuonMu1fNDF;   //!
   TBranch        *b_MyFourMuoncosAlpha;   //!
   TBranch        *b_MyFourMuonFLSig;   //!
   TBranch        *b_MyFourMuonrVtxMag2D;   //!
   TBranch        *b_MyFourMuonsigmaRvtxMag2D;   //!
   TBranch        *b_MyFourMuonTrkIsoOverFourMuSumpt;   //!
   TBranch        *b_MyFourMuonTrkIsoOverFourMuVectpt;   //!
   TBranch        *b_MyFourMuonMu3fNDF;   //!
   TBranch        *b_MyFourMuonMu3Idx;   //!
   TBranch        *b_MyFourMuonMu3Px;   //!
   TBranch        *b_MyFourMuonMu3Py;   //!
   TBranch        *b_MyFourMuonMu3Pz;   //!
   TBranch        *b_MyFourMuonMu3fChi2;   //!
   TBranch        *b_MyFourMuonMu4fNDF;   //!
   TBranch        *b_MyFourMuonMu4Idx;   //!
   TBranch        *b_MyFourMuonMu4Px;   //!
   TBranch        *b_MyFourMuonMu4Py;   //!
   TBranch        *b_MyFourMuonMu4Pz;   //!
   TBranch        *b_MyFourMuonMu4fChi2;   //!
   TBranch        *b_nmumuonly;   //!
   TBranch        *b_mumuonlyMass;   //!
   TBranch        *b_mumuonlyMassErr;   //!
   TBranch        *b_mumuonlyVtxCL;   //!
   TBranch        *b_mumuonlyPx;   //!
   TBranch        *b_mumuonlyPy;   //!
   TBranch        *b_mumuonlyPz;   //!
   TBranch        *b_mumuonlymu1Idx;   //!
   TBranch        *b_mumuonlymu2Idx;   //!
   TBranch        *b_mumuonlyctau;   //!
   TBranch        *b_mumuonlyctauerr;   //!
   TBranch        *b_mumuonlymuoverlapped;   //!
   TBranch        *b_mumuonlyChg;   //!
   TBranch        *b_mumuonlynsharedSeg;   //!

   coffe(TTree *tree=0);
   virtual ~coffe();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef coffe_cxx
coffe::coffe(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("mymultilep_SPS_test.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("mymultilep_SPS_test.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("mymultilep_SPS_test.root:/mkcands");
      //TDirectory * dir = (TDirectory*)f->Get("../../Downloads/ntuple_testsps.root:/mkcands");
      dir->GetObject("X_data",tree);

   }
   Init(tree);
}

coffe::~coffe()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t coffe::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t coffe::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void coffe::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   TrigRes = 0;
   TrigNames = 0;
   MatchTriggerNames = 0;
   L1TrigRes = 0;
   PriVtxXCorrX = 0;
   PriVtxXCorrY = 0;
   PriVtxXCorrZ = 0;
   PriVtxXCorrEX = 0;
   PriVtxXCorrEY = 0;
   PriVtxXCorrEZ = 0;
   PriVtxXCorrC2 = 0;
   PriVtxXCorrCL = 0;
   gedphotonPt = 0;
   gedphotonEta = 0;
   gedphotonPhi = 0;
   gedphotonLoose = 0;
   gedphotonMedium = 0;
   gedphotonTight = 0;
   gedphotonhOverE = 0;
   gedphotonhasPixelSeed = 0;
   gedphotonfull5x5_sigmaIetaIeta = 0;
   gedphotonisoChargedHadrons = 0;
   gedphotonisoNeutralHadrons = 0;
   gedphotonisoPhotons = 0;
   gedphotonmvaValue = 0;
   gedphotonmvaCategory = 0;
   pfphotonPx = 0;
   pfphotonPy = 0;
   pfphotonPz = 0;
   pfphotonEnergy = 0;
   elePx = 0;
   elePy = 0;
   elePz = 0;
   eleE = 0;
   eleGsfTrkPt = 0;
   eleGsfTrkEta = 0;
   eleGsfTrkPhi = 0;
   eleTrkatVtxPt = 0;
   eleTrkatVtxEta = 0;
   eleTrkatVtxPhi = 0;
   eleCftTrkPt = 0;
   eleCftTrkEta = 0;
   eleCftTrkPhi = 0;
   eleNDF = 0;
   eleChi = 0;
   elePhits = 0;
   eleShits = 0;
   eleD0 = 0;
   eleD0E = 0;
   eleZ0 = 0;
   eleZ0E = 0;
   eleCharge = 0;
   eleIsTightEle = 0;
   eleIsLooseEle = 0;
   elemvaValue = 0;
   elemvaCategory = 0;
   muPx = 0;
   muPy = 0;
   muPz = 0;
   muD0 = 0;
   muD0E = 0;
   muDz = 0;
   muChi2 = 0;
   muGlChi2 = 0;
   mufHits = 0;
   muFirstBarrel = 0;
   muFirstEndCap = 0;
   muDzVtx = 0;
   muDxyVtx = 0;
   muNDF = 0;
   muGlNDF = 0;
   muPhits = 0;
   muShits = 0;
   muGlMuHits = 0;
   muType = 0;
   muQual = 0;
   muTrack = 0;
   muCharge = 0;
   muIsoratio = 0;
   munMatchedSeg = 0;
   muIsGoodSoftMuonNewIlseMod = 0;
   muIsGoodSoftMuonNewIlse = 0;
   muIsGoodLooseMuonNew = 0;
   muIsGoodLooseMuon = 0;
   muIsGoodTightMuon = 0;
   muIsPatLooseMuon = 0;
   muIsPatTightMuon = 0;
   muIsPatSoftMuon = 0;
   muIsPatMediumMuon = 0;
   muIsJpsiTrigMatch = 0;
   muIsUpsTrigMatch = 0;
   muMVAMuonID = 0;
   musegmentCompatibility = 0;
   mupulldXdZ_pos_noArb = 0;
   mupulldYdZ_pos_noArb = 0;
   mupulldXdZ_pos_ArbDef = 0;
   mupulldYdZ_pos_ArbDef = 0;
   mupulldXdZ_pos_ArbST = 0;
   mupulldYdZ_pos_ArbST = 0;
   mupulldXdZ_pos_noArb_any = 0;
   mupulldYdZ_pos_noArb_any = 0;
   muUpsVrtxMatch = 0;
   muL3TriggerMatch = 0;
   MyFourMuonTrigMatch = 0;
   MyFourMuonChg = 0;
   MyFourMuonMass = 0;
   MyFourMuonMassErr = 0;
   MyFourMuonCTau = 0;
   MyFourMuonCTauErr = 0;
   MyHitBeforeVrtx = 0;
   MyMissAfterVrtx = 0;
   My1234Mass = 0;
   My1324Mass = 0;
   My1423Mass = 0;
   My1234JpsiDisXY = 0;
   My1324JpsiDisXY = 0;
   My1423JpsiDisXY = 0;
   My1234JpsiDisZ = 0;
   My1324JpsiDisZ = 0;
   My1423JpsiDisZ = 0;
   MyJpsi1CTau_Mu12 = 0;
   MyJpsi1CTauErr_Mu12 = 0;
   MyJpsi1ChiProb_Mu12 = 0;
   MyJpsi1HitsBeforeMu12 = 0;
   MyJpsi1MissAfterMu12 = 0;
   MyJpsi2CTau_Mu34 = 0;
   MyJpsi2CTauErr_Mu34 = 0;
   MyJpsi2ChiProb_Mu34 = 0;
   MyJpsi2HitsBeforeMu34 = 0;
   MyJpsi2MissAfterMu34 = 0;
   MyJpsi3CTau_Mu13 = 0;
   MyJpsi3CTauErr_Mu13 = 0;
   MyJpsi3ChiProb_Mu13 = 0;
   MyJpsi3HitsBeforeMu13 = 0;
   MyJpsi3MissAfterMu13 = 0;
   MyJpsi4CTau_Mu24 = 0;
   MyJpsi4CTauErr_Mu24 = 0;
   MyJpsi4ChiProb_Mu24 = 0;
   MyJpsi4HitsBeforeMu24 = 0;
   MyJpsi4MissAfterMu24 = 0;
   MyJpsi5CTau_Mu14 = 0;
   MyJpsi5CTauErr_Mu14 = 0;
   MyJpsi5ChiProb_Mu14 = 0;
   MyJpsi5HitsBeforeMu14 = 0;
   MyJpsi5MissAfterMu14 = 0;
   MyJpsi6CTau_Mu23 = 0;
   MyJpsi6CTauErr_Mu23 = 0;
   MyJpsi6ChiProb_Mu23 = 0;
   MyJpsi6HitsBeforeMu23 = 0;
   MyJpsi6MissAfterMu23 = 0;
   MyJpsi1Mass_Mu12 = 0;
   MyJpsi1MassErr_Mu12 = 0;
   MyJpsi2Mass_Mu34 = 0;
   MyJpsi2MassErr_Mu34 = 0;
   MyJpsi3Mass_Mu13 = 0;
   MyJpsi3MassErr_Mu13 = 0;
   MyJpsi4Mass_Mu24 = 0;
   MyJpsi4MassErr_Mu24 = 0;
   MyJpsi5Mass_Mu14 = 0;
   MyJpsi5MassErr_Mu14 = 0;
   MyJpsi6Mass_Mu23 = 0;
   MyJpsi6MassErr_Mu23 = 0;
   MyFourMuonOverlap12 = 0;
   MyFourMuonOverlap13 = 0;
   MyFourMuonOverlap14 = 0;
   MyFourMuonOverlap23 = 0;
   MyFourMuonOverlap24 = 0;
   MyFourMuonOverlap34 = 0;
   MyFourMuonSharedSeg12 = 0;
   MyFourMuonSharedSeg13 = 0;
   MyFourMuonSharedSeg14 = 0;
   MyFourMuonSharedSeg23 = 0;
   MyFourMuonSharedSeg24 = 0;
   MyFourMuonSharedSeg34 = 0;
   MyFourMuonVtxCL = 0;
   MyFourMuonVtxC2 = 0;
   MyFourMuonPx = 0;
   MyFourMuonPy = 0;
   MyFourMuonPz = 0;
   MyFourMuonDecayVtxX = 0;
   MyFourMuonDecayVtxY = 0;
   MyFourMuonDecayVtxZ = 0;
   MyFourMuonDecayVtxXE = 0;
   MyFourMuonDecayVtxYE = 0;
   MyFourMuonDecayVtxZE = 0;
   MyFourMuonMu1Idx = 0;
   MyFourMuonMu2Idx = 0;
   MyFourMuonMu2Px = 0;
   MyFourMuonMu2Py = 0;
   MyFourMuonMu2Pz = 0;
   MyFourMuonMu1Px = 0;
   MyFourMuonMu1Py = 0;
   MyFourMuonMu1Pz = 0;
   MyFourMuonMu2fChi2 = 0;
   MyFourMuonMu2fNDF = 0;
   MyFourMuonMu1fChi2 = 0;
   MyFourMuonMu1fNDF = 0;
   MyFourMuoncosAlpha = 0;
   MyFourMuonFLSig = 0;
   MyFourMuonrVtxMag2D = 0;
   MyFourMuonsigmaRvtxMag2D = 0;
   MyFourMuonTrkIsoOverFourMuSumpt = 0;
   MyFourMuonTrkIsoOverFourMuVectpt = 0;
   MyFourMuonMu3fNDF = 0;
   MyFourMuonMu3Idx = 0;
   MyFourMuonMu3Px = 0;
   MyFourMuonMu3Py = 0;
   MyFourMuonMu3Pz = 0;
   MyFourMuonMu3fChi2 = 0;
   MyFourMuonMu4fNDF = 0;
   MyFourMuonMu4Idx = 0;
   MyFourMuonMu4Px = 0;
   MyFourMuonMu4Py = 0;
   MyFourMuonMu4Pz = 0;
   MyFourMuonMu4fChi2 = 0;
   mumuonlyMass = 0;
   mumuonlyMassErr = 0;
   mumuonlyVtxCL = 0;
   mumuonlyPx = 0;
   mumuonlyPy = 0;
   mumuonlyPz = 0;
   mumuonlymu1Idx = 0;
   mumuonlymu2Idx = 0;
   mumuonlyctau = 0;
   mumuonlyctauerr = 0;
   mumuonlymuoverlapped = 0;
   mumuonlyChg = 0;
   mumuonlynsharedSeg = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("TrigRes", &TrigRes, &b_TrigRes);
   fChain->SetBranchAddress("TrigNames", &TrigNames, &b_TrigNames);
   fChain->SetBranchAddress("MatchTriggerNames", &MatchTriggerNames, &b_MatchTriggerNames);
   fChain->SetBranchAddress("L1TrigRes", &L1TrigRes, &b_L1TrigRes);
   fChain->SetBranchAddress("evtNum", &evtNum, &b_evtNum);
   fChain->SetBranchAddress("runNum", &runNum, &b_runNum);
   fChain->SetBranchAddress("lumiNum", &lumiNum, &b_lumiNum);
   fChain->SetBranchAddress("nGoodPrimVtx", &nGoodPrimVtx, &b_nGoodPrimVtx);
   fChain->SetBranchAddress("mybxlumicorr", &mybxlumicorr, &b_mybxlumicorr);
   fChain->SetBranchAddress("myrawbxlumi", &myrawbxlumi, &b_myrawbxlumi);
   fChain->SetBranchAddress("priVtxX", &priVtxX, &b_priVtxX);
   fChain->SetBranchAddress("priVtxY", &priVtxY, &b_priVtxY);
   fChain->SetBranchAddress("priVtxZ", &priVtxZ, &b_priVtxZ);
   fChain->SetBranchAddress("priVtxXE", &priVtxXE, &b_priVtxXE);
   fChain->SetBranchAddress("priVtxYE", &priVtxYE, &b_priVtxYE);
   fChain->SetBranchAddress("priVtxZE", &priVtxZE, &b_priVtxZE);
   fChain->SetBranchAddress("priVtxChiNorm", &priVtxChiNorm, &b_priVtxChiNorm);
   fChain->SetBranchAddress("priVtxChi", &priVtxChi, &b_priVtxChi);
   fChain->SetBranchAddress("priVtxCL", &priVtxCL, &b_priVtxCL);
   fChain->SetBranchAddress("PriVtxXCorrX", &PriVtxXCorrX, &b_PriVtxXCorrX);
   fChain->SetBranchAddress("PriVtxXCorrY", &PriVtxXCorrY, &b_PriVtxXCorrY);
   fChain->SetBranchAddress("PriVtxXCorrZ", &PriVtxXCorrZ, &b_PriVtxXCorrZ);
   fChain->SetBranchAddress("PriVtxXCorrEX", &PriVtxXCorrEX, &b_PriVtxXCorrEX);
   fChain->SetBranchAddress("PriVtxXCorrEY", &PriVtxXCorrEY, &b_PriVtxXCorrEY);
   fChain->SetBranchAddress("PriVtxXCorrEZ", &PriVtxXCorrEZ, &b_PriVtxXCorrEZ);
   fChain->SetBranchAddress("PriVtxXCorrC2", &PriVtxXCorrC2, &b_PriVtxXCorrC2);
   fChain->SetBranchAddress("PriVtxXCorrCL", &PriVtxXCorrCL, &b_PriVtxXCorrCL);
   fChain->SetBranchAddress("gedphotonPt", &gedphotonPt, &b_gedphotonPt);
   fChain->SetBranchAddress("gedphotonEta", &gedphotonEta, &b_gedphotonEta);
   fChain->SetBranchAddress("gedphotonPhi", &gedphotonPhi, &b_gedphotonPhi);
   fChain->SetBranchAddress("gedphotonLoose", &gedphotonLoose, &b_gedphotonLoose);
   fChain->SetBranchAddress("gedphotonMedium", &gedphotonMedium, &b_gedphotonMedium);
   fChain->SetBranchAddress("gedphotonTight", &gedphotonTight, &b_gedphotonTight);
   fChain->SetBranchAddress("gedphotonhOverE", &gedphotonhOverE, &b_gedphotonhOverE);
   fChain->SetBranchAddress("gedphotonhasPixelSeed", &gedphotonhasPixelSeed, &b_gedphotonhasPixelSeed);
   fChain->SetBranchAddress("gedphotonfull5x5_sigmaIetaIeta", &gedphotonfull5x5_sigmaIetaIeta, &b_gedphotonfull5x5_sigmaIetaIeta);
   fChain->SetBranchAddress("gedphotonisoChargedHadrons", &gedphotonisoChargedHadrons, &b_gedphotonisoChargedHadrons);
   fChain->SetBranchAddress("gedphotonisoNeutralHadrons", &gedphotonisoNeutralHadrons, &b_gedphotonisoNeutralHadrons);
   fChain->SetBranchAddress("gedphotonisoPhotons", &gedphotonisoPhotons, &b_gedphotonisoPhotons);
   fChain->SetBranchAddress("gedphotonmvaValue", &gedphotonmvaValue, &b_gedphotonmvaValue);
   fChain->SetBranchAddress("gedphotonmvaCategory", &gedphotonmvaCategory, &b_gedphotonmvaCategory);
   fChain->SetBranchAddress("pfphotonPx", &pfphotonPx, &b_pfphotonPx);
   fChain->SetBranchAddress("pfphotonPy", &pfphotonPy, &b_pfphotonPy);
   fChain->SetBranchAddress("pfphotonPz", &pfphotonPz, &b_pfphotonPz);
   fChain->SetBranchAddress("pfphotonEnergy", &pfphotonEnergy, &b_pfphotonEnergy);
   fChain->SetBranchAddress("elePx", &elePx, &b_elePx);
   fChain->SetBranchAddress("elePy", &elePy, &b_elePy);
   fChain->SetBranchAddress("elePz", &elePz, &b_elePz);
   fChain->SetBranchAddress("eleE", &eleE, &b_eleE);
   fChain->SetBranchAddress("eleGsfTrkPt", &eleGsfTrkPt, &b_eleGsfTrkPt);
   fChain->SetBranchAddress("eleGsfTrkEta", &eleGsfTrkEta, &b_eleGsfTrkEta);
   fChain->SetBranchAddress("eleGsfTrkPhi", &eleGsfTrkPhi, &b_eleGsfTrkPhi);
   fChain->SetBranchAddress("eleTrkatVtxPt", &eleTrkatVtxPt, &b_eleTrkatVtxPt);
   fChain->SetBranchAddress("eleTrkatVtxEta", &eleTrkatVtxEta, &b_eleTrkatVtxEta);
   fChain->SetBranchAddress("eleTrkatVtxPhi", &eleTrkatVtxPhi, &b_eleTrkatVtxPhi);
   fChain->SetBranchAddress("eleCftTrkPt", &eleCftTrkPt, &b_eleCftTrkPt);
   fChain->SetBranchAddress("eleCftTrkEta", &eleCftTrkEta, &b_eleCftTrkEta);
   fChain->SetBranchAddress("eleCftTrkPhi", &eleCftTrkPhi, &b_eleCftTrkPhi);
   fChain->SetBranchAddress("eleNDF", &eleNDF, &b_eleNDF);
   fChain->SetBranchAddress("eleChi", &eleChi, &b_eleChi);
   fChain->SetBranchAddress("elePhits", &elePhits, &b_elePhits);
   fChain->SetBranchAddress("eleShits", &eleShits, &b_eleShits);
   fChain->SetBranchAddress("eleD0", &eleD0, &b_eleD0);
   fChain->SetBranchAddress("eleD0E", &eleD0E, &b_eleD0E);
   fChain->SetBranchAddress("eleZ0", &eleZ0, &b_eleZ0);
   fChain->SetBranchAddress("eleZ0E", &eleZ0E, &b_eleZ0E);
   fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
   fChain->SetBranchAddress("eleIsTightEle", &eleIsTightEle, &b_eleIsTightEle);
   fChain->SetBranchAddress("eleIsLooseEle", &eleIsLooseEle, &b_eleIsLooseEle);
   fChain->SetBranchAddress("elemvaValue", &elemvaValue, &b_elemvaValue);
   fChain->SetBranchAddress("elemvaCategory", &elemvaCategory, &b_elemvaCategory);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("muPx", &muPx, &b_muPx);
   fChain->SetBranchAddress("muPy", &muPy, &b_muPy);
   fChain->SetBranchAddress("muPz", &muPz, &b_muPz);
   fChain->SetBranchAddress("muD0", &muD0, &b_muD0);
   fChain->SetBranchAddress("muD0E", &muD0E, &b_muD0E);
   fChain->SetBranchAddress("muDz", &muDz, &b_muDz);
   fChain->SetBranchAddress("muChi2", &muChi2, &b_muChi2);
   fChain->SetBranchAddress("muGlChi2", &muGlChi2, &b_muGlChi2);
   fChain->SetBranchAddress("mufHits", &mufHits, &b_mufHits);
   fChain->SetBranchAddress("muFirstBarrel", &muFirstBarrel, &b_muFirstBarrel);
   fChain->SetBranchAddress("muFirstEndCap", &muFirstEndCap, &b_muFirstEndCap);
   fChain->SetBranchAddress("muDzVtx", &muDzVtx, &b_muDzVtx);
   fChain->SetBranchAddress("muDxyVtx", &muDxyVtx, &b_muDxyVtx);
   fChain->SetBranchAddress("muNDF", &muNDF, &b_muNDF);
   fChain->SetBranchAddress("muGlNDF", &muGlNDF, &b_muGlNDF);
   fChain->SetBranchAddress("muPhits", &muPhits, &b_muPhits);
   fChain->SetBranchAddress("muShits", &muShits, &b_muShits);
   fChain->SetBranchAddress("muGlMuHits", &muGlMuHits, &b_muGlMuHits);
   fChain->SetBranchAddress("muType", &muType, &b_muType);
   fChain->SetBranchAddress("muQual", &muQual, &b_muQual);
   fChain->SetBranchAddress("muTrack", &muTrack, &b_muTrack);
   fChain->SetBranchAddress("muCharge", &muCharge, &b_muCharge);
   fChain->SetBranchAddress("muIsoratio", &muIsoratio, &b_muIsoratio);
   fChain->SetBranchAddress("munMatchedSeg", &munMatchedSeg, &b_munMatchedSeg);
   fChain->SetBranchAddress("muIsGoodSoftMuonNewIlseMod", &muIsGoodSoftMuonNewIlseMod, &b_muIsGoodSoftMuonNewIlseMod);
   fChain->SetBranchAddress("muIsGoodSoftMuonNewIlse", &muIsGoodSoftMuonNewIlse, &b_muIsGoodSoftMuonNewIlse);
   fChain->SetBranchAddress("muIsGoodLooseMuonNew", &muIsGoodLooseMuonNew, &b_muIsGoodLooseMuonNew);
   fChain->SetBranchAddress("muIsGoodLooseMuon", &muIsGoodLooseMuon, &b_muIsGoodLooseMuon);
   fChain->SetBranchAddress("muIsGoodTightMuon", &muIsGoodTightMuon, &b_muIsGoodTightMuon);
   fChain->SetBranchAddress("muIsPatLooseMuon", &muIsPatLooseMuon, &b_muIsPatLooseMuon);
   fChain->SetBranchAddress("muIsPatTightMuon", &muIsPatTightMuon, &b_muIsPatTightMuon);
   fChain->SetBranchAddress("muIsPatSoftMuon", &muIsPatSoftMuon, &b_muIsPatSoftMuon);
   fChain->SetBranchAddress("muIsPatMediumMuon", &muIsPatMediumMuon, &b_muIsPatMediumMuon);
   fChain->SetBranchAddress("muIsJpsiTrigMatch", &muIsJpsiTrigMatch, &b_muIsJpsiTrigMatch);
   fChain->SetBranchAddress("muIsUpsTrigMatch", &muIsUpsTrigMatch, &b_muIsUpsTrigMatch);
   fChain->SetBranchAddress("muMVAMuonID", &muMVAMuonID, &b_muMVAMuonID);
   fChain->SetBranchAddress("musegmentCompatibility", &musegmentCompatibility, &b_musegmentCompatibility);
   fChain->SetBranchAddress("mupulldXdZ_pos_noArb", &mupulldXdZ_pos_noArb, &b_mupulldXdZ_pos_noArb);
   fChain->SetBranchAddress("mupulldYdZ_pos_noArb", &mupulldYdZ_pos_noArb, &b_mupulldYdZ_pos_noArb);
   fChain->SetBranchAddress("mupulldXdZ_pos_ArbDef", &mupulldXdZ_pos_ArbDef, &b_mupulldXdZ_pos_ArbDef);
   fChain->SetBranchAddress("mupulldYdZ_pos_ArbDef", &mupulldYdZ_pos_ArbDef, &b_mupulldYdZ_pos_ArbDef);
   fChain->SetBranchAddress("mupulldXdZ_pos_ArbST", &mupulldXdZ_pos_ArbST, &b_mupulldXdZ_pos_ArbST);
   fChain->SetBranchAddress("mupulldYdZ_pos_ArbST", &mupulldYdZ_pos_ArbST, &b_mupulldYdZ_pos_ArbST);
   fChain->SetBranchAddress("mupulldXdZ_pos_noArb_any", &mupulldXdZ_pos_noArb_any, &b_mupulldXdZ_pos_noArb_any);
   fChain->SetBranchAddress("mupulldYdZ_pos_noArb_any", &mupulldYdZ_pos_noArb_any, &b_mupulldYdZ_pos_noArb_any);
   fChain->SetBranchAddress("muUpsVrtxMatch", &muUpsVrtxMatch, &b_muUpsVrtxMatch);
   fChain->SetBranchAddress("muL3TriggerMatch", &muL3TriggerMatch, &b_muL3TriggerMatch);
   fChain->SetBranchAddress("nMyFourMuon", &nMyFourMuon, &b_nMyFourMuon);
   fChain->SetBranchAddress("MyFourMuonTrigMatch", &MyFourMuonTrigMatch, &b_MyFourMuonTrigMatch);
   fChain->SetBranchAddress("MyFourMuonChg", &MyFourMuonChg, &b_MyFourMuonChg);
   fChain->SetBranchAddress("MyFourMuonMass", &MyFourMuonMass, &b_MyFourMuonMass);
   fChain->SetBranchAddress("MyFourMuonMassErr", &MyFourMuonMassErr, &b_MyFourMuonMassErr);
   fChain->SetBranchAddress("MyFourMuonCTau", &MyFourMuonCTau, &b_MyFourMuonCTau);
   fChain->SetBranchAddress("MyFourMuonCTauErr", &MyFourMuonCTauErr, &b_MyFourMuonCTauErr);
   fChain->SetBranchAddress("MyHitBeforeVrtx", &MyHitBeforeVrtx, &b_MyHitBeforeVrtx);
   fChain->SetBranchAddress("MyMissAfterVrtx", &MyMissAfterVrtx, &b_MyMissAfterVrtx);
   fChain->SetBranchAddress("My1234Mass", &My1234Mass, &b_My1234Mass);
   fChain->SetBranchAddress("My1324Mass", &My1324Mass, &b_My1324Mass);
   fChain->SetBranchAddress("My1423Mass", &My1423Mass, &b_My1423Mass);
   fChain->SetBranchAddress("My1234JpsiDisXY", &My1234JpsiDisXY, &b_My1234JpsiDisXY);
   fChain->SetBranchAddress("My1324JpsiDisXY", &My1324JpsiDisXY, &b_My1324JpsiDisXY);
   fChain->SetBranchAddress("My1423JpsiDisXY", &My1423JpsiDisXY, &b_My1423JpsiDisXY);
   fChain->SetBranchAddress("My1234JpsiDisZ", &My1234JpsiDisZ, &b_My1234JpsiDisZ);
   fChain->SetBranchAddress("My1324JpsiDisZ", &My1324JpsiDisZ, &b_My1324JpsiDisZ);
   fChain->SetBranchAddress("My1423JpsiDisZ", &My1423JpsiDisZ, &b_My1423JpsiDisZ);
   fChain->SetBranchAddress("MyJpsi1CTau_Mu12", &MyJpsi1CTau_Mu12, &b_MyJpsi1CTau_Mu12);
   fChain->SetBranchAddress("MyJpsi1CTauErr_Mu12", &MyJpsi1CTauErr_Mu12, &b_MyJpsi1CTauErr_Mu12);
   fChain->SetBranchAddress("MyJpsi1ChiProb_Mu12", &MyJpsi1ChiProb_Mu12, &b_MyJpsi1ChiProb_Mu12);
   fChain->SetBranchAddress("MyJpsi1HitsBeforeMu12", &MyJpsi1HitsBeforeMu12, &b_MyJpsi1HitsBeforeMu12);
   fChain->SetBranchAddress("MyJpsi1MissAfterMu12", &MyJpsi1MissAfterMu12, &b_MyJpsi1MissAfterMu12);
   fChain->SetBranchAddress("MyJpsi2CTau_Mu34", &MyJpsi2CTau_Mu34, &b_MyJpsi2CTau_Mu34);
   fChain->SetBranchAddress("MyJpsi2CTauErr_Mu34", &MyJpsi2CTauErr_Mu34, &b_MyJpsi2CTauErr_Mu34);
   fChain->SetBranchAddress("MyJpsi2ChiProb_Mu34", &MyJpsi2ChiProb_Mu34, &b_MyJpsi2ChiProb_Mu34);
   fChain->SetBranchAddress("MyJpsi2HitsBeforeMu34", &MyJpsi2HitsBeforeMu34, &b_MyJpsi2HitsBeforeMu34);
   fChain->SetBranchAddress("MyJpsi2MissAfterMu34", &MyJpsi2MissAfterMu34, &b_MyJpsi2MissAfterMu34);
   fChain->SetBranchAddress("MyJpsi3CTau_Mu13", &MyJpsi3CTau_Mu13, &b_MyJpsi3CTau_Mu13);
   fChain->SetBranchAddress("MyJpsi3CTauErr_Mu13", &MyJpsi3CTauErr_Mu13, &b_MyJpsi3CTauErr_Mu13);
   fChain->SetBranchAddress("MyJpsi3ChiProb_Mu13", &MyJpsi3ChiProb_Mu13, &b_MyJpsi3ChiProb_Mu13);
   fChain->SetBranchAddress("MyJpsi3HitsBeforeMu13", &MyJpsi3HitsBeforeMu13, &b_MyJpsi3HitsBeforeMu13);
   fChain->SetBranchAddress("MyJpsi3MissAfterMu13", &MyJpsi3MissAfterMu13, &b_MyJpsi3MissAfterMu13);
   fChain->SetBranchAddress("MyJpsi4CTau_Mu24", &MyJpsi4CTau_Mu24, &b_MyJpsi4CTau_Mu24);
   fChain->SetBranchAddress("MyJpsi4CTauErr_Mu24", &MyJpsi4CTauErr_Mu24, &b_MyJpsi4CTauErr_Mu24);
   fChain->SetBranchAddress("MyJpsi4ChiProb_Mu24", &MyJpsi4ChiProb_Mu24, &b_MyJpsi4ChiProb_Mu24);
   fChain->SetBranchAddress("MyJpsi4HitsBeforeMu24", &MyJpsi4HitsBeforeMu24, &b_MyJpsi4HitsBeforeMu24);
   fChain->SetBranchAddress("MyJpsi4MissAfterMu24", &MyJpsi4MissAfterMu24, &b_MyJpsi4MissAfterMu24);
   fChain->SetBranchAddress("MyJpsi5CTau_Mu14", &MyJpsi5CTau_Mu14, &b_MyJpsi5CTau_Mu14);
   fChain->SetBranchAddress("MyJpsi5CTauErr_Mu14", &MyJpsi5CTauErr_Mu14, &b_MyJpsi5CTauErr_Mu14);
   fChain->SetBranchAddress("MyJpsi5ChiProb_Mu14", &MyJpsi5ChiProb_Mu14, &b_MyJpsi5ChiProb_Mu14);
   fChain->SetBranchAddress("MyJpsi5HitsBeforeMu14", &MyJpsi5HitsBeforeMu14, &b_MyJpsi5HitsBeforeMu14);
   fChain->SetBranchAddress("MyJpsi5MissAfterMu14", &MyJpsi5MissAfterMu14, &b_MyJpsi5MissAfterMu14);
   fChain->SetBranchAddress("MyJpsi6CTau_Mu23", &MyJpsi6CTau_Mu23, &b_MyJpsi6CTau_Mu23);
   fChain->SetBranchAddress("MyJpsi6CTauErr_Mu23", &MyJpsi6CTauErr_Mu23, &b_MyJpsi6CTauErr_Mu23);
   fChain->SetBranchAddress("MyJpsi6ChiProb_Mu23", &MyJpsi6ChiProb_Mu23, &b_MyJpsi6ChiProb_Mu23);
   fChain->SetBranchAddress("MyJpsi6HitsBeforeMu23", &MyJpsi6HitsBeforeMu23, &b_MyJpsi6HitsBeforeMu23);
   fChain->SetBranchAddress("MyJpsi6MissAfterMu23", &MyJpsi6MissAfterMu23, &b_MyJpsi6MissAfterMu23);
   fChain->SetBranchAddress("MyJpsi1Mass_Mu12", &MyJpsi1Mass_Mu12, &b_MyJpsi1Mass_Mu12);
   fChain->SetBranchAddress("MyJpsi1MassErr_Mu12", &MyJpsi1MassErr_Mu12, &b_MyJpsi1MassErr_Mu12);
   fChain->SetBranchAddress("MyJpsi2Mass_Mu34", &MyJpsi2Mass_Mu34, &b_MyJpsi2Mass_Mu34);
   fChain->SetBranchAddress("MyJpsi2MassErr_Mu34", &MyJpsi2MassErr_Mu34, &b_MyJpsi2MassErr_Mu34);
   fChain->SetBranchAddress("MyJpsi3Mass_Mu13", &MyJpsi3Mass_Mu13, &b_MyJpsi3Mass_Mu13);
   fChain->SetBranchAddress("MyJpsi3MassErr_Mu13", &MyJpsi3MassErr_Mu13, &b_MyJpsi3MassErr_Mu13);
   fChain->SetBranchAddress("MyJpsi4Mass_Mu24", &MyJpsi4Mass_Mu24, &b_MyJpsi4Mass_Mu24);
   fChain->SetBranchAddress("MyJpsi4MassErr_Mu24", &MyJpsi4MassErr_Mu24, &b_MyJpsi4MassErr_Mu24);
   fChain->SetBranchAddress("MyJpsi5Mass_Mu14", &MyJpsi5Mass_Mu14, &b_MyJpsi5Mass_Mu14);
   fChain->SetBranchAddress("MyJpsi5MassErr_Mu14", &MyJpsi5MassErr_Mu14, &b_MyJpsi5MassErr_Mu14);
   fChain->SetBranchAddress("MyJpsi6Mass_Mu23", &MyJpsi6Mass_Mu23, &b_MyJpsi6Mass_Mu23);
   fChain->SetBranchAddress("MyJpsi6MassErr_Mu23", &MyJpsi6MassErr_Mu23, &b_MyJpsi6MassErr_Mu23);
   fChain->SetBranchAddress("MyFourMuonOverlap12", &MyFourMuonOverlap12, &b_MyFourMuonOverlap12);
   fChain->SetBranchAddress("MyFourMuonOverlap13", &MyFourMuonOverlap13, &b_MyFourMuonOverlap13);
   fChain->SetBranchAddress("MyFourMuonOverlap14", &MyFourMuonOverlap14, &b_MyFourMuonOverlap14);
   fChain->SetBranchAddress("MyFourMuonOverlap23", &MyFourMuonOverlap23, &b_MyFourMuonOverlap23);
   fChain->SetBranchAddress("MyFourMuonOverlap24", &MyFourMuonOverlap24, &b_MyFourMuonOverlap24);
   fChain->SetBranchAddress("MyFourMuonOverlap34", &MyFourMuonOverlap34, &b_MyFourMuonOverlap34);
   fChain->SetBranchAddress("MyFourMuonSharedSeg12", &MyFourMuonSharedSeg12, &b_MyFourMuonSharedSeg12);
   fChain->SetBranchAddress("MyFourMuonSharedSeg13", &MyFourMuonSharedSeg13, &b_MyFourMuonSharedSeg13);
   fChain->SetBranchAddress("MyFourMuonSharedSeg14", &MyFourMuonSharedSeg14, &b_MyFourMuonSharedSeg14);
   fChain->SetBranchAddress("MyFourMuonSharedSeg23", &MyFourMuonSharedSeg23, &b_MyFourMuonSharedSeg23);
   fChain->SetBranchAddress("MyFourMuonSharedSeg24", &MyFourMuonSharedSeg24, &b_MyFourMuonSharedSeg24);
   fChain->SetBranchAddress("MyFourMuonSharedSeg34", &MyFourMuonSharedSeg34, &b_MyFourMuonSharedSeg34);
   fChain->SetBranchAddress("MyFourMuonVtxCL", &MyFourMuonVtxCL, &b_MyFourMuonVtxCL);
   fChain->SetBranchAddress("MyFourMuonVtxC2", &MyFourMuonVtxC2, &b_MyFourMuonVtxC2);
   fChain->SetBranchAddress("MyFourMuonPx", &MyFourMuonPx, &b_MyFourMuonPx);
   fChain->SetBranchAddress("MyFourMuonPy", &MyFourMuonPy, &b_MyFourMuonPy);
   fChain->SetBranchAddress("MyFourMuonPz", &MyFourMuonPz, &b_MyFourMuonPz);
   fChain->SetBranchAddress("MyFourMuonDecayVtxX", &MyFourMuonDecayVtxX, &b_MyFourMuonDecayVtxX);
   fChain->SetBranchAddress("MyFourMuonDecayVtxY", &MyFourMuonDecayVtxY, &b_MyFourMuonDecayVtxY);
   fChain->SetBranchAddress("MyFourMuonDecayVtxZ", &MyFourMuonDecayVtxZ, &b_MyFourMuonDecayVtxZ);
   fChain->SetBranchAddress("MyFourMuonDecayVtxXE", &MyFourMuonDecayVtxXE, &b_MyFourMuonDecayVtxXE);
   fChain->SetBranchAddress("MyFourMuonDecayVtxYE", &MyFourMuonDecayVtxYE, &b_MyFourMuonDecayVtxYE);
   fChain->SetBranchAddress("MyFourMuonDecayVtxZE", &MyFourMuonDecayVtxZE, &b_MyFourMuonDecayVtxZE);
   fChain->SetBranchAddress("MyFourMuonMu1Idx", &MyFourMuonMu1Idx, &b_MyFourMuonMu1Idx);
   fChain->SetBranchAddress("MyFourMuonMu2Idx", &MyFourMuonMu2Idx, &b_MyFourMuonMu2Idx);
   fChain->SetBranchAddress("MyFourMuonMu2Px", &MyFourMuonMu2Px, &b_MyFourMuonMu2Px);
   fChain->SetBranchAddress("MyFourMuonMu2Py", &MyFourMuonMu2Py, &b_MyFourMuonMu2Py);
   fChain->SetBranchAddress("MyFourMuonMu2Pz", &MyFourMuonMu2Pz, &b_MyFourMuonMu2Pz);
   fChain->SetBranchAddress("MyFourMuonMu1Px", &MyFourMuonMu1Px, &b_MyFourMuonMu1Px);
   fChain->SetBranchAddress("MyFourMuonMu1Py", &MyFourMuonMu1Py, &b_MyFourMuonMu1Py);
   fChain->SetBranchAddress("MyFourMuonMu1Pz", &MyFourMuonMu1Pz, &b_MyFourMuonMu1Pz);
   fChain->SetBranchAddress("MyFourMuonMu2fChi2", &MyFourMuonMu2fChi2, &b_MyFourMuonMu2fChi2);
   fChain->SetBranchAddress("MyFourMuonMu2fNDF", &MyFourMuonMu2fNDF, &b_MyFourMuonMu2fNDF);
   fChain->SetBranchAddress("MyFourMuonMu1fChi2", &MyFourMuonMu1fChi2, &b_MyFourMuonMu1fChi2);
   fChain->SetBranchAddress("MyFourMuonMu1fNDF", &MyFourMuonMu1fNDF, &b_MyFourMuonMu1fNDF);
   fChain->SetBranchAddress("MyFourMuoncosAlpha", &MyFourMuoncosAlpha, &b_MyFourMuoncosAlpha);
   fChain->SetBranchAddress("MyFourMuonFLSig", &MyFourMuonFLSig, &b_MyFourMuonFLSig);
   fChain->SetBranchAddress("MyFourMuonrVtxMag2D", &MyFourMuonrVtxMag2D, &b_MyFourMuonrVtxMag2D);
   fChain->SetBranchAddress("MyFourMuonsigmaRvtxMag2D", &MyFourMuonsigmaRvtxMag2D, &b_MyFourMuonsigmaRvtxMag2D);
   fChain->SetBranchAddress("MyFourMuonTrkIsoOverFourMuSumpt", &MyFourMuonTrkIsoOverFourMuSumpt, &b_MyFourMuonTrkIsoOverFourMuSumpt);
   fChain->SetBranchAddress("MyFourMuonTrkIsoOverFourMuVectpt", &MyFourMuonTrkIsoOverFourMuVectpt, &b_MyFourMuonTrkIsoOverFourMuVectpt);
   fChain->SetBranchAddress("MyFourMuonMu3fNDF", &MyFourMuonMu3fNDF, &b_MyFourMuonMu3fNDF);
   fChain->SetBranchAddress("MyFourMuonMu3Idx", &MyFourMuonMu3Idx, &b_MyFourMuonMu3Idx);
   fChain->SetBranchAddress("MyFourMuonMu3Px", &MyFourMuonMu3Px, &b_MyFourMuonMu3Px);
   fChain->SetBranchAddress("MyFourMuonMu3Py", &MyFourMuonMu3Py, &b_MyFourMuonMu3Py);
   fChain->SetBranchAddress("MyFourMuonMu3Pz", &MyFourMuonMu3Pz, &b_MyFourMuonMu3Pz);
   fChain->SetBranchAddress("MyFourMuonMu3fChi2", &MyFourMuonMu3fChi2, &b_MyFourMuonMu3fChi2);
   fChain->SetBranchAddress("MyFourMuonMu4fNDF", &MyFourMuonMu4fNDF, &b_MyFourMuonMu4fNDF);
   fChain->SetBranchAddress("MyFourMuonMu4Idx", &MyFourMuonMu4Idx, &b_MyFourMuonMu4Idx);
   fChain->SetBranchAddress("MyFourMuonMu4Px", &MyFourMuonMu4Px, &b_MyFourMuonMu4Px);
   fChain->SetBranchAddress("MyFourMuonMu4Py", &MyFourMuonMu4Py, &b_MyFourMuonMu4Py);
   fChain->SetBranchAddress("MyFourMuonMu4Pz", &MyFourMuonMu4Pz, &b_MyFourMuonMu4Pz);
   fChain->SetBranchAddress("MyFourMuonMu4fChi2", &MyFourMuonMu4fChi2, &b_MyFourMuonMu4fChi2);
   fChain->SetBranchAddress("nmumuonly", &nmumuonly, &b_nmumuonly);
   fChain->SetBranchAddress("mumuonlyMass", &mumuonlyMass, &b_mumuonlyMass);
   fChain->SetBranchAddress("mumuonlyMassErr", &mumuonlyMassErr, &b_mumuonlyMassErr);
   fChain->SetBranchAddress("mumuonlyVtxCL", &mumuonlyVtxCL, &b_mumuonlyVtxCL);
   fChain->SetBranchAddress("mumuonlyPx", &mumuonlyPx, &b_mumuonlyPx);
   fChain->SetBranchAddress("mumuonlyPy", &mumuonlyPy, &b_mumuonlyPy);
   fChain->SetBranchAddress("mumuonlyPz", &mumuonlyPz, &b_mumuonlyPz);
   fChain->SetBranchAddress("mumuonlymu1Idx", &mumuonlymu1Idx, &b_mumuonlymu1Idx);
   fChain->SetBranchAddress("mumuonlymu2Idx", &mumuonlymu2Idx, &b_mumuonlymu2Idx);
   fChain->SetBranchAddress("mumuonlyctau", &mumuonlyctau, &b_mumuonlyctau);
   fChain->SetBranchAddress("mumuonlyctauerr", &mumuonlyctauerr, &b_mumuonlyctauerr);
   fChain->SetBranchAddress("mumuonlymuoverlapped", &mumuonlymuoverlapped, &b_mumuonlymuoverlapped);
   fChain->SetBranchAddress("mumuonlyChg", &mumuonlyChg, &b_mumuonlyChg);
   fChain->SetBranchAddress("mumuonlynsharedSeg", &mumuonlynsharedSeg, &b_mumuonlynsharedSeg);
   Notify();
}

Bool_t coffe::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void coffe::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t coffe::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef coffe_cxx
