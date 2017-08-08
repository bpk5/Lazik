#ifndef CZUJNIKOBR_H
#define CZUJNIKOBR_H
#include <Arduino.h>

/**
 * Czujniki obrotów silników głównych.
 * Oblicza ilość obrotów silnika.
 * Pełny obrót silnika wynosi 20.
 * UWAGA jest to obrót silnika, nie koła.
 */
class CzujnikObr {
public:

    /**
     * Ustawienie pinu dla czujnika zliczającego obroty.
     * @param int - ustawienie pinu.
     */
    CzujnikObr(int);


    /**
     * Zlicza obroty tarczy na silniku głównym (pełen obrót tarczy to 20).
     */
    unsigned long zliczObroty();


    /**
     * Zerowanie licznika.
     */
    void zerujLicznik();


private:
    int liczPin; // pin czujnika obrotów silnika
    volatile unsigned long iloscObr; // pełen obrót silnika to 20 (otwory na tarczy)
    bool flaga;
};

#endif
