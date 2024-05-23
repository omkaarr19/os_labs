#include <stdio.h>
#include <stdbool.h>

#define MAX_M 100 // Define a maximum size for the second dimension of arrays

void displayTable(int n, int m, int allocation[n][m], int maximum[n][m], int need[n][m])
{
    printf("\nProcess ID\tAllocated\tMaximum\t\tNeeded\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t", i);
        for (int j = 0; j < m; j++)
        {
            printf("%d ", allocation[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < m; j++)
        {
            printf("%d ", maximum[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

bool isSafe(int available[], int maximum[][MAX_M], int allocation[][MAX_M], int n, int m)
{
    int need[n][m];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    bool finish[n];
    int safeSequence[n];
    int work[m];

    for (int i = 0; i < n; i++)
    {
        finish[i] = false;
        safeSequence[i] = -1;
    }

    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate)
                {
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count] = i;
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }

        if (!found)
        {
            return false;
        }
    }

    displayTable(n, m, allocation, maximum, need);
    printf("\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d", safeSequence[i]);
        if (i != n - 1)
        {
            printf(" -> ");
        }
    }
    printf("\n");
    return true;
}

int main()
{
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int total[m];
    int available[m];
    int maximum[n][MAX_M];
    int allocation[n][MAX_M];

    printf("Enter the total number of each resource: ");
    for (int i = 0; i < m; i++)
    {
        printf("\nEnter the total count of resource %d: ", i + 1);
        scanf("%d", &total[i]);
    }

    printf("Enter current allocation for each process: \n\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter the resources allocated for process %d: ", i + 1);
        for (int j = 0; j < m; j++)
        {
            printf("R%d: ", j + 1);
            scanf("%d", &allocation[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < m; i++)
    {
        available[i] = 0;
        for (int j = 0; j < n; j++)
        {
            available[i] += allocation[j][i];
        }
        available[i] = total[i] - available[i];
    }

    printf("Enter maximum demand for each process: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &maximum[i][j]);
        }
    }

    if (isSafe(available, maximum, allocation, n, m))
    {
        printf("The system is in a safe state.\n");
    }
    else
    {
        printf("The system is in an unsafe state.\n");
    }

    return 0;
}
