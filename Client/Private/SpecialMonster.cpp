#include "stdafx.h"
#include "..\Public\SpecialMonster.h"
#include "../Public/Level_StageSpecial.h"

CSpecialMonster::CSpecialMonster(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CSpecialMonster::CSpecialMonster(const CSpecialMonster & rhs)
	:CMonster(rhs)
{
}

HRESULT CSpecialMonster::NativeConstruct_Prototype() {
	return S_OK;
}

HRESULT CSpecialMonster::NativeConstruct(void * pArg) {
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CSpecialMonster : NativeConstruct");
		return E_FAIL;
	}
	m_pLevel = (CLevel_StageSpecial*)pArg;
	Safe_AddRef(m_pLevel);

	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(_float(rand() % 25), 1.f, 24.f));
	m_pTransform->Scaled(_float3(1.f, 1.f, 1.f));

	m_eMState = MONSTER_WALK;
	m_iSprite = 8;

	m_tInfo.iMaxHp = 100;
	m_tInfo.iHp = m_tInfo.iMaxHp;

	return S_OK;
}

void CSpecialMonster::Tick(_float fTimeDelta) {
	if (MONSTER_DEAD != m_eMState) {
		CTransform* pTargetTransform = (CTransform*)(m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));
		_float3 vTargetPos = pTargetTransform->Get_State(CTransform::STATE_POSITION);
		m_pTransform->Chase(vTargetPos, fTimeDelta, 0.5f);
	}
	if (MONSTER_DEAD != m_eMState) {
		Collision_Bullet();
	}
}

void CSpecialMonster::LateTick(_float fTimeDelta) {
	if (3.f >= m_pTransform->Get_State(CTransform::STATE_POSITION).z) {
		m_eState = STATE_DEAD;
		m_pLevel->Life();
	}
	Move_Frame();
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CSpecialMonster::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSpecialMonster : Render");
		return E_FAIL;
	}
	return S_OK;
}

void CSpecialMonster::Collision_Bullet() {
	list<CGameObject*>* pBulletList = m_pGameInstance->Find_Layer_List(LEVEL_STAGESPECIAL, L"Layer_Bullet");
	if (nullptr == pBulletList) {
		return;
	}

	for (auto& iter : *pBulletList) {
		if (m_pCollision->Collision_Sphere(m_pTransform, (CTransform*)(iter->Get_Component(L"Com_Transform")))) {
			iter->Set_Dead();
			m_pLevel->Score();
			m_eMState = MONSTER_DEAD;
		}
	}
}

void CSpecialMonster::Move_Frame() {
	++m_iTick;
	if (MONSTER_WALK == m_eMState) {
		if (20 <= m_iTick) {
			m_iTick = 0;
			++m_iSprite;
			if (12 <= m_iSprite) {
				m_iSprite = 8;
			}
		}
	}
	else if (MONSTER_DEAD == m_eState) {
		if (10 <= m_iTick) {
			m_iTick = 0;
			++m_iSprite;
			if (25 <= m_iSprite) {
				m_iSprite = 14;
				m_eState = STATE_DEAD;
			}
		}
	}
}

HRESULT CSpecialMonster::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGESPECIAL, TEXT("Prototype_Component_Texture_Special"), (CComponent**)&m_pTexture))) {
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
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CSpecialMonster * CSpecialMonster::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CSpecialMonster*	pInstance = new CSpecialMonster(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSpecialMonster : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CSpecialMonster::Clone(void * pArg) {
	CSpecialMonster*	pInstance = new CSpecialMonster(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSpecialMonster : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSpecialMonster::Free() {
	__super::Free();
	Safe_Release(m_pLevel);
}