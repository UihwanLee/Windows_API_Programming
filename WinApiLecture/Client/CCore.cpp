#include "pch.h"
#include "CCore.h"

//CCore* CCore::g_pInst = nullptr;


CCore::CCore()
	: m_hWnd(0)
	, m_ptResouluton{}
	, m_hDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResouluton = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = {0, 0, m_ptResouluton.x, m_ptResouluton.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	return S_OK;
}

void CCore::progress()
{
	// 그리기

}
