
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef __TKPHYSICS__
#define __TKPHYSICS__

namespace TKPhysicalConstant
{
	//TKPhysicalConstant is defined in the SI system of unit.

	const int speed_of_light_in_vacuum = 299792458;				//c [m/s]
	const double permeability_of_free_space = 4.0E-7 * M_PI;		//mu [H/m]
	const double permittivity_of_free_space = 8.854187817E-12;		//epsilon_0 [F/m]
	const double boltzman_constant = 1.38064852E-23;			//k_B [J/K]
	const double elementary_charge = 1.6021766208E-19;			//e [C]

#ifdef _USE_TKPHYSICALCONSTANT_SHORT_NAME
	const double &c = speed_of_light_in_vacuum;
	const double &mu_0 = permeability_of_free_space;
	const double &eps_0 = permittivity_of_free_space;
	const double &k_B = boltzman_constant;
	const double &e = elementary_charge;
#endif
}

class TKParticlePalameter
{
public:
	double density;
	double temperature;
	double mass;
};

class TKPlasmaParameter
{
public:

};

class TKPlasma
{
public:
	TKParticlePalameter neutral, electron, ion;
	double n_e = electron.density;

};

#endif