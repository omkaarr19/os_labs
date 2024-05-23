#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct Process {
    int id;
    int priority;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;
    int response;
    bool completed;
};

void priority_np(struct Process processes[], int n) {
    int currenttime = 0;
    int completed_processes = 0;
    int max_priority;
    struct Process *currproc = NULL;

    while (completed_processes < n) {
        max_priority = INT32_MAX;
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && max_priority > processes[i].priority && processes[i].arrival <= currenttime) {
                max_priority = processes[i].priority;
                currproc = &processes[i];
            }
        }

        if (currproc == NULL) {
            currenttime++;
        } else {
            if (currproc->response == -1)
                currproc->response = currenttime;

            currenttime += currproc->burst;
            currproc->completion = currenttime;
            currproc->turnaround = currenttime - currproc->arrival;
            currproc->waiting = currproc->turnaround - currproc->burst;
            currproc->completed = true;
            completed_processes++;
        }
    }

    printf("Id\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].burst, processes[i].completion,
               processes[i].turnaround, processes[i].waiting);
    }
}

int main() {
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    int arr, burst, priority;
    for (int i = 0; i < n; i++) {
        printf("Enter arrival, burst, and priority for process %d: ", i);
        scanf("%d %d %d", &arr, &burst, &priority);
        processes[i].id = i;
        processes[i].arrival = arr;
        processes[i].burst = burst;
        processes[i].priority = priority;
        processes[i].completion = 0;
        processes[i].waiting = 0;
        processes[i].turnaround = 0;
        processes[i].response = -1;
        processes[i].completed = false;
    }

    priority_np(processes, n);
}
