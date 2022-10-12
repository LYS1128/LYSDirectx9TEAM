#pragma once
#include "Client_Define.h"
#include "UI.h"

BEGIN(Client)

class CLevelUp final  : public CUI {
private:
	explicit CLevelUp(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CLevelUp(const CLevelUp& rhs);
	virtual ~CLevelUp() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CLevelUp* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END