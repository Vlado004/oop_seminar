#ifndef BOARD_H
#define BOARD_H
#include "Row.h"
#include <iostream>

class Board {
public:
	Row *red = NULL;
	int popunjenost[7];
	
	Board() {}
	~Board() { delete[] red; }

	void board_reset() {
		//std::cout << red << std::endl;
		if (red != NULL) {
			//std::cout << "Izbrisan red" << std::endl;
			delete[] red;
		}
		//std::cout << "top" << std::endl;
		red = new Row[6];
		Row tmp;
		for (int i = 0; i < 6; i++) {
			red[i] = tmp;
			popunjenost[i] = 0;
		}
		//std::cout << "Izaslo2" << std::endl;
	}
};

#endif