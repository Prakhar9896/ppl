#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

#define BLOCK_SIZE 256

__global__ void convolution1D(float *N, float *M, float *P,
                              int width, int mask_width) {

    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < width) {
        float sum = 0.0f;
        int half = mask_width / 2;

        for (int j = 0; j < mask_width; j++) {
            int index = i - half + j;

            if (index >= 0 && index < width) {
                sum += N[index] * M[j];
            }
        }

        P[i] = sum;
    }
}

int main() {
    int width, mask_width;

    printf("Enter width of input array: ");
    scanf("%d", &width);

    printf("Enter width of mask: ");
    scanf("%d", &mask_width);

    float *h_N = (float*)malloc(width * sizeof(float));
    float *h_M = (float*)malloc(mask_width * sizeof(float));
    float *h_P = (float*)malloc(width * sizeof(float));

    printf("Enter elements of input array:\n");
    for (int i = 0; i < width; i++) {
        scanf("%f", &h_N[i]);
    }

    printf("Enter elements of mask array:\n");
    for (int i = 0; i < mask_width; i++) {
        scanf("%f", &h_M[i]);
    }

    float *d_N, *d_M, *d_P;

    cudaMalloc((void**)&d_N, width * sizeof(float));
    cudaMalloc((void**)&d_M, mask_width * sizeof(float));
    cudaMalloc((void**)&d_P, width * sizeof(float));

    cudaMemcpy(d_N, h_N, width * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, h_M, mask_width * sizeof(float), cudaMemcpyHostToDevice);

    int gridSize = (width + BLOCK_SIZE - 1) / BLOCK_SIZE;
    convolution1D<<<gridSize, BLOCK_SIZE>>>(d_N, d_M, d_P,
                                           width, mask_width);

    cudaMemcpy(h_P, d_P, width * sizeof(float), cudaMemcpyDeviceToHost);

    printf("\nOutput Array:\n");
    for (int i = 0; i < width; i++) {
        printf("%.2f ", h_P[i]);
    }
    printf("\n");
    printf("\nPrakhar Umrao 230962210\n");

    free(h_N);
    free(h_M);
    free(h_P);

    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);

    return 0;
}
