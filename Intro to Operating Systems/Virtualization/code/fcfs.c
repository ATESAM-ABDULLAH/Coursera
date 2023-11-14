#include <stdio.h>

// Define a structure for a process
struct Process
{
    int processID;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

int main()
{
    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[numProcesses];

    // Gather burst times for each process
    for (int i = 0; i < numProcesses; i++)
    {
        processes[i].processID = i + 1;
        printf("Enter duration for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    // Calculate waiting time and turnaround time using FCFS
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;

    for (int i = 1; i < numProcesses; i++)
    {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
    }

    // Display the results
    printf("Process\tDuration\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < numProcesses; i++)
    {
        if (i == 0)
        {
            processes[i].turnaroundTime = 2;
        }
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    // Calculate average waiting time and average turnaround time
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < numProcesses; i++)
    {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    float avgWaitingTime = totalWaitingTime / numProcesses;
    float avgTurnaroundTime = totalTurnaroundTime / numProcesses;

    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}
