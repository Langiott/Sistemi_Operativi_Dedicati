/*
 * User-defined signal handling
*/

#include <signal.h>
#include <cstring> 
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char *argv[]) {
	pid_t pid_dest = atoi(argv[1]);
	const union sigval valore = {atoi(argv[2])};
	cout << "Invio SIGUSR1 al processo " << pid_dest
	     << " con valore " << atoi(argv[2]) << endl;
	int ret = sigqueue(pid_dest, SIGUSR1, valore);
	if (ret != 0) {
		cerr << "errore sigqueue: ";
		exit(1);
	}
	return 0;
}
