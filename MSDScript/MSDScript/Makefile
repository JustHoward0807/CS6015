CXX = c++
HEADERS = Expr.hpp cmdline.h
CXXFLAGS = --std=c++14
CXXSOURCE = main.cpp Expr.cpp cmdline.cpp

msdscript: $(HEADERS) $(CXXSOURCE)
	$(CXX) $(CXXFLAGS) -c $(CXXSOURCE)
	$(CXX) $(CXXFLAGS) $(CXXSOURCE) -o msdscript

.PHONY: clean
clean:
	rm -f *.o *.out msdscript
