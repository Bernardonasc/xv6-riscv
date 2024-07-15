#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NUM_PROCESSES 3

void display_process_info() {
    struct pstat process_stats;

    if (getpinfo(&process_stats) != 0) {
        printf("Error: Unable to retrieve process info.\n");
        exit(1);
    }

    for (int i = 0; i < NPROC; i++) {
        
        if (process_stats.inuse[i]) {
            if(process_stats.pid[i] > 3){
                printf("%d\t%d\t%d\n", process_stats.pid[i], process_stats.tickets[i], process_stats.ticks[i]);
            }
        }
    }
}

int main(void) {
    int p[2];
    int tickets[NUM_PROCESSES] = {30, 20, 10};

	for(int i=0 ; i < NUM_PROCESSES ; i++){
        p[i] = fork();
        if(p[i] == 0){
            settickets(tickets[i]);
            while(1);
        }
    }

    printf("PID\tTICKETS\tTICKS\n");
    for (int i = 0; i < 50 ; i++) {
		sleep(10);
		display_process_info();
	}
		
    
    kill(p[1]);
	kill(p[2]);
	kill(p[3]);

    exit(0);
}