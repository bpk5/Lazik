#ifndef CZUJNIKODL_H
#define CZUJNIKODL_H
#include <Arduino.h>

/**
 * Pomiar odległości za pomocą czujnika.
 * Odległość podawana jest w cm.
 * UWAGA - problemy z pomiarem odległości ustawionych
 * pod pewnym kątem do czujnika. Co pewien czas czujnik podaje
 * błędne wartości.
 */
class CzujnikOdl {
public:

    /**
     * @param TRIG nr pinu Arduino połączony z trigger czujnika.
     * @param ECHO nr pinu Arduino połączony z echo czujnika.
     * @param LATCHPIN nr pinu Arduino połączony z układem 74HC595N.
     * @param DATAPIN nr pinu Arduino połączony z układem 74HC595N.
     * @param CLOCKPIN nr pinu Arduino połączony z układem 74HC595N.
     */
    CzujnikOdl(int TRIG, int ECHO, int LATCHPIN,
               int DATAPIN, int CLOCKPIN);


    /**
     * Metoda wykonuje pomiar odległości.
     * Zwraca odległość w cm.
     */
    int podajOdleglosc();


private:
    int trig; // Pin Arduino połączony z pinem Trigger czujnika.
    int echo; // Pin Arduino połączony z pinem Echo czujnika.
    int larchPin; // Pin dla układu 74HC595N.
    int dataPin; // Pin dla układu 74HC595N.
    int clockPin; // Pin dla układu 74HC595N
};

#endif
