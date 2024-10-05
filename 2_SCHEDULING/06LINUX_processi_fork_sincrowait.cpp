/* creazione di un processo mediante la fork()
 * sincronizzazione tramite wait */

#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;
void stampa( const char * str ) {
	while( *str!= '\0' ) {
		cout << *str++ << flush;
		usleep(99);
		}
}
int main() {
	if( fork() == 0 )
		stampa( "................" ); // figlio
	else {
		wait(NULL); // attende il completamento del figlio
		stampa( "||||||||||||||||" ); // padre
	}
}
