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


#ifndef [+NameHUpper+]_H_
#define [+NameHUpper+]_H_



#include <CL/cl.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>


/*** GLOBALS ***/

/*
 * Input data is stored here.
 */
cl_uint *input;

/*
 * Output data is stored here.
 */
cl_uint *output;

/*
 * Multiplier is stored in this variable 
 */
cl_uint multiplier;

/* problem size for 1D algorithm and width of problem size for 2D algorithm */
cl_uint width;

/* The memory buffer that is used as input/output for OpenCL kernel */
cl_mem   inputBuffer;
cl_mem	 outputBuffer;

cl_context          context;
cl_device_id        *devices;
cl_command_queue    commandQueue;

cl_program program;

/* This program uses only one kernel and this serves as a handle to it */
cl_kernel  kernel;


/*** FUNCTION DECLARATIONS ***/
/*
 * OpenCL related initialisations are done here.
 * Context, Device list, Command Queue are set up.
 * Calls are made to set up OpenCL memory buffers that this program uses
 * and to load the programs into memory and get kernel handles.
 */
int initializeCL(void);

/*
 *
 */
int convertToString(const char * filename, std::string& str);

/*
 * This is called once the OpenCL context, memory etc. are set up,
 * the program is loaded into memory and the kernel handles are ready.
 * 
 * It sets the values for kernels' arguments and enqueues calls to the kernels
 * on to the command queue and waits till the calls have finished execution.
 *
 * It also gets kernel start and end time if profiling is enabled.
 */
int runCLKernels(void);

/* Releases OpenCL resources (Context, Memory etc.) */
int cleanupCL(void);

/* Releases program's resources */
void cleanupHost(void);

/*
 * Prints no more than 256 elements of the given array.
 * Prints full array if length is less than 256.
 *
 * Prints Array name followed by elements.
 */
void print1DArray(
         const std::string arrayName, 
         const unsigned int * arrayData, 
         const unsigned int length);


#endif  /* #ifndef [+NameHUpper+]_H_ */
