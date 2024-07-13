#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    struct pstat st;

    getpinfo(&st);

    printf("NAME\tPID\tSTATUS\t\tCOLOR\tTICKETS\n");

    for (int i = 0; i < NPROC; i++) {
        if (st.inuse[i]) {
            printf("%s\t%d\t", st.name[i], st.pid[i]);
            switch (st.state[i]) {
                case UNUSED: printf("%s",   "UNUSED          "); break;
                case USED: printf("%s",     "USED            "); break;
                case SLEEPING: printf("%s", "SLEEPING        "); break;
                case RUNNABLE: printf("%s", "RUNNABLE        "); break;
                case RUNNING: printf("%s",  "RUNNING         "); break;
                case ZOMBIE: printf("%s",   "ZOMBIE          "); break;
                default: printf("%s",       "UNKNOWN         ");
            }
            switch (st.color[i]) {
                case RED: printf("%s",    "RED     "); break;
                case ORANGE: printf("%s", "ORANGE  "); break;
                case YELLOW: printf("%s", "YELLOW  "); break;
                case GREEN: printf("%s",  "GREEN   "); break;
                case BLUE: printf("%s",   "BLUE    "); break;
                case INDIGO: printf("%s", "INDIGO  "); break;
                case VIOLET: printf("%s", "VIOLET  "); break;
                default: printf("%s",     "UNKNOWN ");
            }

            printf("%d\n", st.tickets[i]);
        }
    }

    return 0;
}