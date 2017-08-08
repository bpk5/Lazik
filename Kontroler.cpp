#include "Kontroler.h"


Kontroler::Kontroler(Manewry * manewry, SkanFoto * skanFoto, Servo * serwoFoto,
             Servo * serwoOdleglosc, Flaga * flaga,
             SilnikG * silnikL, SilnikG * silnikP, CzujnikOdl * czujnikOdl,
             SilnikKrokowy *silnikKrokowy, int poziomSwiatla) {
    this->manewry = manewry;
    this->skanFoto = skanFoto;
    this->serwoFoto = serwoFoto;
    this->serwoOdleglosc = serwoOdleglosc;
    this->flaga = flaga;
    this->silnikL = silnikL;
    this->silnikP = silnikP;
    this->czujnikOdl = czujnikOdl;
    this->silnikKrokowy = silnikKrokowy;
    this->pozMinFoto = 10;
    this->pozMaxFoto = 160;
    this->pozMinFotoSt = 0;
    this->pozMaxFotoSt = 180;
    this->pozMinOdl = 20;
    this->pozMaxOdl = 170;
    this->kierPodstawowy = 2; // Jedzie do przodu.
    this->poziomSwiatla = poziomSwiatla;
    this->krok = 1;
    this->licznikWidly = 0;
}

///------------------------------------------------------------------------------------------------
void Kontroler::skanujFotoCAkcja(int obrotyL, int obrotyP, int pozAktualna) {
    // Wywołanie skanowania. Pozycje ustawione zawsze na sam początek i sam koniec. Kierunek nie ma znaczenia.
    this->skanFoto->skanujCiag(this->pozMinFotoSt, this->pozMaxFotoSt);
    // Ustawienie serwa do odpowiedniej pozycji.
    this->serwoFoto->write(this->skanFoto->getPozycja());
    // Jeżeli jedzie do przodu to wyłączyć flagę, kontrolę przejmie metoda jedzZaSwiatlem.
    if (this->flaga->getFlaga(0) == true) {
        this->flaga->setFlaga(0, false); // Jazda do przodu.
    }

    /// TODO nowy kod ***********************************************************
    /// TODO tutaj wstawić kod zamiast obrotów to jedz za światłem
    // Jeżeli światło jest mocne i nie są wykonywane manewry w lewo lub w prawo.
    if (((this->skanFoto->getOdczytL() > this->poziomSwiatla - 50) ||
         (this->skanFoto->getOdczytP() > this->poziomSwiatla - 50)) &&
            (this->flaga->getFlaga(2) == false) &&
            (this->flaga->getFlaga(3) == false)) {
        // zera do testów
        this->manewry->jedzZaSwiatlem(obrotyL, obrotyP, this->skanFoto->getPozycja());
        // Jeżeli światło zostało zgubione:
    } else {
        /// TODO
        // Jeżeli to się wykonuje oznacza to że było mocne światło ale zostało zgubione.
        this->flaga->setFlaga(12, true); // Wywołanie skanu pełnego foto.
        this->flaga->setFlaga(4, true); // Flaga dla zatrzymania pojazdu.
        /// TODO dopisać kawałek, który obróci łazik do kierunku 2.
    }
    /// *************************************************************************

}

///------------------------------------------------------------------------------------------------
void Kontroler::skanujFotoPAkcja(int pozAktualna) {
    // Ustawienie pozMin pozMax.
    //this->ustawPozMinMax();
    this->flaga->setFlaga(6, this->skanFoto->skanujPel(this->pozMinFoto, this->pozMaxFoto, pozAktualna));

    // Ustawienie serwa do ustalonej pozycji.
    this->serwoFoto->write(this->skanFoto->getPozycja());
    // Jeżeli metoda zakończyła działanie sprawdź jakie wartości uzyskała.
    if ((this->flaga->getFlaga(6) == false) && (this->skanFoto->getSwiatlo() > this->poziomSwiatla)) {
        this->flaga->setFlaga(7, true); // Skan ciągły foto.
        this->flaga->setFlaga(8, false); // Skan odległości.
        this->flaga->setFlaga(12, false); // Wywołanie skanu pełnego.
    }
}

///------------------------------------------------------------------------------------------------
void Kontroler::wywolajSkanFotoPAkcja() {
    this->flaga->setFlaga(7, false); // Skanowanie ciągłe foto.
    this->flaga->setFlaga(6, true); // Wywołanie pełnego skanowania.
}

///------------------------------------------------------------------------------------------------
void Kontroler::skanujOdlAkcja(int pozAktualna) {
    int doPrzeszkody = 30;

    // Ustawienie pozMin pozMax.
    this->ustawPozMinMax();

    // Pomiar odległości.
    int odl = this->czujnikOdl->podajOdleglosc();

    // Wybór akcji na podstawie kierunku.
    switch (this->flaga->getKierunek()) {

    case 1: // Jazda w LEWO. OMIJANIE PRZESZKODY.
        // Jeżeli flaga omijanie jest true.
        if (this->flaga->getFlaga(9) == true) {
            // Jeżeli jazda do przodu nie jest włączona to ją włącz.
            if (this->flaga->getFlaga(1) == false) {
                this->flaga->setFlaga(0, true); // jazda prosto
                this->flaga->setFlaga(5, false); // zatrzymany
            }

            // Jeżeli przeszkody po prawej stronie już nie ma to:
            if ((pozAktualna == this->pozMinOdl) && (odl > (doPrzeszkody + 10))) {
                this->flaga->setFlaga(4, true); // Zatrzymaj pojazd.
                this->flaga->setFlaga(10, true); // podjedź do przodu
                this->flaga->setFlaga(3, true); // Obrót w prawo.
                // Jeżeli podczas omijania dodatkowo napotkano na przeszkdę przed łazikiem.
                /// TODO tutaj powinien być jakiś inny manewr bo łązik znowu się obruci i będzie jeździł tak bez końca, ewentualnie omiń to w testach , nie pisz , może nie będzie takiej sytuacji.
            } else if ((pozAktualna == this->pozMaxOdl) && (odl < doPrzeszkody)) {
                this->flaga->setFlaga(4, true); // Zatrzymaj pojazd.
                this->flaga->setFlaga(11, true); // obrót o 180 stopni
            }
        }
        break;

    case 2: // Jazda do PRZODU.
        // Jeżeli odległość mniejsza niż 20 to wykonuj obrót w prawo (omijanie przeszkody).
        if (odl < doPrzeszkody) {
            this->flaga->setFlaga(9, true); // Omijanie na true.
            this->flaga->setFlaga(4, true); // Zatrzymaj pojazd.
            this->flaga->setFlaga(3, true); // Obrót w prawo.
        } else if ((odl >= doPrzeszkody) && // Odległość duża - jedź prosto.
                   (this->flaga->getFlaga(0) == false)) { // jedzie do przodu
            // Ustawienie flag do jazdy prosto
            this->ustawPozMinMax(); // Zmiana pozMin, pozMax.
            this->flaga->setFlaga(9, false); // omijanie
            this->flaga->setFlaga(0, true); // jazda prosto
            this->flaga->setFlaga(5, false); // zatrzymany
        }
        break;

    case 3: // Jazda w PRAWO. OMIJANIE PRZESZKODY.
        // Jeżeli flaga omijanie jest true.
        if (this->flaga->getFlaga(9) == true) {
            // Jeżeli jazda do przodu nie jest włączona to włącz.
            if (this->flaga->getFlaga(1) == false) {
                this->flaga->setFlaga(0, true); // jazda prosto
                this->flaga->setFlaga(5, false); // zatrzymany
            }

            // Jeżeli przeszkody po lewej stronie już nie ma to:
            if ((pozAktualna == this->pozMaxOdl) && (odl > (doPrzeszkody + 10))) {
                this->flaga->setFlaga(4, true); // Zatrzymaj pojazd.
                this->flaga->setFlaga(10, true); // podjedź do przodu
                this->flaga->setFlaga(2, true); // Obrót w lewo.
                // Jeżeli podczas omijania dodatkowo napotkano na przeszkdę przed łazikiem.
            } else if ((pozAktualna == this->pozMinOdl) && (odl < doPrzeszkody)) {
                this->flaga->setFlaga(4, true); // Zatrzymaj pojazd.
                this->flaga->setFlaga(11, true); // obrót o 180 stopni
            }
        }

        break;
    case 4: // Jazda do TYŁU.
        /// TODO - jazda do tyłu, akcja odległość, możliwe że tu nie będzie kodu.
        break;
    }
    //}


    // Mechanizm do zmieniania raz na pozMin, a po kolejnym wywołaniu na pozMax
    if (pozAktualna == this->pozMinOdl) {
        this->serwoOdleglosc->write(this->pozMaxOdl);
    } else {
        this->serwoOdleglosc->write(this->pozMinOdl);
    }
}

///------------------------------------------------------------------------------------------------
void Kontroler::jedzDoPrzoduAkcja(int predkosc, int obrotyL, int obrotyP) {
    // Ustawienie flag.
    this->flaga->setFlaga(5, false); // flaga5 - zatrzymany.
    // Wywołanie metod manewry.
    this->manewry->setPredkosc(predkosc);
    this->manewry->jedzProsto(obrotyL, obrotyP);
}

///------------------------------------------------------------------------------------------------
void Kontroler::obrocWLewoAkcja(int obrotyL, int obrotyP) {
    // Jeżeli skanowanie odległości włączone to je wyłącz.
    if (this->flaga->getFlaga(8) == true) {
        this->flaga->setFlaga(8, false);
    }

    // Wykonianie obrotu.
    this->flaga->setFlaga(2, this->manewry->obrocLewo(obrotyL, obrotyP, 1));

    // Po wykonaniu manewru zmień kierunek.
    if (this->flaga->getFlaga(2) == false) {
        this->zmienKierLewo(); // Zmiana kierunku.
        this->ustawPozMinMax(); // Ustawienie na nowo pozycji min max.
        this->flaga->setFlaga(8, true); // skan odległości
    }
}

///------------------------------------------------------------------------------------------------
void Kontroler::obrocWPrawoAkcja(int obrotyL, int obrotyP) {
    // Jeżeli skanowanie odległości włączone to je wyłącz.
    if (this->flaga->getFlaga(8) == true) {
        this->flaga->setFlaga(8, false);
    }

    // Wykonianie obrotu.
    this->flaga->setFlaga(3, this->manewry->obrocPrawo(obrotyL, obrotyP));

    // Po wykonaniu manewru zmień kierunek.
    if (this->flaga->getFlaga(3) == false) {
        this->zmienKierPrawo(); // Zmiana kierunku.
        this->ustawPozMinMax(); // Ustawienie na nowo pozycji min max.
        this->flaga->setFlaga(8, true); // skan odległości
    }
}

///------------------------------------------------------------------------------------------------
void Kontroler::podjedzAkcja(int obrotyL, int obrotyP) {
    this->flaga->setFlaga(5, false); // zatrzymany
    this->flaga->setFlaga(10, this->manewry->podjedz(obrotyL, obrotyP));
}

///------------------------------------------------------------------------------------------------
void Kontroler::obroc180Akcja(int obrotyL, int obrotyP) {
    // Jeżeli skanowanie odległości włączone to je wyłącz.
    if (this->flaga->getFlaga(8) == true) {
        this->flaga->setFlaga(8, false);
    }

    // Wykonanie obrotu o 180 stopni.
    this->flaga->setFlaga(11, this->manewry->obroc180(obrotyL, obrotyP));

    // Po wykonaniu manewru zmień kierunek.
    if (this->flaga->getFlaga(11) == false) {
        this->zmienKierLewo(); // Zmiana kierunku.
        this->zmienKierLewo(); // Zmiana kierunku.
        this->ustawPozMinMax(); // Ustawienie na nowo pozycji min max.
        this->flaga->setFlaga(8, true); // skan odległości
    }
}

///------------------------------------------------------------------------------------------------
void Kontroler::zatrzymajAkcja() {
    this->flaga->setFlaga(4, this->manewry->zatrzymaj());

    // Jeżeli manewr zatrzymywania wykonał się to flaga zatrzymany na true.
    if (this->flaga->getFlaga(4) == false) {
        this->flaga->setFlaga(0, false); // jazda do przodu
        this->flaga->setFlaga(1, false); // jazda do tyłu
        this->flaga->setFlaga(5, true); // zatrzymany
    }
}

///------------------------------------------------------------------------------------------------
void Kontroler::zmieniajPlynniePrAkcja() {
    this->silnikL->zmieniajPredkosc();
    this->silnikP->zmieniajPredkosc();
}

///------------------------------------------------------------------------------------------------
void Kontroler::ustawPozMinMax() {
    switch (this->flaga->getKierunek()) {

    case 1: // Łazik jedzie w kierunku LEWO.
        // Jeżeli flaga9 (omijanie) na true to ustawienia więcej ograniczone.
        if (this->flaga->getFlaga(9) == true) {
            // Pozycje przy omijaniu.
            this->pozMinFoto = 10;
            this->pozMaxFoto = 125;
            this->pozMinOdl = 20;
            this->pozMaxOdl = 90;
        } else {
            // Pozycje przy obrocie łazika ale przez foto.
            this->pozMinFoto = 10;
            this->pozMaxFoto = 125;
            this->pozMinOdl = 70;
            this->pozMaxOdl = 110;
        }
        break;

    case 2: // Łazik jedzie w kierunku PRZÓD.
        this->pozMinFoto = 10;
        this->pozMaxFoto = 160;
        this->pozMinOdl = 70;
        this->pozMaxOdl = 110;
        break;

    case 3: // Łazik jedzie w kierunku PRAWO.
        // Jeżeli flaga9 (omijanie) na true to ustawienia więcej ograniczone.
        if (this->flaga->getFlaga(9) == true) {
            // Pozycje przy omijaniu.
            this->pozMinFoto = 45;
            this->pozMaxFoto = 160;
            this->pozMinOdl = 90;
            this->pozMaxOdl = 160;
        } else {
            // Pozycje przy obrocie łazika ale przez foto.
            this->pozMinFoto = 45;
            this->pozMaxFoto = 160;
            this->pozMinOdl = 70;
            this->pozMaxOdl = 110;
        }
        break;

    case 4: // Łazik jedzie w kierunku TYŁ.
        this->pozMinFoto = 10;
        this->pozMaxFoto = 160;
        this->pozMinOdl = 70;
        this->pozMaxOdl = 110;
        break;
    }
}

///------------------------------------------------------------------------------------------------
void Kontroler::zmienKierPrawo() {
    // Jeżeli licznik doszedł do 4 to:
    if (this->flaga->getKierunek() == 4) {
        this->flaga->setKierunek(1);
    } else {
        // Zwiększenie kierunku o jeden.
        this->flaga->setKierunek(this->flaga->getKierunek() + 1);
    }
}

///------------------------------------------------------------------------------------------------
void Kontroler::zmienKierLewo() {
    if (this->flaga->getKierunek() == 1) {
        this->flaga->setKierunek(4);
    } else {
        // Zwiększenie kierunku o jeden.
        this->flaga->setKierunek(this->flaga->getKierunek() - 1);
    }
}


///-----------------------------------------------------------------------------
void Kontroler::skanujCzujnikPrzechylAkcja(bool odczyt) {
    /// TODO
    if (odczyt == false) {
        // Na początek ustawienie flag, zatrzymanie procesów.
        this->flaga->wylaczenie();
        // Włączenie podnoszenia wideł.
        this->flaga->setFlaga(13, true); // podnoszenie wideł
    }
}


///-----------------------------------------------------------------------------
void Kontroler::resetWidelAkcja() {
    /// TODO reset wideł

    switch (this->krok) {
    case 1:
        // Na początek wyłączyć wszystko
        this->flaga->wylaczenie();
        this->flaga->setFlaga(13, true); // podnoszenie wideł
        this->flaga->setFlaga(14, true); // reset wideł
        this->krok = 2;
        break;

    case 2:
        // Czekanie na widły. Jak dojadą do samej góry to zmieni się flaga.
        if (this->flaga->getFlaga(13) == false) {
            this->krok = 3;
        }
        break;

    case 3:
        // Opuszczanie wideł.
        if (this->licznikWidly < 500) {
            this->silnikKrokowy->widlyDoDolu();
            this->licznikWidly++;
        // Widły opuszczone.
        } else {
            // Usatwienia początkowe flag.
            this->flaga->ustawPoczatkowe();
            // Reset
            this->krok = 1;
            this->licznikWidly = 0;
        }
        break;
    }
}

///-----------------------------------------------------------------------------
void Kontroler::podniesWidlyAkcja(bool odczyt) {
    if (odczyt == false) {
        this->flaga->setFlaga(13, false);
        // Na koniec włączyć odpowiednie akcje
    }

    this->silnikKrokowy->widlyDoGory();
}




