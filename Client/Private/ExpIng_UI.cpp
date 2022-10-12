#include "stdafx.h"
#include "..\Public\ExpIng_UI.h"

CExpIng_UI::CExpIng_UI(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CExpIng_UI::CExpIng_UI(const CExpIng_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CExpIng_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CExpIng_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CExpIng_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CExpIng_UI : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CExpIng_UI : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = g_iWinCX + 180.f;
	m_tUIInfo.fCY = 15.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 355.f;


	// 355
	return S_OK;
}

void CExpIng_UI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CExpIng_UI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CExpIng_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CExpIng_UI : Render");
		return E_FAIL;
	}


	return S_OK;
}

HRESULT CExpIng_UI::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CExpIng_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_ExpIng_UI"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_ExpIng_UI"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CExpIng_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CExpIng_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CExpIng_UI : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CExpIng_UI * CExpIng_UI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CExpIng_UI*	pInstance = new CExpIng_UI(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CExpIng_UI : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CExpIng_UI::Clone(void * pArg)
{
	CExpIng_UI*	pInstance = new CExpIng_UI(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CExpIng_UI : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CExpIng_UI::Free()
{
	__super::Free();
}
