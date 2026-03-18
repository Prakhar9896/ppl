#include <stdio.h>
#include <cuda.h>

__global__ void vectorAdd_a(float *A, float *B, float *C, int N) {
    int i = threadIdx.x;  
    if (i < N) {
        C[i] = A[i] + B[i];
    }
}

int main() {
    int N = 8;
    size_t size = N * sizeof(float);

    float h_A[N], h_B[N], h_C[N];

    for(int i = 0; i < N; i++) {
        h_A[i] = i;
        h_B[i] = i * 2;
    }

    float *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    vectorAdd_a<<<1, N>>>(d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    printf("Result:\n");
    for(int i = 0; i < N; i++)
        printf("%f ", h_C[i]);
    
    printf("\n");
    printf("Prakhar Umrao 230962210\n");

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
