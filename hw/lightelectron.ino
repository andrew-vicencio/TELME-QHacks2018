#include "Particle.h"
#include "cellular_hal.h"

#include "sample.h"

#define LEN 512

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
            cc.write(sample_wav, sample_wav_len);
            /*
            byte buf[LEN];
            long r;
            for(int i=0; i<(sample_wav_len/LEN); i++) {
                digitalWrite(D0, HIGH);
                for(int j=0; j<LEN && (i*LEN)+j<sample_wav_len; j++) {
                    Serial.println((i*LEN)+j);
                    buf[j] = sample_wav[(i*LEN)+j];
                    level(buf[j]);
                    r = j;
                    delay(2);
                }
                level((uint8_t)0);
                //cc.write(buf, r);
                digitalWrite(D0, LOW);
            }
            */
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
    if(l > 0x00) hl |= 1;
    if(l > 0x40) hl |= 2;
    if(l > 0x80) hl |= 4;
    if(l > 0xC0) hl |= 8;
    if(l > 0xF0) hl |= 16;
    
    digitalWrite(B0, hl&1 ? HIGH : LOW);
    digitalWrite(B1, hl&2 ? HIGH : LOW);
    digitalWrite(B2, hl&4 ? HIGH : LOW);
    digitalWrite(B3, hl&8 ? HIGH : LOW);
    digitalWrite(B4, hl&16 ? HIGH : LOW);
}
