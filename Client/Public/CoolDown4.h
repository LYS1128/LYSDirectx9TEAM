#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CCool_Down4 final : public CUI
{
public:
	explicit CCool_Down4(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CCool_Down4(const CCool_Down4& rhs);
	virtual ~CCool_Down4() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

public:
	static CCool_Down4* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END