#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE_BUFFER 50

#define RESOURCES_NUMBER 3
#define PROCCESSES_NUMBER 5

/** pIdx is index of proccess */
bool processCanBeExecuted(int pIdx, int R[PROCCESSES_NUMBER][RESOURCES_NUMBER], int A[RESOURCES_NUMBER]) {
	for (int rIdx = 0; rIdx < RESOURCES_NUMBER; ++rIdx) {
		if (R[pIdx][rIdx] > A[rIdx])
			return false;
	}
	return true;
}

/** pIdx is index of proccess */
void executeProcess(int pIdx, bool finished[PROCCESSES_NUMBER], int C[PROCCESSES_NUMBER][RESOURCES_NUMBER], int A[RESOURCES_NUMBER]) {
	// free the resources that were occupied by this proccess	
	for (int rIdx = 0; rIdx < RESOURCES_NUMBER; ++rIdx) {
		A[rIdx] += C[pIdx][rIdx];
	}
	finished[pIdx] = true;
}

int main() {
	FILE *fp;
    fp = fopen("input.txt", "r");

    if (fp == NULL) {
		perror("Cannot open file \"input.txt\"\n");
        return EXIT_FAILURE;
	}
	
	int E[RESOURCES_NUMBER]; // num of resources
	int A[RESOURCES_NUMBER]; // num of availabe resources
	int C[PROCCESSES_NUMBER][RESOURCES_NUMBER]; // current allocation matrix
	int R[PROCCESSES_NUMBER][RESOURCES_NUMBER]; // request matrix
	
	// read E
	for (int eIdx = 0; eIdx < RESOURCES_NUMBER; ++eIdx) { 
		fscanf(fp, "%d", &E[eIdx]); 
	}
	// read A
	for (int aIdx = 0; aIdx < RESOURCES_NUMBER; ++aIdx) { 
		fscanf(fp, "%d", &A[aIdx]); 
	}
	// read C
	for (int pIdx = 0; pIdx < PROCCESSES_NUMBER; ++pIdx) {
		for (int rIdx = 0; rIdx < RESOURCES_NUMBER; ++rIdx) {
			fscanf(fp, "%d", &C[pIdx][rIdx]);
		}
	}
	// read R
	for (int pIdx = 0; pIdx < PROCCESSES_NUMBER; ++pIdx) {
		for (int rIdx = 0; rIdx < RESOURCES_NUMBER; ++rIdx) {
			fscanf(fp, "%d", &R[pIdx][rIdx]);
		}
	}

	fclose(fp);

	/* ====== Main part of Deadlock detection algorithm ====== */
	bool finished[PROCCESSES_NUMBER]; 
	int finishedProcNum = 0; // number of finished processes
	bool wasDeadlock = false;
	
	// at starting time no proccesses are finished
	for(int pIdx = 0; pIdx < PROCCESSES_NUMBER; ++pIdx) { 
		finished[pIdx] = false;
	}
	
	// manage resources
	while (!wasDeadlock && finishedProcNum != PROCCESSES_NUMBER) {
		wasDeadlock = true; // by default consider deadlock
		for (int pIdx = 0; pIdx < PROCCESSES_NUMBER; ++pIdx) {
			if (!finished[pIdx]) { // consider only not finished processes
				if (processCanBeExecuted(pIdx, R, A)) {
					executeProcess(pIdx, finished, C, A);
					++finishedProcNum;
					wasDeadlock = false; // if any process could executed => no deadlock yet
				}
			}
		}
	}
	
	if (!wasDeadlock) {
		printf("No deadlocks detected\n");
	} else {
		for (int pIdx = 0; pIdx < PROCCESSES_NUMBER; ++pIdx) {
			if (!finished[pIdx])
				printf("Process #%d causes deadlock\n", pIdx + 1);		
		}
	}
	
	return EXIT_SUCCESS;
}
