#pragma once
#include "Client_Define.h"
#include "Monster.h"


BEGIN(Client)

class CBalrog final : public CMonster
{
public:
	typedef struct tagBossPatern {
		_float3 vTargetLook;
		_float3 vPosition;
	}BOSSPATERN;
private:
	enum MONSTERATTACK { ATTACK_FIREBALL, ATTACK_MABUBJIN, ATTACK_BALST, ATTACK_END };
private:
	explicit CBalrog(LPDIRECT3DDEVICE9 pGraphic_Device);
	CBalrog(const CBalrog& rhs);
	virtual~CBalrog() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	void Skill_Patern();
	void Skill_Tick();
	void Sprite_Frame();
private:
	void Damaged();
private:
	_bool m_bAttack = false;
	_uint m_iPhase = 0, m_iPrePhase = 0;
	_uint m_iFireBallTick = 240, m_iFireBallCool = 4, m_iMabubjinTick = 480, m_iMabubjinCool = 8,
		m_iBlastTick = 360, m_iBlastCool = 6;
	_uint m_iMyTick = 0;
	_float m_fTargetDis = 0.f;
	_float3 m_vTargetLook;
	MONSTERATTACK m_eAttack = ATTACK_END;
	_uint m_iNowSkill = 0, m_iPreSkill = 0, m_iHandTick = 0;
public:
	_uint Get_Skill() { return m_iNowSkill; }
	_uint Get_PreSkill() { return m_iPreSkill; }
	void Set_NowSkill(_uint Skill) { m_iNowSkill = Skill; }
	void Set_Skill(_uint PreSkill) { m_iPreSkill = PreSkill; }
private:
	HRESULT SetUp_Components();
public:
	static CBalrog* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END