#include <stdio.h>
#include <string.h>
#include <cuda.h>

__global__ void countWord(char *sentence, char *word, int *count, int len_s, int len_w) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx <= len_s - len_w) {
        int match = 1;

        for (int i = 0; i < len_w; i++) {
            if (sentence[idx + i] != word[i]) {
                match = 0;
                break;
            }
        }

        if (match) {
            if ((idx == 0 || sentence[idx - 1] == ' ') &&
                (idx + len_w == len_s || sentence[idx + len_w] == ' ')) {
                
                atomicAdd(count, 1);  
            }
        }
    }
}

int main() {
    char sentence[] = "cuda is fast and cuda is powerful cuda";
    char word[] = "cuda";

    int len_s = strlen(sentence);
    int len_w = strlen(word);

    char *d_sentence, *d_word;
    int *d_count, h_count = 0;

    cudaMalloc((void**)&d_sentence, len_s);
    cudaMalloc((void**)&d_word, len_w);
    cudaMalloc((void**)&d_count, sizeof(int));

    cudaMemcpy(d_sentence, sentence, len_s, cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, len_w, cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &h_count, sizeof(int), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocks = (len_s + threadsPerBlock - 1) / threadsPerBlock;

    countWord<<<blocks, threadsPerBlock>>>(d_sentence, d_word, d_count, len_s, len_w);

    cudaMemcpy(&h_count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Word '%s' occurred %d times\n", word, h_count);
    printf("Prakhar Umrao 230962210\n");

    cudaFree(d_sentence);
    cudaFree(d_word);
    cudaFree(d_count);

    return 0;
}