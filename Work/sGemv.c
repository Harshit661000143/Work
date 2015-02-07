#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include<math.h>
#include<string.h>


void dump_error(cl_int *err)
{

if(err[0]==CL_INVALID_PLATFORM)
{

printf("\nInvalid platform");
}
else if(err[0]==CL_INVALID_PROGRAM_EXECUTABLE)
{
printf("invalid executable");
}
else if (err[0]==CL_INVALID_DEVICE)
{
printf("\nInvalid Device");
}

else if (err[0]==CL_OUT_OF_RESOURCES)
{
printf("\nout of resources");
}

else if(err[0]==CL_INVALID_CONTEXT)
{
printf("\nInvalid Context");
}

else if(err[0]==CL_INVALID_WORK_GROUP_SIZE)
{
printf("\nInval work group size");
}
else if(err[0]==CL_INVALID_KERNEL)
{
printf("\nInvalid kernel");
}

else if(err[0]==CL_INVALID_VALUE)
{
printf("\nInvalid value");
}

else if(err[0]==CL_INVALID_QUEUE_PROPERTIES)
{
printf("\nInvalid properties");
}

else if(err[0]==CL_OUT_OF_HOST_MEMORY)
{
printf("\nOut of host memory");
}

else if(err[0]==CL_INVALID_KERNEL)
{
printf("\nError in kernel launch");
}

else if(err[0]==CL_INVALID_COMMAND_QUEUE)
{
printf("\ninvalid command queue");
}

else if(err[0]==CL_INVALID_KERNEL_ARGS)
{
printf("\ninvalid kernel args");
}

else if(err[0]==CL_INVALID_WORK_ITEM_SIZE)
{
printf("\ninvalid work item size");
}

else if(err[0]==CL_INVALID_GLOBAL_OFFSET)
{
printf("\ninvalid global offset");
}

else if(err[0]==CL_MEM_OBJECT_ALLOCATION_FAILURE)
{
printf("\ninvalid object allocation");
}
else if(err[0]==CL_INVALID_EVENT_WAIT_LIST)
{
printf("\ninvalid object allocation");
}


}


    // Create the two input vectors

main(int argc,char** argv)
{
int i;
int m=atoi(argv[1]);
int n=atoi(argv[2]);
int incx=atoi(argv[5]);
int alpha=atoi(argv[3]);
int beta=atoi(argv[4]);
int incy=atoi(argv[6]);
float *A = (float*)malloc(sizeof(float)*m*n);
float *B = (float*)malloc(sizeof(float)*n);
float *C = (float*)malloc(sizeof(float)*m);
size_t global_item_size,local_item_size, shared_size;   
float *D = (float*)malloc(sizeof(float)*m);
global_item_size=m*n;
local_item_size=n;
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
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,n *m* sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, n * sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("b mem error");}
    cl_mem d_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, m * sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("d mem error");}
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, m * sizeof(float), NULL, &ret);
if(ret!=CL_SUCCESS)
{
printf("c mem error");}
for(i=0;i<n*m;i++)
{
A[i]=1.0;
if(i<m)
{
D[i]=1.0;
}
}
for(i=0;i<n;i++)
{
B[i]=1.0;
}
    // Copy the lists A and B to their respective memory buffers
ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * m*sizeof(float), A, 0, NULL, NULL);
if(ret!=CL_SUCCESS)
{
printf("a_mem error");}

ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n * sizeof(float), B, 0, NULL, NULL);
ret = clEnqueueWriteBuffer(command_queue, d_mem_obj, CL_TRUE, 0, m*sizeof(float), D, 0, NULL, NULL);
if(ret!=CL_SUCCESS)
{
printf("d_mem error");}



 // Load the kernel source code into the array source_stringh  
const char *source ="__kernel void dot_pro(__global float* A, __global float* B,__global float* C,__global float* D, int n,int alpha, int beta, int incx, int incy, __local float* shared ){shared[get_local_id(0)]=0;shared[get_local_id(0)*incx]=B[get_local_id(0)*incx];int i; float j=0;shared[get_local_id(0)]=alpha*A[get_global_id(0)]*shared[get_local_id(0)]; if(get_local_id(0)==0){for(i=0;i<n;i++){j+=shared[i];}if(get_group_id(0)*incy<get_num_groups(0)){C[get_group_id(0)]=j+beta*D[get_group_id(0)*incy];}}}";

//const char *source="__kernel void dot_pro(__global float* A, __global float* B,__global float* C, const int n,const int m, int incx, int incy, __local float* shared){int loc=get_local_id(0);int glo=get_global_id(0);int i,j; j=0;}";
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
    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "dot_pro", &ret);
if(ret!=CL_SUCCESS)
{
printf("\nError in creating kernel");
}
shared_size = n * sizeof(float);
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
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument3");

}
    ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&d_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument3");

}
    ret = clSetKernelArg(kernel, 4, sizeof(int), &n);
    if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument4");
}
    ret = clSetKernelArg(kernel, 5, sizeof(int), &alpha);
    if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument4");
}
    ret = clSetKernelArg(kernel, 6, sizeof(int), &beta);
    if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument4");
}

    ret = clSetKernelArg(kernel, 7, sizeof(int), &incx);
   
  if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting 6th kernel arg");
        
   }

    ret = clSetKernelArg(kernel, 8, sizeof(int), &incy);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting 7th kernel arg");
        
   }
ret= clSetKernelArg(kernel, 9, shared_size, NULL);
  if (ret!=CL_SUCCESS) {
       printf("\nerror in setting 8th kernel arg");
        
   }
 ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size,&local_item_size, 0, NULL, NULL);
if(ret!=CL_SUCCESS)
{
dump_error(&ret);
printf("\nNDRange kernel error");
}
    // Read the memory buffer C on the device to the local variable C
    
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, m* sizeof(float), C, 0, NULL, NULL);

if(ret!=CL_SUCCESS)
{
printf("\nError in getting back c");
}


printf("\nC=\n");

//float time3 =((end3 - start3)*1.0e-6f);
#if 1
for(i=0;i<m;i++)
{

printf("%f ",C[i] );
}
#endif
printf("\n");
    ret = clFlush(command_queue);
ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    return 0;
}

