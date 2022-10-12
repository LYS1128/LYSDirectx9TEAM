#pragma once
#include "Client_Define.h"
#include "GameObject.h"

BEGIN(Client)

class CIcePart final : public CGameObject {
private:
	explicit CIcePart(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CIcePart(const CIcePart& rhs);
	virtual ~CIcePart() = default;
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
	_float m_fOriginPosY = 0.f;
	_float3 m_fGO = _float3(0.f, 0.f, 0.f);
	_float m_fG = 0.f;
public:
	static CIcePart* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END