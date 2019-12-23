#include <Arduino.h>
#include "User_Setup.h"

const byte rampsDir = 19;
const byte rampsSterp = 18;
const byte pin_Adir = 13;
const byte pin_Astep = 12;
const byte endStopZ = 11;
const byte endStopY = 10;
const byte endStopX = 9;
const byte enable = 8;
const byte endStopA = A0;
const byte pin_Zdir = 7;
const byte pin_Ydir = 6;
const byte pin_Xdir = 5;
const byte pin_Zstep = 4;
const byte pin_Ystep = 3;
const byte pin_Xstep = 2;
const byte updir = 0;

byte disableA = 0;
byte disableX = 0;
byte disableY = 0;
byte disableZ = 0;

void step () {
    // legim el estat del pins i els copiem els demes pololus
    byte dirStatus = digitalRead(rampsDir);
    digitalWrite(pin_Adir, dirStatus);
    digitalWrite(pin_Zdir, dirStatus);
    digitalWrite(pin_Xdir, dirStatus);
    digitalWrite(pin_Ydir, dirStatus);

    //fem el mateix amb el step pero desabilitem les motors en cas de detectar el seu final de cursa
    byte step = digitalRead(rampsSterp);
    if (disableA) {
        digitalWrite(pin_Astep, step);
    } else {
        digitalWrite(pin_Astep, 0);
    }

    if (disableX) {
        digitalWrite(pin_Xstep, step);
    } else {
        digitalWrite(pin_Xstep, 0);
    }

    if (disableY) {
        digitalWrite(pin_Zstep, step);
    } else {
        digitalWrite(pin_Zstep, 0);
    }

    if (disableZ) {
        digitalWrite(pin_Ystep, step);
    } else {
        digitalWrite(pin_Ystep, 0);
    }

}


void setup() {

    // definim els pins de entreada per controlar els step i pas que ens donara la ramps
    pinMode(enable, INPUT);
    pinMode(rampsDir, INPUT);
    pinMode(rampsSterp, INPUT);

    // entradas dels finals de cursa el endStop A va conectat el abort
    pinMode(endStopX, INPUT);
    pinMode(endStopY, INPUT);
    pinMode(endStopZ, INPUT);
    pinMode(endStopA, INPUT);


    // deminim els pins de surtida
    pinMode(pin_Xdir, OUTPUT);
    pinMode(pin_Xstep, OUTPUT);
    pinMode(pin_Ydir, OUTPUT);
    pinMode(pin_Ystep, OUTPUT);
    pinMode(pin_Zdir, OUTPUT);
    pinMode(pin_Zstep, OUTPUT);
    pinMode(pin_Adir, OUTPUT);
    pinMode(pin_Astep, OUTPUT);

    // interupcio cuan el pin 18 cavi tirarem la funcio stem per copiar els pasos de la ramps a la placa
    // de control
    attachInterrupt(digitalPinToInterrupt(rampsSterp), step, CHANGE);
}

void loop() {

    if (digitalRead(rampsDir) == updir) {
        disableA = digitalRead(endStopA);
        disableX = digitalRead(endStopX);
        disableY = digitalRead(endStopY);
        disableZ = digitalRead(endStopZ);
    } else {
        disableZ = 0;
        disableY = 0;
        disableX = 0;
        disableA = 0;
    }
}


