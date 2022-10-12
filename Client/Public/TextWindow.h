#pragma once
#include "Client_Define.h"
#include "UI.h"

BEGIN(Client)

class CTextWindow final : public CUI
{
private:
	explicit CTextWindow(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CTextWindow(const CTextWindow& rhs);
	virtual ~CTextWindow() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

public:
	static CTextWindow* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END