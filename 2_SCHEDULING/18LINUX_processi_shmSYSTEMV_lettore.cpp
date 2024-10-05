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
	   cout << "Lettore: leggo le " << c << "\n";
	   cout << p_memcond << endl;
	   sleep(3);
	   }
   cout << "Lettore: disassocio memoria condivisa\n";
   if (shmdt(p_memcond) == -1) {
      cerr <<"shmdt";
      return 1;
   }
   cout << "Lettore: finito!\n";
   return 0;
}
