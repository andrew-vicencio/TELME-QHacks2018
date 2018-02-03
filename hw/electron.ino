#include "Particle.h"
#include "cellular_hal.h"

STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));

TCPClient cc;
byte srv[] = { 138, 197, 152, 152 };
int pt = 2000;

void req();

void setup() {
    Serial.begin(9600);
    
    Particle.keepAlive(30);
    setADCSampleTime(ADC_SampleTime_3Cycles);
    
	pinMode(D7, OUTPUT);
    
    Wire.begin();
    Wire.setSpeed(CLOCK_SPEED_100KHZ);
    Wire.onRequest(req);
}

void loop () {
    for(;;) Particle.process();
/*
    int e = 0;
    for(int i=1; i<127; i++) {
        Wire.beginTransmission(i);
        e = Wire.endTransmission();
        
        if(!e) {
            Serial.print("Detected @ ");
            Serial.println(i);
        }
        else if(e == 4) {
            Serial.print("Error @ ");
            Serial.println(i);
        }
        else {
            Serial.print(".");
        }
    }
    Serial.println("");
    
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

void req() {
    digitalWrite(D7, HIGH);
    delay(1000);
    digitalWrite(D7, LOW);
    delay(1000);
}
