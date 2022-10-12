#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CLoad_Semi0 final : public CUI
{
public:
	explicit CLoad_Semi0(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CLoad_Semi0(const CLoad_Semi0& rhs);
	virtual ~CLoad_Semi0() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

public:
	static CLoad_Semi0* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END