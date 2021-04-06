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
	Configuration * cfg;
	const char* scope;
	const char* configFile;
public:
	ParamFactory();
	~ParamFactory();
	Parameters ParseParams();


};




#endif /* PARAMFACTORY_HPP_ */
