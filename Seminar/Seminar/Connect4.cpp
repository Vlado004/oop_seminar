#include "Connect4.h"

/***PRIVATE METODE***/

int Connect4::check() {

	int red = ploca.popunjenost[zadnji_stupac] - 1;
	int broj_zaredom[4] = { 0,0,0,0 };
	bool pun = true;

	for (int i = 0; i < 7; i++) {
		if (ploca.popunjenost[i] < 6)
			pun = false;
	}
	if (pun)
		return -1;

	for (int i = -3; i <= 3; i++) {

		if(zadnji_stupac + i < 7 && zadnji_stupac + i >= 0) { 

			if (ploca.red[red].stupac[zadnji_stupac + i] == ploca.red[red].stupac[zadnji_stupac]) { //lijevo - desno
				broj_zaredom[0] += 1;

			} else {
				broj_zaredom[0] = 0;
			}

			if (red + i < 6 && red + i >= 0) {

				if (ploca.red[red + i].stupac[zadnji_stupac] == ploca.red[red].stupac[zadnji_stupac]) { //gore - dolje
					broj_zaredom[1] += 1;
				}
				else {
					broj_zaredom[1] = 0;
				}

				if (ploca.red[red + i].stupac[zadnji_stupac + i] == ploca.red[red].stupac[zadnji_stupac]) { //gore desno - dolje lijevo
					broj_zaredom[2] += 1;
				}
				else {
					broj_zaredom[2] = 0;
				}
			}

			if (red - i < 6 && red - i >= 0) {
				if (ploca.red[red - i].stupac[zadnji_stupac + i] == ploca.red[red].stupac[zadnji_stupac]) { //gore lijevo - dolje desno
					broj_zaredom[3] += 1;
				}
				else {
					broj_zaredom[3] = 0;
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			if (broj_zaredom[i] >= 4) {
				return 1;
			}
		}
	}
	return 0;
}

void Connect4::finish(bool pobijeda) {
	kraj = true;
	if (pobijeda) {
		pobijednik = ploca.red[ploca.popunjenost[zadnji_stupac] - 1].stupac[zadnji_stupac];
		rezultati[ploca.red[ploca.popunjenost[zadnji_stupac] - 1].stupac[zadnji_stupac]] += 1;
	} else {
		rezultati[2] += 1;
	}
}

void Connect4::set(int lokacija) { //gdje ce biti - lokacija izmedu 0 i 6
	int igrac = ploca.red[ploca.popunjenost[zadnji_stupac] - 1].stupac[zadnji_stupac] ^ 1;
	ploca.red[ploca.popunjenost[lokacija]].stupac[lokacija] = igrac;
	ploca.popunjenost[lokacija] += 1;
	zadnji_stupac = lokacija;
}

void Connect4::set(int lokacija, int igrac) { //gdje ce biti - lokacija izmedu 0 i 6
	ploca.red[ploca.popunjenost[lokacija]].stupac[lokacija] = igrac;
	ploca.popunjenost[lokacija] += 1;
	zadnji_stupac = lokacija;
}

void Connect4::remove(int lokacija) { //gdje je prije bilo - lokacija izmedu 0 i 6
	ploca.red[ploca.popunjenost[zadnji_stupac] - 1].stupac[zadnji_stupac] = -1;
	(ploca.popunjenost[zadnji_stupac])--;
	zadnji_stupac = lokacija;
}

int Connect4::min_max(int dubina, bool max, bool top) { //"Vjv neradi" - Neradi.
	int value, rez, prethodno, najbolje;

	if (this->check() == 1) {
		std::cout << "uslo -> " << ((max) ? 50 : -1000) << " " << std::endl;
		return (max) ? 50 : -1000;
	}

	if (dubina == 0) {
		value = 0;
		for (int i = 0; i < 7; i++) {
			if (ploca.popunjenost[i] < 6) {

				prethodno = zadnji_stupac;
				this->set(i);

				if (this->check() == 1) {
					value = (max) ? value + 50 : value - 1000;
					std::cout << "uslo -> " << value << " " << i << std::endl;
				}


				this->remove(prethodno);
			}
			//if(i == 6)
				//std::cout << std::endl;
		}

		return value;
	}

	value = (max) ? INT_MIN : INT_MAX;

	for (int i = 0; i < 7; i++) {
		if (ploca.popunjenost[i] < 6) {

			prethodno = zadnji_stupac;
			this->set(i);
			rez = this->min_max(dubina - 1, !max, false);
			if (max) {
				if (rez > value) {
					value = rez;
					najbolje = i;
				}
			} else {
				if (rez < value) {
					value = rez;
					najbolje = i;
				}
			}

			this->remove(prethodno);
		}
	}

	if (top)
		this->set(najbolje);

	return value;

/*	int value = 0, temp_value, najbolje_mjesto;

	if (dubina == 0) {
		int zadnja_lok = zadnji_stupac;
		this->set(lokacija);

		if(this->check() == 1) {
			if (ploca.red[ploca.popunjenost[zadnji_stupac] - 1].stupac[zadnji_stupac] == 0)
				value = 100;
			else
				value = -100;
		}

		this->remove(zadnja_lok);
		return value;
	}

	if (max) {
		value = INT_MIN;
		for (int i = 0; i < 7; i++) {
			temp_value = this->min_max(dubina - 1, i, false, false);
			if (temp_value > value) {
				value = temp_value;
				najbolje_mjesto = i;
			}
		}

	} else {
		value = INT_MAX;
		for (int i = 0; i < 7; i++) {
			temp_value = this->min_max(dubina - 1, i, true, false);
			if (temp_value < value) {
				value = temp_value;
				najbolje_mjesto = i;
			}
		}

	}

	if (top) {
		this->set(najbolje_mjesto);
	}
	
	return value;*/
}

/***PUBLIC METODE***/

void Connect4::reset() {
	//std::cout << "Uslo" << std::endl;
	ploca.board_reset();
	//std::cout << "Proslo plocu" << std::endl;
	igraci[0].ai = false;
	igraci[0].znak = 'x';
	igraci[1].ai = true;
	igraci[1].hard = true;
	igraci[1].znak = 'o';
	kraj = false;
	pobijednik = -1;
	zadnji_stupac = -1;
	//std::cout << "Izaslo" << std::endl;
}

void Connect4::play() { //ZA IGRACA RADI
	char lokacija;
	bool unos_ok = false;
	int lok;
	int igrac;

	if (zadnji_stupac == -1) {
		igrac = 0;
	}
	else {
		igrac = ploca.red[ploca.popunjenost[zadnji_stupac] - 1].stupac[zadnji_stupac] ^ 1;
	}

	if (!igraci[igrac].ai) {
		do {
			std::cout << "Unesite broj stupca na koji zelite ubaciti zeton: ";
			std::cin >> lokacija;

			if (isdigit(lokacija)) {
				lok = lokacija - '0';

				if (lok >= 1 && lok <= 7) {

					if (ploca.popunjenost[lok - 1] < 6) { //set funkcija? Pukne za prvi put igrat
						this->set(lok - 1, igrac);
						unos_ok = true;

					}
					else {
						std::cout << "Taj stupac je popunjen." << std::endl;
					}

				}
				else {
					std::cout << "Broj treba biti u rasponu od 1 do 7." << std::endl;
				}

			}
			else {
				std::cout << "Niste unijeli broj." << std::endl;
			}

		} while (!unos_ok);

	}
	else {
		if (igraci[igrac].hard)
			this->min_max(4, true, true);
		else
			this->min_max(2, true, true);

	}

	int rez = this->check();
	if (rez < 0)
		this->finish(false);
	else if (rez > 0)
		this->finish(true);

}

const bool Connect4::gameover() {
	return kraj;
}

const int Connect4::winner() {
	if(kraj)
		return pobijednik;
	return -1;
}

const void Connect4::print() {


	for (int i = 5; i >= 0; i--) {
		for (int j = 0; j < 7; j++) {
			if (ploca.red[i].stupac[j] == 0)
				std::cout << igraci[0].znak;
			else if (ploca.red[i].stupac[j] > 0)
				std::cout << igraci[1].znak;
			else
				std::cout << '_';
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	for (int i = 1; i < 8; i++)
		std::cout << i << " ";
	std::cout << std::endl << std::endl;
}

const void Connect4::print_score() {
	std::cout << "Pobjeda: " << rezultati[0] 
		<< " Izjednaceno: " << rezultati[2] 
		<< " Izgubljeno: " << rezultati[1] 
		<< std::endl;
}