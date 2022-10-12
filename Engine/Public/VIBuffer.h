#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent {
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer() = default;
public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;
	virtual HRESULT Render();
public:
	LPDIRECT3DINDEXBUFFER9 Get_Indices();
protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB = nullptr;
	_uint m_iNumVertices = 0;
	_uint m_iStride = 0;
	_ulong m_dwFVF = 0;
	D3DPRIMITIVETYPE m_ePrimitiveType;
	_uint m_iNumPrimitives = 0;
protected:
	LPDIRECT3DINDEXBUFFER9 m_pIB = nullptr;
	_uint m_iPrimitiveIndicesSize = 0;
	D3DFORMAT m_eFormat;
protected:
	HRESULT Create_VertexBuffer();
	HRESULT Create_IndexBuffer();
public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END