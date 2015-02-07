#include<stdio.h>
#include"nsample.h"
#include<CL/cl.h>
main(int argc,char** argv)
{
int i;
int n=atoi(argv[1]);
float alpha=atoi(argv[2]);
int incx=atoi(argv[3]);
int incy=atoi(argv[4]);
float *A = (float*)malloc(sizeof(float)*n);
float *B = (float*)malloc(sizeof(float)*n);
cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
cl_ulong start1,start2,end1,end2;

cl_event event1,event2;

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
A[i]=1.0;
B[i]=1.0;
}
    // Copy the lists A and B to their respective memory buffers
ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(float), A, 0, NULL,&event1 );
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}
ret=clWaitForEvents(1, &event1);
if(ret!=CL_SUCCESS)
{
printf("wrong");}
clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start1, NULL);
clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end1, NULL);

ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n * sizeof(float), B, 0, NULL, &event2);
 ret=clWaitForEvents(1, &event2);
if(ret!=CL_SUCCESS)
{
printf("wrong");}
clGetEventProfilingInfo(event2, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start2, NULL);
clGetEventProfilingInfo(event2, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end2, NULL);

A=xscal(n,alpha,A,incx,device_id,context,command_queue,a_mem_obj,ret);

// A=saxpy(n,alpha,A,incx,B,incy,device_id,context,command_queue,a_mem_obj,b_mem_obj,ret); 
if(ret!=CL_SUCCESS)
{
 printf("a_mem error");
}

for(i=0;i<n;i++)
{
 printf("%f\t",A[i]);
}


return 0;
}
