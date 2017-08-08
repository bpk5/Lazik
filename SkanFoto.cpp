#include "SkanFoto.h"


SkanFoto::SkanFoto(int FOTOA, int FOTOB, int poziomSwiatla) {
    this->fotoLpin = FOTOA;
    this->fotoPpin = FOTOB;
    this->pozycja = 85;
    this->swiatlo = 0;
    this->odczytL = 0;
    this->odczytP = 0;
    this->swiatloMax = 0;
    this->pozycjaMax = 85;
    this->poziomSwiatla = poziomSwiatla;
    this->krok = 1;
    this->czas = 0;
}


void SkanFoto::skanujCiag(int pozMin, int pozMax) {
    this->odczytL = analogRead(this->fotoLpin);
    this->odczytP = analogRead(this->fotoPpin);
    // Jeżeli odczytany poziom światła jest większy od ustalonego poziomu to wykonuj skanowania.
    //if ((this->odczytL > poziomSwiatla) || (this->odczytP > poziomSwiatla)) {
        // Porównanie odczytanych danych.
        if (this->odczytL > this->odczytP + 20) {
            // Zabezpieczenie przed nadmiernym wychyleniem.
            if (this->pozycja <= pozMax) {
                this->pozycja = this->pozycja + 2;
            }
        } else if (this->odczytL < this->odczytP - 20) {
            // Zabezpieczenie przed nadmiernym wychyleniem.
            if (this->pozycja >= pozMin) {
                this->pozycja = this->pozycja - 2;
            }
        }
   // }
}


bool SkanFoto::skanujPel(int pozMin, int pozMax, int pozAktualna) {
    bool dzialanie = true;
    int swiatlo = 0;

    switch (this->krok) {
    case 1: // Ustawienie serwomechanizmu.
        this->pozycja = pozMin; // Ustawienie pozycji na pozMin.
        this->czas = millis(); // Pobranie aktualnego czasu.
        this->krok = 2; // Przejście do następnego kroku.
        break;
    case 2: // Czeka na uzyskanie minimalnej pozycji.
        // Odczekanie 250 ms. Czas dla serwa.
        if ((millis() - this->czas) > 250) {
            this->krok = 3; // Przejście do następnego kroku.
        }
        break;
    case 3: // Przeskanowanie i ustalenie pozycji gdzie jest najmocniejszy sygnał.
        // Odczyt fotorezystora.
        swiatlo = analogRead(this->fotoLpin);
        // Wyszukanie najmocniejszego światła.
        if ((this->swiatloMax < swiatlo) && (swiatlo > this->poziomSwiatla)) {
            this->swiatloMax = swiatlo;
            this->pozycjaMax = this->pozycja;
        }
        this->pozycja = this->pozycja + 2;
        // Jeżeli serwo uzyskało maksymalną pozycję przejdz krok dalej.
        if (this->pozycja >= pozMax) {
            // Zapamiętanie w innym polu pozycji gdzie światło było maksymalne.
            // pozycjaMax na koniec jest resetowana dlatego dodatkowe pole.
            this->pozycja = this->pozycjaMax;
            // Zapamiętanie w innym polu poziomu maksymalnego światła po zeskanowaniu całości.
            // swiatloMax na koniec jest resetowane dlatego dodatkowe pole zapamiętujące.
            this->swiatlo = this->swiatloMax;
            // Przed przejściem do następnego kroku pobrać czas. Potrzebne do opóźnienia kroku 4.
            this->czas = millis(); // Pobranie aktualnego czasu.
            this->krok = 4;
        }
        break;
    case 4: // Ustawienie serwa do pozycji z maksymalnym światłem.
        /// TODO tutaj trzeba troszkę poczekać na serwomechanizm. nie ma czasu na obrót do poz max.
        // Przed zakończeniem metody troszkę trzeba odczekać na serwomechanizm, który będzie się ustawiał do poz max.

        // Odczekanie 250 ms. Czas dla serwa.
        if ((millis() - this->czas) > 450) {
            // Reset
            pozycjaMax = 85;
            swiatloMax = 0;
            // Krok na początek.
            this->krok = 1;
            // Zakończyła skanowanie.
            dzialanie = false;
        }

        break;
    }

    return dzialanie;
}


int SkanFoto::getPozycja() {
    return this->pozycja;
}

int SkanFoto::getSwiatlo() {
    return this->swiatlo;
}


int SkanFoto::getOdczytL() {
    return this->odczytL;
}


int SkanFoto::getOdczytP() {
    return this->odczytP;
}



