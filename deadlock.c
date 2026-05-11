#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, r;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &r);

    int allocation[n][r], request[n][r], available[r];
    int work[r];
    bool finish[n];

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < r; i++) {
        scanf("%d", &available[i]);
        work[i] = available[i];
    }

    for (int i = 0; i < n; i++) {
        bool all_zero = true;
        for (int j = 0; j < r; j++) {
            if (allocation[i][j] != 0) {
                all_zero = false;
                break;
            }
        }
        finish[i] = all_zero;
    }

    bool found;
    do {
        found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_be_done = true;
                for (int j = 0; j < r; j++) {
                    if (request[i][j] > work[j]) {
                        can_be_done = false;
                        break;
                    }
                }

                if (can_be_done) {
                    for (int j = 0; j < r; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }
    } while (found);

    int deadlocked[n], count = 0;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlocked[count++] = i;
        }
    }

    if (count > 0) {
        printf("\nSystem is in a DEADLOCK state.");
        printf("\nDeadlocked processes: ");
        for (int i = 0; i < count; i++) {
            printf("P%d ", deadlocked[i]);
        }
        printf("\n");
    } else {
        printf("\nNo Deadlock Detected. System is safe.\n");
    }

    return 0;
}
