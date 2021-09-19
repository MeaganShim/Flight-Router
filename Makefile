# List all the drivers
all: graphdriver


# list the test program all classes (cpp files)
#  cpp files must use #include , to include *.h or *.hpp files

graphdriver: create_graph.cpp
	g++ -std=c++11 -o  graphdriver create_graph.cpp

# List all the executables under 'all:'
clean:
	rm -rf *.o graphdriver
