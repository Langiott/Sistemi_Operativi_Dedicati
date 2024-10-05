/* processo_memoria.cpp */
#include <iostream>
extern int _etext, _edata, _end;
using namespace std;
int a=1; // in DATA
int b;   // in BSS
int main(int argc, char **argv) {
 cout << "TEXT termina a " <<hex<< long(&_etext) << endl;//etext
 cout << "DATA termina a " <<hex<< long(&_edata) << endl;//edata
 cout << "BSS  termina a " <<hex<< long(&_end) << endl;	//_end
 static int c=2;	// in DATA
 static int d;		// in BSS
 int e; 			// in STACK
 int *f = new int;	// in HEAP
 cout << "globale inizializzata a " << hex << long(&a) << endl;
 cout << "statica inizializzata c " << hex << long(&c) << endl;
 cout << "globale NON inizializ b " << hex << long(&b) << endl;
 cout << "statica NON inizializ d " << hex << long(&d) << endl;
 cout << "locale e "                << hex << long(&e) << endl;
 cout << "puntatore dinamica f "    << hex << long(&f) << endl;
 cout << "variabile dinamica *f "   << hex << long(f) << endl;
 cout << "primo argomento "         << hex << long(argv);
 return 0;
}

