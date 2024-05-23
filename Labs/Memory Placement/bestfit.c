#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Block
{
    int size;
    int allocated;
};

void bestFit(struct Block *memory, int numBlocks, int processSize)
{
    int bestFitIndex = -1;
    int minSize = INT_MAX;

    for (int i = 0; i < numBlocks; ++i)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            if (memory[i].size < minSize)
            {
                minSize = memory[i].size;
                bestFitIndex = i;
            }
        }
    }

    if (bestFitIndex != -1)
    {
        memory[bestFitIndex].allocated = 1;
        printf("Process allocated to Block %d\n", bestFitIndex + 1);
    }
    else
    {
        printf("No suitable block found for the process.\n");
    }
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

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    for (int i = 0; i < numProcesses; ++i)
    {
        int processSize;
        printf("Enter the size of Process %d: ", i + 1);
        scanf("%d", &processSize);
        bestFit(memory, numBlocks, processSize);
    }
    free(memory);

    return 0;
}
