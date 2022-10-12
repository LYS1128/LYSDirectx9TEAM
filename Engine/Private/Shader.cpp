#include "..\Public\Shader.h"

CShader::CShader(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CComponent(pGraphic_Device)
{
}

CShader::CShader(const CShader & rhs)
	:CComponent(rhs)
	,m_pEffect(rhs.m_pEffect)
{
	Safe_AddRef(m_pEffect);
}

HRESULT CShader::NativeConstruct_Prototype(const _tchar * pShaderFilePath) {
	if (FAILED(D3DXCreateEffectFromFile(m_pGraphic_Device, pShaderFilePath, nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr))) {
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CShader::NativeConstruct(void * pArg) {
	return S_OK;
}

HRESULT CShader::SetUp_RawValue(D3DXHANDLE hParameter, void * pData, _uint iLength) {
	if (nullptr == m_pEffect) {
		return E_FAIL;
	}
	return m_pEffect->SetRawValue(hParameter, pData, 0, iLength);
}

HRESULT CShader::SetUp_Texture(D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture) {
	if (nullptr == m_pEffect) {
		return E_FAIL;
	}
	return m_pEffect->SetTexture(hParameter, pTexture);
}

HRESULT CShader::Begin() {
	if (nullptr == m_pEffect) {
		return E_FAIL;
	}
	return m_pEffect->Begin(nullptr, 0);
}

HRESULT CShader::Begin_Pass(_uint iPassIndex) {
	if (nullptr == m_pEffect) {
		return E_FAIL;
	}
	return m_pEffect->BeginPass(iPassIndex);
}

HRESULT CShader::End_Pass() {
	if (nullptr == m_pEffect) {
		return E_FAIL;
	}
	return m_pEffect->EndPass();
}

HRESULT CShader::End() {
	if (nullptr == m_pEffect) {
		return E_FAIL;
	}
	return m_pEffect->End();
}

CShader * CShader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, const _tchar * pShaderFilePath) {
	CShader*	pInstance = new CShader(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype(pShaderFilePath))) 	{
		MSG_BOX(TEXT("Failed To CShader : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CShader::Clone(void * pArg) {
	CShader*	pInstance = new CShader(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) 	{
		MSG_BOX(TEXT("Failed To CShader : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CShader::Free() {
	__super::Free();
	Safe_Release(m_pEffect);
}