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


void AllenCahnEquation::initialize_field(){
	phi = new double* [param.Nx];
	for(unsigned int i=0;i<param.Nx;i++)
		phi[i] = new double [param.Ny];
	//Initialize the field
	for(unsigned int i=0;i<param.Nx;i++){
		for(unsigned int j=0;j<param.Ny;j++)
			phi[i][j] = 0.0;
	}
}

void AllenCahnEquation::setup_initial_profile(){
		for(unsigned int i=49-param.radius;i<=49+param.radius;i++){
			for(unsigned int j=49-param.radius;j<=49+param.radius;j++){
				if(sqrt((i-49)*(i-49)+(j-49)*(j-49)) <= param.radius)
					phi[i][j] = 1.0;
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
	for(double t=param.TimeStep;t <= param.FinalTime;t += param.TimeStep){
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
		double tStep = t/param.TimeStep;
		Output_field(tStep);
	}
}
bool AllenCahnEquation::on_boundary(unsigned int j,unsigned int k){
	if(j==0 || j==param.Nx-1 || k==0 || k==param.Ny-1)
		return true;
	else
		return false;
}
void AllenCahnEquation::Output_field(double tStep){
	if((int)tStep % 10 == 0){
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
AllenCahnEquation::AllenCahnEquation(){
	param.Nx = 100;
	param.Ny = 100;
	param.dx = 1;
	param.dy = 1;
	param.radius = 10;
	param.TimeStep = 0.01;
	param.FinalTime = 1.01;

	param.tau = 1.0;
	param.gamma = 1.0;
	param.epsilon = 4.0;
	param.L = 1.0;

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


