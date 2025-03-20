#define SIZE 3

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void playerMove();
void computerMove();
void clearBoard();
void checkSpaces();
void checkWinner();

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
