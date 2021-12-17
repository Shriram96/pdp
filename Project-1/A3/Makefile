NVCC=nvcc
CXX=g++
CXXFLAGS=-std=c++17 -O3
OPENMPFLAGS=-fopenmp -std=c++17 -O3

all: a3.cu
	$(NVCC) $(CXXFLAGS) a3.cu -o a3

vanilla: a3_vanilla

openmp: a3_vanilla
	$(CXX) $(OPENMPFLAGS) a3_vanilla.cpp -o a3_openmp

clean:
	rm -rf a3
	rm -rf a3_vanilla
	rm -rf a3_openmp
