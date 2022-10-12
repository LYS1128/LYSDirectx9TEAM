#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CAlphaHP_UI final : public CUI
{
public:
	explicit CAlphaHP_UI(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CAlphaHP_UI(const CAlphaHP_UI& rhs);
	virtual ~CAlphaHP_UI() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

public:
	static CAlphaHP_UI* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END