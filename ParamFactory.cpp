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

using namespace config4cpp;



int main(int argc,char** argv){
	Configuration * cfg = Configuration::create();
	const char* scope = "";
	const char* configFile = "parameters.cfg";
	int Nx;
	int Ny;
	int dx;
	int dy;
	int radius;
	double TimeStep;
	int FinalTime;
	StringVector Steps;
	std::vector<int> steps;


		try{
			cfg->parse(configFile);
			Nx = cfg->lookupInt(scope,"Nx");
			Ny = cfg->lookupInt(scope,"Ny");
			dx = cfg->lookupInt(scope,"dx");
			dy = cfg->lookupInt(scope,"dy");
			radius = cfg->lookupInt(scope,"radius");
			TimeStep = cfg->lookupFloat(scope, "TimeStep");
			FinalTime = cfg->lookupInt(scope, "FinalTime");
			cfg->lookupList(scope, "steps",Steps);
			for(unsigned int i=0;i<Steps.length();i++)
				steps.push_back(atoi(Steps[i]));

		}
		catch(const ConfigurationException& ex){
			std::cerr<<ex.c_str()<<std::endl;
			cfg->destroy();
			return 1;
		}
		std::cout<<"The parameters are"<<Nx<<","<<Ny<<","<<dx<<","<<dy<<","<<radius<<","<<TimeStep<<","<<FinalTime<<","<<steps[0]<<std::endl;
		cfg->destroy();
		return 0;
}



