#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct Process {
    int num;    // number of process
    int AT;     // arrival time
    int BT;     // burst time
    int CT;     // completion time
    int TAT;    // turnaround time
    int WT;     // waiting time
} Process;


/* Comparing processes function for qsort */
int compare_processes(const void *a, const void *b) {
    Process p1 = *(Process*)(a);
    Process p2 = *(Process*)(b);

    if (p1.AT < p2.AT || (p1.AT == p2.AT && p1.num < p2.num))
        return -1;
    if (p1.AT > p2.AT || (p1.AT == p2.AT && p1.num > p2.num))
        return 1;
    return 0;
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

    printf("Enter Arrival time ans Burst time for each process:\n");  

    for (int i = 0; i < n; ++i) {
        pcs[i].num = i + 1;
        printf("Arrival Time of process #[%d]:\t", i + 1);
        scanf("%d", &pcs[i].AT);

        printf("Burst Time of process #[%d]:\t", i + 1);
        scanf("%d", &pcs[i].BT);       
    }


    /* ============<COMPUTING>============ */

    // sort processes by arrival time
    qsort(pcs, n, sizeof(Process), compare_processes);
    
    double avgTAT = 0.0, avgWT = 0.0;
    

    // completion time of the first process = AT + BT
    pcs[0].CT = pcs[0].AT + pcs[0].BT;
    
    // computing all properties
    for (int i = 0; i < n; ++i) {
        if (i != 0) { // exclude first process
            int startTime = MAX(pcs[i - 1].CT, pcs[i].AT);
            pcs[i].CT = startTime + pcs[i].BT;
        }
        
        pcs[i].TAT = pcs[i].CT - pcs[i].AT;
        pcs[i].WT = pcs[i].TAT - pcs[i].BT;

        avgTAT += pcs[i].TAT;
        avgWT += pcs[i].WT;
    }

    avgTAT /= n;
    avgWT /= n;
    

    /* ============<OUTPUT>============ */
    
    printTable(pcs, n);
    printf("Average Turnaround Time = %f\nAverage Waiting Time = %f\n", avgTAT, avgWT);
    
    return EXIT_SUCCESS;
}
