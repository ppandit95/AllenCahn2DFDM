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
#include<cassert>
#include<cmath>
using namespace config4cpp;

ParamFactory::ParamFactory(){
	cfg = Configuration::create();
	scope = "";
	configFile = "parameters.cfg";
}
ParamFactory::~ParamFactory(){
	cfg->destroy();
}

Parameters ParamFactory::ParseParams(){
	Parameters param;
	StringVector Steps;
	bool FileParsingSuccess = false;
	try{
		cfg->parse(configFile);
		param.Nx = fabs(cfg->lookupInt(scope,"Nx"));
		param.Ny = fabs(cfg->lookupInt(scope,"Ny"));
		if(param.Nx != param.Ny){
			std::cout<<"The domain should be square in order to get initial circular seed..."<<std::endl;
			assert(false);
		}
		param.dx = cfg->lookupFloat(scope,"dx");
		param.dy = cfg->lookupFloat(scope,"dy");
		param.radius = fabs(cfg->lookupInt(scope,"radius"));
		param.TimeStep = cfg->lookupFloat(scope, "TimeStep");
		param.FinalTime = fabs(cfg->lookupInt(scope, "FinalTime"));
		cfg->lookupList(scope, "steps",Steps);
		for(unsigned int i=0;i<Steps.length();i++)
			param.steps.push_back(fabs(atoi(Steps[i])));
		param.tau = cfg->lookupFloat(scope,"tau");
		param.gamma = cfg->lookupFloat(scope,"gamma");
		param.epsilon = cfg->lookupFloat(scope,"epsilon");
		param.L = cfg->lookupFloat(scope,"L");
		}
		catch(const ConfigurationException& ex){
			std::cerr<<ex.c_str()<<std::endl;
			assert(FileParsingSuccess);
			cfg->destroy();
		}
		std::cout<<"Parsed Successfully...."<<std::endl;
		return param;
}






