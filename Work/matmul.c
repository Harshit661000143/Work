#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>
void matrixmul(int *a ,int *b,int *c , int N);
int main(int argc,char *argv[])
{
    int numproc,myrank,i,j,s,k;
    int *a,*b,*c,*d;
    int N;
    int  asrc,adst;
    int  bsrc,bdst;
    int   xrank,yrank;
    int num_xrank;
    MPI_Init(&argc,&argv);
    MPI_Status status1,status2,status3,status4;
    MPI_Request  request1,request2,request3,request4;
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&numproc);
    num_xrank = sqrt(numproc);
    xrank =  myrank/num_xrank;
    yrank =  myrank%num_xrank;
        s = atoi(argv[1]);

       
    N= s/sqrt(numproc);

    a = (int *) malloc(N*N*sizeof(int));
    b = (int *) malloc(N*N*sizeof(int));
    c = (int *) calloc(N*N,sizeof(int));
     if(myrank==0)
     {
     d = (int *) calloc(s*s,sizeof(int));
     } 
    srand(1000*myrank);
    for(i=0;i< N*N;i++)
    {    
        a[i]=rand()%10;
        b[i]=rand()%10;
        
    printf("%d\t%d\n",a[i],b[i]);
    
    }         
    for(i=0;i<num_xrank;i++)
    {
        if(xrank==i)
        {
            for(j=0;j<xrank;j++)
            {
                if(yrank==0)
                    adst = myrank+(num_xrank-1);
                else
                    adst = myrank-1;
                if(yrank==num_xrank-1)
                    asrc=myrank-(num_xrank-1);
                else
                    asrc=myrank+1;
                                  
               MPI_Isend(a,N*N,MPI_INT,adst ,99,MPI_COMM_WORLD,&request1);            
               MPI_Recv(a,N*N,MPI_INT,asrc,99,MPI_COMM_WORLD,&status1);                  
           
               
            }
        }
        if(yrank==i)
        {
            for(j=0;j<yrank;j++)
            {
                if(xrank==0)   
                    bdst = myrank+(num_xrank-1)*num_xrank;
                else
                    bdst = myrank-num_xrank;
                if(xrank== num_xrank-1)
                    bsrc=myrank-(num_xrank-1)*num_xrank;
                else
                    bsrc=myrank+num_xrank;
               
                                    
                 MPI_Isend(b,N*N,MPI_INT,bdst,88,MPI_COMM_WORLD,&request2);  
                MPI_Recv(b,N*N,MPI_INT,bsrc,88,MPI_COMM_WORLD,&status2);                 
           
                               
            }
        }
    }

    for(i=0 ; i< num_xrank ;i++)
    {
        matrixmul(a,b,c,N);
        if(yrank==0)
            adst = myrank+(num_xrank-1);
        else
            adst = myrank-1;
        if(yrank==num_xrank-1)
            asrc=myrank-(num_xrank-1);
        else
            asrc=myrank+1;
        if(xrank==0)   
            bdst = myrank+(num_xrank-1)*num_xrank;
        else
            bdst = myrank-num_xrank;
        if(xrank== num_xrank-1)
            bsrc=myrank-(num_xrank-1)*num_xrank;
        else
            bsrc=myrank+num_xrank;
        MPI_Isend(a,N*N,MPI_INT,adst ,45,MPI_COMM_WORLD,&request3);
        MPI_Isend(b,N*N,MPI_INT,bdst,55,MPI_COMM_WORLD,&request4);
        MPI_Recv(a,N*N,MPI_INT,asrc,45,MPI_COMM_WORLD,&status3);
        MPI_Recv(b,N*N,MPI_INT,bsrc,55,MPI_COMM_WORLD,&status4);

    }

        MPI_Gather(c,N*N,MPI_INT,d,N*N,MPI_INT,0,MPI_COMM_WORLD);
          if(myrank==0)
               {
                   for(i=0;i<s*s;i++)
                    printf("%d\n",d[i]);
                }

MPI_Finalize();
}
void matrixmul(int *a ,int *b,int *c , int N)
{
    int i,j,k;
    for(i=0;i< N ;i++)
    {
        for(j=0;j< N ;j++)
        {
            for(k=0;k< N ;k++)
            {
                 c[i*N+j] = c[i*N+j]+a[i*N+k]*b[k*N+j];
            }
        }
    }
}