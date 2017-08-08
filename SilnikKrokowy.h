#ifndef SilnikKrokowy_h
#define SilnikKrokowy_h
#include <Arduino.h>

/**
* Steruje silnikiem krokowym odpowiedzialnym za podnoszenie
* wideł.
*
* Bartłomiej Kulesa
*/
class SilnikKrokowy
{

public:
	/**
	* @param int PA PB PC PD piny
	*/
	SilnikKrokowy(int PA, int PB, int PC, int PD, int LATCHPIN, int DATAPIN, int CLOCKPIN);


	/**
	* Podnosi widły do góry.
	*/
	void widlyDoGory();


	/**
	* Opuszcza widły.
	*/
	void widlyDoDolu();


private:
	int dly; // przerwa między krokami
	int iloscKrokow;
	int PA;
	int PB;
	int PC;
	int PD;
	int LATCHPIN;
	int DATAPIN;
	int CLOCKPIN;
};

#endif
