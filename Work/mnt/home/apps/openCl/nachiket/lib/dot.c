#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <math.h>
float dot(int n,float *A,int incx, float *B, int incy) {
    // Create the two input vectors
    int i;
float j;
   
cl_ulong start1,start2,start3,end1,end2,end3,start4,end4; 

cl_event event1,event2,event3,event4; 
    float *D = (float*)calloc(n,sizeof(float));


 // Load the kernel source code into the array source_str
//  const char *source ="__kernel void dot_pro(__global int* A, __global int* B,__global int* D, __global int* C, const int m){int lsum=0;__local sum[16];int i;C[0]=0;int x=get_global_id(0);D[x]=0;if(x<m){sum[get_local_id(0)]=A[x]*B[x];} barrier(CLK_LOCAL_MEM_FENCE);if(get_local_id(0)==0){for(i=0;i<16;i++){lsum+=sum[i];}D[x]=lsum; }}";

   //const char *source ="__kernel void dot_pro(__global float* A, __global float* B,__global float* D, __global float* C, const int m){float lsum=0;__local float sum[16];sum[get_local_id(0)]=0;int i;C[0]=0;int x=get_global_id(0);D[x]=0;if(x<m){sum[get_local_id(0)]=A[x]*B[x];} barrier(CLK_LOCAL_MEM_FENCE);if(get_local_id(0)==0){for(i=0;i<16;i++){lsum+=sum[i]; }D[x]=lsum; }}";

  
const char *source ="__kernel void dot_pro(__global float* A, __global float* B,__global float* D, const int m, int incx, int incy){float lsum=0;__local float sum[16];sum[get_local_id(0)]=0;int i;int x=get_global_id(0);D[x]=0;if(x*incx<m&&x*incy<m){sum[get_local_id(0)]=A[x*incx]*B[x*incy];} barrier(CLK_LOCAL_MEM_FENCE);if(get_local_id(0)==0){for(i=0;i<16;i++){lsum+=sum[i]; }D[x]=lsum; }}";

  
const char *err="-cl-fast-relaxed-math";
    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
   cl_command_queue command_queue = clCreateCommandQueue( context,device_id,CL_QUEUE_PROFILING_ENABLE, NULL );

    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,n * sizeof(float), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(float), NULL, &ret);
    cl_mem d_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, n * sizeof(float), NULL, &ret);

   
    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(float), A, 0, NULL, &event1);
ret=clWaitForEvents(1, &event1);
if(ret!=CL_SUCCESS)
{
printf("wrong1");}
clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start1, NULL);
clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end1, NULL); 

ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n * sizeof(float), B, 0, NULL, &event2);
 ret=clWaitForEvents(1, &event2);
if(ret!=CL_SUCCESS)
{
printf("wrong2");}
clGetEventProfilingInfo(event2, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start2, NULL);
clGetEventProfilingInfo(event2, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end2, NULL); 
   
// Create a program from the kernel source
   
cl_program program = clCreateProgramWithSource( context,1,&source,NULL, &ret );

  if(ret!=CL_SUCCESS)
{
printf("\nError in creating program");

}
  // Build the program
    ret = clBuildProgram(program, 1, &device_id,err, NULL, NULL);

if(ret!=CL_SUCCESS)
{
printf("\nError in building program");

}
    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "dot_pro", &ret);
if(ret!=CL_SUCCESS)
{
printf("\nError in creating kernel");

}
  // Set the arguments of the kernel
   ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument1");

}
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument2");

}
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&d_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument3");

}
    ret = clSetKernelArg(kernel, 3, sizeof(int), &n);
    if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument4");

}

    ret = clSetKernelArg(kernel, 4, sizeof(int), &incx);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting fifth kernel arg");
        
   }

    ret = clSetKernelArg(kernel, 5, sizeof(int), &incy);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting sixth kernel arg");
        
   }


size_t global_item_size,local_item_size;   
if(n%16!=0)
{
global_item_size=(int)(floor(n/16)+1)*16;
local_item_size=16;
}
else
{
global_item_size=n;
local_item_size=16;
}

 ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size,&local_item_size, 0, NULL, &event3);
if(ret!=CL_SUCCESS)
{
printf("\nNDRange kernel error");

}
ret=clWaitForEvents(1, &event3);
if(ret!=CL_SUCCESS)
{
printf("wrong3");}
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start3, NULL);
clGetEventProfilingInfo(event3, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end3, NULL); 
    // Read the memory buffer C on the device to the local variable C
    
    ret = clEnqueueReadBuffer(command_queue, d_mem_obj, CL_TRUE, 0, n* sizeof(float), D, 0, NULL, &event4);

if(ret!=CL_SUCCESS)
{
printf("\nError in getting back D");
}
ret=clWaitForEvents(1, &event4);
if(ret!=CL_SUCCESS)
{
printf("wrong4");}
clGetEventProfilingInfo(event4, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start4, NULL);
clGetEventProfilingInfo(event4, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end4, NULL); 
   
// Display the result to the screen
/*
 printf("\nA=\t");  
  for(i = 0; i < n; i++)
{
printf("%f ",A[i]);
}
printf("\nB=\t");  
  for(i = 0; i < n; i++)
{
printf("%f ",B[i]);
}
printf("\n");
*/
j=0;
  for(i = 0; i < n; i++)
{
j=j+D[i];
}
printf("\n");

 float time1 =((end1 - start1)*1.0e-6f);
 float time2 =((end2 - start2)*1.0e-6f);
float time3 =((end3 - start3)*1.0e-6f);
float time4 =((end4 - start4)*1.0e-6f);
printf("%d %f\n",n,time1+time2+time3+time4);




//clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(A);
    free(B);

    return j;
}

