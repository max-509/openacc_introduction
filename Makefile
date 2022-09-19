RESULTS_FILE=results.csv
ARRAY_SIZE?=100000000UL
FLOAT_TYPE?=double
CC_FLAGS=-DARRAY_SIZE=$(ARRAY_SIZE) -DFLOAT_TYPE=$(FLOAT_TYPE) -acc -Minfo=accel -std=c11 -lm -O3

all: build run clean

rebuild: clean build

build: mkdir_build solution_cpu solution_gpu

solution_cpu: solution_cpu.c solution.h
	pgcc $(CC_FLAGS) solution_cpu.c -o build/solution_cpu

solution_gpu: solution_cpu.c solution.h
	pgcc $(CC_FLAGS) solution_gpu.c -o build/solution_gpu

mkdir_build:
	mkdir -p build

run:
	if [ ! -f $(RESULTS_FILE) ] ; then echo 'target platform,array size,data type,elapsed timel,sum result' >> $(RESULTS_FILE) ; fi
	./build/solution_cpu >> $(RESULTS_FILE)
	./build/solution_gpu >> $(RESULTS_FILE)

clean:
	rm -rf build/*

.PHONY: mkdir_build run clean