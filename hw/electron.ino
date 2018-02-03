#include "cellular_hal.h"

#define B_NU 5
#define B_LN 1000
#define S_RT 8000
#define M_SP 30000

STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));

TCPClient cc;
byte srv[] = { 138, 197, 152, 152 };
int pt = 2000;

byte b[B_NU][B_LN];

void setup() {
    Serial.begin(9600);
    Particle.keepAlive(30);
    setADCSampleTime(ADC_SampleTime_3Cycles);
	pinMode(D7, OUTPUT);
}

void loop () {
    Serial.print("Sample: ");
    Serial.println(analogRead(A0)<<2);
/*
    if(!x) {
        Serial.println("Connecting");
        if(cc.connect(srv, pt)) {
            Serial.println("Connected");
            cc.write(&b, 1);
            x++;
        }
        Serial.println("End");
        cc.stop();
    }
*/
}
