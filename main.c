#include <stdio.h>
#include <stdlib.h>
#include <time.h> //for random generation
#include <string.h>
#include <stdbool.h>
#include <unistd.h> // for usleep
#define SIZE 3

char board[SIZE][SIZE];

void resetBoard();
void printBoard();
void updateBoard(int, char);
void check_data();                      // check the ranking list
void save_data(char name[], int score); // save data to a ranking list
void printLogo();
void printVictory(char name[]);
void printDefeat();
void printDraw();
void printTopPlayers();
void printResult(bool singlePlayer, int turn, char name[]);
void togglePlayer(char *currentPlayer);
int randomNumGeneration(int range);
int interWithUserO(const char* user); // O turn
int interWithUserX(const char* user); // X turn:
int checkWinner(int data);



struct Name
{
  char name[15];
  int score;
};

int main()
{
  int winner = 0;
  struct Name userData[4];
  int score = 0;
  int userInput = 0;
  int user2Input = 0;
  int robotTurn = 0;
  int turn = 0;
  char currentPlayer = 'X';
  bool singlePlayer = false;

  printLogo();

  printf("Type:\n\n");
  printf("1: start new game vs PC\n2: start new game multiplayer\n3: check the ranking list\n");
  printf("------> ");
  scanf("%d", &userInput);

  switch (userInput)
  {
  case 1:
    singlePlayer= true;
    printf("Enter your name: ");
    scanf("%s", userData[1].name);
    resetBoard();
    printBoard();
    while (winner == 0)
    {
      printf("\n");
      if (currentPlayer == 'X' )
      {
        while (winner == 0)
        {
          userInput = interWithUserX(userData[1].name);
          int row = (userInput - 1) / SIZE;
          int col = (userInput - 1) % SIZE;
          if (board[row][col] == 'X' || board[row][col] == 'O')
          {
            printf("The cell %d is occupied\n", userInput);
            continue;
          }
          else
          {
            updateBoard(userInput, 'X');
            printBoard();
            puts("\n");
            winner = checkWinner(turn);
            if (winner == 1)
            {
              printResult(singlePlayer, turn,userData[1].name);
              save_data(userData[1].name, 1);
            }
            turn++;
            break;
          }
        }
      }
      else
      {
        while (winner == 0)
        {
          robotTurn = randomNumGeneration(9);
          int row = (robotTurn - 1) / SIZE;
          int col = (robotTurn - 1) % SIZE;
          if (board[row][col] == 'X' || board[row][col] == 'O')
          {
            robotTurn = randomNumGeneration(9);
          }
          else
          {
            updateBoard(robotTurn, 'O');
            printBoard();
            puts("\n");
            winner = checkWinner(turn);
            if (winner == 1)
            {
              printResult(singlePlayer, turn, userData[1].name);
              save_data(userData[1].name, -1);
            }
            turn++;
            break;
          }
        }
      }
    }
    break;






  case 2:
    singlePlayer = false;
    printf("Player 1 enter your name: ");
    scanf("%s", userData[2].name);
    save_data(userData[2].name, userData[2].score);
    printf("Player 2 enter your name: ");
    scanf("%s", userData[3].name);
    save_data(userData[3].name, userData[3].score);
    resetBoard();
    printBoard();

    while (winner == 0)
    {
      printf("\n");
      if (currentPlayer=='X')
      {
        while (winner == 0)
        {
          userInput = interWithUserX(userData[2].name);
          int row = (userInput - 1) / SIZE;
          int col = (userInput - 1) % SIZE;
          if (board[row][col] == 'X' || board[row][col] == 'O')
          {
            printf("The cell %d is occupied\n", userInput);
            continue;
          }
          else
          {
            updateBoard(userInput, 'X');
            printBoard();
            puts("\n");

            winner = checkWinner(turn);
            if (winner == 1)
            {
              printResult(singlePlayer, turn, userData[2].name);
              save_data(userData[2].name, 1);
              save_data(userData[3].name, -1);
              }
            togglePlayer(&currentPlayer);
            turn++;
            break;
          }
        }
      }
      else
      {
        while (winner == 0)
        {
          user2Input = interWithUserO(userData[3].name);
          int row = (user2Input - 1) / SIZE;
          int col = (user2Input - 1) % SIZE;
          if (board[row][col] == 'X' || board[row][col] == 'O')
          {
            printf("The cell %d is occupied\n", user2Input);
            continue;
          }
          else
          {
            updateBoard(user2Input, 'O');
            printBoard();
            puts("\n");
            winner = checkWinner(turn);
            if (winner == 1)
            {
              printResult(singlePlayer, turn, userData[3].name);
              save_data(userData[3].name, 1);
              save_data(userData[2].name, -1);
            }
            togglePlayer(&currentPlayer);
            turn++;
            break;
          }
        }
      }
    }
    break;









  case 3:
    check_data();
    break;
  }

  return 0;
}

int randomNumGeneration(int num)
{
  int randNum = 0;
  srand(time(NULL));        // seed for a generation function
  randNum = rand() % num + 1; // generate a digit within specific limit
  return randNum;
}

int interWithUserX(const char* user) {
    int choice = 0;
    int result;

    do {
        printf("%s, please enter a digit of cell to draw X (1-9): ", user);
        result = scanf("%d", &choice);

        while (getchar() != '\n'); // use this to flush the line

        if (result != 1 || choice < 1 || choice > 9) {
            printf("Invalid input. Must be a number between 1 and 9.\n");
        }

    } while (result != 1 || choice < 1 || choice > 9);

    return choice;
}

int interWithUserO(const char* user) {
    int choice = 0;
    int result;

    do {
        printf("%s, please enter a digit of cell to draw O (1-9): ", user);
        result = scanf("%d", &choice);

        while (getchar() != '\n');

        if (result != 1 || choice < 1 || choice > 9) {
            printf("Invalid input. Must be a number between 1 and 9.\n");
        }

    } while (result != 1 || choice < 1 || choice > 9);

    return choice;
}


void check_data()
{
  printTopPlayers();
  FILE *file = fopen("game_data.txt", "r");
  char ch;
  while ((ch = fgetc(file)) != EOF)
  {              // read until the end of the file
    putchar(ch); // similar to printf function
  }
}

void save_data(char name[], int score)
{
  FILE *file = fopen("game_data.txt", "r");
  if (file == NULL)
  {
    perror("File opening failed");
    return;
  }

  FILE *tempFile = fopen("temp_game_data.txt", "w");
  if (tempFile == NULL)
  {
    perror("Temporary file opening failed");
    fclose(file);
    return;
  }

  char line[30];
  int found = 0;

  while (fgets(line, sizeof(line), file))
  {
    char exstracted_name[15];
    int exstracted_score = 0;
    if (sscanf(line, "%s - %d", exstracted_name, &exstracted_score) == 2)
    {
      if (strcmp(exstracted_name, name) == 0)
      {
        exstracted_score += score;
        fprintf(tempFile, "%s - %d\n", exstracted_name, exstracted_score);
        found = 1;
      }
      else
      {
        fputs(line, tempFile);
      }
    }
    else
    {
      fputs(line, tempFile);
    }
  }

  if (!found)
  {
    fprintf(tempFile, "%s - %d\n", name, score);
  }

  fclose(file);
  fclose(tempFile);

  remove("game_data.txt");
  rename("temp_game_data.txt", "game_data.txt");
}

void printBoard()
{
  printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
  printf("\n --|---|--\n");
  printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
  printf("\n --|---|--\n");
  printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
}

void resetBoard()
{
  int boardCounter = 1;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      board[i][j] = '0' + boardCounter;
      boardCounter++;
    }
  }
  boardCounter = 0;
}

void updateBoard(int cell, char sym)
{
  int row = (cell - 1) / SIZE;
  int col = (cell - 1) % SIZE;

  if (board[row][col] == 'X' || board[row][col] == 'O')
  {
    printf("The cell %c is occupied\n", board[row][col]);
    return;
  }

  board[row][col] = sym;
}

int checkWinner(int data)
{
  // checking rows
  for (int row = 0; row < SIZE; row++)
  {
    if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
    {
      return 1;
    }

  }

  // check columns
  for (int col = 0; col < SIZE; col++)
  {
    if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
    {
      return 1;
    }
  }

  // check diagonals
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
  {
    return 1;
  }
  if (board[2][0] == board[1][1] && board[1][1] == board[0][2])
  {
    return 1;
  }
  // check draw
  if(data==8){
    return 1;
  }
  return 0;
}

void togglePlayer(char *player) {
  *player = (*player == 'X') ? 'O' : 'X';
}

void printResult(bool singlePlayer, int turn, char name[]){
  if(singlePlayer){
    if (turn % 2 == 0)
    {
      printVictory(name);
    }
    else
    {
      printDefeat();
    }
  }
  else{
    if(turn!=8){
      printVictory(name);
    } else{
      printDraw();
    }
  }
}


void printLogo()
{
  printf(" ______  ____   __                 ______   ____    __                 ______   ___     ___ \n");
  printf("|      ||    | /  ]               |      | /    |  /  ]               |      | /   \\   /  _]\n");
  printf("|      | |  | /  /      _____     |      ||  o  | /  /      _____     |      ||     | /  [_ \n");
  printf("|_|  |_| |  |/  /      |     |    |_|  |_||     |/  /      |     |    |_|  |_||  O  ||    _]\n");
  printf("  |  |   |  /   \\_     |_____|      |  |  |  _  /   \\_     |_____|      |  |  |     ||   [_ \n");
  printf("  |  |   |  \\     |                 |  |  |  |  \\     |                 |  |  |     ||     |\n");
  printf("  |__|  |____\\____|                 |__|  |__|__|\\____|                 |__|   \\___/ |_____|\n");
  printf("\n");
  printf("                             __    __   ___   ____   _      ___                             \n");
  printf("                            |  |__|  | /   \\ |    \\ | |    |   \\                            \n");
  printf("                            |  |  |  ||     ||  D  )| |    |    \\                           \n");
  printf("                            |  |  |  ||  O  ||    / | |___ |  D  |                          \n");
  printf("                            |  `  '  ||     ||    \\ |     ||     |                          \n");
  printf("                             \\      / |     ||  .  \\|     ||     |                          \n");
  printf("                              \\_/\\_/   \\___/ |__|\\_||_____||_____|                          \n");
  printf("\n");
}

void printVictory(char name[])
{
  const char* victoryMessages[] = {
    "%s, you are unbeatable!",
    "Incredible job, %s!",
    "You are the champion, %s!",
    "You are amazing, %s!",
    "%s just swept the board!"
};
int numMessages = sizeof(victoryMessages) / sizeof(victoryMessages[0]);

// Choose a random message
int msgIndex = randomNumGeneration(numMessages);

  const char* lines[] = {
        " __     _____ ____ _____ ___  ______   __",
        " \\ \\   / /_ _/ ___|_   _/ _ \\|  _ \\ \\ / /",
        "  \\ \\ / / | | |     | || | | | |_) \\ V / ",
        "   \\ V /  | | |___  | || |_| |  _ < | |  ",
        "    \\_/  |___\\____| |_| \\___/|_| \\_\\|_|  ",
    };

    for (int i = 0; i < 5; i++) {
        printf("%s\n", lines[i]); // prints out lines in array
        usleep(1000000); // Speed it prints at
    }

    printf("\n");
    printf("\t");
    printf(victoryMessages[msgIndex], name);
    printf("\n");
}



void printDefeat()
{
  printf("  ____  _____ _____ _____    _  _____ \n");
  printf(" |  _ \\| ____|  ___| ____|  / \\|_   _|\n");
  printf(" | | | |  _| | |_  |  _|   / _ \\ | |  \n");
  printf(" | |_| | |___|  _| | |___ / ___ \\| |  \n");
  printf(" |____/|_____|_|   |_____/_/   \\_\\_|  \n");
}



void printDraw()
{
    const char* lines[] = {
        "  ____                     ",
        " |  _ \\ _ __ __ ___      __",
        " | | | | '__/ _` \\ \\ /\\ / /",
        " | |_| | | | (_| |\\ V  V / ",
        " |____/|_|  \\__,_| \\_/\\_/  ",
    };

    for (int i = 0; i < 5; i++) {
        printf("%s\n", lines[i]); // prints out lines in array
        usleep(1000000); // Speed it prints at, 1 second between lines
    }
}

void printTopPlayers()
{
  printf("  _____ ___  ____    ____  _        _ __   _______ ____  ____  \n");
  printf(" |_   _/ _ \\|  _ \\  |  _ \\| |      / \\\\ \\ / / ____|  _ \\/ ___| \n");
  printf("   | || | | | |_) | | |_) | |     / _ \\\\ V /|  _| | |_) \\___ \\ \n");
  printf("   | || |_| |  __/  |  __/| |___ / ___ \\\\|| | |___|  _ < ___) | \n");
  printf("   |_| \\___/|_|     |_|   |_____/_/   \\_\\_| |_____|_| \\_\\____/ \n");
  printf("\nScores:\n");
}