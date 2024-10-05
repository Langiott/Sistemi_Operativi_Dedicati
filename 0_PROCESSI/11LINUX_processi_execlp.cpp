/*
 * uso di un'altra syscall per rimpiazzare il codice del figlio
 * è buona norma controllare sempre se c'è stato un errore
 * risp=syscall(....);
		if (risp < 0) {
			perror("Errore nella chiamata di syscall \n");
			exit(-1);
		}
* per valutare e segnalare se la syscall è andata a buon fine
* 
* man syscall - per vedere in quale header file sono contenuti il prototipo 
*               e le strutture dati utilizzate dalla syscall
*
* le syscall della famiglia exec() non creano nuovi processi e non ritornano
* alcun valore al processo chiamante in caso di successo; lo fanno solo in caso
* di insuccesso ed in questo caso si tratta di un numero negativo
* execl() execlp() execle() execv() execvp() execve()
 */

#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
	pid_t pid;                 
	switch(pid = fork()) {          // genera il nuovo processo
		case -1: // errore nella generazione del nuovo processo
			cerr << "generazione del nuovo processo fallita\n";
			exit(-1);
			break;
		case 0:                              // processo figlio
			execlp("ls", "ls", "-l", NULL);
			cerr << "Errore nella chiamata di execlp \n";
			exit(-1);
			break;
		default:   // padre attende il completamento del figlio
			wait(NULL);
			cout << "il processo figlio ha terminato \n";
			exit(0);
	}
}



