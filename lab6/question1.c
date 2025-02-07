#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Structure for storing process information
struct Process {
    int id;               // Process ID
    int burstTime;        // Burst Time
    int arrivalTime;      // Arrival Time
    int remainingTime;    // Remaining Time for Preemptive SJF and RR
    int waitingTime;      // Waiting Time
    int turnaroundTime;   // Turnaround Time
    int priority;         // Priority (for Non-Preemptive Priority Scheduling)
};

// Function prototypes
void preemptiveSJF(struct Process proc[], int n);
void roundRobin(struct Process proc[], int n, int quantum);
void priorityScheduling(struct Process proc[], int n);
void calculateWaitingTime(struct Process proc[], int n);
void calculateTurnaroundTime(struct Process proc[], int n);
void displayResults(struct Process proc[], int n);

int main() {
    int choice, n, i, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[MAX];

    // Input process details
    for (i = 0; i < n; i++) {
        proc[i].id = i + 1;  // Process ID starts from 1
        printf("\nEnter details for Process %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &proc[i].burstTime);
        printf("Arrival Time: ");
        scanf("%d", &proc[i].arrivalTime);
        proc[i].remainingTime = proc[i].burstTime; // For Preemptive SJF and RR
    }

    do {
        printf("\nMenu:\n");
        printf("1. Preemptive SJF Scheduling\n");
        printf("2. Round Robin Scheduling\n");
        printf("3. Non-Preemptive Priority Scheduling\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                preemptiveSJF(proc, n);
                break;
            case 2:
                printf("Enter time quantum for Round Robin: ");
                scanf("%d", &quantum);
                roundRobin(proc, n, quantum);
                break;
            case 3:
                priorityScheduling(proc, n);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

// Function to implement Preemptive SJF Scheduling
void preemptiveSJF(struct Process proc[], int n) {
    int completed = 0, currentTime = 0;
    int minRemainingTime, shortestProcess;
    int isProcessCompleted[MAX] = {0};

    printf("\nExecuting Preemptive SJF Scheduling...\n");

    while (completed < n) {
        minRemainingTime = 99999;
        shortestProcess = -1;

        // Find the process with the smallest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (!isProcessCompleted[i] && proc[i].arrivalTime <= currentTime &&
                proc[i].remainingTime < minRemainingTime) {
                minRemainingTime = proc[i].remainingTime;
                shortestProcess = i;
            }
        }

        if (shortestProcess != -1) {
            // Execute the process for 1 unit of time
            proc[shortestProcess].remainingTime--;
            currentTime++;

            // If the process is complete, mark it
            if (proc[shortestProcess].remainingTime == 0) {
                isProcessCompleted[shortestProcess] = 1;
                completed++;
                proc[shortestProcess].turnaroundTime = currentTime - proc[shortestProcess].arrivalTime;
                proc[shortestProcess].waitingTime = proc[shortestProcess].turnaroundTime - proc[shortestProcess].burstTime;
            }
        } else {
            currentTime++;  // If no process is ready to execute, move forward in time
        }
    }

    // Calculate and display results
    calculateTurnaroundTime(proc, n);
    calculateWaitingTime(proc, n);
    displayResults(proc, n);
}

// Function to implement Round Robin Scheduling
void roundRobin(struct Process proc[], int n, int quantum) {
    int completed = 0, currentTime = 0;
    int isProcessCompleted[MAX] = {0};

    printf("\nExecuting Round Robin Scheduling...\n");

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!isProcessCompleted[i] && proc[i].arrivalTime <= currentTime) {
                if (proc[i].remainingTime > quantum) {
                    proc[i].remainingTime -= quantum;
                    currentTime += quantum;
                } else {
                    currentTime += proc[i].remainingTime;
                    proc[i].remainingTime = 0;
                    isProcessCompleted[i] = 1;
                    completed++;
                    proc[i].turnaroundTime = currentTime - proc[i].arrivalTime;
                    proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
                }
            }
        }
    }

    // Calculate and display results
    calculateTurnaroundTime(proc, n);
    calculateWaitingTime(proc, n);
    displayResults(proc, n);
}

// Function to implement Non-Preemptive Priority Scheduling
void priorityScheduling(struct Process proc[], int n) {
    int completed = 0, currentTime = 0;
    int minPriority, highestPriorityProcess;
    int isProcessCompleted[MAX] = {0};

    // Input priority for each process
    for (int i = 0; i < n; i++) {
        printf("\nEnter priority for Process %d: ", proc[i].id);
        scanf("%d", &proc[i].priority);
    }

    printf("\nExecuting Non-Preemptive Priority Scheduling...\n");

    while (completed < n) {
        minPriority = 99999;
        highestPriorityProcess = -1;

        // Find the process with the highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (!isProcessCompleted[i] && proc[i].arrivalTime <= currentTime &&
                proc[i].priority < minPriority) {
                minPriority = proc[i].priority;
                highestPriorityProcess = i;
            }
        }

        if (highestPriorityProcess != -1) {
            // Execute the process
            currentTime += proc[highestPriorityProcess].burstTime;
            isProcessCompleted[highestPriorityProcess] = 1;
            completed++;
            proc[highestPriorityProcess].turnaroundTime = currentTime - proc[highestPriorityProcess].arrivalTime;
            proc[highestPriorityProcess].waitingTime = proc[highestPriorityProcess].turnaroundTime - proc[highestPriorityProcess].burstTime;
        } else {
            currentTime++;  // If no process is ready to execute, move forward in time
        }
    }

    // Calculate and display results
    calculateTurnaroundTime(proc, n);
    calculateWaitingTime(proc, n);
    displayResults(proc, n);
}

// Function to calculate Waiting Time
void calculateWaitingTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
    }
}

// Function to calculate Turnaround Time
void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaroundTime = proc[i].waitingTime + proc[i].burstTime;
    }
}

// Function to display the results
void displayResults(struct Process proc[], int n) {
    printf("\nProcess ID | Burst Time | Arrival Time | Waiting Time | Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%9d | %10d | %12d | %12d | %15d\n",
               proc[i].id, proc[i].burstTime, proc[i].arrivalTime,
               proc[i].waitingTime, proc[i].turnaroundTime);
    }

    // Calculate and display average waiting time and turnaround time
    int totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += proc[i].waitingTime;
        totalTAT += proc[i].turnaroundTime;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWT / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTAT / n);
}

