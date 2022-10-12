#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Monster.h"

BEGIN(Client)

class CBossRealHp final : public CUI {
private:
	explicit CBossRealHp(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBossRealHp(const CBossRealHp& rhs);
	virtual ~CBossRealHp() = default;
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
private:
	_float m_fOriginScaleX = 0.f;
public:
	static CBossRealHp* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END