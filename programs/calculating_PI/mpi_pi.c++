#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include<float.h>
# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <ctime>

# include "mpi.h"

using namespace std;

#ifdef LDBL_DECIMAL_DIG
  #define OP_DBL_Digs (LDBL_DECIMAL_DI)
#else  
  #ifdef DECIMAL_DIG
    #define OP_DBL_Digs (DECIMAL_DIG)
  #else  
    #define OP_DBL_Digs (LDBL_DIG + 100)
  #endif
#endif

long double get_pi(long int n, int id, int p);

int main(int argc, char *argv[]){
    int i;
    int id;
    int master = 0;
    int n;
    int n_factor;
    int n_hi;
    int n_lo;
    int p;
    long double total;
    long double total_part;
    double wtime;
    double totaltime=0;



    MPI::Init(argc, argv);
    p = MPI::COMM_WORLD.Get_size();
    id = MPI::COMM_WORLD.Get_rank();
    
    // Serie's limit.
    n         = 1;
    n_factor  = 10;
    n_hi      = 10e6;


    while(n <= n_hi){
        
        if(id == master){
            wtime = MPI::Wtime();
        }

        MPI::COMM_WORLD.Bcast(&n, 1, MPI::INT, master);
        total_part = get_pi(n, id, p);
        MPI::COMM_WORLD.Reduce(&total_part, &total, 1, MPI::LONG_DOUBLE, MPI::SUM, master);

        if(id == master){
            wtime = MPI::Wtime() - wtime;
            totaltime += wtime;
            printf("\nPI = %.*Lf\n", OP_DBL_Digs, total);
        }
        n = n * n_factor;
    }

    MPI::Finalize();

    if(id == master){
        cout<<totaltime<<endl;
    }

    return 0;
}

long double get_pi(long int n, int id, int p){
    long int i;
    long double sum = 0.0, term, pi;

    int total;

    total = 0;

    for ( i = 1 * id; i <= n; i = i + p){
        
        /* Applying Leibniz Formula */    
        term = pow(-1, i) / (2 * i + 1);
        sum += term;
    }

    pi = 4 * total;
    //printf("\nPI = %.*Lf\n", OP_DBL_Digs, pi);

    return pi;

	}