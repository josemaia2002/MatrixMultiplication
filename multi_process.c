#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int sumOdd = 0, sumEven = 0, n, i;
    n = fork();

    // Parent process
    if(n > 0) {
        for(i = 0; i < 10; i++) {
            if(a[i] % 2 == 0)
                sumEven = sumEven + a[i];
        }
        printf("Parent process %d: ", getpid());
        printf("sum of even no. is %d\n", sumEven);
    }

    // Child process
    else {
        for(i = 0; i < 10; i++) {
            if(a[i] % 2 != 0)
                sumOdd = sumOdd + a[i];
        }
        printf("Child process: %d: ", getpid());
        printf("sum of odd no. is %d\n", sumOdd);
    }
 
    return 0;
}