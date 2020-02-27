#include "SimpleFactory.h"

AbstractProduct* SimpleFactoryA::createProduct()
{
	return new ProductA();
}

AbstractProduct* SimpleFactoryB::createProduct()
{
	return new ProductB();
}
