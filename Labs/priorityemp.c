#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct Process {
    int id, priority, at, bt, ct, wt, tat, rt, remaining;
    bool completed;
};

void priority_premp(struct Process processes[], int n) {
    int currentTime = INT32_MAX;

    for (int i = 0; i < n; i++) {
        if (processes[i].at < currentTime) {
            currentTime = processes[i].at;
        }
    }

    int completedProcesses = 0;
    struct Process *currentProcess;
    int maxPriority = INT32_MAX;

    while (completedProcesses < n) {
        currentProcess = NULL; 
        maxPriority = INT32_MAX;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].at <= currentTime && maxPriority >= processes[i].priority) {
                maxPriority = processes[i].priority;
                currentProcess = &processes[i];
            }
        }

        if (currentProcess ==  NULL) {
            currentTime++;
        } else {
            printf("P%d\n",currentProcess->id);
            if (currentProcess->rt == -1) {
                currentProcess->rt == currentTime - currentProcess->at; 
            }

            currentTime++; 

            if (currentProcess->remaining > 0) {
                currentProcess->remaining--;

                if (currentProcess->remaining == 0) {
                    currentProcess->ct = currentTime;
                    currentProcess->tat = currentTime - currentProcess->at;
                    currentProcess->wt = currentProcess->tat - currentProcess->bt;
                    currentProcess->completed = true;
                    completedProcesses++;
                }
            }
        }
    }

    printf("Id\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].at, processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    int arrival, burst, priority;

    for (int i = 0; i < n; i++) {
        printf("Enter the Priority, Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d %d", &priority, &arrival, &burst);
        processes[i].id = i;
        processes[i].priority = priority;
        processes[i].at = arrival;
        processes[i].bt = burst;
        processes[i].ct = 0;
        processes[i].wt = 0;
        processes[i].tat = 0;
        processes[i].rt = -1;
        processes[i].remaining = burst;
        processes[i].completed = false;
    }

    priority_premp(processes, n);

    return 0;
}
