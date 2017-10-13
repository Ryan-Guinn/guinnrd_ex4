# makefile for cube code

all: HexiConverter HexTest
		g++ -std=c++14 -Wall --coverage HexiConverter.o HexString.o  Main.cpp

# linking combine os and libs to executable-> complete progame 
HexiConverter: HexiConverter.o HexString.o Main.o
	g++ -std=c++14 -Wall --coverage HexiConverter.o HexString.o  Main.o -o HexiConverter 

HexiConverter.o: HexiConverter.h HexiConverter.cpp HexString.h
	g++ -std=c++14 -Wall --coverage -c HexiConverter.cpp

HexString.o: HexString.h HexString.cpp 
	g++ -std=c++14 -Wall --coverage -c HexString.cpp

HexTest: HexTest.o HexiConverter.o HexString.o
	g++ -pthread -std=c++14 -Wall --coverage Hextest.o HexiConverter.o HexString.o -lgtest_main -lgtest -lpthread -o HexTest 

HexTest.o: HexTest.cpp 
	g++ -std=c++14 -Wall --coverage -c HexTest.cpp 

Main.o: HexiConverter.h Main.cpp 
	g++ -std=c++14 -Wall --coverage -c Main.cpp

coverage: HexTest
	mkdir -p code_coverage_report
	-./HexTest
	lcov --directory ./ --capture --output-file ./code_coverage.info -rc lcov_branch_coverage=1
	genhtml code_coverage.info --branch-coverage --output-directory ./code_coverage_report/

clean:
	rm -f *.o *.gcda *.gcno code_coverage.info HexiConverter HexTest
	rm -rf code_coverage_report


