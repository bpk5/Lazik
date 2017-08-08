#ifndef SILNIKG_H
#define SILNIKG_H
#include <Arduino.h>

/**
 *	Sterowanie silnikiem głównym.
 *	Aby uruchomić silnik należy wywołać metodę zmieniajPredkosc()
 *	w funkcji loop.
 *	Uwaga wywoływać ją czasowo timerem co 100 ms!!!
 *
 *	Po wprowadzaeniu prędkości metodą setPredkoscN() silnik zacznie się
 *	obracać.
 *
 *	Do konstruktora podajemy nr pinów pod jakie został podpięty sterownik silnika
 *	pwmMotorApin - nr pinu PWM na płycie Arduino do którego
 *					podpięto sterownik silnika,
 *					sygnał PWM kanału A - służy do regulacji prędkości
 *					obrotowej silnika podłączonego do kanału A
 *	inMotorA1pin - nr pinu, sterowanie silnikiem przód - tył
 *	inMotorA2pin - nr pinu, sterowanie silnikem przód - tył
 */
class SilnikG {
public:
    SilnikG(int pwmMotorApin, int inMotorA1pin, int inMotorA2pin);


    /**
     * Metoda ma być wywołana w funkcji loop niezależnie.
     * Płynnie zmienia prędkość z aktualnej na nowo wprowadzoną.
     * Ma to zapobiec gwałtownemu szarpaniu łazikiem
     * przy znacznej zmianie prędkości lub kierunku jazdy.
     */
    void zmieniajPredkosc();


    /**
     * Ustawienie prędkości silnika.
     * Nowo wprowadzona prędkość zostanie wprowadzono do silnika
     * stopniowo przez metodę zmieniajPredkosc();
     * Aby silnik kręcił się do przodu wprowadz wartość od 1 do 100.
     * Aby silnik kręcił się do tyłu wprowadz wartość od -100 do -1.
     * Silnik nie kręci się - wartość 0.
     * @param int predkoscN - nowa prędkość pojazdu.
     */
    void setPredkoscN(int predkoscN);


    /**
     * Ustawianie natychmiastowe prędkości silnika.
     * Wartość przekazana jest natychmiastowo do silnika
     * (wywoła metodę jedz()).
     * Po wprowadzeniu prędkości nie następuje efekt rozmycia.
     * Aby silnik kręcił się do przodu wprowadz wartość od 1 do 100.
     * Aby silnik kręcił się do tyłu wprowadz wartość od -100 do -1.
     * Silnik nie kręci się - wartość 0.
     * @param int predkoscAktualna - prędkość aktualna pojazdu.
     */
    void setPredkoscAktualna(int predkoscAktualna);


    /**
     * Zwraca aktualną prędkość.
     */
    int getPredkoscAktualna();


    /**
     * Zwraca prędkość nowo wprowadzoną.
     */
    int getPredkoscN();


private:
    int pwmMotorApin; // Pin
    int inMotorA1pin; // Pin
    int inMotorA2pin; // Pin
    int predkoscAktualna; // Prędkość aktualna pojazdu.
    int predkoscN; // Nowo wprowadzona prędkość.


    /**
     * Metoda steruje silnikiem, uruchamia go, wybiera kierunek
     * kręcenia się.
     * Na podstawie pola predkoscAktualna wybierany jest kierunek
     * kręcenia się silnika (wartości ujemne - do tyłu, dodatnie - do przodu).
     * Ustawia daną prędkość. Silnik z zadaną prędkością kręci się
     * do momentu wprowadzenia innej wartości do pola predkoscN.
     */
    void jedz();
};

#endif
