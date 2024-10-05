/*
 * Breve esempio di uso di fork() e signal() che genera due task che si scambiano
 * alternativamente un signal a intervalli "regolari di tempo.
 * Quesiti:
 * 1) Perché è stata inserita la linea if(secondi == 0)?
 * 2) Perché anche con questa linea c'è un caso critico di deadlock e quale è?
*/

#include <signal.h> // libreria per i segnali
#include <cstring> // string.h - per memset
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int secondi=0;
void gestore(int segnale_qualunque) {                    // gestore del segnale
	secondi++;
}
int main() {
	pid_t figlio, padre;
	struct sigaction nuova;            // dichiara una struct di tipo sigaction
	nuova.sa_handler = gestore;                       // punta il nuovo gestore
	sigemptyset(&nuova.sa_mask);         // il gestore maschera TUTTI i segnali
	nuova.sa_flags = 0;                            // nessun flag viene settato
	// installo l'handler prima della fork in modo che sia ereditato dal figlio
	sigaction(SIGUSR1, &nuova, NULL);  // registra il nuovo gestore per SIGUSR1
	switch(figlio = fork()) {                               // genera il figlio
		case -1:                                                      // errore
			cerr << "generazione del nuovo processo fallita\n";
			exit(-1); break;
		case 0:                                              // sono nel figlio
			padre = getppid();
			while(1) {
				sleep(10);                       // il figlio attende un secondo
				kill(padre, SIGUSR1);          // poi manda un segnale al padre
				pause();                              // e attende una risposta
				cout << "Secondi trascorsi (figlio) " << 2*secondi
				     << " -- ora = " << time(NULL) << endl;
				 } break;
		default:                                              // sono nel padre
			if (secondi == 0) pause();
			while(1) {
				cout << "Secondi trascorsi (padre)  " << 2*secondi - 1
				     << " -- ora = " << time(NULL) << endl;
				sleep(10);                        // il padre attende un secondo
				kill(figlio, SIGUSR1);        // poi manda un segnale al figlio
				pause();                              // e attende una risposta
			}
		}
}
