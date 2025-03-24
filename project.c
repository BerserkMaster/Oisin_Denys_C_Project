#include <stdio.h>
#include <stdlib.h>
#include <time.h>      //for random generation
#include <string.h>

void check_data();  //check the ranking list
void save_data(char name[], int score);  //save data to a ranking list
int randomNumGeneration();
int interWithUserO(int* );  // O turn
int interWithUserX(int* );  // X turn:

struct Name{
  char name[15];
  int score;  
};

int main() {
    struct Name userData[3];
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
      scanf("%s", &userData[1].name);
      userData[1].score = 10;
      save_data(userData[1].name, userData[1].score);
      break;
      case 2:
      printf("Player 1 enter your name: ");
      scanf("%s", &userData[1].name);
      userData[1].score = 10;
      printf("Player 2 enter your name: ");
      scanf("%s", &userData[1].name);
      save_data(userData[1].name, userData[1].score);
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

void save_data(char name[], int score) {

  FILE* file = fopen("game_data.txt", "r+");
  if (file == NULL) {
    perror("File opening failed");
    return;
  }

  char line[25];
  int pos = 0;
  int found = 0;
  FILE *tempFile = fopen("temp_game_data.txt", "w");

  while (fgets(line, sizeof(line), file)) {
    pos = ftell(file);
    if (strstr(line, name) != NULL) {
      fseek(file, pos - strlen(line), SEEK_SET);
      fprintf(file, "%s - %d\n", name, score);
      fflush(file);  // flush buffer to ensure that data is written
      found = 1;
      break;
    }
      }
  if (!found) {
    fseek(file, 0, SEEK_END);
    fprintf(file, "%s - %d\n", name, score);
    fflush(file);
  }


 fclose(file);
}