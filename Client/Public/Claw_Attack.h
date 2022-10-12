#pragma once
#include "Client_Define.h"
#include "Boss_Skill.h"

BEGIN(Client)

class CClaw_Attack final : public CBoss_Skill {
private:
	explicit CClaw_Attack(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CClaw_Attack(const CClaw_Attack& rhs);
	virtual ~CClaw_Attack() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CClaw_Attack* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END