/*
sched__rr_get_interval
 */

#include <iostream>
#include <pthread.h>
#include <sched.h>

using namespace std;

struct timespec q;

void *figlio(void *) {
	sched_rr_get_interval(0,&q);
	cout << "il figlio ha un quanto di " << q.tv_sec  << " secondi e "
		 << q.tv_nsec/1000000 << " millisecondi \n";
	pthread_exit(NULL);
}

int main() {
	pthread_attr_t		mioatt;	             // struttura dell'attributo
	struct sched_param	miopar;	             // struttura della priorità
	pthread_t 			tid;
	pthread_attr_init(&mioatt);	              // inizializza l'attributo
	pthread_attr_setdetachstate(&mioatt, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setinheritsched(&mioatt, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&mioatt, SCHED_RR);
	sched_rr_get_interval(0,&q);
	cout << "il padre ha un quanto di " << q.tv_sec  << " secondi e "
		 << q.tv_nsec/1000000 << " millisecondi \n";
	miopar.sched_priority = 23;
	pthread_attr_setschedparam(&mioatt, &miopar);
	pthread_create(&tid, &mioatt, figlio, NULL);
	pthread_join(tid, NULL);
	pthread_attr_destroy(&mioatt);
	pthread_exit(NULL);
}
