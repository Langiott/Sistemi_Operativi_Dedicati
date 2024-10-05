#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
	pid_t pid;
	pid = fork();
	if (pid == 0) {
	  system("ps -f");
      cout << "Figlio: pid " <<getpid()<<" ppid "<<getppid()<<endl;
      exit(0);
   } else {
      cout << "Padre: pid " << getpid()<<" ppid "<<getppid()<<endl;
      sleep(10);
      system("ps -aux|grep Z");
   }
   return 0;
}

