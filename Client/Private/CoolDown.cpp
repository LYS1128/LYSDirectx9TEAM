#include "stdafx.h"
#include "..\Public\CoolDown.h"

CCool_Down::CCool_Down(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CCool_Down::CCool_Down(const CCool_Down & rhs)
	: CUI(rhs)
{
}

HRESULT CCool_Down::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CCool_Down : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCool_Down::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CCool_Down : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CCool_Down : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 45.f;
	m_tUIInfo.fCY = 45.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f - 255.f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 223.f;

	m_iSprite = 0;
	return S_OK;
}

void CCool_Down::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	
	if (m_pPlayer->Get_SkillOpen() & 64)
	{
		++m_iTickCount;
		if (m_iTickCount == 7)
		{
			m_iTickCount = 0;
			if (m_pPlayer->Get_CrayTick() == 120)
			{
				m_iSprite = 0;
			}
			if (m_pPlayer->Get_CrayTick() < 120)
			{
				++m_iSprite;
				if (m_iSprite >= 17)
					m_iSprite = 0;
			}
		}
	}
	else
		m_iSprite = 1;
}

void CCool_Down::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CCool_Down::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CCool_Down : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCool_Down::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CCool_Down : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_CoolDown"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_CoolDown"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CCool_Down : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CCool_Down : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CCool_Down : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CCool_Down * CCool_Down::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CCool_Down*	pInstance = new CCool_Down(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CCool_Down : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCool_Down::Clone(void * pArg)
{
	CCool_Down*	pInstance = new CCool_Down(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CCool_Down : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCool_Down::Free()
{
	__super::Free();
}
