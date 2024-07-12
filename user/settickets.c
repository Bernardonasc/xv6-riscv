// #include "kernel/syscall.h"
// //#include "kernel/stat.h"
// #include "user/user.h"



// int main(int argc, char *argv[]) {
//   int pid = fork();
//   if(pid == 0) { // Processo filho
//     settickets(20); // Ajusta os tickets para 20
//     while(1) {
//       sleep(100); // Adiciona um pequeno atraso para evitar ocupação excessiva da CPU
//     }
//   } else {
//     // Processo pai
//     printf("Processo filho com PID %d tem 20 tickets\n", pid);
//   }
//   return 0;
// }
