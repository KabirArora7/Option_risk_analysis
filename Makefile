all: main

main: main.cpp
	g++ main.cpp -o main -lpgplot -lcpgplot -lgfortran

clean:
	rm -f main
