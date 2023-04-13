run: main.o Point.o mergeSort.o
	g++ -o run main.o Point.o mergeSort.o

main.o: main.cpp Point.hpp mergeSort.hpp
	g++ -c main.cpp

Point.o: Point.cpp Point.hpp
	g++ -c Point.cpp

mergeSort.o: mergeSort.cpp mergeSort.hpp Point.hpp
	g++ -c mergeSort.cpp
