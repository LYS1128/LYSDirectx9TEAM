#pragma once
#include "Component.h"
#include "Shader.h"

BEGIN(Engine)

class ENGINE_DLL CTexture final : public CComponent{
public:
	enum TYPE { TYPE_DEFAULT, TYPE_CUBE, TYPE_END };
private:
	explicit CTexture(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CTexture(const CTexture& rhs);
	virtual ~CTexture() = default;
public:
	virtual HRESULT NativeConstruct_Prototype(TYPE eTextureType, const _tchar* pTextureFilePath, _uint iNumTextures);
	virtual HRESULT NativeConstruct(void* pArg) override;
public:
	HRESULT Bind_OnGraphicDevice(_uint iIndex = 0);
	HRESULT Bind_OnShader(class CShader* pShader, D3DXHANDLE hParameter, _uint iTextureIndex = 0);
private:
	vector<LPDIRECT3DBASETEXTURE9> m_Textures;
	typedef vector<LPDIRECT3DBASETEXTURE9> TEXTURES;
public:
	static CTexture* Create(LPDIRECT3DDEVICE9 pGraphic_Device, TYPE eTextureType, const _tchar* pTextureFilePath, _uint iNumTextures = 1);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END