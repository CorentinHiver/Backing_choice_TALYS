#include "Load_file.h"

void ProtonSpectra()
{
	const char *name = "Proton total spectrum";
	auto c1 = new TCanvas(name, name);
	TGraph *BeGraph = new TGraph();
	TGraph *AlGraph = new TGraph();
	TGraph *CGraph = new TGraph();
	TGraph *OGraph = new TGraph();	
	TGraph *U235Graph = new TGraph();
	loadSpectra ("spectra/d+Be.o.spectra", Ejectile::Proton, BeGraph);
	loadSpectra ("spectra/d+Al.o.spectra", Ejectile::Proton, AlGraph);
	loadSpectra ("spectra/d+C.o.spectra", Ejectile::Proton, CGraph);
	loadSpectra ("spectra/d+O.o.spectra3", Ejectile::Proton, OGraph);
	loadSpectra ("fissionU235/d+U235.o.spectra", Ejectile::Proton, U235Graph);

	auto *legend = new TLegend();

	U235Graph -> Draw("apc");
	U235Graph -> SetTitle("Proton total spectrum for some d+X reactions");
	U235Graph -> GetXaxis() -> SetTitle("Energy (MeV)");
	U235Graph -> GetYaxis() -> SetTitle("Yield");
	U235Graph -> GetYaxis() -> SetRangeUser(1e-3,1e3);

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

	OGraph -> Draw("SAME");
	OGraph -> SetLineColor(kMagenta);
	legend -> AddEntry(OGraph, "d + O");
	gPad -> SetLogy(true);
	gPad -> SetLogx(false);

	legend -> Draw();	
}