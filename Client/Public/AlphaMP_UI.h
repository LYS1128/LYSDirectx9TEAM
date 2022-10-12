#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CAlphaMP_UI final : public CUI
{
public:
	explicit CAlphaMP_UI(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CAlphaMP_UI(const CAlphaMP_UI& rhs);
	virtual ~CAlphaMP_UI() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

public:
	static CAlphaMP_UI* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END