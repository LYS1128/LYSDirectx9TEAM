#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Text.h"

BEGIN(Client)

class CBullet_UI final : public CUI
{
private:
	explicit CBullet_UI(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CBullet_UI(const CBullet_UI& rhs);
	virtual ~CBullet_UI() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

public:
	static CBullet_UI* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END