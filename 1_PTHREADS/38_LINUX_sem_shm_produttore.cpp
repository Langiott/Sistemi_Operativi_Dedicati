#include <iostream>
#include <fcntl.h> // per la open
#include <unistd.h> // per ftruncate
#include <sys/shm.h> // server di memoria condivisa
#include <sys/mman.h>
#include <semaphore.h>
using namespace std;

#define MEMORIA "/shm_pippo"
#define SEMnnPieno "/sem_nnPieno"
#define SEMnnVuoto "/sem_nnVuoto"
#define SIZE 4096
int main () {
	int mc;
	char *base, *ptr;
	mc = shm_open(MEMORIA, O_CREAT|O_RDWR, 0666);
	ftruncate(mc, SIZE); // dimensiona il segmento di memoria
	base = (char*) mmap(0,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,mc,0);
	// crea il semaforo col nome SEMnonPieno e lo inizializza a VERDE
	sem_t *sem_np = sem_open(SEMnnPieno, O_CREAT, S_IRUSR|S_IWUSR,1);
	// crea il semaforo col nome SEMnonVuoto e lo inizializza a ROSSO
	sem_t *sem_nv = sem_open(SEMnnVuoto, O_CREAT, S_IRUSR|S_IWUSR,0);

	for (int j = 0; j < 10; ++j) {
		ptr = base;
		cout << "WAIT_nonPieno\n"<< flush;
		sem_wait(sem_np); // -------------------------- WAIT_nonPieno
		for (int i = 0; i < 200; ++i) *(ptr++) = (j+48);
		cout << "POST_nonVuoto\n" << flush;
		sem_post(sem_nv); // -------------------------- POST_nonVuoto
	}
	cout << "STOP\n";
	return 0;
}
