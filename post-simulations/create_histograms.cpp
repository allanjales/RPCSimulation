//#include <string>
using namespace RooFit;

void create_histograms()
{
	TFile* file0    = TFile::Open("../build/results/output_0.root");
	//TFile* file0    = TFile::Open("../build/results/output_0_amostra.root");
	TTree* DataTree = (TTree*)file0->Get(("DetectedParticles"));
	
	RooRealVar ParticleID  ("ParticleID",     "ParticleID"    , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar RegionID    ("RegionID",       "RegionID"      , 0,                      RooNumber::infinity());
	RooRealVar PositionX   ("PositionX",      "PositionX"     , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar PositionY   ("PositionY",      "PositionY"     , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar PositionZ   ("PositionZ",      "PositionZ"     , -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar KinectEnergy("KinectEnergy",   "KinectEnergy"  , 0,                      RooNumber::infinity());
	RooRealVar Theta       ("Theta",          "Theta"         , 0,           TMath::Pi());
	RooRealVar Phi         ("Phi",            "Phi"           , -TMath::Pi(),           TMath::Pi());
	RooRealVar CosTheta    ("CosTheta",       "CosTheta"      , -1.,                    1.);
	RooRealVar OldCosTheta ("OldCosTheta",    "OldCosTheta"   , -1.,                    1.);
	RooRealVar Pseudorapidity    ("Pseudorapidity", "Pseudorapidity", -RooNumber::infinity(),          RooNumber::infinity());
	RooRealVar MomentumMagnitude    ("MomentumMagnitude", "MomentumMagnitude", 0,                      RooNumber::infinity());
	RooArgSet  vars(ParticleID, RegionID, PositionX, PositionY, PositionZ, KinectEnergy,
	Theta, Phi, CosTheta, OldCosTheta, Pseudorapidity, MomentumMagnitude);
	
	RooDataSet DataCut("data", "data", DataTree, vars, "ParticleID==11 && RegionID==0");
	int total = DataCut.sumEntries();

	TFile* outFile = new TFile("histograms.root", "RECREATE");
	
	// ----------------------------
	// SETTINGS
	// ----------------------------

	int color = 9;	//9 -> blue
	string sufix = " (1 million mu+ w/ 1 GeV)";

	
	cout << "Total    tree entries: " << DataTree->GetEntries() << "\n";
	cout << "Filtered tree entries: " << total  << "\n";

	// General Latex
	TLatex* text = new TLatex();
	text->SetTextSize(0.04);
	text->SetTextAlign(12);
	text->SetNDC(kTRUE);

	// ----------------
	// Energy Plot
	// ----------------
	{
		//Create histogram
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = KinectEnergy.frame(0., 100.);
		frame->SetTitle((string("Electrons")+sufix).c_str());
		DataCut.plotOn(frame, DrawOption("BX"), FillColor(color));
		frame->SetMinimum(1);
		frame->GetXaxis()->SetTitle("Energy (MeV)");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");

		// Save histogram
		outFile->cd();
		frame->getHist()->Write("ElectronEnergyDistribution");

		int inRange = DataCut.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= KinectEnergy && KinectEnergy <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.6, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.6, 0.80, Form("Out of range = %d", total - inRange));
		c1->SetLogy();
	}

	// ---------------------
	// Cos Theta
	// ---------------------
	{
		// Create histogram
		TCanvas* c1  = new TCanvas();
		RooPlot* frame = CosTheta.frame(-1, 1, 100);
		//RooPlot* frame = CosTheta.frame(-0.04, -0.01, 1000);
		frame->SetTitle((string("Electrons Cos(#theta)")+sufix).c_str());
		DataCut.plotOn(frame, DrawOption("BX"), FillColor(color));
		frame->SetMinimum(1);
		//frame->SetMaximum(35000);
		frame->GetXaxis()->SetTitle("Cos(#theta)");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");

		// Save histogram
		outFile->cd();
		frame->getHist()->Write("ElectronCosThetaDistribution");

		int inRange = DataCut.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= CosTheta && CosTheta <="
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.65, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.65, 0.80, Form("Out of range = %d", total - inRange));
	}

	// ---------------------
	// OLD Cos Theta
	// ---------------------
	{
		// Create histogram
		TCanvas* c1  = new TCanvas();
		RooPlot* frame = OldCosTheta.frame(-1, 1, 100);
		//RooPlot* frame = OldCosTheta.frame(-0.04, -0.01, 1000);
		frame->SetTitle((string("Old Electrons Cos(#theta)")+sufix).c_str());
		DataCut.plotOn(frame, DrawOption("BX"), FillColor(color));
		frame->SetMinimum(1);
		//frame->SetMaximum(35000);
		frame->GetXaxis()->SetTitle("Cos(#theta)");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");

		// Save histogram
		outFile->cd();
		frame->getHist()->Write("OldElectronCosThetaDistribution");

		int inRange = DataCut.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= OldCosTheta && OldCosTheta <="
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.65, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.65, 0.80, Form("Out of range = %d", total - inRange));
	}

	// ---------------------
	// Theta
	// ---------------------
	{
		// Create histogram
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = Theta.frame(0, TMath::Pi());
		frame->SetTitle((string("Electrons #theta")+sufix).c_str());
		DataCut.plotOn(frame, DrawOption("BX"), FillColor(color));
		frame->SetMinimum(1);
		frame->GetXaxis()->SetTitle("#theta (rad)");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");

		// Save histogram
		outFile->cd();
		frame->getHist()->Write("ElectronThetaDistribution");

		int inRange = DataCut.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= Theta && Theta <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.65, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.65, 0.80, Form("Out of range = %d", total - inRange));
	}

	// ---------------------
	// Phi
	// ---------------------
	{
		// Create histogram
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = Phi.frame(-TMath::Pi(), TMath::Pi());
		frame->SetTitle((string("Electrons #phi")+sufix).c_str());
		DataCut.plotOn(frame, DrawOption("BX"), FillColor(color));
		frame->SetMinimum(1);
		frame->GetXaxis()->SetTitle("#phi (rad)");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");

		// Save histogram
		outFile->cd();
		frame->getHist()->Write("ElectronPhiDistribution");

		int inRange = DataCut.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= Phi && Phi <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.65, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.65, 0.80, Form("Out of range = %d", total - inRange));
	}

	// ---------------------
	// Pseudorapidity
	// ---------------------
	{
		// Create histogram
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = Pseudorapidity.frame(-8, 8);
		frame->SetTitle((string("Electrons #eta")+sufix).c_str());
		DataCut.plotOn(frame, DrawOption("BX"), FillColor(color));
		frame->SetMinimum(1);
		frame->GetXaxis()->SetTitle("#eta");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");

		// Save histogram
		outFile->cd();
		frame->getHist()->Write("ElectronEtaDistribution");

		int inRange = DataCut.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= Pseudorapidity && Pseudorapidity <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.65, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.65, 0.80, Form("Out of range = %d", total - inRange));
	}

	// ---------------------
	// Momentum Magnitude
	// ---------------------
	{
		// Create histogram
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = MomentumMagnitude.frame(0, 100.);
		frame->SetTitle((string("Electrons p")+sufix).c_str());
		DataCut.plotOn(frame, DrawOption("BX"), FillColor(color));
		frame->SetMinimum(1);
		frame->GetXaxis()->SetTitle("p (MeV/c)");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");

		// Save histogram
		outFile->cd();
		frame->getHist()->Write("ElectronMomentumDistribution");

		int inRange = DataCut.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= MomentumMagnitude && MomentumMagnitude <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.65, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.65, 0.80, Form("Out of range = %d", total - inRange));
	}

	// ---------------------
	// 2D Hist
	// ---------------------
	{
		// Create histogram
		TCanvas* c1  = new TCanvas;
		TH2* hist2d;
		hist2d = dynamic_cast<TH2*>(DataCut.createHistogram("hist", PositionX, RooFit::Binning(50, -2, 2), RooFit::YVar(PositionY, RooFit::Binning(50, -2, 2))));
		hist2d->SetTitle((string("Electrons")+sufix).c_str());
		hist2d->Draw("colz") ;
		hist2d->GetXaxis()->SetTitle("X (mm)");
		hist2d->GetYaxis()->SetTitle("Y (mm)");

		// Save histogram
		outFile->cd();
		hist2d->Write("Electron2DDistribution");
		
		gStyle->SetOptStat(0);
		/*
		//Box with infos
		TBox *b = new TBox(0.5, 0.5, 0.85, 0.8);
		b->SetFillColor(kRed);
		b->SetLineColor(kBlack);
		b->SetLineWidth(8.);
		b->Draw();
		*/

		text->DrawLatex(0.65, 0.86, Form("Entries = %f", DataCut.sumEntries()));
	}

	// ---------------------
	// 2D Hist side
	// ---------------------
	{
		// Create histogram
		TCanvas* c1  = new TCanvas;
		TH2* hist2d;
		hist2d = dynamic_cast<TH2*>(DataCut.createHistogram("hist", PositionZ, RooFit::Binning(50, -1, 1), RooFit::YVar(PositionY, RooFit::Binning(50, -4, 4))));
		hist2d->SetTitle((string("Electrons")+sufix).c_str());
		hist2d->Draw("colz") ;
		hist2d->GetXaxis()->SetTitle("Z (mm)");
		hist2d->GetYaxis()->SetTitle("Y (mm)");

		// Save histogram
		outFile->cd();
		hist2d->Write("Electron2DSideDistribution");
		
		gStyle->SetOptStat(0);
		/*
		//Box with infos
		TBox *b = new TBox(0.5, 0.5, 0.85, 0.8);
		b->SetFillColor(kRed);
		b->SetLineColor(kBlack);
		b->SetLineWidth(8.);
		b->Draw();
		*/

		text->DrawLatex(0.65, 0.86, Form("Entries = %f", DataCut.sumEntries()));
	}

	cout << "File created \n";
	file0->Close();
	outFile->Close();
}