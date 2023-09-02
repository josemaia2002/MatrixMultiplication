#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	int m1, n1, m2, n2;
	FILE* fptr;


	// First matrix
	fptr = fopen("m1.txt", "r");

	if(fptr == NULL) {
		printf("ERROR!\n");
		exit(0);
	}

	fscanf(fptr, "%d", &m1);
	fscanf(fptr, "%d", &n1);

	int* vector1;
	int size1 = m1*n1;
	vector1 = (int*)malloc(size1 * sizeof(int));

	if(vector1 == NULL){
		printf("ERROR\n");
	}
	else {
		for(int i = 0; i < size1; i++) {
			fscanf(fptr, "%d", &vector1[i]);		
		}	
	}

	fclose(fptr);

	// Second matrix
	fptr = fopen("m2.txt", "r");

	if(fptr == NULL) {
		printf("ERROR!\n");
		exit(0);
	}

	fscanf(fptr, "%d", &m2);
	fscanf(fptr, "%d", &n2);

	int* vector2;
	int size2 = m2*n2;
	vector2 = (int*)malloc(size2 * sizeof(int));

	if(vector2 == NULL){
		printf("ERROR\n");
	}
	else {
		for(int i = 0; i < size2; i++) {
			fscanf(fptr, "%d", &vector2[i]);		
		}	
	}

	fclose(fptr);

	for(int i = 0; i < size1; i++) {
		printf("%d\n", vector1[i]);
	}

	printf("#################\n");

	for(int i = 0; i < size2; i++) {
		printf("%d\n", vector2[i]);
	}	

	return 0;
}