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

		if (red + i < 6 && red + i >= 0) {

			if (ploca.red[red + i].stupac[zadnji_stupac] == ploca.red[red].stupac[zadnji_stupac]) { //gore - dolje
				broj_zaredom[1] += 1;
			}
			else {
				broj_zaredom[1] = 0;
			}

		}

		if(zadnji_stupac + i < 7 && zadnji_stupac + i >= 0) { 

			if (ploca.red[red].stupac[zadnji_stupac + i] == ploca.red[red].stupac[zadnji_stupac]) { //lijevo - desno
				broj_zaredom[0] += 1;
			}
			else {
				broj_zaredom[0] = 0;
			}

			if (red + i < 6 && red + i >= 0) {

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

int Connect4::min(int dubina) {
	int value, rez, prethodno;

	if (this->check() != 0) {
		return 10000;
	}

	if (dubina == 0) {
		value = 0;
		for (int i = 0; i < 7; i++) {
			if (ploca.popunjenost[i] < 6) {

				prethodno = zadnji_stupac;
				this->set(i);

				if (this->check() == 1) {
					value -= 100;
				}
				this->remove(prethodno);
			}
		}
		return value;
	}


	value = INT_MAX;
	for (int i = 0; i < 7; i++) {
		if (ploca.popunjenost[i] < 6) {

			prethodno = zadnji_stupac;
			this->set(i);
			rez = this->max(dubina - 1, false);
			if (rez < value) {
				value = rez;
			}
			this->remove(prethodno);
		}
	}

	return value;
}

int Connect4::max(int dubina, bool top) { //"Vjv neradi" - Neradi.
	int value, rez, prethodno, najbolje;

	if (this->check() != 0) {
		return -10000;
	}

	if (dubina == 0) {
		value = 0;
		for (int i = 0; i < 7; i++) {
			if (ploca.popunjenost[i] < 6) {

				prethodno = zadnji_stupac;
				this->set(i);

				if (this->check() == 1) {
					value += 100;
				}


				this->remove(prethodno);
			}
		}

		return value;
	}

	value = INT_MIN;

	for (int i = 0; i < 7; i++) {
		if (ploca.popunjenost[i] < 6) {

			prethodno = zadnji_stupac;
			this->set(i);
			rez = this->min(dubina - 1);
			if (rez > value) {
				value = rez;
				najbolje = i;
			}

			this->remove(prethodno);
		}
	}

	if (top) {
		this->set(najbolje);
	}

	return value;
}

/***PUBLIC METODE***/

void Connect4::set_player() {
	char izbor;
	bool dobar = false;

	std::cout << "Hocete li igrati protiv bota ili drugog igraca (1/2)?" << std::endl;
	do {
		std::cin >> izbor;
		if (izbor == '1') {
			std::cout << "Izaberite tezinu: 1 - Lagano : 2 - Srednje : 3 - Tesko" << std::endl;
			do {
				std::cin >> izbor;
				if (izbor == '1' || izbor == '2' || izbor == '3') {
					igraci[1].tezina = izbor - '1';
					igraci[1].ai = true;
					dobar = true;
				}
				else {
					std::cout << "Unesite 1, 2 ili 3. :]" << std::endl;
				}
			} while (!dobar);
		}
		else if (izbor == '2') {
			igraci[1].ai = false;
			dobar = true;
		}
		else {
			std::cout << "Molimo da unos bude ili 1 ili 2. :)" << std::endl;
		}
	} while (!dobar);
}

void Connect4::reset() {
	ploca.board_reset();
	igraci[0].ai = false;
	igraci[0].znak = 'x';
	igraci[1].znak = 'o';
	kraj = false;
	pobijednik = -1;
	zadnji_stupac = -1;
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
		if (igraci[igrac].tezina == 2)
			this->max(8, true);
		else if (igraci[igrac].tezina == 1)
			this->max(6, true);
		else
			this->max(4, true);

		std::cout << "Bot je odigrao u stupcu: " << zadnji_stupac + 1 << "." << std::endl;

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
	
	std::cout << " _ _ _ _ _ _ _" << std::endl;
	for (int i = 5; i >= 0; i--) {
		std::cout << "|";
		for (int j = 0; j < 7; j++) {
			if (ploca.red[i].stupac[j] == 0)
				std::cout << igraci[0].znak;
			else if (ploca.red[i].stupac[j] > 0)
				std::cout << igraci[1].znak;
			else
				std::cout << '_';
			std::cout << "|";
		}
		std::cout << std::endl;
	}
	std::cout << " ";
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