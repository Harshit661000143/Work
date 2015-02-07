/*
 * Copyright 1993-2007 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  Users and possessors of this source code
 * are hereby granted a nonexclusive, royalty-free license to use this code
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.   This source code is a "commercial item" as
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 *
 * Any use of this source code in individual and commercial software must
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */

/* This example demonstrates how to use the CUBLAS library
 * by scaling an array of floating-point values on the device
 * and comparing the result to the same operation performed
 * on the host.
 */

/* Includes, system */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Includes, cuda */
#include "cublas.h"

/* Matrix size */
#define N  (275)

/* Host implementation of a simple version of sgemm */


//void simple_saxpy(n2, alpha, h_A, 1,h_B,1 ,h_C);
static void simple_saxpy(int n, float alpha, const float *A, int incx, const float *B,int incy, float *C)
{
    int i;
    int j;
    int k;
    for (i = 0,j=0,k=0; k<n; i+=incx,j+=incy,k++) {
                    float prod = 0;
                   C[i] = alpha * A[i]+B[j];
            }
}

/* Main */
int main(int argc, char** argv)
{    
    cublasStatus status;
    float* h_A;
    float* h_B;
    float* h_C;
    float* d_A = 0;
    float* d_B = 0;
    float* d_C = 0;
    float alpha =1.0f;
    float beta = 0.0f;
    int n2 = N ;
    int i;
    float error_norm;
    float ref_norm;
    float diff;

if(argc==3)
{
    n2=atoi(argv[1]);
    alpha=atof(argv[2]);
}
    
    /* Initialize CUBLAS */
    status = cublasInit();
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! CUBLAS initialization error\n");
        return EXIT_FAILURE;
    }

    /* Allocate host memory for the matrices */
    h_A = (float*)malloc(n2 * sizeof(h_A[0]));
    if (h_A == 0) {
        fprintf (stderr, "!!!! host memory allocation error (A)\n");
        return EXIT_FAILURE;
    }
    h_B = (float*)malloc(n2 * sizeof(h_B[0]));
    if (h_B == 0) {
        fprintf (stderr, "!!!! host memory allocation error (B)\n");
        return EXIT_FAILURE;
    }
#if 0
    h_C = (float*)malloc(n2 * sizeof(h_C[0]));
    if (h_C == 0) {
        fprintf (stderr, "!!!! host memory allocation error (C)\n");
        return EXIT_FAILURE;
    }
#endif
    /* Fill the matrices with test data */
    for (i = 0; i < n2; i++) {

          h_A[i]=1.0;
	  h_B[i]=2.0;
 //       h_A[i] = rand() / (float)RAND_MAX;
   //     h_B[i] = rand() / (float)RAND_MAX;
//        h_C[i] = rand() / (float)RAND_MAX;
    }

    /* Allocate device memory for the matrices */
    status = cublasAlloc(n2, sizeof(d_A[0]), (void**)&d_A);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device memory allocation error (A)\n");
        return EXIT_FAILURE;
    }
    status = cublasAlloc(n2, sizeof(d_B[0]), (void**)&d_B);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device memory allocation error (B)\n");
        return EXIT_FAILURE;
    }

    /* Initialize the device matrices with the host matrices */
    status = cublasSetVector(n2, sizeof(h_A[0]), h_A, 1, d_A, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (write A)\n");
        return EXIT_FAILURE;
    }
    status = cublasSetVector(n2, sizeof(h_B[0]), h_B, 1, d_B, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (write B)\n");
        return EXIT_FAILURE;
    }
    
    /* Performs operation using plain C code */
//    simple_saxpy(n2, alpha, h_A, 1,h_B,1 ,h_C);

    /* Clear last error */
    cublasGetError();

    /* Performs operation using cublas */
    cublasSaxpy(n2, alpha, d_A, 1, d_B, 1 );

//cublasSaxpy (int n, float alpha, const float *x,
//int incx, float *y, int incy)
    status = cublasGetError();
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! kernel execution error.\n");
        return EXIT_FAILURE;
    }

    /* Read the result back */
    status = cublasGetVector(n2, sizeof(h_B[0]), d_B, 1, h_B, 1);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! device access error (read C)\n");
        return EXIT_FAILURE;
    }

    /* Check result against reference */
    error_norm = 0;
    ref_norm = 0;
#if 0
    for (i = 0; i < n2; ++i) {
        diff = h_C[i] - h_B[i];
        error_norm += diff * diff;
        ref_norm += h_C[i] * h_C[i];
        printf("\noutput[%d]=%f",i,h_B[i]);

    }
    error_norm = (float)sqrt((double)error_norm);
    ref_norm = (float)sqrt((double)ref_norm);
    if (fabs(ref_norm) < 1e-7) {
        fprintf (stderr, "!!!! reference norm is 0\n");
        return EXIT_FAILURE;
    }
    printf( "Test %s\n", (error_norm / ref_norm < 1e-6f) ? "PASSED" : "FAILED");

#endif
    /* Memory clean up */
    free(h_A);
    free(h_B);
    free(h_C);
    status = cublasFree(d_A);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! memory free error (A)\n");
        return EXIT_FAILURE;
    }
    status = cublasFree(d_B);
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! memory free error (B)\n");
        return EXIT_FAILURE;
    }
    /* Shutdown */
    status = cublasShutdown();
    if (status != CUBLAS_STATUS_SUCCESS) {
        fprintf (stderr, "!!!! shutdown error (A)\n");
        return EXIT_FAILURE;
    }
#if 0
    if (argc <= 1 || strcmp(argv[1], "-noprompt")) {
        printf("\nPress ENTER to exit...\n");
        getchar();
    }
#endif
    return EXIT_SUCCESS;
}
