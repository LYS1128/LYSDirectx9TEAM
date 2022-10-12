#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "GameInstance.h"

BEGIN(Client)

class CGround final : public CGameObject {
private:
	explicit CGround(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGround(const CGround& rhs);
	virtual ~CGround() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
public:
	HRESULT SetUp_Components();
public:
	_uint Get_Index();
private:
	CTransform* m_pTransform = nullptr;
	CVIBuffer_Cube* m_pVIBuffer = nullptr;
	CRenderer* m_pRenderer = nullptr;
	CTexture* m_pTexture = nullptr;
private:
	_float4 m_fInfo;
	_uint m_iIndex;
public:
	static CGround* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END