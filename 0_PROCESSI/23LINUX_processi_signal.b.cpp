#include <iostream>
#include <signal.h>
#include <cstring> // per memset()
using namespace std;
void gestore_divisionePerZero(int signum) {// nuovo gestore
   if (signum == SIGFPE) {
      cout << "Ricevuto un SIGFPE! Ma non hai ancora imparato"
           << " a fare i controlli per evitare la divisione per zero?";
      exit (0);
   } 
   else cout << "Ricevuto il segnale " << signum << endl;
   return;
}
int main() {
   int risultato, num, den;
   struct sigaction nuova; // nuova struct di tipo sigaction
   memset(&nuova, 0, sizeof(nuova));  // resetta la nuova
   nuova.sa_handler = gestore_divisionePerZero; // setta nuovo gestore
   sigaction (SIGFPE, &nuova, NULL); // registra l'handler per SIGFPE
   if (nuova.sa_handler == SIG_ERR) {
      cerr << "errore di segnale generico: ";
      return 1;
   }
   cin >> num >> den; risultato = num/den;
   cout << "Il risultato della divisione è " << risultato << endl;
   return 0;
}


