#include<stdio.h>
#include<stdlib.h>

int mutex = 1;
int full = 0;
int empty = 3, x = 0;
int item[3];
int top=-1;
int value =5;
void wait()
{
    mutex--;
}

void signal()
{
    mutex++;
}

void producer()
{
    wait();
    full++;
    empty--;
    x++;

    printf("Producer has produced: Item %d\n", x);

    signal();
}

void consumer()
{
    wait();
    full--;
    empty++;

    printf("Consumer has consumed: Item %d\n", x);

    x--;

    signal();
}

int main()
{
    int n;

    printf("\n1.Producer\n2.Consumer\n3.Exit");

    while(1)
    {
        printf("\nEnter your choice:\n");
        scanf("%d", &n);

        switch(n)
        {
            case 1:
                if((mutex == 1) && (empty != 0))
                {
                    producer();
                }
                else
                {
                    printf("Buffer is full!");
                }
                break;

            case 2:
                if((mutex == 1) && (full != 0))
                {
                    consumer();
                }
                else
                {
                    printf("Buffer is empty!");
                }
                break;

            case 3:
                exit(0);
                break;

            default:
                printf("Invalid choice!");
        }
    }

    return 0;
}
