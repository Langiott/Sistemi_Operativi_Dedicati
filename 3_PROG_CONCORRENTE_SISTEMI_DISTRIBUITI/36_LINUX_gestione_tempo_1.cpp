/*
gestione del tempo nella libreria POSIX <pthread.h>

struct timespec {
	time_t tv_sec;
	long   tv_nsec;
}
* clock_getres
* clock_gettime
* clock_settime
*/
 
#include <iostream>
#include <pthread.h>
#include <time.h> // per le funzioni e le strutture temporali
using namespace std;

// confronta le due variabili temporali t1 e t2
// restituisce 0  se t1=t2
// restituisce +1 se t1>t2
// restituisce -1 se t1<t2
int confronta_istanti(struct timespec t1, struct timespec t2) {
	if (t1.tv_sec > t2.tv_sec) return 1;
	if (t1.tv_sec < t2.tv_sec) return -1;
	if (t1.tv_nsec > t2.tv_nsec) return 1;
	if (t1.tv_nsec < t2.tv_nsec) return -1;
	return 0;
}

// copia la variabile temporale ts in quella puntata da td
void copia_istante(struct timespec *td, struct timespec ts) {
	td->tv_sec = ts.tv_sec;
	td->tv_nsec = ts.tv_nsec;
}

//aggiunge ms millisecondi alla variabile temporale puntata da t
void aggiunge_millisecondi(struct timespec *t, int ms) {
	t->tv_sec += ms/1000;
	t->tv_nsec += (ms%1000) * 1000000;
	if( t->tv_nsec > 1000000000) {
		t->tv_nsec -= 1000000000;
		t->tv_sec += 1;
	}
}

#define SECONDI 2
#define NANOSECONDI 2

int main() {
	timespec t;
	clock_getres(CLOCK_REALTIME, &t);// vede la risoluzione temporale
	cout << "RISOLUZIONE \t\t" << t.tv_sec << " secondi\t" << t.tv_nsec 
	     << " nanosecondi" << endl;
	clock_gettime(CLOCK_MONOTONIC, &t);                // prende l'ora
	cout << "clock_gettime MT\t"<< t.tv_sec << " secondi\t" << t.tv_nsec 
	     << " nanosecondi"  << endl;
	clock_gettime(CLOCK_REALTIME, &t);                // prende l'ora
	cout << "clock_gettime RT\t"<< t.tv_sec << " secondi\t" << t.tv_nsec 
	     << " nanosecondi"  << endl;
	t.tv_sec = SECONDI;
	t.tv_nsec = NANOSECONDI;
	aggiunge_millisecondi(&t, 1000);          // aggiunge millisecondi
	clock_settime(CLOCK_MONOTONIC, &t);                 // setta l'ora
	clock_gettime(CLOCK_MONOTONIC, &t);                // prende l'ora
	cout << "clock_gettime MT\t"<< t.tv_sec << " secondi\t" << t.tv_nsec 
	     << " nanosecondi"  << endl;
	clock_settime(CLOCK_REALTIME, &t);                 // setta l'ora
	clock_gettime(CLOCK_REALTIME, &t);                // prende l'ora
	cout << "clock_gettime RT\t"<< t.tv_sec << " secondi\t" << t.tv_nsec 
	     << " nanosecondi"  << endl;
	pthread_exit(NULL);
}
