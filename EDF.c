#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    float C, D;
    float remaining;
    int arrival;
    int completed;
} Task;

void EDF(Task tasks[], int n) {
    float U = 0;

    for (int i = 0; i < n; i++) {
        U += tasks[i].C / tasks[i].D;
        tasks[i].remaining = tasks[i].C;
        tasks[i].completed = 0;
    }

    printf("\nUtilization = %.3f\n", U);

    if (U > 1)
        printf("Not feasible\n");
    else
        printf("Feasible\n");

    int t = 0, done = 0;

    while (done < n) {
        int idx = -1;
        float min_deadline = 1e9;

        for (int i = 0; i < n; i++) {
            if (!tasks[i].completed && tasks[i].arrival <= t) {
                if (tasks[i].D < min_deadline) {
                    min_deadline = tasks[i].D;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            t++;
            continue;
        }

        printf("Time %d: Running Task %d\n", t, tasks[idx].id);

        tasks[idx].remaining -= 1;

        if (tasks[idx].remaining <= 0) {
            tasks[idx].completed = 1;
            done++;
            printf("Task %d completed\n", tasks[idx].id);
        }

        t++;
    }
}

int main() {
    int n;
    Task tasks[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;

        printf("\nTask %d\n", i+1);

        printf("Execution Time (C): ");
        scanf("%f", &tasks[i].C);

        printf("Deadline (D): ");
        scanf("%f", &tasks[i].D);

        printf("Arrival Time: ");
        scanf("%d", &tasks[i].arrival);
    }

    EDF(tasks, n);

    return 0;
}
