#include <cstring>  
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fcntl.h> // per la open
#include <unistd.h> 
using namespace std;

int main () {
	int fd;
	char myfifo[] = "/tmp/myfifo";
	// crea la FIFO modalità duplice
	mkfifo(myfifo, 0666);
	char stringa1[80], stringa2[80];
	while(1) {
		// apre la FIFO in modalità scrittura
		fd = open(myfifo, O_WRONLY); 
		cin.getline(stringa2,80);
		// scrive sulla FIFO
		write(fd,stringa2,strlen(stringa2)+1);
		close(fd); // chiude la FIFO
		// apre la FIFO in modalità lettura
		fd = open(myfifo, O_RDONLY); 
		// legge dalla FIFO
		read(fd, stringa1, sizeof(stringa1));
		cout << "Utente 2: " << stringa1 << endl;
		close(fd); // chiude la FIFO
	}
	return 0;
}
