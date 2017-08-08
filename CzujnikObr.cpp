#include "CzujnikObr.h"


CzujnikObr::CzujnikObr(int LICZ) {
    this->liczPin = LICZ;
    this->flaga = false;
    this->iloscObr = 0;
}


unsigned long CzujnikObr::zliczObroty() {
    int wynik = digitalRead(this->liczPin);

    if ((wynik == 1) && (this->flaga == true)) {
        this->iloscObr++;
        this->flaga = false;
    } else if ((wynik == 0) && (this->flaga == false)) {
        this->flaga = true;
    }

    return this->iloscObr;
}


void CzujnikObr::zerujLicznik() {
    this->iloscObr = 0;
}
