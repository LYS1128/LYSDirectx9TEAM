#include "stdafx.h"
#include "..\Public\Exp_Text.h"

CExp_Text::CExp_Text(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CExp_Text::CExp_Text(const CExp_Text & rhs)
	: CUI(rhs)
{
}

HRESULT CExp_Text::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CExp_Text : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CExp_Text::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CExp_Text : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CExp_Text : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 7.f;
	m_tUIInfo.fCY = 9.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f - 2.f;		
	m_tUIInfo.fY = g_iWinCY * 0.5f + 355.f;

	m_iUIType = UI_INVENFONT;

	return S_OK;
}

void CExp_Text::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_uint iPercentExp = (_uint)(((_float)m_pPlayer->Get_Player_Info().iExp / m_pPlayer->Get_Player_Info().iMaxExp)*100);
	if((iPercentExp / 10) < 10)
		m_iSprite = iPercentExp / 10;
}

void CExp_Text::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CExp_Text::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CExp_Text : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CExp_Text::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CExp_Text : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Exp_Text"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Exp_Text"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CExp_Text : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CExp_Text : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CExp_Text : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CExp_Text * CExp_Text::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CExp_Text*	pInstance = new CExp_Text(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CExp_Text : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CExp_Text::Clone(void * pArg)
{
	CExp_Text*	pInstance = new CExp_Text(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CExp_Text : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CExp_Text::Free()
{
	__super::Free();
}
