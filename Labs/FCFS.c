#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int arrivaltime;
    int bursttime;
    int completiontime;
    int turnaroundtime;
    int waitingtime;
    int completed;
};

void fcfs(struct Process processes[], int n) {
    int currenttime = 0;
    for (int i = 0; i < n; i++) {
        struct Process *currentProc = &processes[i];
        for (int j = 0; j < n; j++) {
            if (processes[j].arrivaltime <= currenttime && !processes[j].completed && currentProc->arrivaltime > processes[j].arrivaltime) {
                currentProc = &processes[j];
            }
        }
        if (currenttime < currentProc->arrivaltime)
            currenttime = currentProc->arrivaltime;

        currenttime += currentProc->bursttime;
        currentProc->completiontime = currenttime;
        currentProc->turnaroundtime = currenttime - currentProc->arrivaltime;
        currentProc->waitingtime = currentProc->turnaroundtime - currentProc->bursttime;
        currentProc->completed = 1;

        printf("Process id: %d\n", currentProc->id);
        printf("Process arr: %d\n", currentProc->arrivaltime);
        printf("Process burst: %d\n", currentProc->bursttime);
        printf("Process completion: %d\n", currentProc->completiontime);
        printf("Process turnaround: %d\n", currentProc->turnaroundtime);
        printf("Process waiting: %d\n\n", currentProc->waitingtime);
    }
}

int main() {
    int n;
    float AverageWT = 0;
    float AverageTAT = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));

    printf("Enter arrival times and burst times for each process:\n");
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &processes[i].arrivaltime);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &processes[i].bursttime);
        processes[i].completed = 0;
    }
    // Perform FCFS scheduling
    fcfs(processes, n);

    // Display the scheduling results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        AverageWT += processes[i].waitingtime;
        AverageTAT += processes[i].turnaroundtime;

        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivaltime, processes[i].bursttime,
               processes[i].completiontime, processes[i].turnaroundtime, processes[i].waitingtime);
    }

    printf("\nAverage Waiting Time is %f\n", AverageWT / n);
    printf("Average Turnaround Time is %f\n", AverageTAT / n);

    free(processes);
    return 0;
}
