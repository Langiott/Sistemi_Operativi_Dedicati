/* LINUX: ambiente di programmazione
 * prima di lanciare il main() LINUX chiama una startup che prende le
 * variabili d’ambiente, gli argomenti da riga di comando
 * (ed altro ancora) e le passa al main() (avendo prima generato il
 * processo tramite fork/exec); al termine del processo LINUX
 * esegue una end routine; il programma illustra il funzionamento di:
 * getenv() per prelevare il valore di una variabile d’ambiente
 * setenv() per valorizzarla
 */
#include <iostream>
#include <stdlib.h>  // per getenv e setenv
using namespace std;
extern char **environ; // 'man environ' per la descrizione di questa
// importante variabile (puntatore ad un array di puntatori a stringa
// detto "environment"); variabile specifica dello standard POSIX
// da notare che il main ha 3 parametri; il terzo non fa parte dello
// standard del C ma è ammesso da molti compilatori e gioca lo stesso
// ruolo di environ
int main(int argc, char **argv, char *topolino[]) {
  int c = 0;
  cout << "\n";
  while(environ[c] != NULL) {    // stampa a video tutte le stringhe
	  cout << environ[c] << endl;  // ovvero le variabili d'ambiente
	  cout << "=================================================\n";
	  c++;
  }
  c = 0;
  while(topolino[c] != NULL) { // fa la stessa cosa di environ
	  cout << topolino[c] << endl;
	  cout << "_________________________________________________\n";
	  c++;
  }
  // man getenv
  char *val = getenv("USER"); // val va a puntare la variabile il
  // cui nome  fornito come stringa a getenv()
  cout << "\nL'utente corrente è " << val << endl;
  // man setenv
  if(setenv("USER","franco",1)) { // setta la variabile e
    cerr << "\n setenv() fallimento\n";
    return 1;
  }
  cout << "Ho cambiato il valore della variabile USER\n";
  val = getenv("USER");
  cout << "\nL'utente corrente è " << val << endl;
  return 0;
}
