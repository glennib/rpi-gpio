#include <string>
using namespace std;

class Pin {
public:
	/// Type used for direction of pin used.
	enum Mode {
		OUT,
		IN
	};
	
	/// Constructor with GPIO number as argument. Using this, you will need to set direction.
	Pin(int n);

	/// Constructor with GPIO number and mode as arguments.
	Pin(int n, Mode m);

	/// Deconstructor unexports pin and sets output to 0 if it's an output.
	~Pin();

	/// Tells r-pi that this GPIO is going to be used
	void exportPin();

	/// Removes this GPIO from usage of r-pi.
	void unexportPin();

	/// Sets the direction of GPIO.
	void setMode(Mode m);

	/// Gets the direction of the GPIO.
	Mode getMode();

	/// Sets the output according to the boolean argument.
	void set(bool s);

	/// Sets the PWM dutyPeriod (int is milliseconds). (Not in use yet.)
	void set(int dutyPeriod);

	/// Sets the PWM duty cycle % according to duty (between 0 and 1). (Not in use yet.)
	void set(float duty);

	/// Gets the value of the GPIO.
	bool get();

	/// Gets the GPIO number used.
	int getNumber();

	/// Activates the GPIO to be a PWM output. (Not in use yet.)
	void activatePwm(int period);

	/// Deactivates the GPIO as PWM output. (Not in use yet.)
	void deactivatePwm();

private:
	int _gpionum;
	string gpiostr();
	bool _pwm;
	int _period;
	int _duty;
};
