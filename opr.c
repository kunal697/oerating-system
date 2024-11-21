#include <stdio.h>
#include <stdbool.h>

int main() {
    int hit = 0, fault = 0;
    int pagecount;

    // Input for page reference sequence
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

        // If the page is not present, replace using Optimal Algorithm
        if (!ispresent) {
            // If there's an empty frame, use it
            int empty_frame = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    empty_frame = j;
                    break;
                }
            }

            if (empty_frame != -1) {
                // If an empty frame is found, load the current page into it
                frames[empty_frame] = current;
                fault++;
            } else {
                // If no empty frame, find the page that will not be used for the longest time in the future
                int farthest_use = -1, page_to_replace = -1;
                for (int j = 0; j < frameCount; j++) {
                    int next_use = -1;
                    for (int k = i + 1; k < pagecount; k++) {
                        if (frames[j] == pages[k]) {
                            next_use = k;
                            break;
                        }
                    }

                    // If a page does not appear again in the future, it's optimal to replace it
                    if (next_use == -1) {
                        page_to_replace = j;
                        break;
                    }

                    // If the next use of the page is further away in the future, replace it
                    if (next_use > farthest_use) {
                        farthest_use = next_use;
                        page_to_replace = j;
                    }
                }

                // Replace the farthest used page
                frames[page_to_replace] = current;
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

    // Print fault and hit statistics
    printf("Faults: %d\n", fault);
    printf("Hits: %d\n", hit);
    printf("Fault ratio: %.2f\n", (float)fault / pagecount);
    printf("Hit ratio: %.2f\n", (float)hit / pagecount);

    return 0;
}
