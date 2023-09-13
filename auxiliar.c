#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	int m1, n1, m2, n2;
	FILE* fptr;

	m1 = atoi(argv[1]);
	n1 = atoi(argv[2]);
	m2 = atoi(argv[3]);
	n2 = atoi(argv[4]);


	// First matrix
	fptr = fopen("m1.txt", "w");

	if(fptr == NULL) {
		printf("ERROR!\n");
		exit(0);
	}

	// Indicates the dimensions in the file
	fprintf(fptr, "%d\n", m1);
	fprintf(fptr, "%d\n", n1);

	// Filling the matrix
	for(int i = 0; i < (m1*n1); i++) {
		fprintf(fptr, "%d\n", (1));	
		// mat1[i][j] = rand() % 10;
	}

	fclose(fptr);

	// Second matrix
	fptr = fopen("m2.txt", "w");

	if(fptr == NULL) {
		printf("ERROR!\n");
		exit(0);
	}

	// Indicates the dimensions in the file
	fprintf(fptr, "%d\n", m2);
	fprintf(fptr, "%d\n", n2);

	// Filling the matrix
	for(int i = 0; i < (m2*n2); i++) {
		fprintf(fptr, "%d\n", (1));	
		// mat2[i][j] = rand() % 10;
	}

	fclose(fptr);

	return 0;
}