#include <stdio.h>
#include <stdlib.h>

struct Block
{
    int size;
    int allocated;
};

void firstFit(struct Block *memory, int numBlocks, int processSize)
{
    for (int i = 0; i < numBlocks; i++)
    {
        if (!memory[i].allocated && memory[i].size >= processSize)
        {
            memory[i].allocated = 1;
            printf("Process allocated to Block %d\n", i + 1);
            return;
        }
    }

    printf("No suitable block found for the process\n");
}

int main()
{
    int numBlocks; // number of blocks in main memory
    printf("Enter number of blocks in the memory: ");
    if (scanf("%d", &numBlocks) != 1 || numBlocks <= 0)
    {
        printf("Invalid input. Please enter a positive integer for the number of blocks.\n");
        return 1;
    }

    struct Block *memory = (struct Block *)malloc(numBlocks * sizeof(struct Block));

    for (int i = 0; i < numBlocks; i++)
    {
        printf("Enter size of block %d: ", i + 1);
        if (scanf("%d", &memory[i].size) != 1 || memory[i].size <= 0)
        {
            printf("Invalid input. Please enter a positive integer for the block size.\n");
            free(memory);
            return 1;
        }
        memory[i].allocated = 0;
    }

    int numProcesses;
    printf("Enter the number of processes: ");
    if (scanf("%d", &numProcesses) != 1 || numProcesses <= 0)
    {
        printf("Invalid input. Please enter a positive integer for the number of processes.\n");
        free(memory);
        return 1;
    }

    for (int i = 0; i < numProcesses; i++)
    {
        int processSize;
        printf("Enter the size of Process %d: ", i + 1);
        if (scanf("%d", &processSize) != 1 || processSize <= 0)
        {
            printf("Invalid input. Please enter a positive integer for the process size.\n");
            free(memory);
            return 1;
        }
        firstFit(memory, numBlocks, processSize);
    }

    free(memory);

    return 0;
}
