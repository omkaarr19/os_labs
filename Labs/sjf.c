#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    bool completed;
};

int sjf(struct Process processes[], int n) {
    int currenttime = 0;
    int countComplete = 0;
    struct Process *currentproc = NULL;
    int min_burst;

    while (countComplete < n) {
        min_burst = INT32_MAX;
        for (int j = 0; j < n; j++) {
            if (processes[j].arrival <= currenttime && min_burst > processes[j].burst && !processes[j].completed) {
                min_burst = processes[j].burst;
                currentproc = &processes[j];
            }
        }

        if (currentproc == NULL) {
            currenttime++;
        } else {
            if (currenttime < currentproc->arrival)
                currenttime = currentproc->arrival;

            printf("P%d\n",currentproc->id);
            currenttime += currentproc->burst;
            currentproc->completion = currenttime;
            currentproc->turnaround = currentproc->completion - currentproc->arrival;
            currentproc->waiting = currentproc->turnaround - currentproc->burst;
            currentproc->completed = true;
            countComplete++;
        }
    }

    printf("Id\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].turnaround, processes[i].waiting);
    }
    return 0;
}

int main() {
    int n;
    printf("Enter num of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    int arr, burst;
    for (int i = 0; i < n; i++) {
        printf("Enter process %d arrival time: ", i);
        scanf("%d", &arr);
        printf("Enter process %d burst time: ", i);
        scanf("%d", &burst);
        processes[i].arrival = arr;
        processes[i].burst = burst;
        processes[i].id = i;
        processes[i].completed = false;
    }

    sjf(processes, n);
    return 0;
}
