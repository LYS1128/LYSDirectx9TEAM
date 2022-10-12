#pragma once
#include "Client_Define.h"
#include "Boss_Skill.h"

BEGIN(Client)

class CMabubjin_Attack final : public CBoss_Skill {
private:
	explicit CMabubjin_Attack(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CMabubjin_Attack(const CMabubjin_Attack& rhs);
	virtual ~CMabubjin_Attack() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CMabubjin_Attack* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END