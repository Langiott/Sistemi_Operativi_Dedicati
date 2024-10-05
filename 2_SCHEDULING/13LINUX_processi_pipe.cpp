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
   cout << "Scrivo sulla pipe - Messaggio 1: " <<  scritto[0] << endl;
   write(fd[1], scritto[0], sizeof(scritto[0]));
   read(fd[0], letto, sizeof(letto));
   cout << "Leggo dalla pipe – Messaggio 1: " << letto << endl;
   cout << "Scrivo sulla pipe - Messaggio 2: " <<  scritto[1] << endl;
   write(fd[1], scritto[1], sizeof(scritto[1]));
   read(fd[0], letto, sizeof(letto));
   cout << "Leggo dalla pipe – Messaggio 2: " << letto << endl;
   return 0;
}
