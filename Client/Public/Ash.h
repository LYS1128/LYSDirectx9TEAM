#pragma once
#include "GameObject.h"
#include "Client_Define.h"
#include "GameInstance.h"

BEGIN(Client)

class CAsh final : public CGameObject
{
private:
	explicit CAsh(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CAsh(const CAsh& rhs);
	virtual ~CAsh() = default;

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
	_float3 m_fGO = _float3(0.f,0.f,0.f);
	_uint m_iSprite = rand() % 5;
public:
	static CAsh* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END