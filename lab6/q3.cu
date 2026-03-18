#include <stdio.h>
#include <cuda_runtime.h>

#define BLOCK_SIZE 256

__global__ void oddEvenPhase(int *arr, int n, int phase) {

    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    int i;

    if (phase == 0) {
        i = 2 * tid;
    } else {
        i = 2 * tid + 1;
    }

    if (i + 1 < n) {
        if (arr[i] > arr[i + 1]) {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
}

int main() {

    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *h_arr = (int*)malloc(n * sizeof(int));

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &h_arr[i]);
    }

    int *d_arr;
    cudaMalloc((void**)&d_arr, n * sizeof(int));

    cudaMemcpy(d_arr, h_arr, n * sizeof(int), cudaMemcpyHostToDevice);

    int threads = BLOCK_SIZE;
    int pairs = n / 2;
    int blocks = (pairs + threads - 1) / threads;

    for (int i = 0; i < n; i++) {

        int phase = i % 2; 
        oddEvenPhase<<<blocks, threads>>>(d_arr, n, phase);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(h_arr, d_arr, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nSorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", h_arr[i]);
    }
    printf("\n");
    printf("\nPrakhar Umrao 230962210\n");


    cudaFree(d_arr);
    free(h_arr);

    return 0;
}
