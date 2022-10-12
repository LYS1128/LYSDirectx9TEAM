#include "stdafx.h"
#include "..\Public\Load_Semi0.h"



CLoad_Semi0::CLoad_Semi0(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CLoad_Semi0::CLoad_Semi0(const CLoad_Semi0 & rhs)
	: CUI(rhs)
{
}

HRESULT CLoad_Semi0::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CLoad_Semi0 : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLoad_Semi0::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CLoad_Semi0 : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CLoad_Semi0 : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = g_iWinCX;
	m_tUIInfo.fCY = g_iWinCY;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	
	m_iUIType = UI_LOGO;

	return S_OK;
}

void CLoad_Semi0::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	
}

void CLoad_Semi0::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CLoad_Semi0::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLoad_Semi0 : Render");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CLoad_Semi0::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CLoad_Semi0 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Semi0"), LEVEL_LOADING, TEXT("Prototype_Component_Texture_Semi0"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CLoad_Semi0 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CLoad_Semi0 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CLoad_Semi0 : SetUp_Components");
		return E_FAIL;
	}
	
	return S_OK;
}

CLoad_Semi0 * CLoad_Semi0::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLoad_Semi0*	pInstance = new CLoad_Semi0(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CLoad_Semi0 : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CLoad_Semi0::Clone(void * pArg)
{
	CLoad_Semi0*	pInstance = new CLoad_Semi0(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CLoad_Semi0 : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoad_Semi0::Free()
{
	__super::Free();
}
