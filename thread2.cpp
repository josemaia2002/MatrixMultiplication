#include <iostream>
#include <vector>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

vector<vector<int>> mat1;
vector<vector<int>> mat2;
vector<vector<int>> res;

int number_threads;
int m1, n1, m2, n2;
FILE* fptr;
FILE* res_file;

void * multiplication(void *arg) {
	long int num = (long int)arg;
	int i, j, k;

	char filename[20];
	sprintf(filename, "results%ld.txt", num);


	res_file = fopen(filename, "w");
	if(res_file == NULL) {
		printf("ERROR!\n");
		exit(0);
	}

	// Indicates the dimensions in the file
	fprintf(res_file, "%d\n", m1);
	fprintf(res_file, "%d\n", n2);

	// Matrix multiplication
	int from = (num*m1)/number_threads;
	int to = ((num+1)*m1)/number_threads;

	for(i = from; i < to; i++) {
		for(j = 0; j < n2; j++) {
			res[i][j] = 0;
			for(k = 0; k < n2; k++) {
				res[i][j] += mat1[i][k] * mat2[k][j];				
			}
			fprintf(res_file, "%d\n", res[i][j]);	
		}
	}
}

int main(int argc, char const *argv[]) {
	long int i, j;
	pthread_t tid[10];

	// First matrix
	fptr = fopen(argv[1], "r");

	if(fptr == NULL) {
		printf("ERROR!\n");
		exit(0);
	}

	fscanf(fptr, "%d", &m1);
	fscanf(fptr, "%d", &n1);

	mat1.resize(m1, vector<int>(n1));

	int temp; // Stores a temp value that will be assigned to an element
	// Filling the matrix
	for(int i = 0; i < m1; i++) {
		for(int j = 0; j < n1; j++) {
			fscanf(fptr, "%d", &temp);		
			mat1[i][j] = temp;
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

	mat2.resize(m2, vector<int>(n2));

	// Filling the matrix
	for(int i = 0; i < m2; i++) {
		for(int j = 0; j < n2; j++) {
			fscanf(fptr, "%d", &temp);		
			mat2[i][j] = temp;
		}
	}	

	fclose(fptr);

	// Setting the size of the result matrix
	res.resize(m1, vector<int>(n2));

	number_threads = atoi(argv[3]);


	FILE *files[number_threads];
	for(int i = 0; i < number_threads; i++) {
		char filename[20];
		sprintf(filename, "results%d.txt", i);
		files[i] = fopen(filename, "w");
	}	


	// Create threads
	for(i = 0; i < number_threads; i++) {
		pthread_create(&tid[i], NULL, multiplication, (void*)i);
	}

	// Join threads
	for(j = 0; j < number_threads; j++) {
		pthread_join(tid[j], NULL);
	}	

	return 0;
}