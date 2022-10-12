#pragma once
#include "Client_Define.h"
#include "GameInstance.h"

BEGIN(Client)

class CBullet final : public CGameObject {
private:
	explicit CBullet(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBullet(const CBullet& rhs);
	virtual ~CBullet() = default;

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
	CCollision* m_pCollision = nullptr;
private:
	_float3 m_vLook;
	_uint m_iBullet = 20;
private:
	HRESULT SetUp_Components();
public:
	static CBullet* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END