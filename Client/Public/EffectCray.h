#pragma once
#include "Effect.h"
#include "Client_Define.h"
#include "GameInstance.h"
#include "Player.h"
#include "Collision.h"

BEGIN(Client)

class CEffectCray final : public CEffect
{

public:
	explicit CEffectCray(LPDIRECT3DDEVICE9 pGraphic_Device);
	CEffectCray(const CEffectCray& rhs);
	virtual ~CEffectCray() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

public:
	void Collision_Ground();
	void Gravity(_float fTimeDelta);
private:
	HRESULT SetUp_Components();
	_float3 m_fGoGoGo;
	_uint m_iTickk = 0;
	CPlayer::EFFECT m_tEffect;
	_bool ParticleEnd = false;
	CCollision* m_pCollision = nullptr;

public:
	static CEffectCray* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();


};

END
