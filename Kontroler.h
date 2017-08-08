#ifndef AKCJA_H_
#define AKCJA_H_

#include <Arduino.h>
#include "Manewry.h"
#include <Servo.h>
#include "Flaga.h"
#include "SkanFoto.h"
#include "CzujnikOdl.h"
#include "SilnikKrokowy.h"

/**
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
 */
class Kontroler {
public:

    /**
     * @brief Akcja
     * @param manewry - wskaźnik na obiekt manewry,
     * @param skanFoto - wskaźnik na obiekt
     * @param serwoFoto - wskaźnik na obiekt
     * @param serwoOdleglosc - wskaźnik na obiekt
     * @param flaga - wskaźnik na obiekt
     * @param silnikL - wskaźnik na obiekt
     * @param silnikP - wskaźnik na obiekt
     * @param czujnikOdl - wskaźnik na obiekt
     * @param silnikKrokowy - wskaźnik na obiekt
     * @param poziomSwiatla - poziom światła
     */
    Kontroler(Manewry * manewry, SkanFoto * skanFoto, Servo * serwoFoto,
          Servo * serwoOdleglosc, Flaga * flaga,
          SilnikG * silnikL, SilnikG * silnikP, CzujnikOdl * czujnikOdl,
          SilnikKrokowy * silnikKrokowy, int poziomSwiatla);

/// metody skanujace ***********************************************************

    /**
     * @brief skanujCzujnikPrzechyl odczytuej wartość z czujnika przechyłowego
     * zamocowanego na widłach.
     * @param odczyt - odczyt z czujnika przechyłowego na widłach.
     */
    void skanujCzujnikPrzechylAkcja(bool odczyt);


    /**
     * Ciągłe skanowania terenu fotorezystorami.
     * Jeżeli wychył serwa jest duży ustawia flagi do obrotu w lewo lub prawo.
     * @param obrotyL - liczba obrotów lewego silnika.
     * @param obrotyP - liczba obrotów prawego silnika.
     * @param int pozAktualnaa - aktualna pozycja serwo.
     */
    void skanujFotoCAkcja(int obrotyL, int obrotyP, int pozAktualna);


    /**
     * Wywołuje pełne skanowanie fotorezystorem.
     */
    void wywolajSkanFotoPAkcja();


    /**
     * Pełne skanowanie terenu foto.
     * @param int pozAktualnaa - aktualna pozycja serwo.
     */
    void skanujFotoPAkcja(int pozAktualna);


    /**
     * Skanowanie czujnikiem odległości.
     * @param int pozMin - pozycja serwa, której nie może przekroczyć (ogranicznik).
     * @param int pozMax - pozycja serwa, której nie może przekroczyć (ogranicznik).
     * @param int pozAktualnaa - aktualna pozycja serwo.
     */
    void skanujOdlAkcja(int pozAktualna);


/// metody wykonujace **********************************************************

    /**
     * Jazda do przodu z podaną prędkością.
     * @param predkosc - prędkość łazika.
     * @param obrotyL - zliczone obroty silnika lewego.
     * @param obrotyP - zliczone obroty silnika prawego.
     */
    void jedzDoPrzoduAkcja(int predkosc, int obrotyL, int obrotyP);


    /**
     * Łazik podjedzie do przodu.
     * Po wykonaniu manewru zmiana flagi na false.
     * @param obrotyL - zliczone obroty silnika lewego.
     * @param obrotyP - zliczone obroty silnika prawego.
     */
    void podjedzAkcja(int obrotyL, int obrotyP);


    /*
     * Procedura zatrzymująca samochodzik.
     * Ustawia odpowiednio flagi.
     */
    void zatrzymajAkcja();


    /**
     * Wykonanie obrotu o 90 stopni w lewo.
     * Po wykonaniu manewru zmiana flagi na false.
     * @param obrotyL - zliczone obroty silnika lewego.
     * @param obrotyP - zliczone obroty silnika prawego.
     */
    void obrocWLewoAkcja(int obrotyL, int obrotyP);


    /**
     * Wykonanie obrotu o 90 stopni w prawo.
     * Po wykonaniu manewru zmiana flagi na false.
     * @param obrotyL - zliczone obroty silnika lewego.
     * @param obrotyP - zliczone obroty silnika prawego.
     */
    void obrocWPrawoAkcja(int obrotyL, int obrotyP);




    /**
     * Obróci łazik o 180 stopni.
     * Po wykonaniu manewru zmiana flagi na false.
     * @param obrotyL - zliczone obroty silnika lewego.
     * @param obrotyP - zliczone obroty silnika prawego.
     */
    void obroc180Akcja(int obrotyL, int obrotyP);


    /**
     * Metoda resetuje widły. Oznacza to że podnisi je do samej góry.
     * Po wykryciu że przełącznik wideł przełączył się opuszcza widły
     * o określoną wartość do dołu.
     * @brief resetWidel
     */
    void resetWidelAkcja();


/// metody inne ****************************************************************

    /**
     * Metoda podnosi widły do momentu przełączenia się przełącznika ograniczającego.
     * @brief podniesWidly
     */
    void podniesWidlyAkcja(bool odczyt);



    /**
     * Płynna zmiana prędkości z aktalnej na nowo wprowadzoną.
     */
    void zmieniajPlynniePrAkcja();









private:
    // Wskaźniki na obiekty.
    Manewry * manewry;
    SkanFoto * skanFoto;
    Servo * serwoFoto;
    Servo * serwoOdleglosc;
    Flaga * flaga;
    SilnikG * silnikL;
    SilnikG * silnikP;
    CzujnikOdl * czujnikOdl;
    SilnikKrokowy * silnikKrokowy;

    int pozMinFoto; // Pozycja minimalna do jakiej wychyli się serwo foto.
    int pozMaxFoto; // Pozycja maksymalna do jakiej wychyli się serwo foto.
    int pozMinFotoSt; // Pozycja minimalna do jakiej wychyli się serwo ale jest to wartość zawsze najmniejsza, nie ma znaczenia kierunek.
    int pozMaxFotoSt; // Pozycja maksymalna do jakiej wychyli się serwo ale jest to wartość zawsze największa, nie ma znaczenia kierunek.
    int pozMinOdl; // Pozycja minimalna do jakiej wychyli się serwo odległości.
    int pozMaxOdl; // Pozycja maksymalna do jakiej wychyli się serwo odległości.
    int kierPodstawowy; // Kierunkiem podstawowym jest 2 jeżeli jedzie po ładunek, 4 jeżeli wraca z łądunkiem.
    int poziomSwiatla; // Poziom światła, światło mocne, próg od którego uznaje się źródło światła za wykryte.
    int krok; // kroki switch
    int licznikWidly; // zlicza obroty silnika krokowego (widły do dołu).

    /**
     * Po wywołaniu tej metody zostaną ustawione pozMin i pozMax
     * w zależności od kierunku jazdy.
     */
    void ustawPozMinMax();


    /**
     * Zmienia kierunek jazdy.
     * Uruchamiać gdy obrócono pojazd w prawo.
     */
    void zmienKierPrawo();


    /**
     * Zmienia kierunek jazdy.
     * Uruchamiać gdy obrócono pojazd w lewo.
     */
    void zmienKierLewo();

};

#endif /* AKCJA_H_ */
