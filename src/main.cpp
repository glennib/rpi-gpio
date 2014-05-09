#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "Pin.h"
#include <unistd.h>

using namespace std;

int main() {
	bool inputstate;
	Pin* pin0 = new Pin(4);
	Pin* pin1 = new Pin(7);
	
	pin0->exportPin();
	pin1->exportPin();
	
	cout << "Pins exported" << endl;

	pin0->setMode(Pin::Mode::OUT);
	pin1->setMode(Pin::Mode::IN);

	cout << "Set Pin modes" << endl;
	
	int c = 0;
	while(c++ < 10) {
		usleep(500000);
		inputstate = pin1->get();
		
		if (inputstate) {
			cout << "Input is pressed" << endl;
		}
		else {
			cout << "Input is released" << endl;
		}
		
		pin0->set(inputstate);
	}
	
	pin0->unexportPin();
	pin1->unexportPin();

	return 0;
}
