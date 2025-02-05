/* File:       pi-MPI.c
 * Source:     https://www.cs.usfca.edu/~mmalensek/cs220/schedule/code/week09/pi-mpi.c.html
 * Purpose:    Estimates pi using the Leibniz formula parallelized with MPI
 * Compile:    mpicc -g -Wall -o pi-mpi pi-mpi.c
 * Run:        mpiexec -n <number of processes> pi-mpi
 */

#include <stdio.h>
#include <math.h>
#include <mpi.h>

/* We define pi here so we can check and see how accurate our computation is. */
#define PI 3.141592653589793238462643

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int processes, pe;
    MPI_Comm_size(MPI_COMM_WORLD, &processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &pe);

    /* Let's prompt for the number of intervals. We'll broadcast whatever
     * process 0 reads to the other processes. We could use command line
     * arguments instead, but then there'd be no reason to broadcast! */
    int intervals;
    if (pe == 0) {
        printf("Number of intervals: ");
        fflush(stdout);
        scanf("%d", &intervals);
    }

    double time1 = MPI_Wtime();

    MPI_Bcast(&intervals, 1, MPI_INT, 0, MPI_COMM_WORLD);

    long int count = intervals / processes;
    long int start = count * pe;
    long int end = count * pe + count;

    double i;
    double subtotal, total = 0;
    for (i = start; i < end; ++i) {
        subtotal += pow(-1, i) / (2 * i + 1);
    }

    MPI_Reduce(&subtotal, &total, 1, MPI_DOUBLE, MPI_SUM,
        0, MPI_COMM_WORLD);

    double time2 = MPI_Wtime();

    if (pe == 0) {
        total = 4 * total;
        printf("Result:   %.50lf\n", total);
        printf("Accuracy: %.50lf\n", PI - total);
        printf("Time:     %.10lf\n", time2 - time1);
    }

    MPI_Finalize();
}