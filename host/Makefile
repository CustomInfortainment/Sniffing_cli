all: build build/serial_test
build:
	mkdir -p build
build/serial_test: build/bootstrap.o build/main.o
	g++ -o build/serial_test build/bootstrap.o build/main.o

build/bootstrap.o : include/bootstrap.h src/bootstrap.cpp
	g++ -c -I include -o build/bootstrap.o src/bootstrap.cpp

build/main.o : src/main.cpp
	g++ -c -I include -o build/main.o src/main.cpp

clean:
	rm -rf build
