#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    float C;
    float remaining;
    int weight;
    int completed;
} Task;

void ProportionalShare(Task tasks[], int n, int quantum) {
    int total_weight = 0;

    for (int i = 0; i < n; i++) {
        total_weight += tasks[i].weight;
        tasks[i].remaining = tasks[i].C;
        tasks[i].completed = 0;
    }

    int done = 0;

    while (done < n) {
        for (int i = 0; i < n; i++) {

            if (tasks[i].completed)
                continue;

            float time_slice = ((float)tasks[i].weight / total_weight) * quantum;

            if (time_slice < 1)
                time_slice = 1;

            printf("Running Task %d for %.2f units\n", tasks[i].id, time_slice);

            tasks[i].remaining -= time_slice;

            if (tasks[i].remaining <= 0) {
                tasks[i].completed = 1;
                total_weight -= tasks[i].weight;
                done++;
                printf("Task %d completed\n", tasks[i].id);
            }
        }
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

        printf("Execution Time: ");
        scanf("%f", &tasks[i].C);

        printf("Weight: ");
        scanf("%d", &tasks[i].weight);
    }

    ProportionalShare(tasks, n, 10);

    return 0;
}
