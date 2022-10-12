#pragma once
#include "Client_Define.h"
#include "Boss_Skill.h"

BEGIN(Client)

class CCircle final : public CBoss_Skill {
private:
	explicit CCircle(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CCircle(const CCircle& rhs);
	virtual ~CCircle() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	_uint m_iTick = 0;
	_uint m_iSprite = 0;
public:
	static CCircle* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END