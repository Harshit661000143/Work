#include <stdio.h>
#include<conio.h>
#include<math.h>
#include<cuda.h>
__global__ void copy((int n,__global float *A,int incx, __global float *B,int incy)
 
{
int tx=blockIdx.x*N+threadIdx.x;
if((tx*incx<n)&&(tx*incy<n))
{A[tx*incy]= B[tx*incx];
}
}

int main( int argc,char **argv ) {
 int n,i,incx,incy;
float alpha;
   n=atoi(argv[1]);
incx=atoi(argv[2]);
incy=atoi(argv[3]);
  float *A = (float*)malloc(sizeof(float)*n);
    float *B = (float*)malloc(sizeof(float)*n);    
    for(i = 0; i < n; i++) 
{
        A[i] = 0.0;
        B[i] = 1.0;
    }

int x;
if(n%16==0){   
 x = n;

}
else{
x=(int)((floor(n/16)+1)*16);
}

int *dev_a, *dev_b, *dev_c;
// allocate the memory on the GPU
HANDLE_ERROR( cudaMalloc( (void**)&dev_a,n * sizeof(float) ) );
HANDLE_ERROR( cudaMalloc( (void**)&dev_b,n * sizeof(float) ) );

// fill the arrays 'a' and 'b' on the CPU
    for(i = 0; i < n; i++) 
{
        A[i] = 0.0;
        B[i] = 1.0;
    }

//copy the arrays
HANDLE_ERROR(cudaMemcpy(dev_a,a,n*sizeof(float),cudaMemcpyHostToDevice));
HANDLE_ERROR(cudaMemcpy(dev_b,b,n*sizeof(float),cudaMemcpyHostToDevice));
copy<<<x,16>>>(n,dev_a,incx,dev_b,incy);
HANDLE_ERROR(cudaMemcpy(a,dev_a,n*sizeof(float),cudaMemcpyDeviceToHost));
 
printf("A=\t");  
  for(i = 0; i < n; i++)
{
printf("%f\t",A[i]);
}

printf("\nB=\t");  
  for(i = 0; i <n ; i++)
{
printf("%f\t",B[i]);
}
cudaFree(dev_a);
cudaFree(dev_b);

return 0;
}
}
