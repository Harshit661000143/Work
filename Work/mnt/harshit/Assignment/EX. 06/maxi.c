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

    for(i = 0; i < n; i++)
 {
      A[i]=(2*i+1);
    }
max[0]=A[0];

  
 
    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
   
    cl_int ret = clGetPlatformIDs(1, &platform_id,NULL);
  if (ret !=CL_SUCCESS) {
   printf("Error getting platforms ids:\n ");
   exit(ret);
}
  ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
if (ret !=CL_SUCCESS) {
   printf("Error getting device ids:\n ");
   exit(ret);
}

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
if (ret !=CL_SUCCESS) {
   printf("Error creating context:\n ");
   exit(ret);
}
    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id,0, &ret);
if (ret !=CL_SUCCESS) {
   printf("Error creating command queues:\n ");
   exit(ret);
}
    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, n * sizeof(int), NULL, &ret);
   if (ret !=CL_SUCCESS) {
   printf("Error creating buffer A:\n ");
   exit(ret);
}
    cl_mem max_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, j * sizeof(int), NULL, &ret);
if (ret !=CL_SUCCESS) {
   printf("Error creating buffer max:\n ");
   exit(ret);
}
    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(int), A, 0, NULL, NULL);
  if (ret !=CL_SUCCESS) {
   printf("Error copynig buffer A:\n ");
   exit(ret);
}
    ret = clEnqueueWriteBuffer(command_queue, max_mem_obj, CL_TRUE, 0,j * sizeof(int), max, 0, NULL, NULL);
if (ret !=CL_SUCCESS) {
   printf("Error copying buffer max:\n ");
   exit(ret);
}    

FILE *fp;
    char *source_str;
    int source_size;

    fp = fopen("max.cl", "r");
    if (!fp) {
        printf("Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(1000);
    source_size = fread( source_str, 1, 1000, fp);
    fclose( fp );

// Create a program from the kernel source
cl_program program = clCreateProgramWithSource(context, 1,(const char **)&source_str,(const size_t *)&source_size, &ret);
if (ret !=CL_SUCCESS) {
   printf("Error creating program:\n ");
if (ret==CL_OUT_OF_HOST_MEMORY )
{
printf("out of host memory\n");
}   
//  exit(ret);
}
    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
if (ret !=CL_SUCCESS) {
   printf("Error building program: \n");
if (ret==CL_INVALID_PROGRAM)
{
printf("invalid program\n");
}  
//exit(ret);
}
    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "max", &ret);
if (ret !=CL_SUCCESS) {
   printf("Error creating kernel: \n");
if (ret==CL_INVALID_PROGRAM)
{
printf("invalid program\n");
}  
  // exit(ret);
}
    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
if (ret !=CL_SUCCESS) {
   printf("Error creating argument a for kernel: \n");
  // exit(ret);
}
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&max_mem_obj);
   if (ret !=CL_SUCCESS) {
   printf("Error creating argument max for kernel: \n");
   //exit(ret);
}
     // Execute the OpenCL kernel on the list
    size_t global_item_size = n; // Process the entire lists
  size_t local_item_size = n/2;//  Process one item at a time
 
 ret = clEnqueueNDRangeKernel(command_queue, kernel,1,NULL,&global_item_size, &local_item_size, 0, NULL, NULL);
if (ret !=CL_SUCCESS) {
   printf("Error in ND range kernel: \n");
   //exit(ret);
}
  // Read the memory buffer C on the device to the local variable C
  
    ret = clEnqueueReadBuffer(command_queue, max_mem_obj, CL_TRUE, 0,j * sizeof(int), max, 0, NULL, NULL);
if (ret !=CL_SUCCESS) {
   printf("Error getting back max from kernel:\n ");
   //exit(ret);
}
ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(int), A, 0, NULL, NULL);
    // Display the result to the screen
    for(i = 0; i < n; i++)
  printf("%d : %d\n", i, A[i]);
printf("max is %d",max[0]);

ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(max_mem_obj);
   
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(A);
    free(max);

    return 0;
}

