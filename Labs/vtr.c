#include <stdio.h>
#include <math.h>

#define PAGE_SIZE 4096

int logicalToPhysical(int logicalAddress, int pageTable[], int pageTableSize, int pageSize)
{
    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;
    if (pageNumber >= 0 && pageNumber < pageTableSize && pageTable[pageNumber] != -1)
    {
        int frameNumber = pageTable[pageNumber];
        int physicalAddress = frameNumber * pageSize + offset;
        return physicalAddress;
    }
    else
    {
        printf("Page fault: Page %d not in memory.\n", pageNumber);
        return -1;
    }
}

int main()
{
    int pageTable[] = {1, 0, -1, 2};
    int pageTableSize = sizeof(pageTable) / sizeof(pageTable[0]);
    int logicalAddress;
    printf("Enter a logical address: ");
    scanf("%d", &logicalAddress);
    int physicalAddress = logicalToPhysical(logicalAddress, pageTable, pageTableSize, PAGE_SIZE);
    if (physicalAddress != -1)
    {
        printf("Physical Address: %d\n", physicalAddress);
    }

    return 0;
}
