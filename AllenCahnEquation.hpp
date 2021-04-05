/*
 * AllenCahnEquation.hpp
 *
 *  Created on: 05-Apr-2021
 *      Author: pushkar
 */

#ifndef ALLENCAHNEQUATION_HPP_
#define ALLENCAHNEQUATION_HPP_
#include "structures.hpp"
class AllenCahnEquation{
private:
	Parameters param;
	FDM_Constants consts;
	unsigned int node;
	double** phi;
public:
	AllenCahnEquation();
	~AllenCahnEquation();
	void run();
	void initialize_field();
	void setup_initial_profile();
	void output_initial_profile();
	void initialize_FDMConstants();
	void Evolve_with_FDM();
	void Evolve_on_boundaries(unsigned int j,unsigned int k);
	bool on_boundary(unsigned int j,unsigned int k);
	void Output_field(double tStep);
};



#endif /* ALLENCAHNEQUATION_HPP_ */
