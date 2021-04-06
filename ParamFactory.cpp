/*
 * ParamFactory.cpp
 *
 *  Created on: 06-Apr-2021
 *      Author: pushkar
 */

#include<iostream>
#include<locale.h>
#include<config4cpp/Configuration.h>
#include<vector>
#include<string>
#include"ParamFactory.hpp"
#include"structures.hpp"

using namespace config4cpp;



void ParamFactory::ParseParams(Parameters& param){
	 cfg = Configuration::create();
	 scope = "";
	 configFile = "parameters.cfg";
	try{
		cfg->parse(configFile);
		param.Nx = cfg->lookupInt(scope,"Nx");
		param.Ny = cfg->lookupInt(scope,"Ny");
		param.dx = cfg->lookupInt(scope,"dx");
		param.dy = cfg->lookupInt(scope,"dy");
		param.radius = cfg->lookupInt(scope,"radius");
		param.TimeStep = cfg->lookupFloat(scope, "TimeStep");
		param.FinalTime = cfg->lookupInt(scope, "FinalTime");
		cfg->lookupList(scope, "steps",Steps);
		for(unsigned int i=0;i<Steps.length();i++)
			param.steps.push_back(atoi(Steps[i]));
		}
		catch(const ConfigurationException& ex){
			std::cerr<<ex.c_str()<<std::endl;
			cfg->destroy();
		}
		cfg->destroy();

}
int main(int argc,char** argv){
	ParamFactory pf;
	Parameters par;
	pf.ParseParams(par);
	std::cout<<"The parameters are"<<par.Nx<<","
			<<par.Ny<<","<<par.dx<<","<<par.dy<<","
			<<par.radius<<","<<par.TimeStep<<","<<par.FinalTime
			<<","<<par.steps[2]<<std::endl;

}



