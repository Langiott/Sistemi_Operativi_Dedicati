/*
primo esempio di thread:
* thread creation
*/

#include <iostream>
#include <pthread.h>
using namespace std;
void* funzione(void*) {
	cout << "Ciao mondo! Io sono un semplice thread \n";
	pthread_exit(NULL);
}
int main() {
	int ambito;
	pthread_attr_t attributo; // struttura dell'attributo
	pthread_attr_init(&attributo); // attributi di default
	// per prima cosa appura l'ambito della contesa
	if (pthread_attr_getscope(&attributo,&ambito) !=0)
	cerr << "Impossibile appurare l'ambito della contesa.\n";
	else {
	   if (ambito == PTHREAD_SCOPE_PROCESS) cout << "PCS\n";
	   else if (ambito == PTHREAD_SCOPE_SYSTEM) cout << "SCS\n";
	     else cerr << "Valore d'ambito della contesa non ammesso.\n";
	}
	// imposta a PCS o SCS l'algoritmo di scheduling
	pthread_attr_setscope(&attributo,PTHREAD_SCOPE_PROCESS);//errore?
	pthread_t identificatore; 
	pthread_create(&identificatore, &attributo, funzione, NULL);
	pthread_exit(NULL);
}
