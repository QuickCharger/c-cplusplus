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
	virtual AbstractProduct*	createProduct( int type ) = 0;
};

class SimpleFactory: public AbstractFactory
{
public:
	SimpleFactory()	{};
	virtual ~SimpleFactory()	{};

public:
	AbstractProduct*	createProduct( int type );
};

#endif