CXX = g++-5
CXXFLAGS = -fopenmp -Wall
MAIN = main
CORE = core
OBJ = objs
BIN = bin

rt: raytracer.o primitive.o geometry.o light.o
	$(CXX) $(CXXFLAGS) $(addprefix $(OBJ)/, raytracer.o primitive.o geometry.o) -o $(BIN)/raytracer

raytracer.o: $(MAIN)/raytracer.cpp $(CORE)/raytracer.h
	$(CXX) -c $(MAIN)/raytracer.cpp -o $(OBJ)/$@

primitive.o: $(addprefix $(CORE)/, primitive.cpp primitive.h)
	$(CXX) -c $(CORE)/primitive.cpp -o $(OBJ)/$@

geometry.o: $(addprefix $(CORE)/, geometry.cpp geometry.h)
	$(CXX) -c $(CORE)/geometry.cpp -o $(OBJ)/$@

light.o: $(addprefix $(CORE)/, light.cpp light.h)
	$(CXX) -c $(CORE)/light.cpp -o $(OBJ)/$@
