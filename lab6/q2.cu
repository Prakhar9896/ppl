#include <stdio.h>
#include <cuda_runtime.h>

__global__ void rankSort(int *input, int *output, int n) {

    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < n) {

        int rank = 0;

        for (int j = 0; j < n; j++) {
            if (input[j] < input[i] || 
               (input[j] == input[i] && j < i)) {
                rank++;
            }
        }

        output[rank] = input[i];
    }
}

int main() {

    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *h_input = (int*)malloc(n * sizeof(int));
    int *h_output = (int*)malloc(n * sizeof(int));

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &h_input[i]);
    }

    int *d_input, *d_output;

    cudaMalloc((void**)&d_input, n * sizeof(int));
    cudaMalloc((void**)&d_output, n * sizeof(int));

    cudaMemcpy(d_input, h_input, n * sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;

    rankSort<<<gridSize, blockSize>>>(d_input, d_output, n);

    cudaMemcpy(h_output, d_output, n * sizeof(int), cudaMemcpyDeviceToHost);

    printf("\nSorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", h_output[i]);
    }
    printf("\n");

    cudaFree(d_input);
    cudaFree(d_output);
    free(h_input);
    free(h_output);

    return 0;
}