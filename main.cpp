/*
 * main.cpp
 *
 *  Created on: 05-Apr-2021
 *      Author: pushkar
 */

#include"AllenCahnEquation.hpp"
#include"structures.hpp"
#include"ParamFactory.hpp"


int main(int argc,char** argv){
	ParamFactory pf;
	Parameters param;
	pf.ParseParams(param);
	std::cout<<"Parsed parameters are : "<<param.Nx<<","<<param.Ny<<std::endl;
	//AllenCahnEquation task_assignment(param);
	//task_assignment.run();
	return 0;
}
// ac -cfg <file>


