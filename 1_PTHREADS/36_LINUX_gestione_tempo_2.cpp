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


void *figlio(void *argomento) {
	int nome = *(int*)argomento;
	cout << "Ciao mondo! Io sono il thread " << nome;
	cout << " e ho come ID " << pthread_self() << endl;
	pthread_exit(NULL);
}


int main() {
	pthread_t tid1, tid2;
	int a=1, b=2;
	timespec t;
	
	clock_getres(CLOCK_REALTIME, &t); // clock_getres
	cout << "clock_getres \t" << t.tv_sec << " secondi\t" << t.tv_nsec 
	     << " nanosecondi" << endl;
	
	clock_gettime(CLOCK_MONOTONIC, &t); // clock_gettime
	cout << "clock_gettime \t"<< t.tv_sec << " secondi\t" << t.tv_nsec 
	     << " nanosecondi"  << endl;
	
	t.tv_sec = 0;
	t.tv_nsec =  0;
	clock_settime(CLOCK_MONOTONIC, &t); // clock_set_time
	cout << "clock_settime \t"<< t.tv_sec << " secondi\t" << t.tv_nsec 
	     << " nanosecondi"  << endl;
	     
	aggiunge_millisecondi(&t, 1000);
	clock_nanosleep(CLOCK_MONOTONIC, 0, &t, NULL); // clock_nanosleep	
	pthread_create(&tid1, NULL, figlio, (void*)&a);
	
	clock_gettime(CLOCK_MONOTONIC, &t);
	aggiunge_millisecondi(&t, 1000);
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL); // clock_nanosleep	
	pthread_create(&tid2, NULL, figlio, (void*)&b);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);	
	pthread_exit(NULL);
}
