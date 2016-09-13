CXX = g++-5
CXXFLAGS = -fopenmp -Wall
MAIN = main
CORE = core
OBJ = objs
BIN = bin

rt: raytracer.o shape.o
	$(CXX) $(CXXFLAGS) $(C11) $(addprefix $(OBJ)/, raytracer.o shape.o) -o $(BIN)/raytracer

raytracer.o: $(MAIN)/raytracer.cpp $(CORE)/raytracer.h $(CORE)/geometry.h
	$(CXX) -c $(MAIN)/raytracer.cpp -o $(OBJ)/$@

shape.o: $(addprefix $(CORE)/, shape.cpp shape.h)
	$(CXX) -c $(CORE)/shape.cpp -o $(OBJ)/$@
