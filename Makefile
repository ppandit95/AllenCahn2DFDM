ParamFactory.o:ParamFactory.cpp structures.hpp ParamFactory.hpp
	g++ -c ParamFactory.cpp -L"./config4cpp/lib" -lconfig4cpp -I"config4cpp/include"
AllenCahnEquation.o : AllenCahnEquation.cpp AllenCahnEquation.hpp structures.hpp
	g++ -c AllenCahnEquation.cpp
AllenCahn : main.cpp AllenCahnEquation.o AllenCahnEquation.hpp structures.hpp ParamFactory.o
	g++ -o AllenCahn main.cpp AllenCahnEquation.o ParamFactory.o -L"./config4cpp/lib" -lconfig4cpp -I"./config4cpp/include/"
run:AllenCahn
	./AllenCahn -cfg parameters.cfg