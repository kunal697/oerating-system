#include <stdio.h>
#include <limits.h>

// Define the process structure
struct P {
    int id, at, bt, st, ft, rt, priority;
};

// Function to find the process with the highest priority available at the current time
int findhighestpriority(struct P p[], int ct, int n) {
    int highestpriorityindex = -1;
    int highestpriority = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (p[i].at <= ct && p[i].rt > 0) { // Process is available and not completed
            if (p[i].priority < highestpriority) { // Check for higher priority
                highestpriority = p[i].priority;
                highestpriorityindex = i;
            }
        }
    }
    return highestpriorityindex;
}

// Priority Preemptive Scheduling Function
void prioritypreemptive(struct P p[], int n) {
    int ct = 0; // Current Time
    int completed = 0; // Number of completed processes
    int twt = 0, ttat = 0; // Total waiting time and turnaround time

    printf("\nPriority Preemptive Scheduling:\n");
    printf("ID\tAT\tBT\tPriority\tST\tFT\tTAT\tWT\n");

    while (completed < n) {
        int id = findhighestpriority(p, ct, n);

        if (id != -1) { // If a process is found
            if (p[id].rt == p[id].bt) { // First time the process is executed
                p[id].st = ct;
            }

            p[id].rt--; // Reduce remaining time by 1 unit
            ct++; // Increment current time

            if (p[id].rt == 0) { // Process completed
                p[id].ft = ct;
                int tat = p[id].ft - p[id].at; // Turnaround Time
                int wt = tat - p[id].bt; // Waiting Time
                twt += wt; // Add to total waiting time
                ttat += tat; // Add to total turnaround time
                completed++;

                printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
                       p[id].id, p[id].at, p[id].bt, p[id].priority,
                       p[id].st, p[id].ft, tat, wt);
            }
        } else {
            ct++; // Increment time if no process is ready
        }
    }

    printf("Average Waiting Time: %.2f\n", (float)twt / n);
    printf("Average Turnaround Time: %.2f\n", (float)ttat / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct P p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1; // Assign process ID
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].rt = p[i].bt; // Initialize remaining time
    }

    // Sort processes by arrival time
    struct P temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Perform priority preemptive scheduling
    prioritypreemptive(p, n);

    return 0;
}
