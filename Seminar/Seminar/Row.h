#ifndef ROW_H
#define ROW_H
#include <iostream>

class Row {
public:
	int *stupac;

	~Row() { /*std::cout << "Izbrisan?" << std::endl;*/ delete[] stupac; }
	Row& operator=(const Row& other) { //HVALA TI STO POSTOJIS
		stupac = new int[7];
		for (int i = 0; i < 7; i++) {
			stupac[i] = -1;
		}
		return *this;
	}
};

#endif