#pragma once

#include "Effect.h"
#include "Client_Define.h"
#include "GameInstance.h"
#include "Player.h"
#include "Collision.h"

BEGIN(Client)

class CFreeze final : public CEffect
{
private:
	explicit CFreeze(LPDIRECT3DDEVICE9 pGraphic_Device);
	CFreeze(const CFreeze& rhs);
	virtual~CFreeze() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

private:
	HRESULT SetUp_Components();
	_float3 m_fGoGoGo;
	CPlayer::EFFECT m_tEffect;

	CCollision* m_pCollision = nullptr;

public:
	static CFreeze* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();

};

END