#include "Load_file.h"

void ProtonSpectraDDX()
{

	TGraph *BeGraph = new TGraph();
	TGraph *AlGraph = new TGraph();
	TGraph *CGraph = new TGraph();
	TGraph *OGraph = new TGraph();	
	TGraph *U235Graph = new TGraph();
	double angle = 120.000;
	loadDdxSpectra ("ddx/d+Be.o.ddxmode3", Ejectile::Proton, angle, BeGraph);
	loadDdxSpectra ("ddx/d+Al.o.ddxmode3", Ejectile::Proton, angle, AlGraph);
	loadDdxSpectra ("ddx/d+C.o.ddxmode3", Ejectile::Proton, angle, CGraph);
	loadDdxSpectra ("ddx/d+O.o.ddxmode3", Ejectile::Proton, angle, OGraph);
	loadDdxSpectra ("ddx/d+U235.o.ddxmode3", Ejectile::Proton, angle, U235Graph);

	TString name = DoubleToTString(angle,2,"Proton_differential_cross_section_at.","_deg");
	auto c1 = new TCanvas(name, name,1100,800);


	auto *legend = new TLegend();


	OGraph -> Draw("ac");
	OGraph -> SetLineColor(kMagenta);
	OGraph -> SetTitle(DoubleToTString(angle, 2, "Proton differential cross section at ", "#circ"));
	OGraph -> GetXaxis() -> SetTitle("Energy (MeV)");
	OGraph -> GetYaxis() -> SetTitle("Yield");
	OGraph -> GetYaxis() -> SetRangeUser(1e-3,5e3);
	legend -> AddEntry(OGraph, "d + O");


	U235Graph -> Draw("SAME");
	U235Graph -> SetLineColor(kCyan);
	legend -> AddEntry(U235Graph, "d + U235");

	AlGraph -> Draw("SAME");
	AlGraph -> SetLineColor(kGreen);
	legend -> AddEntry(AlGraph, "d + Al");

	BeGraph -> Draw("SAME");
	BeGraph -> SetLineColor(kBlue);
	legend -> AddEntry(BeGraph, "d + Be");

	CGraph -> Draw("SAME");
	CGraph -> SetLineColor(kBlack);
	legend -> AddEntry(CGraph, "d + C");

	gPad -> SetLogy(true);
	gPad -> SetLogx(false);

	legend -> Draw();	
}
