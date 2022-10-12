#pragma once
#include "Client_Define.h"
#include "Effect.h"
#include "Player.h"

BEGIN(Client)

class CIce final : public CEffect {
private:
	explicit CIce(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CIce(const CIce& rhs);
	virtual ~CIce() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CIce* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();
};

END