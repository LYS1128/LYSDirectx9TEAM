#pragma once
#include "GameObject.h"
#include "Client_Define.h"
#include "Shield.h"
#include "Player.h"

BEGIN(Client)

class CShieldParticle final : public CGameObject
{
private:
	explicit CShieldParticle(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CShieldParticle(const CShieldParticle& rhs);
	virtual~CShieldParticle() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	CTransform* m_pTransform = nullptr;
	CVIBuffer_Cube* m_pVIBuffer = nullptr;
	CTexture* m_pTexture = nullptr;
	CRenderer* m_pRenderer = nullptr;
private:
	HRESULT SetUp_Components();
private:
	CPlayer::EFFECT m_tEffect;
private:
	_uint m_TickCount = 0;
	_float3 m_fGO;
	_float3 m_fLeft;
	_uint m_iRand = 0;
public:
	static CShieldParticle* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END

