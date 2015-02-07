#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<pthread.h>
#include<unistd.h>
#include<math.h>
#include<sys/time.h>
FILE *fp;
void *mult_thread(void *t);
int *a,*b,*c,N;
int main(int argc,char *argv[])
{

	struct timeval start,stop; 
	int *d,*e,asource,adst,bsource,bdst,xrank,yrank,num_xrank,numproc,myrank,i,j,s,k,rc[2],v;

	fp=fopen("result2.txt","w");
	MPI_Init(&argc,&argv);
	MPI_Status status1,status2,status3,status4,status5;
	MPI_Request  request1,request2,request3,request4,request5;
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&numproc);
	num_xrank = sqrt(numproc);
	xrank =  myrank/num_xrank;
	yrank =  myrank%num_xrank;
	s = atoi(argv[1]);     
	N= s/sqrt(numproc);

	pthread_t id[2];

	e = (int *) malloc(N*N*sizeof(int));
	a = (int *) malloc(N*N*sizeof(int));
	b = (int *) malloc(N*N*sizeof(int));
	c = (int *) calloc(N*N,sizeof(int));
	if(myrank==0) 
		d = (int *) calloc(s*s,sizeof(int));
	
	srand(1000*myrank);
	for(i=0;i< N*N;i++)
	{    
		a[i]=rand()%10;
		b[i]=rand()%10;


	}   

	MPI_Gather(a,N*N,MPI_INT,d,N*N,MPI_INT,0,MPI_COMM_WORLD);
	if(myrank==0)
	{
		for(k=0;k<num_xrank;k++)
		{
			for(i=0;i<N ;i++)
			{
				for(j=0;j<num_xrank;j++)
				{
					MPI_Isend(d+(j*N*N+i*N+k*N*num_xrank*N),N,MPI_INT,(i*num_xrank+j)/N+k*num_xrank,77,MPI_COMM_WORLD,&request5);
				}
			}
		}
	}
	for(i=0;i<N;i++)
	{
		MPI_Recv(e+i*N,N,MPI_INT,0,77,MPI_COMM_WORLD,&status5);
	}
	MPI_Gather(e,N*N,MPI_INT,d,N*N,MPI_INT,0,MPI_COMM_WORLD);

	if(myrank==0)
	{
		printf("value of a is\n");
		fprintf(fp,"value of a is\n ");
		for(i=0;i<s;i++)
		{
			for(j=0;j<s;j++)
			{
				fprintf(fp,"%d ",d[i*s+j]);
				printf("%d\t",d[i*s+j]);
			}
			fprintf(fp,"\n ");
			printf("\n");
		}
		printf("\n\n");



	}


	MPI_Gather(b,N*N,MPI_INT,d,N*N,MPI_INT,0,MPI_COMM_WORLD);
	if(myrank==0)
	{
		for(k=0;k<num_xrank;k++)
		{
			for(i=0;i<N ;i++)
			{
				for(j=0;j<num_xrank;j++)
				{
					MPI_Isend(d+(j*N*N+i*N+k*N*num_xrank*N),N,MPI_INT,(i*num_xrank+j)/N+k*num_xrank,77,MPI_COMM_WORLD,&request5);
				}
			}
		}
	}
	for(i=0;i<N;i++)
	{
		MPI_Recv(e+i*N,N,MPI_INT,0,77,MPI_COMM_WORLD,&status5);
	}
	MPI_Gather(e,N*N,MPI_INT,d,N*N,MPI_INT,0,MPI_COMM_WORLD);
	if(myrank==0)
	{
		printf("value of b is\n");
		fprintf(fp,"value of b is\n");
		for(i=0;i<s;i++)
		{
			for(j=0;j<s;j++)
			{
				fprintf(fp,"%d ",d[i*s+j]);
				printf("%d\t",d[i*s+j]);
			}
			fprintf(fp,"\n");
			printf("\n\n");
		}

	}


gettimeofday(&start,0); 
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
					asource=myrank-(num_xrank-1);
				else
					asource=myrank+1;

				MPI_Isend(a,N*N,MPI_INT,adst ,99,MPI_COMM_WORLD,&request1);            
				MPI_Recv(a,N*N,MPI_INT,asource,99,MPI_COMM_WORLD,&status1);                  


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
					bsource=myrank-(num_xrank-1)*num_xrank;
				else
					bsource=myrank+num_xrank;


				MPI_Isend(b,N*N,MPI_INT,bdst,88,MPI_COMM_WORLD,&request2);  
				MPI_Recv(b,N*N,MPI_INT,bsource,88,MPI_COMM_WORLD,&status2);                 


			}
		}
	}

	for(i=0 ; i< num_xrank ;i++)
	{
		for(j=0;j<2;j++)
		{
			pthread_create(&id[j],NULL,mult_thread,&j);


		}
		for(j=0;j<2;j++)
		{
			pthread_join(id[j],NULL);
		}

		if(yrank==0)
			adst = myrank+(num_xrank-1);
		else
			adst = myrank-1;
		if(yrank==num_xrank-1)
			asource=myrank-(num_xrank-1);
		else
			asource=myrank+1;
		if(xrank==0)   
			bdst = myrank+(num_xrank-1)*num_xrank;
		else
			bdst = myrank-num_xrank;
		if(xrank== num_xrank-1)
			bsource=myrank-(num_xrank-1)*num_xrank;
		else
			bsource=myrank+num_xrank;
		MPI_Isend(a,N*N,MPI_INT,adst ,45,MPI_COMM_WORLD,&request3);
		MPI_Isend(b,N*N,MPI_INT,bdst,55,MPI_COMM_WORLD,&request4);
		MPI_Recv(a,N*N,MPI_INT,asource,45,MPI_COMM_WORLD,&status3);
		MPI_Recv(b,N*N,MPI_INT,bsource,55,MPI_COMM_WORLD,&status4);

	}
gettimeofday(&stop,0);
fprintf(fp,"Time = %.6f\n\n",
			(stop.tv_sec+stop.tv_usec*1e-6)-(start.tv_sec+start.tv_usec*1e-6));
	MPI_Gather(c,N*N,MPI_INT,d,N*N,MPI_INT,0,MPI_COMM_WORLD);
	if(myrank==0)
	{
		for(k=0;k<num_xrank;k++)
		{
			for(i=0;i<N ;i++)
			{
				for(j=0;j<num_xrank;j++)
				{
					MPI_Isend(d+(j*N*N+i*N+k*N*num_xrank*N),N,MPI_INT,(i*num_xrank+j)/N+k*num_xrank,77,MPI_COMM_WORLD,&request5);
				}
			}
		}
	}
	for(i=0;i<N;i++)
	{
		MPI_Recv(e+i*N,N,MPI_INT,0,77,MPI_COMM_WORLD,&status5);
	}
	MPI_Gather(e,N*N,MPI_INT,d,N*N,MPI_INT,0,MPI_COMM_WORLD);
	if(myrank==0)
	{
		printf("value of c is\n");
		fprintf(fp,"value of c is\n");
		for(i=0;i<s;i++)
		{
			for(j=0;j<s;j++)
			{
				fprintf(fp,"%d ",d[i*s+j]);
				printf("%d\t",d[i*s+j]);
			}
			fprintf(fp,"\n");
			printf("\n");
		}

	}
	
	

	fclose(fp);

	MPI_Finalize();
}
void * mult_thread(void *t)
{

	int i,j,k,r,id;
	id =  *(int*) t;
	printf("id=%d\n");
	if(N%2==0)
	{
		for(i=id*N/2;i< (id+1)*N/2;i++)
		{
			for(j=0;j<N;j++)
			{
				for(k=0;k<N;k++)
				{
					c[i*N+j] += a[i*N+k]*b[k*N+j];
				}
			}
		}
	}
	else if(N%2!=0)
	{
		if(id==0)
		{         
			for(i=0;i< N/2;i++)
			{
				for(j=0;j<N;j++)
				{
					for(k=0;k<N;k++)
					{
						c[i*N+j] += a[i*N+k]*b[k*N+j];
					}
				}
			}}
			if(id==1)
			{
				for(i=N/2;i<N;i++)
				{
					for(j=0;j<N;j++)
					{
						for(k=0;k<N;k++)
						{
							c[i*N+j] += a[i*N+k]*b[k*N+j];
						}
					}

				}
			}
	}
}

