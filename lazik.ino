//#include "config.cpp"
// QT Creator 1.6.2
#include <Arduino.h>
#include <Servo.h>
#include "CzujnikObr.h"
#include "Manewry.h"
#include "SilnikG.h"
#include "SilnikKrokowy.h"
#include "Kontroler.h"
#include "CzujnikOdl.h"
#include "SkanFoto.h"
#include "Flaga.h"
#include "Timer.h"
#include "Informacje.h"

extern HardwareSerial Serial;

const int TRIG = 32; // trig, czujnik odległości, wartość dla 74HC595N
const int PA = 2; // silnik krokowy, wartość dla 74HC595N
const int PB = 4; // silnik krokowy, wartość dla 74HC595N
const int PC = 8; // silnik krokowy, wartość dla 74HC595N
const int PD = 16; // silnik krokowy, wartość dla 74HC595N

const int FOTOL = 14; // fotorezystor 1 LEWY
const int FOTOP = 15; // fotorezystor 2 PRAWY
const int LATCHPIN = 16; // latchPin układ 74HC595N
const int CLOCKPIN = 17; // clockPin układ 74HC595N
const int OGRWIDLY = 18; // przełącznik nad widłami, ogranicznik wideł
const int PRZECH = 19; // czujnik przechyłu, zamocowany na widłach

const int BIN1 = 13;
const int BIN2 = 12;
const int DATAPIN = 11; // dataPin układ 74HC595N
const int SERVO2 = 10; // sygnał serwo fotorezystorów
const int SERVO1 = 9; // sygnał serwo czujnik odległości
const int AIN2 = 8;
const int AIN1 = 7;
const int PWMB = 6;
const int PWMA = 5;
const int ECHO = 4; // echo, czujnik odległości
const int LICZP = 3; // czujnik obrotów prawego silnika
const int LICZL = 2; // czujnik obrotów lewego silnika

int pozycjaSO = 90; // Pozycja serwo od odległości na środku.
int pozycjaSF = 85; // Pozycja serwo od fororezystorów na środku.

int poziomSwiatla = 350; // Poziom światła, światło mocne, próg od którego uznaje się źródło światła za wykryte.

// Wywołanie obiektów.
Flaga flaga;
CzujnikOdl czujnikOdl(TRIG, ECHO, LATCHPIN, DATAPIN, CLOCKPIN);
Servo serwoOdleglosc;
Servo serwoFoto;
CzujnikObr czujnikObrL(LICZL);
CzujnikObr czujnikObrP(LICZP);
SilnikG silnikP(PWMA, AIN1, AIN2);
SilnikG silnikL(PWMB, BIN1, BIN2);
Manewry manewry(& czujnikObrL, & czujnikObrP, & silnikL, & silnikP, pozycjaSF);
SkanFoto skanFoto(FOTOL, FOTOP, poziomSwiatla);
Timer timer[10];
SilnikKrokowy silnikKrokowy(PA, PB, PC, PD, LATCHPIN, DATAPIN, CLOCKPIN);
Kontroler kontroler(& manewry, & skanFoto, & serwoFoto, & serwoOdleglosc,
            & flaga, & silnikL, & silnikP, & czujnikOdl,& silnikKrokowy, poziomSwiatla);

void info();

void setup() {
    Serial.begin(9600);
    // Piny dla silnika
    pinMode(PWMA, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    // Piny czujnika odległości
    pinMode(ECHO, INPUT);
    // Piny fotorezystora
    pinMode(FOTOL, INPUT);
    pinMode(FOTOP, INPUT);
    // Piny liczników
    pinMode(LICZL, INPUT);
    pinMode(LICZP, INPUT);
    // Piny układu 74HC595N
    pinMode(LATCHPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATAPIN, OUTPUT);
    // Pin przełącznika ograniczającego widły.
    pinMode(OGRWIDLY, INPUT_PULLUP);
    // Pin czujnika przechyłowego na widłach.
    pinMode(PRZECH, INPUT_PULLUP);

    //Ustawienie pinów dla serwa1 i serwa2
    serwoOdleglosc.attach(SERVO1);
    serwoFoto.attach(SERVO2);

    // Ustawienie pozycji początkowej
    serwoOdleglosc.write(pozycjaSO);
    serwoFoto.write(pozycjaSF);

    // Wyłączenie napięcia w układzie 74HC595N.
    digitalWrite(LATCHPIN, LOW);
    shiftOut(DATAPIN, CLOCKPIN, MSBFIRST, 0);
    digitalWrite(LATCHPIN, HIGH);

    //Ustawienie timerów.
    timer[0].setInterwal(10); // Płynna zmiana prędkości.
    timer[1].setInterwal(20); // Ciągłę skanowanie fotorezystorami.
    timer[2].setInterwal(403); // Skanowanie odległości.
    timer[3].setInterwal(1500); // Wywołanie skanowania foto pełnego.
    timer[4].setInterwal(10);
    timer[5].setInterwal(7); // Skanowanie foto pełne.
    timer[6].setInterwal(100); // Sprawdzanie czujnika podnoszenia wideł i czujnik przechyłowy na widłach.

    timer[9].setInterwal(1000); // Informacje
    timer[8].setInterwal(60000); // testy, zatrzymanie

    // Opóźnienie startu łazika.
    delay(3000);

    flaga.wylaczenie();
    flaga.setFlaga(14, true);
    //flaga.setFlaga(13,true);

}


void loop() {

    // PŁYNNA ZMIANA PRĘDKOŚCI!
    if (timer[0].cykl() == true) {
        kontroler.zmieniajPlynniePrAkcja();
        timer[0].reset();
    }

    // WYWOŁANIE PEŁNEGO SKANOWANIA FOTO!
    if ((timer[3].cykl() == true) &&
            (flaga.getFlaga(12) == true) &&
            (flaga.getFlaga(9) == false)) {
        kontroler.wywolajSkanFotoPAkcja();
        timer[3].reset();
    }

    // SKANOWANIE FOTO PEŁNE!
    if ((timer[5].cykl() == true) &&
            (flaga.getFlaga(6) == true) &&
            (flaga.getFlaga(9) == false)) {
        kontroler.skanujFotoPAkcja(serwoFoto.read());
        timer[5].reset();
    }

    // SKANOWANIE FOTO CIĄGŁE!
    if ((timer[1].cykl() == true) &&
            (flaga.getFlaga(7) == true) &&
            (flaga.getFlaga(9) == false)) {
        kontroler.skanujFotoCAkcja(czujnikObrL.zliczObroty(), czujnikObrP.zliczObroty(), serwoFoto.read());
        timer[1].reset();
    }

    // SKANOWANIE ODLEGŁOŚCI!
    if ((timer[2].cykl() == true) &&
            (flaga.getFlaga(8) == true) && // skanowanie odległości
            (flaga.getFlaga(2) == false) && // obrót w lewo
            (flaga.getFlaga(3) == false) && // obrót w prawo
            (flaga.getFlaga(11) == false)) { // obrót o 180 stopni
        kontroler.skanujOdlAkcja(serwoOdleglosc.read());
        timer[2].reset();
    }

    // JEDŹ PROSTO!
    if ((flaga.getFlaga(0) == true) && // jazda do przodu
            (flaga.getFlaga(1) == false) && // jazda do tyłu
            (flaga.getFlaga(2) == false) && // obrot w lewo
            (flaga.getFlaga(3) == false) && // obrót w prawo
            (flaga.getFlaga(10) == false) && // podjedz do przodu
            (flaga.getFlaga(11) == false)) { // obrót o 180 stopni
        kontroler.jedzDoPrzoduAkcja(35, czujnikObrL.zliczObroty(), czujnikObrP.zliczObroty());
    }

    // OBRÓT W LEWO!
    if ((flaga.getFlaga(0) == false) && // jazda do przodu
            (flaga.getFlaga(1) == false) && // jazda do tyłu
            (flaga.getFlaga(2) == true) && // obrot w lewo
            (flaga.getFlaga(3) == false) && // obrót w prawo
            (flaga.getFlaga(5) == true) && // zatrzymany
            (flaga.getFlaga(10) == false) && // podjedź do przodu
            (flaga.getFlaga(11) == false)) { // obrót o 180 stoopni
        kontroler.obrocWLewoAkcja(czujnikObrL.zliczObroty(), czujnikObrP.zliczObroty());
    }

    // OBRÓT W PRAWO!
    if ((flaga.getFlaga(0) == false) && // jazda do przodu
            (flaga.getFlaga(1) == false) && // jazda do tyłu
            (flaga.getFlaga(2) == false) && // obrot w lewo
            (flaga.getFlaga(3) == true) && // obrót w prawo
            (flaga.getFlaga(5) == true) && // zatrzymany
            (flaga.getFlaga(10) == false) && // podjedź do przodu
            (flaga.getFlaga(11) == false)) { // obrót o 180 stoopni
        kontroler.obrocWPrawoAkcja(czujnikObrL.zliczObroty(), czujnikObrP.zliczObroty());
    }

    // PODJEDZ DO PRZODU!
    if ((flaga.getFlaga(1) == false) && // jazda do tyłu
            (flaga.getFlaga(10) == true) && // podjedz do przodu
            (flaga.getFlaga(11) == false)) { // obróć o 180 stopni
        kontroler.podjedzAkcja(czujnikObrL.zliczObroty(), czujnikObrP.zliczObroty());
    }

    // OBRÓT O 180 STOPNI!
    if ((flaga.getFlaga(0) == false) && // jazda do przodu
            (flaga.getFlaga(1) == false) && // jazda do tyłu
            (flaga.getFlaga(2) == false) && // obrot w lewo
            (flaga.getFlaga(3) == false) && // obrót w prawo
            (flaga.getFlaga(5) == true) && // zatrzymany
            (flaga.getFlaga(10) == false) && // podjedź do przodu
            (flaga.getFlaga(11) == true)) { // obrót o 180 stoopni
        kontroler.obroc180Akcja(czujnikObrL.zliczObroty(), czujnikObrP.zliczObroty());
    }

    // ZATRZYMAJ!
    if ((flaga.getFlaga(4) == true) && // zatrzymaj
            (flaga.getFlaga(5) == false) && // zatrzymany
            (flaga.getFlaga(10) == false)) { // podjedz do przodu
        kontroler.zatrzymajAkcja();
    }

    // CZUJNIK PRZECHYŁOWY NA WIDŁĄCH
    if ((timer[6].cykl() == true) &&
            (flaga.getFlaga(15) == true)) { // czujnik przechyłowy na widłach
        kontroler.skanujCzujnikPrzechylAkcja(digitalRead(PRZECH));
        timer[6].reset();
    }

    // PODNOSZENIE WIDEŁ
    if (flaga.getFlaga(13) == true) {
        kontroler.podniesWidlyAkcja(digitalRead(OGRWIDLY));
    }

    // RESET WIDEŁ
    if (flaga.getFlaga(14) == true) {
        kontroler.resetWidelAkcja();
    }


    // -----------------------------------------------------------------------------
    // TESTOWANIE
    if (timer[9].cykl()) {
        //info();
        timer[9].reset();
    }


}

void info() {

    Serial.println("-----------start-------------------------------------");
    Serial.print("Flaga 0 = Jazda do przodu = ");
    Serial.println(flaga.getFlaga(0));
    Serial.print("Flaga 1 = Jazda do tyłu = ");
    Serial.println(flaga.getFlaga(1));
    Serial.print("Flaga 2 = Obrot w lewo = ");
    Serial.println(flaga.getFlaga(2));
    Serial.print("Flaga 3 = Obrot w prawo = ");
    Serial.println(flaga.getFlaga(3));
    Serial.print("Flaga 4 = Zatrzymaj = ");
    Serial.println(flaga.getFlaga(4));
    Serial.print("Flaga 5 = Zatrzymany = ");
    Serial.println(flaga.getFlaga(5));
    Serial.print("Flaga 6 = skan pelny foto = ");
    Serial.println(flaga.getFlaga(6));
    Serial.print("Flaga 7 = skan ciagly foto = ");
    Serial.println(flaga.getFlaga(7));
    Serial.print("Flaga 8 = skan odleglosci = ");
    Serial.println(flaga.getFlaga(8));
    Serial.print("Flaga 9 = omijanie = ");
    Serial.println(flaga.getFlaga(9));
    Serial.print("Flaga 10 = podjedz = ");
    Serial.println(flaga.getFlaga(10));
    Serial.print("Flaga 11 = 180 stopni = ");
    Serial.println(flaga.getFlaga(11));
    Serial.print("Flaga 12 = wywolanie skanu pelnego = ");
    Serial.println(flaga.getFlaga(12));
    Serial.print("Flaga 13 = podnoszenie widel = ");
    Serial.println(flaga.getFlaga(13));
    Serial.print("Flaga 14 = reset widel = ");
    Serial.println(flaga.getFlaga(14));
    Serial.print("Flaga 15 = czujnik przechylowy = ");
    Serial.println(flaga.getFlaga(15));


    Serial.print("kierunek = ");
    Serial.println(flaga.getKierunek());

    Serial.print("pozycja serwo odl = ");
    Serial.println(serwoOdleglosc.read());
    // Serial.println("");
    // Serial.print("Silnik L, predkosc Aktualna = ");
    // Serial.println(silnikL.getPredkoscAktualna());
    // Serial.print("Silnik L, predkosc Nowa = ");
    // Serial.println(silnikL.getPredkoscN());
    // Serial.print("Silnik P, predkosc Aktualna = ");
    // Serial.println(silnikP.getPredkoscAktualna());
    // Serial.print("Silnik P, predkosc Nowa = ");
    // Serial.println(silnikP.getPredkoscN());
    // Serial.print("odleglosc = ");
    // Serial.println(czujnikOdl.podajOdleglosc());
    // Serial.print("licznik obrotow L = ");
    // Serial.println(czujnikObrL.zliczObroty());
    // Serial.print("licznik obrotow P = ");
    // Serial.println(czujnikObrP.zliczObroty());
    Serial.println("------------end------------------------------------");
}
