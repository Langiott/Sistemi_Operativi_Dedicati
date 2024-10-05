/*
 * User-defined pipe handling
 */
#include <signal.h> // libreria per i segnali
#include <cstring>  // string.h - per memset
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <unistd.h> // anche per _PC_PIPE_BUF
using namespace std;

#define DIMBUFF 80    // dimensione buffer per la stringa ricevuta dal padre
//#define DO_SIGPIPE
void handler(int signum) {
	cout << "Ricevuto SIGPIPE n° " << signum << endl;
	exit(0);
}
int main() {
	pid_t figlio;
	int fd[2];
	struct sigaction nuova;         // dichiara una struct di tipo sigaction
	char stringa[] = "Le parole che non ti ho mai detto!";
	char locale[DIMBUFF];       // dove il padre sistema la stringa ricevuta 
	nuova.sa_handler = handler;          // installo l'handler della SIGPIPE
	sigemptyset(&nuova.sa_mask); 
	nuova.sa_flags = 0; 
	if(sigaction(SIGPIPE, &nuova, NULL) == -1) {
		cerr << "errore nell'installazione della SIGPIPE\n";
		exit(-1);}
	if (pipe(fd) == -1) {                                   // crea la pipe
	cerr << "errore nella pipe";
	exit(-1);}
	switch(figlio = fork()) { // il figlio eredita i descrittori della pipe 
		case -1:                                      
			cerr << "generazione del nuovo processo fallita\n";
			exit(-1);
			break;
		case 0:  // sono nel figlio che chiude il descrittore in lettura
			close(fd[0]); // perché sulla pipe deve solo scrivere
			for (unsigned char i=0; i<=strlen(stringa); i++) {
				if (write(fd[1], &stringa[i], sizeof(char)) == -1) {
					cerr << "Errore nella write ...\n";
					exit(-1);
				}
			}
			cout << "Fine della scrittura\n";
			close(fd[1]);
			break;
		default: // sono nel padre che chiude il descrittore in scrittura
			close(fd[1]); // perché sulla pipe deve solo leggere
#ifdef DO_SIGPIPE
			close(fd[0]); // il padre chiude anche in lettura causando 
			wait(NULL); // l'irritazione del figlio che riceve una SIGPIPE
			exit(0);
#endif
			for (unsigned char i=0; i<DIMBUFF; i++) {
				if (read(fd[0], &locale[i], sizeof(char)) == -1) {
					cerr << "Errore nella read ...\n";
					exit(-1);
				}
				if (locale[i] == 0) break;
			}
			locale[DIMBUFF-1] = 0;
			cout << "Io, il padre, ho ricevuto \"" << locale << "\"\n";
			exit(0);
		}
}
