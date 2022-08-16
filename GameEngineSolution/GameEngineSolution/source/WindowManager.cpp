#include "../header/WindowManager.h"
#include "../header/EngineCore.h"
#include "../header/SceneManager.h"
#include "../header/RenderTool.h"

SINGLETON_CPP(WindowManager)

bool WindowMgr::Init(HINSTANCE hInstance,
    unsigned int width, unsigned int height, std::wstring title)
{
    m_hInstance = hInstance;
    m_width = width;
    m_height = height;
    m_title = title;
    //wcscpy_s(m_title, sizeof(m_title),title);

    if (!MyRegisterClass()) return false;
    if (!MyCreateWindow()) return false;    

    m_hDC = GetDC(m_hWnd);

	return true;
}

LRESULT WindowMgr::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowMgr::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInstance;
    wcex.hIcon = NULL;//LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_DIRECTX11PROJECT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = m_title.c_str();
    wcex.hIconSm = NULL;

    return RegisterClassExW(&wcex);
}

BOOL WindowMgr::MyCreateWindow()
{
    m_hWnd = CreateWindowW(m_title.c_str(), m_title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInstance, nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }

    RECT rc = { 0,0,m_width,m_height };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left,
        rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

    //ShowWindow(m_hWnd, SW_SHOW);
    //UpdateWindow(m_hWnd);

    return TRUE;
}

LRESULT CALLBACK WindowMgr::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
    switch (message)
    {
    case WM_CREATE:
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;        
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);       
    }
        break;
    case WM_SIZE:
        m_pInst->m_width = LOWORD(lParam);
        m_pInst->m_height = HIWORD(lParam);
        if(RenderTool::Instance() != nullptr)
            RenderTool::Instance()->Reshape(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_DESTROY:
        EngineCore::Instance()->EndLoop();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HINSTANCE WindowManager::GetHInstance() {
    return m_hInstance;
}

HWND WindowManager::GetHWND(){
    return m_hWnd;
}

HDC WindowManager::GetHDC() {
    return m_hDC;
}

UINT WindowManager::GetHeight() {
    return m_height;
}

UINT WindowManager::GetWidth() {
    return m_width;
}