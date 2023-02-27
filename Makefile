CXX = c++
HEADERS = Expr.hpp cmdline.h
CXXFLAGS = --std=c++14
CXXSOURCE = main.cpp Expr.cpp cmdline.cpp
CXXTESTSOURCE = testMain.cpp exec.cpp
CXXTESTHEADERS = exec.h

msdscript: $(HEADERS) $(CXXSOURCE)
	$(CXX) $(CXXFLAGS) -c $(CXXSOURCE)
	$(CXX) $(CXXFLAGS) $(CXXSOURCE) -o msdscript
	rm -f *.o *.out

test_msdscript: $(CXXTESTHEADERS) $(CXXTESTSOURCE)
	$(CXX) $(CXXFLAGS) -c $(CXXTESTSOURCE)
	$(CXX) $(CXXFLAGS) $(CXXTESTSOURCE) -o test_msdscript
	rm -f *.o *.out

.PHONY: clean
clean:
	rm -f *.o *.out msdscript test_msdscript

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
	
