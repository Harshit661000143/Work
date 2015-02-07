#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include <math.h>

void dump_error(cl_int *err)
{

if(err[0]==CL_INVALID_PLATFORM)
{

printf("\nInvalid platform");
}

else if (err[0]==CL_INVALID_DEVICE)
{
printf("\nInvalid Device");
}

else if(err[0]==CL_INVALID_CONTEXT)
{
printf("\nInvalid Context");
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

else if(err[0]==CL_INVALID_ARG_INDEX)
{
printf("\ninvalid arg index");
}
else if(err[0]==CL_INVALID_ARG_SIZE)
{
printf("\ninvalid arg size");
}
else if(err[0]==CL_INVALID_ARG_VALUE)
{
printf("\ninvalid arg value");
}
else if(err[0]==CL_INVALID_MEM_OBJECT)
{
printf("\ninvalid mem object");
}
else if(err[0]==CL_INVALID_KERNEL)
{
printf("\nError in kernel launch");
}
else if(err[0]==CL_BUILD_PROGRAM_FAILURE)
{
printf("\nBuild program failure");
}
else if(err[0]==CL_INVALID_PROGRAM)
{printf("invalid program");}
}
main()
{
int i,n,x;
printf("the size of array is:");
scanf("\t%d",&n);
printf("\nThe value of x:");
scanf("\t%d",&x);

int *A=(int*)malloc(sizeof(int)*n);
for(i=0;i<n;i++)
{
A[i]=i;
}
 // Load the kernel source code into the array source_str
  const char *source ="__kernel void kk(__global int* A,int x,int n){int i = get_global_id(0);A[i]=x*A[i];}";

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
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE,n * sizeof(int), NULL, &ret);
    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(int), A, 0, NULL, NULL);   
// Create a program from the kernel source
   
cl_program program = clCreateProgramWithSource( context,1,&source,NULL, &ret );

  if(ret!=CL_SUCCESS)
{
printf("\nError in creating program");
dump_error(&ret);
}
  // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

if(ret!=CL_SUCCESS)
{
printf("\nError in building program");
dump_error(&ret);
}
    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "kk", &ret);
if(ret!=CL_SUCCESS)
{
printf("\nError in creating kernel");
dump_error(&ret);
}
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
if(ret!=CL_SUCCESS)
{
printf("\nError in setting argument1");
dump_error(&ret);
}
 

    ret = clSetKernelArg(kernel, 1, sizeof(int), &x);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting 2nd kernel arg");
        dump_error(&ret);
   }
 ret = clSetKernelArg(kernel, 2, sizeof(int), &n);
     if(ret!=CL_SUCCESS)
   {
       printf("\nerror in setting 3rd kernel arg");
        dump_error(&ret);
   }

//Execute the OpenCl kernel

size_t global_item_size = n;
size_t local_item_size = 1;

ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size,&local_item_size, 0, NULL, NULL);
if(ret!=CL_SUCCESS)
{
printf("\nNDRange kernel error");
dump_error(&ret);
}
//read the memory buffer 
ret = clEnqueueReadBuffer(command_queue,a_mem_obj,CL_TRUE,0,n*sizeof(int),A,0,NULL,NULL);
 // Display the result to the screen
for(i=0;i<n;i++)
{
printf("\nthe value of A:\t %d",A[i]);
}
return 0;
}
