#include "stdafx.h"
#include "..\Public\MoonLight_Effect.h"

CMoonLight_Effect::CMoonLight_Effect(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CEffect(pGraphic_Device)
{
}

CMoonLight_Effect::CMoonLight_Effect(const CMoonLight_Effect & rhs)
	:CEffect(rhs)
{
}

HRESULT CMoonLight_Effect::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMoonLight_Effect : NativeConstruct_Prototype");
		return E_FAIL;
	}

	m_fDamagePercent = 5.0f;

	return S_OK;
}

HRESULT CMoonLight_Effect::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMoonLight_Effect : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMoonLight_Effect : NativeConstruct");
		return E_FAIL;
	}
	m_tSkillFrame.fFrame = 0.f;
	m_tSkillFrame.iSpriteEnd = 13;
	
	m_pTransform->Set_State(CTransform::STATE_POSITION, *((_float3*)(pArg)));
	m_iDamage = _uint(m_pPlayer->Get_Player_Info().iAtt * m_fDamagePercent);

	m_pTransform->Scaled(_float3(2.5f, 2.5f, 2.5f));

	m_eSkillID = SKILL_MOONLIGHT;

	return S_OK;
}

void CMoonLight_Effect::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CMoonLight_Effect::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	BillBoard(m_pTransform);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CMoonLight_Effect::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMoonLight_Effect : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMoonLight_Effect::SetUp_Components() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CMoonLight_Effect : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_MoonLight"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CMoonLight_Effect : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CMoonLight_Effect : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CMoonLight_Effect : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CMoonLight_Effect* CMoonLight_Effect::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CMoonLight_Effect* pInstance = new CMoonLight_Effect(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CMoonLight_Effect : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMoonLight_Effect::Clone(void* pArg) {
	CMoonLight_Effect* pInstance = new CMoonLight_Effect(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CMoonLight_Effect : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMoonLight_Effect::Free() {
	__super::Free();
}