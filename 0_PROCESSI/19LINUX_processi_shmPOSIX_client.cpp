#include <iostream>
#include <unistd.h>
#include <sys/shm.h> // server di memoria condivisa
#include <sys/mman.h>
#include <sys/stat.h> // per costanti mode
#include <fcntl.h>   // per costanti O_*
using namespace std;
int main () {
	int mc_fd;
	char * ptr;
	mc_fd = shm_open("/pippo", O_RDONLY, 0666);
	if (mc_fd == -1) {
		cerr << "Fallimento apertura memoria condivisa\n";
		exit(-1);
	}
	ptr = (char *) mmap(0,4096,PROT_READ,MAP_SHARED,mc_fd,0);
	if (ptr == MAP_FAILED) {
		cerr << "Fallimento della mappatura\n";
		return -1;
		}
	cout << (char *) ptr; // scrive contenuto memoria condivisa
	if (shm_unlink("/pippo") == -1) {// chiude memoria condivisa
		cerr << "errore rimozione memoria" <<  endl;
		exit(-1);
	}
return 0;
}
