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
.PHONY: doc
doc: 
	cd documentation && doxygen

#CXX = c++
#CXXFLAGS = --std=c++14
#CXXSOURCE = main.cpp cmdline.cpp Expr.cpp
#
#msdscript: main.o cmdline.o Expr.o
#	$(CXX) $(CXXFLAGS) main.o cmdline.o Expr.o -o msdscript
#
#cmdline.o: cmdline.h
#Expr.o: Expr.hpp
#
#printM:
#	@echo ${HEADERS}
#	@echo ${CXXSOURCE}
#
#.PHONY: clean
#clean:
#	rm -f *.o *.out msdscript
#
	
