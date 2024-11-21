#include <stdio.h>
#include <stdbool.h>

int main() {
    int hit = 0, fault = 0;
    int pagecount;

    // Input for page sequence
    printf("Enter number of pages: ");
    scanf("%d", &pagecount);

    int pages[pagecount];
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < pagecount; i++) {
        scanf("%d", &pages[i]);
    }

    int frameCount;
    printf("Enter the size of the frame holder: ");
    scanf("%d", &frameCount);

    int frames[frameCount]; // Array to represent frames
    int time[frameCount]; // Array to track the last access time of pages in frames
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
        time[i] = -1;   // Initialize time array
    }

    bool ispresent; // To check if a page is in a frame
    for (int i = 0; i < pagecount; i++) {
        printf("Iteration %d: ", i + 1);

        ispresent = false;
        int current = pages[i];
        int lru_index = -1, min_time = i + 1; // Track the least recently used page

        // Check if the current page is already in a frame
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == current) {
                hit++;
                time[j] = i; // Update the last access time for the current page
                ispresent = true;
                break;
            }
        }

        // If the page is not present, replace using LRU
        if (!ispresent) {
            // Find the least recently used page (the one with the minimum time value)
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    // If there's an empty frame, use it
                    frames[j] = current;
                    time[j] = i;
                    fault++;
                    ispresent = true;
                    break;
                } else if (time[j] < min_time) {
                    min_time = time[j];
                    lru_index = j;
                }
            }

            // Replace the LRU page
            if (!ispresent) {
                frames[lru_index] = current;
                time[lru_index] = i;
                fault++;
            }
        }

        // Print the current state of the frame
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]); // Print valid pages
            } else {
                printf("- "); // Print empty slots as '-'
            }
        }
        printf("\n");
    }

    printf("Faults: %d\n", fault);
    printf("Hits: %d\n", hit);
    printf("Fault ratio: %.2f\n", (float)fault / pagecount);
    printf("Hit ratio: %.2f\n", (float)hit / pagecount);

    return 0;
}
