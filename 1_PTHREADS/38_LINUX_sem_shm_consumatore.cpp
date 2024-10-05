#include <iostream>
#include <fcntl.h> // per la open
#include <sys/shm.h> // server di memoria condivisa
#include <sys/mman.h>
#include <semaphore.h>
using namespace std;

#define MEMORIA "/shm_pippo"
#define SEMnnPieno "/sem_nnPieno"
#define SEMnnVuoto "/sem_nnVuoto"
#define SIZE 4096
int main () {
	int mc_fd;
	char *base, *ptr;
	mc_fd = shm_open(MEMORIA, O_RDONLY, 0666);
	base = (char *) mmap(0, SIZE, PROT_READ, MAP_SHARED, mc_fd,0);

	sem_t *sem_np = sem_open(SEMnnPieno, O_EXCL);//apre SEMnnPieno
	sem_t *sem_nv = sem_open(SEMnnVuoto, O_EXCL);//apre SEMnnVuoto

	for (int j = 0; j < 10; ++j) {
		ptr = base;
		cout << "\nWAIT_nonVuoto\n"<< flush;
		sem_wait(sem_nv); // ----------------------- WAIT_nonVuoto
		for (int i = 0; i < 200; ++i) cout << *(ptr++);
		cout << "\nPOST_nonPieno\n" << flush;
		sem_post(sem_np); // ----------------------- POST_nonPieno
	}
	sem_unlink(SEMnnPieno);// chiude e rilascia l'oggetto semaforo
	sem_unlink(SEMnnVuoto);// chiude e rilascia l'oggetto semaforo
	shm_unlink(MEMORIA);          // rilascia la memoria condivisa
	return 0;
}
