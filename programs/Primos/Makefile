GCC = mpic++

PROGS: primos all

all: clean primos

primos:
	$(GCC) $@.c++ -o $@ 
	

clean:
	$(RM) $(PROGS) *.o
	$(RM) primos