#pragma once
#include "GameObject.h"
#include "Client_Define.h"

BEGIN(Client)

class CEQParticle final : public CGameObject
{
private:
	explicit CEQParticle(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CEQParticle(const CEQParticle& rhs);
	virtual ~CEQParticle() = default;

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
	_uint m_TickCount = 0;
	_float3 m_fGO;
public:
	static CEQParticle* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END