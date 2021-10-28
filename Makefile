all: bin/demo
bin/demo: Demo.cpp bin/libprofiler.o 
	c++ -O3 -std=c++17 -finstrument-functions bin/libprofiler.o Demo.cpp -o bin/demo
bin/libprofiler.o: Profiler.cpp 
	c++ -O3 -std=c++17 -c Profiler.cpp -o bin/libprofiler.o
