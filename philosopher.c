#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n, h, ch, i, j;
    int p[10];

    printf("Enter the total number of philosophers: ");
    scanf("%d", &n);

    printf("How many are hungry: ");
    scanf("%d", &h);

    for(i = 0; i < h; i++)
    {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, n);
        scanf("%d", &p[i]);
    }

    while(1)
    {
        printf("\n1. One can eat at a time");
        printf("\n2. Two can eat at a time");
        printf("\n3. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:

                printf("\nAllow one philosopher to eat at any time\n");

                for(i = 0; i < h; i++)
                {
                    printf("\nP %d is waiting", p[i]);
                }

                for(i = 0; i < h; i++)
                {
                    printf("\nP %d is granted to eat", p[i]);
                    printf("\nP %d has finished eating\n", p[i]);
                }

                break;

            case 2:

                printf("\nAllow two philosophers to eat at a time\n");

                for(i = 0; i < h; i = i + 2)
                {
                    if(i + 1 < h)
                    {
                        printf("\nP %d and P %d are granted to eat",
                               p[i], p[i + 1]);

                        printf("\nP %d and P %d have finished eating\n",
                               p[i], p[i + 1]);
                    }
                    else
                    {
                        printf("\nP %d is granted to eat", p[i]);
                        printf("\nP %d has finished eating\n", p[i]);
                    }
                }

                break;

            case 3:
                exit(0);

            default:
                printf("\nInvalid choice");
        }
    }

    return 0;
}
