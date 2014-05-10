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
	/// This part is for Ctrl^C interrupt
	struct sigaction sigStruct;
	sigStruct.sa_handler = sig_handler;
	sigStruct.sa_flags = 0;
	sigemptyset(&sigStruct.sa_mask);

	if (sigaction(SIGINT, &sigStruct, NULL) == -1) {
		cout << "Problem with sigaction" << endl;
		exit(1);
	}
	
	bool inputstate;
	Pin* outputPin = new Pin(4, Pin::Mode::OUT); // To connect LED
	Pin* inputPin = new Pin(7, Pin::Mode::IN); // Connect button with pulldown

	bool prevState = inputPin->get();
	
	while(true) {
		usleep(100000);
		inputstate = inputPin->get();
		
		if (!prevState && inputstate) {
			outputPin->set(!outputPin->get());
		}
		
		prevState = inputstate;
		if (ctrlCPressed) {
			delete inputPin;
			inputPin = 0;
			delete outputPin;
			outputPin = 0;
			
			break;
		}
	}
	
	cout << "\nExiting..." << endl;

	return 0;
}

void sig_handler(int sig) {
	ctrlCPressed = true;
}
