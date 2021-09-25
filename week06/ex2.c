#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Process {
    int num;    // number of process
    int AT;     // arrival time
    int BT;     // burst time
    int CT;     // completion time
    int TAT;    // turnaround time
    int WT;     // waiting time

    bool executed; // (true) - if process is executed, (false) - if not
} Process;


/* Find not yet executed process with min BT among processes which AT is less than or equal to @time
 *  If no such process is found, then return @NULL
 */
Process *findMinBTProcessLessEqualTime(Process *pcs, int size, int time) {
    Process *min = NULL;

    for (int i = 0; i < size; ++i) {
        if (!pcs[i].executed && pcs[i].AT <= time && (min == NULL || pcs[i].BT < min->BT))
            min = &pcs[i];
    }

    return min;
}


void printTable(const Process *pcs, int size) {
    printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
    
    for (int i = 0; i < size; ++i) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pcs[i].num, pcs[i].AT, 
                                            pcs[i].BT, pcs[i].CT, 
                                            pcs[i].TAT, pcs[i].WT);    
    }
    printf("\n");
}



int main() {
    /* ============<INPUT>============ */

    printf("Enter number of processes:\n");
    int n; scanf("%d", &n);
    
    if (n <= 0) {
        printf("Number of processes must be positive\n");
        return EXIT_SUCCESS;
    } 
    
    // array of n processes
    Process *pcs = (Process*) (malloc(sizeof(Process) * n));
    int minAT = -1;

    printf("Enter Arrival time ans Burst time for each process:\n");  

    for (int i = 0; i < n; ++i) {
        pcs[i].num = i + 1;
        printf("Arrival Time of process #[%d]:\t", i + 1);
        scanf("%d", &pcs[i].AT);

        printf("Burst Time of process #[%d]:\t", i + 1);
        scanf("%d", &pcs[i].BT);  

        if (minAT == -1 || pcs[i].AT < minAT)
            minAT = pcs[i].AT;
    }


    /* ============<COMPUTING>============ */
    
    int currentTime = minAT; // the time of processes execution starts from min AT
    double avgTAT = 0.0, avgWT = 0.0;
        
    while (true) { // loop is ended by break below
        // find next process from waiting ones
        Process *currentProcess = findMinBTProcessLessEqualTime(pcs, n, currentTime);
        
        if (currentProcess == NULL) // no such process is found == all processe are executed
            break;
        
        currentProcess->executed = true;
        currentProcess->CT = currentTime + currentProcess->BT;
        currentProcess->TAT = currentProcess->CT - currentProcess->AT;
        currentProcess->WT = currentProcess->TAT - currentProcess->BT;

        avgTAT += currentProcess->TAT;
        avgWT += currentProcess->WT;
        
        currentTime = currentProcess->CT;
    }

    avgTAT /= n;
    avgWT /= n;
    

    /* ============<OUTPUT>============ */
    
    printTable(pcs, n);
    printf("Average Turnaround Time = %f\nAverage Waiting Time = %f\n", avgTAT, avgWT);
    
    return EXIT_SUCCESS;
}
