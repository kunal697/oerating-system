#include <stdio.h>

int arr[100][6]; // 2D array to store process details.

void SJF(int n) {
    int completed = 0, current_time = 0, min_bt, shortest;
    int visited[100] = {0}; // Track if a process is completed.

    while (completed < n) {
        min_bt = 1e9; // Set a high value initially.
        shortest = -1;

        // Find the shortest process that has arrived and is not completed.
        for (int i = 0; i < n; i++) {
            if (!visited[i] && arr[i][0] <= current_time && arr[i][1] < min_bt) {
                min_bt = arr[i][1];
                shortest = i;
            }
        }

        if (shortest == -1) {
            // If no process has arrived, increment the time.
            current_time++;
            continue;
        }

        // Assign Start Time and End Time
        arr[shortest][2] = current_time;               // Start Time
        arr[shortest][3] = current_time + arr[shortest][1]; // End Time
        current_time = arr[shortest][3];              // Update current time.
        visited[shortest] = 1;                        // Mark as completed.
        completed++;

        // Calculate Turnaround Time and Waiting Time
        arr[shortest][5] = arr[shortest][3] - arr[shortest][0]; // TAT = ET - AT
        arr[shortest][4] = arr[shortest][5] - arr[shortest][1]; // WT = TAT - BT
    }
}

void sort(int n) {
    // Sort processes by Arrival Time (AT).
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i][0] > arr[j][0]) {
                for (int k = 0; k < 2; k++) {
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
        for (int j = 0; j < 6; j++) {
            arr[i][j] = 0;
        }
    }

    // Input Arrival Time (AT) and Burst Time (BT)
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for process %d: ", i + 1);
        for (int j = 0; j < 2; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    sort(n);  // Sort by Arrival Time
    SJF(n);   // Apply SJF scheduling

    // Output the results
    printf("AT\tBT\tST\tET\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

    // Calculate and display average Waiting Time and Turnaround Time
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += arr[i][4];
        total_turnaround_time += arr[i][5];
    }

    printf("Average Waiting Time = %f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time = %f\n", (float)total_turnaround_time / n);

    return 0;
}
