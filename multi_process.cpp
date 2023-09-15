#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

FILE* res_file;

int main(int argc, char const *argv[]) {
	int number_elements = atoi(argv[1]);
	int number_process = atoi(argv[2]);

	FILE *files[number_process];
	for(int i = 0; i < number_process; i++) {
		char filename[20];
		sprintf(filename, "results%d.txt", i);
		files[i] = fopen(filename, "w");
	}	
	
	vector<int> v;
	for(int i = 0; i < number_elements; i++)
		v.push_back(i+1);

	for(int i = 0; i < number_process; i++) { // loop will run n times (n=5)
		if(fork() == 0) {
			// printf("[son] pid %d from [parent] pid %d\n", getpid(), getppid());
			int sum = 0;

			int from = (i*number_elements)/number_process;
			int to = ((i+1)*number_elements)/number_process;
	
			for(int j = from; j < to; j++) {
				sum += v[j];
			}

			char filename[20];
			sprintf(filename, "results%d.txt", i);

			res_file = fopen(filename, "w");

			// printf("Soma = %d\n", sum);
			fprintf(res_file, "%d\n", sum);	

			exit(0);
		}
	}

	for(int i = 0; i < number_process; i++) // loop will run n times (n=5)
		wait(NULL);
}












/*
	#include <iostream>
	#include <vector>
	#include <stdlib.h>
	#include <unistd.h>
	#include <time.h>
	#include <sys/types.h>


	using namespace std;

	vector<vector<int>> mat1;
	vector<vector<int>> mat2;
	vector<vector<int>> res;

	int number_process;
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

		number_process = atoi(argv[3]);


		FILE *files[number_process];
		for(int i = 0; i < number_process; i++) {
			char filename[20];
			sprintf(filename, "results%d.txt", i);
			files[i] = fopen(filename, "w");
		}	


		// Matrix multiplication
		int from = (num*m1)/number_process;
		int to = ((num+1)*m1)/number_process;	

		for(i = from; i < to; i++) {
			for(j = 0; j < n2; j++) {
				res[i][j] = 0;
				for(k = 0; k < n2; k++) {
					res[i][j] += mat1[i][k] * mat2[k][j];				
				}
				fprintf(res_file, "%d\n", res[i][j]);	
			}
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
*/