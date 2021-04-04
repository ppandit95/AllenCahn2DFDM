/*--------------------------------------
 *
 * FDM Code to Solve Allen-Cahn Equation
 *
 *--------------------------------------*/

#include<iostream>
#include<cmath>
#include<fstream>
#include<string.h>

int main(int argc, char **argv) {
 //Simulation Parameters
	unsigned int Nx = 100;//Domain Size in xDirection
	unsigned int Ny = 100;//Domain Size in YDirection
	unsigned int dx = 1;//Grid Spacing in xDirection
	unsigned int dy = 1;//Grid Spacing in yDirection
	unsigned int radius = 10;//Radius of the initial seed
	double TimeStep = 0.01;//Temporal step size
	double FinalTimeStep = 1.01;//Final time step of the simulation



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



	//Defining Coefficients of FDM Stencil

	double C1 = 1 - ((4*gamma*TimeStep)/(tau*dx*dx)) - ((4*gamma*TimeStep)/(tau*dy*dy))
					- ((18*gamma*TimeStep)/(tau*epsilon*epsilon)) +
					((6*L*TimeStep)/tau*epsilon);//Coefficient of phi[i][j] term at time t

	double C2 = (2*gamma*TimeStep)/(tau*dx*dx);//Coefficient of phi[i-1][j] and phi[i+1][j]

	double C3 = (2*gamma*TimeStep)/(tau*dy*dy);//Coefficient of phi[i][j+1] and phi[i][j-1]

	double C4 = ((54*gamma*TimeStep)/(tau*epsilon*epsilon)) - ((6*L*TimeStep)/(tau*epsilon));//Coefficient of phi[i][j]*phi[i][j] term at time t

	double C5 = (36*gamma*TimeStep)/(tau*epsilon*epsilon);//Coefficient of phi[i][j]*phi[i][j]*phi[i][j] term at time t

	//std::cout <<"The Coefficients of FDM Stencil are "<<C1<<" , "<<C2<<" , "<<C3<<" , "<<C4<<" , "<<C5<<std::endl;


	for(double i=TimeStep;i<=FinalTimeStep;i+=TimeStep){
		for(unsigned int j=1;j<(Nx-1);j++){
			for(unsigned int k=1;k<(Ny-1);k++){
				std::cout<<"Solving for ("<<j<<","<<k<<") in space at time t= "<<i<<std::endl;
				/*
				//Implementing Periodic Boundary Conditions
				if(k==0&&j==0)
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j+Nx-1][k] +
					C3*phi[j][k+1] + C3*phi[j][k+Ny-1] + C4*phi[j][k]*phi[j][k]
					- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(j==(Nx-1) && k==(Ny-1))
					phi[j][k] = C1*phi[j][k] + C2*phi[0][k] + C2*phi[j-1][k] +
										C3*phi[j][0] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
										- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(j==(Nx-1)&&k==0)
					phi[j][k] = C1*phi[j][k] + C2*phi[0][k] + C2*phi[j-1][k] +
										C3*phi[j][k+1] + C3*phi[j][k+Ny-1] + C4*phi[j][k]*phi[j][k]
										- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(j==0 && k==(Ny-1))
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j+Nx-1][k] +
												C3*phi[j][0] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
												- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(j==0)
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j+Nx-1][k] +
										C3*phi[j][k+1] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
										- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(j==(Nx-1))
					phi[j][k] = C1*phi[j][k] + C2*phi[0][k] + C2*phi[j-1][k] +
												C3*phi[j][k+1] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
												- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(k==0)
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j-1][k] +
												C3*phi[j][k+1] + C3*phi[j][k+Ny-1] + C4*phi[j][k]*phi[j][k]
												- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(k==(Ny-1))
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j-1][k] +
												C3*phi[j][0] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
												- C5*phi[j][k]*phi[j][k]*phi[j][k];

				else
				*/
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j-1][k] +
							C3*phi[j][k+1] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
							- C5*phi[j][k]*phi[j][k]*phi[j][k];
			}

		}
		double time = i/TimeStep;
		if((int)time % 10 == 0  ){
			std::cout<<"Writing output at time = "<<i<<std::endl;
			std::string filename = "Output-"+std::to_string(time)+".dat";
			std::ofstream output(filename);
			for(unsigned int p=0;p<Nx;p++){
					for(unsigned int q=0;q<Ny;q++)
						output<<phi[p][q]<<"\t";
					output<<std::endl;
				}
			output.close();
		}

	}

	for(unsigned int i=0;i<Nx;i++)
		delete[] phi[Ny];
	delete[] phi;
	return 0;
}
