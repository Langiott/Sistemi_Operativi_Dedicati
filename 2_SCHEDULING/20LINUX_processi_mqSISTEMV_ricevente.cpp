#include <iostream>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
using namespace std;
#define PERMS 0644
struct buf_mess {
   long tipo;
   char testo[200];
};
int main() {
   buf_mess buf;
   int id_coda;
   key_t chiave;
   if ((chiave = ftok("coda.txt", 'B')) == -1) {
      cerr << "ftok";
      exit(1);
   }
   if ((id_coda = msgget(chiave, PERMS)) == -1) {//connette a coda
      cerr << "msgget";
      exit(1);
   }
   cout << "RICEVENTE: pronto a ricevere messaggi.\n";
   for(;;) { 
      if (msgrcv(id_coda, &buf, sizeof(buf.testo), 0, 0) == -1) {
         cerr << "msgrcv";
         exit(1);
      }
      cout << "ricevuto: " << buf.testo << endl;
      if (!strcmp(buf.testo, "fine")) break;
   }
   cout << "RICEVENTE: terminata ricezione messaggi.\n";
   system("rm coda.txt");
   return 0;
}
