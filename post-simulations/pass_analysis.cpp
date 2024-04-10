//#include <string>
using namespace RooFit;

void pass_analysis()
{
	TFile* file0    = TFile::Open("../build/results/output_0.root");
	TTree* DataTree = (TTree*)file0->Get(("DetectedParticles"));
	
	RooRealVar ParticleID  ("fParticleID",   "ParticleID"   , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar RegionID    ("fRegionID",     "RegionID"     , 0,                      RooNumber::infinity());
	RooRealVar PositionX   ("fPositionX",    "PositionX"    , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar PositionY   ("fPositionY",    "PositionY"    , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar PositionZ   ("fPositionZ",    "PositionZ"    , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar KinectEnergy("fKinectEnergy", "KinectEnergy" , 0,                      RooNumber::infinity());
	RooRealVar CosTheta    ("fCosTheta",     "CosTheta"     , -1.,                    1.);
	RooRealVar Phi         ("fPhi",          "Phi"          , -TMath::Pi(),           TMath::Pi());
	RooDataSet DataGamma("data", "data", DataTree,
	RooArgSet(ParticleID, RegionID, PositionX, PositionY, PositionY, KinectEnergy, CosTheta, Phi));

	cout << DataTree->GetEntries() << endl;

	// SETTINGS
	int color = 9;	//Blue
	string sufix = " (1 million mu+ w/ 1 GeV)";

	
	
	int total = DataGamma.sumEntries();

	// General Latex
	TLatex* text = new TLatex();
	text->SetTextSize(0.04);
	text->SetTextAlign(12);
	text->SetNDC(kTRUE);

	// --------------------------------
	// Particle IDs
	// --------------------------------
	{
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = ParticleID.frame(-13, 13, 26);
		frame->SetTitle((string("Particle types")+sufix).c_str());
		DataGamma.plotOn(frame, DrawOption("BE"), FillColor(color));
		frame->GetXaxis()->SetTitle("Particle ID");
		frame->GetYaxis()->SetTitle("Events");
		frame->Draw("B");
		int inRange = DataGamma.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= fParticleID && fParticleID <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.6, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.6, 0.80, Form("Out of range = %d", total - inRange));
		c1->SetLogy();
		c1->SaveAs("particle_ids.png");
	}


	// --------------------------------
	// Region IDs
	// --------------------------------
	{
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = RegionID.frame(0, 10, 10);
		frame->SetTitle((string("Detect region")+sufix).c_str());
		DataGamma.plotOn(frame, DrawOption("BE"), FillColor(color));
		frame->GetXaxis()->SetTitle("Region ID");
		frame->GetYaxis()->SetTitle("Events");
		frame->Draw("B");
		int inRange = DataGamma.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= fRegionID && fRegionID <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.6, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.6, 0.80, Form("Out of range = %d", total - inRange));
		c1->SetLogy();
		c1->SaveAs("regions_ids.png");
	}
}