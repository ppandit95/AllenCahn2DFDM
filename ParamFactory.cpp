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






