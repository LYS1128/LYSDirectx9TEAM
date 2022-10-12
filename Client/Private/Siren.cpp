#include "stdafx.h"
#include "..\Public\Siren.h"



CSiren::CSiren(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CSiren::CSiren(const CSiren & rhs)
	: CUI(rhs)
{
}

HRESULT CSiren::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CSiren : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSiren::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CSiren : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CSiren : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = g_iWinCX;
	m_tUIInfo.fCY = g_iWinCY;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;
	CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
	CSound_Manager::GetInstance()->PlaySound(L"Siren.wav", CSound_Manager::EFFECT, VOLUME);

	m_iUIType = UI_LOGO;
	m_iSprite = 0;
	return S_OK;
}

void CSiren::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	
}

void CSiren::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	++m_iTickCount;

	if (m_iTickCount == 15)
	{
		m_iTickCount = 0;

		++m_iSprite;
		
		if (m_iSprite == 11)
		{
			m_iSprite = 0;
			m_iSirenCount += 1;
		}
	}
	
	if (m_iSirenCount == 5)
		m_eState = STATE_DEAD;


}

HRESULT CSiren::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSiren : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSiren::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CSiren : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Siren"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Siren"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CSiren : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CSiren : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CSiren : SetUp_Components");
		return E_FAIL;
	}
	
	return S_OK;
}

CSiren * CSiren::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSiren*	pInstance = new CSiren(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSiren : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CSiren::Clone(void * pArg)
{
	CSiren*	pInstance = new CSiren(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSiren : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSiren::Free()
{
	__super::Free();
}
