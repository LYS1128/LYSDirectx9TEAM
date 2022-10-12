#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CSemi_1 final : public CUI
{
public:
	explicit CSemi_1(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CSemi_1(const CSemi_1& rhs);
	virtual ~CSemi_1() = default;
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
	_uint Get_End() { return m_iSprite; }
public:
	static CSemi_1* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END