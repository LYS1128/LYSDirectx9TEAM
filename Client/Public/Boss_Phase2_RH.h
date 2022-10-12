#pragma once
#include "Client_Define.h"
#include "Monster.h"
#include "Balrog.h"

BEGIN(Client)

class CBoss_Phase2_RH final : public CMonster {
public:
	typedef struct tagBossPatern {
		_float3 vTargetLook;
		_float3 vPosition;
	}BOSSPATERN;
private:
	enum MONSTERATTACK { ATTACK_ICE, ATTACK_WYVERN, ATTACK_END };
private:
	explicit CBoss_Phase2_RH(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBoss_Phase2_RH(const CBoss_Phase2_RH& rhs);
	virtual ~CBoss_Phase2_RH() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	void Skill_Patern();
	void Skill_Tick();
	void Sprite_Frame();
private:
	void Damaged();
private:
	_uint m_tickCount = 0, m_iRand = 0;

	_bool m_bAttack = false;
	_uint m_iPhase = 0, m_iPrePhase = 0;
	_uint m_iIceTick = 120, m_iIceCool = 2, m_iWyTick = 240, m_iWyCool = 4;
	_float m_fTargetDis = 0.f;
	_float3 m_vTargetLook;
	MONSTERATTACK m_eAttack = ATTACK_END;
public:
	static CBoss_Phase2_RH* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END