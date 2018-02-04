#include "Particle.h"
#include "cellular_hal.h"

#include "sample.h"

void start(); void level(int);

STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));

TCPClient cc;
byte host[] = { 138, 197, 152, 152 };
int port = 2000;

byte state = 0;

void setup() {
    Serial.begin(9600);
    pinMode(B0, OUTPUT);
    pinMode(B1, OUTPUT);
    pinMode(B2, OUTPUT);
    pinMode(B3, OUTPUT);
    pinMode(B4, OUTPUT);
    pinMode(D0, OUTPUT);
	pinMode(D7, OUTPUT);
    pinMode(C0, INPUT);
    
    attachInterrupt(C0, start, CHANGE);
}

void loop() {
    switch(state) {
        case 0:
            digitalWrite(D0, HIGH);
            delay(500);
            digitalWrite(D0, LOW);
            delay(500);
            break;
        case 1:
            if(cc.connect(host, port))
                state++;
            else
                delay(5000);
            break;
        case 2:
            digitalWrite(D7, HIGH);
            byte buf[1024];
            long r;
            for(int i=0; i<44; i++) {
                digitalWrite(D0, HIGH);
                for(int j=0; j<1024; j++) {
                    Serial.println((i*1024)+j);
                    buf[j] = sample_wav[(i*1024)+j];
                    level(buf[j]);
                    r = j;
                    delay(25);
                }
                cc.write(buf, r);
                digitalWrite(D0, LOW);
            }
            cc.stop();
            digitalWrite(D7, LOW);
            state = 0;
            break;
    }
}

void start() {
    if(state == 0)
        state++;
}

void level(uint8_t l) {
    int hl = 0;
    if(l > 0x10) hl |= 1;
    if(l > 0x20) hl |= 2;
    if(l > 0x40) hl |= 4;
    if(l > 0x80) hl |= 8;
    if(l > 0xA0) hl |= 16;
    
    digitalWrite(B0, hl&1 ? HIGH : LOW);
    digitalWrite(B1, hl&2 ? HIGH : LOW);
    digitalWrite(B2, hl&4 ? HIGH : LOW);
    digitalWrite(B3, hl&8 ? HIGH : LOW);
    digitalWrite(B4, hl&16 ? HIGH : LOW);
}
