#include "stdafx.h"
#include "..\Public\Loading_Level4.h"



CLoading_Level4::CLoading_Level4(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CLoading_Level4::CLoading_Level4(const CLoading_Level4 & rhs)
	: CUI(rhs)
{
}

HRESULT CLoading_Level4::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CLoading_Level4 : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLoading_Level4::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CLoading_Level4 : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CLoading_Level4 : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = g_iWinCX;
	m_tUIInfo.fCY = g_iWinCY;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);
	CSound_Manager::GetInstance()->PlaySound(L"Henesis.wav", CSound_Manager::BGM, VOLUME);

	m_iUIType = UI_LOGO;
	m_iSprite = 0;
	return S_OK;
}

void CLoading_Level4::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	
}

void CLoading_Level4::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	++m_iTickCount;

	if (m_iTickCount == 10)
	{
		m_iTickCount = 0;

		++m_iSprite;
		
		if (m_iSprite == 11)
		{
			m_iSprite = 0;
		}
	}
	


}

HRESULT CLoading_Level4::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLoading_Level4 : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLoading_Level4::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CLoading_Level4 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_LDLV4"), LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV4"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CLoading_Level4 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CLoading_Level4 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CLoading_Level4 : SetUp_Components");
		return E_FAIL;
	}
	
	return S_OK;
}

CLoading_Level4 * CLoading_Level4::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLoading_Level4*	pInstance = new CLoading_Level4(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CLoading_Level4 : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CLoading_Level4::Clone(void * pArg)
{
	CLoading_Level4*	pInstance = new CLoading_Level4(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CLoading_Level4 : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoading_Level4::Free()
{
	__super::Free();
}
