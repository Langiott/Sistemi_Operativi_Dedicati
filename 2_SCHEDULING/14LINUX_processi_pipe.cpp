#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
   int ris, fd[2];
   char scritto[2][20]={"Ciao", "Buongiorno"};
   char letto[20];
   ris = pipe(fd);
   if (ris == -1) {
      cerr << "Non sono riuscito a creare la pipe\n";
      return 1;
   }
   pid_t pid = fork();
   if (pid == 0) { // FIGLIO
      read(fd[0], letto, sizeof(letto));
      cout <<"FIGLIO. Leggo dalla pipe – Messaggio 1: "<<letto<<endl;
      read(fd[0], letto, sizeof(letto));
      cout <<"FIGLIO. Leggo dalla pipe – Messaggio 2: "<<letto<<endl;
   } else {          //PADRE
      cout<<"PADRE. Scrivo sulla pipe - Messg 1: "<<scritto[0]<<endl;
      write(fd[1], scritto[0], sizeof(scritto[0]));
      cout<<"PADRE. Scrivo sulla pipe - Messg 2: "<<scritto[1]<<endl;
      write(fd[1], scritto[1], sizeof(scritto[1]));
   }
   return 0;
}
