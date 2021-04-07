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
	if(param.Nx != param.Ny){
		std::cout<<"The domain should be square in order to get initial circular seed..."<<std::endl;
		assert(false);
	}
	//ParamsFactory paramsFactory;
	//Parameters params = paramsFactory.getParams();
	AllenCahnEquation task_assignment(param);
	task_assignment.run();
	end:return 0;
}
// ac -cfg <file>


