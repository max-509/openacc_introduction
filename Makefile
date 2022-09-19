all: build run clean

rebuild: clean build

build: mkdir_build main.c
	pgcc main.c -o build/main_c -acc -Minfo=accel -lm

mkdir_build:
	mkdir -p build

run:
	./build/main_c

clean:
	rm -rf build/*

.PHONY: mkdir_build run clean