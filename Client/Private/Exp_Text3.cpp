#include "stdafx.h"
#include "..\Public\Exp_Text3.h"

CExp_Text3::CExp_Text3(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CExp_Text3::CExp_Text3(const CExp_Text3 & rhs)
	: CUI(rhs)
{
}

HRESULT CExp_Text3::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CExp_Text3 : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CExp_Text3::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CExp_Text3 : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CExp_Text3 : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 11.f;
	m_tUIInfo.fCY = 9.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f + 16.f;		
	m_tUIInfo.fY = g_iWinCY * 0.5f + 355.f;

	m_iUIType = UI_INVENFONT;

	return S_OK;
}

void CExp_Text3::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

}

void CExp_Text3::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CExp_Text3::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CExp_Text3 : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CExp_Text3::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CExp_Text3 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Exp_Text3"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Exp_Text3"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CExp_Text3 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CExp_Text3 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CExp_Text3 : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CExp_Text3 * CExp_Text3::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CExp_Text3*	pInstance = new CExp_Text3(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CExp_Text3 : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CExp_Text3::Clone(void * pArg)
{
	CExp_Text3*	pInstance = new CExp_Text3(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CExp_Text3 : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CExp_Text3::Free()
{
	__super::Free();
}
