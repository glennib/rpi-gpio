#include <fstream>
#include <string>
#include <sstream>
#include "Pin.h"
#include <iostream>

#define GPIO_PATH "/sys/class/gpio/"

using namespace std;

Pin::Pin(int n) {
	_gpionum = n;
}

Pin::Pin(int n, Mode m) {
	_gpionum = n;
	setMode(m);
}

Pin::~Pin() {
	set(false);
	unexportPin();
}

bool Pin::exportPin() {
	string exportString = GPIO_PATH "export";
	ofstream exportgpio(exportString.c_str());
	if (exportgpio < 0) {
		throw "OPERATION FAILED: Unable to export GPIO " + gpiostr();
		return false;
	}

	exportgpio << _gpionum;
	exportgpio.close();
	
	return true;
}

bool Pin::unexportPin() {
	string unexportString = GPIO_PATH "unexport";
	ofstream unexportgpio(unexportString.c_str());
	if (unexportgpio < 0) {
		throw "OPERATION FAILED: Unable to unexport GPIO" + gpiostr();
		return false;
	}
	
	unexportgpio << _gpionum;
	unexportgpio.close();
	return true;
}

bool Pin::setMode(Mode m) {
	string setdirString = GPIO_PATH "gpio" + gpiostr() + "/direction";
	ofstream setdirgpio(setdirString.c_str());
	if (setdirgpio < 0) {
		throw "OPERATION FAILED: Unable to set direction on GPIO " + gpiostr();
		return false;
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
		return false;
	}
	
	setdirgpio << dir;
	setdirgpio.close();
	return true;
}

bool Pin::set(bool s) {
	string setvalString = GPIO_PATH "gpio" + gpiostr() + "/value";
	ofstream setvalgpio(setvalString.c_str());
	if (setvalgpio < 0) {
		throw "OPERATION FAILED: Unable to set the value of GPIO " + gpiostr();
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

bool Pin::set(int dutyPeriod) {
	if (!_pwm) {
		if (dutyPeriod > 0) {
			set(true);
		}
		else {
			set(false);
		}
		return true;
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
	return true;
}

bool Pin::set(float duty) {
	int dutyPeriod;
	dutyPeriod = int(duty * _period);
	return set(dutyPeriod);
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

bool Pin::activatePwm(int period) {
	_pwm = true;
	_period = period;
	return true;
}

string Pin::gpiostr() {
	string s = to_string(_gpionum);
	return s;
}
