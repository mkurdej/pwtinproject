/*
 * VoIPPacketsManager.h
 *
 *  Created on: 2010-01-14
 *      Author: Piotr Gwizda�a
 */

#ifndef VOIPPACKETSMANAGER_H_
#define VOIPPACKETSMANAGER_H_

#include "debug/debug.h"

class VoIPPacketsManager {
public:
	/**
	 * TODO: jakie� dane potrzebne przy konstrukcji!
	 */
	VoIPPacketsManager();
	virtual ~VoIPPacketsManager();

	/**
	 * Zwraca przez retBuffer pakiet kt�ry jest gotowy do wys�ania.
	 * Zadanie to polega na odczytaniu porcji informacji z pliku audio
	 * lub z pliku z danymi steganograficznymi, opakowaniu jej i zwr�ceniu
	 * przez retBuffer.
	 */
	void getPacketToSend(char** retBuffer, int packetSize);

	/**
	 * Odbiera pakiet odebrany przez po��czenie VoIP. Zadanie polega
	 * na 'odpakowaniu' pakietu (jesli to konieczne) i zapisaniu
	 * odebranych danych w pami�ci. P�niej dane te b�d� mog�y by�
	 * zapisane w plikach wyj�ciowych.
	 */
	void putReceivedPacket(char** packet, int packetSize);

};

#endif /* VOIPPACKETSMANAGER_H_ */
