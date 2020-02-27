#ifndef _SIMPLEFACTORY_H_
#define _SIMPLEFACTORY_H

#include "iostream"
#include "AbstractProduct.h"
using namespace std;

class AbstractFactory
{
public:
	AbstractFactory()	{};
	virtual	~AbstractFactory()	{};

public:
	virtual AbstractProduct*	createProduct() = 0;
};

class SimpleFactoryA: public AbstractFactory
{
public:
	SimpleFactoryA()	{};
	virtual ~SimpleFactoryA()	{};

public:
	AbstractProduct*	createProduct() {
		return new ProductA();
	}
};

class SimpleFactoryB : public AbstractFactory
{
public:
	SimpleFactoryB()	{};
	virtual ~SimpleFactoryB()	{};
public:
	AbstractProduct*	createProduct() {
		return new ProductB();
	}
};

#endif