/*
 * ParamFactory.cpp
 *
 *  Created on: 06-Apr-2021
 *      Author: pushkar
 */

#include<vector>
#include<string>
#include"config4cpp/Configuration.h"
#include"structures.hpp"
#include<iostream>
using namespace config4cpp;
/*
void ParamFactory::ParseParams(Parameters& param){
	Configuration* cfg = Configuration::create();
	const char* scope = "";
	const char* configFile = "parameters.cfg";
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
		for(unsigned int i=0;i<Steps.length();i++)
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
	for(unsigned int i=0;i<Steps.length();i++)
		param.steps_param[i] = steps[i];

	param.tau = tau;
	param.gamma = gamma;
	param.epsilon = epsilon;
	param.L = L;
	cfg->destroy();
}*/
int main(int argc,char** argv){
	StringVector Steps;
	Parameters param;
	std::vector<int> steps;
	Configuration* cfg = Configuration::create();
	const char* scope = "";
	const char* configFile = "parameters.cfg";
	try{
		cfg->parse(configFile);
		int Nx = cfg->lookupInt(scope,"Nx");
		int Ny = cfg->lookupInt(scope,"Ny");
		int dx = cfg->lookupInt(scope,"dx");
		int dy = cfg->lookupInt(scope,"dy");
		int radius = cfg->lookupInt(scope,"radius");
		double TimeStep = cfg->lookupFloat(scope,"TimeStep");
		int FinalTime = cfg->lookupInt(scope,"FinalTime");
		cfg->lookupList(scope, "steps", Steps);
		for(unsigned int i=0;i<Steps.length();i++)
			steps[i] = atoi(Steps[i]);

		double tau = cfg->lookupFloat(scope,"tau");
		double gamma = cfg->lookupFloat(scope,"gamma");
		double epsilon = cfg->lookupFloat(scope,"epsilon");
		double L = cfg->lookupFloat(scope,"L");

		/*param.Nx = Nx;
		param.Ny = Ny;
		param.dx = dx;
		param.dy = dy;
		param.radius = radius;
		param.TimeStep = TimeStep;
		param.FinalTime = FinalTime;
		for(unsigned int i=0;i<Steps.length();i++)
			param.steps_param[i] = steps[i];

		param.tau = tau;
		param.gamma = gamma;
		param.epsilon = epsilon;
		param.L = L;*/
		std::cout<<"Parsed Successfully : "<<param.Nx<<std::endl;
	}catch(const ConfigurationException& ex){
		std::cerr<<ex.c_str()<<std::endl;
		cfg->destroy();
	}

	cfg->destroy();

	return 0;
}


