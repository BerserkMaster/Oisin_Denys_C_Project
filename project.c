#include <stdio.h>
#include <stdlib.h>
#include <time.h>      //for random generation

void check_data();  //check the ranking list
void save_data();  //save data to a ranking list
int randomNumGeneration();
int interWithUserO(int* );  // O turn
int interWithUserX(int* );  // X turn

int main() {
    char name;
    int score = 0;
    int userInput = 0;
    int counter = 0;
    int turn = 0;
    int *ptrTurn = &turn;

    printf("1: start new game vs PC\n2: start new game multiplayer\n3: check the ranking list\n");
    scanf("%d", &userInput);

    switch (userInput) {
      case 1: 
      printf("Enter your name: ");
      scanf("%c", &name);
      break;
      case 2:
      case 3:
      check_data();
      break;
    }    

   // randomNumGeneration();

    /*while (counter < 9){
      if (counter % 2 == 0) {
        interWithUserO(ptrTurn);
      } else if (counter % 2 != 0) {
        interWithUserX(ptrTurn);
      } 

      counter++;
    } 
*/

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

void check_data() {
  FILE* file = fopen("game_data.txt", "r");
  char ch;
  while ((ch = fgetc(file)) != EOF) {  // read until the end of the file
    putchar(ch);  // similar to printf function
  }
}

void save_data() {
  FILE* file = fopen("game_data.txt", "w");
}