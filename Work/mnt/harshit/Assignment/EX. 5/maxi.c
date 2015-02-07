#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
int main(void) {
    // Create the two input vectors
    int i,n,j;
j=1;

  
   printf("enter size of array");
	scanf("%d",&n);	
    int *A = (int*)malloc(sizeof(int)*n);
    int *max = (int*)malloc(sizeof(int)*j);
printf("enter value of elements");
    for(i = 0; i < n; i++) {
      scanf("%d",&A[i]);
    }
max[0]=A[0];


   const char *source ="__kernel void max( __global int *A,__global int *max){int i = get_global_id(0);int m=A[i]; if(m>max[0]) {max[0]=m;}}";

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
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id,0, &ret);

    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, n * sizeof(int), NULL, &ret);
   
    cl_mem max_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, j * sizeof(int), NULL, &ret);

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(int), A, 0, NULL, NULL);
  
    ret = clEnqueueWriteBuffer(command_queue, max_mem_obj, CL_TRUE, 0,j * sizeof(int), max, 0, NULL, NULL);
    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, &source, NULL, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "max", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&max_mem_obj);
   
     // Execute the OpenCL kernel on the list
    size_t global_item_size = n; // Process the entire lists
  size_t local_item_size = 1;//  Process one item at a time
 
 ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size, &local_item_size, 0, NULL, NULL);

  // Read the memory buffer C on the device to the local variable C
  
    ret = clEnqueueReadBuffer(command_queue, max_mem_obj, CL_TRUE, 0,j * sizeof(int), max, 0, NULL, NULL);

    // Display the result to the screen
    for(i = 0; i < n; i++)
  printf("%d : %d\n", i, A[i]);
printf("max is %d",max[0]);

    return 0;
}

