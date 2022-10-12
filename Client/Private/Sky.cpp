#include "stdafx.h"
#include "..\Public\Sky.h"


CSky::CSky(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CSky::CSky(const CSky & rhs)
	:CGameObject(rhs)
{
}

HRESULT CSky::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CSky : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSky::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CSky : NativeConstruct_Prototype");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CSky : NativeConstruct_Prototype");
		return E_FAIL;
	}
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.0f, 0.f, 0.f));
	return S_OK;
}

void CSky::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	// 9 ±úÁö°í ½ÌÅ©¾È¸Â´Â ÀÌ»óÇÑ ÇÏ´Ã /10 ¿ì¿©°îÀı ³¡¿¡ Åº»ıÇÑ ÀÌ»Û ¹àÀº ÇÏ´Ã/ 11 ±úÁö´Â º¸¶ùºû ÇÏ´Ã / 12 °ÅÀÇ CountingStar±Ş ¹ãÇÏ´ÃÀÇ º° / 13 ±úÁö´Â »ç¸·
	if (g_iLevel < 7)
		m_iSprite = 10;
	if (g_iLevel == 8)
		m_iSprite = 3;
	if (g_iLevel == 9)
		m_iSprite = 12;
	if (g_iLevel == 10)
		m_iSprite = 12;
	if (g_iLevel == 12)
		m_iSprite = 13;
	if (g_iLevel == 13)
		m_iSprite = 13;
	if (g_iLevel == 14)
		m_iSprite = 12;
	if (g_iLevel == 15)
		m_iSprite = 3;
}

void CSky::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);

	if (nullptr == m_pGraphic_Device) {
		return;
	}
	_float4x4 ViewMatrix;

	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, *(_float3*)&ViewMatrix.m[3][0]);

	m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_PRIORITY, this);
}

HRESULT CSky::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSky : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(m_iSprite))) {
		MSG_BOX(L"Failed To CSky : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransformCom->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CSky : Render");
		return E_FAIL;
	}
	m_pVIBufferCom->Render();
	return S_OK;
}

HRESULT CSky::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 0.3f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc))) {
		MSG_BOX(L"Failed To CSky : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom))) {
		MSG_BOX(L"Failed To CSky : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Cube"), (CComponent**)&m_pVIBufferCom))) {
		MSG_BOX(L"Failed To CSky : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Sky"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CSky : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CSky* CSky::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CSky* pInstance = new CSky(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))	{
		MSG_BOX(TEXT("Failed To CSky : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CSky::Clone(void* pArg) {
	CSky* pInstance = new CSky(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSky : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSky::Free() {
	__super::Free();
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}