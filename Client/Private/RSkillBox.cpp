#include "stdafx.h"
#include "..\Public\RSkillBox.h"

CRSkillBox::CRSkillBox(LPDIRECT3DDEVICE9 pGrpahic_Device)
	:CUI(pGrpahic_Device)
{
}

CRSkillBox::CRSkillBox(const CRSkillBox & rhs)
	: CUI(rhs)
{
}

HRESULT CRSkillBox::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CRSkillBox : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CRSkillBox::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CRSkillBox : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CRSkillBox : NativeConstruct");
		return E_FAIL;
	}

	m_tUIInfo.fCX = 400.f;
	m_tUIInfo.fCY = 200.f;
	m_tUIInfo.fX = g_iWinCX * 0.5f + 220.f;
	m_tUIInfo.fY = g_iWinCY * 0.5f + 250.f;

	return S_OK;
}

void CRSkillBox::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CRSkillBox::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CRSkillBox::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CRSkillBox : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CRSkillBox::SetUp_Components()
{
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CRSkillBox : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_RSkillBox_UI"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_RSkillBox_UI"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CRSkillBox : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CRSkillBox : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CRSkillBox : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CRSkillBox * CRSkillBox::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CRSkillBox*	pInstance = new CRSkillBox(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CRSkillBox : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CRSkillBox::Clone(void * pArg)
{
	CRSkillBox*	pInstance = new CRSkillBox(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CRSkillBox : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRSkillBox::Free()
{
	__super::Free();
}
