#include <stdio.h>
#define MAX_PROCESSES 50

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
    struct Process processes[MAX_PROCESSES];
    int front, rear;
    int timeQuantum;
};

void initializeQueues(struct Queue queues[], int numQueues)
{
    int times[] = {2, 4, 8}; // High, Medium, Low
    for (int i = 0; i < numQueues; i++)
    {
        queues[i].front = -1;
        queues[i].rear = -1;
        queues[i].timeQuantum = times[i];
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
    printf("Process %d enqueued in queue with time quantum %d\n", process.processID, queue->timeQuantum);
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
    printf("Process %d dequeued from queue with time quantum %d\n", process.processID, queue->timeQuantum);
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

    for (int i = 0; i < numProcesses; i++)
    {
        processes[i].processID = i + 1;
        printf("Enter duration for process %d: ", i + 1);
        scanf("%d", &processes[i].duration);
        processes[i].remainingTime = processes[i].duration;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        enqueue(&queues[0], processes[i]); // Enqueue in the high-priority queue initially
    }

    int time = 0;

    for (int j = 0; j < 3; j++)
    {
        // Inside the while loop where processes are being executed
        while (queues[j].front != -1)
        {
            struct Process runningProcess = dequeue(&queues[j]);

            printf("Process %d is running in %s priority queue\n", runningProcess.processID, (j == 0) ? "high" : (j == 1) ? "medium"
                                                                                                                          : "low");

            int timeElapsed = (runningProcess.remainingTime > queues[j].timeQuantum) ? queues[j].timeQuantum : runningProcess.remainingTime;
            runningProcess.remainingTime -= timeElapsed;

            if (runningProcess.waitingTime == -1)
                runningProcess.waitingTime = time;

            // printf("time: %ds, run: %ds, rem: %ds\n", time, timeElapsed, runningProcess.remainingTime);

            time += timeElapsed;

            // Update waiting and turnaround times
            for (int k = 0; k < numProcesses; k++)
            {
                if (processes[k].processID == runningProcess.processID)
                {
                    processes[k].remainingTime = runningProcess.remainingTime;

                    if (runningProcess.remainingTime <= 0)
                    {
                        processes[k].turnaroundTime = time;
                        processes[k].waitingTime = time - processes[k].duration;
                    }
                    break;
                }
            }

            if (runningProcess.remainingTime <= 0)
            {
                printf("Process %d finished execution\n", runningProcess.processID);
            }
            else
            {
                if (j == 2) // stop decreasing priority after lowest
                {
                    enqueue(&queues[j], runningProcess);
                    continue;
                }
                enqueue(&queues[j + 1], runningProcess);
            }
        }
    }

    printf("Process\tDuration\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < numProcesses; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].duration, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    return 0;
}