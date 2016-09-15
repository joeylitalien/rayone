CXX = g++-5
CXXFLAGS = -Wall -std=c++11
OMPFLAG = -fopenmp
MAIN = main
CORE = core
OBJ = objs
BIN = bin

rayone: pathtracer.o shape.o renderer.o montecarlo.o
	$(CXX) $(CXXFLAGS) $(OMPFLAG) $(addprefix $(OBJ)/, pathtracer.o shape.o renderer.o montecarlo.o) -o $(BIN)/rayone

pathtracer.o: $(MAIN)/pathtracer.cpp $(CORE)/pathtracer.h
	$(CXX) $(CXXFLAGS) $(OMPFLAG) -c $(MAIN)/pathtracer.cpp -o $(OBJ)/$@

shape.o: $(addprefix $(CORE)/, shape.cpp shape.h)
	$(CXX) $(CXXFLAGS) -c $(CORE)/shape.cpp -o $(OBJ)/$@

renderer.o: $(addprefix $(CORE)/, renderer.cpp renderer.h)
	$(CXX) $(CXXFLAGS) -c $(CORE)/renderer.cpp -o $(OBJ)/$@

montecarlo.o: $(addprefix $(CORE)/, montecarlo.cpp montecarlo.h)
	$(CXX) -c $(CORE)/montecarlo.cpp -o $(OBJ)/$@
