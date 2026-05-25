#include <stdio.h>

int main()
{
    int frames, n, i, j, k, pageFaults;

    printf("Enter the number of Frames: ");
    scanf("%d", &frames);

    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter the reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    // ---------------- FIFO ----------------
    int fifo[frames];
    for(i = 0; i < frames; i++)
        fifo[i] = -1;

    int index = 0;
    pageFaults = 0;

    printf("\nFIFO Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < frames; j++)
        {
            if(fifo[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            fifo[index] = pages[i];
            index = (index + 1) % frames;
            pageFaults++;

            printf("PF No. %d: ", pageFaults);

            for(k = 0; k < frames; k++)
            {
                if(fifo[k] != -1)
                    printf("%d ", fifo[k]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("FIFO Page Faults: %d\n", pageFaults);

    // ---------------- LRU ----------------
    int lru[frames], recent[frames];

    for(i = 0; i < frames; i++)
    {
        lru[i] = -1;
        recent[i] = 0;
    }

    pageFaults = 0;
    int time = 0;

    printf("\nLRU Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < frames; j++)
        {
            if(lru[j] == pages[i])
            {
                found = 1;
                time++;
                recent[j] = time;
                break;
            }
        }

        if(!found)
        {
            int pos = 0;

            for(j = 1; j < frames; j++)
            {
                if(recent[j] < recent[pos])
                    pos = j;
            }

            lru[pos] = pages[i];
            time++;
            recent[pos] = time;
            pageFaults++;

            printf("PF No. %d: ", pageFaults);

            for(k = 0; k < frames; k++)
            {
                if(lru[k] != -1)
                    printf("%d ", lru[k]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("LRU Page Faults: %d\n", pageFaults);

    int opt[frames];

    for(i = 0; i < frames; i++)
        opt[i] = -1;

    pageFaults = 0;

    printf("\nOptimal Page Replacement Process:\n");

    for(i = 0; i < n; i++)
    {
        int found = 0;

        for(j = 0; j < frames; j++)
        {
            if(opt[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int pos = -1;

            for(j = 0; j < frames; j++)
            {
                if(opt[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
            {
                int farthest = -1;

                for(j = 0; j < frames; j++)
                {
                    int nextUse = 999;

                    for(k = i + 1; k < n; k++)
                    {
                        if(opt[j] == pages[k])
                        {
                            nextUse = k;
                            break;
                        }
                    }

                    if(nextUse > farthest)
                    {
                        farthest = nextUse;
                        pos = j;
                    }
                }
            }

            opt[pos] = pages[i];
            pageFaults++;

            printf("PF No. %d: ", pageFaults);

            for(k = 0; k < frames; k++)
            {
                if(opt[k] != -1)
                    printf("%d ", opt[k]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("Optimal Page Faults: %d\n", pageFaults);

    return 0;
}
