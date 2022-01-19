#include "Load_file.h"

void NeutronSpectraDDX2D()
{

	TGraph2D *Graph = new TGraph2D();
	loadDdxSpectra2D ("ddx/d+U235.o.ddxmode3", Ejectile::Neutron, Graph);

	TString name = "Neutron_differential_cross_section_for_U235";
	auto c1 = new TCanvas(name, name,1100,800);

	Graph -> Draw("surf2");
	Graph -> SetLineColor(kMagenta);
	Graph -> SetTitle("Neutron differential cross section for U235;Energy (MeV);Angle;Cross Section");
	//Graph -> GetZaxis() -> SetRangeUser(0.00000001,1e5);
	//Graph -> SetTitleSize(2);
	Graph -> GetXaxis() -> SetTitleSize(0.01);
	Graph -> GetYaxis() -> SetTitleSize(0.01);
	//gStyle -> SetTitleZSize(0.01);
	//legend -> AddEntry(AlGraph, "d + O");


	gPad -> SetLogy(false);
	gPad -> SetLogx(false);
	gPad -> SetLogz(true);

}