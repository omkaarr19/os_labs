#include <stdio.h>
#include <stdbool.h>

bool search(int key, int fr[], int fr_size)
{
    for (int i = 0; i < fr_size; i++)
    {
        if (fr[i] == key)
        {
            return true;
        }
    }
    return false;
}

int predict(int pg[], int pn, int fr[], int fr_size, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < fr_size; i++)
    {
        int j;
        for (j = index; j < pn; j++)
        {
            if (fr[i] == pg[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == pn)
        {
            return i;
        }
    }
    return (res == -1) ? 0 : res;
}

void printFrames(int fr[], int fr_size)
{
    for (int i = 0; i < fr_size; i++)
    {
        if (fr[i] == -1)
        {
            printf("- ");
        }
        else
        {
            printf("%d ", fr[i]);
        }
    }
}

void optimalPage(int pg[], int pn, int fn)
{
    int fr[fn];
    for (int i = 0; i < fn; i++)
    {
        fr[i] = -1; // Initialize frames with -1
    }
    int hit = 0;
    char result;

    printf("Page String\tFrames\t\tHit/Miss\n");

    for (int i = 0; i < pn; i++)
    {
        printf("%d\t\t", pg[i]);

        if (search(pg[i], fr, fn))
        {
            hit++;
            result = 'H';
        }
        else
        {
            if (fr[fn - 1] == -1)
            {
                fr[fn - 1] = pg[i];
                result = 'M';
            }
            else
            {
                int j = predict(pg, pn, fr, fn, i + 1);
                result = 'M';
                fr[j] = pg[i];
            }
        }

        printFrames(fr, fn);
        printf("\t\t%c\n", result);
    }

    printf("No. of hits = %d\n", hit);
    printf("No. of misses = %d\n", pn - hit);
}

int main()
{
    int pn, fn;

    printf("Enter the number of page references: ");
    scanf("%d", &pn);

    int pg[pn];

    printf("Enter the page reference string: ");
    for (int i = 0; i < pn; i++)
    {
        scanf("%d", &pg[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &fn);

    optimalPage(pg, pn, fn);

    return 0;
}
