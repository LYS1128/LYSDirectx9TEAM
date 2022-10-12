#include "stdafx.h"
#include "..\Public\Exp_Text2.h"

CExp_Text2::CExp_Text2(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CExp_Text2::CExp_Text2(const CExp_Text2 & rhs)
	: CUI(rhs)
{
}

HRESULT CExp_Text2::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CExp_Text2 : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CExp_Text2::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CExp_Text2 : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CExp_Text2 : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 7.f;
	m_tUIInfo.fCY = 9.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f + 6.f;		
	m_tUIInfo.fY = g_iWinCY * 0.5f + 355.f;

	m_iUIType = UI_INVENFONT;

	return S_OK;
}

void CExp_Text2::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_uint iPercentExp = (_uint)(((_float)m_pPlayer->Get_Player_Info().iExp / m_pPlayer->Get_Player_Info().iMaxExp) * 100);
	if ((iPercentExp % 10) < 10)
		m_iSprite = iPercentExp % 10;
}

void CExp_Text2::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CExp_Text2::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CExp_Text2 : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CExp_Text2::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CExp_Text2 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Exp_Text2"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Exp_Text2"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CExp_Text2 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CExp_Text2 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CExp_Text2 : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CExp_Text2 * CExp_Text2::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CExp_Text2*	pInstance = new CExp_Text2(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CExp_Text2 : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CExp_Text2::Clone(void * pArg)
{
	CExp_Text2*	pInstance = new CExp_Text2(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CExp_Text2 : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CExp_Text2::Free()
{
	__super::Free();
}
