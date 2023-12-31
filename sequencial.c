#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

	// Declaration
	int** vector1;
	int size1 = m1*n1;
	vector1 = (int**)malloc(size1 * sizeof(int*));
	for(int i = 0; i < m1; i++) {
		vector1[i] = (int*)malloc(n1 * sizeof(int));
	}

	// Filling the matrix
	if(vector1 == NULL){
		printf("ERROR\n");
	}
	else {
		for(int i = 0; i < m1; i++) {
			for(int j = 0; j < n1; j++) {
				fscanf(fptr, "%d", &vector1[i][j]);		
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

	// Declaration
	int** vector2;
	int size2 = m2*n2;
	vector2 = (int**)malloc(size2 * sizeof(int*));
	for(int i = 0; i < m2; i++) {
		vector2[i] = (int*)malloc(n2 * sizeof(int));
	}

	// Filling the matrix
	if(vector2 == NULL){
		printf("ERROR\n");
	}
	else {
		for(int i = 0; i < m2; i++) {
			for(int j = 0; j < n2; j++) {
				fscanf(fptr, "%d", &vector2[i][j]);		
			}
		}	
	}

	fclose(fptr);

	// Start measuring time
    struct timespec begin, end; 
    clock_gettime(CLOCK_REALTIME, &begin);
    
    // Calculation of the result
	int** result;
	int size3 = m1*n2;
	result = (int**)malloc(size3 * sizeof(int*));
	for(int i = 0; i < m1; i++) {
		result[i] = (int*)malloc(n2 * sizeof(int));
	}

	for(int i = 0; i < m1; i++) {
		for(int j = 0; j < n2; j++) {
			int sum = 0;
			for(int k = 0; k < m2; k++) {
				sum = sum + vector1[i][k] * vector2[k][j];
			}
			result[i][j] = sum;
		}
	}
    
    // Stop measuring time and calculate the elapsed time
    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    
    
	// Writing the result to the file
	fptr = fopen("data/sequential/result.txt", "w");

	if(fptr == NULL) {
		printf("ERROR!\n");
		exit(0);
	}

	// Indicates the dimensions in the file
	fprintf(fptr, "%d ", m1);
	fprintf(fptr, "%d\n", n2);

	for(int i = 0; i < m1; i++) {
		for(int j = 0; j < n2; j++) {
			fprintf(fptr, "c%d%d ", i+1, j+1);
			fprintf(fptr, "%d\n", result[i][j]);	
		}
	}
	fprintf(fptr, "%.3f\n", elapsed);
	printf("%f\n", elapsed);

	fclose(fptr);

	return 0;
}