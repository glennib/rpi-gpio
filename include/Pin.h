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
	bool set(int dutyPeriod);
	bool set(float duty);
	bool get();
	int getNumber();
	bool activatePwm(int period);
	bool deactivatePwm();
private:
	int _gpionum;
	string gpiostr();
	bool _pwm;
	int _period;
	int _duty;
};
