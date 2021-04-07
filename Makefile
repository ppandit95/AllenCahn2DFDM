ParamFactory.o : ParamFactory.cpp ParamFactory.hpp structures.hpp
	g++ -c ParamFactory.cpp -L"./lib/config4cpp/lib" -lconfig4cpp -I"lib/config4cpp/include"
AllenCahnEquation.o : AllenCahnEquation.cpp AllenCahnEquation.hpp structures.hpp
	g++ -c AllenCahnEquation.cpp
AllenCahn : main.cpp AllenCahnEquation.o AllenCahnEquation.hpp structures.hpp ParamFactory.o
	g++ -o AllenCahn main.cpp AllenCahnEquation.o ParamFactory.o -L"./lib/config4cpp/lib" -lconfig4cpp -I"lib/config4cpp/include"
run : AllenCahn
	./AllenCahn -cfg parameters.cfg
clean : 
	rm Output-* Initial_Profile.dat AllenCahn *.o