#include "CzujnikOdl.h"


CzujnikOdl::CzujnikOdl(int TRIG, int ECHO, int LATCHPIN,
                       int DATAPIN, int CLOCKPIN) {
    this->trig = TRIG;
    this->echo = ECHO;
    this->larchPin = LATCHPIN;
    this->dataPin = DATAPIN;
    this->clockPin = CLOCKPIN;
}


int CzujnikOdl::podajOdleglosc() {
    // Ustawienie stanu wysokiego na 10 uS - impuls inicjalizujacy
    // Ustawienie układu 74HC595N.
    // MSBFIRST - liczenie od pierwszego pinu.
    digitalWrite(this->larchPin, LOW);
    shiftOut(this->dataPin, this->clockPin, MSBFIRST, this->trig);
    digitalWrite(this->larchPin, HIGH);
    delayMicroseconds(10);
    // Ustawienie ukłądu 74HC595N.
    digitalWrite(this->larchPin, LOW);
    shiftOut(this->dataPin, this->clockPin, MSBFIRST, 0);
    digitalWrite(this->larchPin, HIGH);
    unsigned long czas = pulseIn(this->echo, HIGH);
    //szerokość odbitego impulsu w uS podzielone przez 58 to odleglosc w cm
    int odleglosc = czas / 58.00;
    return odleglosc;
}


