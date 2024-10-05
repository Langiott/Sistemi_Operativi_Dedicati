/*
* pthread_attr_setschedpolicy
 */

#include <iostream>
#include <pthread.h>

using namespace std;

void *figlio(void *p) {
//	int *pi = (int *) p;
	pthread_t tid = pthread_self();
	cout << "Ciao mondo! Mi chiamo " << (char *)p << endl;
	cout << "ho ID  " << tid << "e sono schedulato FIFO a priorità 22\n";
	pthread_exit(NULL);
}

int main() {
	pthread_attr_t		mioatt;	 // struttura dell'attributo
	struct sched_param	miopar;	 // struttura della priorità
	pthread_t 			tid; 
	pthread_attr_init(&mioatt);	 // inizializza l'attributo
	pthread_attr_setdetachstate(&mioatt, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setinheritsched(&mioatt, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&mioatt, SCHED_FIFO);
	miopar.sched_priority = 22;
	pthread_attr_setschedparam(&mioatt, &miopar);
	char a[]= "Pippo";
	pthread_create(&tid, &mioatt, figlio, (void *)&a);
	pthread_join(tid, NULL);
	pthread_attr_destroy(&mioatt);
	cout << "sono il padre\n";
	pthread_exit(NULL);
}
