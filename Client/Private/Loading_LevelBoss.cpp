#include "stdafx.h"
#include "..\Public\Loading_LevelBoss.h"



CLoading_LevelBoss::CLoading_LevelBoss(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CLoading_LevelBoss::CLoading_LevelBoss(const CLoading_LevelBoss & rhs)
	: CUI(rhs)
{
}

HRESULT CLoading_LevelBoss::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CLoading_LevelBoss : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLoading_LevelBoss::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CLoading_LevelBoss : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CLoading_LevelBoss : NativeConstruct");
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

void CLoading_LevelBoss::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	
}

void CLoading_LevelBoss::LateTick(_float fTimeDelta)
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

HRESULT CLoading_LevelBoss::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLoading_LevelBoss : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLoading_LevelBoss::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CLoading_LevelBoss : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_LDLVBoss"), LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLVBoss"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CLoading_LevelBoss : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CLoading_LevelBoss : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CLoading_LevelBoss : SetUp_Components");
		return E_FAIL;
	}
	
	return S_OK;
}

CLoading_LevelBoss * CLoading_LevelBoss::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLoading_LevelBoss*	pInstance = new CLoading_LevelBoss(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CLoading_LevelBoss : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CLoading_LevelBoss::Clone(void * pArg)
{
	CLoading_LevelBoss*	pInstance = new CLoading_LevelBoss(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CLoading_LevelBoss : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoading_LevelBoss::Free()
{
	__super::Free();
}