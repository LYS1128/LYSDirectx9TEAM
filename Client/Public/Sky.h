#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "GameInstance.h"

BEGIN(Client)

class CSky final : public CGameObject {
private:
	explicit CSky(LPDIRECT3DDEVICE9 pGraphic_Device);
	CSky(const CSky& rhs);
	virtual ~CSky() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	CTransform*	m_pTransformCom = nullptr;
	CVIBuffer_Cube*	m_pVIBufferCom = nullptr;	
	CTexture* m_pTextureCom = nullptr;
	CRenderer* m_pRendererCom = nullptr;
private:
	_uint m_iSprite = 0;
public:
	static CSky* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END