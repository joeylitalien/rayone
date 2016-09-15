CXX = g++-5
CXXFLAGS = -Wall -fopenmp
MAIN = main
CORE = core
OBJ = objs
BIN = bin

rayone: pathtracer.o shape.o renderer.o montecarlo.o
	$(CXX) $(CXXFLAGS) $(addprefix $(OBJ)/, pathtracer.o shape.o renderer.o montecarlo.o) -o $(BIN)/rayone

pathtracer.o: $(MAIN)/pathtracer.cpp $(CORE)/pathtracer.h $(CORE)/geometry.h
	$(CXX) -c $(MAIN)/pathtracer.cpp -o $(OBJ)/$@

shape.o: $(addprefix $(CORE)/, shape.cpp shape.h)
	$(CXX) -c $(CORE)/shape.cpp -o $(OBJ)/$@

renderer.o: $(addprefix $(CORE)/, renderer.cpp renderer.h montecarlo.h)
	$(CXX) -c $(CORE)/renderer.cpp -o $(OBJ)/$@

# scene.o: $(addprefix $(CORE)/, scene.cpp scene.h shape.h)
# 	$(CXX) -c $(CORE)/scene.cpp -o $(OBJ)/$@

montecarlo.o: $(addprefix $(CORE)/, montecarlo.cpp montecarlo.h)
	$(CXX) -c $(CORE)/montecarlo.cpp -o $(OBJ)/$@
