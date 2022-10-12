#include "stdafx.h"
#include "..\Public\Semi_2.h"

CSemi_2::CSemi_2(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CSemi_2::CSemi_2(const CSemi_2 & rhs)
	: CUI(rhs)
{
}

HRESULT CSemi_2::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CSemi_2 : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSemi_2::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CSemi_2 : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CSemi_2 : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = g_iWinCX;
	m_tUIInfo.fCY = g_iWinCY;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_iSprite = 0;

	return S_OK;
}

void CSemi_2::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	++m_iTickCount;
	if (m_iTickCount == 3)
	{
		m_iTickCount = 0;
		if (m_bCheck == true)
		{
			++m_iSprite;
			if (m_iSprite >= 13)
				m_iSprite = 13;
		}
	}
}

void CSemi_2::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CSemi_2::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSemi_2 : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSemi_2::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CSemi_2 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Semi2"), LEVEL_STAGESEMIAFTER, TEXT("Prototype_Component_Texture_Semi2"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CSemi_2 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CSemi_2 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CSemi_2 : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CSemi_2 * CSemi_2::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSemi_2*	pInstance = new CSemi_2(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSemi_2 : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CSemi_2::Clone(void * pArg)
{
	CSemi_2*	pInstance = new CSemi_2(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSemi_2 : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSemi_2::Free()
{
	__super::Free();
}
