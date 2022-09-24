GCC = mpicc

PROGS: hybrid-openmp-mm all

all: clean hybrid-openmp-mm

hybrid-openmp-mm:
	$(GCC) $@.c -o $@ -fopenmp

clean:
	$(RM) $(PROGS) *.o
	$(RM) hybrid-openmp-mm
 
