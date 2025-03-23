#include <stdio.h>
#include <stdlib.h>
#include <time.h>      //for random generation

int randomNumGeneration();
int interWithUserO(int* );  // O turn
int interWithUserX(int* );  // X turn

int main() {
    int counter = 0;
    int turn = 0;
    int *ptrTurn = &turn;

    randomNumGeneration();

    while (counter < 9){
      if (counter % 2 == 0) {
        interWithUserO(ptrTurn);
      } else if (counter % 2 != 0) {
        interWithUserX(ptrTurn);
      } 

      counter++;
    } 


    return 0;
}

int randomNumGeneration(){
    int randNum = 0;
    srand(time(NULL));  //seed for a generation function
    randNum = rand() % 9 + 1;  //generate a digit within specific limit 
    return randNum;
}

int interWithUserO(int* o){
    printf("Please enter a digit of cell to draw O: ");
    scanf("%d", o);
}

int interWithUserX(int* x){
    int choice = 0;
    printf("Please enter a digit of cell to draw X: ");
    scanf("%d", x);
}