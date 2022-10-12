#include "stdafx.h"
#include "..\Public\Ground.h"

CGround::CGround(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CGround::CGround(const CGround& rhs)
	:CGameObject(rhs)
{
}

HRESULT CGround::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CGround : NativeConstruct_Prototype");
		return E_FAIL;
	}
	m_fInfo = _float4(0.f, 0.f, 0.f, 0.f);
	return S_OK;
}

HRESULT CGround::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CGround : NativeConstruct");
		return E_FAIL;
	}

	m_iIndex = 0;
	m_fInfo = _float4(0.f, 0.f, 0.f, 0.f);

	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CGround : NativeConstruct");
		return E_FAIL;
	}
	m_iIndex = ((pair<_uint, _float4>*)pArg)->first;
	m_fInfo = ((pair<_uint, _float4>*)pArg)->second;
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(m_fInfo.x, m_fInfo.y, m_fInfo.z));

	return S_OK;
}

void CGround::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CGround::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	if(m_pGameInstance->Check_InOut(m_pTransform->Get_State(CTransform::STATE_POSITION),1.f))
		m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
	return;
}

HRESULT CGround::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CGround : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTexture->Bind_OnGraphicDevice((_uint)m_fInfo.w))) {
		MSG_BOX(L"Failed To CGround : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CGround : Render");
		return E_FAIL;
	}
	m_pVIBuffer->Render();

	return S_OK;
}

HRESULT CGround::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 0.3f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(L"Com_Transform", LEVEL_STATIC, L"Prototype_Component_Transform", (CComponent**)(&m_pTransform)))) {
		MSG_BOX(L"Failed To CGround : SetUp_Component");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Cube", (CComponent**)(&m_pVIBuffer)))) {
		MSG_BOX(L"Failed To CGround : SetUp_Component");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)(&m_pRenderer)))) {
		MSG_BOX(L"Failed To CGround : SetUp_Component");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Texture", LEVEL_STATIC, L"Prototype_Component_Texture", (CComponent**)(&m_pTexture)))) {
		MSG_BOX(L"Failed To CGround : SetUp_Component");
		return E_FAIL;
	}
	return S_OK;
}

_uint CGround::Get_Index() {
	return m_iIndex;
}

CGround* CGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CGround* pInstance = new CGround(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))	{
		MSG_BOX(TEXT("Failed To CGround : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CGround::Clone(void* pArg) {
	CGround* pInstance = new CGround(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CGround : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CGround::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}