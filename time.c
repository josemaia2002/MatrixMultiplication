#include <stdio.h>
#include <time.h>

void enter() {
    while(1)
        if(getchar())
            break;
}

int main () {
    // Start measuring time
    struct timespec begin, end; 
    clock_gettime(CLOCK_REALTIME, &begin);
    
    enter();
    
    // Stop measuring time and calculate the elapsed time
    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    
    printf("Time measured: %.3f seconds.\n", elapsed);
    
    return 0;
}   