//
// Created by Александр Плискин on 16.02.17.
//
#include "iostream"
#include "omp.h"
#include "../../array_utils.h"

const int N = 6;
const int M = 8;

int main() {

    srand(time(NULL));

    int **matrix = new int *[N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[M];
        for (int j = 0; j < M; j++) {
            matrix[i][j] = rand() % 10;
        }
    }

    print_matrix(matrix, N, M);
    printf("\n");

    int max = 0;
    int min = 10;

#pragma omp parallel for num_threads(2)
    for (int i = 0; i < N; i++) {
#pragma omp critical
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
#pragma omp critical
        for (int j = 0; j < M; j++) {
            if (matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
    }
    printf("Max is : %d, min is : %d\n", max, min);
}
