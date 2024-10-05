#include <iostream>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
using namespace std;

//aggiunge ms millisecondi alla variabile temporale puntata da t
void aggiunge_millisecondi(struct timespec *t, int ms) {
	t->tv_sec += ms/1000;
	t->tv_nsec += (ms%1000) * 1000000;
	if( t->tv_nsec > 1000000000) {
		t->tv_nsec -= 1000000000;
		t->tv_sec += 1;
	}
}

sem_t a, b, c, d;
struct parametri {   // definisco un po' di parametri caratteristici del thread
	int nome;
	unsigned periodo;	// periodo
	struct timespec at; // istante di riattivazione
	short    priorita;	// in [0-32]
};
void *periodico(void *arg) {
  struct parametri *p = (struct parametri *) arg;
  clock_gettime(CLOCK_MONOTONIC, &(p->at));
  aggiunge_millisecondi(&(p->at), p->periodo);
  while(1) {
   switch(p->nome) {
   case 1: cout<<"11111111111111111111111111111111111111111111111111\n"<<flush;
            sem_post(&a); break;
    case 2: sem_wait(&a);
            cout << "          2222222222\n"
                 << "          2222222222\n" << flush;
            sem_post(&b); break;
    case 3: sem_wait(&b);
            cout << "                    3333333333\n"
                 << "                    3333333333\n" << flush;
            sem_post(&c); break;
    case 4: sem_wait(&c);
            cout << "                              4444444444\n"
                 << "                              4444444444\n" << flush;
             sem_post(&d); break;
    case 5: sem_wait(&d);
            cout << "                                        5555555555\n"
                 << "                                        5555555555\n"<<flush;
             break;
     }
   clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &(p->at), NULL);
   aggiunge_millisecondi(&(p->at), p->periodo);
 }
}
int main() {
	pthread_t  tid1, tid2, tid3, tid4, tid5;             // identificatori tidX
	pthread_attr_t	attr1, attr2, attr3, attr4, attr5;       // attributi attrX
	struct sched_param	miopar;           // per iniettare la priorità in attrX
	struct parametri tp1, tp2, tp3, tp4, tp5;                  // parametri tpX
	sem_init(&a, 0, 0);
	sem_init(&b, 0, 0);
	sem_init(&c, 0, 0);
	sem_init(&d, 0, 0);
	tp1.nome = 1; tp1.periodo = 100; tp1.priorita = 20;
	tp2.nome = 2; tp2.periodo = 100; tp2.priorita = 20;
	tp3.nome = 3; tp3.periodo = 100; tp3.priorita = 20;
	tp4.nome = 4; tp4.periodo = 100; tp4.priorita = 20;
	tp5.nome = 5; tp5.periodo = 100; tp5.priorita = 20;
	pthread_attr_init(&attr1);
	pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr1, SCHED_OTHER);
	miopar.sched_priority = tp1.priorita;
	pthread_attr_setschedparam(&attr1, &miopar);//___________________
	pthread_attr_init(&attr2);
	pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr2, SCHED_OTHER);
	miopar.sched_priority = tp2.priorita;
	pthread_attr_setschedparam(&attr2, &miopar);//___________________
	pthread_attr_init(&attr3);
	pthread_attr_setinheritsched(&attr3, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr3, SCHED_OTHER);
	miopar.sched_priority = tp3.priorita;
	pthread_attr_setschedparam(&attr3, &miopar);//___________________
	pthread_attr_init(&attr4);
	pthread_attr_setinheritsched(&attr4, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr4, SCHED_OTHER);
	miopar.sched_priority = tp4.priorita;
	pthread_attr_setschedparam(&attr4, &miopar);//___________________
	pthread_attr_init(&attr5);
	pthread_attr_setinheritsched(&attr5, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attr5, SCHED_OTHER);
	miopar.sched_priority = tp5.priorita;
	pthread_attr_setschedparam(&attr5, &miopar);//___________________
	pthread_create(&tid1, &attr1, periodico, (void *) &tp1);
	pthread_create(&tid2, &attr2, periodico, (void *) &tp2);
	pthread_create(&tid3, &attr3, periodico, (void *) &tp3);
	pthread_create(&tid4, &attr4, periodico, (void *) &tp4);
	pthread_create(&tid5, &attr5, periodico, (void *) &tp5);
	pthread_join(tid1, NULL); pthread_attr_destroy(&attr1);
	pthread_join(tid2, NULL); pthread_attr_destroy(&attr2);
	pthread_join(tid3, NULL); pthread_attr_destroy(&attr3);
	pthread_join(tid4, NULL); pthread_attr_destroy(&attr4);
	pthread_join(tid5, NULL); pthread_attr_destroy(&attr5);
	pthread_exit(NULL);
}
