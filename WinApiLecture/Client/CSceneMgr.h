#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene*		m_arrScene[(UINT)SCEN_TYPE::END];	// ¸ðµç ¸ñ·Ï ¾À
	CScene* m_pCurScene;							// ÇöÀç ¾À


public:
	void init();
	void update();
	void render(HDC _dc);

};

