#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"

//CCore* CCore::g_pInst = nullptr;

CObject g_obj;

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

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	g_obj.SetPos(Vec2( (float)(m_ptResouluton.x / 2), (float)(m_ptResouluton.y / 2)));
	g_obj.SetScale(Vec2( 100, 100 ));

	return S_OK;
}

void CCore::progress()
{
	update();

	render();
}

void CCore::update()
{
	// 오브젝트들의 변경점을 체크

	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 0.01f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 0.01f;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_hDC
			, int(vPos.x - vScale.x / 2.f)
			, int(vPos.y - vScale.y / 2.f)
			, int(vPos.x + vScale.x / 2.f)
			, int(vPos.y + vScale.y / 2.f));
}
