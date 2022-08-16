#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <iostream>
#include <map>
#include <string>

#include "Singleton.h"

class IResource;

template <class T>
class ResourceManager
{
	SINGLETON_H(ResourceManager<T>)

private:
	ResourceManager() {}
	~ResourceManager() 
	{
		for (auto& pValue : m_resources)
		{
			delete pValue.second;
		}
		m_resources.clear();
	}

private:
	std::map<std::string, IResource*> m_resources;

public:

	T* GetResource(const std::string& key) 
	{
		return (T*)m_resources[key];
	}

	bool Load(const std::wstring& path, const std::string& key)
	{
		IResource* pResource = new T();

		if (!pResource->Load(path))
		{
			std::cout << "fail to load resource. (" << path.c_str() << ")" << std::endl;
			return false;		
		}

		m_resources[key] = pResource;

		return true;
	}	

	void Clear()
	{
		for (auto& pValue : m_resources)
		{
			delete pValue.second;
		}
		m_resources.clear();
	}
};

template<class T>
ResourceManager<T>* ResourceManager<T>::m_pInst = nullptr;

template<class T>
using ResourceMgr = ResourceManager<T>;

#endif // !_RESOURCE_MANAGER_H_

