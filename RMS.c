#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id;
    int C, T;
    int remaining;
    int next_release;
} Task;

void RMS(Task tasks[], int n, int sim_time) {
    float U = 0;

    // Step 1: Utilization
    for (int i = 0; i < n; i++) {
        U += (float)tasks[i].C / tasks[i].T;
    }

    float bound = n * (pow(2, 1.0/n) - 1);

    printf("\nUtilization = %.3f\n", U);
    printf("Bound = %.3f\n", bound);

    if (U <= bound)
        printf("Schedulable using RMS\n");
    else
        printf("Not guaranteed schedulable\n");

    // Step 2: Sort by period (priority)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (tasks[i].T > tasks[j].T) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }

    // Initialize
    for (int i = 0; i < n; i++) {
        tasks[i].remaining = 0;
        tasks[i].next_release = 0;
    }

    printf("\n--- RMS Scheduling Timeline ---\n");

    // Step 3: Simulation loop
    for (int t = 0; t < sim_time; t++) {

        // Release tasks
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_release) {
                tasks[i].remaining = tasks[i].C;
                tasks[i].next_release += tasks[i].T;
            }
        }

        // Pick highest priority READY task
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining > 0) {
                selected = i;
                break;
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d running\n", t, tasks[selected].id);
            tasks[selected].remaining--;
        } else {
            printf("Time %d: CPU Idle\n", t);
        }
    }
}

int main() {
    int n, sim_time;
    Task tasks[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;

        printf("\nTask %d\n", i+1);
        printf("Execution Time (C): ");
        scanf("%d", &tasks[i].C);

        printf("Period (T): ");
        scanf("%d", &tasks[i].T);
    }

    printf("\nEnter simulation time: ");
    scanf("%d", &sim_time);

    RMS(tasks, n, sim_time);

    return 0;
}
