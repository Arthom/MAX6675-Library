#include <iostream>
#include <unistd.h>
#include <wiringPi.h>

#include "max6675.h"

void MAX6675::begin(uint8_t csPin = 0, uint8_t misoPin = 0, uint8_t sckPin = 0) {
	MAX6675::CS = csPin;
	MAX6675::MISO = misoPin;
	MAX6675::SCK = sckPin;

	wiringPiSetup();

	pinMode(MAX6675::CS, OUTPUT);
	pinMode(MAX6675::SCK, OUTPUT);
	pinMode(MAX6675::MISO, INPUT);

	digitalWrite(MAX6675::CS, HIGH);

	usleep(500 * 1000);
}

char MAX6675::SPIRead(void) {
	char d = 0;

	for (int i = 7; i >= 0; i--) {
		digitalWrite(MAX6675::SCK, LOW);
		usleep(1000); //dont need to multiply by 1
		if (digitalRead(MAX6675::MISO))
			d |= (1 << i);
		digitalWrite(MAX6675::SCK, HIGH);
		usleep(1000); //dont need to multiply by 1
	}

	return d;
}

double MAX6675::convertToCelsius(void) {
	uint16_t v;

	digitalWrite(MAX6675::CS, LOW);
	usleep(1 * 1000);

	v = MAX6675::SPIRead();
	v <<= 8;
	v |= MAX6675::SPIRead();

	if (v & 0x4)
		return -1;

	v >>= 3;
	return v * 0.25;
}
