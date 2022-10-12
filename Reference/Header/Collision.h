#pragma once
#include "Component.h"
#include "Transform.h"

BEGIN(Engine)

class ENGINE_DLL CCollision final : public CComponent{
public:
	enum COLLISION { COL_LEFT, COL_RIGHT, COL_UP, COL_DOWN, COL_BACK, COL_FRONT, COL_END };
private:
	explicit CCollision(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CCollision(const CCollision& rhs);
	virtual ~CCollision() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
public:
	COLLISION Check_CollisionXZ(_float3 vPos1, _float3 fLength1, _float3 vPos2, _float3 fLength2);
	_bool Collision(_float3 Cube1, _float3 Size1, _float3 Cube2, _float3 Size2, _float* fCX, _float* fCY, _float* fCZ);
	void My_Collision(_float4 Cube, CTransform * pTransform2);
	_uint After_Collision(_float4 Cube, CTransform* pTransform2);
	_bool Collision_Cylinder(CTransform* pTransform1, CTransform* pTransform2);
	_bool Collision_Cube(_float4 Cube, CTransform* pTransform, _float3 vCollsion);
	_bool Collision_Sphere(CTransform* pTransform1, CTransform* pTransform2);
public:
	static CCollision* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END