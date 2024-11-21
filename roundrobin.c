#include <stdio.h>

int arr[100][6]; // Process details: AT, BT, ST, ET, TAT, WT

void RoundRobin(int n, int time_quantum) {
    int remaining_bt[100];  // Remaining burst time of processes
    int completed = 0, current_time = 0, process_queue[100];
    int front = 0, rear = -1, visited[100] = {0}; // Circular queue and visited tracker

    // Initialize remaining burst time
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = arr[i][1];
    }

    // Add first process to the queue
    for (int i = 0; i < n; i++) {
        if (arr[i][0] <= current_time && !visited[i]) {
            process_queue[++rear] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front > rear) { // If queue is empty, increase time
            current_time++;
            for (int i = 0; i < n; i++) {
                if (arr[i][0] <= current_time && !visited[i]) {
                    process_queue[++rear] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        // Dequeue the process at the front
        int current_process = process_queue[front++];

        // If this is the first time process executes, set the Start Time
        if (remaining_bt[current_process] == arr[current_process][1]) {
            arr[current_process][2] = current_time; // Start Time
        }

        // Process execution for Time Quantum or remaining time
        int exec_time = (remaining_bt[current_process] > time_quantum) ? time_quantum : remaining_bt[current_process];
        remaining_bt[current_process] -= exec_time;
        current_time += exec_time;

        // Add new processes arriving during execution to the queue
        for (int i = 0; i < n; i++) {
            if (arr[i][0] <= current_time && !visited[i]) {
                process_queue[++rear] = i;
                visited[i] = 1;
            }
        }

        // If process is completed
        if (remaining_bt[current_process] == 0) {
            completed++;
            arr[current_process][3] = current_time; // End Time
            arr[current_process][5] = arr[current_process][3] - arr[current_process][0] - arr[current_process][1]; // Waiting Time
            arr[current_process][4] = arr[current_process][3] - arr[current_process][0]; // Turnaround Time
        } else {
            // Re-enqueue the current process
            process_queue[++rear] = current_process;
        }
    }
}

void sort(int n) {
    // Sort processes by Arrival Time (AT)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i][0] > arr[j][0]) {
                for (int k = 0; k < 6; k++) {
                    int temp = arr[i][k];
                    arr[i][k] = arr[j][k];
                    arr[j][k] = temp;
                }
            }
        }
    }
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    // Initialize process array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            arr[i][j] = 0;
        }
    }

    // Input Arrival Time and Burst Time
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for process %d: ", i + 1);
        scanf("%d %d", &arr[i][0], &arr[i][1]);
    }

    sort(n);             // Sort processes by Arrival Time
    RoundRobin(n, time_quantum); // Perform Round Robin scheduling

    // Output results
    printf("AT\tBT\tST\tET\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5]);
    }

    // Calculate and display average Waiting Time and Turnaround Time
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += arr[i][5];
        total_turnaround_time += arr[i][4];
    }

    printf("Average Waiting Time = %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_turnaround_time / n);

    return 0;
}
