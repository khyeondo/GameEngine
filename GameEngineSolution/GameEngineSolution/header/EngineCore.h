#ifndef _ENGINE_MANAGER_
#define _ENGINE_MANAGER_

#include "WindowManager.h"
#include "Singleton.h"
#include "EngineSetup.h"

class EngineCore
{
	SINGLETON_H(EngineCore)

private:
	bool m_bLoop = true;

private:
	EngineCore() {}
	~EngineCore();

public:
	
	bool Init(HINSTANCE hInstance, const EngineSetup& setup);
	void Run();	
	void EndLoop();
};


#endif
