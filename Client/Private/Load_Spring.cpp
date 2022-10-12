#include "stdafx.h"
#include "..\Public\Load_Spring.h"



CLoad_Spring::CLoad_Spring(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CLoad_Spring::CLoad_Spring(const CLoad_Spring & rhs)
	: CUI(rhs)
{
}

HRESULT CLoad_Spring::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CLoad_Spring : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLoad_Spring::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CLoad_Spring : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CLoad_Spring : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = g_iWinCX;
	m_tUIInfo.fCY = g_iWinCY;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);
	CSound_Manager::GetInstance()->PlaySound(L"Henesis.wav", CSound_Manager::BGM, VOLUME);

	m_iUIType = UI_LOGO;

	return S_OK;
}

void CLoad_Spring::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	
}

void CLoad_Spring::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	++m_iTickCount;

	if (m_iTickCount == 10)
	{
		m_iTickCount = 0;
		++m_iSprite;

		if (m_iSprite == 116)
		{
			// Logo_Winter.wav
		}

		if (m_iSprite == 12)
		{
			m_iSprite = 0;
		}
	}
	


}

HRESULT CLoad_Spring::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLoad_Spring : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLoad_Spring::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CLoad_Spring : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_LDSPR0"), LEVEL_LOADING, TEXT("Prototype_Component_Texture_UI_LDSPR0"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CLoad_Spring : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CLoad_Spring : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CLoad_Spring : SetUp_Components");
		return E_FAIL;
	}
	
	return S_OK;
}

CLoad_Spring * CLoad_Spring::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLoad_Spring*	pInstance = new CLoad_Spring(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CLoad_Spring : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CLoad_Spring::Clone(void * pArg)
{
	CLoad_Spring*	pInstance = new CLoad_Spring(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CLoad_Spring : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoad_Spring::Free()
{
	__super::Free();
}
