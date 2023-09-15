#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int m1, n1, m2, n2;
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

	vector<vector<int>> mat1;
	vector<vector<int>> mat2;
	vector<vector<int>> res;

	m1 = n1 = m2 = n2 = 3;


	mat1.resize(m1, vector<int>(n1));
	for(int i = 0; i < m1; i++)
		for(int j = 0; j < n1; j++)
			mat1[i][j] = i+j;

	mat2.resize(m2, vector<int>(n2));
	for(int i = 0; i < m2; i++)
		for(int j = 0; j < n2; j++)
			mat2[i][j] = i+j;


	res.resize(m1, vector<int>(n2));

	for(int current_process = 0; current_process < number_process; current_process++) {
		int i, j, k;
		if(fork() == 0) {	
			printf("Current process: %d\n", current_process);

			char filename[20];
			sprintf(filename, "results%d.txt", current_process);
			res_file = fopen(filename, "w");

			fprintf(res_file, "[son] pid %d from [parent] pid %d\n", getpid(), getppid());

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
			exit(0);
		}
	}

	for(int i = 0; i < number_process; i++) // loop will run n times (n=5)
		wait(NULL);



/*
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

*/


}
