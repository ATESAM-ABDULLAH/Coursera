/* SCAN disk scheduling algorithm */

#include <stdio.h>
#include <stdlib.h>

int requests[200];
int i;
int j;
int n = 10;

int headMotion = 0;
int headStart = 10;
int size = 200;

int main(int argc, char *argv[])
{

    printf("Enter disk locations to service: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    };

    // SCAN algorithm
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (requests[j] > requests[j + 1])
            {
                int temp;
                temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int index;
    for (i = 0; i < n; i++)
    {
        if (headStart < requests[i])
        {
            index = i;
            break;
        }
    }

    for (i = index - 1; i >= 0; i--)
    {
        printf("Sector %d\n", requests[i]);
        headMotion = headMotion + abs(requests[i] - headStart);
        headStart = requests[i];
    }

    headMotion = headMotion + abs(requests[i + 1] - 0);
    headStart = 0;

    for (i = index; i < n; i++)
    {
        printf("Sector %d\n", requests[i]);
        headMotion = headMotion + abs(requests[i] - headStart);
        headStart = requests[i];
    }

    printf("Total Disk Head Movement: %d\n", headMotion);
    return 0;
}