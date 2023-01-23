#ifndef PANTS_H
#define PANTS_H
#include "Clothing.h"


class Pants :	public Clothing
{
private:
	int pockets;
	float tax;
public:
	Pants(string ic, float p, float v, int s,int pkts,float t);
	~Pants();
	float gettax();
	virtual void print() const;
	virtual void printbill() const;
};

#endif
