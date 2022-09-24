MPICC = mpicc
MPICPP = mpic++
PROGS: hybrid-openmp-mm all MM

all: clean hybrid-openmp-mm MM

hybrid-openmp-mm:
	$(MPICC) $@.c -o $@ -fopenmp

MM:
	$(MPICPP) $@.c++ -o $@ 


clean:
	$(RM) $(PROGS) *.o
	$(RM) hybrid-openmp-mm
	$(RM) MM
 
