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


#include "[+NormalName+].hpp"

/*
 * \brief Host Initialization 
 *        Allocate and initialize memory 
 *        on the host. Print input array. 
 */
int
initializeHost(void)
{
	width				= 256;
	input				= NULL;
	output				= NULL;
	multiplier			= 2;

	/////////////////////////////////////////////////////////////////
	// Allocate and initialize memory used by host 
	/////////////////////////////////////////////////////////////////
    cl_uint sizeInBytes = width * sizeof(cl_uint);
    input = (cl_uint *) malloc(sizeInBytes);
	if(input == NULL)
	{
		std::cout<<"Error: Failed to allocate input memory on host\n";
		return 1; 
	}

    output = (cl_uint *) malloc(sizeInBytes);
	if(output == NULL)
	{
		std::cout<<"Error: Failed to allocate output memory on host\n";
		return 1; 
	}

    for(cl_uint i = 0; i < width; i++)
        input[i] = i;

	// print input array
	print1DArray(std::string("Input").c_str(), input, width);
	return 0;
}

/*
 * Converts the contents of a file into a string
 */
std::string
convertToString(const char *filename)
{
	size_t size;
	char*  str;
	std::string s;

	std::fstream f(filename, (std::fstream::in | std::fstream::binary));

	if(f.is_open())
	{
		size_t fileSize;
		f.seekg(0, std::fstream::end);
		size = fileSize = (size_t)f.tellg();
		f.seekg(0, std::fstream::beg);

		str = new char[size+1];
		if(!str)
		{
			f.close();
			return NULL;
		}

		f.read(str, fileSize);
		f.close();
		str[size] = '\0';
	
		s = str;
		delete[] str;
		return s;
	}
	else
	{
		std::cout << "\nFile containg the kernel code(\".cl\") not found. Please copy the required file in the folder containg the executable.\n";
		exit(1);
	}
	return NULL;
}

/*
 * \brief OpenCL related initialization 
 *        Create Context, Device list, Command Queue
 *        Create OpenCL memory buffer objects
 *        Load CL file, compile, link CL source 
 *		  Build program and kernel objects
 */
int
initializeCL(void)
{
    cl_int status = 0;
    size_t deviceListSize;

    /*
     * Have a look at the available platforms and pick either
     * the AMD one if available or a reasonable default.
     */

    cl_uint numPlatforms;
    cl_platform_id platform = NULL;
    status = clGetPlatformIDs(0, NULL, &numPlatforms);
    if(status != CL_SUCCESS)
    {
        std::cout << "Error: Getting Platforms. (clGetPlatformsIDs)\n";
        return 1;
    }
    
    if(numPlatforms > 0)
    {
        cl_platform_id* platforms = new cl_platform_id[numPlatforms];
        status = clGetPlatformIDs(numPlatforms, platforms, NULL);
        if(status != CL_SUCCESS)
        {
            std::cout << "Error: Getting Platform Ids. (clGetPlatformsIDs)\n";
            return 1;
        }
        for(unsigned int i=0; i < numPlatforms; ++i)
        {
            char pbuff[100];
            status = clGetPlatformInfo(
                        platforms[i],
                        CL_PLATFORM_VENDOR,
                        sizeof(pbuff),
                        pbuff,
                        NULL);
            if(status != CL_SUCCESS)
            {
                std::cout << "Error: Getting Platform Info.(clGetPlatformInfo)\n";
                return 1;
            }
            platform = platforms[i];
            if(!strcmp(pbuff, "Advanced Micro Devices, Inc."))
            {
                break;
            }
        }
        delete platforms;
    }

    if(NULL == platform)
    {
        std::cout << "NULL platform found so Exiting Application." << std::endl;
        return 1;
    }

    /*
     * If we could find our platform, use it. Otherwise use just available platform.
     */
    cl_context_properties cps[3] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0 };

	/////////////////////////////////////////////////////////////////
	// Create an OpenCL context
	/////////////////////////////////////////////////////////////////
    context = clCreateContextFromType(cps, 
                                      CL_DEVICE_TYPE_CPU, 
                                      NULL, 
                                      NULL, 
                                      &status);
    if(status != CL_SUCCESS) 
	{  
		std::cout<<"Error: Creating Context. (clCreateContextFromType)\n";
		return 1; 
	}

    /* First, get the size of device list data */
    status = clGetContextInfo(context, 
                              CL_CONTEXT_DEVICES, 
                              0, 
                              NULL, 
                              &deviceListSize);
    if(status != CL_SUCCESS) 
	{  
		std::cout<<
			"Error: Getting Context Info \
		    (device list size, clGetContextInfo)\n";
		return 1;
	}

	/////////////////////////////////////////////////////////////////
	// Detect OpenCL devices
	/////////////////////////////////////////////////////////////////
    devices = (cl_device_id *)malloc(deviceListSize);
	if(devices == 0)
	{
		std::cout<<"Error: No devices found.\n";
		return 1;
	}

    /* Now, get the device list data */
    status = clGetContextInfo(
			     context, 
                 CL_CONTEXT_DEVICES, 
                 deviceListSize, 
                 devices, 
                 NULL);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<
			"Error: Getting Context Info \
		    (device list, clGetContextInfo)\n";
		return 1;
	}

	/////////////////////////////////////////////////////////////////
	// Create an OpenCL command queue
	/////////////////////////////////////////////////////////////////
    commandQueue = clCreateCommandQueue(
					   context, 
                       devices[0], 
                       0, 
                       &status);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<"Creating Command Queue. (clCreateCommandQueue)\n";
		return 1;
	}

	/////////////////////////////////////////////////////////////////
	// Create OpenCL memory buffers
	/////////////////////////////////////////////////////////////////
    inputBuffer = clCreateBuffer(
				      context, 
                      CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
                      sizeof(cl_uint) * width,
                      input, 
                      &status);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<"Error: clCreateBuffer (inputBuffer)\n";
		return 1;
	}

    outputBuffer = clCreateBuffer(
					   context, 
                       CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR,
                       sizeof(cl_uint) * width,
                       output, 
                       &status);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<"Error: clCreateBuffer (outputBuffer)\n";
		return 1;
	}


	/////////////////////////////////////////////////////////////////
	// Load CL file, build CL program object, create CL kernel object
	/////////////////////////////////////////////////////////////////
    const char * filename  = "[+NormalName+]_Kernels.cl";
    std::string  sourceStr = convertToString(filename);
    const char * source    = sourceStr.c_str();
    size_t sourceSize[]    = { strlen(source) };

    program = clCreateProgramWithSource(
			      context, 
                  1, 
                  &source,
				  sourceSize,
                  &status);
	if(status != CL_SUCCESS) 
	{ 
	  std::cout<<
			   "Error: Loading Binary into cl_program \
			   (clCreateProgramWithBinary)\n";
	  return 1;
	}

    /* create a cl program executable for all the devices specified */
    status = clBuildProgram(program, 1, devices, NULL, NULL, NULL);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<"Error: Building Program (clBuildProgram)\n";
		return 1; 
	}

    /* get a kernel object handle for a kernel with the given name */
    kernel = clCreateKernel(program, "[+NormaHLower+]Kernel", &status);
    if(status != CL_SUCCESS) 
	{  
		std::cout<<"Error: Creating Kernel from program. (clCreateKernel)\n";
		return 1;
	}

	return 0;
}


/*
 * \brief Run OpenCL program 
 *		  
 *        Bind host variables to kernel arguments 
 *		  Run the CL kernel
 */
int 
runCLKernels(void)
{
    cl_int   status;
	cl_uint maxDims;
    cl_event events[2];
    size_t globalThreads[1];
    size_t localThreads[1];
	size_t maxWorkGroupSize;
	size_t maxWorkItemSizes[3];

	/**
	* Query device capabilities. Maximum 
	* work item dimensions and the maximmum
	* work item sizes
	*/ 
	status = clGetDeviceInfo(
		devices[0], 
		CL_DEVICE_MAX_WORK_GROUP_SIZE, 
		sizeof(size_t), 
		(void*)&maxWorkGroupSize, 
		NULL);
    if(status != CL_SUCCESS) 
	{  
		std::cout<<"Error: Getting Device Info. (clGetDeviceInfo)\n";
		return 1;
	}
	
	status = clGetDeviceInfo(
		devices[0], 
		CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, 
		sizeof(cl_uint), 
		(void*)&maxDims, 
		NULL);
    if(status != CL_SUCCESS) 
	{  
		std::cout<<"Error: Getting Device Info. (clGetDeviceInfo)\n";
		return 1;
	}

	status = clGetDeviceInfo(
		devices[0], 
		CL_DEVICE_MAX_WORK_ITEM_SIZES, 
		sizeof(size_t)*maxDims,
		(void*)maxWorkItemSizes,
		NULL);
    if(status != CL_SUCCESS) 
	{  
		std::cout<<"Error: Getting Device Info. (clGetDeviceInfo)\n";
		return 1;
	}
    
    globalThreads[0] = width;
    localThreads[0]  = 1;

	if(globalThreads[0] > maxWorkItemSizes[0] || 
	    localThreads[0] > maxWorkGroupSize)
	{
		std::cout<<"Unsupported: Device does not support requested number of work items.";
		return 1;
	}

    /*** Set appropriate arguments to the kernel ***/
    /* the output array to the kernel */
    status = clSetKernelArg(
                    kernel, 
                    0, 
                    sizeof(cl_mem), 
                    (void *)&outputBuffer);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<"Error: Setting kernel argument. (output)\n";
		return 1;
	}

    /* the input array to the kernel */
    status = clSetKernelArg(
                    kernel, 
                    1, 
                    sizeof(cl_mem), 
                    (void *)&inputBuffer);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<"Error: Setting kernel argument. (input)\n";
		return 1;
	}

    /*multiplier*/
    status = clSetKernelArg(
                    kernel, 
                    2, 
                    sizeof(cl_uint), 
                    (void *)&multiplier);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<< "Error: Setting kernel argument. (multiplier)\n";
		return 1;
	}

    /* 
     * Enqueue a kernel run call.
     */
    status = clEnqueueNDRangeKernel(
			     commandQueue,
                 kernel,
                 1,
                 NULL,
                 globalThreads,
                 localThreads,
                 0,
                 NULL,
                 &events[0]);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<
			"Error: Enqueueing kernel onto command queue. \
			(clEnqueueNDRangeKernel)\n";
		return 1;
	}


    /* wait for the kernel call to finish execution */
    status = clWaitForEvents(1, &events[0]);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<
		    "Error: Waiting for kernel run to finish. \
			(clWaitForEvents)\n";
		return 1;
	}

    status = clReleaseEvent(events[0]);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<
		    "Error: Release event object. \
			(clReleaseEvent)\n";
		return 1;
	}

    /* Enqueue readBuffer*/
    status = clEnqueueReadBuffer(
                commandQueue,
                outputBuffer,
                CL_TRUE,
                0,
                width * sizeof(cl_uint),
                output,
                0,
                NULL,
                &events[1]);
    
    if(status != CL_SUCCESS) 
	{ 
        std::cout << 
    		"Error: clEnqueueReadBuffer failed. \
             (clEnqueueReadBuffer)\n";

		return 1;
    }
    
    /* Wait for the read buffer to finish execution */
    status = clWaitForEvents(1, &events[1]);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<
		    "Error: Waiting for read buffer call to finish. \
			(clWaitForEvents)\n";
		return 1;
	}
    
    status = clReleaseEvent(events[1]);
    if(status != CL_SUCCESS) 
	{ 
		std::cout<<
		    "Error: Release event object. \
			(clReleaseEvent)\n";
		return 1;
	}

	return 0;
}


/*
 * \brief Release OpenCL resources (Context, Memory etc.) 
 */
int  
cleanupCL(void)
{
    cl_int status;

    status = clReleaseKernel(kernel);
    if(status != CL_SUCCESS)
	{
		std::cout<<"Error: In clReleaseKernel \n";
		return 1; 
	}
    status = clReleaseProgram(program);
    if(status != CL_SUCCESS)
	{
		std::cout<<"Error: In clReleaseProgram\n";
		return 1; 
	}
    status = clReleaseMemObject(inputBuffer);
    if(status != CL_SUCCESS)
	{
		std::cout<<"Error: In clReleaseMemObject (inputBuffer)\n";
		return 1; 
	}
	status = clReleaseMemObject(outputBuffer);
    if(status != CL_SUCCESS)
	{
		std::cout<<"Error: In clReleaseMemObject (outputBuffer)\n";
		return 1; 
	}
    status = clReleaseCommandQueue(commandQueue);
    if(status != CL_SUCCESS)
	{
		std::cout<<"Error: In clReleaseCommandQueue\n";
		return 1;
	}
    status = clReleaseContext(context);
    if(status != CL_SUCCESS)
	{
		std::cout<<"Error: In clReleaseContext\n";
		return 1;
	}

	return 0;
}


/* 
 * \brief Releases program's resources 
 */
void
cleanupHost(void)
{
    if(input != NULL)
    {
        free(input);
        input = NULL;
    }
	if(output != NULL)
	{
		free(output);
		output = NULL;
	}
    if(devices != NULL)
    {
        free(devices);
        devices = NULL;
    }
}


/*
 * \brief Print no more than 256 elements of the given array.
 *
 *        Print Array name followed by elements.
 */
void print1DArray(
		 const std::string arrayName, 
         const unsigned int * arrayData, 
         const unsigned int length)
{
    cl_uint i;
    cl_uint numElementsToPrint = (256 < length) ? 256 : length;

    std::cout << std::endl;
    std::cout << arrayName << ":" << std::endl;
    for(i = 0; i < numElementsToPrint; ++i)
    {
        std::cout << arrayData[i] << " ";
    }
    std::cout << std::endl;

}

void verify()
{
    bool passed = true;
    for(unsigned int i = 0; i < width; ++i)
        if(input[i] * multiplier != output[i])
            passed = false;

    if(passed == true)
        std::cout << "Passed!\n";
    else
        std::cout << "Failed!\n";
}

int 
main(int argc, char * argv[])
{
    // Initialize Host application 
	if(initializeHost()==1)
		return 1;

    // Initialize OpenCL resources
    if(initializeCL()==1)
		return 1;

    // Run the CL program
    if(runCLKernels()==1)
		return 1;

    // Print output array
    print1DArray(std::string("Output"), output, width);

    // Verify output
    verify();

    // Releases OpenCL resources 
    if(cleanupCL()==1)
		return 1;

    // Release host resources
    cleanupHost();

    return 0;
}