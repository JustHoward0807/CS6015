#ifndef CAPS_H
#define CAPS_H


#include "Clothing.h"
#include <string>

class Caps : public Clothing
{
private:
	int Long;
	char Sleeves;
public:
	Caps(std::string ic, float p, float v, int s, int l, char slv);
	~Caps();
	virtual void print() const;
};

#endif
