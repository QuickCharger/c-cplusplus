#ifndef _CTESTMODULE_H_
#define _CTESTMODULE_H_

#include "iostream"
#include "CModuleManager.h"

using std::cout;
using std::endl;

class CTestModule : public CModuleManager<CTestModule>
{
public:
	CTestModule();
	~CTestModule();

	void Show1()
	{
		cout << "this is Module 1   input num: " << m_i << endl;
		cout << "this point address: " << this << endl;
	}

private:
	int m_i;
};

#endif
