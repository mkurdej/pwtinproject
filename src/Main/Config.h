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

	//ID usera do ktorego dzwonimy
	string calleeID;

	/**
	 * ścieżka do pliku z dziweikiem ktory wysylamy
	 */
	string audioFilePath;

	/**
	 * Port używany do dzwonienia
	 * TODO: upewnic sie ze tak ma byc
	 */
	int callPort;

	/**
	 * Mówi czy bedziemy przesylac dane steganograficzne czy nie
	 */
	bool doSteg;

};

#endif /* CONFIG_H_ */