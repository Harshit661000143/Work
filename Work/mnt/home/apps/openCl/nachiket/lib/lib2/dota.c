#include<stdio.h>
#include"nsample.h"
#include<CL/cl.h>
main(int argc,char** argv)
{
int i;
int n=atoi(argv[1]);
int incx=atoi(argv[2]);
int incy=atoi(argv[3]);
float *A = (float*)malloc(sizeof(float)*n);
float *B = (float*)malloc(sizeof(float)*n);
cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
cl_ulong start1,start2,start3,end1,end2,end3,start4,end4;
float x=3;
cl_event event1,event2,event3,event4;

if(ret!=CL_SUCCESS)
{
printf("platform id error");
}
ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

if(ret!=CL_SUCCESS)
{
printf("device id error");
}
    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("context error");}
    // Create a command queue
   cl_command_queue command_queue = clCreateCommandQueue( context,device_id,CL_QUEUE_PROFILING_ENABLE, &ret );
if(ret!=CL_SUCCESS)
{
printf("queue error");}
    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,n * sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, n * sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("b mem error");}
for(i=0;i<n;i++)
{
A[i]=rand()%100;
B[i]=rand()%100;
}
    // Copy the lists A and B to their respective memory buffers
ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(float), A, 0, NULL, NULL);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n * sizeof(float), B, 0, NULL, NULL);

float j;
j = dot(n,A,incx,B,incy,device_id,context,command_queue,a_mem_obj,b_mem_obj); 
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

 printf("\n%f\t\n",j);
return 0;
}
