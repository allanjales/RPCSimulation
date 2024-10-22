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
#include "src/MinMax.hh"
#include "src/HistogramControl.hh"

void visualizate()
{
	string filePath = "../build/results/output_0.root";
	//string filePath = "../build/results/output_0.root";
	
	string cutString = "ParticleID==11";

	// ----------------------------
	// Open file, get and prepare tree
	// ----------------------------

	TFile* file0    = TFile::Open(filePath.c_str());
	cout << "File opened: " << filePath << "\n";
	TTree* tree = (TTree*)file0->Get(("DetectedParticles"));

	long long numberEntries = tree->GetEntries();
	//numberEntries = 1000000;
	printf("TTree has %lld entries", numberEntries);

	int ParticleID;
	double PositionX, PositionY, PositionZ;
	double KinectEnergy, TotalEnergy, Theta, Phi, Momentum;
	double Pt, Eta, CosTheta;

	tree->SetBranchAddress("ParticleID",   &ParticleID);   // -INF. INF
	
	tree->SetBranchAddress("PositionX",    &PositionX);    // -INF. INF
	tree->SetBranchAddress("PositionY",    &PositionY);    // -INF. INF
	tree->SetBranchAddress("PositionZ",    &PositionZ);    // -INF. INF

	tree->SetBranchAddress("KinectEnergy", &KinectEnergy); // 0, INF
	tree->SetBranchAddress("TotalEnergy",  &TotalEnergy);  // 0, INF
	tree->SetBranchAddress("Theta",        &Theta);        // 0, PI
	tree->SetBranchAddress("Phi",          &Phi);          // -PI, PI
	tree->SetBranchAddress("Momentum",     &Momentum);     // 0, INF
	
	tree->SetBranchAddress("Pt",           &Pt);           // 0, INF
	tree->SetBranchAddress("Eta",          &Eta);          // -INF, INF
	tree->SetBranchAddress("CosTheta",     &CosTheta);     // -1.,  1.

	constexpr double PI  = TMath::Pi();

	cout << "Addresses set.\n";

	// ----------------------------
	// Prepare and fill visualizations
	// ----------------------------

	cout << "Finding useful min/max...\n";
	MinMax mmKinectEnergy, mmTotalEnergy, mmMomentum, mmPt, mmEta, mmParticleID;
	bool areMinMaxSet = false;
	for (long long i : tq::trange(numberEntries))
	{
		tree->GetEntry(i);

		if (ParticleID < mmParticleID.min)
			mmParticleID.min = ParticleID;
		if (ParticleID > mmParticleID.max)
			mmParticleID.max = ParticleID;

		// ParticleID 11 -> Electron
		if (ParticleID != 11)
			continue;

		if (!areMinMaxSet)
		{
			mmParticleID.min = ParticleID;
			mmParticleID.max = ParticleID;

			mmKinectEnergy.min = KinectEnergy;
			mmKinectEnergy.max = KinectEnergy;

			mmTotalEnergy.min = TotalEnergy;
			mmTotalEnergy.max = TotalEnergy;

			mmMomentum.min = Momentum;
			mmMomentum.max = Momentum;

			mmPt.min = Pt;
			mmPt.max = Pt;

			mmEta.min = Eta;
			mmEta.max = Eta;

			areMinMaxSet = true;
			continue;
		}

		if (KinectEnergy < mmKinectEnergy.min)
			mmKinectEnergy.min = KinectEnergy;
		if (KinectEnergy > mmKinectEnergy.max)
			mmKinectEnergy.max = KinectEnergy;

		if (TotalEnergy < mmTotalEnergy.min)
			mmTotalEnergy.min = TotalEnergy;
		if (TotalEnergy > mmTotalEnergy.max)
			mmTotalEnergy.max = TotalEnergy;

		if (Momentum < mmMomentum.min)
			mmMomentum.min = Momentum;
		if (Momentum > mmMomentum.max)
			mmMomentum.max = Momentum;

		if (Pt < mmPt.min)
			mmPt.min = Pt;
		if (Pt > mmPt.max)
			mmPt.max = Pt;

		if (Eta < mmEta.min)
			mmEta.min = Eta;
		if (Eta > mmEta.max)
			mmEta.max = Eta;
	}

	cout << "\nCreating histograms\n";

	TH1I hParticleID("ParticleID", "Particle's ID distribution;PDG ID;Counts", 50, -25, 25);

	double diff = mmParticleID.max++ - mmParticleID.min;
	int nBins = diff;
	if (nBins > 100)
		nBins = 100;
	TH1I hParticleIDFullRange("ParticleIDFullRange", "Particle's ID distribution (full range);PDG ID;Counts", nBins, mmParticleID.min - int(diff*0.05), mmParticleID.max + int(diff*0.05));

	TH1D hEnergy("Energy", "Electron's kinect energy distribution;Energy (MeV);Counts", 100, mmKinectEnergy.min, mmKinectEnergy.max);
	TH1D hTheta("Theta", "Electron's longitudinal angle distribution;#theta (rad);Counts", 100, 0, PI);
	TH1D hPhi("Phi", "Electron's azimuthal angle distribution;#phi (rad);Counts", 100, -PI, PI);
	hPhi.SetMinimum(0);
	TH1D hCosTheta("CosTheta", "Electron's cos#theta distribution;cos#theta;Counts", 100, -1, 1);
	//hCosTheta.SetMinimum(0);

	TH1D hEta("Eta", "Electron's pseudorapidity distribution;#eta;Counts", 100, mmEta.min, mmEta.max);
	TH1D hP("P", "Electron's momentum distribution;p (MeV/c);Counts", 100, mmMomentum.min, mmMomentum.max);
	TH1D hPt("Pt", "Electron's transverse momentum distribution;p_{T} (MeV/c);Counts", 100, mmPt.min, mmPt.max);

	TH2D hThetaPhi("ThetaPhi", "Electron's angle distribution;#theta (rad);#phi (rad)", 20, 0, PI, 20, -PI, PI);
	TH2D hEtaPhi("EtaPhi", "Electron's angle distribution;#eta;#phi (rad)", 20, mmEta.min, mmEta.max, 20, -PI, PI);
	TH2D hPtEta("PtEta", "Electron's momentum and angle distribution;p_{T} (MeV/c);#eta", 20, mmPt.min, mmPt.max, 20, mmEta.min, mmEta.max);

	nBins = 20;
	TH3D hPosition("Position", "Electron's position;z (mm);x (mm);y (mm)", nBins, -1, 1, nBins, -2, 2, nBins, -2, 2);
	TH3D hZEtaPhi("ZEtaPhi", "Electron's angle and position distribution;z (mm);#eta;#phi (rad)", nBins, -1, 1, nBins, mmEta.min, mmEta.max, nBins, -PI, PI);
	TH3D hZThetaPhi("ZThetaPhi", "Electron's angle and position distribution;z (mm);#theta (rad);#phi (rad)", nBins, -1, 1, nBins, 0, PI, nBins, -PI, PI);

	cout << "Histograms created.\n";

	StopWatch timer;
	cout << "Starting to fill visualizations\n";;
	for (long long i : tq::trange(numberEntries))
	{
		tree->GetEntry(i);

		hParticleID.Fill(ParticleID);
		hParticleIDFullRange.Fill(ParticleID);

		if (ParticleID != 11)
			continue;

		hEnergy.Fill(KinectEnergy);
		hTheta.Fill(Theta);
		hPhi.Fill(Phi);
		hCosTheta.Fill(CosTheta);
	
		hEta.Fill(Eta);
		hP.Fill(Momentum);
		hPt.Fill(Pt);

		hThetaPhi.Fill(Theta, Phi);
		hEtaPhi.Fill(Eta, Phi);
		hPtEta.Fill(Pt, Eta);

		hPosition.Fill(PositionZ, PositionX, PositionY);
		hZEtaPhi.Fill(PositionZ, Eta, Phi);
		hZThetaPhi.Fill(PositionZ, Eta, Phi);
	}
	printf("\nFilling visualizations finished. Took about %s\n", timer.TimeElapsedString().c_str());


	// ----------------------------
	// Save visualizations and delete objects
	// ----------------------------

	// Create output file
	TFile* outFile = new TFile("histograms.root", "RECREATE");

	// Show it
	HistogramControl::DrawAndSave1D(hParticleID, "", "y");
	HistogramControl::DrawAndSave1D(hParticleIDFullRange, "", "y");
	HistogramControl::DrawAndSave1D(hEnergy, "", "y");
	HistogramControl::DrawAndSave1D(hTheta);
	HistogramControl::DrawAndSave1D(hPhi);
	HistogramControl::DrawAndSave1D(hCosTheta, "", "y");

	HistogramControl::DrawAndSave1D(hEta, "", "y");
	HistogramControl::DrawAndSave1D(hP, "", "y");
	HistogramControl::DrawAndSave1D(hPt, "", "y");

	HistogramControl::DrawAndSave2D(hThetaPhi, "colz");
	HistogramControl::DrawAndSave2D(hEtaPhi, "colz");
	HistogramControl::DrawAndSave2D(hPtEta, "colz");

	HistogramControl::DrawAndSave3D(hPosition, "scat");
	HistogramControl::DrawAndSave3D(hZEtaPhi, "scat");
	HistogramControl::DrawAndSave3D(hZThetaPhi, "scat");

	outFile->Close();

	delete tree;
	delete file0;
	delete outFile;
}