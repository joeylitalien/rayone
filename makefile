all:
	g++-5 -O3 -fopenmp rt.cpp -o rt
	./rt
	display image.ppm
