# AllenCahn2DFDM

A Finite Difference Implementation of Allen Cahn Equation on a square grid using Jacobi Method with the parameters as defined in configuration file and periodic boundary conditions with explicit time marching of the governing equation  :\
![equation](https://latex.codecogs.com/gif.latex?%5Ctau%20%5Cepsilon%20%3D%202%5Cgamma%20%5Cepsilon%20%5CDelta%20%5Cphi%20-%20%5Cfrac%7B18%5Cgamma%20%7D%7B%5Cepsilon%7D%5Cphi%281-%5Cphi%29%281-2%5Cphi%29%20&plus;%206L%5Cphi%281-%5Cphi%29)

# Insructions To Run the Program

After downloading the zip of this repository using https://github.com/ppandit95/AllenCahn2DFDM/archive/refs/heads/main.zip ,the program can be run by using command :
```
$ make run
```
After execution of program, the generated output can be visualized by julia using the folloing command :
```
julia visualize.jl
```
And the output  dat files generated can be visualized by creating a png image with julia by simply running visualize.jl in Julia.\
Moreover,the Makefile also contains rule for cleaning up all the generated files given by :
```
$ make clean
```



