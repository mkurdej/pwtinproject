/*
 * NoSteg.cpp
 *
 *  Created on: 2010-01-14
 *      Author: Piotr Gwizda�a
 */

#include "NoSteg.h"
#include "../Main/Main.h"
#include <fstream>

NoSteg::NoSteg(Config* cfg) :
	VoIPPacketsManager(cfg) {
	templatePacket.delay = config->noStegRTPDelay;

	// TODO inicjalizacja danych na char* ?
	vector<char> data = getAudioDataToSend();
	templatePacket.data = new char[data.size()];
	for (int i = 0; i < (int) data.size(); i++) {
		templatePacket.data[i] = data[i];
	}
	templatePacket.dataSize = data.size();
}

NoSteg::~NoSteg() {
	// TODO Auto-generated destructor stub
}

RTPPacket& NoSteg::getNextPacket() {
	PRNBITS_(4, templatePacket.header->toString());
	templatePacket.header->nextRTPHeader(NARROW_BAND); // changes sequenceNumber and timestamp
	PRNBITS_(4, templatePacket.header->toString());

	templatePacket.delay = config->noStegRTPDelay;
	VAR_(2, (int)templatePacket.delay);

	vector<char> data = getAudioDataToSend();
	templatePacket.data = new char[data.size()];
	templatePacket.dataSize = data.size();
	for (int i = 0; i < (int) data.size(); i++) {
		templatePacket.data[i] = data[i];
	}
	VAR_(2, (int)templatePacket.dataSize);
	return templatePacket;
}

void NoSteg::putReceivedPacketData(RTPPacket& packet) {
	//nie interesuje nas to co dostajemy gdy my dzwonimy.
	if (config->weAreCalling) return;
	ofstream myfile (config->outputAudioFilePath.c_str());
	if (myfile.is_open()) {
		myfile.write(packet.data, packet.dataSize);
		myfile.close();
	}
	else Main::getInstance()->handleError("Unable to open output audio data file: "
										+config->outputAudioFilePath);
}
