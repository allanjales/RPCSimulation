#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <RooDataSet.h>
#include <RooRealVar.h>

#include <iostream>
using namespace std;

#include "src/CreateHistogram.hh"

void create_histograms()
{
	string filePath = "../build/results/output_0.root";
	// ParticleID 11 -> Electron
	string cutString = "ParticleID==11";

	// ----------------------------
	// Open file and get tree
	// ----------------------------

	TFile* file0    = TFile::Open(filePath.c_str());
	cout << "File opened: " << filePath << "\n";
	TTree* DataTree = (TTree*)file0->Get(("DetectedParticles"));
	
	constexpr double INF = RooNumber::infinity();
	constexpr double PI  = TMath::Pi();
	RooRealVar ParticleID  ("ParticleID",   "ParticleID",  -INF, INF);
	
	RooRealVar PositionX   ("PositionX",    "PositionX",   -INF, INF);
	RooRealVar PositionY   ("PositionY",    "PositionY",   -INF, INF);
	RooRealVar PositionZ   ("PositionZ",    "PositionZ",   -INF, INF);
	
	RooRealVar KinectEnergy("KinectEnergy", "KinectEnergy", 0,   INF);
	RooRealVar TotalEnergy ("TotalEnergy",  "TotalEnergy",  0,   INF);
	RooRealVar Theta       ("Theta",        "Theta",        0,   PI);
	RooRealVar Phi         ("Phi",          "Phi",         -PI,  PI);
	RooRealVar Momentum    ("Momentum",     "Momentum",     0,   INF);
	
	RooRealVar Pt          ("Pt",           "Pt",           0,   INF);
	RooRealVar Eta         ("Eta",          "Eta",         -INF, INF);
	RooRealVar CosTheta    ("CosTheta",     "CosTheta",    -1.,  1.);
	
	// Open tree file
	RooArgSet vars(ParticleID, PositionX, PositionY, PositionZ, KinectEnergy, TotalEnergy,
	Theta, Phi, Momentum, Pt, Eta, CosTheta);
	RooDataSet* DataCut = new RooDataSet("data", "data", DataTree, vars, cutString.c_str());
	int total = DataCut->sumEntries();
	cout << "Total    tree entries: " << DataTree->GetEntries() << "\n";
	cout << "Filtered tree entries: " << total  << "\n";

	// Create output file
	TFile* outFile = new TFile("histograms.root", "RECREATE");

	CreateHistogram::Histogram1D(*DataCut, outFile, "Energy",   KinectEnergy);
	CreateHistogram::Histogram1D(*DataCut, outFile, "Theta",    Theta, true);
	CreateHistogram::Histogram1D(*DataCut, outFile, "Phi",      Phi,   true);
	CreateHistogram::Histogram1D(*DataCut, outFile, "CosTheta", CosTheta, true);
	CreateHistogram::Histogram1DRanged(*DataCut, outFile, "Eta",      Eta, -6., 6.);
	CreateHistogram::Histogram1D(*DataCut, outFile, "Momentum", Momentum);
	CreateHistogram::Histogram1D(*DataCut, outFile, "Pt",       Pt);
	CreateHistogram::Histogram2DRanged(*DataCut, outFile, "XY", PositionX, -2, 2, 50, PositionY, -2, 2, 50);
	CreateHistogram::Histogram2DRanged(*DataCut, outFile, "ZY", PositionZ, -1, 1, 50, PositionY, -4, 4, 50);
	CreateHistogram::Histogram2D(*DataCut, outFile, "ThetaPhi", Theta, 50, Phi, 50, true);
	CreateHistogram::Histogram2D(*DataCut, outFile, "PtP", Pt, 50, Momentum, 50);
	CreateHistogram::Histogram2DRanged(*DataCut, outFile, "PtEta", Pt, 0, 90, 50, Eta, -6, 6, 50);

	delete DataCut;

	// Get particles ID
	RooDataSet* DataTreeID = new RooDataSet("data", "data", DataTree, RooArgSet(ParticleID));
	double minId, maxId;
	DataTreeID->getRange(ParticleID, minId, maxId);
	int nBins = maxId-minId;
	if (nBins > 200) nBins = 200;
	CreateHistogram::Histogram1DRanged(*DataTreeID, outFile, "ParticleID", ParticleID, minId, maxId, nBins);
	CreateHistogram::Histogram1DRanged(*DataTreeID, outFile, "ParticleIDMain", ParticleID, -25, 25, 50);
	delete DataTreeID;

	cout << "File created \n";
	file0->Close();
	outFile->Close();

	delete file0;
	delete outFile;
}