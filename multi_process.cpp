#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int m1, n1, m2, n2;
FILE* fptr;
FILE* res_file;

int main(int argc, char const *argv[]) {
	vector<vector<int>> mat1;
	vector<vector<int>> mat2;
	vector<vector<int>> res;

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

	int p = atoi(argv[3]);
	int number_process = (n1*m2)/p;

	FILE *files[number_process];
	for(int i = 0; i < number_process; i++) {
		char filename[40];
		sprintf(filename, "data/process/results%d.txt", i);

		files[i] = fopen(filename, "w");
	}	

	// Create the child processes to calculate the result
	for(int current_process = 0; current_process < number_process; current_process++) {
		int i, j, k;
		if(fork() == 0) {	
			char filename[40];
			sprintf(filename, "data/process/results%d.txt", current_process);
			res_file = fopen(filename, "w");

			// Indicates the dimensions in the file
			fprintf(res_file, "%d\n", m1);
			fprintf(res_file, "%d\n", n2);

			// Start measuring time
		    struct timespec begin, end; 
		    clock_gettime(CLOCK_REALTIME, &begin);    

			int from = (current_process*m1)/number_process;
			int to = ((current_process+1)*m1)/number_process;

			for(i = from; i < to; i++) {
				for(j = 0; j < n2; j++) {
					res[i][j] = 0;
					for(k = 0; k < n2; k++) {
						res[i][j] += mat1[i][k] * mat2[k][j];				
					}
					fprintf(res_file, "%d\n", res[i][j]);	
				}
			}

			// Stop measuring time and calculate the elapsed time
		    clock_gettime(CLOCK_REALTIME, &end);
		    long seconds = end.tv_sec - begin.tv_sec;
		    long nanoseconds = end.tv_nsec - begin.tv_nsec;
		    double elapsed = seconds + nanoseconds*1e-9;
		    
			fprintf(res_file, "%.3f\n", elapsed);
			printf("%f\n", elapsed);

			exit(0);
		}
	}

	for(int i = 0; i < number_process; i++) 
		wait(NULL);

}