#include <stdio.h>
#include <string.h>
#include <cuda_runtime.h>

__global__ void patternKernel(char* S, char* RS, int n) {
    int i = threadIdx.x;

    if (i < n) {
        int startPos = (i * n) - (i * (i - 1) / 2);
        int numToCopy = n - i;

        for (int j = 0; j < numToCopy; j++) {
            RS[startPos + j] = S[j];
        }
    }
}

int main() {
    char h_S[] = "PCAP";
    int n = strlen(h_S);
    int rs_len = (n * (n + 1)) / 2; 

    char *d_S, *d_RS;
    char *h_RS = (char*)malloc(rs_len + 1);

    cudaMalloc(&d_S, n + 1);
    cudaMalloc(&d_RS, rs_len + 1);

    cudaMemcpy(d_S, h_S, n + 1, cudaMemcpyHostToDevice);

    patternKernel<<<1, n>>>(d_S, d_RS, n);

    cudaMemcpy(h_RS, d_RS, rs_len, cudaMemcpyDeviceToHost);
    h_RS[rs_len] = '\0'; 

    printf("Input: %s\nOutput: %s\n", h_S, h_RS);

    printf("Prakhar Umrao 230962210\n");

    free(h_RS);
    cudaFree(d_S); cudaFree(d_RS);
    return 0;
}