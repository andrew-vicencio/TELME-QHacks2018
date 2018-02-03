#include "cellular_hal.h"

STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));

void setup() {
    Particle.keepAlive(30);
	pinMode(D7, OUTPUT);
}

void loop () {
    digitalWrite(D7, HIGH);
	delay(1000);
	digitalWrite(D7, LOW);
	delay(1000);
}
