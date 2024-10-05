#include <sys/wait.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <fcntl.h> // per la open
#include <unistd.h>
using namespace std;

int main () {
	int fd2;
	char myfifo[] = "/tmp/myfifo";
	// crea la FIFO modalità duplice
	mkfifo(myfifo, 0666);
	char stringa1[80], stringa2[80];
	while(1) {
		// apre la FIFO in modalità lettura
		fd2 = open(myfifo, O_RDONLY);
		// e legge dalla FIFO
		read(fd2,stringa1,sizeof(stringa1));
		cout << "Utente 1: " << stringa1 << endl; 
		close(fd2); // chiude la FIFO
		// apre la FIFO in modalità scrittura
		fd2 = open(myfifo, O_WRONLY);
		cin.getline(stringa2,80);
		// e  la scrive sulla FIFO
		write(fd2, stringa2, sizeof(stringa2)+1);
		close(fd2); // chiude la FIFO
	}
	return 0;
}
