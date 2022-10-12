#pragma once
#include "Claw_Attack.h"
#include "Boss_Skill.h"

BEGIN(Client)

class CBossHit_Effect final : public CBoss_Skill {
public:
	typedef struct tagBossHit {
		_float3 vPos;
		BOSSSKILL eSkill;
	}BOSSHIT;
private:
	explicit CBossHit_Effect(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBossHit_Effect(const CBossHit_Effect& rhs);
	virtual ~CBossHit_Effect() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CBossHit_Effect* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END