#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "Pin.h"
#include <unistd.h>
#include <signal.h>

using namespace std;

/// For Ctrl^C interrupt
void sig_handler(int sig);
bool ctrlCPressed = false;

int main() {
	cout << "Running..." << endl;
	clog << "light.app started running" << endl;
	/// This part is for Ctrl^C interrupt
	struct sigaction sigStruct;
	sigStruct.sa_handler = sig_handler;
	sigStruct.sa_flags = 0;
	sigemptyset(&sigStruct.sa_mask);

	if (sigaction(SIGINT, &sigStruct, NULL) == -1) {
		cout << "Problem with sigaction" << endl;
		clog << "Problem with sigaction" << endl;
		exit(1);
	}
	
	bool inputstate;
	Pin* outputPin = new Pin(4, Pin::Mode::OUT); // To connect LED
	Pin* inputPin = new Pin(7, Pin::Mode::IN); // Connect button with pulldown
	
	clog << "Declared input and output pins." << endl;

	bool prevState = inputPin->get();
	
	while(true) {
		usleep(100000);
		inputstate = inputPin->get();
		
		if (!prevState && inputstate) {
			outputPin->set(!outputPin->get());
			clog << "Toggle." << endl;
		}
		
		prevState = inputstate;
		if (ctrlCPressed) {
			clog << "Ctrl + C pressed." << endl;
			delete inputPin;
			inputPin = 0;
			clog << "Deleted input pin." << endl;
			delete outputPin;
			outputPin = 0;
			clog << "Deleted output pin." << endl;
			
			clog << "Exiting while loop." << endl;
			break;
		}
	}
	
	cout << "\nExiting..." << endl;
	clog << "Exiting..." << endl;

	return 0;
}

void sig_handler(int sig) {
	ctrlCPressed = true;
}
