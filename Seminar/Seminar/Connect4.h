#ifndef CONNECT4_H
#define CONNECT4_H
#include "Board.h"
#include "Player.h"

class Connect4 {
private:
	Board ploca;
	Player igraci[2];
	bool kraj;
	int pobijednik, zadnji_stupac;
	int rezultati[3];
	static int counter;

	int check();
	void finish(bool);
	void set(int);
	void set(int, int);
	void remove(int);
	int min(int);
	int max(int, bool);
public:
	Connect4() { 
		rezultati[0] = 0;
		rezultati[1] = 0;
		rezultati[2] = 0;
		this->reset();
	}

	void set_player();
	void reset();
	void play();
	const bool gameover();
	const int winner();
	const void print();
	const void print_score();

};

#endif