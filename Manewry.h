#ifndef MANEWRY_H_
#define MANEWRY_H_
#include <Arduino.h>
#include "CzujnikObr.h"
#include "SilnikG.h"

/**
 * Klasa odpowiada za wykonywanie manewrów.
 * Działa na silnikach, ustawia kierunki kręcenia
 * oraz prędkość.
 */
class Manewry {

public:
    Manewry(CzujnikObr*, CzujnikObr*, SilnikG*, SilnikG*, int pozycjaSF);


    /**
     * Metoda ustawia łazik w kierunku serwomechanizmu foto.
     * Ma za zadanie ustawić łazik tak aby serwofoto było na pozycji 90
     * czyli prosto.
     * Zlicza obroty, na podstawie tych liczb będzie można wyznaczyć
     * jaki jest kierunek, do jakiego wyrównać (1, 2, 3, 4).
     * Metoda jest nowa i eksperymentalna.
     * @brief jedzZaSwiatlem
     * @param obrotyL - obroty silnika lewego.
     * @param obrotyP - obroty silnika prawego.
     * @param pozycjaSF - pozycja serwa foto.
     */
    void jedzZaSwiatlem(int obrotyL, int obrotyP, int pozycjaSF);


    /**
     * Łazik jedzie prosto, koryguje prędkość silnika.
     * łazik ma jechać prosto, zlicza obroty i wyrównuje tak aby było tyle samo
     * na każdym kole.
     * Metoda musi być wywoływana cały czas jeżeli pojazd ma
     * jechać prosto. Zawiera w sobie mechanizm korygujący
     * prędkość silników, wyrównuje jazdę.
     * Korekta prędkości jest niezbędna do prostej jazdy.
     * Silniki nie działają precyzyjnie.
     * @param int obrotyL - ilość obrotów silnika lewego.
     * @param int obrotyP - ilość obrotów silnika prawego.
     */
    void jedzProsto(int obrotyL, int obrotyP);

    /**
     * Zatrzymuje stopniowo silniki.
     * Po pełnym zatrzymaniu zwraca false.
     */
    bool zatrzymaj();


    /**
     * Obrót o 90 stopni w lewo.
     * Jeżeli metoda zwróciła false manewr został zakończony.
     * Jeżeli metoda stwierdzi że liczba obrotów nie zwiększa się
     * to podniesie prędkość, zwiększy moc silników.
     * Standardowo silniki obracają się z małą prędkością i małą mocą.
     * Może być za mała.
     * Uwaga!
     * Metoda nie ma wewnętrznej pętli.
     * Wywołać np w funkcji loop().
     * Do metody przekazujemy obroty silników.
     * @param int obrotyL - ilość obrotów silnika lewego.
     * @param int obrotyP - ilość obrotów silnika prawego.
     * @param int ileRazy - ile razy ma się obrócić, 1 to 90 stopni w lewo.
     * @return false metoda zakończyła działanie, true - działa dalej.
     */
    bool obrocLewo(int obrotyL, int obrotyP, int ileRazy);


    /**
     * Obrót o 90 stopni w prawo.
     * Jeżeli metoda zwróciła false manewr został zakończony.
     * Uwaga!
     * Metoda nie ma wewnętrznej pętli.
     * Wywołać np w funkcji loop().
     * Do metody przekazujemy obroty silników.
     * @param int obrotyL - ilość obrotów silnika lewego.
     * @param int obrotyP - ilość obrotów silnika prawego.
     * @return false metoda zakończyła działanie, true - działa dalej.
     */
    bool obrocPrawo(int obrotyL, int obrotyP);


    /**
     * Obrót o 180 stopni.
     * Metoda wywołuje metodę w lewo i ustawia ileRazy na 2.
     * @param int obrotyL - ilość obrotów silnika lewego.
     * @param int obrotyP - ilość obrotów silnika prawego.
     * @return - zwraca false jeżeli manewr został wykonany, true jeżeli trwa.
     */
    bool obroc180(int obrotyL, int obrotyP);


    /**
     * Łazik podjedzie kawałek do przodu.
     * @param int obrotyL - ilość obrotów silnika lewego.
     * @param int obrotyP - ilość obrotów silnika prawego.
     * @return false jeżeli wykonał manewr, true manewr trwa.
     */
    bool podjedz(int obrotyL, int obrotyP);


    /**
     * Prędkość jazdy.
     * Wartości dodatnie - jazda do przodu.
     * Wartości ujemne - jazda do tyłu.
     * @param int predkosc - prędkość silników.
     */
    void setPredkosc(int predkosc);

private:
    int predkosc; // Prędkość jazdy.
    int predkoscKorekta; // Prędkość korygowana.
    int predkoscManewry; // Prędkość silników przy manewrach.
    int pozycjaSF; // Początkowa pozycja serwa foto.
    int obroty; // Liczba mówi o ile ma się obrócić silnik.
    bool silnikOn; // Silnik został włączony lub wyłączony.
    bool flagaReset; // Flaga dla resetu obrotów. Reset ma być wykonany tylko raz podczas działania metody.
    // Wskaźniki na obiekty.
    CzujnikObr *czujnikObrL;
    CzujnikObr *czujnikObrP;
    SilnikG *silnikL;
    SilnikG *silnikP;
};

#endif
