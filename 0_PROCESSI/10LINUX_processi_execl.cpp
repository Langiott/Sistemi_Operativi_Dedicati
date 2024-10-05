/* è buona norma controllare sempre se c'è stato un errore
 * risp=syscall(....);
		if (risp < 0) {
			perror("Errore nella chiamata di syscall \n");
			exit(-1);
		}
* per valutare e segnalare se la syscall è andata a buon fine
* man syscall - per vedere in quale header file sono contenuti il
* prototipo e le strutture dati utilizzate dalla syscall
* le syscall della famiglia exec() non creano nuovi processi e non
* ritornano alcun valore al processo chiamante in caso di successo;
* lo fanno solo in caso di insuccesso ed in questo caso si tratta
* di un numero negativo
* execl() execlp() execle() execv() execvp() execve() */
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
	int risp;
	pid_t pid = fork();                 // genera il nuovo processo
	if (pid < 0) {                                        // errore
		cerr << "generazione del nuovo processo fallita\n";
		exit(-1);
	}
	else if (pid == 0) {                         // processo figlio
		risp=execl("/bin/ls", "ls", NULL);
		if (risp < 0) {
			cerr << "Errore nella chiamata di execlp \n";
			exit(-1);
		}
	}
	else { // processo genitore attende il completamento del figlio
		wait(NULL);
		cout << "il processo figlio ha terminato \n";
	}
	return 0;
}
