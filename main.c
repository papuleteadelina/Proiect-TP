#include <stdio.h>
#include <stdlib.h>

// Funcții placeholder (urmează să fie implementate în viitor)
void playGame() {
    printf("\n[WIP] Logica jocului Simon Says va fi implementata aici.\n");
}

void showLeaderboard() {
    printf("\n[WIP] Sistemul de clasament urmeaza sa fie adaugat.\n");
}

int main() {
    int optiune;

    do {
        printf("\n--- SIMON SAYS ---\n");
        printf("1. Joaca\n");
        printf("2. Clasament (Leaderboard)\n");
        printf("3. Iesire\n");
        printf("Alege o optiune: ");

        scanf("%d", &optiune);

        switch(optiune) {
            case 1:
                playGame();
                break;
            case 2:
                showLeaderboard();
                break;
            case 3:
                printf("La revedere!\n");
                break;
            default:
                printf("Optiune invalida!\n");
        }
    } while(optiune != 3);

    return 0;
}
