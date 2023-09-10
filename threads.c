#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define MAX 100

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];
int step_i = 0;

void* multi(void* arg) {
    int i = step_i++; //i denotes row number of resultant matC
   
    for(int j = 0; j < MAX; j++) {
		for(int k = 0; k < MAX; k++) {
        	matC[i][j] += matA[i][k] * matB[k][j];
    	}
    }
}

int main(int argc, char const *argv[]) {
	int m1, n1, m2, n2;
	FILE* fptr;

	// First matrix
	fptr = fopen(argv[1], "r");

	if(fptr == NULL) {
		printf("ERROR!\n");
		exit(0);
	}

	fscanf(fptr, "%d", &m1);
	fscanf(fptr, "%d", &n1);

	// Filling the matrix
	if(matA == NULL){
		printf("ERROR\n");
	}
	else {
		for(int i = 0; i < m1; i++) {
			for(int j = 0; j < n1; j++) {
				fscanf(fptr, "%d", &matA[i][j]);		
			}
		}	
	}

	fclose(fptr);

	// Second matrix
	fptr = fopen(argv[2], "r");

	if(fptr == NULL) {
		printf("ERROR!\n");
		exit(0);
	}

	fscanf(fptr, "%d", &m2);
	fscanf(fptr, "%d", &n2);

	// Filling the matrix
	if(matB == NULL){
		printf("ERROR\n");
	}
	else {
		for(int i = 0; i < m2; i++) {
			for(int j = 0; j < n2; j++) {
				fscanf(fptr, "%d", &matB[i][j]);		
			}
		}	
	}

	fclose(fptr);

	int p = atoi(argv[3]);
	int number_threads = (m1*n2)/p;		

	pthread_t threads[number_threads];

	for(int i = 0; i < number_threads; i++) {
		int* p;
		pthread_create(&threads[i], NULL, multi, (void*)(p));
	}

	// joining and waiting for all threads to complete
	for(int i = 0; i < number_threads; i++)
		pthread_join(threads[i], NULL);

	// Displaying the result matrix
	printf("\nMultiplication of A and B\n");

	for(int i = 0; i < number_threads; i++) {
		for(int j = 0; j < number_threads; j++)
			printf("%d ", matC[i][j]);
		printf("\n");
	}	

	return 0;
}