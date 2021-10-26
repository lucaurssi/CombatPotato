#include <math.h>
#include <stdlib.h>

/*
    Function RANDOM needs the "srand(time(NULL));" command to work.
    so it needs the "stdlib.h" and "time.h" included on the main file.
    To use it type "random(n)", generating a random number from 0 to n-1.
*/
int random(int n){
    return rand()%n; // random numbers
}
