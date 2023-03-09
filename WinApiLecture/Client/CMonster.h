#pragma once
#include "CObject.h"

class CMonster :
    public CObject
{
private:
    Vec2        m_vCenterPos;   // 중심점
    float       m_fSpeed;       // 스피드
    float       m_fMaxDistance; // 최대 이동 거리
    int         m_iDir;         // 진행 방향 1, -1

    

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
    virtual void update();

public:
    CMonster();
    ~CMonster();
};

