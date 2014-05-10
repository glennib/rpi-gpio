#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "Pin.h"
#include <unistd.h>
#include <signal.h>

using namespace std;

void sig_handler(int sig);

bool ctrlCPressed = false;

int main() {
	struct sigaction sigStruct;
	sigStruct.sa_handler = sig_handler;
	sigStruct.sa_flags = 0;
	sigemptyset(&sigStruct.sa_mask);

	if (sigaction(SIGINT, &sigStruct, NULL) == -1) {
		cout << "Problem with sigaction" << endl;
		exit(1);
	}

	bool inputstate;
	Pin* outputPin = new Pin(4);
	Pin* inputPin = new Pin(7);
	
	outputPin->exportPin();
	inputPin->exportPin();
	
	cout << "Pins exported" << endl;

	outputPin->setMode(Pin::Mode::OUT);
	inputPin->setMode(Pin::Mode::IN);

	cout << "Set Pin modes" << endl;
	
	while(true) {
		inputstate = inputPin->get();
		
		//if (inputstate) {
		//	cout << "Input is pressed" << endl;
		//}
		//else {
		//	cout << "Input is released" << endl;
		//}
		
		outputPin->set(inputstate);

		if (ctrlCPressed) {
			cout << "Ctrl + C pressed" << endl;
			cout << "Unexporting pins" << endl;
			
			outputPin->unexportPin();
			inputPin->unexportPin();
			
			cout << "Deallocating pin objects" << endl;
			
			delete inputPin;
			inputPin = 0;
			delete outputPin;
			outputPin = 0;
			break;
		}	
	}
	
	cout << "Exiting..." << endl;

	return 0;
}

void sig_handler(int sig) {
	write(0, "\nCtrl^C pressed in sig handler\n", 32);
	ctrlCPressed = true;
}
