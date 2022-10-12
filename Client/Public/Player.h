#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "GameInstance.h"
#include "Sound_Manager.h"
#include "Shadow.h"


BEGIN(Client)
class CMultiCamera;
class CStatWindow;
class CMonster;
class CGameOver;
class CBoss_Skill;
class CBossHit_Effect;

class CPlayer final : public CGameObject {
public:
	enum BASICSTATE { STATE_L, STATE_R, STATE_U, STATE_D, STATE_UL, STATE_UR, STATE_DL, STATE_DR, BASICSTATE_END };
	enum STATE {
		U_RUN, D_RUN, L_RUN, R_RUN, UL_RUN, DL_RUN, UR_RUN, DR_RUN,					//달리기
		U_STAB, D_STAB, L_STAB, R_STAB, LU_STAB, LD_STAB, RU_STAB, RD_STAB,				//찌르기
		U_HORCUT, D_HORCUT, L_HORCUT, R_HORCUT, LU_HORCUT, LD_HORCUT, RU_HORCUT, RD_HORCUT, 	//횡베기
		U_VERCUT, D_VERCUT, L_VERCUT, R_VERCUT, LU_VERCUT, LD_VERCUT, RU_VERCUT, RD_VERCUT,				//종베기
		U_STAND, D_STAND, L_STAND, R_STAND, LU_STAND, LD_STAND, RU_STAND, RD_STAND,	STATE_END
	};
	enum BIND {	BIND_5, BIND_7, BIND_10, BIND_1, BIND_END };
private:
	typedef struct tagTarget {
		_float fDis;
		_float3 vPos;
	}TARGET;
public:
	typedef struct tagEffect {
		map<const _uint, _float4> mapCube;
		CTransform* pTargetTransform;
		BASICSTATE eBasicState;
	}EFFECT;

private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CPlayer(const CPlayer& rhs);
	virtual ~CPlayer() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
	HRESULT SetUp_Standing_Texture();
	HRESULT SetUp_Run_Texture();
	HRESULT SetUp_Stab_Texture();
	HRESULT SetUp_HorCut_Texture();
	HRESULT SetUp_VerCut_Texture();
	
private:
	void Key_Input(_float fTimeDelta);
	void Standing();
	void Collision_Ground();
	void Gravity(_float fTimeDelta);
	void Diving();
	void Level_Up();
	void Collision_Monster();
	void Damaged_MonsterSkill();
	void Player_Dead();
	void Skill_Tick();
	void Write_Damage(_uint iDamage);

	void FPS();

public:
	INFO Get_Player_Info() { return m_tInfo; }
	_uint Get_SkillOpen() { return m_iSkillOpen; }
	_uint Get_Meso() { return m_iMeso; }
	_bool Get_HpLow() { return m_bHpLow; }

	void Set_SkillOpen(_uint Skill) { m_iSkillOpen += Skill; }
	void Set_State(OBJECTSTATE eState) { m_eState = eState; }
	void Set_Pos(_float3 vPos) { m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos); }
	void Set_Revive();

	void Stop_Player();
	void UnStop_Player();

	void Set_Bullet() { m_iBullet = 20; }
	void Set_RedPotion() { ++m_iHpPotion; }
	void Set_BluePotion() { ++m_iMpPotion; }
	void Set_Meso(_uint iMeso) { m_iMeso -= iMeso; }
	void Set_HpLow(_bool HpLow) { m_bHpLow = HpLow; }
	void Lost_Soul() { m_iSoul = 0; }
private:	
	CTransform*	m_pTransformCom = nullptr;	
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;	
	CTexture* m_pTextureCom = nullptr;	
	CRenderer* m_pRendererCom = nullptr;
	CCollision* m_pCollisionCom = nullptr;
private:
	_bool m_bJumping = false, m_bAttack = false, m_bMoving = false, m_bDamaged = false, m_bDead = false;
	_uint m_iTick = 0, m_iSprite = 0, m_iAttack = 0, m_iDamagedTick = 0, m_iSuperTick = 0;
	_float m_fJumpTime = 3.6f;
	_uint m_iHpPotion = 0, m_iMpPotion = 0, m_iMeso = 0, m_iSoul = 0;
	_uint m_Grav = 0;
	_uint m_iSkillOpen = 255;
	_uint m_iMpUp = 0;
private:
	STATE m_ePlayerState = STATE_END, m_ePrePlayerState = STATE_END;
	BIND m_eBind = BIND_END;
	BASICSTATE m_eBasicState = BASICSTATE_END;
	INFO m_tInfo;
	_bool m_bStatWin=false, m_bSuper = false, m_bHpLow = false;
	_uint m_iBullet = 20;
public:
	void Hp_Minus(_uint Damage) { m_tInfo.iHp -= Damage; }
	void Exp_Plus(_uint Exp) { m_tInfo.iExp += Exp; }
	_uint Get_SoulNum() { return m_iSoul; }
	_uint Get_Bullet() { return m_iBullet; }
private:
	map<const _uint, _float4> m_mapCube;

private:
	_uint m_iFreezeTick = 0, m_iCrayTick = 0, m_iIceTick = 0, m_iShieldTick = 0, m_iEarthquakeTick = 0, m_iMoonLightTick = 0;
	_uint m_iFreezeCool = 1, m_iCrayCool = 2, m_iIceCool = 4, m_iShieldCool = 1, m_iEarthquakeCool = 5, m_iMoonLightCool = 20;

public:
	_uint Get_FreezeTick() { return m_iFreezeTick; }
	_uint Get_CrayTick() { return m_iCrayTick; }
	_uint Get_IceTick() { return m_iIceTick; }
	_uint Get_ShieldTick() { return m_iShieldTick; }
	_uint Get_EarthquakeTick() { return m_iEarthquakeTick; }
	_uint Get_MoonLightTick() { return m_iMoonLightTick; }
public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

public:
	void Set_Map(map<const _uint, _float4> Map) { m_mapCube = Map; }
	void PlusHpPo() { ++m_iHpPotion; }
	void PlusMpPo() { ++m_iMpPotion; }
	void PlusMeso() { ++m_iMeso; }
	void PlusSoul() { ++m_iSoul; }

};

END