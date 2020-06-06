#include <stdio.h> 

#include <mpi.h> 

  

int main(int argc, char **argv) 

{ 

    int i,n,pid,npr; 

    double x, base, suma=0.0,pi_local,pi; 

     

    MPI_Init(&argc, &argv); 

  

    MPI_Comm_rank(MPI_COMM_WORLD, &pid); 

    MPI_Comm_size(MPI_COMM_WORLD, &npr); 

     

    if(pid==0) 

    { 

    //~ printf("nro de intervalos"); 

    //~ scanf("%d",&n); 

    n=2000000000; 

    } 

     

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD); 

     

    base=1.0/(double)n; 

    for (i = pid; i < n; i+=npr) 

    { 

        x=i*base; 

        suma=suma+((4.0/(1+x*x))); 

    } 

    pi_local=suma*base;     

     

    MPI_Reduce(&pi_local,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD); 

     

    if(pid==0) 

    { 

        printf("Rta=%lf\n",pi); 

    } 

    MPI_Finalize();     

    return 0; 

} 