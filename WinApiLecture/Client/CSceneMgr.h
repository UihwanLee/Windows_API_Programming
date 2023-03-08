#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene*		m_arrScene[(UINT)SCEN_TYPE::END];	// ��� ��� ��
	CScene* m_pCurScene;							// ���� ��


public:
	void init();
	void update();
	void render(HDC _dc);

};

