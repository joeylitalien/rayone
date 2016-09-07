CXX = g++-5
CXXFLAGS = -fopenmp -Wall
MAIN = main
CORE = core
OBJ = objs
BIN = bin

rt: raytracer.o shapes.o geometry.o
	$(CXX) $(CXXFLAGS) $(addprefix $(OBJ)/, raytracer.o shapes.o geometry.o) -o $(BIN)/raytracer

raytracer.o: $(MAIN)/raytracer.cpp $(CORE)/raytracer.h
	$(CXX) -c $(MAIN)/raytracer.cpp -o $(OBJ)/$@

shapes.o: $(addprefix $(CORE)/, shapes.cpp shapes.h)
	$(CXX) -c $(CORE)/shapes.cpp -o $(OBJ)/$@

geometry.o: $(addprefix $(CORE)/, geometry.cpp geometry.h)
	$(CXX) -c $(CORE)/geometry.cpp -o $(OBJ)/$@
