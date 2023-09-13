#include <iostream>
#include <vector>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

vector<vector<int>> mat1;
vector<vector<int>> mat2;
vector<vector<int>> res;

int number_threads;
// int m,n;
int m1, n1, m2, n2;
FILE* fptr;

void matrix_read() {
	int i, j;
	mat1.resize(m1, vector<int>(n1));
	mat2.resize(m2, vector<int>(n2));
	res.resize(m1, vector<int>(n2));

	// Filling
	for(i = 0; i < m1; i++) {
		for(j = 0; j < n1; j++){
			mat1[i][j] = 1;
		}
	}
	// Printing
	printf("Matrix 1\n");
	for(i = 0; i < m1; i++) {
		for(j = 0; j < n1; j++){
			cout << mat1[i][j] << " ";
		}
		cout << endl;
	}
		
	// Filling	
	for(i = 0; i < m2; i++) {
		for(j = 0; j < n2; j++){
			mat2[i][j] = 1;
		}
	}
	// Printing
	printf("Matrix 2\n");
	for(i = 0; i < m2; i++) {
		for(j = 0; j < n2; j++){
			cout << mat2[i][j] << " ";
		}
		cout << endl;
	}
}

void * multiplication(void *arg) {
	long int num = (long int)arg;
	int i, j, k;

	// Matrix multiplication
	int from = (num*m1)/number_threads;
	int to = ((num+1)*m1)/number_threads;

	printf("\n From=%d To=%d\n", from, to);
	for(i = from; i < to; i++) {
		for(j = 0; j < n2; j++) {
			res[i][j] = 0;
			for(k = 0; k < n2; k++) {
				res[i][j] += mat1[i][k] * mat2[k][j];				
			}
			printf("%d ", res[i][j]);
		}
	}

	printf("\nMatrix by thread %ld: \n", num);
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

	// matrix_read();

	// printf("Enter number of threads\n");
	// scanf("%d", &number_threads);

	number_threads = atoi(argv[3]);

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