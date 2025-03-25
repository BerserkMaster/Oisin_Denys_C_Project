#define SIZE 3

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void playerMove();
void computerMove();
void clearBoard();
void checkSpaces();
void checkWinner();
void check_data();  //check the ranking list
void save_data(char name[], int score);  //save data to a ranking list


char board[SIZE][SIZE];


int main() {
	clearBoard;
	printBoard();
	

	return 0;
}

void playerMove() {
}
void computerMove() {
}
void clearBoard() {

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; i < SIZE; i++) {
			board[i][j] = ' ';
		}
	}

}
void checkSpaces() {

}
void checkWinner() {

}

void printBoard() {
	printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
	printf("\n -- | -- | --\n");
	printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
	printf("\n -- | -- | --\n");
	printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
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