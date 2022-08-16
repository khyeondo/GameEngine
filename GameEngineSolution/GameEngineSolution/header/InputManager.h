#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_

#include <unordered_map>
#include <string>
#include <Windows.h>

#include "Singleton.h"
#include "Vec2i.h"


struct KeyInfo
{	
	std::string tag;
	int key;
	bool isDown = false;
	bool isHold = false;
	bool isUp = false;
};

class InputManager
{
	SINGLETON_H(InputManager)		

private:
	std::unordered_map<std::string, KeyInfo> m_mapKey;
	Vec2i m_mousePos;
	Vec2i m_mouseDisplacement;
	Vec2i m_preMousePos;

	bool m_isCursorLock = false;

public:
	void Update();
	void AddKey(const std::string& tag, int key);
	KeyInfo GetKeyInfo(const std::string& tag);
	bool GetKeyDown(int key);
	Vec2i GetMousePos();
	Vec2i GetMouseDisplacement();
	void SetCursorPosition(Vec2i pos);
	void SetCursorVisible(bool b);

	void SetCursorLock(bool b);
	
};

typedef InputManager InputMgr;

#endif // !_INPUT_SYSTEM_H_

