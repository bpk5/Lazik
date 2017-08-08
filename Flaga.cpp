#include "Flaga.h"


Flaga::Flaga() {
    this->kierunek = 2; // Jazda do przodu.

    this->flaga[0] = false; // Jazda do przodu.
    this->flaga[1] = false; // Jazda do tyłu.
    this->flaga[2] = false; // Obrót w lewo.
    this->flaga[3] = false; // Obrót w prawo.
    this->flaga[4] = false; // Zatrzymaj - wykonywana jest metoda zatrzymująca.
    this->flaga[5] = true; // Zatrzymany - pojazd nie jedzie, zatrzymał się.
    this->flaga[6] = false; // Skanowanie pełne foto.
    this->flaga[7] = false; // Skanowanie ciągłe foto.
    this->flaga[8] = true; // Skanowanie odległości.
    this->flaga[9] = false; // Omijanie.
    this->flaga[10] = false; // Podjedź do przodu.
    this->flaga[11] = false; // Obróć o 180 stopni.
    this->flaga[12] = true; // Wywołanie skanowania pełnego.
    this->flaga[13] = false; // Podnoszenie wideł.
    this->flaga[14] = false; // Reset wideł.
    this->flaga[15] = true; // Czujnik przechyłowy na widłach.
    this->flaga[16] = false;
    this->flaga[17] = false;
    this->flaga[18] = false;
    this->flaga[19] = false;
    //this->flaga[16] = true; // Czujnik ograniczający podnoszenie wideł.
}


void Flaga::setFlaga(int nr, bool wartosc) {
    this->flaga[nr] = wartosc;
}


bool Flaga::getFlaga(int nr) {
    return this->flaga[nr];
}


void Flaga::setKierunek(int kierunek) {
    this->kierunek = kierunek;
}


int Flaga::getKierunek() {
    return this->kierunek;
}


void Flaga::ustawPoczatkowe() {
    this->flaga[0] = false; // Jazda do przodu.
    this->flaga[1] = false; // Jazda do tyłu.
    this->flaga[2] = false; // Obrót w lewo.
    this->flaga[3] = false; // Obrót w prawo.
    this->flaga[4] = false; // Zatrzymaj - wykonywana jest metoda zatrzymująca.
    this->flaga[5] = true; // Zatrzymany - pojazd nie jedzie, zatrzymał się.
    this->flaga[6] = false; // Skanowanie pełne foto.
    this->flaga[7] = false; // Skanowanie ciągłe foto.
    this->flaga[8] = true; // Skanowanie odległości.
    this->flaga[9] = false; // Omijanie.
    this->flaga[10] = false; // Podjedź do przodu.
    this->flaga[11] = false; // Obróć o 180 stopni.
    this->flaga[12] = true; // Wywołanie skanowania pełnego.
    this->flaga[13] = false; // Podnoszenie wideł.
    this->flaga[14] = false; // Reset wideł.
    this->flaga[15] = true; // Czujnik przechyłowy na widłach.
    //this->flaga[16] = true; // Czujnik ograniczający podnoszenie wideł.
}


void Flaga::wylaczenie() {
    this->flaga[0] = false; // Jazda do przodu.
    this->flaga[1] = false; // Jazda do tyłu.
    this->flaga[2] = false; // Obrót w lewo.
    this->flaga[3] = false; // Obrót w prawo.
    this->flaga[4] = true; // Zatrzymaj - wykonywana jest metoda zatrzymująca.
    this->flaga[5] = false; // Zatrzymany - pojazd nie jedzie, zatrzymał się.
    this->flaga[6] = false; // Skanowanie pełne foto.
    this->flaga[7] = false; // Skanowanie ciągłe foto.
    this->flaga[8] = false; // Skanowanie odległości.
    this->flaga[9] = false; // Omijanie.
    this->flaga[10] = false; // Podjedź do przodu.
    this->flaga[11] = false; // Obróć o 180 stopni.
    this->flaga[12] = false; // Wywołanie skanowania pełnego.
    this->flaga[13] = false; // Podnoszenie wideł.
    this->flaga[14] = false; // Reset wideł.
    this->flaga[15] = false; // Czujnik przechyłowy na widłach.
    //this->flaga[16] = false; // Czujnik ograniczający podnoszenie wideł.
}
