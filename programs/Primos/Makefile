GCC = mpic++ 

PROGS: primos primes_opnmp_mpi

all: clean primes_opnmp_mpi

primos:
	$(GCC) $@.c++ -o $@ -fopenmp
	
primes_opnmp_mpi:
	$(GCC) $@.c++ -o $@ -fopenmp

clean:
	$(RM) $(PROGS) *.o
	$(RM) primes_opnmp_mpi
