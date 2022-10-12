#pragma once

#include "Client_Define.h"
#include "Effect.h"
#include "Player.h"

BEGIN(Client)

class CMoonLight final : public CEffect
{
private:
	explicit CMoonLight(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CMoonLight(const CMoonLight& rhs);
	virtual~CMoonLight() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
public:
	static CMoonLight* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();

};

END