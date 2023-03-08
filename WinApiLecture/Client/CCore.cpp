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
	, m_hBit(0)
	, m_memDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
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

	// 이중 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResouluton.x, m_ptResouluton.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);

	// 1픽셀의 BitMap을 가진 DC는 바로 제거해준다(DC는 생성될때 기본적으로 1픽셀의 BitMap을 가짐)
	DeleteObject(hOldBit); 

	// Manager 초기화
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();

	g_obj.SetPos(Vec2( (float)(m_ptResouluton.x / 2), (float)(m_ptResouluton.y / 2)));
	g_obj.SetScale(Vec2( 100, 100 ));

	return S_OK;
}

void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();

	update();

	render();
}

void CCore::update()
{
	// 오브젝트들의 변경점을 체크

	Vec2 vPos = g_obj.GetPos();

	if (CKeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		vPos.x -= 200.f * CTimeMgr::GetInst()->GetfDT();
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 200.f * CTimeMgr::GetInst()->GetfDT();
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 사용할 DC는 BitMap의 m_memDC 사용

	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResouluton.x + 1, m_ptResouluton.y + 1);

	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memDC
			, int(vPos.x - vScale.x / 2.f)
			, int(vPos.y - vScale.y / 2.f)
			, int(vPos.x + vScale.x / 2.f)
			, int(vPos.y + vScale.y / 2.f));

	BitBlt(m_hDC, 0, 0, m_ptResouluton.x, m_ptResouluton.y
			, m_memDC, 0, 0, SRCCOPY);
}
