/*
 * ParamFactory.hpp
 *
 *  Created on: 06-Apr-2021
 *      Author: pushkar
 */

#ifndef PARAMFACTORY_HPP_
#define PARAMFACTORY_HPP_
#include "/usr/lib/config4cpp/include/config4cpp/Configuration.h"
#include<iostream>

class ParamFactory{
	config4cpp::Configuration * cfg = Configuration.create();
};




#endif /* PARAMFACTORY_HPP_ */
