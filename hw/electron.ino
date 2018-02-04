#include "Particle.h"
#include "cellular_hal.h"

STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));

TCPClient cc;
byte srv[] = { 138, 197, 152, 152 };
int pt = 2000;

void blink();
void lvl(int);

void setup() {
    Serial.begin(9600);
    
    Wire.begin(0x05);
    Wire.onRequest(blink);
    
    pinMode(A0, INPUT);
    pinMode(B0, OUTPUT);
    pinMode(B1, OUTPUT);
    pinMode(B2, OUTPUT);
	pinMode(D7, OUTPUT);
}

void loop() {
    lvl(9000);
    delay(1000);
    lvl(0);
    delay(1000);
}

/*
void loop () {
    delay(4);
    lvl(analogRead(A0));
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
}
*/

void lvl(int l) {
    int hl = 0;
    Serial.println(l);
    if(l > 750) hl |= 1;
    if(l > 900) hl |= 2;
    if(l > 1150) hl |= 4;
    
    digitalWrite(B0, hl&1 ? HIGH : LOW);
    digitalWrite(B1, hl&2 ? HIGH : LOW);
    digitalWrite(B2, hl&4 ? HIGH : LOW);
}

void blink() {
    digitalWrite(D7, HIGH);
    delay(1000);
    digitalWrite(D7, LOW);
    delay(1000);
}
