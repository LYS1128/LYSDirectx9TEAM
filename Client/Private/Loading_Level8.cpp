#include "stdafx.h"
#include "..\Public\Loading_Level8.h"



CLoading_Level8::CLoading_Level8(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CLoading_Level8::CLoading_Level8(const CLoading_Level8 & rhs)
	: CUI(rhs)
{
}

HRESULT CLoading_Level8::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CLoading_Level8 : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLoading_Level8::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CLoading_Level8 : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CLoading_Level8 : NativeConstruct");
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

void CLoading_Level8::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	
}

void CLoading_Level8::LateTick(_float fTimeDelta)
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

HRESULT CLoading_Level8::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLoading_Level8 : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLoading_Level8::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CLoading_Level8 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_LDLV8"), LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV8"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CLoading_Level8 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CLoading_Level8 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CLoading_Level8 : SetUp_Components");
		return E_FAIL;
	}
	
	return S_OK;
}

CLoading_Level8 * CLoading_Level8::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLoading_Level8*	pInstance = new CLoading_Level8(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CLoading_Level8 : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CLoading_Level8::Clone(void * pArg)
{
	CLoading_Level8*	pInstance = new CLoading_Level8(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CLoading_Level8 : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoading_Level8::Free()
{
	__super::Free();
}
