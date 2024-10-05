/* creazione di un processo mediante la syscall fork()
 * il figlio ha pid=0 e lo stesso codice del padre
 * pid_t wait(int *status);
 * pid_t waitpid(pid_t pid, int *status, int options);*/
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
char car= 'a';
int main() {
	pid_t pid;
	pid = fork();                      // genera il nuovo processo
	if (pid==0) {                              // processo figlio
		cout << "inserisci un carattere \n";
		cin >> car;
	}
	else {// processo genitore attende il completamento del figlio
		wait(NULL);
		cout << "hai inserito il carattere " << car << endl;
	}
	return 0;
}
