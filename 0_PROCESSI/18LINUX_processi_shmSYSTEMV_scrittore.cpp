#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define DIM_BUF 1024
#define CHIAVE 0x1234
using namespace std;
int main() {
   char c;
   int id_segmem;
   char *p_memcond;
   // crea il segmento di memoria
   id_segmem = shmget(CHIAVE, DIM_BUF, 0644|IPC_CREAT);
   if (id_segmem == -1) {
      cerr << "Fallimento apertura memoria condivisa\n";
      return 1;
   }
   // allaccia il segmento di memoria
   p_memcond = (char *)shmat(id_segmem, NULL, 0);
   if (p_memcond == (void *) -1) {
      cerr << "Fallimento associatura memoria condivisa\n";
      return 1;
   }
   for (c = 'A'; c < 'F'; c++) {
	   memset(p_memcond, c, DIM_BUF-1);
	   *(p_memcond+DIM_BUF) = '\0';
	   cout << "Scrittore: scritti " << c << endl;
	   sleep(3);
	   }
   if (shmdt(p_memcond) == -1) {
      cerr << "shmdt";
      return 1;
   }
   if (shmctl(id_segmem, IPC_RMID, 0) == -1) {
      cerr << "shmctl";
      return 1;
   }
   cout << "Scrittore: finito!\n";
   return 0;
}

