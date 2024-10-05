/*
 * User-defined signal handling
siginfo_t {
 int      si_signo;   // Signal number
 int      si_errno;   // An errno value
 int      si_code;    // Signal code
 int      si_trapno;  // Trap number that caused hardware-generated signal
 pid_t    si_pid;     // Sending process ID
 uid_t    si_uid;     // Real user ID of sending process
 int      si_status;  // Exit value or signal
 clock_t  si_utime;   // User time consumed
 clock_t  si_stime;   // System time consumed
 sigval_t si_value;   // Signal value
 int      si_int;     // POSIX.1b signal
 void    *si_ptr;     // POSIX.1b signal
 int      si_overrun; // Timer overrun countnPOSIX.1b timers
 int      si_timerid; // Timer ID; POSIX.1b timers 
 void    *si_addr;    // Memory location which caused fault
 long     si_band;    // Band event 
 int      si_fd;      // File descriptor
 short    si_addr_lsb;// Least significant bit of address
 void    *si_lower;   // Lower bound when address violation occurred 
 void    *si_upper;   // Upper bound when address violation occurred
 int      si_pkey;    // Protection key on PTE that caused fault
 void    *si_call_addr;// Address of system call instruction
 int      si_syscall; // Number of attempted system call
 unsigned int si_arch;// Architecture of attempted system call
}
 
#include <signal.h> // libreria per i segnali
struct sigaction {
     void     (*sa_handler)(int); // punta all'handler nel caso normale
     void     (*sa_sigaction)(int, siginfo_t *, void *); // caso di SA_SIGINFO
     sigset_t   sa_mask; // maschera i segnali che devono essere bloccati
                         // durante l'esecuzione dell'handler
     int        sa_flags; // flags che modificano il comportamente dell'handler
     void     (*sa_restorer)(void);
};

int sigaction(int signum,const struct sigaction *act,struct sigaction *oldact);
signum: id della signal di cui si vuole installare l'handler
act: punta alla struttura contenente le informazioni circa il nuovo handler
oldact: se diverso da NULL punta alla struttura in cui vengono salvate le 
        informazioni riguardanti il vecchio handler
*/

#include <signal.h> // libreria per i segnali
#include <cstring> // string.h - per memset
#include <iostream>
#include <unistd.h>
using namespace std;
int contatore = 0;
char car;
// potenziale handler di un qualche segnale
static void gestore_segnale(int numero_signal) { 
	++contatore;
}
int main() {
	struct sigaction nuova; // definisco una struct di tipo sigaction
	memset(&nuova, 0, sizeof(nuova));  // resetta la struct nuova
	// il sigaction handler di nuova va a puntare gestore_segnale()
	nuova.sa_handler = gestore_segnale; 
	sigaction (SIGUSR1, &nuova, NULL); // registra gestore per SIGUSR1
	int mestesso = getpid();
	cerr << "programma in esecuzione " << mestesso << "\n";
	while ((cin >> car) && car != 'a') kill(mestesso, SIGUSR1);
	cout << "mi sono inviato SIGUSR1 " << contatore << " volte\n";
	return 0;
}
