/*
 * figlio.cpp
 * 
 * Copyright 2019 Aldo Franco Dragoni <a.f.dragoni@univpm.it>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>

using namespace std;
int main () {
	pid_t pid;
	char * array[4] = {(char*)"Aldo",(char*)"Franco",(char*)"Dragoni"};
	switch (pid = fork()) {                   // genera processo figlio
		case -1:
			cerr << "generazione del nuovo processo fallita\n";
			exit(-1);
			break;
		case 0:                             // rimpiazza processo figlio
			cout << "Processo figlio ... padre = " << getppid() << endl;
			execv( "./figlio" , array);    // execv(programma,argomenti)
			cerr << "è fallita la execv\n";
			exit(-1);
			break;
		default:  // padre attende il completamento del programma figlio
			cout << "Processo padre .... pid t = " << getpid() << endl;
			sleep(1);
			exit(0);
	}
}
