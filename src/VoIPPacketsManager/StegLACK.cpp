/*
 * StegLACK.cpp
 *
 *  Created on: 2010-01-14
 *      Author: Piotr Gwizda�a
 */

#include "StegLACK.h"
#include "../Main/Main.h"
#include "../debug/debug.h"
#include <cstdlib>
#include <fstream>

StegLACK::StegLACK(Config* cfg) :
	VoIPPacketsManager(cfg) {
	srand((unsigned) time(0));
	string seq = cfg->stegSequence;
	bool done = false;
	while (!done) {
		int pos = seq.find_first_of(" ");
		if (pos == -1)
			done = true;
		stegSeq.push_back(StegSeqElem(seq.substr(0, pos)));
		seq = seq.substr(pos + 1);
	}

	intervalCount = 0;
	seqPosition = 0;
	seqFireInterval = getRandNumber(config->minStegInterval,
			config->maxStegInterval);
	stegTransferDone = false;
	readStegDataToMem();
	VAR_(3, seqFireInterval);
}

void StegLACK::readStegDataToMem() {
	ifstream f(config->stegDataFile.c_str(), ios::in | ios::binary | ios::ate);
	if (f.is_open()) {
		f.seekg(0, ios::beg);
		while (!f.eof()) {
			char c;
			f.get(c);
			stegData.push_back(c);
		}
		f.close();
	} else
		Main::getMain()->handleError(
				"Can't open the steganography input file: "
						+ config->stegDataFile);
}

vector<char> StegLACK::getStegDataToSend() {
	int size = config->RTPPayloadSize;
	vector<char> ret;
	for (int i=1; i<size; i++) {
		lastReadStegByte++;
		if (lastReadStegByte<(int)stegData.size())
			ret.push_back(stegData[lastReadStegByte]);
		else ret.push_back(' ');
	}
	if (lastReadStegByte>=(int)stegData.size()) stegTransferDone = true;
	return ret;
}

StegLACK::~StegLACK() {
	// TODO Auto-generated destructor stub
}

RTPPacket& StegLACK::getNextPacket() {

	vector<char> payloadData;

	//we are doing the sequence
	if ( ! stegTransferDone && intervalCount >= seqFireInterval) {
		StegSeqElem se = stegSeq[seqPosition];
		long delay = getRandNumber(se.intervMin, se.intervMax);
		templatePacket.delay = delay;
		//wysylamy steg packet
		if (se.isStegPacket && ! stegTransferDone) {
			payloadData = getStegDataToSend();
			PRN_(1, "in steg sequence: sending packet: steg, delay="+delay);
		}
		//wysylamy audio packet
		else {
			//dodajemy audio do pakietu:
			payloadData = getAudioDataToSend();
			PRN_(1, "in steg sequence: sending packet: audio, delay="+delay);
		}
		seqPosition++;

		//we finished the sequence...
		if ((unsigned) seqPosition == stegSeq.size()) {
			seqPosition = intervalCount = 0;
			seqFireInterval = getRandNumber(config->minStegInterval,
					config->maxStegInterval);
		}
	}
	//we send the normal package
	else {
		intervalCount++;
		templatePacket.delay = config->noStegRTPDelay;
		PRN_(1, "sending normal packet");
		//dodajemy audio do pakietu:
		payloadData = getAudioDataToSend();
	}

	templatePacket.data = new char[payloadData.size()];
	templatePacket.dataSize = payloadData.size();
	for (int i = 0; i < (int) payloadData.size(); i++) {
		templatePacket.data[i] = payloadData[i];
	}

	//return prepared packet
	return templatePacket;
}

void StegLACK::putReceivedPacketData(char* data, int dataSize) {
	// TODO czy to w ogle potrzebne? czy jakis watek sie tym nie bedzie zajmowal VoIPModule::processIncomingPackets()
}

StegSeqElem::StegSeqElem(string stegSeq) {
	int semicolpos = stegSeq.find_first_of(':');
	string timing = stegSeq.substr(0, semicolpos);
	string type = stegSeq.substr(semicolpos + 1);
	isStegPacket = (type == "S");
	int dashpos = timing.find_first_of('-');
	if (dashpos == -1) {
		intervMin = intervMax = atoi(timing.c_str());
	} else {
		intervMin = atoi(timing.substr(0, dashpos).c_str());
		intervMax = atoi(timing.substr(dashpos + 1).c_str());
	}
}

/**
 * Losuje liczbe w przedziale domknietym <min, max>
 */
long StegLACK::getRandNumber(long min, long max) {
	return (min + (rand() % (max - min + 1)));
}