#include <stdio.h>
#include <limits.h> // For INT_MAX

int arr[100][7]; // 2D array to store process details.

void SJF_Preemptive(int n) {
    int completed = 0, current_time = 0;
    int remaining_bt[100]; // Array to store remaining burst times.
    int min_bt, shortest = -1, finish_time;
    int is_found = 0;

    // Initialize remaining burst time
    for (int i = 0; i < n; i++) {
        remaining_bt[i] = arr[i][1];
    }

    while (completed < n) {
        // Find the process with the shortest remaining burst time at the current time
        min_bt = INT_MAX;
        is_found = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i][0] <= current_time && remaining_bt[i] > 0 && remaining_bt[i] < min_bt) {
                min_bt = remaining_bt[i];
                shortest = i;
                is_found = 1;
            }
        }

        if (!is_found) {
            // If no process is available, increment time
            current_time++;
            continue;
        }

        // Execute the shortest process for 1 unit of time
        remaining_bt[shortest]--;
        current_time++;

        // If a process is completed
        if (remaining_bt[shortest] == 0) {
            completed++;
            finish_time = current_time;

            // Calculate turnaround time and waiting time
            arr[shortest][4] = finish_time; // End Time
            arr[shortest][5] = finish_time - arr[shortest][0]; // Turnaround Time (TAT)
            arr[shortest][6] = arr[shortest][5] - arr[shortest][1]; // Waiting Time (WT)
        }
    }
}

void sort(int n) {
    // Sort processes by Arrival Time (AT).
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i][0] > arr[j][0]) {
                for (int k = 0; k < 7; k++) {
                    int temp = arr[i][k];
                    arr[i][k] = arr[j][k];
                    arr[j][k] = temp;
                }
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Initialize the array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 7; j++) {
            arr[i][j] = 0;
        }
    }

    // Input Arrival Time (AT) and Burst Time (BT)
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for process %d: ", i + 1);
        scanf("%d %d", &arr[i][0], &arr[i][1]);
    }

    sort(n);            // Sort by Arrival Time
    SJF_Preemptive(n);  // Apply SJF Preemptive Scheduling

    // Output the results
    printf("AT\tBT\tST\tET\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               arr[i][0], arr[i][1], arr[i][3], arr[i][4], arr[i][5], arr[i][6]);
    }

    // Calculate and display average Waiting Time and Turnaround Time
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += arr[i][6];
        total_turnaround_time += arr[i][5];
    }

    printf("Average Waiting Time = %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_turnaround_time / n);

    return 0;
}
