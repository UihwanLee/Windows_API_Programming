#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	// �� ���� ����
	for (UINT i = 0; i < (UINT)SCEN_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::init()
{
	// Scene ����
	m_arrScene[(UINT)SCEN_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCEN_TYPE::START]->SetName(L"Start Scene");

	//m_arrScene[(UINT)SCEN_TYPE::TOOL] = new CScene_Tool;
	//m_arrScene[(UINT)SCEN_TYPE::STAGE01] = new CScene_Stage01;
	//m_arrScene[(UINT)SCEN_TYPE::STAGE02] = new CScene_Stage02;

	// ���� �� ����
	m_pCurScene = m_arrScene[(UINT)SCEN_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneMgr::update()
{
	m_pCurScene->update();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}
