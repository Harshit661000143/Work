/* 
* oclBLASParser OpenCL Host Application for Level 1 BLAS
* Copyright (C) 2009 Wendell Rodrigues <wendell.rodrigues@inria.fr>
* Author(s): Wendell Rodrigues
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without event the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Sofware
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

// common SDK header for standard utilities and system libs 
#include <oclUtils.h>

// Name of the file with the source code for the computation kernel
// *********************************************************************
const char* cSourceFile = "dartBLAS.cl";

// ------------------------------------------------------------
// OpenCL Vars
// ------------------------------------------------------------
cl_context cxGPUContext;        // OpenCL context
cl_command_queue cqCommandQue;  // OpenCL command que
cl_device_id* cdDevices;        // OpenCL device list    
cl_program cpProgram;           // OpenCL program
cl_kernel ckKernel;             // OpenCL kernel
cl_mem   cmDevVEC1;               // OpenCL device destination buffer 
cl_mem   cmDevVEC2;               // OpenCL device destination buffer 
size_t szGlobalWorkSize;        // 1D var for Total # of work items
size_t szLocalWorkSize;	        // 1D var for # of work items in the work group	
size_t szParmDataBytes;		// Byte size of context information
size_t szKernelLength;		// Byte size of kernel code
cl_int dartErr1, dartErr2;		// Error code var
char* cPathAndName = NULL;      // var for full paths to data, src, etc.
char* cSourceCL = NULL;         // Buffer to hold source for compilation 
// ------------------------------------------------------------

// Program Vars
float *VEC1;
float *VEC2;
float RET;
unsigned int N;


// Forward Declarations
// *********************************************************************
void Cleanup (int iExitCode);

void gp2StartLogs(char *filenamelog, char *appli) {
    // start logs 
    shrSetLogFileName (filenamelog);
    shrLog(LOGBOTH, 0.0, "%s Starting...\n\n", appli); 
}

void gp2CreateContext() {
    cxGPUContext = clCreateContextFromType(0, CL_DEVICE_TYPE_GPU, NULL, NULL, &dartErr1);
    shrLog(LOGBOTH, 0.0, "clCreateContextFromType...\n"); 
    if (dartErr1 != CL_SUCCESS)
    {
        shrLog(LOGBOTH, 0.0, "Error in clCreateContextFromType, near Line %u in file %u", __LINE__, __FILE__);
        Cleanup(EXIT_FAILURE);
    }
}


void gp2ListDevices() {
    dartErr1 = clGetContextInfo(cxGPUContext, CL_CONTEXT_DEVICES, 0, NULL, &szParmDataBytes);
    cdDevices = (cl_device_id*)malloc(szParmDataBytes);
    dartErr1 |= clGetContextInfo(cxGPUContext, CL_CONTEXT_DEVICES, szParmDataBytes, cdDevices, NULL);
    shrLog(LOGBOTH, 0.0, "clGetContextInfo...\n"); 
    if (dartErr1 != CL_SUCCESS)
    {
        shrLog(LOGBOTH, 0.0, "Error in clGetContextInfo, near Line %u in file %u", __LINE__, __FILE__);
        Cleanup(EXIT_FAILURE);
    }
}

void gp2CommandQueue() {
    cqCommandQue = clCreateCommandQueue(cxGPUContext, cdDevices[0], 0, &dartErr1);
    shrLog(LOGBOTH, 0.0, "clCreateCommandQueue...\n"); 
    if (dartErr1 != CL_SUCCESS)
    {
        shrLog(LOGBOTH, 0.0, "Error in clCreateCommandQueue, near Line %u in file %u", __LINE__, __FILE__);
        Cleanup(EXIT_FAILURE);
    }
}

void gp2CreateBuild(char *filepath) {
    // ------------------------------------------------------------
    // Read the OpenCL kernel in from source file
    // ------------------------------------------------------------
    cPathAndName = shrFindFilePath(cSourceFile, filepath);
    cSourceCL = oclLoadProgSource(cPathAndName, "", &szKernelLength);
    shrLog(LOGBOTH, 0.0, "oclLoadProgSource (%s) (%s)...\n", cSourceFile,filepath); 
    // ------------------------------------------------------------

    // ------------------------------------------------------------
    // Create the program
    // ------------------------------------------------------------
    cpProgram = clCreateProgramWithSource(cxGPUContext, 1, (const char **)&cSourceCL, &szKernelLength, &dartErr1);
    shrLog(LOGBOTH, 0.0, "clCreateProgramWithSource...\n"); 
    if (dartErr1 != CL_SUCCESS)
    {
        shrLog(LOGBOTH, 0.0, "Error in clCreateProgramWithSource, near Line %u in file %u", __LINE__, __FILE__);
        Cleanup(EXIT_FAILURE);
    }

    // ------------------------------------------------------------
    // Build the program
    // ------------------------------------------------------------
    dartErr1 = clBuildProgram(cpProgram, 0, NULL, NULL, NULL, NULL);
    shrLog(LOGBOTH, 0.0, "clBuildProgram...\n"); 
    if (dartErr1 != CL_SUCCESS)
    {
        shrLog(LOGBOTH, 0.0, "Error in clBuildProgram, near Line %u in file %u Err %d", __LINE__, __FILE__,dartErr1);
        Cleanup(EXIT_FAILURE);
    }
    // ------------------------------------------------------------
}


void gp2CreateKernel(char *kernelname) {
    ckKernel = clCreateKernel(cpProgram, kernelname, &dartErr1);
    if (dartErr1 != CL_SUCCESS)
    {
        shrLog(LOGBOTH, 0.0, "Error in clCreateKernel, near Line %u in file %u %d", __LINE__, __FILE__,dartErr1);
        Cleanup(EXIT_FAILURE);
    }
}


void gp2LauchKernel() {
    dartErr1 = clEnqueueNDRangeKernel(cqCommandQue, ckKernel, 1, NULL, &szGlobalWorkSize, &szLocalWorkSize, 0, NULL, NULL);
    if (dartErr1 != CL_SUCCESS)
    {
        shrLog(LOGBOTH, 0.0, "Error in clEnqueueNDRangeKernel, near Line %u in file %u", __LINE__, __FILE__);
        Cleanup(EXIT_FAILURE);
    }
}


float dartSdot(int n, cl_mem x, int incx, cl_mem y, int incy) {
    cl_mem   cmDevRET;                // OpenCL device destination buffer 
    float ret;

    cmDevRET  = clCreateBuffer(cxGPUContext, CL_MEM_READ_WRITE, sizeof(cl_float), NULL, &dartErr1);

    gp2CreateKernel("sDOT");

    dartErr1  = clSetKernelArg(ckKernel, 0, sizeof(cl_int),  (void*)&n);
    dartErr1 |= clSetKernelArg(ckKernel, 1, sizeof(cl_mem),  (void*)&x);
    dartErr1 |= clSetKernelArg(ckKernel, 2, sizeof(cl_int),  (void*)&incx);
    dartErr1 |= clSetKernelArg(ckKernel, 3, sizeof(cl_mem),  (void*)&y);
    dartErr1 |= clSetKernelArg(ckKernel, 4, sizeof(cl_int),  (void*)&incy);
    dartErr1 |= clSetKernelArg(ckKernel, 5, sizeof(cl_mem),  (void*)&cmDevRET);
    dartErr1 |= clSetKernelArg(ckKernel, 6, sizeof(cl_float)*szLocalWorkSize,  NULL);
    if (dartErr1 != CL_SUCCESS) Cleanup(EXIT_FAILURE);

    gp2LauchKernel();

    dartErr1 = clEnqueueReadBuffer(cqCommandQue, cmDevRET, CL_TRUE, 0, sizeof(cl_float), &ret, 0, NULL, NULL);
    if (dartErr1 != CL_SUCCESS) Cleanup(EXIT_FAILURE);

    if(ckKernel)clReleaseKernel(ckKernel);
    if(cmDevRET)clReleaseMemObject(cmDevRET);

    return(ret);
}


float dartSnrm2(int n, cl_mem x, int incx) {
    cl_mem   cmDevRET;                // OpenCL device destination buffer 
    float ret;

    cmDevRET  = clCreateBuffer(cxGPUContext, CL_MEM_READ_WRITE, sizeof(cl_float), NULL, &dartErr1);

    gp2CreateKernel("sNRM2");

    dartErr1  = clSetKernelArg(ckKernel, 0, sizeof(cl_int),  (void*)&n);
    dartErr1 |= clSetKernelArg(ckKernel, 1, sizeof(cl_mem),  (void*)&x);
    dartErr1 |= clSetKernelArg(ckKernel, 2, sizeof(cl_int),  (void*)&incx);
    dartErr1 |= clSetKernelArg(ckKernel, 3, sizeof(cl_mem),  (void*)&cmDevRET);
    dartErr1 |= clSetKernelArg(ckKernel, 4, sizeof(cl_float)*szLocalWorkSize,  NULL);
    if (dartErr1 != CL_SUCCESS) Cleanup(EXIT_FAILURE);

    gp2LauchKernel();

    dartErr1 = clEnqueueReadBuffer(cqCommandQue, cmDevRET, CL_TRUE, 0, sizeof(cl_float), &ret, 0, NULL, NULL);
    if (dartErr1 != CL_SUCCESS) Cleanup(EXIT_FAILURE);

    if(ckKernel)clReleaseKernel(ckKernel);
    if(cmDevRET)clReleaseMemObject(cmDevRET);

    return(ret);
}


void dartSscal(int n, float alpha, cl_mem x, int incx) {
    cl_mem   cmDevRET;                // OpenCL device destination buffer 
    float ret;

    cmDevRET  = clCreateBuffer(cxGPUContext, CL_MEM_READ_WRITE, sizeof(cl_float), NULL, &dartErr1);

    gp2CreateKernel("sSCAL");

    dartErr1  = clSetKernelArg(ckKernel, 0, sizeof(cl_int),    (void*)&n);
    dartErr1 |= clSetKernelArg(ckKernel, 1, sizeof(cl_float),  (void*)&alpha);
    dartErr1 |= clSetKernelArg(ckKernel, 2, sizeof(cl_mem),  (void*)&x);
    dartErr1 |= clSetKernelArg(ckKernel, 3, sizeof(cl_int),  (void*)&incx);
    if (dartErr1 != CL_SUCCESS) Cleanup(EXIT_FAILURE);

    gp2LauchKernel();

    dartErr1 = clEnqueueReadBuffer(cqCommandQue, cmDevRET, CL_TRUE, 0, sizeof(cl_float), &ret, 0, NULL, NULL);
    if (dartErr1 != CL_SUCCESS) Cleanup(EXIT_FAILURE);

    if(ckKernel)clReleaseKernel(ckKernel);
    if(cmDevRET)clReleaseMemObject(cmDevRET);
}

void dartSaxpy(int n, float alpha, cl_mem x, int incx, cl_mem y, int incy) {
    cl_mem   cmDevRET;                // OpenCL device destination buffer 
    float ret;

    cmDevRET  = clCreateBuffer(cxGPUContext, CL_MEM_READ_WRITE, sizeof(cl_float), NULL, &dartErr1);

    gp2CreateKernel("sAXPY");

    dartErr1  = clSetKernelArg(ckKernel, 0, sizeof(cl_int),  (void*)&n);
    dartErr1 |= clSetKernelArg(ckKernel, 1, sizeof(cl_float),(void*)&alpha);
    dartErr1 |= clSetKernelArg(ckKernel, 2, sizeof(cl_mem),  (void*)&x);
    dartErr1 |= clSetKernelArg(ckKernel, 3, sizeof(cl_int),  (void*)&incx);
    dartErr1 |= clSetKernelArg(ckKernel, 4, sizeof(cl_mem),  (void*)&y);
    dartErr1 |= clSetKernelArg(ckKernel, 5, sizeof(cl_int),  (void*)&incy);
    if (dartErr1 != CL_SUCCESS) Cleanup(EXIT_FAILURE);

    gp2LauchKernel();

    dartErr1 = clEnqueueReadBuffer(cqCommandQue, cmDevRET, CL_TRUE, 0, sizeof(cl_float), &ret, 0, NULL, NULL);
    if (dartErr1 != CL_SUCCESS) Cleanup(EXIT_FAILURE);

    if(ckKernel)clReleaseKernel(ckKernel);
    if(cmDevRET)clReleaseMemObject(cmDevRET);
}


// Main function 
// *********************************************************************
int main(int argc, char **argv)
{
    
    gp2StartLogs("oclBLASParser.log",argv[0]);

    if (argc>1){
      shrLog(LOGBOTH, 0.0, "No arguments needed"); 
      exit(0);
    }

    szLocalWorkSize = 32;

    gp2CreateContext();
    gp2ListDevices();
    gp2CommandQueue();

    gp2CreateBuild(argv[0]);

    N = 10;
    VEC1 = (float *)malloc(sizeof(cl_float) * N);
    VEC2 = (float *)malloc(sizeof(cl_float) * N);
    printf("VEC1 and VEC2 = [");
    for (int i=0;i<10;i++) {VEC1[i]=i;VEC2[i]=i;printf("%d ",i);}
    printf("]\n");
    cmDevVEC1  = clCreateBuffer(cxGPUContext, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(cl_float)*N, VEC1, &dartErr1);
    cmDevVEC2  = clCreateBuffer(cxGPUContext, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(cl_float)*N, VEC2, &dartErr1);

    szGlobalWorkSize = shrRoundUp((int)szLocalWorkSize, N);  // rounded up to the nearest multiple of the LocalWorkSize
    shrLog(LOGBOTH, 0.0, "Global Work Size \t\t= %u\nLocal Work Size \t\t= %u\n# of Work Groups \t\t= %u\n\n", 
            szGlobalWorkSize, szLocalWorkSize, (szGlobalWorkSize % szLocalWorkSize + szGlobalWorkSize/szLocalWorkSize)); 

    RET = dartSdot(N, cmDevVEC1, 1, cmDevVEC2, 1);
    printf("Result sDOT: %f\n",RET);

    RET = dartSnrm2(N, cmDevVEC1, 1);
    printf("Result sNRM2: %f\n",RET);

    dartSscal(N, 5, cmDevVEC1, 1);
    dartErr1 = clEnqueueReadBuffer(cqCommandQue, cmDevVEC1, CL_TRUE, 0, sizeof(cl_float)*N, VEC1, 0, NULL, NULL);
    if (dartErr1 != CL_SUCCESS) Cleanup(EXIT_FAILURE);
    printf("Result sSCAL alpha=5 X ="); for (int i=0;i<10;i++) printf(" %.0f",VEC1[i]); printf("\n");

    dartSaxpy(N, 5, cmDevVEC1, 1, cmDevVEC2, 1);
    dartErr1 = clEnqueueReadBuffer(cqCommandQue, cmDevVEC2, CL_TRUE, 0, sizeof(cl_float)*N, VEC2, 0, NULL, NULL);
    if (dartErr1 != CL_SUCCESS) Cleanup(EXIT_FAILURE);
    printf("Result sAXPY alpha=5 Y ="); for (int i=0;i<10;i++) printf(" %.0f",VEC2[i]); printf("\n");
   
    Cleanup(EXIT_SUCCESS);
}


void Cleanup (int iExitCode)
{
    // Cleanup allocated objects
    shrLog(LOGBOTH, 0.0, "\nStarting Cleanup...\n\n");
    if(cdDevices)free(cdDevices);
    if(cPathAndName)free(cPathAndName);
    if(cSourceCL)free(cSourceCL);
    if(ckKernel)clReleaseKernel(ckKernel);  
    if(cpProgram)clReleaseProgram(cpProgram);
    if(cqCommandQue)clReleaseCommandQueue(cqCommandQue);
    if(cxGPUContext)clReleaseContext(cxGPUContext);
    if(cmDevVEC1)clReleaseMemObject(cmDevVEC1);
    if(cmDevVEC2)clReleaseMemObject(cmDevVEC2);


    // Free host memory
    free(VEC1); 
    free(VEC2);

    shrLog(LOGBOTH | CLOSELOG, 0.0, "oclTestBlas.exe Ending...\nPress Enter to Exit\n");
    getchar();

    exit (iExitCode);
}
