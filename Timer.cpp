#include "Timer.h"


Timer::Timer() {
    this->interwal = 1000;
    this->czasPoprzedni = 0;
}


bool Timer::cykl() {
    if (this->stan == false) {
        Timer::odlicz();
    }
    return this->stan;
}


void Timer::odlicz() {
    // Pobranie czasu.
    unsigned long czasAktualny = millis();

    if ((czasAktualny - this->czasPoprzedni) > this->interwal) {
        // Czas upłynął.
        this->stan = true;
    } else {
        // Trwa odliczanie.
        this->stan = false;
    }
}


void Timer::setInterwal(int interwal) {
    this->interwal = interwal;
}


void Timer::reset() {
    this->stan = false;
    this->czasPoprzedni = millis();
}


