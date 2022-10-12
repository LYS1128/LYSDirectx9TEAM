#pragma once
#include "Client_Define.h"
#include "Boss_Skill.h"
#include "Boss_Phase1.h"

BEGIN(Client)

class CFireBall_Attack final : public CBoss_Skill {
private:
	explicit CFireBall_Attack(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CFireBall_Attack(const CFireBall_Attack& rhs);
	virtual ~CFireBall_Attack() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	_uint m_iTick = 0;
	_float3 m_vLook;
public:
	static CFireBall_Attack* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END