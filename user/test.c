#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NUM_PROCESSES 11

void display_process_info() {
    struct pstat process_stats;

    if (getpinfo(&process_stats) != 0) {
        printf("Error: Unable to retrieve process info.\n");
        exit(1);
    }

    printf("NAME\tPID\tTICKETS\tTICKS\n");
    for (int i = 0; i < NPROC; i++) {
        if (process_stats.inuse[i]) {
            printf("%s\t%d\t%d\t%d\n", process_stats.name[i], process_stats.pid[i], process_stats.tickets[i], process_stats.ticks[i]);
        }
    }
}

int main(void) {
    int pids[NUM_PROCESSES];
    int tickets[NUM_PROCESSES] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 256};

    for (int i = 0; i < NUM_PROCESSES; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            setTickets(tickets[i]);
            while(1);
            exit(0);
        } else if (pids[i] < 0) {
            printf("Error: Fork failed for process %d\n", i);
            exit(1);
        }
    }

    sleep(300);

    display_process_info();
    
    for (int i = 0; i < NUM_PROCESSES; i++) {
        kill(pids[i]);
    }

    exit(0);
}
