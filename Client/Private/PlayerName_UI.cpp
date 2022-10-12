#include "stdafx.h"
#include "..\Public\PlayerName_UI.h"

CPlayerName_UI::CPlayerName_UI(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CPlayerName_UI::CPlayerName_UI(const CPlayerName_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CPlayerName_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CPlayerName_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPlayerName_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CPlayerName_UI : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CPlayerName_UI : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 120.f;
	m_tUIInfo.fCY = 22.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 330.f;

	return S_OK;
}

void CPlayerName_UI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_iSprite = m_pPlayer->Get_Player_Info().iLevel - 1;
}

void CPlayerName_UI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CPlayerName_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CPlayerName_UI : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPlayerName_UI::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CPlayerName_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_PlayerName_UI"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_PlayerName_UI"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CPlayerName_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CPlayerName_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CPlayerName_UI : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CPlayerName_UI * CPlayerName_UI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayerName_UI*	pInstance = new CPlayerName_UI(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CPlayerName_UI : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CPlayerName_UI::Clone(void * pArg)
{
	CPlayerName_UI*	pInstance = new CPlayerName_UI(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CPlayerName_UI : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayerName_UI::Free()
{
	__super::Free();
}
