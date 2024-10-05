/*
 * User-defined signal handling
*/

#include <signal.h> 
#include <cstring> 
#include <sys/types.h>
#include <iostream>
#include <unistd.h>

using namespace std;

void handler(int sig_num, siginfo_t *info, void *extra) {
	cout << " Numero del segnale     " << info->si_signo << endl;
	cout << " Codice del segnale     " << info->si_code << endl;
	cout << " Processo mittente      " << info->si_pid << endl;
	cout << " ID utente del mittente " << info->si_uid << endl;
}

int main() {
	struct sigaction sa; 
	memset(&sa, 0, sizeof(sa));   
	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	int mestesso = getpid();
	cerr << "programma in esecuzione " << mestesso << "\n";
	kill(mestesso, SIGUSR1);
	return 0;
}
