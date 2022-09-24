#include <stdio.h>
#include <omp.h>
#include "mpi.h"

int prime_number ( int n, int id, int p );

int main(int argc, char *argv[]) {
    int i;
    int id;
    int master = 0;
    int n;
    int n_factor;
    int n_hi;
    int n_lo;
    int p;
    int primes;
    int primes_part;
    double wtime;
    double totaltime=0;

    int numprocs, rank, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int iam = 0, np = 1;

    n_lo = 1;
    n_hi = atoi(argv[1]);
    n_factor = 2;
    MPI::Init ( argc, argv );
    p = MPI::COMM_WORLD.Get_size (  );
    id = MPI::COMM_WORLD.Get_rank ( );

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    #pragma omp parallel default(shared) private(iam, np)
    {
        np = omp_get_num_threads();
        iam = omp_get_thread_num();
        printf("Hello from thread %d out of %d from process %d out of %d on %s\n",
            iam, np, rank, numprocs, processor_name);
    }

    MPI_Finalize();

  if(id == master){
    cout<<p<<","<<n_hi<<","<<totaltime<<endl;
  }

  return 0;
}

int prime_number ( int n, int id, int p ){
  int i;
  int j;
  int prime;
  int total;

  total = 0;


  for ( i = 2 + id; i <= n; i = i + p ){
    prime = 1;
    for ( j = 2; j < i; j++ ){
      if ( ( i % j ) == 0 ){
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }
  return total;
}

void MM1c_OMP(int threads, int size, double *Ma, double *Mb, double *Mr)
{
	omp_set_num_threads(threads);
/*Instruction to the compiler, telling that here starts the
parallel computation*/
#pragma omp parallel
	{
		int i, j, k;
#pragma omp for
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				/*Necesita puteros auxiliares*/
				double *pA, *pB;
				double sumaAuxiliar = 0.0;
				pA = Ma + (i * size);
				pB = Mb + j;
				for (k = 0; k < size; ++k, pA++, pB += size)
				{
					sumaAuxiliar += (*pA * *pB);
				}
				Mr[i * size + j] = sumaAuxiliar;
			}
		}
	}
}