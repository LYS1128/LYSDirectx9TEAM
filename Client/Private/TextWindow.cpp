#include "stdafx.h"
#include "..\Public\TextWindow.h"



CTextWindow::CTextWindow(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CTextWindow::CTextWindow(const CTextWindow & rhs)
	: CUI(rhs)
{
}

HRESULT CTextWindow::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CTextWindow : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CTextWindow::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CTextWindow : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CLoad_Spring : NativeConstruct");
		return E_FAIL;
	}

	m_iSprite = 0;
	m_tUIInfo.fCX = g_iWinCX;
	m_tUIInfo.fCY = 300;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY -150;

	return S_OK;
}

void CTextWindow::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CTextWindow::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CTextWindow::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CTextWindow : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CTextWindow::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CTextWindow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_TextWindow"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_TextWindow"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CTextWindow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CTextWindow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CTextWindow : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CTextWindow * CTextWindow::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTextWindow*	pInstance = new CTextWindow(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CTextWindow : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CTextWindow::Clone(void * pArg)
{
	CTextWindow*	pInstance = new CTextWindow(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CTextWindow : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTextWindow::Free()
{
	__super::Free();
}
