/* First Come First Serve disk scheduling algorithm */

#include <stdio.h>
#include <stdlib.h>

int requests[200];
int i; // counter
int n; // number of disk requests by user
int headMotion = 0;
int headStart = 10;
int n = 10;

int main(int argc, char *argv[])
{
    printf("Enter disk locations to service: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    };

    for (i = 0; i < n; i++)
    {
        printf("Sector %d\n", requests[i]);
        headMotion = headMotion + abs(requests[i] - headStart); // calculate the head's movement between each request
        headStart = requests[i];
    }

    printf("Total Disk Head Movement: %d\n", headMotion);
    return 0;
}