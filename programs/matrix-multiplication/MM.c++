# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>
# include <stdio.h>
# include "mpi.h"

using namespace std;

double **memReserve(int size);
void initMatrix(double **MA, double **MB, double **MC, int size);
void MMx (int N, double **Ma, double **Mb, double **Mc, int id, int p);
void printMatrix(double **M, int size, char const *name);
void printResultantMatrix(double **M, int size, char const *name,int id,int p);

int main ( int argc, char *argv[] ){
  int id;
  int master = 0;
  int p;
  double wtime;
  int N = atoi(argv[1]);

  /*Memory creation and reserce for each matrix*/
  double **Ma = memReserve(N); 
  double **Mb = memReserve(N);
  double **Mc = memReserve(N);  
  initMatrix(Ma, Mb, Mc, N);

  MPI::Init ( argc, argv );
  p = MPI::COMM_WORLD.Get_size (  );
  id = MPI::COMM_WORLD.Get_rank ( );

  if ( id == master )
  {
    printMatrix(Ma, N, "Matrix A");
    printMatrix(Mb, N, "Matrix B");
  }


  if ( id == master ){
    wtime = MPI::Wtime ( );
  }

  MPI::COMM_WORLD.Bcast(&N, 1, MPI::INT, master);

  MMx(N, Ma, Mb, Mc, id, p);

  //MPI::COMM_WORLD.Reduce(&Mc, &Mc, 1, MPI::INT, MPI::SUM, master );

  if ( id == master ){
    wtime = MPI::Wtime ( ) - wtime;

    cout <<N<<","<<p<<","<< wtime << "\n";
  }

  MPI::Finalize ( );

  
  printResultantMatrix(Mc, N, "Matrix C",id,p);
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
void MMx (int N, double **Ma, double **Mb, double **Mc, int id, int p){
  int i, j,k;
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
 * @brief Reserves the memory size for a given matrix
 * @param size Matrix size
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
 * @brief Gives values for each space of a matrix
 * @param MA Matrix A
 * @param MB Matrix B
 * @param MC Matrix C
 * @param size Size of the matrix
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

/**
 * @brief Fuction to print matrix of type double pointer
 * 
 * @param M matrix of type double pointer to print
 * @param size Matrix size
 * @param name Name matrix
 * @param id id of process
 */
void printMatrix(double **M, int size, char const *name){
	int i, j; /*indexes*/
	if (size < 5)
	{
		printf("%s\n", name);
		for (i = 0; i < size; ++i)
		{
			for (j = 0; j < size; ++j)
			{
				printf("	%.2f", M[i][j]);
			}
			printf("\n");
		}
		printf("----------------------------------------------------------\n");
	}
}

/**
 * @brief Function to print resultant matrix
 * 
 * @param M That is the matrix to be printed
 * @param size That is the size N of a matrix NxN
 * @param name That is the matrix name
 * @param id That is the process id
 * @param p That is the world processors number
 */
void printResultantMatrix(double **M, int size, char const *name, int id,int p){
  int i, j; /*indexes*/
  int portionSize, initRow, endRow;
  portionSize = size / p;	      	    // Sets matrix A's portion for sending to each processor.
	initRow = id * portionSize;	      // Beggining of the row.
	endRow = (id + 1) * portionSize;  // End of the row.
	if (size < 5){
		if(id ==0)
			printf("%s\n", name);
		for (i = initRow; i < endRow; ++i){
			for (j = 0; j < size; ++j)
				printf("	%.2f", M[i][j]);
			printf("\n");
		}
    if (size ==endRow)
		  printf("----------------------------------------------------------\n");
	}
}