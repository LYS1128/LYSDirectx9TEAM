#pragma once
#include "Client_Define.h"
#include "Effect.h"

BEGIN(Client)

class CHit_Effect final : public CEffect {
public:
	typedef struct tagHit_Effect {
		_float3 vPoisition;
		SKILLID eHitType;
	}HIT;
private:
	explicit CHit_Effect(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CHit_Effect(const CHit_Effect& rhs);
	virtual ~CHit_Effect() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	HIT m_tHit;
public:
	static CHit_Effect* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();
};

END