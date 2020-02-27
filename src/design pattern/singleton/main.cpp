#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <time.h>

using namespace std;

class GlobalClass
{
	int m_vlaue;
	GlobalClass(int v = 0)
	{
		m_vlaue = 0;
	}
public:
	int get_value()
	{
		return m_vlaue;
	}
	void set_value(int v)
	{
		m_vlaue = v;
	}
	static GlobalClass *instance()
	{
		static GlobalClass ret;
		return &ret;
	}
};

void foo()
{
	GlobalClass::instance()->set_value(1);
	cout << __FUNCTION__ << " value: " << GlobalClass::instance()->get_value() << endl;
}

void bar()
{
	GlobalClass::instance()->set_value(2);
	cout << __FUNCTION__ << ". value: " << GlobalClass::instance()->get_value() << endl;
}

int main(int argc, char **argv)
{
	cout << __FUNCTION__ << ". value: " << GlobalClass::instance()->get_value() << endl;
	foo();
	bar();

	getchar();
}
