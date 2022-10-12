#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CExp_Invisible_UI final : public CUI
{
public:
	explicit CExp_Invisible_UI(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CExp_Invisible_UI(const CExp_Invisible_UI& rhs);
	virtual ~CExp_Invisible_UI() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
	

public:
	static CExp_Invisible_UI* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END