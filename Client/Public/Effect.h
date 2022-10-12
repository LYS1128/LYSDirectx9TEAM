#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "Player.h"

BEGIN(Client)

class CEffect abstract : public CGameObject {
public:
	typedef struct tagSkillFrame {
		_uint iSpriteEnd;
		_float fFrame;
	}SKILLFRAME;
protected:
	explicit CEffect(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CEffect(const CEffect& rhs);
	virtual ~CEffect() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	_uint Get_Damage() { return m_iDamage; }
	SKILLID Get_SkillID() { return m_eSkillID; }
protected:
	void MoveFrame(_float fTimeDelta);
protected:
	CTransform* m_pTransform = nullptr;
	CVIBuffer* m_pVIBuffer = nullptr;
	CTexture* m_pTexture = nullptr;
	CRenderer* m_pRenderer = nullptr;
protected:
	SKILLFRAME m_tSkillFrame;
	_float m_fRange = 0.f;
	_uint m_iDamage = 0;
	_float m_fDamagePercent = 0.f;
	CPlayer* m_pPlayer = nullptr;
	SKILLID m_eSkillID = SKILL_END;
public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free();
};

END