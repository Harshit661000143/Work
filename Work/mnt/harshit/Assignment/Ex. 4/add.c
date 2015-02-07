// I have loaded kernel using file I/O
#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
int main(void) {
    // Create the two input vectors
    int i,n;
   
   printf("enter size of array");
	scanf("%d",&n);	
    int *A = (int*)malloc(sizeof(int)*n);
    int *B = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++) {
        A[i] = i;
        B[i] = n-i ;
    }

//for time
cl_ulong start=0;
cl_ulong end=0; 

cl_event event1;

    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    int source_size;

    fp = fopen("vector_add_kernel.cl", "r");
    if (!fp) {
        printf("Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(100000);
    source_size = fread( source_str, 1, 100000, fp);
    fclose( fp );

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
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &ret);

    // Create memory buffers on the device for each vector 
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, 
            n * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            n * sizeof(int), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
            n * sizeof(int), NULL, &ret);

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,n * sizeof(int), A, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,n * sizeof(int), B, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, 
            (const char **)&source_str, (const size_t *)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);
    
    // Execute the OpenCL kernel on the list
    size_t global_item_size = n; // Process the entire lists
  size_t local_item_size = 1;//  Process one item at a time
//clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);   
 ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size, &local_item_size, 0, NULL, &event1);
//to measure time
clWaitForEvents(1, &event1);
clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start, NULL);
clGetEventProfilingInfo(event1, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end, NULL); 


    // Read the memory buffer C on the device to the local variable C
    int *C = (int*)malloc(sizeof(int)*n);
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, n * sizeof(int), C, 0, NULL, NULL);

    // Display the result to the screen
    for(i = 0; i < n; i++)
  printf("%d + %d = %d\n", A[i], B[i], C[i]);

/*float star=start;
float en=end;
printf("time of start is %f and time of end is %f",star,en);*/
float time =((end - start)*1.0e-6f); 
printf("time of execution is %f [ms]",time);

  
}

