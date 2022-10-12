#pragma once
#include "Client_Define.h"
#include "Effect.h"

class CMoonLight_Effect final : public CEffect {
private:
	explicit CMoonLight_Effect(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CMoonLight_Effect(const CMoonLight_Effect& rhs);
	virtual ~CMoonLight_Effect() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CMoonLight_Effect* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();
};

