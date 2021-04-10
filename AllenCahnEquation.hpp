/*
 * AllenCahnEquation.hpp
 *
 *  Created on: 05-Apr-2021
 *      Author: pushkar
 */

#ifndef ALLENCAHNEQUATION_HPP_
#define ALLENCAHNEQUATION_HPP_
#include "structures.hpp"
#define PHI_MAX 1.0;
#define PHI_MIN 0.0;
class AllenCahnEquation{
private:
	Parameters param;
	FDM_Constants consts;
	unsigned int center[2];
	double** phi;
	double** phitilde;//Variable to store updated value at each time step which is transfered to phi
public:
	AllenCahnEquation();
	AllenCahnEquation(Parameters& params);
	~AllenCahnEquation();
	void run();
	void setup();
	void initialize_field();
	void setup_initial_profile();
	void output_initial_profile();
	void initialize_FDMConstants();
	void Evolve_with_FDM();
	void Evolve_on_boundaries(unsigned int j,unsigned int k);
	bool on_boundary(unsigned int j,unsigned int k);
	void Output_field(unsigned int tStep);

};



#endif /* ALLENCAHNEQUATION_HPP_ */
