#pragma once
#include "Base.h"
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CShader final : public CComponent {
private:
	explicit CShader(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CShader(const CShader& rhs);
	virtual ~CShader() = default;

public:
	virtual HRESULT NativeConstruct_Prototype(const _tchar* pShaderFilePath);
	virtual HRESULT NativeConstruct(void* pArg);

public:
	HRESULT SetUp_RawValue(D3DXHANDLE hParameter, void* pData, _uint iLength);
	HRESULT SetUp_Texture(D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture);
	HRESULT Begin();
	HRESULT Begin_Pass(_uint iPassIndex);
	HRESULT End_Pass();
	HRESULT End();

private:
	LPD3DXEFFECT	 m_pEffect = nullptr;

public:
	static CShader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, const _tchar* pShaderFilePath);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END