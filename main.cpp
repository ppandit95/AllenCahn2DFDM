/*
 * main.cpp
 *
 *  Created on: 05-Apr-2021
 *      Author: pushkar
 */

#include"AllenCahnEquation.hpp"
#include"structures.hpp"
#include <config4cpp/Configuration.h>
#include"ParamFactory.hpp"


int main(int argc,char** argv){
	ParamFactory pf;
	Parameters param;
	param = pf.ParseParams();
	AllenCahnEquation task_assignment(param);
	task_assignment.setup();
	task_assignment.run();
	end:return 0;
}



