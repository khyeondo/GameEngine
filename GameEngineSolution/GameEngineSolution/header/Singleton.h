#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#define SINGLETON_H(Type) \
private:\
	static Type* m_pInst;\
public:\
	static Type* Instance(){\
		if(m_pInst == nullptr)\
			m_pInst = new Type();\
		return m_pInst;\
	}\
	static void DestroySingle(){\
		delete m_pInst;\
	}

#define SINGLETON_CPP(Type)\
Type* Type::m_pInst = nullptr;

#endif // _SINGLETON_H_