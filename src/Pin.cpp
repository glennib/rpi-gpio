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


