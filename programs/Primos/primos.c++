# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
# include <ctime>

# include "mpi.h"

using namespace std;

int main ( int argc, char *argv[] );
int prime_number ( int n, int id, int p );

int main ( int argc, char *argv[] )

{
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

  n_lo = 1;
  n_hi = 131072;
  n_factor = 2;
  MPI::Init ( argc, argv );
  p = MPI::COMM_WORLD.Get_size (  );
  id = MPI::COMM_WORLD.Get_rank ( );

  n = n_lo;

  while ( n <= n_hi )
  {
    if ( id == master )
    {
      wtime = MPI::Wtime ( );
    }
    MPI::COMM_WORLD.Bcast( &n, 1, MPI::INT, master );

    primes_part = prime_number( n, id, p );

    MPI::COMM_WORLD.Reduce(&primes_part, &primes, 1, MPI::INT, MPI::SUM, master );

    if ( id == master )
    {
      wtime = MPI::Wtime ( ) - wtime;
      totaltime += wtime;
    }
    n = n * n_factor;
  }
  MPI::Finalize ( );

  
  if ( id == master )
  {
    cout<<totaltime<<endl;
  }
  return 0;
}

int prime_number ( int n, int id, int p )

{
  int i;
  int j;
  int prime;
  int total;

  total = 0;

  for ( i = 2 + id; i <= n; i = i + p )
  {
    prime = 1;
    for ( j = 2; j < i; j++ )
    {
      if ( ( i % j ) == 0 )
      {
        prime = 0;
        break;
      }
    }
    total = total + prime;
  }
  return total;
}