#include "TFile.h"
#include "TTree.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "TMath.h"
#include "RooPlot.h"
#include "RooHist.h"

#include "TCanvas.h"
#include "TH2.h"

#include <iostream>
using namespace std;

/// @brief Creates a histogram for a variable and saves it to a file.
/// @param data RooDataSet containing the data.
/// @param outFile TFile for saving the histogram.
/// @param histSaveName Name for the saved histogram.
/// @param variable RooRealVar representing the variable.
/// @param minVar Minimum value of the variable range.
/// @param maxVar Maximum value of the variable range.
/// @param nBins Number of bins in the histogram, default is 100.
void create_histogram(const RooDataSet& data, TFile* outFile, const char* histSaveName,
RooRealVar& variable, double minVar, double maxVar, int nBins = 100)
{
	// Create histogram for the variable and plot data on it
	RooPlot* frame = variable.frame(minVar, maxVar, nBins);
	data.plotOn(frame);

	// Save histogram
	outFile->cd();
	frame->getHist()->Write(histSaveName);
	delete frame;
}

/// @brief Creates a histogram for a variable and saves it to a file.
///        Allows for automatic determination of the variable range if not specified to use the variable's bounds.
/// @param data RooDataSet containing the data.
/// @param outFile TFile for saving the histogram.
/// @param histSaveName Name for the saved histogram.
/// @param variable RooRealVar representing the variable.
/// @param sameVarBounds Use variable's bounds if true, otherwise determine automatically. The default value is false.
/// @param nBins Number of bins in the histogram, default is 100.
void create_histogram(const RooDataSet& data, TFile* outFile, const char* histSaveName,
RooRealVar& variable, bool sameVarBounds = false, int nBins = 100)
{
	// Get min and max values of the variable
	double minVar;
	double maxVar;
	if (sameVarBounds)
	{
		minVar = variable.getMin();
		maxVar = variable.getMax();
	}
	else
	{
		data.getRange(variable, minVar, maxVar);
	}

	cout << "TH1 for " << variable.GetName() << (sameVarBounds ? " using same var bounds" : " getting min-max") << "\n";
	cout << "> Min: " << minVar << "\n";
	cout << "> Max: " << maxVar << "\n\n";

	create_histogram(data, outFile, histSaveName, variable, minVar, maxVar, nBins);
}

void create_histogram_2d(const RooDataSet& data, TFile* outFile, const char* histSaveName,
RooRealVar& xVariable, double xMin, double xMax, int xNBins,
RooRealVar& yVariable, double yMin, double yMax, int yNBins)
{
	// Create histogram for the variable and plot data on it
	TH2* hist2d = dynamic_cast<TH2*>(data.createHistogram("hist2d",
	xVariable, RooFit::Binning(xNBins, xMin, xMax), RooFit::YVar(
	yVariable, RooFit::Binning(yNBins, yMin, yMax))));

	// Save histogram
	outFile->cd();
	hist2d->Write(histSaveName);
	delete hist2d;
}

void create_histogram_2d(const RooDataSet& data, TFile* outFile, const char* histSaveName,
RooRealVar& xVariable, int xNBins,
RooRealVar& yVariable, int yNBins,  bool sameVarBounds = false)
{
	// Get min and max values of the variable
	double xMin;
	double xMax;
	double yMin;
	double yMax;
	if (sameVarBounds)
	{
		xMin = xVariable.getMin();
		xMax = xVariable.getMax();
		yMin = yVariable.getMin();
		yMax = yVariable.getMax();
	}
	else
	{
		data.getRange(xVariable, xMin, xMax);
		data.getRange(yVariable, yMin, yMax);
	}

	cout << "TH2 for " << yVariable.GetName() << " x " << xVariable.GetName() << (sameVarBounds ? " using same var bounds" : " getting min-max") << "\n";
	cout << "> Min " << xVariable.GetName() << ": " << xMin << "\n";
	cout << "> Max " << xVariable.GetName() << ": " << xMax << "\n";
	cout << "> Min " << yVariable.GetName() << ": " << yMin << "\n";
	cout << "> Max " << yVariable.GetName() << ": " << yMax << "\n\n";

	create_histogram_2d(data, outFile, histSaveName, xVariable, xMin, xMax, xNBins, yVariable, yMin, yMax, yNBins);
}


void create_histograms()
{
	string filePath = "../build/results/output_0.root";
	// ParticleID 11 -> Electron; RegionID 0 -> Gas volume
	string cutString = "ParticleID==11 && RegionID==0";

	// ----------------------------
	// Open file and get tree
	// ----------------------------

	TFile* file0    = TFile::Open(filePath.c_str());
	cout << "File opened: " << filePath << "\n";
	TTree* DataTree = (TTree*)file0->Get(("DetectedParticles"));
	
	RooRealVar ParticleID  ("ParticleID",     "ParticleID"    , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar RegionID    ("RegionID",       "RegionID"      , 0,                      RooNumber::infinity());
	
	RooRealVar PositionX   ("PositionX",      "PositionX"     , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar PositionY   ("PositionY",      "PositionY"     , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar PositionZ   ("PositionZ",      "PositionZ"     , -RooNumber::infinity(), RooNumber::infinity());
	
	RooRealVar KinectEnergy("KinectEnergy",   "KinectEnergy"  , 0,                      RooNumber::infinity());
	RooRealVar TotalEnergy ("TotalEnergy",    "TotalEnergy"   , 0,                      RooNumber::infinity());
	RooRealVar Theta       ("Theta",          "Theta"         , 0,                      TMath::Pi());
	RooRealVar Phi         ("Phi",            "Phi"           , -TMath::Pi(),           TMath::Pi());
	RooRealVar MomentumMagnitude("MomentumMagnitude", "MomentumMagnitude", 0,           RooNumber::infinity());
	
	RooRealVar Pt             ("Pt",             "Pt"            , 0,                      RooNumber::infinity());
	RooRealVar Pseudorapidity ("Pseudorapidity", "Pseudorapidity", -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar CosTheta       ("CosTheta",       "CosTheta"      , -1.,                    1.);
	
	// Open tree file
	RooArgSet vars(ParticleID, RegionID, PositionX, PositionY, PositionZ, KinectEnergy, TotalEnergy,
	Theta, Phi, MomentumMagnitude, Pt, Pseudorapidity, CosTheta);
	RooDataSet* DataCut = new RooDataSet("data", "data", DataTree, vars, cutString.c_str());
	int total = DataCut->sumEntries();
	cout << "Total    tree entries: " << DataTree->GetEntries() << "\n";
	cout << "Filtered tree entries: " << total  << "\n";

	// Create output file
	TFile* outFile = new TFile("histograms.root", "RECREATE");

	create_histogram(*DataCut, outFile, "Energy",            KinectEnergy);
	create_histogram(*DataCut, outFile, "Theta",             Theta, true);
	create_histogram(*DataCut, outFile, "Phi",               Phi,   true);
	create_histogram(*DataCut, outFile, "CosTheta",          CosTheta, true);
	create_histogram(*DataCut, outFile, "Eta",               Pseudorapidity);
	create_histogram(*DataCut, outFile, "MomentumMagnitude", MomentumMagnitude);
	create_histogram(*DataCut, outFile, "Pt",                Pt);
	create_histogram_2d(*DataCut, outFile, "XY", PositionX, -2, 2, 50, PositionY, -2, 2, 50);
	create_histogram_2d(*DataCut, outFile, "ZY", PositionZ, -1, 1, 50, PositionY, -4, 4, 50);
	create_histogram_2d(*DataCut, outFile, "ThetaPhi", Theta, 50, Phi, 50, true);
	create_histogram_2d(*DataCut, outFile, "PtP", Pt, 50, MomentumMagnitude, 50);
	delete DataCut;

	// Get particles ID
	RooDataSet* DataTreeID = new RooDataSet("data", "data", DataTree, RooArgSet(ParticleID, RegionID), "RegionID==0");
	double minId, maxId;
	DataTreeID->getRange(ParticleID, minId, maxId);
	create_histogram(*DataTreeID, outFile, "ParticleID", ParticleID, minId+0.5, maxId+0.5, maxId-minId);
	delete DataTreeID;

	cout << "File created \n";
	file0->Close();
	outFile->Close();

	delete file0;
	delete outFile;
}