#include "simon.h"

// Functie care curata orice enter sau spatiu ramas in buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void clearScreen() {
    system("clear || cls");
}

void getRandomSequence(const char* filename, char* buffer) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        strcpy(buffer, "1 2 3");
        return;
    }

    int count = 0;
    char line[256];
    while(fgets(line, sizeof(line), file)) count++;

    if (count == 0) {
        strcpy(buffer, "1 2 3");
        fclose(file);
        return;
    }

    rewind(file);
    int randomLine = rand() % count;
    for(int i = 0; i <= randomLine; i++) {
        fgets(line, sizeof(line), file);
    }

    line[strcspn(line, "\r\n")] = 0;
    strcpy(buffer, line);
    fclose(file);
}

void playGame() {
    int choice;
    printf("\nAlege tipul de secventa:\n1. Cifre\n2. Litere\n3. Cuvinte\nOptiune: ");
    scanf("%d", &choice);
    clearInputBuffer();

    const char* filename;
    if(choice == 1) filename = "cifre.txt";
    else if(choice == 2) filename = "litere.txt";
    else filename = "cuvinte.txt";

    int diff;
    printf("\nAlege dificultatea:\n1. Usor (4 sec)\n2. Mediu (3 sec)\n3. Greu (2 sec)\nOptiune: ");
    scanf("%d", &diff);
    clearInputBuffer();

    // Setam timpul de asteptare pe baza dificultatii
    int timeLimit = (diff == 1) ? 4 : (diff == 2) ? 3 : 2;

    char sequence[256];
    getRandomSequence(filename, sequence);

    clearScreen();
    printf("\nMemoreaza secventa:\n\n%s\n\n", sequence);
    fflush(stdout); // Forteaza textul sa apara pe ecran inainte de sleep
    sleep(timeLimit);

    clearScreen();

    // Placeholder pentru interactiunea viitoare
    printf("[WIP] Timpul a expirat! Aici jucatorul va fi invitat sa introduca raspunsul.\n");
    sleep(3); // Pauza mica pentru a putea citi mesajul inainte sa se intoarca in meniu
}
