#include <stdio.h>
#include<conio.h>
#include<math.h>
#include<cuda.h>

__global__ void max(__global float *A,int m,int incx)
{
int i=blockIdx.x*N+threadIdx.x;
int j=threadIdx.x;
__shared__ float asa[16];

asa[j]=0;
if(i*incx<m)
{
asa[j]=A[i*incx];
int k;
 if(j==0){int max=asa[0];
for(k=0;k<16;k++)
{
if(max<asa[k]){max=asa[k];	
}
}
A[get_group_id(0)]=max;
}
}
}

int main(int argc,char **argv)
{
 int n,incx,i,mm;
// printf("enter size of array");
//scanf("%d",&n);
n=atoi(argv[1]);
incx=atoi(argv[2]);
float *A = (float*)malloc(sizeof(float)*n);
int mm=n;
int x;
if(n%16==0){   
 x = n;
}
else{
x=(int)((floor(n/16)+1)*16);
}
int xx=x/16;
int *dev_a;
// allocate the memory on the GPU
HANDLE_ERROR( cudaMalloc( (void**)&dev_a,n * sizeof(float) ) );

for(i = 0; i < n; i++) 
{
A[i] =i;
}


//copy the arrays
HANDLE_ERROR(cudaMemcpy(dev_a,a,n*sizeof(float),cudaMemcpyHostToDevice));

while(mm!=0)
{
max<<<x,16>>> (n,dev_a,incx);

if(x%16!=0)
{
x=(int)(floor(xx/16)+1)*16;
}
else
{
x=xx;
}
xx=x/16;
mm=mm/16;
incx=1;

}
HANDLE_ERROR(cudaMemcpy(a,dev_a,a*sizeof(float),cudaMemcpyDeviceToHost));
 
printf("max=\t");  
  
printf("%f\t",A[0]);

cudaFree(dev_a);


return 0;
}
}
