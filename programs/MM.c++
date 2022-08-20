# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>
# include "mpi.h"

using namespace std;

int main ( int argc, char *argv[] );
int prime_number ( int n, int id, int p );
double **memReserve(int size);
void initMatrix(double **MA, double **MB, double **MC, int size);

int main ( int argc, char *argv[] ){
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
  int N = 3;  //Matriz size

  /*Memory creation and reserce for each matrix*/
  double **Ma = memReserve(N); 
  double **Mb = memReserve(N);
  double **Mc = memReserve(N);  
  initMatrix(Ma, Mb, Mc, N);

  n_lo = 1;
  n_hi = 131072;
  n_factor = 2;
  MPI::Init ( argc, argv );
  p = MPI::COMM_WORLD.Get_size (  );
  id = MPI::COMM_WORLD.Get_rank ( );

  if ( id == master )
  {
    cout << "\n";
    cout << "Matrix Multiplication - C++/MPI version\n";
    cout << " Program for multipliying square matrix\n";
    cout << "  Corriendo en " << p << " procesos\n";
    cout << "\n";
    cout << "         N        S          Tiempo\n";
    cout << "\n";
  }

  n = n_lo;

  while ( n <= n_hi ){
    if ( id == master ){
      wtime = MPI::Wtime ( );
    }

    MPI::COMM_WORLD.Bcast(&N, 1, MPI::INT, master);

    primes_part = MMx(int N; double **Ma, double **Mb, double **Mc, int id, int p);

    // MPI::COMM_WORLD.Reduce(&primes_part, &primes, 1, MPI::INT, MPI::SUM, master );

    if ( id == master ){
      wtime = MPI::Wtime ( ) - wtime;

      cout << "  " << setw(8) << n
           << "  " << setw(8) << primes
           << "  " << setw(14) << wtime << "\n";
    }
    n = n * n_factor;
  }

  MPI::Finalize ( );

  if ( id == master ){
    cout << "\n";
    cout << "PRIME_MPI - Procesos maestro:\n";
    cout << "  Finalizacion del calculo normal.\n";
  }

  return 0;
}

/**
 * @brief: Divides and multiplies matrices.
 * @param id: Processor ID.
 * @param p: Total number of processors.
 * @param N: Matrix size.
 * @param Ma: Matriz A.
 * @param Mb: Matriz B.
 * @param Mc: Matriz C -> Result.
*/
int MMx (int N; double **Ma, double **Mb, double **Mc, int id, int p){
  int i;
  int j;
  int portionSize, initRow, endRow;
	double sum;

	portionSize = N / p;	      	    // Sets matrix A's portion for sending to each processor.
	initRow = id * portionSize;	      // Beggining of the row.
	endRow = (id + 1) * portionSize;  // End of the row.

	for (i = initRow; i < endRow; i++){
		for (j = 0; j < N; ++j){
			sum = 0;
			for (k = 0; k < N; k++){
				sum += Ma[i][k] * Mb[k][j];
			}
			Mc[i][j] = sum;
		}
	}
}


/*********** Functions ******************/
/**
 * @brief: Reserves the memory size for a given matrix
 * @param size: Matrix size
*/
double **memReserve(int size){
	/* Memory reserve of dimenion NxN double*/
	double *val = (double *)malloc(size * size * sizeof(double));

	/* Doble pointer Vector reserve of dimenion size*/
	double **ptr = (double **)malloc(size * size * sizeof(double *));
	/* Iteration with the purpose that each pointer position itself in the memory reserve*/
	
  for (int i = 0; i < size; ++i){
		ptr[i] = &val[i * size];
	}
	return ptr;
}

/**
 * @brief: Gives values for each space of a matrix
 * @param MA: Matrix A
 * @param MB: Matrix B
 * @param MC: Matrix C
 * @param size: Size of the matrix
 */
void initMatrix(double **MA, double **MB, double **MC, int size){
	int i, j; /*Indices*/
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			MA[i][j] = 3.2 * (i + j);
			MB[i][j] = 2.4 * (i - j);
			MC[i][j] = 0.0;
		}
	}
}