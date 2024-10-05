#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
	pid_t pid;
	system("ps -f");
	pid = fork();
	if (pid == 0) {
      cout << "Figlio: pid " << getpid() << " ppid " << getppid()<<  endl;
      sleep(5);
      cout << "Figlio: pid " << getpid() << " ppid " << getppid()<<  endl;
      system("ps -f");
   } else {
      cout << "Padre: pid " << getpid() << " ppid " << getppid()<< endl;
      sleep(2);
      exit(0);
   }
   return 0;
}

