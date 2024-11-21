#include <stdio.h>
#include <stdbool.h>

int main() {
    int hit = 0, fault = 0;
    int idx = 0; // Index to track FIFO replacement
    int pagecount;

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
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
    }

    bool ispresent; // To check if a page is in a frame
    for (int i = 0; i < pagecount; i++) {
        printf("Iteration %d: ", i + 1);

        ispresent = false; 
        int current = pages[i];

        // Check if the current page is already in a frame
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == current) {
                hit++;
                ispresent = true;
                break;
            }
        }

        // If the page is not present, replace using FIFO
        if (!ispresent) {
            frames[idx] = current; // Replace the oldest page
            idx = (idx + 1) % frameCount; // Circular increment for FIFO
            fault++;
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
