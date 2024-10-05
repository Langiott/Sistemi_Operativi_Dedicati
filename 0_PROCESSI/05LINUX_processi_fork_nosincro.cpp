/* creazione di un processo mediante la fork()
 * mancanza di sincronizzazione */

#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;

void stampa( const char * str ) {
	while( *str != '\0' ) {
		cout << *str++ << flush;
		usleep(9);
		}
}

int main() {
	if( fork() == 0 )
		stampa( "................" ); // figlio
	else
		stampa( "||||||||||||||||" ); // padre
}

