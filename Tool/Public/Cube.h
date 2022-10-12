#pragma once
#include "Tool_Define.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"
#include "VIBuffer_Cube.h"
#include "Texture.h"
#include "../Default/ToolView.h"

BEGIN(Tool)

class CCube final : public CGameObject {
private:
	explicit CCube(LPDIRECT3DDEVICE9 pGraphic_Device);
	CCube(const CCube& rhs);
	virtual ~CCube() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();

private:
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Cube* m_pVIBufferCom = nullptr;
	CTexture* m_pTextureCom = nullptr;
	CRenderer* m_pRendererCom = nullptr;

private:
	HRESULT SetUp_Components();
	_float4 m_fInfo;

public:
	_float GetDraw() { return m_fInfo.w; }
public:
	static CCube* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END
