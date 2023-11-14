#include <stdio.h>

struct Process {
    int processID;
    int duration;
    int waitingTime;
    int turnaroundTime;
};

void sortProcesses(struct Process processes[], int numProcesses) {
    // Simple sorting algorithm (Bubble Sort) based on process duration
    for (int i = 0; i < numProcesses - 1; i++) {
        for (int j = 0; j < numProcesses - i - 1; j++) {
            if (processes[j].duration > processes[j + 1].duration) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[numProcesses];

    for (int i = 0; i < numProcesses; i++) {
        processes[i].processID = i + 1;
        printf("Enter execution time for process %d: ", i + 1);
        scanf("%d", &processes[i].duration);
    }

    // Sort processes by duration
    sortProcesses(processes, numProcesses);

    // Calculate waiting time and turnaround time
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].duration;

    for (int i = 1; i < numProcesses; i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].duration;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].duration;
    }

    // Display the results
    printf("Process\tExecution Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].duration, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    // Calculate average waiting time and average turnaround time
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < numProcesses; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    float avgWaitingTime = totalWaitingTime / numProcesses;
    float avgTurnaroundTime = totalTurnaroundTime / numProcesses;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}
