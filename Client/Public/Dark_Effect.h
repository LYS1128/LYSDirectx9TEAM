#pragma once
#include "UI.h"

BEGIN(Client)

class CDark_Effect final : public CUI {
private:
	explicit CDark_Effect(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CDark_Effect(const CDark_Effect& rhs);
	virtual ~CDark_Effect() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	CUI* m_pUltimate = nullptr;
public:
	static CDark_Effect* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END