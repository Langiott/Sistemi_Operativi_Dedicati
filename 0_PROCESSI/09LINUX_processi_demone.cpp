#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
using namespace std;
int main(int argc, char *argv[]) {
  pid_t pid;
  int cont, fd, max_iter;
  char buffer[100];
  if (argc < 2) max_iter = 5;
  else {
    max_iter = atoi(argv[1]);
    if ((max_iter <= 0) || (max_iter > 20)) max_iter = 10;
  }
  switch(pid = fork()) {          // genera il nuovo processo
    case -1: // errore nella generazione del nuovo processo
      cerr << "generazione del nuovo processo fallita\n";
      exit(-1);
      break;
    case 0:                              // processo figlio
      fd = open("/tmp/demone.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
      if (fd == -1) {
        cerr << "apertura del file demone.txt fallita\n";
        return 1;}
      cout << "Figlio: pid " <<getpid()<<" ppid "<<getppid()<<endl;
      cout << "\nFiglio prima di diventare session leader\n";
      sprintf(buffer, "ps -ef|grep %s", argv[0]);
      system(buffer);
      setsid();
      cout << "\nFiglio dopo essere diventato session leader\n";
      sprintf(buffer, "ps -ef|grep %s", argv[0]);
      system(buffer);
      close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);
      break;
    default:   // padre
      cout << "Padre: pid " <<getpid()<<" ppid "<<getppid()<<endl;
      cout << "Padre: Esco\n";
      exit(0);
  }
  for (cont = 0; cont < max_iter; cont++) { // esegue maxiter volte
    sprintf(buffer,"demone: pid %d ppid %d\n",getpid(),getppid());
    write(fd, buffer, strlen(buffer));
    sleep(2);
  }
  strcpy(buffer, "Fatto!\n");
  write(fd, buffer, strlen(buffer));
  printf("Ho finito\n"); // non si stampa perché STDOUT chiuso
  close(fd);
  return 0;
}
