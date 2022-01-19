#include "Load_file.h"

void ElasticAngleDistrib()
{
	const char *name = "Deuteron elastic scattering";
	//auto c1 = new TCanvas(name, name);
	TGraph *BeGraph = new TGraph();
	TGraph *AlGraph = new TGraph();
	TGraph *CGraph = new TGraph();
	TGraph *OGraph = new TGraph();	
	TGraph *U235Graph = new TGraph();
	loadAngleElastic ("angle/d+Be.o.angle", BeGraph);
	loadAngleElastic ("angle/d+Al.o.angle", AlGraph);
	loadAngleElastic ("angle/d+C.o.angle", CGraph);
	loadAngleElastic ("angle/d+O.o.angle", OGraph);
	loadAngleElastic ("angle/d+U235.o.angle", U235Graph);

	TString Graph_Title = "Deuteron elastic scattering for some d+X reactions;Energy (MeV);Yield";

	myMultiGraph *gr = new myMultiGraph(name,Graph_Title, U235Graph,"d + U235","ac");
	gr -> addEntry(AlGraph,"d + Al");
	gr -> addEntry(BeGraph,"d + Be");
	gr -> addEntry(CGraph, "d + C");
	gr -> addEntry(OGraph, "d + O");

	gr -> setYRange(1,1e5);

	gPad -> SetLogy(true);
	gPad -> SetLogx(false);

}















/*
A titre d'archivage : 
	
	...

	// auto *legend = new TLegend();

	// U235Graph -> Draw("ac");
	// U235Graph -> SetTitle("Deuteron elastic scattering for some d+X reactions");
	// U235Graph -> GetXaxis() -> SetTitle("Energy (MeV)");
	// U235Graph -> GetYaxis() -> SetTitle("Yield");
	// U235Graph -> GetYaxis() -> SetRangeUser(1,1e5);

	// U235Graph -> SetLineColor(kCyan);
	// legend -> AddEntry(U235Graph, "d + U235");

	// AlGraph -> Draw("SAME");
	// AlGraph -> SetLineColor(kGreen);
	// legend -> AddEntry(AlGraph, "d + Al");

	// BeGraph -> Draw("SAME");
	// BeGraph -> SetLineColor(kBlue);
	// legend -> AddEntry(BeGraph, "d + Be");

	// CGraph -> Draw("SAME");
	// CGraph -> SetLineColor(kBlack);
	// legend -> AddEntry(CGraph, "d + C");

	// OGraph -> Draw("SAME");
	// OGraph -> SetLineColor(kMagenta);
	// legend -> AddEntry(OGraph, "d + O");

	...

	// legend -> Draw();	

*/