#include "SilnikKrokowy.h"


SilnikKrokowy::SilnikKrokowy(int PA, int PB, int PC, int PD, int LATCHPIN, int DATAPIN, int CLOCKPIN) {
    this->dly = 6;
    this->iloscKrokow = 1000; // to będzie niepotrzebne.
    this->PA = PA;
    this->PB = PB;
    this->PC = PC;
    this->PD = PD;
    this->LATCHPIN = LATCHPIN;
    this->DATAPIN = DATAPIN;
    this->CLOCKPIN = CLOCKPIN;
}


void SilnikKrokowy::widlyDoGory() {
    // Napięcie na pin pd
    digitalWrite(this->LATCHPIN, LOW);
    shiftOut(this->DATAPIN, this->CLOCKPIN, MSBFIRST, this->PD);
    digitalWrite(this->LATCHPIN, HIGH);

    delay(this->dly);
    // Napięcie na pin pc
    digitalWrite(this->LATCHPIN, LOW);
    shiftOut(this->DATAPIN, this->CLOCKPIN, MSBFIRST, this->PC);
    digitalWrite(this->LATCHPIN, HIGH);

    delay(this->dly);
    // Napięcie na pin pb
    digitalWrite(this->LATCHPIN, LOW);
    shiftOut(this->DATAPIN, this->CLOCKPIN, MSBFIRST, this->PB);
    digitalWrite(this->LATCHPIN, HIGH);

    delay(this->dly);
    // Napięcie na pin pa
    digitalWrite(this->LATCHPIN, LOW);
    shiftOut(this->DATAPIN, this->CLOCKPIN, MSBFIRST, this->PA);
    digitalWrite(this->LATCHPIN, HIGH);

    delay(this->dly);
    // Wyłączenie napięcia.
    digitalWrite(this->LATCHPIN, LOW);
    shiftOut(this->DATAPIN, this->CLOCKPIN, MSBFIRST, 0);
    digitalWrite(this->LATCHPIN, HIGH);
}


void SilnikKrokowy::widlyDoDolu() {
    // Napięcie na pin pa
    digitalWrite(this->LATCHPIN, LOW);
    shiftOut(this->DATAPIN, this->CLOCKPIN, MSBFIRST, this->PA);
    digitalWrite(this->LATCHPIN, HIGH);

    delay(this->dly);
    // Napięcie na pin pb
    digitalWrite(this->LATCHPIN, LOW);
    shiftOut(this->DATAPIN, this->CLOCKPIN, MSBFIRST, this->PB);
    digitalWrite(this->LATCHPIN, HIGH);

    delay(this->dly);
    // Napięcie na pin pc
    digitalWrite(this->LATCHPIN, LOW);
    shiftOut(this->DATAPIN, this->CLOCKPIN, MSBFIRST, this->PC);
    digitalWrite(this->LATCHPIN, HIGH);

    delay(this->dly);
    // Napięcie na pin pd
    digitalWrite(this->LATCHPIN, LOW);
    shiftOut(this->DATAPIN, this->CLOCKPIN, MSBFIRST, this->PD);
    digitalWrite(this->LATCHPIN, HIGH);

    delay(this->dly);
    // Wyłączenie napięcia.
    digitalWrite(this->LATCHPIN, LOW);
    shiftOut(this->DATAPIN, this->CLOCKPIN, MSBFIRST, 0);
    digitalWrite(this->LATCHPIN, HIGH);
}
