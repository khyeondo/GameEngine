#include <Windows.h>

#include "../header/InputManager.h"
#include "../header/WindowManager.h"

SINGLETON_CPP(InputManager)

void InputManager::Update()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(WindowMgr::Instance()->GetHWND(), &point);	
	m_mousePos.x = point.x;
	m_mousePos.y = point.y;		

	m_mouseDisplacement = m_mousePos - m_preMousePos;

	m_preMousePos = m_mousePos;

	if (m_isCursorLock == true)
	{
		SetCursorPosition(Vec2i(50, 50));
		SetCursorVisible(false);
	}
	else
	{
		SetCursorVisible(true);
	}

	for (auto& value : m_mapKey)
	{
		if (GetAsyncKeyState(value.second.key))
		{			
			if (value.second.isDown == false && 
				value.second.isHold == false)
			{
				value.second.isDown = true;
				value.second.isHold = true;
			}
			else if (value.second.isDown == true)
			{
				value.second.isDown = false;
			}
		}		
		else
		{
			if (value.second.isDown == true ||
				value.second.isHold == true)
			{
				value.second.isHold = false;
				value.second.isUp = true;
			}
			else if (value.second.isUp == true)
			{
				value.second.isUp = false;
			}
		}
	}
}

void InputManager::AddKey(const std::string& tag,int key)
{
	//소문자라면
	if(97 <= key && key <= 122)
	{
		key -= 32;
	}
	m_mapKey[tag].key = key;
}

KeyInfo InputManager::GetKeyInfo(const std::string& tag)
{
	return m_mapKey[tag];
}

bool InputManager::GetKeyDown(int key)
{	
	if (GetAsyncKeyState(key))
		return true;

	return false;
}

Vec2i InputManager::GetMousePos() 
{
	return m_mousePos;
}

Vec2i InputManager::GetMouseDisplacement()
{
	if (m_isCursorLock == true)
	{		
		return m_mousePos - Vec2i(42, 19);
	}
	else
	{
		return m_mouseDisplacement;
	}
}

void InputManager::SetCursorPosition(Vec2i pos)
{	
	RECT rect;
	GetWindowRect(WindowMgr::Instance()->GetHWND(), &rect);
	SetCursorPos(pos.x + rect.left, pos.y + rect.top);
}

void InputManager::SetCursorVisible(bool b)
{
	ShowCursor(b);
}

void InputManager::SetCursorLock(bool b)
{
	m_isCursorLock = b;
}