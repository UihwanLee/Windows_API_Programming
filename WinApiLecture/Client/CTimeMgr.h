#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;

	// FPS
	// 1 �����Ӵ� �ð� (Delta Time)

public:
	void init();
	//QueryPe

};

