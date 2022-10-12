#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CMP_UI final : public CUI
{
public:
	explicit CMP_UI(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CMP_UI(const CMP_UI& rhs);
	virtual ~CMP_UI() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	CShader* m_pShader = nullptr;
	_float m_fPercent = 0.f;

public:
	static CMP_UI* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END