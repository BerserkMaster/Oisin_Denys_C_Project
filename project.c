#include <stdio.h>
#include <stdlib.h>
#include <time.h>      //for random generation

int randomNumGeneration();

int main() {
    printf("A random digit is: %d ", randomNumGeneration());



    return 0;
}

int randomNumGeneration(){
    int randNum = 0;
    srand(time(NULL));  //seed for a generation function
    randNum = rand() % 9 + 1;  //generate a digit within specific limit 
    return randNum;
}