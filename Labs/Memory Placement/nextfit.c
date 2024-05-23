#include <stdio.h>
#include <stdlib.h>

struct Block
{
    int size;
    int allocated;
};

void nextFit(struct Block *memory, int numBlocks, int processSize, int *lastAllocated)
{
    int startIndex = *lastAllocated;

    do
    {
        if (!memory[startIndex].allocated && memory[startIndex].size >= processSize)
        {
            memory[startIndex].allocated = 1;
            printf("Process allocated to Block %d\n", startIndex + 1);
            *lastAllocated = (startIndex + 1) % numBlocks;
            return;
        }

        startIndex = (startIndex + 1) % numBlocks;
    } while (startIndex != *lastAllocated);
    printf("No suitable block found for the process.\n");
}

int main()
{
    int numBlocks;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    struct Block *memory = (struct Block *)malloc(numBlocks * sizeof(struct Block));

    for (int i = 0; i < numBlocks; ++i)
    {
        printf("Enter the size of Block %d: ", i + 1);
        scanf("%d", &memory[i].size);
        memory[i].allocated = 0;
    }

    int numProcesses;
    int lastAllocated = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    for (int i = 0; i < numProcesses; ++i)
    {
        int processSize;
        printf("Enter the size of Process %d: ", i + 1);
        scanf("%d", &processSize);
        nextFit(memory, numBlocks, processSize, &lastAllocated);
    }

    free(memory);

    return 0;
}
