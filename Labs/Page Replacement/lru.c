#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

void displayCacheHeader()
{
    printf("Cache\tHit/Miss\n");
}

void displayCache(int s[], int n, int page, bool isHit, bool displayHeader)
{
    if (displayHeader)
    {
        displayCacheHeader();
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d\t", s[i]);
        if (s[i] == page && isHit)
        {
            printf("Hit");
        }
        else
        {
            printf("Miss");
        }
        printf("\n");
    }
    printf("\n");
}

int pageFaults(int pages[], int n, int capacity)
{
    int s[capacity];
    int indexes[1000] = {0}; // Assuming a maximum page index of 1000
    int page_faults = 0;

    bool displayHeader = true;

    for (int i = 0; i < n; i++)
    {
        printf("Page %d - \n", pages[i]);

        bool isHit = false;
        for (int j = 0; j < capacity; j++)
        {
            if (s[j] == pages[i])
            {
                isHit = true;
                break;
            }
        }

        if (!isHit)
        {
            if (page_faults == capacity)
            {
                int lru = INT_MAX, val;
                for (int j = 0; j < capacity; j++)
                {
                    if (indexes[s[j]] < lru)
                    {
                        lru = indexes[s[j]];
                        val = s[j];
                    }
                }
                for (int j = 0; j < capacity; j++)
                {
                    if (s[j] == val)
                    {
                        s[j] = pages[i];
                        break;
                    }
                }
            }
            else
            {
                s[page_faults] = pages[i];
            }
            page_faults++;
        }
        displayCache(s, capacity, pages[i], isHit, displayHeader);
        displayHeader = false;
        indexes[pages[i]] = i;
    }

    return page_faults;
}

int main()
{
    int n;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter the page references:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    int capacity;
    printf("Enter the capacity of the cache: ");
    scanf("%d", &capacity);

    printf("Page Faults: %d\n", pageFaults(pages, n, capacity));

    return 0;
}
