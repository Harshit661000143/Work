#include<stdio.h>
#include"sample.h"
#include<stdlib.h>

int main(int argc,char** argv)
{
int i;
int n=atoi(argv[1]);
int incx=atoi(argv[2]);
int incy=atoi(argv[3]);
float *A = (float*)calloc(n,sizeof(float));
float *B = (float*)calloc(n,sizeof(float));
float g=0;
for(i=0;i<n;i++)
{
A[i]=1.0;
B[i]=1.0;
}
g = dot(n,A,incx,B,incy);
//for(i=0;i<n;i++)

 printf("\nc=%f\n ",g);

return 0;
}
