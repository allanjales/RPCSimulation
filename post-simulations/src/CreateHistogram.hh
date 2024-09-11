#ifndef CREATEHISTOGRAM_HH
#define CREATEHISTOGRAM_HH

#include <RooDataSet.h>
#include <RooRealVar.h>
#include <RooPlot.h>
#include <TFile.h>
#include <RooHist.h>

#include <TH2.h>
#include <RooFormulaVar.h>

#include <iostream>
using namespace std;

#include <TCanvas.h>
#include <TNtuple.h>

class CreateHistogram
{
public:

	// 1 Dimensional Histogram

	/// @brief Creates a histogram for a variable and saves it to a file.
	/// @param data RooDataSet containing the data.
	/// @param outFile TFile for saving the histogram.
	/// @param histSaveName Name for the saved histogram.
	/// @param variable RooRealVar representing the variable.
	/// @param minVar Minimum value of the variable range.
	/// @param maxVar Maximum value of the variable range.
	/// @param nBins Number of bins in the histogram, default is 100.
	void static Histogram1DRanged(const RooDataSet& data, TFile* outFile, const char* histSaveName,
	RooRealVar& variable, double minVar, double maxVar, int nBins = 100, bool versbose = true)
	{

		if (versbose)
			cout << "\nTH1 for " << variable.GetName() << " in (" << minVar << "," << maxVar << ") range (nBins)...";
		// Create histogram for the variable and plot data on it
		RooPlot* frame = variable.frame(minVar, maxVar, nBins);
		data.plotOn(frame);

		// Save histogram
		outFile->cd();
		frame->getHist()->Write(histSaveName);
		delete frame;

		if (versbose)
			cout << " created.\n";
	}

	/// @brief Creates a histogram for a variable and saves it to a file.
	///        Allows for automatic determination of the variable range if not specified to use the variable's bounds.
	/// @param data RooDataSet containing the data.
	/// @param outFile TFile for saving the histogram.
	/// @param histSaveName Name for the saved histogram.
	/// @param variable RooRealVar representing the variable.
	/// @param sameVarBounds Use variable's bounds if true, otherwise determine automatically. The default value is false.
	/// @param nBins Number of bins in the histogram, default is 100.
	void static Histogram1D(const RooDataSet& data, TFile* outFile, const char* histSaveName,
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

		cout << "\nTH1 for " << variable.GetName() << (sameVarBounds ? " using same var bounds" : " getting min-max") << "\n";
		cout << "> Min: " << minVar << "\n";
		cout << "> Max: " << maxVar << "\n";

		Histogram1DRanged(data, outFile, histSaveName, variable, minVar, maxVar, nBins, false);
	}

	// 2 Dimensional Histogram

	void static Histogram2DRanged(const RooDataSet& data, TFile* outFile, const char* histSaveName,
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

	void static Histogram2D(const RooDataSet& data, TFile* outFile, const char* histSaveName,
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

		Histogram2DRanged(data, outFile, histSaveName, xVariable, xMin, xMax, xNBins, yVariable, yMin, yMax, yNBins);
	}

	// 3 Dimensional Scattering

	void static Scatter3D(const RooDataSet& data, string imagePath)
	{
		TCanvas *c = new TCanvas();
		TNtuple *n = new TNtuple("n", "n", "x:y:z:color");
		//data.Draw("PositionX:PositionY:PositionZ", "ParticleID==11 && RegionID==0", "goff");
		/*
		data.DrawClass("PositionX:PositionY:PositionZ", "ParticleID==11 && RegionID==0", "goff");
		for (int i = 0; i < data.numEntries(); i++)
		{
        	n->Fill(data.get(i)., 2, 3);
		}
		auto v1 = (RooRealVar*) vars->find("eta1");
		auto v2 = (RooRealVar*) vars->find("eta2");
		v1->setVal( std::abs( v1->getVal() ) );
		v2->setVal( std::abs( v2->getVal() ) );
		data2.add(*vars);

		n->Draw("x:y:z:color");
		*/
	}
};

#endif