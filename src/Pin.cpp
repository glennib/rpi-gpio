#include <fstream>
#include <string>
#include <sstream>
#include "Pin.h"

#define GPIO_PATH "/sys/class/gpio/"

using namespace std;

Pin::Pin(int n) {
	gpionum = n;
}

bool Pin::exportPin() {
	string exportString = GPIO_PATH + "export";
	ofstream exportgpio(exportString.c_str());
	if (exportgpio < 0) {
		cout << "OPERATION FAILED: Unable to export GPIO" << endl;
		return false;
	}

	exportgpio << gpionum;
	exportgpio.close();
	
	return true;
}

bool Pin::unexportPin() {
	string unexportString = GPIO_PATH + "unexport";
	ofstream unexportgpio(unexport_str.c_str());
	if (unexportgpio < 0) {
		cout << "OPERATION FAILED: Unable to unexport GPIO" << endl;
		return false;
	}
	
	unexportgpio << gpionum;
	unexportgpio.close();
	return true;
}

bool Pin::setMode(mode m) {
	string setdirString = GPIO_PATH + "gpio" + gpionum + "/direction";
	ofstream setdirgpio(setdirString.c_str());
	if (setdirgpio < 0) {
		cout << "OPERATION FAILED: Unable to set direction" << endl;
		return false;
	}
	
	string dir;
	if (m = mode.OUT) {
		dir = "out";
	}
	else if (m = mode.IN) {
		dir = "in";
	}
	else {
		cout << "OPERATION FAILED: Unable to set direction - wrong mode" << endl;
		return false;
	}
	
	setdirgpio << dir;
	setdirgpio.close();
	return true;
}

bool Pin::set(bool s) {
	string setvalString = GPIO_PATH + "gpio" + gpionum + "/value";
	ofstream setvalgpio(setvalString.c_str());
	if (setvalgpio < 0) {
		cout << "OPERATION FAILED: Unable to set the value of pin" << endl;
		return false;
	}
	
	string val;
	if (s)
		val = "1";
	else
		val = "0";
	
	setvalgpio << val;
	setvalgpio.close();
	return true;
}

bool Pin::get() {
	string getvalString = GPIO_PATH + "gpio" + gpionum + "/value";
	ifstream getvalgpio(getvalString.c_str());
	if (setvalgpio < 0) {
		throw "OPERATION FAILED: Unable to read value of pin";
	}
	
	string val = "";
	getvalgpio >> val;
	getvalgpio.close();
	if (val == "0")
		return false;
	else if (val == "1")
		return true;
	else
		throw "OPERATION FAILED: Strange value read from pin " + gpionum + ": " + val;
}

int Pin::getNumber() {
	return gpionum;
}

string Pin::gpiostr() {
	return to_string(gpionum);
}
