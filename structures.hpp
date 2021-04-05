/*
 * structures.hpp
 *
 *  Created on: 05-Apr-2021
 *      Author: pushkar
 */

#ifndef STRUCTURES_HPP_
#define STRUCTURES_HPP_

struct Parameters{
public :
	//Simulation Parameters
	unsigned int Nx;//Domain Size in xDirection
	unsigned int Ny;//Domain Size in YDirection
	unsigned int dx;//Grid Spacing in xDirection
	unsigned int dy;//Grid Spacing in yDirection
	unsigned int radius;//Radius of the initial seed
	double TimeStep;//Temporal step size
	double FinalTime;//Final time step of the simulation

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



#endif /* STRUCTURES_HPP_ */
