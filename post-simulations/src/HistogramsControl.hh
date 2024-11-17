#ifndef HistogramsControl_HH
#define HistogramsControl_HH

#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TPaletteAxis.h>
#include <filesystem>
#include <ostream>
using namespace std;

class HistogramsControl
{
private:
	string savePath {"plots/"};
	string saveExtension {".png"};

	void CreateDirectory()
	{
		if (!std::filesystem::exists(savePath))
			std::filesystem::create_directory(savePath);
	}

public:
	HistogramsControl() {}
	HistogramsControl(string path, string extension) {savePath = path; saveExtension = extension;}
	~HistogramsControl() {}

	void SetSavePath(string path) {savePath = path;}
	void SetSaveExtension(string extension) {saveExtension = extension;}

	void DrawAndSave1D(TH1& h, Option_t* option = "", string logInAxes = "", bool showStats = false)
	{
		TCanvas c1("c1", "c1", 600, 600);
		c1.SetLeftMargin(0.1);
		
		if (logInAxes.find('x') != std::string::npos)
			c1.SetLogx();
		if (logInAxes.find('y') != std::string::npos)
			c1.SetLogy();
		if (logInAxes.find('z') != std::string::npos)
			c1.SetLogz();

		h.SetStats(showStats);
		
		h.Draw(option);
		h.Write();

		CreateDirectory();
		c1.SaveAs((savePath + string(h.GetName()) + saveExtension).c_str());
	}

	void DrawAndSave2D(TH2& h, Option_t* option = "", string logInAxes = "", bool showStats = false)
	{
		TCanvas c1("c1", "c1", 600, 600);
		c1.SetRightMargin(0.15);

		if (logInAxes.find('x') != std::string::npos)
			c1.SetLogx();
		if (logInAxes.find('y') != std::string::npos)
			c1.SetLogy();
		if (logInAxes.find('z') != std::string::npos)
			c1.SetLogz();

		h.GetXaxis()->SetTitleOffset(1.5);

		h.SetStats(showStats);
		
		h.Draw(option);
		
		// Check if has option "z" to draw the z-axis
		if (string(option).find('z') != std::string::npos)
		{
			c1.SetRightMargin(0.20);
			gPad->Update();
			TPaletteAxis* palette = (TPaletteAxis*)h.GetListOfFunctions()->FindObject("palette");
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.93);
		}

		h.Write();
		CreateDirectory();
		c1.SaveAs((savePath + string(h.GetName()) + saveExtension).c_str());
	}

	void DrawAndSave3D(TH3& h, Option_t* option = "")
	{
		TCanvas c1("c1", "c1", 800, 800);

		h.GetXaxis()->SetTitleOffset(1.5);
		h.GetYaxis()->SetTitleOffset(2);
		h.GetZaxis()->SetTitleOffset(1.5);
		
		h.SetStats(false);

		h.SetMarkerColor(kRed);
		h.Draw(option);

		// Check if has option "z" to draw the z-axis
		if (string(option).find('z') != std::string::npos)
		{
			c1.SetRightMargin(0.15);
			gPad->Update();
			TPaletteAxis* palette = (TPaletteAxis*)h.GetListOfFunctions()->FindObject("palette");
			palette->SetX1NDC(0.88);
			palette->SetX2NDC(0.93);
		}

		gPad->SetPhi(30+180);

		h.Write();
		CreateDirectory();
		c1.SaveAs((savePath + string(h.GetName()) + saveExtension).c_str());
	}
};

#endif