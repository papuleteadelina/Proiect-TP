#include "simon.h"

// Curata buffer-ul de citire
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Curata ecranul
void clearScreen() {
    system("clear || cls");
}

// Elimina spatiile si enter-urile pentru a compara corect (ex: "1 5" devine "15")
void removeSpaces(char* str) {
    int i = 0, j = 0;
    while(str[i]) {
        if(str[i] != ' ' && str[i] != '\n' && str[i] != '\r') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

// Extrage linia aleatorie din fisier
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

// Logica principala a jocului
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

    int timeLimit = (diff == 1) ? 4 : (diff == 2) ? 3 : 2; // [cite: 29, 30, 31, 32, 33]
    int lives = 3; // [cite: 34, 35, 36]
    int score = 0;

    char playerName[50];
    printf("\nIntrodu numele tau (fara spatii): ");
    scanf("%s", playerName);
    clearInputBuffer();

    // Cat timp jucatorul are vieti, jocul continua
    while(lives > 0) {
        char sequence[256];
        getRandomSequence(filename, sequence);

        clearScreen();
        printf("\nMemoreaza secventa:\n\n%s\n\n", sequence); // [cite: 10]
        fflush(stdout);
        sleep(timeLimit);

        clearScreen(); // [cite: 11]
        char input[256];
        printf("Introdu secventa: "); // [cite: 12]

        // Citim raspunsul (cu tot cu spatii)
        if(fgets(input, sizeof(input), stdin) == NULL) {
            strcpy(input, "");
        }

        // Curatam ambele siruri de spatii ca sa le putem compara
        char cleanSeq[256];
        strcpy(cleanSeq, sequence);
        removeSpaces(cleanSeq);

        char cleanInput[256];
        strcpy(cleanInput, input);
        removeSpaces(cleanInput);

        // Verificam daca raspunsul este corect [cite: 13]
        if(strcmp(cleanSeq, cleanInput) == 0) {
            printf("\nCORECT!\n"); // [cite: 15]
            score++;
            sleep(2);
        } else {
            lives--; // [cite: 37, 38]
            if(lives == 0) {
                printf("\nGAME OVER\nScor final: %d\n", score); // [cite: 39, 40, 41]
            } else {
                printf("\nGRESIT!\nVieti ramase: %d\n", lives); // [cite: 14]
            }
            sleep(2);
        }
    }

    printf("\n[WIP] In viitor, scorul lui %s va fi salvat in fisierul scoruri.txt!\n", playerName);
    sleep(2);
}
