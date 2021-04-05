AllenCahnEquation.o : AllenCahnEquation.cpp AllenCahnEquation.hpp structures.hpp
	g++ -c AllenCahnEquation.cpp
AllenCahn : main.cpp AllenCahnEquation.o AllenCahnEquation.hpp structures.hpp
	g++ -o AllenCahn main.cpp AllenCahnEquation.o 
run:AllenCahn
	./AllenCahn