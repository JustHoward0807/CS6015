#include "Clothing.h"
#include <iostream>
#include <ctype.h>

using namespace std;

Clothing::Clothing(string ic, float p, float v, int s)
{
    ItemCode = ic;
	
	price = (p > 0 ? p : 0.0);
	vat = (v > 0 ? v : 11);

    size=s;

}



Clothing::~Clothing()
{
}

void Clothing::printbill() const
{
	cout << "Bill: " << price*(100 + vat) / 100 << endl;
}

void Clothing::operator+=(float inc)
{
	price += inc;
}

float Clothing::getprice()
{
    return price;
}

float Clothing::getvat()
{
    return vat;
}

int Clothing::getsize()
{
    return size;
}
