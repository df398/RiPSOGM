AR = ar rcus
CXX = mpicxx
CC  = mpicc
CXXFLAGS = -g -O3 -std=c++0x
CFLAGS   = -O3
DEPS = par.h 
OBJ = par.o main.o
LIB = -L$(PWD) -L$(BOOST_LIB_PATH)
INC = -I$(PWD) -I$(BOOST_INC_PATH)
BOOST= -lboost_filesystem -lboost_system

%.o: %.cpp $(DEPS)
	$(CXX) $(LIB) $(INC) $(CXXFLAGS) -c -o $@ $< $(BOOST)

ripsogm_mpi: $(OBJ)
	$(CXX) $(LIB) $(INC) $(CXXFLAGS) -o $@ $^ $(BOOST)
clean:
	rm -f *.o ripsogm_mpi
