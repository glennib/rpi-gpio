#include <fstream>
#include <string>
#include <sstream>
#include "Pin.h"
#include <iostream>

#define GPIO_PATH "/sys/class/gpio/"

using namespace std;

Pin::Pin(int n) {
	_gpionum = n;
	exportPin();
}

Pin::Pin(int n, Mode m) {
	_gpionum = n;
	setMode(m);
	exportPin();
}

Pin::~Pin() {
	if (getMode() == Pin::Mode::OUT) {
		set(false);
	}
	unexportPin();
}

void Pin::exportPin() {
	string exportString = GPIO_PATH "export";
	ofstream exportgpio(exportString.c_str());
	if (exportgpio < 0) {
		throw "OPERATION FAILED: Unable to export GPIO " + gpiostr();
	}

	exportgpio << _gpionum;
	exportgpio.close();
}

void Pin::unexportPin() {
	string unexportString = GPIO_PATH "unexport";
	ofstream unexportgpio(unexportString.c_str());
	if (unexportgpio < 0) {
		throw "OPERATION FAILED: Unable to unexport GPIO" + gpiostr();
	}
	
	unexportgpio << _gpionum;
	unexportgpio.close();
}

void Pin::setMode(Mode m) {
	string setdirString = GPIO_PATH "gpio" + gpiostr() + "/direction";
	ofstream setdirgpio(setdirString.c_str());
	if (setdirgpio < 0) {
		throw "OPERATION FAILED: Unable to set direction on GPIO " + gpiostr();
	}
	
	string dir;
	if (m == OUT) {
		dir = "out";
	}
	else if (m == IN) {
		dir = "in";
	}
	else {
		throw "OPERATION FAILED: Unable to set direction (wrong mode) on GPIO " + gpiostr();		
	}
	
	setdirgpio << dir;
	setdirgpio.close();
}

Pin::Mode Pin::getMode() {
	string getDirString = GPIO_PATH "gpio" + gpiostr() + "/direction";
	ifstream getDirGpio(getDirString.c_str());
	if (getDirGpio < 0) {
		throw "OPERATION FAILED: Unable to read direction on GPIO" + gpiostr();
	}
	
	string dir = "";
	getDirGpio >> dir;
	getDirGpio.close();
	
	if (dir == "out") {
		return OUT;
	}
	else if (dir == "in") {
		return IN;
	}
	else {
		throw "Strange value read from direction on GPIO " + gpiostr();
	}
}

void Pin::set(bool s) {
	string setvalString = GPIO_PATH "gpio" + gpiostr() + "/value";
	ofstream setvalgpio(setvalString.c_str());
	if (setvalgpio < 0) {
		throw "OPERATION FAILED: Unable to set the value of GPIO " + gpiostr();
	}
	
	string val;
	if (s)
		val = "1";
	else
		val = "0";
	
	setvalgpio << val;
	setvalgpio.close();
}

void Pin::set(int dutyPeriod) {
	if (!_pwm) {
		if (dutyPeriod > 0) {
			set(true);
		}
		else {
			set(false);
		}
	}
	if (dutyPeriod <= _period) {
		if (dutyPeriod >= 0) {
			_duty = dutyPeriod;
		}
		else {
			_duty = 0;
		}
	}
	else {
		_duty = _period;
	}
}

void Pin::set(float duty) {
	int dutyPeriod;
	dutyPeriod = int(duty * _period);
	set(dutyPeriod);
}

bool Pin::get() {
	string getvalString = GPIO_PATH "gpio" + gpiostr() + "/value";
	ifstream getvalgpio(getvalString.c_str());
	if (getvalgpio < 0) {
		throw "OPERATION FAILED: Unable to read value of GPIO " + gpiostr();
	}
	
	string val = "";
	getvalgpio >> val;
	getvalgpio.close();
	if (val == "0")
		return false;
	else if (val == "1")
		return true;
	else
		throw "OPERATION FAILED: Strange value read from GPIO " + gpiostr() + ": " + val;
}

int Pin::getNumber() {
	return _gpionum;
}

void Pin::activatePwm(int period) {
	_pwm = true;
	_period = period;
}

string Pin::gpiostr() {
	string s = to_string(_gpionum);
	return s;
}
