#include "stdafx.h"
#include "..\Public\Semi_1.h"

CSemi_1::CSemi_1(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CSemi_1::CSemi_1(const CSemi_1 & rhs)
	: CUI(rhs)
{
}

HRESULT CSemi_1::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CSemi_1 : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSemi_1::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CSemi_1 : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CSemi_1 : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = g_iWinCX;
	m_tUIInfo.fCY = g_iWinCY;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_iSprite = 0;

	return S_OK;
}

void CSemi_1::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	++m_iTickCount;
	if (m_iTickCount ==3)
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

void CSemi_1::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CSemi_1::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSemi_1 : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSemi_1::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CSemi_1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Semi1"), LEVEL_STAGESEMIBOSS, TEXT("Prototype_Component_Texture_Semi1"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CSemi_1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CSemi_1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CSemi_1 : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CSemi_1 * CSemi_1::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSemi_1*	pInstance = new CSemi_1(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSemi_1 : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CSemi_1::Clone(void * pArg)
{
	CSemi_1*	pInstance = new CSemi_1(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSemi_1 : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSemi_1::Free()
{
	__super::Free();
}
