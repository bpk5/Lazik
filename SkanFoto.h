#ifndef SKANFOTO_H_
#define SKANFOTO_H_
#include <Arduino.h>

/**
 * Skanowanie terenu za pomocą fotorezystorów.
 *
*/
class SkanFoto {

public:
    SkanFoto(int FOTOA, int FOTOB, int poziomSwiatla);


    /**
     * Ciągłe skanowanie fotorezystorami.
     * Porusza serwem tak aby fotorezystory ustawiły się
     * do światła.
     * UWAGA - metoda musi być wywoływana w funkcji loop
     * w timerze ponieważ nie posiada własnej pętli.
     * @param pozMin pozycja serwa, ograniczenie wychyłu.
     * @param pozMax pozycja serwa, ograniczenie wychyłu.
     */
    void skanujCiag(int pozMin, int pozMax);


    /**
     * Wykonanie skanu od pozycji 0 do 180.
     * Po zeskanowaniu ustawia serwo w miejsce gdzie
     * wartości foto były największe. Światło oczywiście musi być odpowiedniej mocy.
     * Jeżeli zwraca true to trwa cykl skanowania.
     * False oznacza koniec skanowania.
     * UWAGA - wyniki pomiarów zostają zapisane w polu pozycja i swiatlo.
     * Te dane należy poddać weryfikacji przez metody akcje.
     * UWAGA - metoda nie posiada własnej pętli, wywołać w funkcji loop.
     * Zastosować timer, musi być małe opóźnienie.
     * @param int pozMin - pozycja z wartością minimalną (obranicznik).
     * @param int pozMax - pozycja z wartością maksymalną (ogranicznik).
     * @param int pozAktalna - aktualna pozycja serwomechanizmu.
     */
    bool skanujPel(int pozMin, int pozMax, int pozAktualna);


    /**
     * Zwraca wartość pola pozycja.
     * Pozycja zawiera położenie do jakiego powinien ustawić się serwomechanizm.
     */
    int getPozycja();


    /**
     * Zwraca wartość pola swiatlo.
     * Jest to maksymalna wartość uzyskana przy skanowaniu.
     */
    int getSwiatlo();


    /**
     * Zwraca odczyt z lewego fotorezystora.
     */
    int getOdczytL();


    /**
     * Zwraca odczyt z prawego fotorezystora.
     */
    int getOdczytP();


private:
    int fotoLpin; // Pin lewego fotorezystora.
    int fotoPpin; // Pin prawego fotorezystora.
    int odczytL; // Odczyt wartości z lewego fotorezystora.
    int odczytP; // Odczyt wartości z prawego fotorezystora.
    int pozycja; // Pozycja serwa gdzie ma się ustawić.
    int swiatlo; // Maksymalny poziom światła uzyskany ze skanowania.
    int swiatloMax; // Maksymalna wartość odczytana z fotorezystorów.
    int pozycjaMax; // Pozycja, w której wartość fotorezystora była największa.
    int poziomSwiatla; // Wartość, od której brany jest pod uwagę.
    int krok; // Dla switcha.
    unsigned long czas; // Czas zapamiętany przy 1 kroku (czekanie na serwo).
};

#endif
