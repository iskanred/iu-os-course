#include <stdio.h>
#include <stdlib.h>


typedef struct Process {
    int num;    // number of process
    int AT;     // arrival time
    int BT;     // burst time
    int CT;     // completion time
    int TAT;    // turnaround time
    int WT;     // waiting time

    int leftTime;   // left time for completion this process; equal to BT if was not started
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
    
    printf("Enter a quantum:\n");
    int quantum; scanf("%d", &quantum);
    
    if (n <= 0 || quantum <= 0) {
        printf("Both number of processes and quantum must be positive\n");
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
        
        pcs[i].leftTime = pcs[i].BT; // left time = BT if process was not started yet
    }


    /* ============<COMPUTING>============ */

    // sort processes by arrival time
    qsort(pcs, n, sizeof(Process), compare_processes);

    int currentTime = pcs[0].AT; // counting time starts from first process arrival
    int completePcsNum = 0; // number of completed processes

    double avgTAT = 0.0, avgWT = 0.0;


    while (completePcsNum != n) {
        for (int pcIdx = 0; pcIdx < n; ++pcIdx) {
            if (pcs[pcIdx].AT > currentTime) // process is not arrived yet, so next processes are not too
                break;

            if (pcs[pcIdx].leftTime == 0) { // process is completed already
                // if all processes before current are completed (but not all processes in total)
                //  we move to the next process which AT is greater than current time (increase current time)
                if (pcIdx == completePcsNum - 1 && completePcsNum != n)
                    ++currentTime;

                continue;
            }
                

            if (pcs[pcIdx].leftTime < quantum) {
                currentTime += pcs[pcIdx].leftTime;
                pcs[pcIdx].leftTime = 0;
            }
            else { // process leftime >= quantum time
                printf("\n\nHELLO\n\n");
                currentTime += quantum;
                pcs[pcIdx].leftTime -= quantum;  
            } 
            
            printf("Num: %d \t Time: %d\n\n", pcs[pcIdx].num, currentTime);

            if (pcs[pcIdx].leftTime > 0) // process has executed for quantum time slot but not completed
                continue;

            pcs[pcIdx].CT = currentTime; // process is completed at current time

            pcs[pcIdx].TAT = pcs[pcIdx].CT - pcs[pcIdx].AT;
            pcs[pcIdx].WT = pcs[pcIdx].TAT - pcs[pcIdx].BT;

            avgTAT += pcs[pcIdx].TAT;
            avgWT += pcs[pcIdx].WT;


            ++completePcsNum; // current process is completed
        }
    }

    avgTAT /= n;
    avgWT /= n;
    

    /* ============<OUTPUT>============ */
    
    printTable(pcs, n);
    printf("Average Turnaround Time = %f\nAverage Waiting Time = %f\n", avgTAT, avgWT);
    
    return EXIT_SUCCESS;
}




/************************************** ========================================== ***************************************/
/************************************* ==== [OUTPUT COMPARISON AND DESCRIPTION] ==== *************************************/
/************************************** ========================================== ***************************************/
/*
1) -------------------------------------------------------------------
    For the input: =============================================
    Num of process: 10
    P1(0, 1)
    P2(0, 2)
    P3(0, 4)
    P4(0, 6)
    P5(0, 8)
    P6(11, 8)
    P7(11, 6)
    P8(11, 4)
    P9(11, 2)
    P10(11, 1)
    ============================================================
    
    1. FIFO
        Average Turnaround Time = 17.600000
        Average Waiting Time = 13.400000
    2. SJN
        Average Turnaround Time = 12.100000
        Average Waiting Time = 7.900000
    3. Round Robin
        (*) quantum = 1:
        Average Turnaround Time = 21.400000
        Average Waiting Time = 17.200000
        (*) quantum = 2:
        Average Turnaround Time = 19.400000
        Average Waiting Time = 15.200000
        (*) quantum = 3:
        Average Turnaround Time = 20.600000
        Average Waiting Time = 16.400000
            

    We see that SJN algorithm is more effective but difficlut to implement since we need to change a 
        lot of information in runtime and calculate completion time of processes. Therefore, it's often 
        better to use FIFO or Round Robin (and get lucky to choose quantum)

    
*/




