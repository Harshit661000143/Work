#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include<math.h>
#include<string.h>

    // Create the two input vectors

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
ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(float), A, 0, NULL, NULL);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n * sizeof(float), B, 0, NULL, NULL);


float j;
  
cl_ulong start3,end3; 

cl_event event3; 
    float *D = (float*)calloc(n,sizeof(float));


 // Load the kernel source code into the array source_stringh  
const char *source ="__kernel void dot_pro(__global float* A, __global float* B,__global float* D, const int m, int incx, int incy){float lsum=0;__local float sum[16];sum[get_local_id(0)]=0;int i;int x=get_global_id(0);D[x]=0;if(x*incx<m&&x*incy<m){sum[get_local_id(0)]=A[x*incx]*B[x*incy];} barrier(CLK_LOCAL_MEM_FENCE);if(get_local_id(0)%8==0){for(i=0;i<8;i++){lsum+=sum[i]; }D[x]=lsum; }}";

  

    cl_mem d_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, n * sizeof(float), NULL, &ret);
// Create a program from the kernel source
   
cl_program program = clCreateProgramWithSource( context,1,&source,NULL, &ret );

  if(ret!=CL_SUCCESS)
{
printf("\nError in creating program");

}
  // Build the program
    ret = clBuildProgram(program, 1, &device_id,NULL, NULL, NULL);

if(ret!=CL_SUCCESS)
{
printf("\nError in building program");

}
char *bindot= (char*)malloc(sizeof(char)*5000);
ret= clGetProgramInfo(program,CL_PROGRAM_BINARIES,5000,&bindot,NULL);
if(ret!=CL_SUCCESS)
{
printf("\nError binary ");
}


 FILE *kk;
kk=fopen("bindot.txt","w");
fwrite(bindot,1,strlen(bindot), kk);
fclose(kk);



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
    
    ret = clEnqueueReadBuffer(command_queue, d_mem_obj, CL_TRUE, 0, n* sizeof(float), D, 0, NULL, NULL);

if(ret!=CL_SUCCESS)
{
printf("\nError in getting back D");
}

  j=0;
  for(i = 0; i < n; i++)
{
j=j+D[i];
}
printf("\n");

float time3 =((end3 - start3)*1.0e-6f);

printf("%f(ans) %f\n",j,time3);
//clean up
    ret = clFlush(command_queue);
ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    return 0;
}

