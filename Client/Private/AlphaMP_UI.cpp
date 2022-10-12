#include "stdafx.h"
#include "..\Public\AlphaMP_UI.h"

CAlphaMP_UI::CAlphaMP_UI(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CAlphaMP_UI::CAlphaMP_UI(const CAlphaMP_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CAlphaMP_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CAlphaMP_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CAlphaMP_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CAlphaMP_UI : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CAlphaMP_UI : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 200.f;
	m_tUIInfo.fCY = 200.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 243.f;

	return S_OK;
}

void CAlphaMP_UI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CAlphaMP_UI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CAlphaMP_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CAlphaMP_UI : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CAlphaMP_UI::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CAlphaMP_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_AlphaMP_UI"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_AlphaMP_UI"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CAlphaMP_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CAlphaMP_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CAlphaMP_UI : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CAlphaMP_UI * CAlphaMP_UI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CAlphaMP_UI*	pInstance = new CAlphaMP_UI(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CAlphaMP_UI : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CAlphaMP_UI::Clone(void * pArg)
{
	CAlphaMP_UI*	pInstance = new CAlphaMP_UI(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CAlphaMP_UI : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CAlphaMP_UI::Free()
{
	__super::Free();
}
