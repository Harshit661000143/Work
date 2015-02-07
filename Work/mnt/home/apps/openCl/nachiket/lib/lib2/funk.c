#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include<math.h>
#if 1
float *saxpy(int n, float alpha, float *A, int incx, float *B, int incy)
{
  const char *source ="__kernel void saxpy(int n,float alpha,__global float *A,int incx, __global float *B,int incy) {int tx=get_global_id(0);if(tx<n){A[tx*incy]=A[tx*incy]+(alpha* B[tx*incx]);}}";

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
       
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
   cl_command_queue command_queue = clCreateCommandQueue( context,device_id,0, &ret );
if(ret!=CL_SUCCESS)
{
printf("queue error");}
    // Create memory buffers on the device for each vector 

    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,n * sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("b mem error");}



    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(float), A, 0, NULL, NULL);




if(ret!=CL_SUCCESS)
{
printf("a write buffer error");}
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n * sizeof(float), B, 0, NULL, NULL);



if(ret!=CL_SUCCESS)
{
printf("b write buffer error");}

    // Create a program from the kernel source
   
cl_program program = clCreateProgramWithSource( context,1,&source,NULL,&ret  );
if(ret!=CL_SUCCESS)
{
printf("create pgm error");}
    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

if(ret!=CL_SUCCESS)
{
printf("build pgm error");}

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "saxpy", &ret);
if(ret!=CL_SUCCESS)
{
printf("create kernel error");}
    // Set the arguments of the kernel
ret = clSetKernelArg(kernel, 0, sizeof(int),&n );
 ret = clSetKernelArg(kernel, 1, sizeof(float),&alpha );

    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&a_mem_obj);

if(ret!=CL_SUCCESS)
{
printf("arg 0 ");}
ret = clSetKernelArg(kernel, 3, sizeof(int),&incx );

    ret = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&b_mem_obj);

if(ret!=CL_SUCCESS)
{
printf("arg1 ");}
    ret = clSetKernelArg(kernel, 5, sizeof(int),&incy );

    if(ret!=CL_SUCCESS)
{
printf("arg2");}

size_t globalWorkSize;
size_t localWorkSize;
if(n%16==0){   
 globalWorkSize = n;
 localWorkSize=16 ;
}
else{
globalWorkSize=(int)((floor(n/16)+1)*16);
localWorkSize=16;}	 
   
 ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&globalWorkSize,&localWorkSize, 0, NULL,NULL);

if(ret!=CL_SUCCESS)
{
printf("ND RANGE ERROR");}


clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n*sizeof(float), A, 0, NULL, NULL);
clFinish(command_queue);
return A;
}
#endif
float *scalar(int n, float alpha, float *A,int incx)
{
const char *source ="__kernel void kk(__global float* A,float x,int n, int incx ){int i = get_global_id(0);A[i*incx]=x*A[i*incx];}";

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
   cl_command_queue command_queue = clCreateCommandQueue( context,device_id,0, NULL );
    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,n * sizeof(float), NULL, &ret);
    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(float), A, 0, NULL, NULL);   
// Create a program from the kernel source
   
cl_program program = clCreateProgramWithSource( context,1,&source,NULL, &ret );

  if(ret!=CL_SUCCESS)
{
printf("\nError in creating program");

}
  // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

if(ret!=CL_SUCCESS)
{
printf("\nError in building program");

}
    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "kk", &ret);
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
    ret = clSetKernelArg(kernel, 1, sizeof(float), &alpha);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting 2nd kernel arg");
        
   }
 ret = clSetKernelArg(kernel, 2, sizeof(int), &n);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting 3rd kernel arg");
        
   }
ret = clSetKernelArg(kernel, 3, sizeof(int), &incx);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting 4th kernel arg");
        
   }
//Execute the OpenCl kernel


size_t global_item_size,local_item_size;   
if(n%16!=0&&n>=16)
{
global_item_size=(int)(floor(n/16)+1)*16;
local_item_size=16;
}
else if(n%16==0&&n>=16)
{
global_item_size=(int)(floor(n/16))*16;
local_item_size=16;
}
else
{
global_item_size=n;
local_item_size=n;
}

ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size,&local_item_size, 0, NULL, NULL);
if(ret!=CL_SUCCESS)
{
printf("\nNDRange kernel error");

}
//read the memory buffer 
ret = clEnqueueReadBuffer(command_queue,a_mem_obj,CL_TRUE,0,n*sizeof(float),A,0,NULL,NULL);
 // Display the result to the screen
return A;
}

