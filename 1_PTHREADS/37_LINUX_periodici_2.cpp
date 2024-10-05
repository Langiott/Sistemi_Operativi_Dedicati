/*
non_periodic
*/
 
#include <iostream>
#include <pthread.h>
#include <time.h> // per le funzioni e le strutture temporali
using namespace std;

// confronta le due variabili temporali t1 e t2
// restituisce 0  se t1=t2
// restituisce +1 se t1>t2
// restituisce -1 se t1<t2
int time_cmp(struct timespec t1, struct timespec t2) {
	if (t1.tv_sec > t2.tv_sec) return 1;
	if (t1.tv_sec < t2.tv_sec) return -1;
	if (t1.tv_nsec > t2.tv_nsec) return 1;
	if (t1.tv_nsec < t2.tv_nsec) return -1;
	return 0;
}

// copia la variabile temporale ts in quella puntata da td
void time_copy(struct timespec *td, struct timespec ts) {
	td->tv_sec = ts.tv_sec;
	td->tv_nsec = ts.tv_nsec;
}

//aggiunge ms millisecondi alla variabile temporale puntata da t
void time_add_ms(struct timespec *t, int ms) {
	t->tv_sec += ms/1000;
	t->tv_nsec += (ms%1000) * 1000000;
	if( t->tv_nsec > 1000000000) {
		t->tv_nsec -= 1000000000;
		t->tv_sec += 1;
	}
}
		
void *periodico(void *arg) {
	struct timespec t;
	int i = *(int*)arg;
	clock_gettime(CLOCK_MONOTONIC, &t);
	time_add_ms(&t, 1000);
	while(1) {
		switch(i) {
			case 1: cout << "11111111111111111111111111111111111111111111111111\n\n"  << flush; break;
			case 2: cout << "          2222222222\n" 
			             << "          2222222222\n" << flush; break;
			case 3: cout << "                    3333333333\n" 
			             << "                    3333333333\n" << flush; break;
			case 4: cout << "                              4444444444\n" 
			             << "                              4444444444\n" << flush; break;
			case 5: cout << "                                        5555555555\n"
			             << "                                        5555555555\n"  << flush; break;
			}
			clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
			time_add_ms(&t, 1000);
	}
}

int main() {
	pthread_t  tid1, tid2, tid3, tid4, tid5; 
	int  id1=1, id2=2, id3=3, id4=4, id5=5;
	pthread_create(&tid1, NULL, periodico, (void *) &id1);
	pthread_create(&tid2, NULL, periodico, (void *) &id2);
	pthread_create(&tid3, NULL, periodico, (void *) &id3);
	pthread_create(&tid4, NULL, periodico, (void *) &id4);
	pthread_create(&tid5, NULL, periodico, (void *) &id5);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	pthread_join(tid5, NULL);
	pthread_exit(NULL);
}
