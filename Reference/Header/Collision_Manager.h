#pragma once
#include "Base.h"
#include "Transform.h"

BEGIN(Engine)

class ENGINE_DLL CCollision_Manager final : public CBase {
	DECLARE_SINGLETON(CCollision_Manager)
public:
	enum COLLISION { COL_LEFT, COL_RIGHT, COL_UP, COL_DOWN, COL_BACK, COL_FRONT, COL_END };
private:
	CCollision_Manager();
	virtual ~CCollision_Manager() = default;
public:
	COLLISION Check_CollisionXZ(_float3 vPos1, _float3 fLength1, _float3 vPos2, _float3 fLength2);
	_bool After_Collision(_float4 Cube, CTransform* pTransform2);
public:
	virtual void Free() override;
};

END