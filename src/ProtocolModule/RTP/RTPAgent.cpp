/*
 * RTPAgent.cpp
 *
 *  Created on: 2010-01-16
 *      Author: marek
 */

#include "DeserializationException.h"
#include "RTPAgent.h"

RTPAgent::RTPAgent() :
	mutex(0) {
	// utwórz gniazdo
	PRN_(1, "Creating socket...");
	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketfd == -1) {
		throw runtime_error("Can't create UDP socket!");
	}
	VAR(socketfd);

	PRN_(1, "Binding to address...");
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = 0;

	if (bind(socketfd, (sockaddr *) &addr, sizeof(addr)) == -1) {
		throw runtime_error("Can't bind to address!");
	}

	int length = sizeof(addr);
	if (getsockname(socketfd, (sockaddr *) &addr, (socklen_t *) &length) == -1) {
		throw runtime_error("Can't get assigned address!");
	}

	// przygotuj strukturę sockaddr_in (częściowo, reszta przy void setRemotePort, setRemoteAddress)
	addr_in.sin_family = AF_INET;

	//	 ustaw localPort na port gniazda
	localPort = ntohs(addr.sin_port);
	VAR_(1, inet_ntoa(addr.sin_addr));
	VAR_(1, localPort);

	killThread = false;
	pthread_create(&thread, NULL, RTPAgentReceiverThread, (void *) this);
	mutex.V();
}

RTPAgent::~RTPAgent() {
	mutex.P();
	killThread = true;
	mutex.V();

	pthread_join(thread, (void **) NULL);

	PRN_(1, "Closing socket...");
	if (close(socketfd) != 0)
		throw runtime_error("Can't close socket!");
	PRN_(1, "OK");

}

void RTPAgent::setRemoteIP(string ip) {
	remoteIP = ip;
	addr_in.sin_addr.s_addr = inet_addr(remoteIP.c_str());
}

void RTPAgent::setRemotePort(int port) {
	remotePort = port;
	addr_in.sin_port = htons(remotePort);
}

void RTPAgent::sendPacket(RTPPacket& rtpPacket) {
	string s = rtpPacket.toStream();
	sendto(socketfd, s.c_str(), s.length(), 0, (sockaddr *) &addr_in,
			sizeof(addr_in));

	PRN_(2, "-----   RTPPacket sent   -----");
	PRN_(2, s);
	PRN_(2, "--------------------------------");
}

void RTPAgent::recvPacket() {
	// TODO
	sockaddr_in sender;
	unsigned int senderlength;
	char buf[32768];
	if (0 >= recvfrom(socketfd, buf, 10, MSG_PEEK | MSG_DONTWAIT, NULL, NULL)) {
		return;
	}
	int length = recvfrom(socketfd, buf, 32768, 0, (sockaddr *) &sender,
			&senderlength);

	RTPPacket* rtpPacket;
	try {
		rtpPacket = new RTPPacket(buf, length);
	} catch (DeserializationException& e) {
		PRN("Received invalid data");
		return;
	}
	PRN("Received RTP Packet: ");
	VAR(length);
	incomingPackets.pushBack(rtpPacket);
}

void* RTPAgentReceiverThread(void* rtpAgent) {
	RTPAgent* agent = (RTPAgent*) rtpAgent;
	PRN_(1, "receiver thread started");
	while (1) {
		sleep(0.1);
		agent->mutex.P();
		agent->recvPacket();
		if (agent->killThread) {
			agent->mutex.V();
			break;
		}
		agent->mutex.V();
	}
	PRN_(1, "receiver thread stopped");
	return NULL;
}