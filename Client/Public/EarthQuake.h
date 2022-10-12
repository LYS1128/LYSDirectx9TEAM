#pragma once
#include "Client_Define.h"
#include "GameInstance.h"
#include "Effect.h"
#include "Player.h"

BEGIN(Client)

class CEarthQuake final : public CEffect {
public:
	explicit CEarthQuake(LPDIRECT3DDEVICE9 pGraphic_Device);
	CEarthQuake(const CEarthQuake& rhs);
	virtual ~CEarthQuake() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
	CPlayer::EFFECT m_tEffect;

	_float3		m_fLook;
	_float		m_fFrame = 0.f;
public:
	static CEarthQuake* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();
};

END