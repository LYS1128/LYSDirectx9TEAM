#include "stdafx.h"
#include "..\Public\MonsterHpBar.h"

CMonsterHpBar::CMonsterHpBar(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CMonsterHpBar::CMonsterHpBar(const CMonsterHpBar& rhs)
	:CGameObject(rhs)
{
}

HRESULT CMonsterHpBar::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMonsterHpBar : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMonsterHpBar::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMonsterHpBar : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMonsterHpBar : NativeConstruct");
		return E_FAIL;
	}
	m_pMonster = ((MONSTERINFO*)pArg)->pMonster;
	Safe_AddRef(m_pMonster);
	m_pTransform->Set_State(CTransform::STATE_POSITION, ((MONSTERINFO*)pArg)->vPos);
	m_pTransform->Scaled(_float3(1.f, 0.1f, 1.f));

	return S_OK;
}

void CMonsterHpBar::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	m_pTransform->Set_State(CTransform::STATE_POSITION, m_pMonster->Get_Transform()->Get_State(CTransform::STATE_POSITION) + _float3(0.f, m_pMonster->Get_Transform()->Get_Scale().y*0.3f, 0.f));
}

void CMonsterHpBar::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	if (STATE_DEAD == m_pMonster->Get_State()) {
		m_eState = STATE_DEAD;
	}
	BillBoard(m_pTransform);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CMonsterHpBar::Render() {
	if (FAILED(m_pTexture->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CMonsterHpBar : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CMonsterHpBar : Render");
		return E_FAIL;
	}
	m_pVIBuffer->Render();
	return S_OK;
}

HRESULT CMonsterHpBar::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_MonsterHpBar"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CMonsterHpBar* CMonsterHpBar::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CMonsterHpBar*	pInstance = new CMonsterHpBar(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CMonsterHpBar : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMonsterHpBar::Clone(void* pArg) {
	CMonsterHpBar*	pInstance = new CMonsterHpBar(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CMonsterHpBar : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonsterHpBar::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pMonster);
}
