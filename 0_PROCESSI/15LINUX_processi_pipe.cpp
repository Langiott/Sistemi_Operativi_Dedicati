#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
   int ris1, ris2, fd1[2], fd2[2]; // due PIPES
   char pipe1scritto[20] = "Ciao";
   char pipe2scritto[20] = "Buongiorno";
   char letto[20];
   ris1 = pipe(fd1);
   if (ris1 == -1) {
      cerr << "Non sono riuscito a creare la pipe 1\n";
      return 1;
   }
   ris2 = pipe(fd2);
   if (ris2 == -1) {
      cerr << "Non sono riuscito a creare la pipe 2\n";
      return 1;
   }
   pid_t pid = fork();
   if (pid != 0) { // PADRE
      close(fd1[0]); // Chiude la pipe1 lato lettura
      close(fd2[1]); // Chiude la pipe2 lato scrittura
      cout << "PADRE. Scrivo sulla pipe 1: " << pipe1scritto << endl;
      write(fd1[1], pipe1scritto, sizeof(pipe1scritto));
      read(fd2[0], letto, sizeof(letto));
      cout << "PADRE. Leggo dalla pipe 2: " << letto << endl;
   } else { // FIGLIO
      close(fd1[1]); // Chiude la pipe1 lato scrittura
      close(fd2[0]); // Chiude la pipe2 lato lettura
      read(fd1[0], letto, sizeof(letto));
      cout << "FIGLIO. Leggo dalla pipe 1: " << letto << endl;
      cout << "FIGLIO. Scrivo sulla pipe 2: " << pipe2scritto << endl;
      write(fd2[1], pipe2scritto, sizeof(pipe2scritto));
   }
   return 0;
}

   
