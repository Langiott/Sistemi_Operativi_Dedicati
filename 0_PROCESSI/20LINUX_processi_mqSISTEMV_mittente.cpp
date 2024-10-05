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
   int id_coda, lung;
   key_t chiave;
   system("touch coda.txt");
   if ((chiave = ftok("coda.txt", 'B')) == -1) {
      cerr << "ftok";
      exit(1);
   }
   if ((id_coda = msgget(chiave, PERMS | IPC_CREAT)) == -1) {
      cerr << "msgget";
      exit(1);
   }
   cout << "MITTENTE: inizia spedizione messaggi.\n.\n";
   cout << "Immetti il testo, ^D per terminare:\n";
   buf.tipo = 1; // qui si definirebbe il tipo 
   while(fgets(buf.testo, sizeof buf.testo, stdin) != NULL) {
      lung = strlen(buf.testo);
      // rimuove il newline se esiste
      if (buf.testo[lung-1] == '\n') buf.testo[lung-1] = '\0';
      if (msgsnd(id_coda, &buf, lung+1, 0) == -1)
      cerr << "msgsnd";
   }
   strcpy(buf.testo, "fine");
   lung = strlen(buf.testo);
   if (msgsnd(id_coda, &buf, lung+1, 0) == -1)
   cerr << "msgsnd";
   if (msgctl(id_coda, IPC_RMID, NULL) == -1) {
      cerr << "msgctl";
      exit(1);
   }
   cout << "MITTENTE: terminata spedizione messaggi.\n";
   return 0;
}
