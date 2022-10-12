#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CSemi_2 final : public CUI
{
public:
	explicit CSemi_2(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CSemi_2(const CSemi_2& rhs);
	virtual ~CSemi_2() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
	_bool m_bCheck = false;
public:
	void Set_Check() { m_bCheck = true; }
public:
	static CSemi_2* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END