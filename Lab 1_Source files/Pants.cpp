#include "Pants.h"
#include <iostream>

using namespace std;

Pants::Pants(string ic, float p, float v, int s, int pkts, float t) :Clothing(ic, p, v, s)
{
	pockets = (pkts > 0 ? pkts : 0);
	tax = (t >= 1 && t <= 5 ? t : 1);
}

Pants::~Pants()
{
}

void Pants::print() const
{
	cout << "Item Code: " << ItemCode << endl;
	cout << "Price: " << price << endl;
	cout << "VAT: " << vat << endl;
	cout << "Size: " << size << endl;
	cout << "Pockets: " << pockets << endl;
	cout << "Import Tax: " << tax << endl;
}

void Pants::printbill() const
{
    cout << "Bill :" << price*(100 + vat) / 100 + tax << endl;
}

float Pants::gettax()
{
    return tax;
}

