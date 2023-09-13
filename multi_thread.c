#include <stdio.h>
#include <pthread.h>

int number_threads;
int mat1[10][10], mat2[10][10], res[10][10];
int m,n;

void matrix_read() {
	int i, j;
	printf("Enter size of matrix\n");
	scanf("%d %d", &m, &n);

	printf("Enter matrix 1\n");
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++){
			scanf("%d" , &mat1[i][j]);
		}
	}

	printf("Enter matrix 2\n");
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++){
			scanf("%d" , &mat2[i][j]);
		}
	}
}

void print_matrix(int x[10][10]) {
	int i, j;
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			printf("%d ", x[i][j]);
		}
		printf("\n");
	}
}

void * multiplication(void *arg) {
	long int num = (long int)arg;
	int i, j, k;

	// Matrix multiplication
	int from = (num*m)/number_threads;
	int to = ((num+1)*m)/number_threads;

	printf("\n From=%d To=%d\n", from, to);
	for(i = from; i < to; i++) {
		for(j = 0; j < n; j++) {
			res[i][j] = 0;
			for(k = 0; k < n; k++) {
				res[i][j] += mat1[i][k] * mat2[k][j];				
			}
			printf("%d ", res[i][j]);
		}
	}

	printf("\nMatrix by thread %ld: \n", num);
}

int main() {
	long int i, j;
	pthread_t tid[10];

	matrix_read();

	printf("Enter number of threads\n");
	scanf("%d", &number_threads);

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

// 1 1 1 1 1 1 1 1 1