#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

#define THREADS_PER_BLOCK 256

__global__ void computeSine(float *input, float *output, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < N) {
        output[idx] = sinf(input[idx]);  
    }
}

int main() {
    int N;

    printf("Enter number of angles: ");
    scanf("%d", &N);

    size_t size = N * sizeof(float);

    float *h_input  = (float*)malloc(size);
    float *h_output = (float*)malloc(size);

    for (int i = 0; i < N; i++) {
        h_input[i] = (float)i * 0.1f;  
    }

    float *d_input, *d_output;
    cudaMalloc((void**)&d_input, size);
    cudaMalloc((void**)&d_output, size);

    cudaMemcpy(d_input, h_input, size, cudaMemcpyHostToDevice);

    int blocks = (N + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK;

    computeSine<<<blocks, THREADS_PER_BLOCK>>>(d_input, d_output, N);

    cudaMemcpy(h_output, d_output, size, cudaMemcpyDeviceToHost);

    printf("\nAngle (rad)    Sine Value\n");
    for (int i = 0; i < (N < 10 ? N : 10); i++) {
        printf("%f        %f\n", h_input[i], h_output[i]);
    }


    printf("\n");

    printf("Prakhar Umrao 230962210\n");
    cudaFree(d_input);
    cudaFree(d_output);
    free(h_input);
    free(h_output);

    return 0;
}
