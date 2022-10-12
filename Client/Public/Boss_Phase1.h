#pragma once
#include "Client_Define.h"
#include "Monster.h"

BEGIN(Client)

class CBoss_Phase1 final : public CMonster {
public:
	typedef struct tagBossPatern {
		_float3 vTargetLook;
		_float3 vPosition;
	}BOSSPATERN;
private:
	enum MONSTERATTACK { ATTACK_CLAW, ATTACK_FIREBALL, ATTACK_MABUBJIN, ATTACK_METEOR, ATTACK_END };
private:
	explicit CBoss_Phase1(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBoss_Phase1(const CBoss_Phase1& rhs);
	virtual ~CBoss_Phase1() = default;
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
	_bool m_bAttack = false;
	_uint m_iPhase = 0, m_iPrePhase = 0;
	_uint m_iClawTick = 120, m_iClawCool = 2, m_iFireBallTick = 240, m_iFireBallCool = 4, m_iMabubjinCool = 8, m_iMabubjinTick = 480, m_iMeteorTick = 60, m_iMeteorCool = 2;
	_float m_fTargetDis = 0.f;
	_float3 m_vTargetLook;
	MONSTERATTACK m_eAttack = ATTACK_END;
public:
	static CBoss_Phase1* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END