#ifndef _CMODULEMANAGER_H_
#define _CMODULEMANAGER_H_

#include <vector>
#include <assert.h>

extern std::vector<void*>	m_vModules;		//this

template<typename T>
class CModuleManager
{
public:
	CModuleManager(T *Obj)
	{
		m_iModuleNum = m_vModules.size();
		m_vModules.push_back(Obj);
		for (auto it = m_vModules.begin(); it != m_vModules.end(); ++it)
		{
			cout << "module address: " << static_cast<int*>(*it) << endl;
		}
		cout << endl;
	};
	~CModuleManager() {};
	template<typename T2>
	T2* ChangeToModule()
	{
		T2 *pModule = reinterpret_cast<T2*>(m_vModules.at(T2::GetModuleID()));
		if (pModule == nullptr)
		{
			return nullptr;
		}
#ifdef _DEBUG
		assert(pModule->GetModuleID() == T2::GetModuleID());
#endif
		return pModule;
	}
	static int GetModuleID()
	{
		return m_iModuleNum;
	}
public:
	static int		m_iModuleNum;
};

template<typename T>
int CModuleManager<T>::m_iModuleNum = 0;

#endif
