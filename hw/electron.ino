/* QHacks 2018
 *
 * Audio Reference:
 * from https://github.com/rickkas7/photonAudioSample1/
 */
 
#include "Particle.h"
#include "cellular_hal.h"
#include "spk.h"

STARTUP(cellular_credentials_set("isp.telus.com", "", "", NULL));

// Audio Buffer Constants
#define AB_SIZE 1024
#define AB_BUFS 16

#define SR 16000

#define TI 20000

IntervalTimer T;

void rec();
void lvl(int);
void blink();
void start();

TCPClient cc;
byte host[] = { 138, 197, 152, 152 };
int port = 2000;

byte ab[AB_BUFS][AB_SIZE];
uint16_t x, y;

unsigned long ref;

byte state = 0;

void setup() {
    Serial.begin(9600);
    
    pinMode(A0, INPUT);
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
    /*
    delay(4);
    lvl(analogRead(A0));
    return;
    */
    delay(500);
    for(int i=0; i<state; i++) {
        digitalWrite(D0, HIGH);
        delay(500);
        digitalWrite(D0, LOW);
        delay(500);
    }
    
    digitalWrite(D0, HIGH);
    delay(1000);
    digitalWrite(D0, LOW);
        
    switch(state) {
        case 0:
            x = y = 0;
            for(int i=0; i<AB_BUFS; i++)
                for(int j=0; j<AB_SIZE; j++)
                    ab[i][j] = 0;
            state++;
            break;
        case 1:
            break;
        case 2:
            if(cc.connect(host, port))
                state++;
            else
                delay(5000);
            break;
        case 3:
            digitalWrite(D7, HIGH);
            T.begin(rec, 1000000 / SR, uSec);
            ref = millis();
            state++;
            break;
        case 4:
            if(x >= AB_SIZE) {
                if(y < AB_BUFS)
                    cc.write(ab[y++], AB_SIZE);
                else
                    state++;
                x = 0;
            }
            else if(millis() - ref >= TI) {
                cc.write(ab[y], x);
                state++;
            }
            break;
        case 5:
            T.end();
            cc.stop();
            digitalWrite(D7, LOW);
            break;
    }
}

void start() {
    if(state == 1)
        state++;
}

void rec() {
    if(y < AB_BUFS && x < AB_SIZE) {
        ab[y][x] = (uint8_t) (analogRead(A0)>>2);
        lvl(ab[y][x++]<<2);
    }
}

/*
void loop () {
    int e = 0;
    for(int i=1; i<127; i++) {
        WirebeginTransmission(i);
        e = Wire.endTransmission();
        
        f(!e) {
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
    if(l > 500) hl |= 1;
    if(l > 600) hl |= 2;
    if(l > 700) hl |= 4;
    if(l > 800) hl |= 8;
    if(l > 900) hl |= 16;
    
    digitalWrite(B0, hl&1 ? HIGH : LOW);
    digitalWrite(B1, hl&2 ? HIGH : LOW);
    digitalWrite(B2, hl&4 ? HIGH : LOW);
    digitalWrite(B3, hl&8 ? HIGH : LOW);
    digitalWrite(B4, hl&16 ? HIGH : LOW);
}

void blink() {
    digitalWrite(D7, HIGH);
    delay(1000);
    digitalWrite(D7, LOW);
    delay(1000);
}
