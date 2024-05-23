#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int completion;
    int remaining;
    int waiting;
    int turnaround;
    int response;
    bool inreadyQ;
    bool completed;
};

void round_robin(struct Process processes[], int n) {
    struct Process *readyQ[n];
    int front = 0;
    int rear = 0;
    int currenttime = 0;
    int time_quantum;
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);
    int completedproc = 0;
    struct Process *currentprocess = NULL;

    printf("Order of execution: ");
    
    while (completedproc < n) {
        // Check if any process arrives at the current time
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && currenttime >= processes[i].arrival && !processes[i].inreadyQ) {
                readyQ[rear] = &processes[i];
                rear = (rear + 1) % n;
                processes[i].inreadyQ = true;
            }
        }

        // If the ready queue is not empty, proceed with the current process
        if (front != rear) {
            currentprocess = readyQ[front];
            front = (front + 1) % n; // Circular queue

            printf("%d ", currentprocess->id);

            if (currentprocess->response == -1)
                currentprocess->response = currenttime - currentprocess->arrival;

            int time_to_execute = (currentprocess->remaining < time_quantum) ? currentprocess->remaining : time_quantum;
            currenttime += time_to_execute;
            currentprocess->remaining -= time_to_execute;

            // Add newly arrived processes during the execution time to the queue
            for (int i = 0; i < n; i++) {
                if (!processes[i].completed && currenttime >= processes[i].arrival && !processes[i].inreadyQ) {
                    readyQ[rear] = &processes[i];
                    rear = (rear + 1) % n;
                    processes[i].inreadyQ = true;
                }
            }

            if (currentprocess->remaining > 0) {
                readyQ[rear] = currentprocess;
                rear = (rear + 1) % n;
            } else {
                completedproc++;
                currentprocess->completion = currenttime;
                currentprocess->turnaround = currenttime - currentprocess->arrival;
                currentprocess->waiting = currentprocess->turnaround - currentprocess->burst;
                currentprocess->completed = true;
            }
        } else {
            // If the ready queue is empty, increment current time
            currenttime++;
        }
    }

    printf("\nId\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].turnaround, processes[i].waiting, processes[i].response);
    }
}

int main() {
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    int arr, burst;
    for (int i = 0; i < n; i++) {
        printf("Enter arrival and burst for process %d: ", i);
        scanf("%d %d", &arr, &burst);
        processes[i].id = i;
        processes[i].arrival = arr;
        processes[i].burst = burst;
        processes[i].remaining = burst;
        processes[i].waiting = 0;
        processes[i].turnaround = 0;
        processes[i].response = -1;
        processes[i].inreadyQ = false;
        processes[i].completed = false;
    }

    round_robin(processes, n);
    return 0;
}
