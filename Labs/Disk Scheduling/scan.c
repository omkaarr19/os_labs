#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int scan(int *requests, int n, int initial_Position, char *direction, int track_size)
{
    int total_seek_time = 0;
    int current_Position = initial_Position;
    int *left = NULL;
    int *right = NULL;
    int left_count = 0, right_count = 0;

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

    // Append the values to left and right arrays depending on the direction
    if (strcmp(direction, "left") == 0)
        left[left_count++] = 0;
    else if (strcmp(direction, "right") == 0)
        right[right_count++] = track_size - 1;

    for (int i = 0; i < n; i++)
    {
        if (requests[i] < initial_Position)
            left[left_count++] = requests[i];
        else
            right[right_count++] = requests[i];
    }

    // Sort left and right arrays
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    // Run the loop twice
    int run = 2;
    while(run--)
    {
        if (strcmp(direction, "left") == 0)
        {
            for (int i = left_count - 1; i >= 0; i--)
            {
                int distance = abs(left[i] - current_Position);
                total_seek_time += distance;
                current_Position = left[i];
            }
            strcpy(direction, "right");
        }
        else if (strcmp(direction, "right") == 0)
        {
            for (int i = 0; i < right_count; i++)
            {
                int distance = abs(right[i] - current_Position);
                total_seek_time += distance;
                current_Position = right[i];
            }
            strcpy(direction, "left");
        }
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

    int seekTime = scan(requests, n, initial_Position, direction, track_size);

    printf("The total seek time is: %d\n", seekTime);

    free(requests);

    return 0;
}
