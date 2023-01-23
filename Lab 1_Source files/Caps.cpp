#include "Caps.h"
#include <iostream>

using namespace std;

Caps::Caps(string ic, float p, float v, int s, int l, char slv) :Clothing(ic, p, v, s)
{
	Long = (l >= 70 && l <= 200 ? l : 100);
	Sleeves = slv;
    //test
}

Caps::~Caps()
{
}

void Caps::print() const
{
	cout << "Item Code: " << ItemCode << endl;
	cout << "Price: " << price << endl;
	cout << "VAT: " << vat << endl;
	cout << "Size: " << size << endl;
	cout << "Long: " << Long << endl;
	cout << "Sleeves: " << Sleeves << endl;
}
