#include "stdafx.h"
#include "..\Public\Hit_Effect.h"

CHit_Effect::CHit_Effect(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CEffect(pGraphic_Device)
{
}

CHit_Effect::CHit_Effect(const CHit_Effect& rhs)
	:CEffect(rhs)
{
}

HRESULT CHit_Effect::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CHit_Effect : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CHit_Effect::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CHit_Effect : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CHit_Effect : NativeConstruct");
		return E_FAIL;
	}
	memcpy(&m_tHit, ((HIT*)pArg), sizeof(HIT));

	m_tSkillFrame.fFrame = 0.f;

	switch (m_tHit.eHitType) {
	case SKILL_FREEZE: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Hit_Freeze"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Freeze_Hit"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To Hit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tSkillFrame.iSpriteEnd = 4;
		break;
	}
	case SKILL_CRAY: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Hit_Cray"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Cray_Hit"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To Hit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tSkillFrame.iSpriteEnd = 7;
		break;
	}
	case SKILL_ICE: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Hit_Ice"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ice_Hit"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To Hit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tSkillFrame.iSpriteEnd = 4;
		break;
	}
	case SKILL_EARTHQUAKE: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Hit_Earthquake"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Earthquake_Hit"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To Hit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tSkillFrame.iSpriteEnd = 5;
		break;
	}
	case SKILL_MOONLIGHT: {
		if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Hit_MoonLight"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_MoonLight_Hit"), (CComponent**)&m_pTexture))) {
			MSG_BOX(L"Failed To Hit_Effect : SetUp_Components");
			return E_FAIL;
		}
		m_tSkillFrame.iSpriteEnd = 7;
		break;
	}
	}
	m_pTransform->Set_State(CTransform::STATE_POSITION, m_tHit.vPoisition);
	m_pTransform->Scaled(_float3(2.5f, 2.5f, 2.5f));

	return S_OK;
}

void CHit_Effect::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CHit_Effect::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	BillBoard(m_pTransform);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CHit_Effect::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CHit_Effect : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CHit_Effect::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CHit_Effect : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CHit_Effect : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CHit_Effect : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CHit_Effect* CHit_Effect::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CHit_Effect* pInstance = new CHit_Effect(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CHit_Effect : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CHit_Effect::Clone(void* pArg) {
	CHit_Effect* pInstance = new CHit_Effect(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CHit_Effect : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHit_Effect::Free() {
	__super::Free();
}