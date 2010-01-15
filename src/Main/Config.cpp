/*
 * Config.cpp
 *
 *  Created on: Jan 15, 2010
 *      Author: piotrrr
 */

#include "Config.h"
#include "../debug/debug.h"
#include "Main.h"
#include <iostream>
#include <fstream>

Config::Config(string configFile) {

	ifstream cf;
	string callIndicator;
	cf.open(configFile.c_str());
	if (cf.is_open()) {
		getline(cf, callIndicator);
		VAR2(callIndicator);
		if (callIndicator == "calling\n") {
			PRN2("we are calling");
			weAreCalling = true; VAR2(weAreCalling);
			getline(cf, myUser); VAR2(myUser);
			getline(cf, myPass); VAR2(myPass);
			getline(cf, localIP); VAR2(localIP);
			getline(cf, SIPProxyIP); VAR2(SIPProxyIP);
			getline(cf, calleeID); VAR2(calleeID);
			getline(cf, audioFilePath); VAR2(audioFilePath);
		}
		else if (callIndicator == "answering\n") {
			PRN2("we are answering");
		}
		else Main::getMain()->handleError("Configuration file has incorrect format.");
		//cout << line << endl;
		cf.close();
	}

	else Main::getMain()->handleError("Unable to open configuration file: "+configFile);

	callPort = 3333;
	//TODO: usunac i wczytac z pliku
	doSteg = false;

}

Config::~Config() {
	// TODO Auto-generated destructor stub
}