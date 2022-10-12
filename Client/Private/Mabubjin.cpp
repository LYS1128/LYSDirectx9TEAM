#include "stdafx.h"
#include "..\Public\Mabubjin.h"

CMabubjin::CMabubjin(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CBoss_Skill(pGraphic_Device)
{
}

CMabubjin::CMabubjin(const CMabubjin & rhs)
	:CBoss_Skill(rhs)
{
}

HRESULT CMabubjin::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMabubjin : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMabubjin::NativeConstruct(void * pArg) {
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

	_float3 vPos = *((_float3*)pArg);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);

	m_pTransform->Set_State(CTransform::STATE_RIGHT, _float3(1.f, 0.f, 0.f));
	m_pTransform->Set_State(CTransform::STATE_UP, _float3(0.f, 0.f, -1.f));
	m_pTransform->Set_State(CTransform::STATE_LOOK, _float3(0.f, 1.f, 0.f));

	m_pTransform->Scaled(_float3(15.f, 15.f, 1.f));
	return S_OK;
}

void CMabubjin::Tick(_float fTimeDelta) {
	m_pTransform->Turn(_float3(0.f, 1.f, 0.f), fTimeDelta);
	++m_iTick;
	if (120 <= m_iTick) {
		if(m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->size() != 0)
			m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossSkill", L"Prototype_GameObject_Boss_Mabubjin_Attack", &(m_pTransform->Get_State(CTransform::STATE_POSITION)));
		m_eState = STATE_DEAD;
	}
}

void CMabubjin::LateTick(_float fTimeDelta) {
	Compute_ZDis(m_pTransform);
	__super::LateTick(fTimeDelta);
}

HRESULT CMabubjin::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CClaw_Attack : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMabubjin::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(10.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Mabubjin"), (CComponent**)&m_pTexture))) {
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

CMabubjin* CMabubjin::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CMabubjin* pInstance = new CMabubjin(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMabubjin : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMabubjin::Clone(void * pArg) {
	CMabubjin* pInstance = new CMabubjin(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMabubjin : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMabubjin::Free() {
	__super::Free();
}