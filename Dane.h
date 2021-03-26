#pragma once

#include <iostream>

class Dane
{
public:
	Dane(int p, int w, int d, int i)
	{
		P = p;
		W = w;
		D = d;
		index = i;
	}
	Dane() : Dane(0, 0, 0, 0) {}
	~Dane() = default;
	int getP() { return P; }
	int getW() { return W; }
	int getD() { return D; }
	int getIndex() { return index; }
	void setALL(int newP, int newW, int newD, int newIndex) { P = newP; W = newW;  D = newD;  index = newIndex; }
	void getALL() { std::cout << P << " " << W << " " << D << std::endl; }
private:
	int P;
	int W;
	int D;
	int index;
};

