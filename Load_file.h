#include "/homeijclab/hiver/CODES/c++/Calculs_Cible/coROOTlib.h"

void loadSpectra (std::string file , Ejectile particle, TGraph *gr)
{
	std::ifstream dataFile (file);	

	if (dataFile)
	{
		std::string line ;
		bool read = false;
		bool gamma = false;
		bool proton = false;
		while (std::getline(dataFile,line)) 
		{
			if (line.size() > 3) // only read lines with at least three characters
			{
				//Gamma spectra : 
				if (line == " Spectra for outgoing gamma   " and particle == Ejectile::Gamma) gamma = true;
				if (line == " Spectra for outgoing neutron " and particle == Ejectile::Gamma) gamma = false;
				if (read and gamma)
				{
					gr -> SetPoint(gr -> GetN(), stod(line.substr(0,8)),stod(line.substr(9,11)));
				}
				if (line.substr(0,8) == "  Energy" and gamma) read = true;// tags the beggining of the data

				//Proton spectra :
				if (line == " Spectra for outgoing proton  " and particle == Ejectile::Proton) proton = true;
				if (line == " Spectra for outgoing deuteron" and particle == Ejectile::Proton) proton = false;
				if (read and proton)
				{
					gr -> SetPoint(gr -> GetN(), stod(line.substr(0,8)),stod(line.substr(9,11)));
				}
				if (line.substr(0,8) == "  Energy" and proton) read = true;// tags the beggining of the data
				
			}
		}
	}
	else {printStr(file +" not found !!");}
}

void loadDdxSpectra(std::string file , Ejectile particle, Double_t Angle, TGraph *gr)
{
	/*
		Reads talys files with ddxmode3 keyword only
	*/
	std::ifstream dataFile (file);	

	if (dataFile)
	{
		std::string line ;

		bool read = false;

		bool neutron = false;
		bool proton = false;
		bool deuteron = false;

		bool angle = false; // Reading at the requested angle

		bool section = false; //reading the 9. section : " 9. Double-differential cross sections per outgoing angle"

		while (std::getline(dataFile,line)) 
		{
			if (line.size() > 3) // only read lines with at least three characters
			{
				if (line ==  " 9. Double-differential cross sections per outgoing angle")section = true;
				//Proton spectra :
				if (line.substr(0,30) == " DDX for outgoing proton   at " and particle == Ejectile::Proton and section == true) 
					{
						proton = true;
						if (stod(line.substr(30,7)) == Angle) angle = true;
						else angle = false;
					}
				if (line.substr(0,31) == " DDX for outgoing deuteron at " and particle == Ejectile::Proton) proton = false;
				if (read and proton and angle)
				{
					gr -> SetPoint(gr -> GetN(), stod(line.substr(0,8)),stod(line.substr(9,12)));
				}
				if (line.substr(0,9) == "    E-out" and proton and angle) read = true;// tags the beggining of the data
				
			}
		}
	}
	else {printStr(file + " not found !!");}
}


void loadAngleElastic(std::string file, TGraph *gr)
{
	std::ifstream dataFile (file);

	if (dataFile)
	{
		std::string line ;

		bool read = false;

		bool neutron = false;
		bool proton = false;
		bool deuteron = false;
		bool triton = false;

		Double_t Angle = 0;

		bool section = false; //reading the 8a2. section : " 8a2. Elastic scattering angular distribution"

		while (std::getline(dataFile,line)) 
		{
			if (line.size() >3 )
			{
				std::string header = " Angle        Total            Direct       Compound       c.s/Rutherford";
				if (line == " 8a2. Elastic scattering angular distribution") read = true;
				else if (line ==  " 8b2. Inelastic angular distributions") read = false;
				else if (read and line != header) 
					gr -> SetPoint(gr -> GetN(), stod(line.substr(0,6)),stod(line.substr(11,11)));
			}
		}
	}
}

void loadDdxSpectra2D(std::string file , Ejectile particle, TGraph2D *gr)
{
	/*
		Reads talys files with ddxmode3 keyword only
	*/
	std::ifstream dataFile (file);	

	if (dataFile)
	{
		std::string line;

		bool neutron = false;
		bool proton = false;
		bool deuteron = false;
		bool triton = false;

		Double_t Angle = 0;

		bool section = false; //reading the 9. section : " 9. Double-differential cross sections per outgoing angle"

		while (std::getline(dataFile,line)) 
		{
			if (line.size() > 3) // only read lines with at least three characters
			{
				if (line ==  " 9. Double-differential cross sections per outgoing angle") section = true;

				std::string angleHeader = "    E-out    Total      Direct     Pre-equil. Mult. preeq   Compound";

				//-----------------------//
				//--- Neutron spectra ---//
				//-----------------------//

				if (particle == Ejectile::Neutron and section)
				{
					if (line.substr(0,17) == " DDX for outgoing")
					{
						if (line.substr(17,10) == " neutron  ")
						{
							neutron = true;
							Angle = stod(line.substr(30,7));
						}
						else{neutron = false;}
					}

					else if (neutron)
					{
						if (line != angleHeader)
							gr -> SetPoint(gr -> GetN(), stod(line.substr(0,8)), Angle, stod(line.substr(9,12)));
					}
				}


				//----------------------//
				//--- Proton spectra ---//
				//----------------------//

				else if (particle == Ejectile::Proton and section)
				{
					if (line.substr(0,17) == " DDX for outgoing")
					{
						if (line.substr(17,10) == " proton   ")
						{
							proton = true;
							Angle = stod(line.substr(30,7));
						}
						else{proton = false;}
					}

					else if (proton)
					{
						if (line != angleHeader)
							gr -> SetPoint(gr -> GetN(), stod(line.substr(0,8)), Angle, stod(line.substr(9,12)));
					}
				}
				

				//------------------------//
				//--- Deuteron spectra ---//
				//------------------------//

				else if (particle == Ejectile::Deuteron and section)
				{
					if (line.substr(0,17) == " DDX for outgoing")
					{
						if (line.substr(17,10) == " deuteron ")
						{
							deuteron = true;
							Angle = stod(line.substr(30,7));
						}
						else{deuteron = false;}
					}

					else if (deuteron)
					{
						if (line != angleHeader)
							gr -> SetPoint(gr -> GetN(), stod(line.substr(0,8)), Angle, stod(line.substr(9,12)));
					}
				}

				//----------------------//
				//--- Triton spectra ---//
				//----------------------//
				
				else if (particle == Ejectile::Triton and section)
				{
					if (line.substr(0,17) == " DDX for outgoing")
					{
						if (line.substr(17,10) == " triton   ")
						{
							triton = true;
							Angle = stod(line.substr(30,7));
						}
						else{triton = false;}
					}

					else if (triton)
					{
						if (line != angleHeader)
							gr -> SetPoint(gr -> GetN(), stod(line.substr(0,8)), Angle, stod(line.substr(9,12)));
					}
				}
				else if (section) {printStr("Particle not found");}
				else{//not in section 9
				}
			}
		}
	}
	else {printStr(file + " not found !!");}
}