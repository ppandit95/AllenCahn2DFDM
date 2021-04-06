/*
 * ParamFactory.cpp
 *
 *  Created on: 06-Apr-2021
 *      Author: pushkar
 */

#include<vector>
#include<string>
#include"config4cpp/Configuration.h"
#include"ParamFactory.hpp"
#include"structures.hpp"
using namespace config4cpp;

void ParamFactory::ParseParams(Parameters& param){
	cfg = Configuration::create();
	scope = "";
	configFile = "parameters.cfg";
	try{
		cfg->parse(configFile);
		Nx = cfg->lookupInt(scope,"Nx");
		Ny = cfg->lookupInt(scope,"Ny");
		dx = cfg->lookupInt(scope,"dx");
		dy = cfg->lookupInt(scope,"dy");
		radius = cfg->lookupInt(scope,"radius");
		TimeStep = cfg->lookupFloat(scope,"TimeStep");
		FinalTime = cfg->lookupInt(scope,"FinalTime");
		cfg->lookupList(scope,"steps",Steps);
		for(unsigned int i=0;i<steps.length();i++)
			steps[i] = atoi(Steps[i]);

		tau = cfg->lookupFloat(scope,"tau");
		gamma = cfg->lookupFloat(scope,"gamma");
		epsilon = cfg->lookupFloat(scope,"epsilon");
		L = cfg->lookupFloat(scope,"L");
	}catch(const ConfigurationException& ex){
		std::cerr<<ex.c_str()<<std::endl;
		cfg->destroy();
	}
	param.Nx = Nx;
	param.Ny = Ny;
	param.dx = dx;
	param.dy = dy;
	param.radius = radius;
	param.TimeStep = TimeStep;
	param.FinalTime = FinalTime;
	for(unsigned int i=0;i<steps.length();i++)
		param.steps_param[i] = steps[i];

	param.tau = tau;
	param.gamma = gamma;
	param.epsilon = epsilon;
	param.L = L;
	cfg->destroy();
}



