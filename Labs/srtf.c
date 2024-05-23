#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int completion;
    int remaining;
    int waiting;
    int turnaround;
    bool completed;
};

void srtf(struct Process processes[], int n) {
    int currenttime = 0;
    struct Process *currentproc = NULL;
    int min_burst;
    int completed_processes = 0;

    while (completed_processes < n) {
        currentproc = NULL;
        int min_burst = INT32_MAX;

        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].remaining > 0 && processes[i].arrival <= currenttime) {
                if (processes[i].remaining < min_burst) {
                    min_burst = processes[i].remaining;
                    currentproc = &processes[i];
                }
            }
        }

        if (currentproc == NULL) {
            printf("Idle(%d -> %d)\n", currenttime, currenttime + 1);
            currenttime++;
        } else {
            currentproc->remaining--;
            currenttime++;
            printf("P%d\n",currentproc->id);

            if (currentproc->remaining == 0) {
                currentproc->completion = currenttime;
                currentproc->turnaround = currentproc->completion - currentproc->arrival;
                currentproc->waiting = currentproc->turnaround - currentproc->burst;
                currentproc->completed = true;
                completed_processes++;
            }
        }
    }

    int avgWT = 0;
    int avgTAT = 0;

    printf("Id\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        avgWT += processes[i].waiting;
        avgTAT += processes[i].turnaround;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].turnaround, processes[i].waiting);
    }

    printf("AverageWT: %f\n", (float)avgWT / n);
    printf("AverageTAT: %f\n", (float)avgTAT / n);
}

int main() {
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));

    int arr, burst;
    for (int i = 0; i < n; i++) {
        printf("Enter process %d arrival time: ", i);
        scanf("%d", &arr);
        printf("Enter process %d burst time: ", i);
        scanf("%d", &burst);
        processes[i].arrival = arr;
        processes[i].burst = burst;
        processes[i].remaining = burst;
        processes[i].id = i;
        processes[i].completed = false;
    }

    srtf(processes, n);

    free(processes);
    return 0;
}
