#include "SimpleFactory.h"

int main(int argc, _TCHAR* argv[])
{
	AbstractFactory *factory = new SimpleFactory();
	AbstractProduct *product = factory->createProduct(1);
	product->operation();
	delete product;
	product = NULL;

	product = factory->createProduct(2);
	product->operation();
	delete product;
	product = NULL;

	return 0;
}

