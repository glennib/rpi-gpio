#include <string>
using namespace std;

class Pin {
public:

	enum Mode {
		OUT,
		IN
	};

	Pin(int n);
	bool exportPin();
	bool unexportPin();
	bool setMode(Mode m);
	bool set(bool s);
	bool get();
	int getNumber();

private:
	int gpionum;
	string gpiostr();
};
