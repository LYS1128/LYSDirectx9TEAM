#include "stdafx.h"
#include "..\Public\MonsterRealHp.h"

CMonsterRealHp::CMonsterRealHp(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CMonsterRealHp::CMonsterRealHp(const CMonsterRealHp& rhs)
	:CGameObject(rhs)
{
}

HRESULT CMonsterRealHp::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMonsterRealHp : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMonsterRealHp::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMonsterRealHp : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMonsterRealHp : NativeConstruct");
		return E_FAIL;
	}
	m_pMonster = ((MONSTERINFO*)pArg)->pMonster;
	Safe_AddRef(m_pMonster);
	m_pTransform->Set_State(CTransform::STATE_POSITION, ((MONSTERINFO*)pArg)->vPos);
	m_pTransform->Scaled(_float3(1.f, 0.1f, 1.f));
	m_vOriginScale = m_pTransform->Get_Scale();

	return S_OK;
}

void CMonsterRealHp::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	_uint iHp = m_pMonster->Get_Monster_Info().iHp;
	_uint iMaxHp = m_pMonster->Get_Monster_Info().iMaxHp;

	_float fHpPercent = (_float)iHp / iMaxHp;

	_float3 vPos = m_pMonster->Get_Transform()->Get_State(CTransform::STATE_POSITION);
	_float3 vOriginPos = vPos;

	_float3 vRight = m_pTransform->Get_State(CTransform::STATE_RIGHT);
	D3DXVec3Normalize(&vRight, &vRight);

	vPos = vOriginPos - vRight * (1.f - fHpPercent) * 0.5f;

	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos + _float3(0.f, m_pMonster->Get_Transform()->Get_Scale().y*0.3f, 0.f));

	m_pTransform->Scaled(_float3(1.f * fHpPercent, 0.1f, 1.f));
}

void CMonsterRealHp::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	if (STATE_DEAD == m_pMonster->Get_State()) {
		m_eState = STATE_DEAD;
	}
	BillBoard(m_pTransform);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
}

HRESULT CMonsterRealHp::Render() {
	if (FAILED(m_pTexture->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CMonsterRealHp : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CMonsterRealHp : Render");
		return E_FAIL;
	}
	m_pVIBuffer->Render();
	return S_OK;
}

HRESULT CMonsterRealHp::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CMonsterRealHp : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_MonsterRealHp"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CMonsterRealHp : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CMonsterRealHp : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CMonsterRealHp : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CMonsterRealHp* CMonsterRealHp::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CMonsterRealHp*	pInstance = new CMonsterRealHp(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CMonsterRealHp : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMonsterRealHp::Clone(void* pArg) {
	CMonsterRealHp*	pInstance = new CMonsterRealHp(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CMonsterRealHp : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonsterRealHp::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pMonster);
}