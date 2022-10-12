#pragma once
#include "Client_Define.h"
#include "GameObject.h"

BEGIN(Client)

class CBlood final : public CGameObject {
private:
	explicit CBlood(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBlood(const CBlood& rhs);
	virtual ~CBlood() = default;
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
	_float m_fTickCount = 0.f;
	_float m_fOriginPosY = 0.f;
	_uint m_iRand = rand();
	_float3 m_fGO = _float3(0.f, 0.f, 0.f);
public:
	static CBlood* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END