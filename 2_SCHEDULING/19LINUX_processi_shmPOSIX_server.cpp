#include <iostream>
#include <unistd.h>   // per ftruncate()
#include <sys/shm.h>  // server di memoria condivisa
#include <sys/mman.h>
#include <sys/stat.h> // per costanti mode
#include <fcntl.h>    // per costanti O_*
#include <cstring>
using namespace std;
int main () {
	const char * message[]={"Sono ",
		                    "scritto ",
		                    "nella ",
		                    "memoria ",
		                    "condivisa\n"};
	int mc_fd;
	char * ptr;
	mc_fd = shm_open("/pippo", O_CREAT | O_RDWR, 0666);
	if (mc_fd == -1) {
		cerr << "Fallimento apertura memoria condivisa\n";
		exit(-1);
	}
	ftruncate(mc_fd, sizeof(message)); // dimensiona memoria
	ptr = (char*)mmap(0,4096,PROT_READ|PROT_WRITE,MAP_SHARED,mc_fd,0);
	if (ptr == MAP_FAILED) {
		cout << "Fallimento della mappatura\n";
		return -1;
	}
	// scrive nel segmento di memoria condivisa
	for (int i = 0; i < strlen(*message); ++i) {
		sprintf(ptr, "%s", message[i]);
		ptr += strlen(message[i]);
	}
	munmap(ptr, 4096); // dealloca memoria condivisa
	return 0;
}
