#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "Collision.h"
#include "GameInstance.h"
#include "Effect.h"
#include "Player.h"
#include "Damage.h"
#include "Quest.h"
#include "Item.h"
#include "Hit_Effect.h"
#include "MultiCamera.h"

BEGIN(Client)

class CMonster abstract : public CGameObject {
public:
	enum MONSTERSTATE { MONSTER_IDLE, MONSTER_WALK, MONSTER_HIT, MONSTER_ATK, MONSTER_DEAD, MONSTER_END };
	enum MONSTERKIND {
		MONSTER_BOSS, MONSTER_GOLEM, MONSTER_COKEMUSH, MONSTER_CUTEBEAR, MONSTER_PIG,
		MONSTER_FIREBOAR, MONSTER_GOURD, MONSTER_NOONOO, MONSTERKIND_END
	};
public:
	typedef struct tagMonster {
		map<const _uint, _float4> mapCube;
		CTransform* pTargetTransform;
		_float3 vPosition;
		MONSTERKIND m_eKind;
	}MONSTER;
protected:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CMonster(const CMonster& rhs);
	virtual ~CMonster() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	CTransform* Get_Transform() { return m_pTransform; }
	INFO Get_Monster_Info() { return m_tInfo; }
protected:
	void Collision_Ground();
	void Diving();
	void Gravity(_float fTimeDelta);
	void Look_Player(_float3 vTarget, _float* fDistance);
	void Random_Move(_float fTimeDelta);
	void Damaged(MONSTERKIND m_eMonsterKind);
	void Drop_Item();
	void Write_Damage(_uint iDamage);
	void Quest();
	void Dead_Sound(MONSTERKIND m_eMonsterKind);
protected:
	CTransform* m_pTransform = nullptr;
	CVIBuffer_Rect* m_pVIBuffer = nullptr;
	CTexture* m_pTexture = nullptr;
	CRenderer* m_pRenderer = nullptr;
	CCollision* m_pCollision = nullptr;
protected:
	MONSTER m_tMonster;
	MONSTERSTATE m_eMState = MONSTER_END, m_eMPreState = MONSTER_END;
	MONSTERKIND m_eKind = MONSTERKIND_END;
	INFO m_tInfo;
	_bool m_bDamage = false, m_bLook = false, m_bPreLook = false, m_bTargeting = false;
	_uint m_iDamageTick = 0, m_iTick = 0, m_iSprite = 0, m_iTimer = 0, m_iDeadSprite = 0;
	_float3 m_vDirection = { 0.f, 0.f, 0.f }, m_vCollision;
	_float3 m_fOriginPos;
	_uint m_Grav = 0;
	_uint m_iMoveMove = 30;

public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END