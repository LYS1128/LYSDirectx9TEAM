#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CLoading_Level5 final : public CUI
{
public:
	explicit CLoading_Level5(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CLoading_Level5(const CLoading_Level5& rhs);
	virtual ~CLoading_Level5() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();

public:
	static CLoading_Level5* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END