#include <stdio.h>

struct Process
{
    int processID;
    int duration;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

struct Queue
{
    struct Process processes[50];
    int front, rear;
    int timeQuantum;
};

void initializeQueues(struct Queue queues[], int numQueues)
{
    int timeQuantum = 2;
    for (int i = 0; i < numQueues; i++)
    {
        queues[i].front = -1;
        queues[i].rear = -1;
        queues[i].timeQuantum = timeQuantum;
        timeQuantum += timeQuantum; // Modifying for demonstration
    }
}

void enqueue(struct Queue *queue, struct Process process)
{
    if (queue->front == -1)
    {
        queue->front = 0;
    }
    queue->rear++;
    queue->processes[queue->rear] = process;
}

struct Process dequeue(struct Queue *queue)
{
    struct Process process = queue->processes[queue->front];
    if (queue->front == queue->rear)
    {
        queue->front = -1;
        queue->rear = -1;
    }
    else
    {
        queue->front++;
    }
    return process;
}

int main()
{
    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[numProcesses];
    struct Queue queues[3];

    initializeQueues(queues, 3);

    printf("Enter the duration for each process:\n");
    for (int i = 0; i < numProcesses; i++)
    {
        processes[i].processID = i + 1;
        printf("Duration for process %d: ", i + 1);
        scanf("%d", &processes[i].duration);
        processes[i].remainingTime = processes[i].duration;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        enqueue(&queues[0], processes[i]); // Enqueue in the high-priority queue initially
    }

    printf("\n");

    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            while (queues[j].front != -1)
            {
                struct Process runningProcess = dequeue(&queues[j]);
                printf("Process %d is running in %s priority queue\n", runningProcess.processID, (j == 0) ? "high" : (j == 1) ? "medium"
                                                                                                                              : "low");

                if (runningProcess.remainingTime <= queues[j].timeQuantum)
                {
                    // runningProcess.waitingTime += ; // Modifying for demonstration
                    runningProcess.turnaroundTime = runningProcess.waitingTime + runningProcess.duration;
                    printf("Process %d finished execution\n", runningProcess.processID);
                }
                else
                {
                    runningProcess.remainingTime -= queues[j].timeQuantum;
                    printf("Process %d is rescheduled with %d remaining time\n", runningProcess.processID, runningProcess.remainingTime);
                    enqueue(&queues[j + 1], runningProcess);
                }
            }
        }
    }

    printf("\nProcess Duration\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < numProcesses; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].duration, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < numProcesses; i++)
    {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    float avgWaitingTime = totalWaitingTime / numProcesses;
    float avgTurnaroundTime = totalTurnaroundTime / numProcesses;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}
