#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
using namespace std;
int main() {
   int fd, lung;
   char buf[80];
   mknod("MIAFIFO", S_IFIFO|0640, 0);
   while(1) {
      fd = open("MIAFIFO", O_RDONLY);
      lung = read(fd, buf, sizeof(buf));
      buf[lung] = '\0';
      cout << "Messaggio ricevuto: "
           << buf << " di "
           << lung
           << " bytes\n";
      if (strcmp(buf, "stop") == 0) {
         close(fd);
         break;
      }
   }
   return 0;
}
