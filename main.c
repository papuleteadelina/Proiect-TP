#include "simon.h"

void showLeaderboard() {
    printf("\n[WIP] Sistemul de clasament urmeaza sa fie adaugat.\n");
}

int main() {
    srand(time(NULL));
    int optiune;

    do {
        printf("\n--- SIMON SAYS ---\n");
        printf("1. Joaca\n");
        printf("2. Clasament (Leaderboard)\n");
        printf("3. Iesire\n");
        printf("Alege o optiune: ");

        if (scanf("%d", &optiune) != 1) {
            clearInputBuffer();
            optiune = 0;
        } else {
            clearInputBuffer();
        }

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
