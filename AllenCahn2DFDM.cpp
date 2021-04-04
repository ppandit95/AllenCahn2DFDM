/*--------------------------------------
 *
 * FDM Code to Solve Allen-Cahn Equation
 *
 *--------------------------------------*/

#include<iostream>
#include<cmath>
#include<fstream>

int main(int argc, char **argv) {
 //Simulation Parameters
	unsigned int Nx = 100;//Domain Size in xDirection
	unsigned int Ny = 100;//Domain Size in YDirection
	unsigned int dx = 1;//Grid Spacing in xDirection
	unsigned int dy = 1;//Grid Spacing in yDirection
	unsigned int radius = 10;//Radius of the initial seed
	double TimeStep = 0.001;//Temporal step size for Explicit Discretization in time
	unsigned int FinalTimeStep = 10000;//Final time step of the simulation
	unsigned int OutputTimeList[] = {1000,2000,5000,10000};//Array of output time steps

	//Material Parameters
	double tau = 1.0;
	double gamma = 1.0;
	double epsilon = 4.0;
	double L = 0.1;


	unsigned int node;
	double** phi;
	phi = new double* [Nx];
	for(unsigned int i=0;i<Nx;i++)
		phi[i] = new double [Ny];

	//Initialize the Grid
	for(unsigned int i=0;i<Nx;i++){
		for(unsigned int j=0;j<Ny;j++)
			phi[i][j] = 0.0;
	}

	//Employ InitialConditions
	for(unsigned int i=49-radius;i<=49+radius;i++){
		for(unsigned int j=49-radius;j<=49+radius;j++){
			if(sqrt((i-49)*(i-49)+(j-49)*(j-49)) <= radius)
				phi[i][j] = 1.0;
		}
	}

	//Output Initial Profile
	std::ofstream write_output("Initial_Profile.dat");
	for(unsigned int i=0;i<Nx;i++){
		for(unsigned int j=0;j<Ny;j++)
			write_output<<phi[i][j]<<"\t";
		write_output<<std::endl;
	}
	write_output.close();
	for(unsigned int i=0;i<Nx;i++)
		delete[] phi[Ny];
	delete[] phi;
	return 0;
}
