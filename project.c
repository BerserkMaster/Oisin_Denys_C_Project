#include <stdio.h>
#include <stdlib.h>
#include <time.h>      //for random generation
#include <string.h>

#define SIZE 3

void resetBoard();
void check_data();  //check the ranking list
void save_data(char name[], int score);  //save data to a ranking list
int randomNumGeneration();
int interWithUserO();  // O turn
int interWithUserX();  // X turn:
void printBoard();
void resetBoard();
void updateBoard(int, char);

char board[SIZE][SIZE];

struct Name{
  char name[15];
  int score;  
};

int main() {
    struct Name userData[3];
    int score = 0;
    int userInput = 0;
    int robotTurn = 0;
    int counter = 0;
    int turn = 0;
    int *ptrTurn = &turn;
    

    printf("1: start new game vs PC\n2: start new game multiplayer\n3: check the ranking list\n");
    scanf("%d", &userInput);

    switch (userInput) {
      case 1: 
      printf("Enter your name: ");
      scanf("%s", userData[1].name);
      resetBoard();
      printBoard();
        while(1) {
          printf("\n");
          if (turn % 2 == 0) {
            while (1) {
              userInput = interWithUserX();
              int row = (userInput - 1) / SIZE;
              int col = (userInput - 1) % SIZE;
                if (board[row][col] == 'X' || board[row][col] == 'O') {
                  printf("The cell %d is occupied\n", userInput);
                  continue;
                } else {
                  updateBoard(userInput, 'X');
                  turn++;
                  break;
                }
            }
          } else {
              while(1) {  
                robotTurn = randomNumGeneration();
                int row = (robotTurn - 1) / SIZE;
                int col = (robotTurn - 1) % SIZE;
                  if (board[row][col] == 'X' || board[row][col] == 'O') {
                    robotTurn = randomNumGeneration();
                  } else {
                    updateBoard(robotTurn,'O');
                    printBoard();
                    printf("\n");
                    turn++;
                    break; 
                  }
              } 
          }
        }
      userData[1].score = 4;
      save_data(userData[1].name, userData[1].score);
      break;
      case 2:
      printf("Player 1 enter your name: ");
      scanf("%s", userData[2].name);
      userData[2].score = 3;
      save_data(userData[2].name, userData[2].score);
      printf("Player 2 enter your name: ");
      userData[3].score = 3;
      scanf("%s", userData[3].name);
      save_data(userData[3].name, userData[3].score);
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

int interWithUserO(){
    int input = 0;
    printf("Please enter a digit of cell to draw O: ");
    scanf("%d", &input);
    return input;
}

int interWithUserX(){
    int choice = 0;
    printf("Please enter a digit of cell to draw X: ");
    scanf("%d", &choice);
    return choice;
}

void check_data() {
  FILE* file = fopen("game_data.txt", "r");
  char ch;
  while ((ch = fgetc(file)) != EOF) {  // read until the end of the file
    putchar(ch);  // similar to printf function
  }
}

void save_data(char name[], int score) {
    FILE* file = fopen("game_data.txt", "r");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }

    FILE* tempFile = fopen("temp_game_data.txt", "w");
    if (tempFile == NULL) {
        perror("Temporary file opening failed");
        fclose(file);
        return;
    }

    char line[30];  
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
      char exstracted_name[15];
      int exstracted_score = 0;
      if (sscanf(line, "%s - %d", exstracted_name, &exstracted_score) == 2) {
        if (strcmp(exstracted_name, name) == 0) {
          exstracted_score += score;
          fprintf(tempFile, "%s - %d\n", exstracted_name, exstracted_score);
          found = 1;
        } else {
          fputs(line, tempFile);
        }
      } else {
        fputs(line, tempFile);
      }
    }

    if (!found) {
        fprintf(tempFile, "%s - %d\n", name, score);
    }

    fclose(file);
    fclose(tempFile);

    remove("game_data.txt");
    rename("temp_game_data.txt", "game_data.txt");
  }

void printBoard() {
	printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
	printf("\n --|---|--\n");
	printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
	printf("\n --|---|--\n");
	printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
}

void resetBoard() {
  int boardCounter = 1;
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        board[i][j] = '0' + boardCounter;
              boardCounter++;
      }
    }
      boardCounter =0;  
}

void updateBoard(int cell, char sym) {
  int row = (cell - 1) / SIZE;
  int col = (cell - 1) % SIZE;

  if (board[row][col] == 'X' || board[row][col] == 'O') {
    printf("The cell %c is occupied\n", board[row][col]);
    return;
  }

  board[row][col] = sym;
}