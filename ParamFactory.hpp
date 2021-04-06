/*
 * ParamFactory.hpp
 *
 *  Created on: 06-Apr-2021
 *      Author: pushkar
 */

#ifndef PARAMFACTORY_HPP_
#define PARAMFACTORY_HPP_

#include<iostream>
#include"config4cpp/Configuration.h"
#include"structures.hpp"
using namespace config4cpp;

class ParamFactory{
private:
	Configuration * cfg ;
	const char* scope;
	const char* configFile;
	int Nx;
	int Ny;
	int dx;
	int dy;
	int radius;
	double TimeStep;
	int FinalTime;
	StringVector Steps;
	std::vector<int> steps;
	double tau;
	double gamma;
	double epsilon;
	double L;
public:
	void ParseParams(Parameters& param);
};




#endif /* PARAMFACTORY_HPP_ */
