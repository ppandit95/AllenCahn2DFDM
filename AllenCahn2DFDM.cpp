/*--------------------------------------
 *
 * FDM Code to Solve Allen-Cahn Equation
 *
 *--------------------------------------*/

#include<iostream>
#include<cmath>
#include<fstream>
#include<string.h>
struct Parameters{
	unsigned int Nx;//Domain Size in xDirection
	unsigned int Ny;//Domain Size in YDirection
	unsigned int dx;//Grid Spacing in xDirection
	unsigned int dy;//Grid Spacing in yDirection
	unsigned int radius;//Radius of the initial seed
	double TimeStep;//Temporal step size
	double FinalTime;//Final time step of the simulation
};
int main(int argc, char **argv) {
 //Simulation Parameters
	Parameters param;
	param.Nx = 100;
	param.Ny = 100;
	param.dx = 1;
	param.dy = 1;
	param.radius = 10;
	param.TimeStep = 0.01;
	param.FinalTime = 1.01;



	//Material Parameters
	double tau = 1.0;
	double gamma = 1.0;
	double epsilon = 4.0;
	double L = 0.1;


	unsigned int node;
	double** phi;
	phi = new double* [param.Nx];
	for(unsigned int i=0;i<param.Nx;i++)
		phi[i] = new double [param.Ny];

	//Initialize the Grid
	for(unsigned int i=0;i<param.Nx;i++){
		for(unsigned int j=0;j<param.Ny;j++)
			phi[i][j] = 0.0;
	}

	//Employ InitialConditions
	for(unsigned int i=49-param.radius;i<=49+param.radius;i++){
		for(unsigned int j=49-param.radius;j<=49+param.radius;j++){
			if(sqrt((i-49)*(i-49)+(j-49)*(j-49)) <= param.radius)
				phi[i][j] = 1.0;
		}
	}

	//Output Initial Profile
	std::ofstream write_output("Initial_Profile.dat");
	for(unsigned int i=0;i<param.Nx;i++){
		for(unsigned int j=0;j<param.Ny;j++)
			write_output<<phi[i][j]<<"\t";
		write_output<<std::endl;
	}
	write_output.close();



	//Defining Coefficients of FDM Stencil

	double C1 = 1 - ((4*gamma*param.TimeStep)/(tau*param.dx*param.dx)) - ((4*gamma*param.TimeStep)/(tau*param.dy*param.dy))
					- ((18*gamma*param.TimeStep)/(tau*epsilon*epsilon)) +
					((6*L*param.TimeStep)/tau*epsilon);//Coefficient of phi[i][j] term at time t

	double C2 = (2*gamma*param.TimeStep)/(tau*param.dx*param.dx);//Coefficient of phi[i-1][j] and phi[i+1][j]

	double C3 = (2*gamma*param.TimeStep)/(tau*param.dy*param.dy);//Coefficient of phi[i][j+1] and phi[i][j-1]

	double C4 = ((54*gamma*param.TimeStep)/(tau*epsilon*epsilon)) - ((6*L*param.TimeStep)/(tau*epsilon));//Coefficient of phi[i][j]*phi[i][j] term at time t

	double C5 = (36*gamma*param.TimeStep)/(tau*epsilon*epsilon);//Coefficient of phi[i][j]*phi[i][j]*phi[i][j] term at time t

	//std::cout <<"The Coefficients of FDM Stencil are "<<C1<<" , "<<C2<<" , "<<C3<<" , "<<C4<<" , "<<C5<<std::endl;


	for(double i=param.TimeStep;i<=param.FinalTime;i+=param.TimeStep){
		for(unsigned int j=1;j<(param.Nx-1);j++){
			for(unsigned int k=1;k<(param.Ny-1);k++){
				std::cout<<"Solving for ("<<j<<","<<k<<") in space at time t= "<<i<<std::endl;

				//Implementing Periodic Boundary Conditions
				if(k==0&&j==0)
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j+param.Nx-1][k] +
					C3*phi[j][k+1] + C3*phi[j][k+param.Ny-1] + C4*phi[j][k]*phi[j][k]
					- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(j==(param.Nx-1) && k==(param.Ny-1))
					phi[j][k] = C1*phi[j][k] + C2*phi[0][k] + C2*phi[j-1][k] +
										C3*phi[j][0] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
										- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(j==(param.Nx-1)&&k==0)
					phi[j][k] = C1*phi[j][k] + C2*phi[0][k] + C2*phi[j-1][k] +
										C3*phi[j][k+1] + C3*phi[j][k+param.Ny-1] + C4*phi[j][k]*phi[j][k]
										- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(j==0 && k==(param.Ny-1))
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j+param.Nx-1][k] +
												C3*phi[j][0] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
												- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(j==0)
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j+param.Nx-1][k] +
										C3*phi[j][k+1] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
										- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(j==(param.Nx-1))
					phi[j][k] = C1*phi[j][k] + C2*phi[0][k] + C2*phi[j-1][k] +
												C3*phi[j][k+1] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
												- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(k==0)
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j-1][k] +
												C3*phi[j][k+1] + C3*phi[j][k+param.Ny-1] + C4*phi[j][k]*phi[j][k]
												- C5*phi[j][k]*phi[j][k]*phi[j][k];
				else if(k==(param.Ny-1))
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j-1][k] +
												C3*phi[j][0] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
												- C5*phi[j][k]*phi[j][k]*phi[j][k];

				else if((j > 0 && k > 0) || (j<(param.Nx-1) && k<(param.Ny-1)))
					phi[j][k] = C1*phi[j][k] + C2*phi[j+1][k] + C2*phi[j-1][k] +
							C3*phi[j][k+1] + C3*phi[j][k-1] + C4*phi[j][k]*phi[j][k]
							- C5*phi[j][k]*phi[j][k]*phi[j][k];
			}

		}
		double time = i/param.TimeStep;
		if((int)time % 10 == 0  ){
			std::cout<<"Writing output at time = "<<i<<std::endl;
			std::string filename = "Output-"+std::to_string(time)+".dat";
			std::ofstream output(filename);
			for(unsigned int p=0;p<param.Nx;p++){
					for(unsigned int q=0;q<param.Ny;q++)
						output<<phi[p][q]<<"\t";
					output<<std::endl;
				}
			output.close();
		}

	}

	for(unsigned int i=0;i<param.Nx;i++)
		delete[] phi[param.Ny];
	delete[] phi;
	return 0;
}
