#include "SilnikG.h"


SilnikG::SilnikG(int pwmMotorApin, int inMotorA1pin, int inMotorA2pin) {
    // Ustawienie pinów.
    this->pwmMotorApin = pwmMotorApin;
    this->inMotorA1pin = inMotorA1pin;
    this->inMotorA2pin = inMotorA2pin;
    // Zerowanie pól.
    this->predkoscAktualna = 0;
    this->predkoscN = 0;
}


void SilnikG::jedz() {
    int predkoscZam = 0;
    // Jazda do przodu.
    if (this->predkoscAktualna >= 0) {
        // Ustalenie kierunku kręcenia się silnika.
        digitalWrite(this->inMotorA1pin, HIGH);
        digitalWrite(this->inMotorA2pin, LOW);
        // Ustawienie odpowiedniej prędkości silnika
        analogWrite(this->pwmMotorApin, this->predkoscAktualna);
    } else if (this->predkoscAktualna < 0) {
        // Jazda do tyłu.
        // Ustalenie kierunku kręcenia się silnika.
        digitalWrite(this->inMotorA1pin, LOW);
        digitalWrite(this->inMotorA2pin, HIGH);
        // Ustawienie odpowiedniej prędkości silnika
        // Prędkość musi być liczbą dodatnią.
        predkoscZam = (-1 * this->predkoscAktualna);
        analogWrite(this->pwmMotorApin, predkoscZam);
    }
}


void SilnikG::zmieniajPredkosc() {
    if (this->predkoscAktualna < this->predkoscN) {
        // Zmiana prędkości - przyspieszanie.
        this->predkoscAktualna = this->predkoscAktualna + 2;
        // Wywołanie prywatnej metody przekazującej prędkość
        // bezpośrednio do silników.
        this->jedz();
    } else if (this->predkoscAktualna > this->predkoscN) {
        // Zmiana prędkości - wychamowywanie.
        this->predkoscAktualna = this->predkoscAktualna - 2;
        // Wywołanie prywatnej metody przekazującej prędkość
        // bezpośrednio do silników.
        this->jedz();
    }
}


void SilnikG::setPredkoscN(int predkoscN) {
    // Zabezpieczenie przed podaniem wartości z poza zakresu (-100 100).
    if (predkoscN < -100) {
        this->predkoscN = -100;
    } else if (predkoscN > 100) {
        this->predkoscN = 100;
    } else {
        this->predkoscN = predkoscN;
    }
}


void SilnikG::setPredkoscAktualna(int predkoscAktualna) {
    // Zabezpieczenie przed podaniem wartości z poza zakresu (-100 100).
    if (predkoscAktualna < -100) {
        this->predkoscAktualna = -100;
        this->predkoscN = -100;
    } else if (predkoscAktualna > 100) {
        this->predkoscAktualna = 100;
        this->predkoscN = 100;
    } else {
        this->predkoscAktualna = predkoscAktualna;
        this->predkoscN = predkoscAktualna;
    }
    // Natychmiastowe przekazanie wartości do silnika.
    this->jedz();
}


int SilnikG::getPredkoscAktualna() {
    return this->predkoscAktualna;
}


int SilnikG::getPredkoscN() {
    return this->predkoscN;
}

