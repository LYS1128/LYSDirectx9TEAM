#include "stdafx.h"
#include "..\Public\Circle.h"

CCircle::CCircle(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CCircle::CCircle(const CCircle & rhs)
	:CBoss_Skill(rhs)
{
}

HRESULT CCircle::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMabubjin : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCircle::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMabubjin : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMabubjin : NativeConstruct");
		return E_FAIL;
	}

	m_tBossSkillFrame.fFrame = 0.f;
	m_tBossSkillFrame.iSpriteEnd = 1;
	m_iSprite = *((_uint*)pArg);

	CTransform* pTransform = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	m_pTransform->Set_State(CTransform::STATE_LOOK, pTransform->Get_State(CTransform::STATE_LOOK));
	m_pTransform->Set_State(CTransform::STATE_RIGHT, pTransform->Get_State(CTransform::STATE_RIGHT));
	m_pTransform->Set_State(CTransform::STATE_UP, pTransform->Get_State(CTransform::STATE_UP));
	m_pTransform->Set_State(CTransform::STATE_POSITION, dynamic_cast<CTransform*>(m_pGameInstance->Get_Component(LEVEL_STAGEBOSS, L"Layer_Boss", L"Com_Transform"))->Get_State(CTransform::STATE_POSITION) + _float3(1.5f, 1.f, 1.5f));

	m_pTransform->Scaled(_float3(10.f, 10.f, 10.f));
	return S_OK;
}

void CCircle::Tick(_float fTimeDelta) {
	m_pTransform->Turn(_float3(-1.f, 0.f, -1.f), fTimeDelta);
	++m_iTick;
	if (120 <= m_iTick) {
			m_eState = STATE_DEAD;
	}
}

void CCircle::LateTick(_float fTimeDelta) {
	Compute_ZDis(m_pTransform);
	__super::LateTick(fTimeDelta);
}

HRESULT CCircle::Render() {
	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iSprite))) {
		MSG_BOX(L"Failed To CEffect : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CEffect : Render");
		return E_FAIL;
	}
	m_pVIBuffer->Render();
	return S_OK;
}

HRESULT CCircle::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(10.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Circle"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CCircle* CCircle::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CCircle* pInstance = new CCircle(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMabubjin : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCircle::Clone(void * pArg) {
	CCircle* pInstance = new CCircle(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMabubjin : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCircle::Free() {
	__super::Free();
}