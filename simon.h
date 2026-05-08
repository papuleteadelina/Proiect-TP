#ifndef SIMON_H
#define SIMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void clearScreen();
void getRandomSequence(const char* filename, char* buffer);
void playGame();
void clearInputBuffer();

#endif
