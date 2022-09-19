all: build run clean

rebuild: clean build

build: mkdir_build solution_cpu solution_gpu
	pgcc main.c -o build/main_c -acc -Minfo=accel -lm

solution_cpu: solution_cpu.c solution.h
	pgcc solution_cpu.c -o build/solution_cpu -acc -Minfo -std=c11 -lm

mkdir_build:
	mkdir -p build

run:
	./build/main_c

clean:
	rm -rf build/*

.PHONY: mkdir_build run clean