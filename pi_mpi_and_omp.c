# include <stdio .h>
# include <stdlib .h>
# include <math .h>
# include <mpi .h>
# include <omp .h>
# define PI 3.1415926535897932384626433832795029 L
# define MTAG1 1
# define MTAG2 2

 double f( double a) { return ( double )4.0/(( double )1.0+( a*a )); }

 int main ( int argc , char * argv [])
 {
 	int n, myid , numprocs , i;
 	double mypi , pi , h, sum , x;

 	MPI_Init (& argc ,& argv );
 	MPI_Comm_size ( MPI_COMM_WORLD ,& numprocs );
 	MPI_Comm_rank ( MPI_COMM_WORLD ,& myid );

 	n = 100000000;
	if (myid == 0 )
 		MPI_Bcast (&n, 1, MPI_INT , 0, MPI_COMM_WORLD );
 
 
 		h = 1.0 / ( double ) n;
 		sum = 0.0;
 		# pragma omp parallel for reduction (+: sum ) private (i,x)
 			for (i = myid + 1; i <= n; i += numprocs ) {
 				x = h * (( double )i - 0.5);
 				sum += f(x);
 			}
 			mypi = h * sum ;

 		MPI_Reduce (& mypi , &pi , 1, MPI_DOUBLE , MPI_SUM , 0, MPI_COMM_WORLD );

 		if ( myid == 0) { printf (" ...\ n", pi , fabs (pi - PI )); }

 	MPI_Finalize ();
 	return EXIT_SUCCESS ;
 }