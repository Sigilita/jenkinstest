#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
// comment to test jenkins3
enum TPin
{
	RED_LED_PIN = 5,
	GREEN_LED_PIN = 6,
	BLUE_LED_PIN = 21
};

void changeColour(int redValue, int blueValue, int greenValue)
{
	softPwmWrite(GREEN_LED_PIN, redValue);
	softPwmWrite(RED_LED_PIN, redValue);
	softPwmWrite(BLUE_LED_PIN, blueValue);
	softPwmWrite(GREEN_LED_PIN, greenValue);
	delay(150);
}

double PosSinWave(int  amplitude, int angle, float frequency) {
	// Creates a Positive sin wave between 0 and amplitude *2
	//
	double radians = M_PI*angle / 180;
	return (amplitude + (amplitude * sin(radians*frequency)));
}
int main(void)
{
	std::cout << "TEST " << std::endl;
	if (wiringPiSetupGpio() == -1) {
		std::cout << wiringPiSetupGpio() << std::endl;
		delay(150);
		exit(1);
	}
	softPwmCreate(RED_LED_PIN, 0, 100);
	softPwmCreate(BLUE_LED_PIN, 0, 100);
	softPwmCreate(GREEN_LED_PIN, 0, 100);
	softPwmWrite(RED_LED_PIN, 0);
	softPwmWrite(BLUE_LED_PIN, 0);
	softPwmWrite(GREEN_LED_PIN, 0);
	softPwmWrite(RED_LED_PIN, 100);
	delay(500);
	softPwmWrite(RED_LED_PIN, 0);
	delay(500);
	softPwmWrite(BLUE_LED_PIN, 100);
	delay(500);
	softPwmWrite(BLUE_LED_PIN, 0);
	delay(500);
	softPwmWrite(GREEN_LED_PIN, 100);
	delay(500);
	softPwmWrite(GREEN_LED_PIN, 0);
	delay(500);

	//  i is the angle. 2 Loops of 360 degrees.
	for (int i = 0; i<720; i = i + 10) {
		std::cout << static_cast<int>(PosSinWave(50, i, 0.5))
			<< " "
			<< static_cast<int>(PosSinWave(50, i, 1))
			<< " "
			<< static_cast<int>(PosSinWave(50, i, 2))
			<< std::endl;
		changeColour(static_cast<int>(PosSinWave(50, i, 0.5)),
			static_cast<int>(PosSinWave(50, i, 1)),
			static_cast<int>(PosSinWave(50, i, 2)));
	}
	softPwmWrite(RED_LED_PIN, 0);
	softPwmWrite(BLUE_LED_PIN, 0);
	softPwmWrite(GREEN_LED_PIN, 0);

	exit(0);
}
