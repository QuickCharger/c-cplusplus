#ifndef _ABSTRACTPRODUCT_H_
#define _ABSTRACTPRODUCT_H_

#include "iostream"

using namespace std;

class AbstractProduct
{
public:
	AbstractProduct()	{};
	virtual ~AbstractProduct()	{};

public:
	virtual void operation() = 0;
};

class ProductA : public AbstractProduct
{
public:
	ProductA()	{};
	virtual ~ProductA()	{};
public:
	void operation();
};

class ProductB : public AbstractProduct
{
public:
	ProductB()	{};
	virtual ~ProductB()	{};
public:
	void operation();
};

#endif