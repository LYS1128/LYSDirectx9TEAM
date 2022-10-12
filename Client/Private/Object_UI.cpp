#include "stdafx.h"
#include "..\Public\Object_UI.h"

CObject_UI::CObject_UI(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CObject_UI::CObject_UI(const CObject_UI & rhs)
	: CUI(rhs)
{
}

HRESULT CObject_UI::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CObject_UI : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CObject_UI::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CObject_UI : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CObject_UI : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = g_iWinCX;
	m_tUIInfo.fCY = g_iWinCY;
	m_tUIInfo.fX = g_iWinCX * 0.5f;
	m_tUIInfo.fY = g_iWinCY * 0.5f;

	m_iUIType = UI_LOGO;

	return S_OK;
}

void CObject_UI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	
}

void CObject_UI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	++m_iTickCount;

	if (m_iTickCount == 6)
	{
		m_iTickCount = 0;
		++m_iSprite;

		if (m_iSprite == 92)
		{
			//CSoundMgr::Get_Instance()->PlayBGM(L"Winter_Logo.wav");
			CSound_Manager::GetInstance()->PlaySound(L"Winter_Logo.wav", CSound_Manager::BGM, VOLUME);
		}

		if (m_iSprite == 150)
		{
			m_iSprite = 141;
		}
	}
	


}

HRESULT CObject_UI::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CObject_UI : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CObject_UI::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CObject_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_UI"), LEVEL_LOGO, TEXT("Prototype_Component_Texture_UI"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CObject_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CObject_UI : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CObject_UI : SetUp_Components");
		return E_FAIL;
	}
	
	return S_OK;
}

CObject_UI * CObject_UI::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CObject_UI*	pInstance = new CObject_UI(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CObject_UI : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CObject_UI::Clone(void * pArg)
{
	CObject_UI*	pInstance = new CObject_UI(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CObject_UI : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CObject_UI::Free()
{
	__super::Free();
}
