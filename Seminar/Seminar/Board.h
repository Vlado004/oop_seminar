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
		if (red != NULL) {
			delete[] red;
		}
		red = new Row[6];
		Row tmp;
		for (int i = 0; i < 6; i++) {
			red[i] = tmp;
			popunjenost[i] = 0;
		}
	}
};

#endif