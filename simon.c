#include "simon.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void clearScreen() {
    system("clear || cls");
}

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

// Functie necesara pentru qsort (sorteaza descrescator)
int compareScores(const void* a, const void* b) {
    PlayerScore* p1 = (PlayerScore*)a;
    PlayerScore* p2 = (PlayerScore*)b;
    return p2->score - p1->score;
}

void showLeaderboard() {
    FILE* f = fopen("scoruri.txt", "r");
    if(!f) {
        printf("\nNu exista scoruri salvate momentan. Fii primul care joaca!\n");
        return;
    }

    PlayerScore scores[100];
    int count = 0;
    char line[256];

    // Citim din fisier
    while(fgets(line, sizeof(line), f)) {
        char* sep = strstr(line, " - ");
        if(sep) {
            *sep = '\0';
            strcpy(scores[count].name, line);
            scores[count].score = atoi(sep + 3);
            count++;
        }
    }
    fclose(f);

    // Sortam cu qsort
    qsort(scores, count, sizeof(PlayerScore), compareScores);

    // Afisam Top 5
    printf("\n--- CLASAMENT (TOP 5) ---\n");
    int limit = (count < 5) ? count : 5;
    for(int i = 0; i < limit; i++) {
        printf("%d. %s - %d puncte\n", i + 1, scores[i].name, scores[i].score);
    }
    printf("\n");
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

    int timeLimit = (diff == 1) ? 4 : (diff == 2) ? 3 : 2;
    int lives = 3;
    int score = 0;

    char playerName[50];
    printf("\nIntrodu numele tau (fara spatii): ");
    scanf("%s", playerName);
    clearInputBuffer();

    while(lives > 0) {
        char sequence[256];
        getRandomSequence(filename, sequence);

        clearScreen();
        printf("\nMemoreaza secventa:\n\n%s\n\n", sequence);
        fflush(stdout);
        sleep(timeLimit);

        clearScreen();
        char input[256];
        printf("Introdu secventa: ");

        if(fgets(input, sizeof(input), stdin) == NULL) {
            strcpy(input, "");
        }

        char cleanSeq[256];
        strcpy(cleanSeq, sequence);
        removeSpaces(cleanSeq);

        char cleanInput[256];
        strcpy(cleanInput, input);
        removeSpaces(cleanInput);

        if(strcmp(cleanSeq, cleanInput) == 0) {
            printf("\nCORECT!\n");
            score++;
            sleep(2);
        } else {
            lives--;
            if(lives == 0) {
                printf("\nGAME OVER\nScor final: %d\n", score);
            } else {
                printf("\nGRESIT!\nVieti ramase: %d\n", lives);
            }
            sleep(2);
        }
    }

    // Partea NOUA: Salvarea in fisier
    FILE* f = fopen("scoruri.txt", "a");
    if(f) {
        fprintf(f, "%s - %d\n", playerName, score);
        fclose(f);
    }
}
