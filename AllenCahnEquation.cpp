/*
 * AllenCahnEquation.cpp
 *
 *  Created on: 05-Apr-2021
 *      Author: pushkar
 */
#include"AllenCahnEquation.hpp"
#include"structures.hpp"
#include<cmath>
#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#define PHI_MIN 0.0;

void AllenCahnEquation::initialize_field(){
	phi = new double* [param.Nx];
	for(unsigned int i=0;i<param.Nx;i++)
		phi[i] = new double [param.Ny];
	//Initialize the field
	for(unsigned int i=0;i<param.Nx;i++){
		for(unsigned int j=0;j<param.Ny;j++)
			phi[i][j] = PHI_MIN;
	}
}

void AllenCahnEquation::setup_initial_profile(){
		for(unsigned int i=center[0]-param.radius;i<=center[0]+param.radius;i++){
			for(unsigned int j=center[1]-param.radius;j<=center[1]+param.radius;j++){
				if(sqrt((i-center[0])*(i-center[0])+(j-center[1])*(j-center[1])) <= param.radius)
					phi[i][j] = PHI_MAX;
			}
		}
}

void AllenCahnEquation::output_initial_profile(){
		std::ofstream write_output("Initial_Profile.dat");
		for(unsigned int i=0;i<param.Nx;i++){
			for(unsigned int j=0;j<param.Ny;j++)
				write_output<<phi[i][j]<<"\t";
			write_output<<std::endl;
		}
		write_output.close();
}
void AllenCahnEquation::initialize_FDMConstants(){
	consts.C1 = 1 - ((4*param.gamma*param.TimeStep)/(param.tau*param.dx*param.dx)) - ((4*param.gamma*param.TimeStep)/(param.tau*param.dy*param.dy))
							- ((18*param.gamma*param.TimeStep)/(param.tau*param.epsilon*param.epsilon)) +
							((6*param.L*param.TimeStep)/param.tau*param.epsilon);
	consts.C2 = (2*param.gamma*param.TimeStep)/(param.tau*param.dx*param.dx);
	consts.C3 = (2*param.gamma*param.TimeStep)/(param.tau*param.dy*param.dy);
	consts.C4 = ((54*param.gamma*param.TimeStep)/(param.tau*param.epsilon*param.epsilon)) - ((6*param.L*param.TimeStep)/(param.tau*param.epsilon));
	consts.C5 = (36*param.gamma*param.TimeStep)/(param.tau*param.epsilon*param.epsilon);
}
void AllenCahnEquation::Evolve_on_boundaries(unsigned int j,unsigned int k){
	if(k==0&&j==0)
		phi[j][k] = consts.C1*phi[j][k] + consts.C2*phi[j+1][k] + consts.C2*phi[j+param.Nx-1][k] +
					consts.C3*phi[j][k+1] + consts.C3*phi[j][k+param.Ny-1] + consts.C4*phi[j][k]*phi[j][k]
					- consts.C5*phi[j][k]*phi[j][k]*phi[j][k];
	else if(j==(param.Nx-1) && k==(param.Ny-1))
		phi[j][k] = consts.C1*phi[j][k] + consts.C2*phi[0][k] + consts.C2*phi[j-1][k] +
					consts.C3*phi[j][0] + consts.C3*phi[j][k-1] + consts.C4*phi[j][k]*phi[j][k]
					- consts.C5*phi[j][k]*phi[j][k]*phi[j][k];
	else if(j==(param.Nx-1)&&k==0)
		phi[j][k] = consts.C1*phi[j][k] + consts.C2*phi[0][k] + consts.C2*phi[j-1][k] +
					consts.C3*phi[j][k+1] + consts.C3*phi[j][k+param.Ny-1] + consts.C4*phi[j][k]*phi[j][k]
					- consts.C5*phi[j][k]*phi[j][k]*phi[j][k];
	else if(j==0 && k==(param.Ny-1))
		phi[j][k] = consts.C1*phi[j][k] + consts.C2*phi[j+1][k] + consts.C2*phi[j+param.Nx-1][k] +
					consts.C3*phi[j][0] + consts.C3*phi[j][k-1] + consts.C4*phi[j][k]*phi[j][k]
					- consts.C5*phi[j][k]*phi[j][k]*phi[j][k];
	else if(j==0)
		phi[j][k] = consts.C1*phi[j][k] + consts.C2*phi[j+1][k] + consts.C2*phi[j+param.Nx-1][k] +
					consts.C3*phi[j][k+1] + consts.C3*phi[j][k-1] + consts.C4*phi[j][k]*phi[j][k]
				    - consts.C5*phi[j][k]*phi[j][k]*phi[j][k];
	else if(j==(param.Nx-1))
		phi[j][k] = consts.C1*phi[j][k] + consts.C2*phi[0][k] + consts.C2*phi[j-1][k] +
					consts.C3*phi[j][k+1] + consts.C3*phi[j][k-1] + consts.C4*phi[j][k]*phi[j][k]
					- consts.C5*phi[j][k]*phi[j][k]*phi[j][k];
	else if(k==0)
		phi[j][k] = consts.C1*phi[j][k] + consts.C2*phi[j+1][k] + consts.C2*phi[j-1][k] +
					consts.C3*phi[j][k+1] + consts.C3*phi[j][k+param.Ny-1] + consts.C4*phi[j][k]*phi[j][k]
					- consts.C5*phi[j][k]*phi[j][k]*phi[j][k];
	else if(k==(param.Ny-1))
		phi[j][k] = consts.C1*phi[j][k] + consts.C2*phi[j+1][k] + consts.C2*phi[j-1][k] +
					consts.C3*phi[j][0] + consts.C3*phi[j][k-1] + consts.C4*phi[j][k]*phi[j][k]
					- consts.C5*phi[j][k]*phi[j][k]*phi[j][k];

}

void AllenCahnEquation::Evolve_with_FDM(){
	for(unsigned int t=1;t<=param.FinalTime;t++){
		for(unsigned int j=0;j<param.Nx;j++){
			for(unsigned int k=0;k<param.Ny;k++){
				if(on_boundary(j,k))
					Evolve_on_boundaries(j, k);
				else
					phi[j][k] = consts.C1*phi[j][k] + consts.C2*phi[j+1][k] + consts.C2*phi[j-1][k] +
												consts.C3*phi[j][k+1] + consts.C3*phi[j][k-1] + consts.C4*phi[j][k]*phi[j][k]
												- consts.C5*phi[j][k]*phi[j][k]*phi[j][k];
			}
		}
		Output_field(t);
	}
}


bool AllenCahnEquation::on_boundary(unsigned int j,unsigned int k){
	if(j==0 || j==(param.Nx-1) || k==0 || k==(param.Ny-1))
		return true;
	else
		return false;
}
void AllenCahnEquation::Output_field(unsigned int tStep){
	if(find(param.steps_param.begin(),param.steps_param.end(),tStep) != param.steps_param.end()){
		std::cout<<"Writing output at time step = "<<tStep<<std::endl;
		std::string filename = "Output-"+std::to_string(tStep)+".dat";
		std::ofstream output(filename);
		for(unsigned int i=0;i<param.Nx;i++){
			for(unsigned int j=0;j<param.Ny;j++)
				output<<phi[i][j]<<"\t";
			output<<std::endl;
		}
		output.close();
	}
}
AllenCahnEquation::AllenCahnEquation(Parameters& params){
	param = params;
	center[0] = param.Nx%2==0 ? param.Nx/2 - 1 : (param.Nx - 1)/2;
	center[1] = param.Ny%2==0 ? param.Ny/2 - 1 : (param.Ny - 1)/2;
	initialize_field();
	initialize_FDMConstants();
}
AllenCahnEquation::~AllenCahnEquation(){
	for(unsigned int i=0;i<param.Nx;i++)
			delete[] phi[param.Ny];
		delete[] phi;
}
void AllenCahnEquation::run(){
	setup_initial_profile();
	output_initial_profile();
	Evolve_with_FDM();
}


