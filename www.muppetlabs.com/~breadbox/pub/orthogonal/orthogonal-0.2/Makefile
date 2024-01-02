COBJ = error.o stack.o value.o grid.o gridptr.o parser.o execpath.o	\
	main.o

CXXFLAGS = -Wall -W

%.o : %.cxx
	$(CXX) -c $(CXXFLAGS) $<

orth : $(COBJ)
	$(CXX) $(CXXFLAGS) $(COBJ) -o $@

error.o    : error.cxx error.hxx gen.hxx
stack.o    : stack.cxx stack.hxx gen.hxx error.hxx
value.o    : value.cxx value.hxx gen.hxx error.hxx
grid.o     : grid.cxx grid.hxx gen.hxx error.hxx
gridptr.o  : gridptr.cxx gridptr.hxx grid.hxx gen.hxx error.hxx
parser.o   : parser.cxx parser.hxx gen.hxx error.hxx value.hxx gridptr.hxx
execpath.o : execpath.cxx execpath.hxx gen.hxx error.hxx stack.hxx	\
		grid.hxx gridptr.hxx parser.hxx
main.o     : main.cxx gen.hxx error.hxx stack.hxx value.hxx grid.hxx	\
		gridptr.hxx parser.hxx execpath.hxx

clean :
	rm $(COBJ) orth
