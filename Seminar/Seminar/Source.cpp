#include <iostream>
#include "Connect4.h"

int main() {

	Connect4 igra;
	char znak;

	//Unos za drugog igraca, gdje? Funkcija za to?

	while (!igra.gameover()) {
		while (!igra.gameover()) {
			igra.print();
			igra.play();
		}
		igra.print();
		std::cout << "Igrac " << igra.winner() + 1 << " je pobijedio/la!" << std::endl;
		igra.print_score();
		std::cout << "KRAJ! Hocete li igrati ponovno (y/Y)?" << std::endl;
		std::cin >> znak;
		if(znak == 'y' || znak == 'Y')
			igra.reset();
	}

}