#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_data(char name[], int score);

int main() {
    char names[] = "Came";
    int score = 50;
    save_data(names, score);

    return 0;
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

    char line[100];  // Increased buffer size to handle longer lines
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        // Check if the line contains the name
        if (strstr(line, name) != NULL) {
            // Write the updated name and score instead of the old line
            fprintf(tempFile, "%s - %d\n", name, score);
            found = 1;
        } else {
            // Write the line unchanged
            fputs(line, tempFile);
        }
    }

    // If name was not found, append new entry
    if (!found) {
        fprintf(tempFile, "%s - %d\n", name, score);
    }

    // Close files
    fclose(file);
    fclose(tempFile);

    // Replace old file with new file
    remove("game_data.txt");
    rename("temp_game_data.txt", "game_data.txt");
}