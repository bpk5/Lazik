#include "Manewry.h"


Manewry::Manewry(CzujnikObr* czujnikObrL, CzujnikObr* czujnikObrP,
                 SilnikG* silnikL, SilnikG* silnikP, int pozycjaSF) {
    this->czujnikObrL = czujnikObrL;
    this->czujnikObrP = czujnikObrP;
    this->silnikL = silnikL;
    this->silnikP = silnikP;
    this->pozycjaSF = pozycjaSF;
    this->predkosc = 0;
    this->predkoscKorekta = 0;
    this->predkoscManewry = 35;
    this->obroty = 15;
    this->silnikOn = false;
    this->flagaReset = true;
}


void Manewry::jedzZaSwiatlem(int obrotyL, int obrotyP, int pozycjaSF) {
    /// TODO dopisać zliczanie obrotów, nie wiadomo czy to będzie działać
    /// pobawić się z ustawieniami prędkości. Wartość zero zatrzymuje i szarpie ale szybciej działa.
    // Kod ustawia łazik do pozycji gdzie serwo foto będzie najbliżej pozycji 90.
    if (pozycjaSF < 88) {
        // lewy jedzie
        // prawy zatrzymaj
        this->silnikL->setPredkoscN(this->predkoscManewry);
        this->silnikP->setPredkoscN(0);
    } else if (pozycjaSF > 92) {
        // lewy zatrzymany
        // prawy jedzie
        this->silnikL->setPredkoscN(0);
        this->silnikP->setPredkoscN(this->predkoscManewry);
    } else {
        // Dwa silniki prosto
        this->silnikL->setPredkoscN((this->predkoscManewry));
        this->silnikP->setPredkoscN(this->predkoscManewry);
    }
}


void Manewry::jedzProsto(int obrotyL, int obrotyP) {
    // Kod odpowiada za korygowanie prędkości silników tak aby kręciły się jednakowo.
    if (obrotyL > obrotyP) {
        this->silnikL->setPredkoscN((this->predkosc - 10));
        this->silnikP->setPredkoscN(this->predkosc + 10);
    } else if (obrotyL < obrotyP) {
        this->silnikL->setPredkoscN((this->predkosc + 10));
        this->silnikP->setPredkoscN(this->predkosc - 10);
    } else {
        this->silnikL->setPredkoscN(this->predkosc);
        this->silnikP->setPredkoscN(this->predkosc);
    }
}


bool Manewry::zatrzymaj() {
    bool dzialanie = true;

    // Łagodne zatrzymanie silników
    this->silnikL->setPredkoscN(0);
    this->silnikP->setPredkoscN(0);

    // Jeżeli silniki się zatrzymały:
    if ((this->silnikL->getPredkoscAktualna() == 0) && (this->silnikP->getPredkoscAktualna() == 0)) {
        // Zerowanie liczników obrotów.
        this->czujnikObrL->zerujLicznik();
        this->czujnikObrP->zerujLicznik();
        dzialanie = false;
    }

    return dzialanie;
}


bool Manewry::obrocLewo(int obrotyL, int obrotyP, int ileRazy = 1) {
    bool dzialanie = true;
    bool l = false;
    bool p = false;

    // Jeżeli silniki wyłączone to je włącz.
    if (!this->silnikOn) {
        // Ustawienie flagi silnik włączony.
        this->silnikOn = true;
        // Ustawienie wszystkich prędkości, dla pewności Aktualna i N.
        this->silnikL->setPredkoscAktualna(-1 * this->predkoscManewry);
        this->silnikL->setPredkoscN(-1 * this->predkoscManewry);
        this->silnikP->setPredkoscAktualna(this->predkoscManewry);
        this->silnikP->setPredkoscN(this->predkoscManewry);
    }

    // Kręć do momentu uzyskania odpowiedniej ilości obrotów.
    if (obrotyL >= (this->obroty * ileRazy)) {
        // Wyzerowanie wszystkich prędkości.
        this->silnikL->setPredkoscAktualna(0);
        this->silnikL->setPredkoscN(0);
        l = true;
    }

    // Kręć do momentu uzyskania odpowiedniej ilości obrotów.
    if (obrotyP >= (this->obroty * ileRazy)) {
        // Wyzerowanie wszystkich prędkości.
        this->silnikP->setPredkoscAktualna(0);
        this->silnikP->setPredkoscN(0);
        p = true;
    }

    // Jeżeli dwa silniki zatrzymały się to wykonaj końcowe ustawienia i zakończ wykonywanie metody.
    if (l && p) {
        // Zerowanie licznika obrotów.
        this->czujnikObrP->zerujLicznik();
        this->czujnikObrL->zerujLicznik();
        dzialanie = false;
        this->silnikOn = false;
    }

    return dzialanie;
}


bool Manewry::obrocPrawo(int obrotyL, int obrotyP) {
    bool dzialanie = true;
    bool l = false;
    bool p = false;

    // Jeżeli silniki wyłączone to je włącz.
    if (!this->silnikOn) {
        // Ustawienie flagi silnik włączony.
        this->silnikOn = true;
        // Ustawienie wszystkich prędkości, dla pewności Aktualna i N.
        this->silnikL->setPredkoscAktualna(this->predkoscManewry);
        this->silnikL->setPredkoscN(this->predkoscManewry);
        this->silnikP->setPredkoscAktualna(-1 * this->predkoscManewry);
        this->silnikP->setPredkoscN(-1 * this->predkoscManewry);
    }

    // Kręć do momentu uzyskania odpowiedniej ilości obrotów.
    if (obrotyL >= this->obroty) {
        // Wyzerowanie wszystkich prędkości.
        this->silnikL->setPredkoscAktualna(0);
        this->silnikL->setPredkoscN(0);
        l = true;
    }

    // Kręć do momentu uzyskania odpowiedniej ilości obrotów.
    if (obrotyP >= this->obroty) {
        // Wyzerowanie wszystkich prędkości.
        this->silnikP->setPredkoscAktualna(0);
        this->silnikP->setPredkoscN(0);
        p = true;
    }

    // Jeżeli dwa silniki zatrzymały się.
    if (l && p) {
        // Zerowanie licznika obrotów.
        this->czujnikObrP->zerujLicznik();
        this->czujnikObrL->zerujLicznik();
        dzialanie = false;
        this->silnikOn = false;
    }

    return dzialanie;
}

bool Manewry::obroc180(int obrotyL, int obrotyP) {
    // Wywołuje metodę obrót w lewo z ilością obróceń 2.
    return this->obrocLewo(obrotyL, obrotyP, 2);
}


bool Manewry::podjedz(int obrotyL, int obrotyP) {
    bool l = false;
    bool p = false;
    bool dzialanie = true;

    // Jednorazowe wyzerowanie spowoduje że do wykonania manewru nie potrzebne jest
    // zatrzymanie pojazdu. Zostaną tylko w biegu zresetowane wartości.
    // Wykonanie jednorazowego resetu obrotów.
    if (this->flagaReset == true) {
        this->czujnikObrP->zerujLicznik(); // zerowanie licznika
        this->czujnikObrL->zerujLicznik(); // zerownaie licznika
        obrotyL = 0; // Zerowanie
        obrotyP = 0; // Zerowanie
        this->flagaReset = false; // Wyłączenie resetowania obrotów na czas działania metody.
    }

    // Jeżeli nie osiągnięto ustalonej ilości obrotów to kręć lewym silnikiem.
    if (obrotyL < 20) {
        this->silnikL->setPredkoscN(this->predkoscManewry);
    } else {
        // Płynne zatrzymanie.
        this->silnikL->setPredkoscN(0);
        l = true;
    }
    // Jeżeli nie osiągnięto ustalonej ilości obrotów to kręć prawym silnikiem.
    if (obrotyP < 20) {
        this->silnikP->setPredkoscN(this->predkoscManewry);
    } else {
        // Płynne zatrzymanie.
        this->silnikP->setPredkoscN(0);
        p = true;
    }

    // Jeżeli dwa silniki wykonały odpowiednią ilość obrotów to dzialanie na false.
    if ((l == true) && (p == true)) {
        this->flagaReset = true; // Włączenie flagi do resetu przy kolejnym wywołaniu metody.
        this->czujnikObrP->zerujLicznik(); // zerowanie licznika
        this->czujnikObrL->zerujLicznik(); // zerowanie licznika
        dzialanie = false; // Dzialanie na false, metoda ma zakończyć działanie.
    }

    return dzialanie;
}


void Manewry::setPredkosc(int predkosc) {
    this->predkosc = predkosc;
}
