/*
 * Config.h
 *
 *  Created on: Jan 15, 2010
 *      Author: piotrrr
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

using namespace std;

class Config {
public:
	Config(string configFilePath);
	virtual ~Config();

	/**
	 * Ustawione na true jesli to my dzwonimy. Jak nie to odbieramy polaczenie.
	 */
	bool weAreCalling;

	/**
	 * Nasz adres IP
	 */
	string localIP;

	/**
	 * Nasz user id np. stud6
	 */
	string myUser;

	/**
	 * Nasze hasło do proxy
	 */
	string myPass;

	/**
	 * IP proxy
	 */
	string SIPProxyIP;

	/**
	 * The port through which we connect with proxy
	 */
	int SIPProxyPort;

	//ID usera do ktorego dzwonimy
	string calleeID;

	/**
	 * ścieżka do pliku z dziweikiem ktory wysylamy
	 */
	string audioFilePath;

	/**
	 * ścieżka do pliku w którym zapisujemy dane audio przychodzące.
	 * tylko w przypadku odbierania połączenia
	 * TODO: czy w przyadku dzwonienia tez zapisywac dane?
	 */
	string outputAudioFilePath;

	/**
	 * Mówi czy bedziemy przesylac dane steganograficzne czy nie
	 */
	bool doSteg;

	/*
	 *maximum interval between steg sequence
	 */
	int maxStegInterval;

	/**
	 *minimum interval between steg sequence
	 */
	int minStegInterval;

	/**
	 * Steganography sequence from config file
	 */
	string stegSequence;

	/**
	 * Path to file with secret data
	 */
	string stegDataFile;

	/**
	 * the size of RTP packet payload in bytes
	 */
	int RTPPayloadSize;

	/**
	 * opoznienie miedzy pakietami gdy wysylamy normalne dane audio z pliku
	 */
	int noStegRTPDelay;

	/**
	 * Czas pomiedzy odczytywaniem pojednczych pakietow z kolejki pakietow przychodzacych
	 * (razem z rozmiarem kolejki definiuje model kolejki pakietow przychodzacych)
	 */
	int incQueueReadInterval;

	/**
	 * Rozmiar kolejki pakietów przychodzacych
	 */
	int incQueueSize;

};

#endif /* CONFIG_H_ */