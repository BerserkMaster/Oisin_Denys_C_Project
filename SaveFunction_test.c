#include <stdio.h>
#include <stdlib.h>

int main() {


    return 0;
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