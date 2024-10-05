#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
using namespace std;
int main() {
   int fd;
   char buf[80];
   cout << "Per terminare scrivi \"stop\"\n";
   fd = open("MIAFIFO", O_CREAT|O_WRONLY);
   while (1) {
      cout << "Immetti un messaggio: ";
      cin.getline(buf,80);
      write(fd, buf, strlen(buf));
      cout << "Messaggio inviato: "
           << buf << endl;
      if (strcmp(buf, "stop") == 0) {
         close(fd);
         break;
      }
   }
   return 0;
}
