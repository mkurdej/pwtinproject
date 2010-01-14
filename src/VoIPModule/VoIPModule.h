/*
 * VoIPModule.h
 *
 *  Created on: 2010-01-14
 *      Author: Piotr Gwizda�a
 */

#ifndef VOIPMODULE_H_
#define VOIPMODULE_H_

#include <string>
#include "debug/debug.h"

using namespace std;

class VoIPModule {
public:
	VoIPModule();
	virtual ~VoIPModule();

	/**
	 * Wysy�amy dane z pliku audio do wskazanego hosta zestawiaj�c najpierw po��czenia VoIP.
	 * TODO: jakie argumenty potrzebne?
	 */
	void doSending(string audioFile, int destIP);

	/**
	 * Czekamy na po��czenie, odbieramy je i zapisujemy dane audio do wskazanego pliku.
	 * TODO: jakie argumenty?
	 */
	void doReceiving(string audioFile);

};

#endif /* VOIPMODULE_H_ */
