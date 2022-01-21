/*
	* Author : corentin.hiver@ijclab.in2p3.fr
	* Goal : make an approximate spectra of emitted gamma following d+X reaction, X being Be, Al, O and U
	* Modifications log :
	*	21/01/2022 add the relative abundance of each atoms in the target
	*
*/

#include "Load_file.h"

void GammaSpectra()
{
	// ------------- Sample informations ------------ //
	//Target of UxOy (typically UO3)
	Float_t Ustoech(1), Ostoech (3); //UxOy chemical representation
	Float_t thicknessTarget(5 * µm), densityTarget(10 * (mg/cm3)), atomicNumberTarget((Ustoech*235+Ostoech*16)/(Ostoech+Ustoech));
	Float_t targetAbundance = cNa*thicknessTarget*densityTarget/atomicNumberTarget; //in atoms/m2
	Float_t Uabundance(atomicThicknessTarget/4), Oabundance(3*atomicThicknessTarget/4);
	//Be backing
	Float_t thicknessBeBacking(10 * µm), densityBeBacking(1.8 * (mg/cm3)), atomicNumberBeBacking(9.);
	Float_t Beabundance = cNa*thicknessBeBacking*densityBeBacking/atomicNumberBeBacking;
	//Al backing
	Float_t thicknessAlBacking(1.5 * µm), densityAlBacking(1.8 * (mg/cm3)), atomicNumberAlBacking(27.);
	Float_t Alabundance = cNa*thicknessAlBacking*densityAlBacking/atomicNumberAlBacking;

	Float_t Ucoeff  = 1;
	Float_t Ocoeff  = Oabundance/Uabundance;
	Float_t Becoeff = Beabundance/Uabundance;
	Float_t Alcoeff = Alabundance/Uabundance;
	// ------------- Instanciate graphs --------------//
	const char *name = "Gamma total spectrum";
	auto c1 = new TCanvas(name, name);
	TGraph *BeGraph = new TGraph();
	TGraph *AlGraph = new TGraph();
	TGraph *CGraph = new TGraph();
	TGraph *OGraph = new TGraph();
	TGraph *U235Graph = new TGraph();
	// ------------------ Load Data ------------------//
	loadSpectra ("spectra/d+Be.o.spectra3", Ejectile::Gamma, BeGraph, Becoeff);
	loadSpectra ("spectra/d+Al.o.spectra3", Ejectile::Gamma, AlGraph, Alcoeff);
	//loadSpectra ("spectra/d+C.o.spectra3", Ejectile::Gamma, CGraph);
	loadSpectra ("spectra/d+O.o.spectra3", Ejectile::Gamma, OGraph,Ocoeff);
	loadSpectra ("fissionU235/d+U235.o.spectra", Ejectile::Gamma, U235Graph, Ucoeff);

	auto *legend = new TLegend();

	U235Graph -> Draw("apl");
	U235Graph -> SetTitle("Gamma total spectrum for some d+X reactions");
	U235Graph -> GetXaxis() -> SetTitle("Energy (MeV)");
	U235Graph -> GetYaxis() -> SetTitle("Yield");
	U235Graph -> GetYaxis() -> SetRangeUser(1e-6,3e3);
	U235Graph -> GetXaxis() -> SetRangeUser(0,5);

	U235Graph -> SetLineColor(kCyan);
	legend -> AddEntry(U235Graph, "d + U235");

	AlGraph -> Draw("SAME pl");
	AlGraph -> SetLineColor(kGreen);
	legend -> AddEntry(AlGraph, "d + Al");

	BeGraph -> Draw("SAME pl");
	BeGraph -> SetLineColor(kBlue);
	legend -> AddEntry(BeGraph, "d + Be");

	// CGraph -> Draw("SAME pl");
	// CGraph -> SetLineColor(kBlack);
	// legend -> AddEntry(CGraph, "d + C");

	OGraph -> Draw("SAME pl");
	OGraph -> SetLineColor(kMagenta);
	legend -> AddEntry(OGraph, "d + O");
	gPad -> SetLogy(true);
	gPad -> SetLogx(false);

	legend -> Draw();

}

/*

	A titre d'archivage :

1 : récupérer les deux vectors d'un std::array<std::vector<Double_t>,2> :

void getVectors(const std::array<std::vector<Double_t>,2> *data)
{
	Double_t *x = &(data -> at(0)[0]);
	Double_t *y = &(data -> at(1)[0]);

}

passer en argument une référence vers le tableau getVectors(&tableau)

2 : Old Code

std::array<std::vector<Double_t>,2> loadSpectra (std::string file = "", std::string particle = "")
{
	std::vector<Double_t> Energy, Yield;
	std::ifstream dataFile (file);

	if (dataFile)
	{
		std::string line ;
		bool read = false;
		bool gamma = false;
		Int_t nb_data = true;
		while (std::getline(dataFile,line))
		{
			if (line.size() > 3) // only read lines with at least one character
			{
				if (line == " Spectra for outgoing gamma   " and particle == "gamma") gamma = true;
				if (line == " Spectra for outgoing neutron " and particle == "gamma") gamma = false;
				if (read and gamma)
				{
					Energy.push_back(stod(line.substr(0,8))); // In MeV
					Yield.push_back(stod(line.substr(9,11))); // Yield
				}


				if (line.substr(0,8) == "  Energy") read = true;// tags the beggining of the data
			}
		}
	}
	else {printStr("File not found !!");}

	std::array<std::vector<Double_t>,2> ret = {Energy,Yield};
	return ret;
}

	Double_t test [Be_nb_data];
	*test = (BeSpectra[0][0]);

	for (auto &t : BeSpectra[0]) std::cout << t << std::endl;

	Double_t *AlEnergy = &(AlSpectra[0][0]);
	Double_t *AlYield = &(AlSpectra[0][0]);
	Int_t Al_nb_data = AlSpectra . at(0) . size();	*/

	/*const char *name = "Gamma total spectrum Be";
	auto c1 = new TCanvas(name,name);

	TGraph *gr = new TGraph(Be_nb_data,BeEnergy,BeYield);
	gr -> Draw("AP");
	gr -> SetMarkerColor(kRed);
	gr -> SetMarkerStyle(kPlus);
	//gPad -> SetLogy(true);
	//gPad -> SetLogx(false);

	//const char *name2 = "Gamma total spectrum Al";
	//auto c2 = new TCanvas(name2,name2);

	TGraph *gr2 = new TGraph(Al_nb_data,AlEnergy,AlYield);
	gr2 -> Draw("AP SAME");
	//gr2 -> SetLineColor(kGreen);
	//gr2 -> SetLineWidth(2);
	gr2 -> SetMarkerColor(kGreen);
	gr2 -> SetMarkerStyle(kMultiply);
	gPad -> SetLogy(true);
	gPad -> SetLogx(false);

*/
