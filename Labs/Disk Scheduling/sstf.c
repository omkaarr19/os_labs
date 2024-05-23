#include <stdio.h>
#include <stdlib.h>

int find_closest_request(int *requests, int n, int current_Position)
{
    int min_Distance = 999;
    int closest_Request = -1;

    for (int i = 0; i < n; i++)
    {
        int seek_Distance = abs(requests[i] - current_Position);
        if (seek_Distance < min_Distance)
        {
            min_Distance = seek_Distance;
            closest_Request = requests[i];
        }
    }

    return closest_Request;
}

int sstf(int *requests, int n, int initial_Position)
{
    int total_seek_time = 0;
    int current_Position = initial_Position;

    while(n > 0)
    {
        int closest_Request = find_closest_request(requests, n, current_Position);
        int seek_distance = abs(closest_Request - current_Position);
        total_seek_time += seek_distance;
        current_Position = closest_Request;

        // Remove the processed request from the array
        for (int i = 0; i < n; i++) {
            if (requests[i] == closest_Request) {
                // Shift elements to left to overwrite the processed request
                for (int j = i; j < n - 1; j++) {
                    requests[j] = requests[j + 1];
                }
                n--; // Decrement the count of requests
                break; // Exit the loop once the request is found and removed
            }
        }
    }

    return total_seek_time;
}

int main()
{
    int n;
    printf("Enter the number of requests you want in the Request Queue: ");
    scanf("%d", &n);

    int *requests = (int *)malloc(n * sizeof(int));
    if (requests == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int initial_Position;
    printf("Enter Initial Position: ");
    scanf("%d", &initial_Position);

    int seekTime = sstf(requests, n, initial_Position);
    printf("The Total Seek Time is %d\n", seekTime);

    free(requests); 

    return 0;
}
