#include <stdio.h>

int arr[100][7]; // 2D array to store process details.

void PriorityScheduling(int n) {
    int completed = 0, current_time = 0, highest_priority, selected;
    int visited[100] = {0}; // Track if a process is completed.

    while (completed < n) {
        highest_priority = 1e9; // Set a high value initially.
        selected = -1;  

        // Find the highest priority process that has arrived and is not completed.
        for (int i = 0; i < n; i++) {
            if (!visited[i] && arr[i][0] <= current_time && arr[i][2] < highest_priority) {
                highest_priority = arr[i][2];
                selected = i;
            }
        }

        if (selected == -1) {
            // If no process has arrived, increment the time.
            current_time++;
            continue;
        }

        // Assign Start Time and End Time
        arr[selected][3] = current_time;               // Start Time
        arr[selected][4] = current_time + arr[selected][1]; // End Time
        current_time = arr[selected][4];              // Update current time.
        visited[selected] = 1;                        // Mark as completed.
        completed++;

        // Calculate Turnaround Time and Waiting Time
        arr[selected][6] = arr[selected][4] - arr[selected][0]; // TAT = ET - AT
        arr[selected][5] = arr[selected][6] - arr[selected][1]; // WT = TAT - BT
    }
}

void sort(int n) {
    // Sort processes by Arrival Time (AT).
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i][0] > arr[j][0]) {
                for (int k = 0; k < 3; k++) { // Swap AT, BT, and Priority
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

    // Input Arrival Time (AT), Burst Time (BT), and Priority
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time, and Priority for process %d: ", i + 1);
        scanf("%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
    }

    sort(n);          // Sort by Arrival Time
    PriorityScheduling(n); // Apply Priority Scheduling

    // Output the results
    printf("AT\tBT\tPriority\tST\tET\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

    // Calculate and display average Waiting Time and Turnaround Time
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += arr[i][5];
        total_turnaround_time += arr[i][6];
    }

    printf("Average Waiting Time = %f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time = %f\n", (float)total_turnaround_time / n);

    return 0;
}
