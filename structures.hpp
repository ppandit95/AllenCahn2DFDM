/*
 * structures.hpp
 *
 *  Created on: 05-Apr-2021
 *      Author: pushkar
 */

#ifndef STRUCTURES_HPP_
#define STRUCTURES_HPP_
#include <vector>

struct Parameters{
public :
	//Simulation Parameters
	unsigned int Nx;
	unsigned int Ny;
	unsigned int dx;
	unsigned int dy;
	unsigned int radius;
	double TimeStep;
	unsigned int FinalTime;
	std::vector<unsigned int> steps_param;


	//Material Parameters
	double tau;
	double gamma;
	double epsilon;
	double L;
};
struct FDM_Constants{
	double C1;//Coefficient of phi[i][j] term at time t
	double C2;//Coefficient of phi[i-1][j] and phi[i+1][j] at time t
	double C3;//Coefficient of phi[i][j+1] and phi[i][j-1]
	double C4;//Coefficient of phi[i][j]*phi[i][j] term at time t
	double C5;//Coefficient of phi[i][j]*phi[i][j]*phi[i][j] term at time t
};
#define PHI_MAX 3.5;



#endif /* STRUCTURES_HPP_ */
