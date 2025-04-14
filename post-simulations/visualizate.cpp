// ----------------------------
// ! Brief: Visualizate the results of the simulation in histograms.
// ! Author: Allan Jales
// ----------------------------

#include <TFile.h>
#include <TTree.h>
#include <TMath.h>

#include <TH1I.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>

#include <ostream>
using namespace std;

#include "src/StopWatch.hh"
#include "src/tqdm.hpp"
#include "src/Range.hh"
#include "src/HistogramsControl.hh"
#include "src/Formulas.hh"

void visualizate()
{
	string filePath = "../build/results/output.root";
	
	string cutString = "ParticleID==11";

	// ----------------------------
	// Open file, get tree and prepare it
	// ----------------------------

	TFile* file0    = TFile::Open(filePath.c_str());
	cout << "File opened: " << filePath << "\n";
	TTree* tree = (TTree*)file0->Get(("TrackerHits"));

	long long numberEntries = tree->GetEntries();
	//numberEntries = 1000000;
	printf("TTree has %lld entries", numberEntries);

	int ParticleID;
	double Edep;
	double PositionX, PositionY, PositionZ;
	double Time;
	double MomentumX, MomentumY, MomentumZ;
	double KinectEnergy;

	tree->SetBranchAddress("ParticleID",   &ParticleID);   // -INF, INF
	tree->SetBranchAddress("Edep",         &Edep);         // 0., INF
	tree->SetBranchAddress("PositionX",    &PositionX);    // -INF, INF
	tree->SetBranchAddress("PositionY",    &PositionY);    // -INF, INF
	tree->SetBranchAddress("PositionZ",    &PositionZ);    // -INF, INF
	tree->SetBranchAddress("Time",         &Time);         // 0., INF
	tree->SetBranchAddress("MomentumX",    &MomentumX);    // -INF, INF
	tree->SetBranchAddress("MomentumY",    &MomentumY);    // -INF, INF
	tree->SetBranchAddress("MomentumZ",    &MomentumZ);    // -INF, INF
	tree->SetBranchAddress("KinectEnergy", &KinectEnergy); // 0, INF
	// tree->SetBranchAddress("Theta",        &Theta);        // 0, PI
	// tree->SetBranchAddress("Phi",          &Phi);          // -PI, PI
	// tree->SetBranchAddress("Momentum",     &Momentum);     // 0, INF
	// tree->SetBranchAddress("Pt",           &Pt);           // 0, INF
	// tree->SetBranchAddress("Eta",          &Eta);          // -INF, INF
	// tree->SetBranchAddress("CosTheta",     &CosTheta);     // -1.,  1.

	constexpr double PI  = TMath::Pi();

	cout << "Addresses set.\n";

	// ----------------------------
	// Find min/max values for creating histograms
	// ----------------------------

	cout << "Finding useful min/max...\n";
	Range rParticleID, rEdep, rPositionX, rPositionY, rPositionZ, rTime, rKinectEnergy;
	Range rMomentum, rPt, rEta;
	for (long long i : tq::trange(numberEntries))
	{
		tree->GetEntry(i);

		rParticleID.UpdateRangeValues(ParticleID);
		
		// ParticleID 11 -> Electron
		if (ParticleID != 11)
			continue;
			
		rEdep.UpdateRangeValues(Edep);
		rPositionX.UpdateRangeValues(PositionX);
		rPositionY.UpdateRangeValues(PositionY);
		rPositionZ.UpdateRangeValues(PositionZ);
		rTime.UpdateRangeValues(Time);
		rKinectEnergy.UpdateRangeValues(KinectEnergy);
		rMomentum.UpdateRangeValues(Formulas::GetMomentum(MomentumX, MomentumY, MomentumZ));
		rPt.UpdateRangeValues(Formulas::GetPt(MomentumX, MomentumY));
		rEta.UpdateRangeValues(Formulas::GetEta(Formulas::GetTheta(MomentumX, MomentumY, MomentumZ)));
	}

	cout << "\nCreating histograms\n";

	// ----------------------------
	// Prepare histograms
	// ----------------------------

	TH1I hParticleID("ParticleID", "Particle's ID distribution;PDG ID;Counts", 50, -25, 25);

	int idDiff = rParticleID.GetMax() + 1 - rParticleID.GetMin();
	int nBins = idDiff;
	if (nBins > 100) nBins = 100;
	TH1I hParticleIDFullRange("ParticleIDFullRange", "Particle's ID distribution (full range);PDG ID;Counts",
	    nBins, rParticleID.GetMin() - int(idDiff*0.05), rParticleID.GetMax() + int(idDiff*0.05));

	TH1D hEdep("Edep", "Electron's energy deposit distribution;Energy (MeV);Counts",
		100, rEdep.GetMin(), rEdep.GetMax());
	TH1D hKinE("Energy", "Electron's kinect energy distribution;Energy (MeV);Counts",
		100, rKinectEnergy.GetMin(), rKinectEnergy.GetMax());
	TH1D hTime("Time", "Electron's time distribution;Time (s);Counts",
		100, rTime.GetMin(), rTime.GetMax());

	TH1D hTheta("Theta", "Electron's longitudinal angle distribution;#theta (rad);Counts", 100, 0, PI);
	TH1D hPhi("Phi", "Electron's azimuthal angle distribution;#phi (rad);Counts", 100, -PI, PI);
	hPhi.SetMinimum(0);
	TH1D hCosTheta("CosTheta", "Electron's cos#theta distribution;cos#theta;Counts", 100, -1, 1);
	//hCosTheta.SetMinimum(0);

	TH1D hP("P", "Electron's momentum distribution;p (MeV/c);Counts",
		100, rMomentum.GetMin(), rMomentum.GetMax());
	TH1D hPt("Pt", "Electron's transverse momentum distribution;p_{T} (MeV/c);Counts",
		100, rPt.GetMin(), rPt.GetMax()); 
	TH1D hEta("Eta", "Electron's pseudorapidity distribution;#eta;Counts",
		100, rEta.GetMin(), rEta.GetMax());

	TH2D hThetaPhi("ThetaPhi", "Electron's angle distribution;#theta (rad);#phi (rad)",
		20, 0, PI, 20, -PI, PI);
	TH2D hPtEta("PtEta", "Electron's momentum and pseudorapidity distribution;p_{T} (MeV/c);#eta",
		20, rPt.GetMin(), rPt.GetMax(), 20, rEta.GetMin(), rEta.GetMax());

	nBins = 20;
	TH3D hPosition("Position", "Electron's position;z (mm);x (mm);y (mm)",
		nBins, -1, 1, nBins, -1, 1, nBins, -1, 1);
	TH3D hZThetaPhi("ZThetaPhi", "Electron's angle and position distribution;z (mm);#theta (rad);#phi (rad)",
		nBins, -1, 1, nBins, 0, PI, nBins, -PI, PI);

	cout << "Histograms created.\n";

	// ----------------------------
	// Fill visualizations
	// ----------------------------

	StopWatch timer;
	cout << "Starting to fill visualizations\n";
	double Theta, Phi, Momentum, Pt, Eta;
	for (long long i : tq::trange(numberEntries))
	{
		tree->GetEntry(i);
	
		Theta    = Formulas::GetTheta(MomentumX, MomentumY, MomentumZ);
		Phi      = Formulas::GetPhi(MomentumX, MomentumY);
		Momentum = Formulas::GetMomentum(MomentumX, MomentumY, MomentumZ);
		Pt       = Formulas::GetPt(MomentumX, MomentumY);
		Eta      = Formulas::GetEta(Theta);

		hParticleID.Fill(ParticleID);
		hParticleIDFullRange.Fill(ParticleID);

		if (ParticleID != 11)
			continue;

		hEdep.Fill(Edep);
		hKinE.Fill(KinectEnergy);
		hTime.Fill(Time);

		hTheta.Fill(Theta);
		hPhi.Fill(Phi);
		hCosTheta.Fill(TMath::Cos(Theta));

		hP.Fill(Momentum);
		hPt.Fill(Pt);
		hEta.Fill(Eta);

		hThetaPhi.Fill(Theta, Phi);
		hPtEta.Fill(Pt, Eta);

		hPosition.Fill(PositionZ, PositionX, PositionY);
		hZThetaPhi.Fill(PositionZ, Eta, Phi);
	}
	printf("\nFilling visualizations finished. Took about %s\n", timer.TimeElapsedString().c_str());


	// ----------------------------
	// Save visualizations and delete objects
	// ----------------------------

	// Create output file
	TFile* outFile = new TFile("histograms.root", "RECREATE");

	// Show it
	HistogramsControl hController("plots/", ".png");
	
	hController.DrawAndSave1D(hParticleID, "", "y");
	hController.DrawAndSave1D(hParticleIDFullRange, "", "y");
	
	hController.DrawAndSave1D(hEdep, "", "y");
	hController.DrawAndSave1D(hKinE, "", "y");
	hController.DrawAndSave1D(hTime, "", "y");

	hController.DrawAndSave1D(hTheta);
	hController.DrawAndSave1D(hPhi);
	hController.DrawAndSave1D(hCosTheta, "", "y");

	hController.DrawAndSave1D(hP, "", "y");
	hController.DrawAndSave1D(hPt, "", "y");
	hController.DrawAndSave1D(hEta, "", "y");

	hController.DrawAndSave2D(hThetaPhi, "colz");
	hController.DrawAndSave2D(hPtEta, "colz");

	hController.DrawAndSave3D(hPosition, "scat");
	hController.DrawAndSave3D(hZThetaPhi, "scat");

	outFile->Close();

	delete tree;
	delete file0;
	delete outFile;
}