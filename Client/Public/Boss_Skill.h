#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "Monster.h"

BEGIN(Client)

class CBoss_Skill abstract : public CGameObject {
public:
	enum BOSSSKILL { SKILL_CLAW, SKILL_FIREBALL, SKILL_MABUBJIN, SKILL_METEOR,  SKILL_BLAST, SKILL_POG, SKILL_ELECTRIC,BOSSSKILL_END };
public:
	typedef struct tagBossSkillFrame {
		_uint iSpriteEnd;
		_float fFrame;
	}BOSSSKILLFRAME;
protected:
	explicit CBoss_Skill(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBoss_Skill(const CBoss_Skill& rhs);
	virtual ~CBoss_Skill() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	_uint Get_Damage() { return m_iDamage; }
	BOSSSKILL Get_Skill_Boss() { return m_eSkill; }
protected:
	void MoveFrame(_float fTimeDelta);
protected:
	CTransform* m_pTransform = nullptr;
	CVIBuffer* m_pVIBuffer = nullptr;
	CTexture* m_pTexture = nullptr;
	CRenderer* m_pRenderer = nullptr;
protected:
	BOSSSKILLFRAME m_tBossSkillFrame;
	BOSSSKILL m_eSkill = BOSSSKILL_END;
	_uint m_iDamage = 0, m_iDamagePercent = 0;
public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END