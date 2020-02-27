#ifndef _CTEST2MODULE_H_
#define _CTEST2MODULE_H_

#include "iostream"
#include "CModuleManager.h"

using std::cout;
using std::endl;

class CTest2Module : public CModuleManager<CTest2Module>
{
public:
	CTest2Module();
	~CTest2Module();

	void Show2()
	{
		cout << "this is Module 2   num: " << m_i << endl;
		cout << "this point address: " << this << endl;
	}
private:
	int m_i;
};

#endif
