#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define M 500
#define N 500
#define P 500
#define NUM_THREADS 4

int A[M][N], B[N][P], C[M][P];

typedef struct {
    int start_row;
    int end_row;
} ThreadData;

void *multiply_matrices(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("Thread processing rows %d to %d took %f seconds.\n", data->start_row, data->end_row - 1, time_taken);
    pthread_exit(NULL);
}

void sequential_multiplication() {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    gettimeofday(&end, NULL);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("Sequential multiplication took %f seconds.\n", time_taken);
}

int main() {
    // Initialize matrices with random values
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            B[i][j] = rand() % 10;
        }
    }
    
    printf("Running sequential multiplication...\n");
    sequential_multiplication();
    
    printf("Running parallel multiplication with %d threads...\n", NUM_THREADS);
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int rows_per_thread = M / NUM_THREADS;
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == NUM_THREADS - 1) ? M : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, multiply_matrices, &thread_data[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Parallel multiplication completed.\n");
    return 0;
}

