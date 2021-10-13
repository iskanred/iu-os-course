#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NUMBER_BITS 16

typedef struct PageFrame {
    unsigned int ref;
    unsigned int ageCounter;
} PageFrame;


int main() {
    printf("Enter the number of pages:\n");
    int pageFramesNum; scanf("%d", &pageFramesNum);

    if (pageFramesNum <= 0) {
        printf("Number of pages frame is incorrect\n");
        return EXIT_SUCCESS;
    }

    // open a file with page quieries
    FILE *inputFile = fopen("input.txt", "r");

    // Create an array of pages frames
    PageFrame *pageFrames = (PageFrame*)(malloc(pageFramesNum * sizeof(PageFrame)));
    // Fill page frames array by {'ref' = 0, 'ageCounter' = 0000...00}
    for (int i = 0; i < pageFramesNum; ++i) {
        PageFrame frame = {0, 0};
        pageFrames[i] = frame;
    }

    int hitNum = 0, missNum = 0;
    int curRef; // reference to the page from the just read page query
    
    while(fscanf(inputFile, "%d", &curRef) != EOF) {
        PageFrame *suitPageFrame = &pageFrames[0];
        bool isHit = false;

        /* Shift age counter for each page frame */
        for (int i = 0; i < pageFramesNum; ++i) {
            pageFrames[i].ageCounter >>= 1;
        }
        
        /* Search for sutiable page frame (if hit => with the same reference as current; 
                                            else => with min age counter) */
        for (int i = 0; i < pageFramesNum; ++i) {
             // hit => no need to search for frame with min age counter
            if (pageFrames[i].ref == curRef) {
                suitPageFrame = &pageFrames[i];
                isHit = true;
                break;
            }
            // search for frame with min age counter
            if (pageFrames[i].ageCounter < suitPageFrame->ageCounter) {
                suitPageFrame = &pageFrames[i];
            }
        }

        suitPageFrame->ref = curRef;
        suitPageFrame->ageCounter |= 1 << (NUMBER_BITS);

        if (isHit) ++hitNum;
        else ++missNum;
    }      

    double ratio = (double)(hitNum) / missNum;
    printf("hit: %d, miss: %d, ratio: %f\n", hitNum, missNum, ratio);
    
    return EXIT_SUCCESS;
}