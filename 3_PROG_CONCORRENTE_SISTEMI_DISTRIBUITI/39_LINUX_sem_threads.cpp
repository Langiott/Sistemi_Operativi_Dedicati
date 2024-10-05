#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

unsigned buffer[100000];
sem_t s; // inizializza semaforo che deve essere GLOBALE

void *uno(void *) {
	cout << "sto partendo" << endl;
	sem_wait(&s); // ---------------------------WAIT
	for (int i=0; i < 100000; i++)  buffer[i]=1;
	sem_post(&s); // -------------------------SIGNAL
	pthread_exit(NULL);
}
void *zero(void *) {
	cout << "sto partendo" << endl;
	sem_wait(&s); // ---------------------------WAIT
	for (int i=0; i < 100000; i++)  buffer[i]=0;
	sem_post(&s); // -------------------------SIGNAL
	pthread_exit(NULL);
}
int main() {
	pthread_t tid1, tid2;
	sem_init(&s, 0, 1);          // INIZIALIZZAZIONE
	pthread_create(&tid1, NULL, uno, NULL);
	pthread_create(&tid2, NULL, zero, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	for (int i=0; i < 100000; i++) cout << buffer[i];
	pthread_exit(NULL);
}
