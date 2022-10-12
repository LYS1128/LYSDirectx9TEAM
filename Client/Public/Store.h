#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Store_Potion.h"
#include "Text.h"

BEGIN(Client)

class CStore final : public CUI {
private:
	explicit CStore(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CStore(const CStore& rhs);
	virtual ~CStore() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
	HRESULT Make_StoreObject();
public:
	static CStore* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END