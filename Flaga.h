#ifndef FLAGA_H_
#define FLAGA_H_

#include <Arduino.h>
/**
 * Klasa zawiera flagi, które można odpowiednio ustawiać.
 */
class Flaga {

public:

    Flaga();


    /**
     * Ustawienie flagi.
     * nr - numer flagi,
     * wartosc - true lub false.
     * flaga[0] = Jazda do przodu.
     * flaga[1] = Jazda do tyłu.
     * flaga[2] = Obrót w lewo.
     * flaga[3] = Obrót w prawo.
     * flaga[4] = Zatrzymaj - wykonywana jest metoda zatrzymująca.
     * flaga[5] = Zatrzymany - pojazd nie jedzie, zatrzymał się.
     * flaga[6] = Skanowanie pełne foto.
     * flaga[7] = Skanowanie ciągłe foto.
     * flaga[8] = Skanowanie odległości.
     * flaga[9] = Omijanie.
     * flaga[10] = Podjedz do przodu.
     * flaga[11] = Obróć o 180 stopni.
     * flaga[12] = Wywołanie skanowania pełnego.
     * flaga[13] = Podnoszenie wideł.
     * flaga[14] = Reset wideł.
     * flaga[15] = Czujnik przechyłowy na widłąch.
     * flaga[16] = Czujnik ograniczający podnoszenie wideł
     * @param int nr - nr flagi.
     * @param int bool - ustawienie flagi.
     */
    void setFlaga(int nr, bool wartosc);


    /**
     * Zwraca wartość flagi,
     * nr - numr flagi.
     * flaga[0] = Jazda do przodu.
     * flaga[1] = Jazda do tyłu.
     * flaga[2] = Obrót w lewo.
     * flaga[3] = Obrót w prawo.
     * flaga[4] = Zatrzymaj - wykonywana jest metoda zatrzymująca.
     * flaga[5] = Zatrzymany - pojazd nie jedzie, zatrzymał się.
     * flaga[6] = Skanowanie pełne foto.
     * flaga[7] = Skanowanie ciągłe foto.
     * flaga[8] = Skanowanie odległości.
     * flaga[9] = Omijanie.
     * flaga[10] = Podjedz do przodu.
     * flaga[11] = Obróć o 180 stopni.
     * flaga[12] = Wywołanie skanowania pełnego.
     * flaga[13] = Podnoszenie wideł.
     * flaga[14] = Reset wideł.
     * flaga[15] = Czujnik przechyłowy na widłąch.
     * flaga[16] = Czujnik ograniczający podnoszenie wideł
     * @param int nr - nr falgi.
     * @return bool - zwraca stan flagi.
     */
    bool getFlaga(int nr);


    /**
     * Ustawienie kierunku jazdy.
     */
    void setKierunek(int kierunek);


    /**
     * Pobranie kierunku.
     */
    int getKierunek();


    /**
     * Ustawia flagi na wartości jakie były na samym początku.
     * @brief ustawPoczatkowe
     */
    void ustawPoczatkowe();


    /**
     * Metoda wyłącz wszytskie procesy, zatrzymuje pojazd.
     * @brief wylaczenie
     */
    void wylaczenie();

private:
    int kierunek; // Kierunek jazdy łazika. 1 - lewo, 2 - przód, 3 - prawo, 4 tył.
    volatile bool flaga[20]; // Tablica flag.
};

#endif
