#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "MultiCamera.h"

BEGIN(Client)

class CFPS final : public CUI {
private:
	explicit CFPS(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CFPS(const CFPS& rhs);
	virtual ~CFPS() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CFPS* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END