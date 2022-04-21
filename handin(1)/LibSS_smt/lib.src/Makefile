# Pick your favorite compiler
CC = g++

# Choose your optimization level here
#OPT  = -g -O3 -finline-functions -funroll-loops
#OPT2 = -g -O
OPT  = -O3 -finline-functions -funroll-loops
OPT2 = -O

INC = -I../include
SIM_LINUX = -DSIM_LINUX
ENDIAN = -DBYTES_LITTLE_ENDIAN -DWORDS_LITTLE_ENDIAN

CFLAGS  = $(OPT)  $(INC) $(SIM_LINUX) $(ENDIAN)
CFLAGS2 = $(OPT2) $(INC) $(SIM_LINUX) $(ENDIAN)

SIM_OBJ = main.o syscall.o memory.o regs.o loader.o ss.o endian.o misc.o \
	  arch.o func_sim.o info.o sim_main.o


all:
	make little

little: libSS_smt_little.a
	touch ../lib/libSS_smt_little.a
	mv ../lib/libSS_smt_little.a ../lib/libSS_smt_little.a.bak
	cp libSS_smt_little.a ../lib/libSS_smt_little.a
	@echo "Compiled for LITTLE_ENDIAN"
	@echo "my work is done here..."

libSS_smt_little.a:	$(SIM_OBJ)
	ar r libSS_smt_little.a $(SIM_OBJ)

func_sim.o:  func_sim.cc
	$(CC) $(CFLAGS2) -c $*.cc
	
endian.o:  endian.cc
	$(CC) $(CFLAGS2) -c $*.cc
	
.cc.o:
	$(CC) $(CFLAGS) -c $*.cc



clean:
	rm -f *.o libSS_smt_little.a core
