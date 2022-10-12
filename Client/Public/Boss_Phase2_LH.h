#pragma once
#include "Client_Define.h"
#include "Monster.h"
#include "Balrog.h"

BEGIN(Client)

class CBoss_Phase2_LH final : public CMonster {
public:
	typedef struct tagBossPatern {
		_float3 vTargetLook;
		_float3 vPosition;
	}BOSSPATERN;
private:
	enum MONSTERATTACK { ATTACK_ELECTRIC, ATTACK_PURPLEPOG, ATTACK_END };
private:
	explicit CBoss_Phase2_LH(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBoss_Phase2_LH(const CBoss_Phase2_LH& rhs);
	virtual ~CBoss_Phase2_LH() = default;
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
	_uint m_iElectricTick = 0, m_iElectricCool = 5, m_iPurplePogTick = 0, m_iPurplePogCool = 6;
	_float m_fTargetDis = 0.f;
	_float3 m_vTargetLook;
	MONSTERATTACK m_eAttack = ATTACK_END;
public:
	static CBoss_Phase2_LH* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END