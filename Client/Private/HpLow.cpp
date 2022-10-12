#include "stdafx.h"
#include "..\Public\HpLow.h"


CHpLow::CHpLow(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CHpLow::CHpLow(const CHpLow & rhs)
	: CUI(rhs)
{
}

HRESULT CHpLow::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CHpLow : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CHpLow::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CHpLow : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CHpLow : NativeConstruct");
		return E_FAIL;
	}
	m_tUIInfo.fCX = g_iWinCX;
	m_tUIInfo.fCY = g_iWinCY;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_fZDis = 1.f;

	return S_OK;
}

void CHpLow::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CHpLow::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);

	_uint iHp = dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Get_Player_Info().iHp;
	_uint iMaxHp = dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Get_Player_Info().iMaxHp;
	
	if (_float(iHp/iMaxHp) > 0.2f && dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Get_HpLow() == true) {
		m_eState = STATE_DEAD;
		dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_HpLow(false);
	}
}

HRESULT CHpLow::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CHpLow : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CHpLow::SetUp_Components() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CHpLow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_HpLow"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CHpLow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CHpLow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CHpLow : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CHpLow * CHpLow::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CHpLow* pInstance = new CHpLow(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CHpLow : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CHpLow::Clone(void * pArg) {
	CHpLow* pInstance = new CHpLow(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CHpLow : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHpLow::Free() {
	__super::Free();
}
