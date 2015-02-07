#define SIZE 32
__kernel void matmul (__global float *A, __global float *B,__global float *C, int size)
{
int x=get_global_id(0);
int y=get_global_id(1);
int x_local=get_local_id(0);
int y_local=get_local_id(1);
int i,j,num_grp;
int flag=0;
int lim;

__local float As[SIZE][SIZE];
__local float Bs[SIZE][SIZE];
__local float Cs[SIZE][SIZE];

Cs[y_local][x_local]=0.0;

num_grp=get_num_groups(0);
#if 1

for(i=0;i<num_grp;i++)
{
#if 1
{
if((x_local+i*get_local_size(0)<size)&&(y<size))
{
As[y_local][x_local]=A[y*size+x_local+i*get_local_size(0)];
flag=1;
}
if((x<size)&&((y_local+i*get_local_size(0))<size))
{Bs[y_local][x_local]=B[(y_local+i*get_local_size(0))*size+x];
flag=1;
}
//Cs[y_local][x_local]=0.0;

#endif
#if 1
if(flag==1)
{
if(i<(int)(size/get_local_size(0)))
{
lim=get_local_size(0);
}

else
{
lim=size%get_local_size(0);
}
for(j=0;j<lim;j++)
{

Cs[y_local][x_local]+=As[y_local][j]*Bs[j][x_local];

}
}
}
barrier(CLK_LOCAL_MEM_FENCE);

}



#endif
if((x<size)&&(y<size))
{
C[y*size+x]=9;
C[y*size+x]=Cs[y_local][x_local];
}


#endif

}
