#include "stdafx.h"
#include "..\Public\MoonLight.h"

CMoonLight::CMoonLight(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CEffect(pGraphic_Device)
{
}

CMoonLight::CMoonLight(const CMoonLight & rhs)
	:CEffect(rhs)
{
	m_tSkillFrame.fFrame = rhs.m_tSkillFrame.fFrame;
	m_tSkillFrame.iSpriteEnd = rhs.m_tSkillFrame.iSpriteEnd;
	m_fDamagePercent = rhs.m_fDamagePercent;
}

HRESULT CMoonLight::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMoonLight : NativeConstruct_Prototype");
		return E_FAIL;
	}

	m_tSkillFrame.fFrame = 0.f;
	m_tSkillFrame.iSpriteEnd = 13;

	m_fDamagePercent = 10.f;

	return S_OK;
}

HRESULT CMoonLight::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMoonLight : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMoonLight : NativeConstruct");
		return E_FAIL;
	}

	_float3 vPosition = *((_float3*)pArg);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPosition);

	m_iDamage = _uint(m_pPlayer->Get_Player_Info().iAtt * m_fDamagePercent);

	m_pTransform->Scaled(_float3(1.5f, 1.5f, 1.5f));
	return S_OK;
}

void CMoonLight::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CMoonLight::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	BillBoard(m_pTransform);

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CMoonLight::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMoonLight : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMoonLight::SetUp_Components()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 0.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(0.f);
	TransformDesc.fScalePerSec = 0.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CMoonLight : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CMoonLight : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CMoonLight : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_MoonLight"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CMoonLight : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;

}

CMoonLight * CMoonLight::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CMoonLight* pInstance = new CMoonLight(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CMoonLight : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMoonLight::Clone(void * pArg)
{
	CMoonLight* pInstance = new CMoonLight(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CMoonLight : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMoonLight::Free()
{
	__super::Free();
}
