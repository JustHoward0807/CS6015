#ifndef CLOTHING_H
#define CLOTHING_H

#include <string>
using namespace std;
class Clothing
{
protected:
	string ItemCode;
	float price;
	float vat;
	int size;
public:
	Clothing(string ic,float p,float v,int s);
	~Clothing();
	virtual void print() const = 0;// pure virtual function
	virtual void printbill() const;
	void operator+=(float inc);// same implementation for all derived subclasses
	
	float getprice();
	float getvat();
	int getsize();
};

#endif
