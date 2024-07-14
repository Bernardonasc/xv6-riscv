#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void print_ticks() {
    struct pstat st;

    if (getpinfo(&st) != 0) {
        printf("getpinfo failed\n");
        exit(1);
    }

    printf("NAME\tPID\tTICKETS\tTICKS\n");
    for (int i = 0; i < NPROC; i++) {
        if (st.inuse[i]) {
            printf("%s\t%d\t%d\t%d\n", st.name[i], st.pid[i], st.tickets[i], st.ticks[i]);
        }
    }
}

int main(void) {
    int pid[11] = {0};
    int tickets[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 256};
    for (int i = 0; i <11; i++) {
        pid[i] = fork();
        if (pid[i] == 0) {
            setTickets(tickets[i]);
            while(5);
            printf("done\n");
            exit(0);
        }
    }

    sleep(300);

    print_ticks();
    
    for (int i = 0; i < 11; i++) {
        kill(pid[i]);
    }

    exit(0);
}