#ifndef _WINDOW_MANAGER_H
#define _WINDOW_MANAGER_H

#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

#include <Windows.h>
#include <string>
#include "Singleton.h"



class WindowManager
{
	SINGLETON_H(WindowManager)

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HDC m_hDC;

	UINT m_width;
	UINT m_height;

	 std::wstring m_title;

private:
	WindowManager() {}

	LRESULT MyRegisterClass();	
	BOOL MyCreateWindow();

	static LRESULT CALLBACK WndProc(HWND hWnd,
		UINT message, WPARAM wParam, LPARAM lParam);

public:
	~WindowManager() {}

	bool Init(HINSTANCE hInstance, 
		unsigned int width, unsigned int height, std::wstring m_title);

	HINSTANCE GetHInstance();
	HWND GetHWND();
	HDC GetHDC();
	UINT GetWidth();
	UINT GetHeight();
};

typedef WindowManager WindowMgr;

#endif // !_WINDOW_MANAGER_H


