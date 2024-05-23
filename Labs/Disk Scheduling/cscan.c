#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int cscan(int *requests, int n, int initial_Position, char *direction, int track_size)
{
    int total_seek_time = 0;
    int *left = NULL;
    int *right = NULL;
    int flag1 = 0, flag2 = 0; //to know if to add track_size-1 or not  
    int currentPosition = initial_Position;

    // Allocate memory for left and right arrays
    left = (int *)malloc(n * sizeof(int));
    if (left == NULL) {
        printf("Memory allocation failed!\n");
        return -1;
    }
    right = (int *)malloc(n * sizeof(int));
    if (right == NULL) {
        printf("Memory allocation failed!\n");
        free(left); // Free the previously allocated memory
        return -1;
    }

    left[0] = 0;
    right[0] = track_size - 1;

    int left_count = 1, right_count = 1;

    for (int i = 0; i < n; i++)
    {
        if (requests[i] < initial_Position)
        {
            left[left_count++] = requests[i];
        }
        else
        {
            right[right_count++] = requests[i];
        }
    }

    // Sort left and right arrays
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    int run = 2;
    while (run--)
    {
        if (strcmp(direction, "right") == 0)
        {
            for (int i = 0; i < right_count; i++)
            {
                int distance = abs(right[i] - currentPosition);
                total_seek_time += distance;
                currentPosition = right[i];
            }
            strcpy(direction, "left");
            flag1 = 1;
            currentPosition = 0;
        }
        else if (strcmp(direction, "left") == 0)
        {
            for (int i = 0; i < left_count; i++)
            {
                int distance = abs(left[i] - currentPosition);
                total_seek_time += distance;
                currentPosition = left[i];
            }
            strcpy(direction, "right");
            currentPosition = track_size - 1;
            flag2 = 1;
        }
    }

    if (flag1 == 1 && flag2 == 1)
    {
        total_seek_time += track_size - 1;
    }

    free(left); // Free dynamically allocated memory
    free(right);

    return total_seek_time;
}

int main()
{
    int n;
    printf("Enter the number of track requests you want: ");
    scanf("%d", &n);

    int *requests = (int *)malloc(n * sizeof(int));
    if (requests == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter the track requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    int initial_Position;
    printf("Enter the Initial Position of the head: ");
    scanf("%d", &initial_Position);

    char direction[10];
    printf("Enter the direction (left/right): ");
    scanf("%s", direction);

    int track_size;
    printf("Enter the maximum number of tracks: ");
    scanf("%d", &track_size);

    int seekTime = cscan(requests, n, initial_Position, direction, track_size);

    printf("The total seek time is: %d\n", seekTime);

    free(requests);

    return 0;
}
