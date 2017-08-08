#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
class Timer {
public:
    Timer();


    /**
     * Metoda odlicza czas. Po upłynięciu czasu metoda
     * zwróci true. Zwraca true do momentu zresetowania.
     * @return jeżeli upłynął odpowiedni czas (interwał)
     *          metoda zwraca true.
     */
    bool cykl();


    /**
     * Ustawia interwał.
     * @param interwal
     */
    void setInterwal(int interwal);


    /**
     * Resetuje odliczanie.
     * Odliczanie zaczynamy od początku.
     */
    void reset();


private:
    volatile unsigned long czasPoprzedni;
    volatile unsigned long cza;
    int interwal;
    bool stan;  // Informacja czy upłynął czas. False - jeszcze nie, true - tak.

    /**
     * Odlicza czas. Po odliczeniu stan ustawia na true.
     */
    void odlicz();
};

#endif /* TIMER_H */

