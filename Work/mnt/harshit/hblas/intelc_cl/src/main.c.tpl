[+ autogen5 template +]
/*
 * Application [+NormalName+]
 * Copyright (C) [+Author+] [+(shell "date +%Y")+] <[+Email+]>
 * 
[+CASE (get "License") +]
[+ == "BSD"  +][+(bsd  (get "Name") (get "Author") " * ")+]
[+ == "LGPL" +][+(lgpl (get "Name") (get "Author") " * ")+]
[+ == "GPL"  +][+(gpl  (get "Name")                " * ")+]
[+ESAC+] */


#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>


#define DATA_SIZE (1024*1024)

const char *KernelSource = "\n"		      \
  "__kernel void square(                    \n" \
  "   __global float* input,                \n" \
  "   __global float* output,               \n" \
  "   const unsigned int count)             \n" \
  "{                                        \n" \
  "   int i = get_global_id(0);             \n" \
  "   if(i < count)                         \n" \
  "       output[i] = input[i] * input[i];  \n" \
  "}                                        \n" \
  "\n";

int main(int argc, char* argv[])
{
  int devType=CL_DEVICE_TYPE_CPU;
  
  if(argc > 1) {
    devType = CL_DEVICE_TYPE_GPU;
    printf("Using: CL_DEVICE_TYPE_GPU\n");
  } else {
    printf("Using: CL_DEVICE_TYPE_CPU\n");
  }
  
  cl_int err;     // error code returned from api calls
  
  size_t global;  // global domain size for our calculation
  size_t local;   // local domain size for our calculation
  
  cl_platform_id cpPlatform; // OpenCL platform
  cl_device_id device_id;    // compute device id
  cl_context context;        // compute context
  cl_command_queue commands; // compute command queue
  cl_program program;        // compute program
  cl_kernel kernel;          // compute kernel
  
  // Connect to a compute device
  err = clGetPlatformIDs(1, &cpPlatform, NULL);
  if (err != CL_SUCCESS) {
    fprintf(stderr,"Error: Failed to find a platform!\n");
    return EXIT_FAILURE;
  }
  
  // Get a device of the appropriate type
  err = clGetDeviceIDs(cpPlatform, devType, 1, &device_id, NULL);
  if (err != CL_SUCCESS) {
    fprintf(stderr,"Error: Failed to create a device group!\n");
    return EXIT_FAILURE;
  }
  
  // Create a compute context
  context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
  if (!context) {
    fprintf(stderr,"Error: Failed to create a compute context!\n");
    return EXIT_FAILURE;
  }
  
  // Create a command commands
  commands = clCreateCommandQueue(context, device_id, 0, &err);
  if (!commands) {
    fprintf(stderr,"Error: Failed to create a command commands!\n");
    return EXIT_FAILURE;
  }
  
  // Create the compute program from the source buffer
  program = clCreateProgramWithSource(context, 1, 
				      (const char **) &KernelSource,
				      NULL, &err);
  if (!program) {
    fprintf(stderr,"Error: Failed to create a compute program!\n");
    return EXIT_FAILURE;
  }
  
  // Build the program executable
  err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  if (err != CL_SUCCESS) {
    size_t len;
    char buffer[2048];
    
    fprintf(stderr,"Error: Failed to build program executable!\n");
    clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
			  sizeof(buffer), buffer, &len);
    fprintf(stderr,"%s\n",buffer);
    exit(1);
  }
  
  // Create the compute kernel in the program
  kernel = clCreateKernel(program, "square", &err);
  if (!kernel || err != CL_SUCCESS) {
    fprintf(stderr,"Error: Failed to create compute kernel!\n");
    exit(1);
  }
  
  // create data for the run
  float* data = (float *)malloc(sizeof(float)*DATA_SIZE);    // original data set given to device
  float* results = (float *)malloc(sizeof(float)*DATA_SIZE); // results returned from device
  unsigned int correct;               // number of correct results returned
  cl_mem input;                       // device memory used for the input array
  cl_mem output;                      // device memory used for the output array
  
  // Fill the vector with random float values
  unsigned int count = DATA_SIZE;
  unsigned int i;
  for(i = 0; i < count; i++)
    data[i] = rand() / (float)RAND_MAX;
  
  // Create the device memory vectors
  //
  input = clCreateBuffer(context,  CL_MEM_READ_ONLY,  
			 sizeof(float) * count, NULL, NULL);
  output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
			  sizeof(float) * count, NULL, NULL);
  if (!input || !output) {
    fprintf(stderr,"Error: Failed to allocate device memory!\n");
    exit(1);
  }   
  
  // Transfer the input vector into device memory
  err = clEnqueueWriteBuffer(commands, input, 
			     CL_TRUE, 0, sizeof(float) * count, 
			     data, 0, NULL, NULL);
  if (err != CL_SUCCESS) {
    fprintf(stderr,"Error: Failed to write to source array!\n");
    exit(1);
  }
  
  // Set the arguments to the compute kernel
  err = 0;
  err  = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input);
  err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &output);
  err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);
  if (err != CL_SUCCESS) {
    fprintf(stderr,"Error: Failed to set kernel arguments!\n");
    exit(1);
  }
  
  // Get the maximum work group size for executing the kernel on the device
  err = clGetKernelWorkGroupInfo(kernel, device_id, 
				 CL_KERNEL_WORK_GROUP_SIZE, 
				 sizeof(local), &local, NULL);
  if (err != CL_SUCCESS) {
    fprintf(stderr,"Error: Failed to retrieve kernel work group info!\n");
    exit(1);
  }
  
// Execute the kernel over the vector using the 
// maximum number of work group items for this device
  global = count;
  err = clEnqueueNDRangeKernel(commands, kernel, 
			       1, NULL, &global, &local, 
			       0, NULL, NULL);
  if (err) {
    fprintf(stderr,"Error: Failed to execute kernel!\n");
    return EXIT_FAILURE;
  }
  
  // Wait for all commands to complete
  clFinish(commands);
  
  // Read back the results from the device to verify the output
  //
  err = clEnqueueReadBuffer( commands, output,
			     CL_TRUE, 0, sizeof(float) * count,
			     results, 0, NULL, NULL ); 
  if (err != CL_SUCCESS) {
    fprintf(stderr,"Error: Failed to read output array!\n");
    exit(1);
  }
  
  // Validate our results
  //
  correct = 0;
  for(i = 0; i < count; i++) {
    if(results[i] == data[i] * data[i])
      correct++;
  }
  
  // Print a brief summary detailing the results
  printf("Computed %u/%u\n",correct, count);
  printf("Computed %100.f\n correct values", (float)correct/(float)count);  

  // Shutdown and cleanup
  free(data);
  free(results);
  
  clReleaseMemObject(input);
  clReleaseMemObject(output);
  clReleaseProgram(program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(commands);
  clReleaseContext(context);
  
  return 0;
}
