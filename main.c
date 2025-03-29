#define SIZE 3
#define playerMove 'X'
#define computerMove 'O'
#define PLAYER 1
#define COMPUTER 2

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


void checkWinner();
void resetBoard();
void checkWinner();
void printBoard();
void playTicTacToe(int currentPlayer);



char board[SIZE][SIZE];
bool gameOver;
int currentPlayer;
int winner;


int main() {
	
	playTicTacToe(PLAYER);

	return 0;
}

void playTicTacToe(int currentPlayer){
    // displayInstructions();
    resetBoard();
	printBoard();
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

void checkWinner() {
    // checking rows
    for(int row=0; row<SIZE; row++){
 if(board[row][0]== board[row][1] && board[row][1] == board[row][2]){
    gameOver = true;
    winner = currentPlayer;
 }
    }

    // check columns
    for(int col=0; col<SIZE; col++){
 if(board[0][col]== board[1][col] && board[1][col] == board[2][col]){
    gameOver = true;
    winner = currentPlayer;
 }
    }

    // check diagonals
 if(board[0][0]== board[1][1] && board[1][1] == board[2][2]){
    gameOver = true;
    winner = currentPlayer;
 }
  if(board[2][0]== board[1][1] && board[1][1] == board[0][2]){
    gameOver = true;
    winner = currentPlayer;
 }

}

void printBoard() {
	printf("\t\t\t%c | %c | %c ", board[0][0], board[0][1], board[0][2]);
	printf("\n\t\t\t----------\n");
	printf("\t\t\t%c | %c | %c ", board[1][0], board[1][1], board[1][2]);
	printf("\n\t\t\t----------\n");
	printf("\t\t\t%c | %c | %c ", board[2][0], board[2][1], board[2][2]);
}
