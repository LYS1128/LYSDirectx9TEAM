#include "stdafx.h"
#include "..\Public\Exp_Invisible_UI.h"

CExp_Invisible_UI::CExp_Invisible_UI(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CExp_Invisible_UI::CExp_Invisible_UI(const CExp_Invisible_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CExp_Invisible_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CExp_Invisible_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CExp_Invisible_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CExp_Invisible_UI : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CExp_Invisible_UI : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = g_iWinCX + 180.f;
	m_tUIInfo.fCY = 15.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 355.f;


	return S_OK;
}

void CExp_Invisible_UI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	
	_uint iPercentExp = (_uint)(((_float)m_pPlayer->Get_Player_Info().iExp / m_pPlayer->Get_Player_Info().iMaxExp) * 100);

		m_tUIInfo.fX = g_iWinCX * 0.5f + iPercentExp*12.8f;
		if (m_tUIInfo.fX >= 1920.f)
			m_tUIInfo.fX = g_iWinCX * 0.5f;
}

void CExp_Invisible_UI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CExp_Invisible_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CExp_Invisible_UI : Render");
		return E_FAIL;
	}



	return S_OK;
}

HRESULT CExp_Invisible_UI::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CExp_Invisible_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Exp_Invisible_UI"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Exp_Invisible_UI"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CExp_Invisible_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CExp_Invisible_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CExp_Invisible_UI : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CExp_Invisible_UI * CExp_Invisible_UI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CExp_Invisible_UI*	pInstance = new CExp_Invisible_UI(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CExp_Invisible_UI : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CExp_Invisible_UI::Clone(void * pArg)
{
	CExp_Invisible_UI*	pInstance = new CExp_Invisible_UI(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CExp_Invisible_UI : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CExp_Invisible_UI::Free()
{
	__super::Free();
}
