OBJS = prog2.o
CXX = g++
CXXFLAGS = -std=c++11

prog2 : prog2.o
	$(CXX) $^ -o $@
clean:
	rm *.o
	rm prog2




