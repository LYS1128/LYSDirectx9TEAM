#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Text.h"

BEGIN(Client)

class CStatWindow final : public CUI
{
private:
	explicit CStatWindow(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CStatWindow(const CStatWindow& rhs);
	virtual ~CStatWindow() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

public:
	static CStatWindow* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END