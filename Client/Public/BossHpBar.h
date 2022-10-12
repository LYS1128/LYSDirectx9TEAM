#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "NooNoo.h"

BEGIN(Client)

class CBossHpBar final : public CUI {
private:
	explicit CBossHpBar(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBossHpBar(const CBossHpBar& rhs);
	virtual ~CBossHpBar() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	CMonster* m_pTargetMonster = nullptr;
public:
	static CBossHpBar* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END