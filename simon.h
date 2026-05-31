#ifndef SIMON_H
#define SIMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Structura pentru a retine numele si scorul
typedef struct {
    char name[50];
    int score;
} PlayerScore;

void clearScreen();
void getRandomSequence(const char* filename, char* buffer);
void playGame();
void clearInputBuffer();
void removeSpaces(char* str);
void showLeaderboard();

#endif
