//#include <string>
using namespace RooFit;

void energy()
{
	TFile* file0    = TFile::Open("../build/results/output_0.root");
	TTree* DataTree = (TTree*)file0->Get(("Particles"));
	
	RooRealVar  ParticleID               ("fParticleID",               "ParticleID", 0, RooNumber::infinity());
	RooRealVar  KinectEnergy             ("fKinectEnergy",             "KinectEnergy", 0, RooNumber::infinity());
	RooRealVar  CosTheta                 ("fCosTheta",                 "CosTheta", -1., 1.);
	RooRealVar  Phi                      ("fPhi",                      "Phi", -TMath::Pi(), TMath::Pi());
	RooRealVar  LongitudinalPolarization ("fLongitudinalPolarization", "LongitudinalPolarization", -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar  PositionX                ("fPositionX",                "PositionX", -RooNumber::infinity(), RooNumber::infinity());
	RooRealVar  PositionY                ("fPositionY",                "PositionY", -RooNumber::infinity(), RooNumber::infinity());

	RooDataSet DataGamma("data", "data", DataTree, RooArgSet(ParticleID, KinectEnergy, CosTheta, Phi, PositionX, PositionY), "fParticleID==5");

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

	//
	// Energy Plot
	//
	{
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = KinectEnergy.frame(0., .1);
		frame->SetTitle((string("Electrons")+sufix).c_str());
		DataGamma.plotOn(frame, DrawOption("BE"), FillColor(color));
		frame->SetMaximum(40000);
		frame->GetXaxis()->SetTitle("Energy (MeV)");
		frame->GetYaxis()->SetTitle("Events / ( 0.05 )");
		frame->Draw();
		int inRange = DataGamma.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= fKinectEnergy && fKinectEnergy <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.6, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.6, 0.80, Form("Out of range = %d", total - inRange));
		c1->SaveAs("electrons+.png");
	}

	//
	// Energy Log Plot
	//
	{
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = KinectEnergy.frame(0., 0.1);
		frame->SetTitle((string("Electrons")+sufix).c_str());
		DataGamma.plotOn(frame, DrawOption("BX"), FillColor(color));
		//frame->GetXaxis()->SetRangeUser(0, 0.1);
		frame->SetMinimum(1);
		frame->SetMaximum(1e5);
		frame->GetXaxis()->SetTitle("Energy (MeV)");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");
		int inRange = DataGamma.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= fKinectEnergy && fKinectEnergy <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.6, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.6, 0.80, Form("Out of range = %d", total - inRange));
		c1->SetLogy();
		c1->SaveAs("electrons+log.png");
	}

	//
	// Full Energy Log Plot
	//
	{
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = KinectEnergy.frame(0., 1.);
		frame->SetTitle((string("Electrons")+sufix).c_str());
		DataGamma.plotOn(frame, DrawOption("BX"), FillColor(color));
		//frame->GetXaxis()->SetRangeUser(0, 0.1);
		frame->SetMinimum(1);
		frame->SetMaximum(1e5);
		frame->GetXaxis()->SetTitle("Energy (MeV)");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");
		int inRange = DataGamma.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= fKinectEnergy && fKinectEnergy <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.6, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.6, 0.80, Form("Out of range = %d", total - inRange));
		c1->SetLogy();
		c1->SaveAs("electrons+logfull.png");
	}

	// 2D Hist
	{
		TCanvas* c1  = new TCanvas;
		TH2* hist2d;
		hist2d = dynamic_cast<TH2*>(DataGamma.createHistogram("hist", PositionX, RooFit::Binning(40, -40, 40), RooFit::YVar(PositionY, RooFit::Binning(40, -40, 40))));
		hist2d->SetTitle((string("Electrons")+sufix).c_str());
		hist2d->Draw("colz") ;
		hist2d->GetXaxis()->SetTitle("X (mm)");
		hist2d->GetYaxis()->SetTitle("Y (mm)");
		
		gStyle->SetOptStat(0);
		/*
		//Box with infos
		TBox *b = new TBox(0.5, 0.5, 0.85, 0.8);
		b->SetFillColor(kRed);
		b->SetLineColor(kBlack);
		b->SetLineWidth(8.);
		b->Draw();
		*/

		text->DrawLatex(0.65, 0.86, Form("Entries = %d", DataGamma.sumEntries()));
		c1->SaveAs("electrons+_pos.png");
	}

	// Cos
	{
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = CosTheta.frame(-1, 1);
		frame->SetTitle((string("Electrons Cos(#theta)")+sufix).c_str());
		DataGamma.plotOn(frame, DrawOption("BX"), FillColor(color));
		frame->SetMinimum(1);
		frame->SetMaximum(35000);
		frame->GetXaxis()->SetTitle("Cos(#theta)");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");
		int inRange = DataGamma.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= fCosTheta && fCosTheta <="
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.65, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.65, 0.80, Form("Out of range = %d", total - inRange));
		c1->SaveAs("electrons+costheta.png");
	}

	// Phi
	{
		TCanvas* c1  = new TCanvas;
		RooPlot* frame = Phi.frame(-TMath::Pi(), TMath::Pi());
		frame->SetTitle((string("Electrons #phi")+sufix).c_str());
		DataGamma.plotOn(frame, DrawOption("BX"), FillColor(color));
		frame->SetMinimum(1);
		frame->SetMaximum(2500);
		frame->GetXaxis()->SetTitle("#phi (rad)");
		frame->GetYaxis()->SetTitle("Events ( 0.05 )");
		frame->Draw("B");
		int inRange = DataGamma.sumEntries(
			(to_string(frame->GetXaxis()->GetXmin()) + "<= fPhi && fPhi <=" 
			+ to_string(frame->GetXaxis()->GetXmax())).c_str());
		text->DrawLatex(0.65, 0.85, Form("Entries = %d", inRange));
		text->DrawLatex(0.65, 0.80, Form("Out of range = %d", total - inRange));
		c1->SaveAs("electrons+phi.png");
	}
}