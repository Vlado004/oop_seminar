#include <iostream>
#include "Connect4.h"

int main() {

	Connect4 igra;
	char znak;

	igra.set_player();

	while (!igra.gameover()) {
		while (!igra.gameover()) {
			igra.print();
			igra.play();
		}
		igra.print();
		if (igra.winner() == -1)
			std::cout << "Izjednaceno!" << std::endl;
		else
			std::cout << "Igrac " << igra.winner() + 1 << " je pobijedio/la!" << std::endl;
		igra.print_score();
		std::cout << "KRAJ! Hocete li igrati ponovno (y/Y)?" << std::endl;
		std::cin >> znak;
		if(znak == 'y' || znak == 'Y')
			igra.reset();
	}

}