/*
 * Main.h
 *
 *  Created on: 2010-01-14
 *      Author: Piotr Gwizda�a
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <string>
#include "../debug/debug.h"

using namespace std;

class Main {
public:
	Main();
	virtual ~Main();

	/**
	 * Tak na prawd� jedyne co mo�emy zrbi� ze string to wy�wietli�, zalogowa� lub nic.
	 */
	static void handleError(string message) {
		PRN("Error: ");
		PRN(message);
	}

	/**
	 * Tu przekazujemy argumenty wywo�ania programu.
	 */
	static int startProgram(int argc, char **argv) {
		PRN1("in startProgram");

		//print arguments
		for (int i=0; i<argc; i++) cout<<"arg nr "<<i<<" = "<<argv[i]<<endl;

		PRN("TODO: wczytanie konfiguracji");
		PRN("TODO: wczytuje dane audio");
		PRN("TODO: wywo�uje odpowiednie metody w VoIPModule..");
		PRN("TODO: zapisuje loga do pliku...");

		PRN1("ends startProgram");
		return 0;
	}

};

#endif /* MAIN_H_ */
