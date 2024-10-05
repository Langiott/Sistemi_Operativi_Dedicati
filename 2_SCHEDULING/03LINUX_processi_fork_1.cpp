/* creazione di un processo mediante la syscall fork()
 * il figlio ha lo stesso codice del padre
 */
#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
	cout << "\nPID = " << getpid() <<flush;          // PID del processo
	cout << "\nPID genitore = " << getppid()<< flush;// PID del genitore
	pid_t pippo;
	pippo = fork(); // genera nuovo processo; PID a pippo

	if (pippo==0) { // la variabile pippo del figlio NON è settata
		cout << "\nio sono il figlio e il mio PID è " << getpid()<< flush;
		cout << "\nmentre quello di mio padre è " << getppid()<< flush;
	}
	else {           // la variabile pippo del padre è settata
		cout << "\nio sono il padre  e il mio PID è " << getpid()<< flush;
		cout << "\nmentre quello di mio figlio è " << pippo<< flush;
	}
	cout << endl;

	system("ps");
	return 0;
}
