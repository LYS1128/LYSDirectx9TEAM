#include "stdafx.h"
#include "..\Public\LSkillBox.h"

CLSkillBox::CLSkillBox(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CLSkillBox::CLSkillBox(const CLSkillBox & rhs)
	: CUI(rhs)
{
}

HRESULT CLSkillBox::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CLSkillBox : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLSkillBox::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CLSkillBox : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CLSkillBox : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 400.f;
	m_tUIInfo.fCY = 200.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f - 220.f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 250.f;

	return S_OK;
}

void CLSkillBox::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CLSkillBox::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CLSkillBox::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLSkillBox : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLSkillBox::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CLSkillBox : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_LSkillBox_UI"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_LSkillBox_UI"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CLSkillBox : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CLSkillBox : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CLSkillBox : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CLSkillBox * CLSkillBox::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CLSkillBox*	pInstance = new CLSkillBox(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CLSkillBox : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CLSkillBox::Clone(void * pArg)
{
	CLSkillBox*	pInstance = new CLSkillBox(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CLSkillBox : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLSkillBox::Free()
{
	__super::Free();
}
