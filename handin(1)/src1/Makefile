CC = g++
OPT = -g -O3
#WARN = -Wall

INC = -I. -I../LibSS_smt/include
LIB = -L../LibSS_smt/lib -L.

SIM_LINUX = -DSIM_LINUX
ENDIAN = -DBYTES_LITTLE_ENDIAN -DWORDS_LITTLE_ENDIAN

CFLAGS = $(OPT) $(WARN) $(INC) $(LIB) $(SIM_LINUX) $(ENDIAN)

SIM_SRC = simulator.cc input.cc output.cc info.cc parameters.cc
SIM_OBJ = simulator.o input.o output.o info.o parameters.o


all:
	make little

little: $(SIM_OBJ)
	$(CC) -o sim_little $(CFLAGS) \
		$(SIM_OBJ) -lSS_smt_little -lBP_little
	@echo "-----------DONE WITH SIM FOR LITTLE ENDIAN-----------"

.cc.o:
	$(CC) $(CFLAGS) -c $*.cc


clean:
	rm -f *.o core Makefile.bak sim_little

clobber:
	rm -f *.o

