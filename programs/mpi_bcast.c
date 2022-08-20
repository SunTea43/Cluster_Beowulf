#include <stdio.h>
#include "mpi.h"

/*Varaible of high value to reserve memory*/
#define DATA_SZ (1024*1024*64*3)

/*Memory space acording reserve memory value*/
static double MEM_CHUNK[DATA_SZ];

void printMatrix(int SZ, double *M, char *name);
////////////
//MPI_Bcast
////////////
//
// int MPI_Bcast( void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm )
//
// This example simply uses MPI_Bcast to broadcast a read in value to all other processes from root process
//
// example usage:
//		compile: mpicc -o mpi_bcast mpi_bcast.c
//		run: mpirun -n 4 mpi_bcast
//
int main(int argc,char **argv){

	int rank;
    /*Apuntamos los vectores (creacion) a espacio de memoria reservada con dimension NxN */
    double *value;
    value = MEM_CHUNK;
    int SZ=3;
    int i, j;
	for (i = 0; i < SZ; ++i)
	{
		for (j = 0; j < SZ; ++j)
		{
			value[j + i * SZ] = 3.2 * (i + j);
			
		}
	}
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //what rank is the current processor

    if (rank == 0) {
        // if root process we read the value to broadcast
        // printf("Enter a number to broadcast:\n");
	    // scanf("%d", &value);
    } else {
        printf("Before\n");
        printMatrix(SZ,value,"value");
        printf("\n");
	}

    // each processor calls MPI_Bcast, data is broadcast from root processor and ends up in everyone value variable
    // root process uses MPI_Bcast to broadcast the value, each other process uses MPI_Bcast to receive the broadcast value
    MPI_Bcast(&value, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    printf("process %d: After MPI_Bcast, value is \n", rank);
    printMatrix(SZ,value,"value");
    MPI_Finalize();

	return 0;
}

/**
 * @brief: Print a matrix
 * @param SZ: Size of the matrix
 */
void printMatrix(int SZ, double *M, char *name)
{
	int i, j;
	if (SZ < 5)
	{
		printf("%s", name);
		for (i = 0; i < SZ; ++i)
		{
			for (j = 0; j < SZ; ++j)
			{
				printf("	%.2f", M[j + i * SZ]);
			}
			printf("\n");
		}
		printf("---------------------------------------------------------\n");
	}
}