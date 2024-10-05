#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char **argv) {
	int i;
	cout << "programma exec-uto dal processo padre " << getppid()
		 << " nel figlio " << getpid() << endl;
	for (i=0; i<argc ; i++) cout << i+1 << " = " << argv[i] << endl;
	return 0;
}
