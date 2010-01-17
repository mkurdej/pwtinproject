/*
 * NoSteg.cpp
 *
 *  Created on: 2010-01-14
 *      Author: Piotr Gwizda�a
 */

#include "NoSteg.h"

NoSteg::NoSteg(Config* cfg) : VoIPPacketsManager(cfg) {
	templatePacket.header->sequenceNumber = RTPHeader::generateSequenceNumber();
	VAR_(2, templatePacket.header->sequenceNumber);
	templatePacket.header->timestamp = RTPHeader::generateTimestamp();
	VAR_(2, (int) templatePacket.header->timestamp);
	templatePacket.header->ssrc = RTPHeader::generateSSRC();
	VAR_(2, (int) templatePacket.header->ssrc);
	PRNBITS_(2, templatePacket.header->toString());
	templatePacket.delay = config->noStegRTPDelay;

	// TODO inicjalizacja danych na char* ?
	//FIXME: segmentation fault dostaje
	vector<char> data = getAudioDataToSend();
	templatePacket.data = new char[data.size()];
	for (int i=0; i<(int)data.size(); i++) templatePacket.data[i]=data[i];
	templatePacket.dataSize = data.size();
}

NoSteg::~NoSteg() {
	// TODO Auto-generated destructor stub
}

RTPPacket NoSteg::getNextPacket() {
	PRNBITS_(4, templatePacket.header->toString());
	templatePacket.header->nextRTPHeader(NARROW_BAND); // changes sequenceNumber and timestamp
	PRNBITS_(4, templatePacket.header->toString());

	// TODO
	RTPPacket packet(templatePacket);
	packet.delay = config->noStegRTPDelay;
	VAR_(2, (int)packet.delay);

	VAR_(2, (int)templatePacket.dataSize);

//	Zatrzymujemy dane z template'a :)
//	packet.data = NULL;
//	packet.dataSize = 0;
	return packet;
}

void NoSteg::putReceivedPacketData(char* data, int dataSize) {
	// TODO
}
