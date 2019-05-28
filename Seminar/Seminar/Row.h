#ifndef ROW_H
#define ROW_H
#include <iostream>

class Row {
public:
	int *stupac;

	~Row() { delete[] stupac; }
	Row& operator=(const Row& other) {
		stupac = new int[7];
		for (int i = 0; i < 7; i++) {
			stupac[i] = -1;
		}
		return *this;
	}
};

#endif