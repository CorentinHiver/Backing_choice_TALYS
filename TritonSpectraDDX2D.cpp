#include "Load_file.h"

void TritonSpectraDDX2D()
{

	TGraph2D *Graph = new TGraph2D();
	//loadDdxSpectra2D ("ddx/d+U235.o.ddxmode3", Ejectile::Triton, Graph);
	//loadDdxSpectra2D ("ddx/d+Be.o.ddxmode3", Ejectile::Triton, Graph);
	loadDdxSpectra2D ("ddx/d+Al.o.ddxmode3", Ejectile::Triton, Graph);

	//TString name = "Triton_differential_cross_section_for_U235";
	// TString name = "Triton_differential_cross_section_for_Be";
	TString name = "Triton_differential_cross_section_for_Al";

	auto c1 = new TCanvas(name, name,1100,800);

	//Graph -> Draw("surf2");
	Graph -> Draw("cont4z");
	Graph -> SetLineColor(kMagenta);
	//Graph -> SetTitle("Triton differential cross section for U235;Energy (MeV);Angle;Cross Section");
	//Graph -> SetTitle("Triton differential cross section for Be;Energy (MeV);Angle;Cross Section");
	Graph -> SetTitle("Triton differential cross section for Al;Energy (MeV);Angle;Cross Section");
	Graph -> GetZaxis() -> SetRangeUser(1e-3,1e3);
	//Graph -> SetTitleSize(2);
	Graph -> GetXaxis() -> SetTitleSize(0.01);
	Graph -> GetYaxis() -> SetTitleSize(0.01);
	//gStyle -> SetTitleZSize(0.01);
	//legend -> AddEntry(AlGraph, "d + O");


	gPad -> SetLogy(false);
	gPad -> SetLogx(false);
	gPad -> SetLogz(true);

}