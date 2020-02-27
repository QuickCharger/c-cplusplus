//#include "CModuleManager.h"
#include "CTestModule.h"
#include "CTest2Module.h"

int main()
{
	CTestModule a;
	CTest2Module b;
	CTest2Module *p1 = a.ChangeToModule<CTest2Module>();
	CTestModule *p2 = b.ChangeToModule<CTestModule>();
	CTestModule *p3 = a.ChangeToModule<CTestModule>();
	//CTest2Module *p2 = static_cast<CTest2Module*>(m_vModules.at(1));
	//CTestModule *p1 = static_cast<CTestModule*>(m_vModules.at(0));
	//CTestModule *p3 = static_cast<CTestModule*>(m_vModules.at(1));

	p1->Show2();
	//cout << reinterpret_cast<int*>(p1->this) << endl;
	p2->Show1();
	p3->Show1();
	//p3->Show1();

	getchar();

	return 0;
}
