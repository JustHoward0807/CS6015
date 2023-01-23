CXX = c++
HEADERS = Expr.hpp
CXXFLAGS = --std=c++14
CXXSOURCE = main.cpp Expr.cpp

Expression: $(HEADERS) $(CXXSOURCE)
	$(CXX) $(CXXFLAGS) -c $(CXXSOURCE)
	$(CXX) $(CXXFLAGS) $(CXXSOURCE) -o Expression

.PHONY: clean
clean:
	rm -f *.o *.out Expression
