/*
 * VoIPPacketsManager.cpp
 *
 *  Created on: 2010-01-14
 *      Author: Piotr Gwizda�a
 */

#include "VoIPPacketsManager.h"

/**
 * TODO: jakie� dane potrzebne przy konstrukcji!
 */
VoIPPacketsManager::VoIPPacketsManager() {
	// TODO Auto-generated constructor stub

}

VoIPPacketsManager::~VoIPPacketsManager() {
	// TODO Auto-generated destructor stub
}


/**
 * Zwraca przez retBuffer pakiet kt�ry jest gotowy do wys�ania.
 * Zadanie to polega na odczytaniu porcji informacji z pliku audio
 * lub z pliku z danymi steganograficznymi, opakowaniu jej i zwr�ceniu
 * przez retBuffer.
 */
void getPacketToSend(char** retBuffer, int packetSize) {

}

/**
 * Odbiera pakiet odebrany przez po��czenie VoIP. Zadanie polega
 * na 'odpakowaniu' pakietu (jesli to konieczne) i zapisaniu
 * odebranych danych w pami�ci. P�niej dane te b�d� mog�y by�
 * zapisane w plikach wyj�ciowych.
 */
void putReceivedPacket(char** packet, int packetSize) {

}
