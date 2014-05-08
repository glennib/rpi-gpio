#include <string>
using namespace std;

class Pin {
public:

	enum mode {
		OUT,
		IN
	};

	Pin(int n);
	bool exportPin();
	bool unexportPin();
	bool setMode(mode m);
	bool set(bool s);
	bool get()
	int getNumber();

private:
	int gpionum;
	string gpiostr();
};

