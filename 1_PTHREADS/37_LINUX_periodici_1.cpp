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

void *barra(void *arg) {
	struct timespec t;
	int periodo = 10; // in millisecondi
	clock_gettime(CLOCK_MONOTONIC, &t);
	aggiunge_millisecondi(&t, periodo);
	while(1) {
		cout << '|';
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		aggiunge_millisecondi(&t, periodo);
	}
}
void *zero(void *arg) {
	struct timespec t;
	int periodo = 1; // in millisecondi
	clock_gettime(CLOCK_MONOTONIC, &t);
	aggiunge_millisecondi(&t, periodo);
	while(1) {
		cout << '_';
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		aggiunge_millisecondi(&t, periodo);
	}
}
void *acapo(void *arg) {
	struct timespec t;
	int periodo = 80; // in millisecondi
	clock_gettime(CLOCK_MONOTONIC, &t);
	aggiunge_millisecondi(&t, periodo);
	while(1) {
		cout << '\n';
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
		aggiunge_millisecondi(&t, periodo);
	}
}
int main() {
	pthread_t  barra_id, zero_id, acapo_id;
	pthread_create(&barra_id, NULL, barra, NULL);
	pthread_create(&zero_id,  NULL, zero,  NULL);
	pthread_create(&acapo_id, NULL, acapo, NULL);
	pthread_join(barra_id, NULL);
	pthread_join(zero_id,  NULL);
	pthread_join(acapo_id, NULL);
	pthread_exit(NULL);
}
