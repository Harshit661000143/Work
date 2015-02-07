#include<stdio.h>
#include<stdlib.h>
main(int argc,char **argv)
{
int i;
float j=0;
int n=atoi(argv[1]);
int incx=atoi(argv[2]);
int incy=atoi(argv[3]);
float *A = (float*)malloc(sizeof(float)*n);
float *B = (float*)malloc(sizeof(float)*n);
for(i=0;i<n;i++)
{
A[i]=rand()%100;
B[i]=rand()%100;
}
for(i=0;i<n;i++)
{
if(i*incx<n&&i*incy<n)
{j+=A[incx*i]*B[incy*i];}
}
printf("%f",j);
}
